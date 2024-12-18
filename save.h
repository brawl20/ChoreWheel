#pragma once
#include "schedules.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <list>
#include <cstring>
using namespace std;

class save
{
public:
	save() {};
	void dataSave(list<task>* rT, list<user>* rU);
};