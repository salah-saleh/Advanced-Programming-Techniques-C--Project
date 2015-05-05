#include "Entity.h"
#include <string>



size_t Entity::getGas(){
	return this->m_vespin;
}

size_t Entity::getMinerals(){
	return this->m_minerals;
}

size_t Entity::getBuildTime(){
	return this->m_time;
}

string Entity::getName(){
	return this->m_name;
}

vector<string> Entity::getDependencies(){
	return this->m_dependencies;
}
