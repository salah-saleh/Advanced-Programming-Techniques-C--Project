#ifndef ELEMCONST_H_
#define ELEMCONST_H_

#include <string>
#include <vector>
#include "Building.h"
#include "Unit.h"

using namespace std;

class ElemConst
{	
	public:
		static void create_obj(vector<string>& data, vector<Unit>& units, vector<Building>& buildings);
		static void constructEntity(vector<vector<string> > data, vector<Unit>& units, vector<Building>& buildings);
};

#endif
