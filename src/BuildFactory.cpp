/*
 * BuildFactory.cpp
 *
 *  Created on: Jan 10, 2013
 *      Author: skippy
 */
//
#include "BuildFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

BuildFactory::BuildFactory(string fileName) {
	string sLine = "";
	ifstream inputStream;
	inputStream.open(fileName.c_str(), ifstream::in);

	while(!inputStream.eof()){
		getline(inputStream, sLine);
		bool ignored = false;
		//Ignore line that contains #
		size_t pos_sharp = sLine.find('#');
		if(pos_sharp != string::npos){
			sLine = sLine.substr(0, pos_sharp);
		}

		size_t no_spaces = 0;
		for(string::iterator it = sLine.begin(); it != sLine.end(); ++it){
			if(isspace(*it)) ++no_spaces;
		}
		if(no_spaces == sLine.length())
			ignored = true;

		//Ignore the line that has only spaces or tabs
		if((sLine.find_first_not_of(' ')== string::npos) ||
				(sLine.find_first_not_of('\t') == string::npos)){
			ignored = true;
		}

		if(false == ignored){
			cout << "Element:" << endl;
			stringstream ss;
			ss << sLine;

			std::string myWord;
			while (ss >> myWord)
			    cout << myWord << endl;
		}
	}
	cout << endl;
}

BuildFactory::~BuildFactory() {
	// TODO Auto-generated destructor stub
}
