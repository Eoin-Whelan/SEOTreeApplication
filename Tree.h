/*
	Title:		Tree.h
	Author:		Eoin Farrell
	DOC:		26/01/2020
	Purpose:	Header file for Tree class. Includes:
				- Definitions for node-relevant functions
				- Class attributes
*/

#pragma once
#include "Node.h"
#include <vector>
class Tree
{
private:
public:
	// Node ptr attribute
	Node* root;
	// Constructor
	Tree();

	// Getter/Setter methods
	void setRoot(Node* newRoot) { root = newRoot; };
	Node* getRoot() { return root; }

	// Value returning methods
	Node* put(Node* root, std::string keyWord, std::string givenURL);
	int count(std::string keyword, Node* root);

	double URLcount(std::string given_URL, Node* root);
	double calculateSEOscore(std::string given_URL);
	double InorderCount(Node* root);

	void URLAssociation(Node* root, std::string given_URL);

	int funcF(Node* root);

	std::string returnSucc(Node* root, std::string givenName);

	// Void methods
	void get(Node* root, std::string keyWord);
	void deleteURL(std::string given_URL, std::string keyword, Node* root);

	void printOrder(Node* root);
	void printSeoScores();
	void popularKeywords();
};