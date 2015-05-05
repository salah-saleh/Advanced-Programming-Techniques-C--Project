/*
 * FileIO.cpp
 *
 *  Created on: Jan 18, 2013
 *      Author: skippy
 */

#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * Constructor
 *
 * Opens all streams associated with the input files
 */
FileIO::FileIO(string _definitionFile, string _buildListFile, string _outputFile) {
	definitionFile.open(_definitionFile.c_str(), ifstream::in);
	buildListFile.open(_buildListFile.c_str(), ifstream::in);
	outputFile.open(_outputFile.c_str(), ofstream::out);

}

/**
 * Reading definitions
 */
vector <vector <string> > FileIO::readDefinitions(){
	vector<vector<string> > definitions;
	string sLine = "";

	if(!buildListFile.is_open()){
			cerr << "Definition list file is not open. Could not open or forgot to?" << endl;
			exit(1);
	}

	//Iterate until you reach EOF
	while(!definitionFile.eof()){
		sLine = "";
		getline(definitionFile, sLine);

		sLine = osCompatibility(sLine);

		bool ignored = false;
		//Cut the line before the # symbol
		size_t pos_sharp = sLine.find('#');
		if(pos_sharp != string::npos){
			sLine = sLine.substr(0, pos_sharp);
		}

		//Count the number of spaces in the line
		//If the line has only spaces then it is ignored
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

		//The line actually contains a definition
		if(false == ignored){
			stringstream ss;
			ss << sLine;
			vector<string> vLine;
			std::string myWord;
			while (ss >> myWord)
				vLine.push_back(myWord);

			//Do an extra check
			if(vLine.size() > 6)
				definitions.push_back(vLine);
		}
	}

	return definitions;
}

/**
 *	Reading build list
 */
vector<string> FileIO::readBuildList(){
	vector<string> buildList;
	string sLine = "";

	if(!buildListFile.is_open()){
		cerr << "Build list file is not open. Could not open or forgot to?" << endl;
		exit(1);
	}

	//Iterate until you reach EOF
	while(!buildListFile.eof()){
		sLine = "";
		getline(buildListFile, sLine);

		//Do OS-specific conversions if necessary
		sLine = osCompatibility(sLine);

		if(sLine.length() > 2)
			buildList.push_back(sLine);
	}

	return buildList;
}

/**
 * This method is here for two reasons:
 * 	1) - new line characters are different on Windows and Linux
 * 	2) - the getline() method from C++ doesn't seem to know 1)
 */
string FileIO::osCompatibility(string line){
	//Do only if we have one character in the line
	//Else bad things happen!
	if(line.size() > 1){
		size_t nPos = line.size() - 1;

		//Check both, just to be sure
		if((line[nPos] == '\r') || (line[nPos] == '\n'))
			line.erase(nPos);
	}

	return line;
}

/**
 * Writing to file one line at a time
 *
 * Warning: Does not close stream after operation
 */
void FileIO::writeNextOutput(string line){
	if(outputFile.is_open()){
		outputFile << line << endl;
	} else {
		cerr << "Can not write to output file." << endl;
		exit(1);
	}
}

/**
 * Destructor
 */
FileIO::~FileIO() {
	//Close everything nicely
	definitionFile.close();
	buildListFile.close();
	outputFile.close();
}

