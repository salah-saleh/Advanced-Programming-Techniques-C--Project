#ifndef BUILDING_H_
#define BUILDING_H_

#include <string>
#include "Entity.h"

using namespace std;

class Building: public Entity
{
	size_t m_prov_psi;

public:
	public:
	Building(string name, size_t prov_psi, size_t minerals, size_t vespin, size_t time, vector<string> dependencies): Entity(name, minerals, vespin,  time, dependencies), m_prov_psi(prov_psi){}
	virtual size_t getPsi();

};

#endif
