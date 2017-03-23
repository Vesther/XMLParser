// ParseXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>
#include "XMLDocument.h"

using namespace std;

int main()
{
	fstream file;
	file.open("test.xml");
	stringstream buffer;
	buffer << file.rdbuf();

	XMLDocument test;
	vector<string> vec = test.lex(buffer.str());
	test.head = test.parse(vec, vec.begin());
	test.head->children[0]->print_children();

	cout << endl << "---------------------" << endl << "Treeee:" << endl << endl;
	test.head->print_tree(test.head);

	int temp = 0;
	XMLDocument::Node* ptr = test.head;
	
	while (true)
	{
		system("cls");
		ptr->print_node();
		ptr->print_children_with_id();
		cin >> temp;
		ptr = ptr->children[temp];
	}
	

	system("cls");

	test.save();
	return 0;
}

