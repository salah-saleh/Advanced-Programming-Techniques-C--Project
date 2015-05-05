#include "ElemConst.h"

#include "Building.h"
#include "Unit.h"
#include "Entity.h"

#include	<string>
#include	<vector>
#include	<sstream>

using namespace std;

void ElemConst::create_obj(vector<string>& data, vector <Unit>& units, vector<Building>& buildings)
{
	string name = data[0];
	size_t prov_psi, req_psi, minerals, vespin, time;
	stringstream(data[1]) >> prov_psi;
	stringstream(data[2]) >> req_psi;
	stringstream(data[3]) >> minerals;
	stringstream(data[4]) >> vespin;
	stringstream(data[5]) >> time;
	string producer = data[6];
	vector<string> dependencies(data.begin() + 7, data.end());

	if (req_psi != 0)
	{
		Unit tmp (name, req_psi, minerals, vespin, time, producer, dependencies);
		units.push_back(tmp);
	}

	else
	{
		Building tmp (name, prov_psi, minerals, vespin, time, dependencies);
		buildings.push_back(tmp);
	}
}

void ElemConst::constructEntity(vector<vector<string> > data, vector <Unit>& units, vector<Building>& buildings)
{
	for(vector<vector<string> >::iterator element = data.begin(); element != data.end(); ++element)
	{
		ElemConst::create_obj(*element, units, buildings);
	}
}
