#pragma once
#include "schedules.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <list>
#include <cstring>
using namespace std;

class load
{
public:
	load() {};
	void dataLoad(list<task>* rT, list<user>* rU, list<assignment>* rA);


};