/*
 * BuildFactory.h
 *
 *  Created on: Jan 10, 2013
 *      Author: skippy
 */

#ifndef BUILDFACTORY_H_
#define BUILDFACTORY_H_

#include <string>

using namespace std;

class BuildFactory {
public:
	BuildFactory(string fileName);
	virtual ~BuildFactory();
};

#endif /* BUILDFACTORY_H_ */
