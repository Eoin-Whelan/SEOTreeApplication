/*
	Title:		Node.h
	Author:		Eoin Farrell
	DOC:		26/01/2020
	Purpose:	Header file for Node class. Includes:
				- Definitions for node-relevant functions
				- Class attributes
*/

#pragma once
#include <string>
#include <list> 

struct Node {
private:
	//	Static list of URLs
	static std::list<std::string> treeURLs;
	//	Non-static list of ptrs to which URLs are associated with a keyword.
	std::list<std::string*>	keyWordURLs;
	std::string keyWord;
	//	Child ptrs
	Node* lChild = NULL;
	Node* rChild = NULL;
public:
	//	Contstructors
	Node(std::string keyword);
	Node(std::string newKeyword, std::string passedURL);
	Node();
	// Getter/Setter methods
	static std::list<std::string>* getTreeURLs() { return &treeURLs; }

	void setLChild(Node* passedAddress);
	void setRChild(Node* passedAddress);
	Node* getLChild() { return lChild; };
	Node* getRChild() { return rChild; };
	std::string getKeyWord() { return keyWord; };
	std::list<std::string*> getKeyWordURLs() { return keyWordURLs; }
	std::list<std::string*>* getKeyWordURLAddress() { return &keyWordURLs; }
	std::string* getURLAddress(std::string URLtext);

	bool isURL(std::string URLtext);

	// URL list manipulating methods.
	void addURL(std::string* newURL);
	bool deleteURL(std::string given_url);

	// Void methods
	void printNodeURLs();
	int funcF(Node* root);
};
