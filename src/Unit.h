#ifndef UNIT_H_
#define UNIT_H_

#include <string>
#include <vector>
#include "Entity.h"

using namespace std;

class Unit: public Entity
{
	size_t m_req_psi;
	string m_producer;

public:
	Unit(string name,  size_t req_psi, size_t minerals, size_t vespin, size_t time, string producer, vector<string> dependencies): Entity(name, minerals, vespin,  time, dependencies), m_req_psi(req_psi), m_producer(producer){}
	size_t getPsi();
	string getProducer();
};

#endif
