#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>

using namespace std;

class Entity 
{
	string m_name;
	size_t m_minerals;
	size_t m_vespin;
	size_t m_time;
	vector<string> m_dependencies;
public:
	string getName();
	size_t getMinerals();
	size_t getGas();
	size_t getBuildTime();
	vector<string> getDependencies();
public:
	Entity(string name, size_t minerals, size_t vespin, size_t time, vector<string> dependencies): m_name(name), m_minerals(minerals), m_vespin(vespin), m_time(time), m_dependencies(dependencies)  
	{
	}
	//virtual ~Entity();
	virtual size_t getPsi() = 0;

};

#endif
