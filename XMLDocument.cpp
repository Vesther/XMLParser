#include "stdafx.h"
#include "XMLDocument.h"

// Note:
// Absolutely all of this, every single part is a horrible hack.
// I am certain not a single parser actually works like this.

using namespace std;

// ##################
// Attribute
// ##################

void XMLDocument::Node::Attribute::parse(string str)
{
	int pos = str.find('=');
	this->name = str.substr(0, pos);
	this->value = str.substr(pos + 1, str.length() - pos);
}

XMLDocument::Node::Attribute::Attribute(string str)
{
	parse(str);
}


// ##################
// Node
// ##################
void XMLDocument::Node::print_node()
{
	cout << endl;

	cout << "Node name: " << endl << "    " << name << endl;
	cout << "Node content: " << endl << "    " << this->content << endl;
	cout << "Node attributes: " << endl;
	for (Attribute a : attributes)
	{
		cout << "    " << a.name << " --> " << a.value << endl;
	}
	cout << "---------------------------" << endl;
}

void XMLDocument::Node::print_children()
{
	cout << endl;

	cout << "Node children: " << endl;
	for (Node* n : children)
	{
		cout << n->name << endl;
	}
}

void XMLDocument::Node::print_children_with_id()
{
	cout << endl;

	cout << "Node children: " << endl;
	for (int i = 0; i < children.size(); i++)
	{
		cout << i << ": " << children[i]->name << endl;
	}
}

void XMLDocument::Node::print_tree(Node* node, int depth)
{
	if (depth == 0)
	{
		cout << node->name << endl;
		depth += 4;
	}
	for (Node* n : node->children)
	{
		for (int i = 0; i < depth; i++) cout << " ";
		cout << n->name << endl;
		print_tree(n, depth + 4);
	}
}


// ##################
// XMLDocument
// ##################

// Tokenizes into tags and values, prefixes values with $$$
vector<string> XMLDocument::lex(string str)
{
	vector<string> vec;

	// Remove newlines from input string
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

	int pos = 0;
	while ((pos = str.find('<', pos)) != string::npos)
	{
		int end_pos = str.find('>', pos);
		vec.push_back(str.substr(pos, end_pos - pos + 1));
		// Check for value inbetween > < tags
		int temp_pos;
		if ((temp_pos = str.find('<', end_pos)) != string::npos)
		{
			string between_tags = str.substr(end_pos + 1, temp_pos - end_pos - 1);
			if (between_tags.find_first_not_of(' ') != std::string::npos)
			{
				vec.push_back("$$$" + between_tags);
			}
		}
		pos++;
	}

	// (Debug) Print token vector 
	for (string s : vec)
	{
		char temp;
		cout << "    " << s << endl;
		//cout << "-------------" << endl;
	}

	return vec;
}

// Helper function to split by whitespace
vector<string> XMLDocument::split_by_whitespace(string str)
{
	vector<string> tokens;
	stringstream tag_stream(str);
	string buffer;
	while (tag_stream >> buffer)
		tokens.push_back(buffer);
	return tokens;
}

// Extracts <? ?> processing instructions and XML Declaration
vector<string>::iterator XMLDocument::extract_processing_instructions(vector<string>& vec)
{
	// Todo
	return vec.begin();
}

// Removes comments from original token vector
vector<string>::iterator XMLDocument::extract_comments(vector<string>& vec)
{
	// Todo
	return vec.begin();
}

// Creates a Tree of Nodes from lexed file 
XMLDocument::Node* XMLDocument::parse(vector<string>& vec, vector<string>::iterator it)
{
	Node* tag = new Node;
	string str = *it;

	// Get whole tag without < and >
	str = str.substr(1, str.length() - 2);

	// Split by whitespace
	vector<string> tokens = split_by_whitespace(str);

	tag->name = tokens[0];
	if (tokens.size() > 1)
	{
		for (int i = 1; i < tokens.size(); i++)
		{
			tag->attributes.push_back(Node::Attribute(tokens[i]));
		}
	}
	tag->print_node();

	if (int pos = (*next(it, 1)).find("$$$") != string::npos)
	{
		tag->content = (*next(it, 1)).substr(3, (*next(it, 1)).length() - 3);
		vec.erase(next(it, 1), next(it, 2));
	}

	if ((*next(it, 1)).find("</") != string::npos)
	{
		vec.erase(it, next(it, 2));
	}
	else
	{
		while ((*next(it, 1)).find("</") == string::npos)
		{
			tag->children.push_back(parse(vec, (next(it, 1))));
		}
		if ((*next(it, 1)).find("</") != string::npos)
		{
			vec.erase(it, next(it, 2));
		}
	}

	return tag;
	}

// Recursively constructs the new XML File as a string
string XMLDocument::write(Node* node, int depth)
{
	string temp = "";
	temp.append(string(depth, ' '));
	temp.append("<");
	temp.append(node->name);
	for (Node::Attribute n : node->attributes)
	{
		temp.append(" ");
		temp.append(n.name);
		temp.append("=");
		temp.append(n.value);
	}
	temp.append(">");
	temp.append("\n");

	if (!node->content.empty())
	{
		temp.append(string(depth + 4, ' '));
		temp.append(node->content);
		temp.append("\n");

	}

	for (Node* n : node->children)
	{
		temp.append(write(n, depth + 4));
	}
	temp.append(string(depth, ' '));
	temp.append("</");
	temp.append(node->name);
	temp.append(">");
	temp.append("\n");

	return temp;
}

// Calls write() to create the string and then writes it to file
void XMLDocument::save()
{
	ofstream file("saved.xml");
	file << write(head);

	//cout << write(head);

	file.close();
}

