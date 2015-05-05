/*
 * Simulation.h
 *
 *  Created on: Feb 4, 2013
 *      Author: skippy
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <vector>
#include "Building.h"
#include "Unit.h"
#include "Entity.h"
#include "FileIO.h"

using namespace std;

class Simulation {
private:
	size_t timestep;
	size_t minerals;
	size_t vespian;
	size_t psi;
	bool haveAssimilator;
	vector<string> built;
	vector<size_t> attime;
	vector<Building> buildings;
	vector<Unit> units;
	vector<string> buildList;
	FileIO* io;

	int hasBuilding(string name);
	int hasUnit(string name);
	void incrementResources();
	string getNextBuildElement();
	int checkBuild(string entity);
	int checkDependencies(Entity* e);
	int checkResources(Entity* e);
	bool checkPSI();
	Entity* getEntity(string name);

public:
	Simulation(vector<Building> _buildings, vector<Unit> _units, vector<string> _buildList, FileIO* _io);
	virtual ~Simulation();
	void gameLoop();
};

#endif /* SIMULATION_H_ */
