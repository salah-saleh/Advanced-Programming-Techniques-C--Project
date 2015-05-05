//============================================================================
// Name        : StarCraft.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "BuildFactory.h"
#include <vector>
#include <string>
#include "FileIO.h"
#include "Entity.h"
#include "Unit.h"
#include "Building.h"
#include "ElemConst.h"
#include "Simulation.h"

using namespace std;

bool debug = false;

int main()
{
	if(debug) cout << "Just starting out" << endl;
	FileIO fi ("entities.txt",  "buildlist.txt", "outTest222.txt");
	vector<vector<string> > def = fi.readDefinitions();
	vector<Unit> units;
	vector<Building> buildings;
	if(debug) cout << "Just read definitiosn" << endl;
	ElemConst::constructEntity(def, units, buildings);
	if(debug) {
		cout << "Finished delegating elements" << endl;
		for(vector<Building>::iterator element = buildings.begin(); element != buildings.end(); ++element)
			cout << (*element).getName() << endl;
	}
	vector<string> buildlist = fi.readBuildList();
	if(debug) {
		cout << "Just read BuildList" << endl;
		//cout << buildlist.size() << endl;
		for (vector<string>::iterator element1 = buildlist.begin(); element1 != buildlist.end(); ++element1)
			cout << *element1 <<endl;
	}

	Simulation s(buildings, units, buildlist, &fi);
        s.gameLoop();

	return 0;
}
