#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

class XMLDocument
{
public:
	class Node
	{
	public:
		class Attribute
		{
		public:
			string name;
			string value;

			Attribute(string str);

			void parse(string str);
		};

		string name;
		string content;
		vector<Attribute> attributes;
		vector<Node*> children;

		void print_node();

		void print_children();

		void print_children_with_id();

		void print_tree(Node* node, int depth = 0);
	};

	// Tokenizes into tags
	vector<string> lex(string str);

	// Helper function to split by whitespace
	vector<string> split_by_whitespace(string str);

	// Extracts <? ?> processing instructions and XML Declaration
	vector<string>::iterator extract_processing_instructions(vector<string>& vec);

	// Removes comments from original token vector
	vector<string>::iterator extract_comments(vector<string>& vec);

	// Creates a Tree of Nodes from lexed file 
	Node* parse(vector<string>& vec, vector<string>::iterator it);

	Node* head;

	void save();

	string write(Node* node, int depth = 0);
};