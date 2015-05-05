/*
 * Simulation.cpp
 *
 *  Created on: Feb 4, 2013
 *      Author: skippy
 */

#include "Simulation.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Entity.h"

using namespace std;

Simulation::Simulation(vector<Building> _buildings, vector<Unit> _units, vector<string> _buildList, FileIO* _io) {
	this->buildings = _buildings;
	this->units = _units;
	this->buildList = _buildList;

	this->minerals = 50;
	this->vespian = 0;
	this->psi = 4;
	this->timestep = 1;
	this->haveAssimilator = false;

	this->io = _io;

	if(this->hasUnit("Probe") >= 0){
		for(int i = 0; i < 6; ++i){
			this->built.push_back("Probe");
			this->attime.push_back(0);
		}
	} else {
		cerr << "Probe was not found. Leaving simulation." << endl;
		exit(1);
	}
}

/**
 * We check whether the building exists and return it's position in the Buildings
 */
int Simulation::hasBuilding(string name){
	int offset = -1;

	for(unsigned int i = 0; i < buildings.size(); ++i){
		if(buildings[i].getName() == name){
			offset = i;
		}
	}

	return offset;
}

/*
* We check whether the unit exists and return it's position in the Units
*/
int Simulation::hasUnit(string name){
	int offset = -1;

	for(unsigned int i = 0; i < units.size(); ++i){
		if(0 == (units[i].getName().compare(name))){
			offset = i;
		}
	}

	return offset;
}

/*
 *We use it every time step to increment the resources
 */
void Simulation::incrementResources(){
	for(unsigned int i = 0; i < built.size(); ++i){
		if("Probe" == built[i]){
			this->minerals = this->minerals + 1;
		} else if("Assimilator" == built[i]) {
			this->vespian = this->vespian + 3;
		} else if("Pylon" == built[i]) {
			if(this->attime[i] == this->timestep)
				this->psi += 8;
		} else if("Nexus" == built[i]) {
			if(this->attime[i] == this->timestep){
				this->psi += 10;
			}
		}
	}
}

/*
 *We get by this function next element from the building list
 */
string Simulation::getNextBuildElement(){
	string element;

	if(0 == this->buildList.size()){
		element = "";
	} else {
		element = *buildList.begin();
		buildList.erase(buildList.begin(), buildList.begin() + 1);
	}

	return element;
}

/**
 * -2 - Not enough Vespian and it cannot be collected
 * -3 Not enough PSI and it will not be provided by any building currently being built
 * 0 - Need to wait to get more resources
 * 1 - All OK
 */
int Simulation::checkResources(Entity* e){
	if((this->minerals >= e->getMinerals()) && (this->vespian >= e->getGas()) && (this->psi >= e->getPsi()))
		return 1;
	else if((this->vespian < e->getGas()) && (false == this->haveAssimilator)){
		return -2;
	}
	else if ((this->psi < e->getPsi()) && (false == checkPSI()))
		return -3;
	else
		return 0;
}

/**
 * Error codes:
 * -1 - not found, dependency does not check out
 * 	0 - dependency found, need to skip
 * 	1 - dependency found, can build
 */
int Simulation::checkDependencies(Entity* e){

	vector<string> dependencies = e->getDependencies();

	for(vector<string>::iterator it = dependencies.begin(); it != dependencies.end(); ++it){
		int offset = -1;
		for(unsigned int i = 0; i < this->built.size(); ++i){
			if(units[i].getName() == *it){
				offset = i;
			}
		}

		if(-1 == offset){
			return -1;
		} else {
			if(this->attime[offset] > this->timestep){
				return 0;
			}
		}
	}

	return 1;
}

Entity* Simulation::getEntity(string name){
	//Asume building, modify otherwise
	bool isBuilding = true;
	int pos = this->hasBuilding(name);

	if(-1 == pos){
		isBuilding = false;
		pos = this->hasUnit(name);

		//If still -1, it can not be found in the definition list
		if(-1 == pos){
			cerr << "This building does not exist on the definition list. Exiting"<< endl;
			exit(1);
		}
	}

	Entity* e;
	if(true == isBuilding){
		e = &this->buildings[pos];
	}else {
		e = &this->units[pos];
	}

	return e;
}

/**
 * Status codes:
 * -2 - no unit exists in definitions
 */
int Simulation::checkBuild(string entity){

	Entity* e = this->getEntity(entity);
	//cout << "BBB " << e->getName() << endl;
	if( (1 == this->checkDependencies(e)) && ( 1 == this->checkResources(e)) ){
		//Build
		//cout << this->checkResources(e);
		return 0;
	}
	else if( (0 <= this->checkDependencies(e)) && ( 0 <= this->checkResources(e)) ){
		//Wait
		return 1;
	}
	else if (-1 == this->checkDependencies(e)){
		cerr<< "Dependencies error. Exiting" <<endl;
		exit(1);
	}
	else if (-2 == this ->checkResources(e)){
		cerr << "Not enough Vespin gas and it cannot be collected. Exiting"<<endl;
		exit(1);
	}
	else if(-3 == this ->checkResources(e)){
		cerr << "Not enough PSI for " << e->getName() << " Exiting"<<endl;
		exit(1);
	}
	//Should not get here!
	return -1;

}

void Simulation::gameLoop(){
	bool weWait = false;
	string toBeBuilt = "";
	//Handle time overflow - Yes, it can happen!
	while((this->timestep > 0)){
		//We are waiting on a building to be built
		if(!weWait){
			toBeBuilt = this->getNextBuildElement();

			if("" == toBeBuilt){
			  cout <<"Reached 'What in this case' !!!!!!!!****Simulation succesfully finished. Exiting" <<endl;				
			  exit(0);
			} else {
				int code = this->checkBuild(toBeBuilt);				
				if(1 == code){
					//Need to wait some more
					weWait = true;
				} else {
					//Start building
					weWait = false;
					Entity* e = this->getEntity(toBeBuilt);
					this->built.push_back(toBeBuilt);
					this->attime.push_back(e->getBuildTime());
					this->minerals = this->minerals - e->getMinerals();
					this->vespian = this->vespian - e->getGas();
					this->psi = this->psi - e->getPsi();

					stringstream s1;
					stringstream s2;
					s1 << this->timestep;
					s2 << this->timestep + e->getBuildTime();
					string outLine = toBeBuilt;
					outLine += " started at time ";
					outLine += s1.str();
					outLine += " and ands at time ";
					outLine += s2.str();
					cout << toBeBuilt << " " << this->timestep << " " << this->timestep + e->getBuildTime() << endl;
					(*io).writeNextOutput(outLine);
				}
			}
		} else {
			int code = this->checkBuild(toBeBuilt);
			if(1 == code){
				//Need to wait some more
				weWait = true;
			} else {
				//Start building
				weWait = false;
				Entity* e = this->getEntity(toBeBuilt);
				this->built.push_back(toBeBuilt);
				this->attime.push_back(e->getBuildTime());
				this->minerals = this->minerals - e->getMinerals();
				this->vespian = this->vespian - e->getGas();
				this->psi = this->psi - e->getPsi();

				stringstream s1;
				stringstream s2;
				s1 << this->timestep;
				s2 << this->timestep + e->getBuildTime();
				string outLine = toBeBuilt;
				outLine += " started at time ";
				outLine += s1.str();
				outLine += " and ands at time ";
				outLine += s2.str();
				cout << toBeBuilt << " " << this->timestep << " " << this->timestep + e->getBuildTime() << endl;
				(*io).writeNextOutput(outLine);
			}
		}
		this->incrementResources();
		++(this->timestep);
	}
}

Simulation::~Simulation() {
}

bool Simulation::checkPSI(){
	for(unsigned int i = 0; i < built.size(); ++i){
		if(((built[i] == "Pylon") || (built[i] == "Nexus")) && attime[i] >= timestep)
			return true;
	}
	return false;
}
