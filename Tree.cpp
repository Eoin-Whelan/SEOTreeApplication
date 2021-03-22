/*
	Title:		Tree.cpp
	Author:		Eoin Farrell
	DOC:		10/02/2020
	Purpose:	Tree class implementation of class functions.
*/

#include "Tree.h"
#include "Node.h"
#include <list> 
#include <vector>
#include <iostream>

//	Constructor
Tree::Tree()
{
	root = NULL;
}

// Outputs every keyword in the tree in alphabetical order using a recursive InOrder traversal. 
void Tree::printOrder(Node* root)
{
	if (root) {
		printOrder(root->getLChild());
		std::cout << root->getKeyWord() << '\n';
		printOrder(root->getRChild());
	}
}
/*	Recursive function which allows an input keyword to be associated with an input URL. 
	If a keyword does not exist in the tree, it is added and the URL association is created. 
*/
Node* Tree::put(Node* root, std::string keyWord, std::string givenURL)
{
	int URLAssocations = URLcount(givenURL, this->getRoot());
	Node* newNode;
	if (!root) {
		if (URLAssocations < 4) {
			newNode = new Node(keyWord, givenURL);
		}
		else {
			std::cout << "\nURL association limited reached! Keyword: " << keyWord << " added to tree, \nhowever URL: " << givenURL << " has not been added as an association.\n\n";
			newNode = new Node(keyWord);
		}
		root = newNode;
		return root;
	}
	else if (root->getKeyWord() == keyWord) {
		if (root->getKeyWordURLs().size() < 5) {
			std::list<std::string*> urlPtr = root->getKeyWordURLs();
			std::list<std::string*>::iterator urlIterator = urlPtr.begin();
			for (urlIterator; urlIterator != urlPtr.end(); urlIterator++) {
				if (**urlIterator == givenURL) {
					std::cout << givenURL << " already exists in list. Duplicate Entry Ignored.\n";
					return root;
				}
			}
			root->addURL(root->getURLAddress(givenURL));
			std::cout << "\n\n" << givenURL << " has been associated with " << keyWord;
		}
		else {
			std::cout << "Maximum associations for " << keyWord << " reached.\n\nPlease remove an associated address before adding " << givenURL << ".\n";
			return root;
		}
	}
	else if (root->getKeyWord() > keyWord) {
		root->setLChild(put(root->getLChild(), keyWord, givenURL));
	}
	else {
		root->setRChild(put(root->getRChild(), keyWord, givenURL));
	}
	return root;
}

/*	Returns the list of URLs associated with a given keyword using InOrder traversal to find 
	the keyword and output each association.
*/
void Tree::get(Node* root, std::string keyWord)
{
	if (!root) {
		std::cout << '\n' <<  keyWord << " is not found.\n";
		return;
	}
	if (root->getKeyWord() == keyWord) {
		root->printNodeURLs();
	}
	else if (root->getKeyWord() > keyWord) {
		get(root->getLChild(), keyWord);
	}
	else {
		get(root->getRChild(), keyWord);
	}
}

/*	Returns the number of URLs associated with a keyword. Using recursion, it traverses InOrder 
	to find the keyword and outputs the size of the list.
*/
int Tree::count(std::string keyword, Node* root)
{
	if (!root) {
		return 0;
	}
	else if (root->getKeyWord() == keyword) {
		return std::size(root->getKeyWordURLs());
	}
	else if (root->getKeyWord() > keyword) {
		return count(keyword, root->getLChild());
	}
	else {
		return count(keyword, root->getRChild());
	}
}

/*	Removes a given URL from a given keyword using recursive methods to find the keyword
	and proceeds to call a node-specific method for deletion. This does not delete the keyword.
*/
void Tree::deleteURL(std::string given_URL, std::string keyword, Node* root) {
	if (!root) {
		std::cout << '\n' << keyword << " not found. Please select an existing keyword to delete a URL from.\n\n";
		return;
	}
	else {
		if (root->getKeyWord() == keyword) {
			if (root->deleteURL(given_URL)) {
				std::cout << '\n' << "Deletion of: " << given_URL << " successful from keyword " << keyword;
			}
			else {
				std::cout << '\n' << given_URL << " is not associated with " << keyword << ". Please select a valid URL to remove.\n";
			}
		}
		else if (root->getKeyWord() > keyword) {
			return deleteURL(given_URL, keyword, root->getLChild());
		}
		else {
			return deleteURL(given_URL, keyword, root->getRChild());
		}
	}
}
/*	Traverses tree recursively to count the number of associations a 
	given URL has in the tree. Used primarily in other functions.
*/
double Tree::URLcount(std::string given_URL, Node* root)
{
	if (!root) {
		return 0;
	}
	else {
		int total;
		total = URLcount(given_URL, root->getLChild());
		std::list<std::string*> urlPtr = root->getKeyWordURLs();
		std::list<std::string*>::iterator urlIterator = urlPtr.begin();
		for (urlIterator; urlIterator != urlPtr.end(); urlIterator++) {
			if (**urlIterator == given_URL) {
				total += 1;
			}
		}
		total += URLcount(given_URL, root->getRChild());
		return total;
	}
}

/*
	popularKeywords
	Uses a set of two vectors to build a list of sites alongside their corresponding SEO scores.
	A selection sort is then performed and the list is output.
*/
void Tree::popularKeywords() {
	std::vector<int> scores;
	std::vector<std::string> keywords;
	std::vector<Node*> parentAddresses;
	Node* currentNode = root;
	while (parentAddresses.size() != 0 || currentNode != NULL)
	{
		while (currentNode != NULL)
		{
			parentAddresses.push_back(currentNode);
			currentNode = currentNode->getLChild();
		}
		currentNode = parentAddresses.back();
		parentAddresses.pop_back();
		std::string currentKeyword = currentNode->getKeyWord();
		keywords.push_back(currentKeyword);
		scores.push_back(count(currentKeyword, currentNode));

		currentNode = currentNode->getRChild();
	}
	for (int i = 0; i < scores.size(); i++) {
		for (int j = i; j < scores.size(); j++) {
			if (scores[j] > scores[i]) {
				std::swap(scores[i], scores[j]);
				std::swap(keywords[i], keywords[j]);
			}
		}
	}
	for (int i = 0; i < scores.size(); i++) {
		std::cout << '\n' << i + 1 << ".\t" << keywords[i] << ": " << scores[i];
	}
}
/*  outputs a list of the highest scoring sites in descending order. For scores, it calls the 
	above calculateSeoScore function to build a vector of percentages. 
	This works in the same fashion as popularKeywords function, however thanks to 
	the static list of URLs does not need any form of tree traversal to retrieve the names.
*/
void Tree::printSeoScores() {
	std::vector<double> scores;
	std::vector<std::string> URLs;
	std::list<std::string> urlPtr = *root->getTreeURLs();
	std::list<std::string>::iterator listIterator = urlPtr.begin();
	for (; listIterator != urlPtr.end(); listIterator++) {
		scores.push_back(calculateSEOscore(*listIterator));
		URLs.push_back(*listIterator);
	}
	for (int i = 0; i < scores.size(); i++) {
		for (int j = i; j < scores.size(); j++) {
			if (scores[j] > scores[i]) {
				std::swap(scores[i], scores[j]);
				std::swap(URLs[i], URLs[j]);
			}
		}
	}
	for (int i = 0; i < scores.size(); i++) {
		std::cout << '\n' << i + 1 << ".\t" << URLs[i] << ": " << scores[i] << "%";
	}
}
/*	Tallies the number of keyword hits associated with a given URL as a percentage of the
	total number of keywords in the tree./> In the context of SEO applications, this would 
	show how high the given site scores in terms of searchability. The higher the percentage, 
	the more likely it is to appear in a search using every keyword. 
	
	This function uses an InorderCount method using the root of the tree to calculate the number of keywords in 
	the tree. It then uses the URLcount function which returns the number of keywords 
	associated with a given URL. The percentage is calculated and returned.
*/
double Tree::calculateSEOscore(std::string given_URL) {
	double numKeywords = InorderCount(root);
	double numURLHits = URLcount(given_URL, root);
	return (numURLHits / numKeywords) * 100;

}

/*	InorderCount traverses recursively to return the number of keywords in the tree. 
	Not used in the UI however used in other operations.
*/
double Tree::InorderCount(Node* root) {
	if (root) {
		int counter;
		counter = InorderCount(root->getLChild());
		counter++;
		counter += InorderCount(root->getRChild());
		return counter;
	}
	else {
		return 0;
	}
}

void Tree::URLAssociation(Node* root, std::string given_URL) {
	if (root) {
		if (root->isURL(given_URL)) {
			std::cout << root->getKeyWord() << '\n';
		}
		URLAssociation(root->getLChild(), given_URL);
		URLAssociation(root->getRChild(), given_URL);
		return;
	}
	else {
		return;
	}
}

int Tree::funcF(Node* root) {
	if (!root) {
		return 0;
	}
	int a = funcF(root->getLChild()) +1;
	int b = funcF(root->getRChild()) + 1;
	return std::max(a, b);
}

std::string Tree::returnSucc(Node* root, std::string givenName) {
	if (!root->getLChild()) {
		return root->getKeyWord();
	}
	else if (root->getKeyWord() <= givenName) {
		return returnSucc(root->getRChild(), givenName);
	}
	else {
		return returnSucc(root->getLChild(), givenName);
	}
}