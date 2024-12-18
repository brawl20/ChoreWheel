#pragma once
#include <list>
	using std::list;
#include <string>
	using std::string;
#include <utility>
	using std::pair;
	using std::make_pair;
#include <fstream>
	using std::ofstream;
#include <iostream>
#include "users.h"
#include "tasks.h"

struct assignment
{
public:
	user* User;
	list<task*> assigned;
	task* Task;
	const char* last_task;

public:
	assignment(user* User, task* Task): User(User), Task(Task) {assigned.push_back(Task);}
	assignment(user* User): User(User) {Task = nullptr;}
};

class Schedules
{
private:
	list<assignment> roster;
public:
	Users users;
	Tasks tasks;

public:
	int addAssignment(char const* username, char const* taskname);
	void removeAssignment(char const* username, char const* taskname);
	void removeTaskFromUser(char const* username, char const* taskname);
	list<assignment>::const_iterator getIter();
	list<assignment>::const_iterator getEnd();
	pair<list<assignment>::const_iterator, list<assignment>::const_iterator> getAssignments();

	void nextAssignments();
	void dataSave();
	void dataLoad();
};