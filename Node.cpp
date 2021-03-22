/*
	Title:		Node.cpp
	Author:		Eoin Farrell
	DOC:		26/01/2020
	Purpose:	Node class implementation of class functions.
*/

#include "Node.h"
#include<iterator>
#include <iostream>
#include <list> 

//	Reference to static variable in implementation.
std::list<std::string> Node::treeURLs;


Node::Node(std::string newKeyword, std::string passedURL)
{
	this->keyWord = newKeyword;
	this->addURL(getURLAddress(passedURL));
}

Node::Node()
{
}

Node::Node(std::string keyword) {
	this->keyWord = keyword;
}

void Node::setLChild(Node* passedAddress)
{
	this->lChild = passedAddress;
}

void Node::setRChild(Node* passedAddress)
{
	this->rChild = passedAddress;
}

void Node::addURL(std::string* newURL)
{
		this->keyWordURLs.push_back(newURL);
}

bool Node::deleteURL(std::string given_URL) {

	std::list<std::string*>::iterator urlIterator = keyWordURLs.begin();
	for (; urlIterator != keyWordURLs.end(); ) {
		if (**urlIterator == given_URL) {
			keyWordURLs.remove(*urlIterator);
			return true;
		}
		urlIterator++;
	}
	return false;
}

std::string* Node::getURLAddress(std::string URLtext) {

	std::list<std::string>* urlListPtr = getTreeURLs();
	std::list<std::string>::iterator urlListIterator = urlListPtr->begin();

	for (urlListIterator; urlListIterator != urlListPtr->end(); urlListIterator++){
		if (*urlListIterator == URLtext) {
			return std::addressof(*urlListIterator);
		}
	}
	this->getTreeURLs()->push_front(URLtext);
	urlListPtr = getTreeURLs();

	return std::addressof(urlListPtr->front());
}

bool Node::isURL(std::string URLtext) {

	std::list<std::string*> urlListPtr = getKeyWordURLs();
	std::list<std::string*>::iterator urlListIterator = urlListPtr.begin();

	for (urlListIterator; urlListIterator != urlListPtr.end(); urlListIterator++) {
		if (**urlListIterator == URLtext) {
			return true;
		}
	}
	return false;
}

void Node::printNodeURLs()
{
	std::list<std::string*>nodeURLPtr = getKeyWordURLs();
	std::list<std::string*>::iterator URLVecIterator = nodeURLPtr.begin();
	if (getKeyWordURLs().size() != 0) {
		std::cout << keyWord << " is found on: \n";
		for (URLVecIterator; URLVecIterator != nodeURLPtr.end(); URLVecIterator++) {
			std::cout << '\t' << **URLVecIterator << '\n';
		}
	}
	else {
		std::cout << "\nNo URLs are associated with " << getKeyWord() << "\n";
	}
}