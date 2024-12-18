#pragma once
#include <string>
	using std::string;
#include <list>
	using std::list;
#include <vector>
	using std::vector;
#include "tasks.h"

struct user
{
public:
	string name;
	bool absent = false;
	int amtIncomplete; //int to keep track of how many times a user does not complete their tasks
public:
	user(char const* name, bool absent, int incomplete): name(name), absent(absent), amtIncomplete(incomplete) {}
};


class Users
{
public:
	list<user> roster;
	vector<char const *> names;
public:
	bool create(char const* name, bool absent, int incomplete);
	void destroy(char const* name);
	const char** getNames();
	int getSize();
	user* getUser(char const* name);

	int incomp();
	void rename(char const* username, char const* newname);
	void removeTask(char const* username, char const* taskname);
	void assignTask(char const* username, task* newTask);
};