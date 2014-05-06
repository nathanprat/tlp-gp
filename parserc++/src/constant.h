#pragma once


#ifndef CONSTANT_H
#define CONSTANT_H
  
#include "member.h"


class Constant : public Member {
	public:
		Constant(string name, vector<Type*> types);
		Constant();
		virtual string to_string();
		string getClass(); 
};

#endif // CONSTANT_H

