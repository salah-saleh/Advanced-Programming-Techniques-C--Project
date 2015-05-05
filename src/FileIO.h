/*
 * FileIO.h
 *
 *  Created on: Jan 18, 2013
 *      Author: skippy
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileIO {
public:
	FileIO(string _definitionFile, string _buildListFile, string _outputFile);
	~FileIO();

	vector <vector <string> > readDefinitions();
	vector<string> readBuildList();
	void writeNextOutput(string line);
private:
	ifstream definitionFile;
	ifstream buildListFile;
	ofstream outputFile;

	string osCompatibility(string line);
};

#endif /* FILEIO_H_ */
