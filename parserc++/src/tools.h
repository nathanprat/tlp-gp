#pragma once


#ifndef TOOLS_H
#define TOOLS_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <fstream>
#include "type.h"
#include "fluent.h"
using namespace std;


class Tools {
	public:
		Tools();
		virtual ~Tools();
		bool isIn(Type* t ,vector<Type*>* v);
		bool compareVectorType(vector<Type*>* v1,vector<Type*>* v2);
		bool solveur();
};

#endif // TOOLS_H

