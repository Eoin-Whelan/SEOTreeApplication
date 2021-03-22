/*
	Title:		Source.cpp
	Author:		Eoin Farrell
	DOC:		26/01/2020
	Purpose:	Main driver for SEO Keyword Program.
*/

#include <string>
#include <vector>
#include "Node.h"
#include "Tree.h"
#include <iostream>

int main() {
	Tree seoTree;

	int menuSelection = 0;
	std::string	wordInput1;
	std::string	wordInput2;
	char	confirmSelection = ' ';
	std::cout << "\nTitle:\tDSA SEO Tree Project\nAuthor:\tEoin Farrell\n";
	while (menuSelection != 10) {
		char	confirmSelection = ' ';

		std::cout << "\n\t--Search Engine Optimisation 2000--\t\n\n\n";
		std::cout << "Please choose from the following options:\n\n\n";
		std::cout << "1.\t Add a keyword/URL association\n";
		std::cout << "2.\t Show URLs associated with a keyword\n";
		std::cout << "3.\t Show keywords associated with a URL\n";
		std::cout << "4.\t Print alphabetical list of keywords.\n";
		std::cout << "5.\t Delete URL from keyword\n";
		std::cout << "6.\t URL Count of keyword\n";
		std::cout << "7.\t Calculate SEO score for a URL\n";
		std::cout << "8.\t View SEO Scoreboard for all URLs by highest score\n";
		std::cout << "9.\t View keyword scoreboard by no. of occurrences\n";
		std::cout << "10.\t Exit Program\n\n\n\n";

		std::cout << "Enter Selection -> ";
		std::cin >> menuSelection;

		switch (menuSelection) {
		case 1:
			std::cout << "\nPlease enter the keyword you wish to add: ";
			std::cin >> wordInput2;
			std::cout << "\nPlease enter the URL you wish to associate " << wordInput2 << " with: ";
			std::cin >> wordInput1;
			if (seoTree.getRoot() != NULL) {
				seoTree.put(seoTree.getRoot(), wordInput2, wordInput1);
			}
			else {
				seoTree.setRoot(seoTree.put(seoTree.getRoot(), wordInput2, wordInput1));
				std::cout << "\n" << wordInput2 << " is the new root and " << wordInput1 << " has been added.\n";
			}
			break;
		case 2:
			if (seoTree.getRoot() != NULL) {
				std::cout << "\nPlease enter the keyword you wish to view: ";
				std::cin >> wordInput1;
				std::cout << "\n\n";
				seoTree.get(seoTree.root, wordInput1);
			}
			else {
				std::cout << "\nThe tree is empty! There are no keywords.\n";
			}
			break;
		case 3:
			if (seoTree.getRoot() != NULL) {
				std::cout << "\nPlease enter the URL you wish to view: ";
				std::cin >> wordInput1;
				std::cout << "\n\n";
				if (seoTree.URLcount(wordInput1, seoTree.getRoot()) != 0) {
					std::cout << wordInput1 << " is associated with the following terms:\n\n";
					seoTree.URLAssociation(seoTree.getRoot(), wordInput1);
				}
				else {
					std::cout << '\n' << wordInput1 << " has 0 assocations.";
				}
			}
			else {
				std::cout << "\nThe tree is empty! There are no keywords.\n";
			}
			break;
		case 4:
			if (seoTree.getRoot() != NULL) {
				seoTree.printOrder(seoTree.getRoot());
			}
			else {
				std::cout << "\nThe tree is empty! There are no keywords.\n";
			}
			break;
		case 5:
			if (seoTree.getRoot() != NULL) {
				std::cout << "\nPlease enter the keyword you wish to remove a URL from: ";
				std::cin >> wordInput2;
				std::cout << "\nPlease enter the URL you wish to remove from " << wordInput2 << ": ";
				std::cin >> wordInput1;
				seoTree.deleteURL(wordInput1, wordInput2, seoTree.getRoot());
			}
			else {
				std::cout << "\n\nTree has no keywords. No deletion can occur.\n";
			}
			break;
		case 6:
			if (seoTree.getRoot() != NULL) {
				std::cout << "\nPlease enter the keyword you wish to view: ";
				std::cin >> wordInput1;
				int count = seoTree.count(wordInput1, seoTree.getRoot());
				std::cout << "\n";
				if (count > 0) {
					std::cout << wordInput1 << " is found on " << seoTree.count(wordInput1, seoTree.getRoot()) << " sites.";
				}
				else {
					std::cout << "\nKeyword either not found in tree or has 0 assocations.";
				}
			}
			else {
				std::cout << "\nThe tree is empty! There are no keywords.\n";
			}
			break;
		case 7:
			if (seoTree.getRoot() != NULL) {
				std::cout << "\nPlease enter a URL to view it's SEO score: ";
				std::cin >> wordInput1;
				int score = seoTree.calculateSEOscore(wordInput1);
				if (score > 0) {
					std::cout << "SEO Score: " << seoTree.calculateSEOscore(wordInput1) << "% with:\n" << seoTree.URLcount(wordInput1, seoTree.getRoot()) << " hits out of a total of " << seoTree.InorderCount(seoTree.getRoot()) << " keywords";
				}
				else {
					std::cout << '\n' << wordInput1 << " has 0 assocations.";
				}
			}
			else {
				std::cout << "\nNo keywords exist to score " << wordInput1 << '\n';
			}
			break;
		case 8:
			if (seoTree.getRoot() != NULL) {
				seoTree.printSeoScores();
			}
			else {
				std::cout << "\nNo keywords exist to create scoreboard.\n";
			}
			break;
		case 9:
			if (seoTree.getRoot() != NULL) {
				seoTree.popularKeywords();
			}
			else {
				std::cout << "\nNo keywords exist. Try adding some first!\n";
			}
			break;
			if (seoTree.getRoot() != NULL) {
				std::cout << "\nPlease enter the URL you wish to view: ";
				std::cin >> wordInput1;
				std::cout << "\n\n";
				if (seoTree.URLcount(wordInput1, seoTree.getRoot()) != 0) {
					std::cout << wordInput1 << " is associated with the following terms:\n\n";
					seoTree.URLAssociation(seoTree.getRoot(), wordInput1);
				}
			}
			else {
				std::cout << "\nThe tree is empty! There are no keywords.\n";
			}
			break;
		case 10:
			std::cout << seoTree.funcF(seoTree.getRoot());
			std::cout << seoTree.returnSucc(seoTree.getRoot(), "Karl");
			std::cout << "\nSee you!\n";
			break;
		default:
			std::cout << "\nInvalid option. Try again!\n";
			break;
		}
	}
}