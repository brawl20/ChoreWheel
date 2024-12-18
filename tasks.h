#pragma once
#include <list>
	using std::list;
#include <string>
	using std::string;
#include <vector>
	using std::vector;

enum Completion{INCOMPLETE = 0, COMPLETE};

struct task
{
public:
	string name;
	int dayLimit;
	bool completeTask = false;

public:
	task(char const* name, int days, bool complete);
};


class Tasks
{
public:
	list<task> roster;
	vector<char const *> names;
public:
	bool create(char const *name, int days, bool complete);
	void destroy(char const *name);
	const char** getNames();
	int getSize();
	task* getTask(char const *name);
	//bool taskCompletion(char const *name, bool completeTask);
	//void endOfDay(char const *name, int days, bool completeTask);
};