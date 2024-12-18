#include "tasks.h"

task::task(char const* name, int days, bool complete): name(name), dayLimit(days), completeTask(complete) {}

// Put task in vector with other tasks
bool Tasks::create(char const* name, int days = 1, bool complete = 0)
{
	for(auto task: roster)
		if(task.name == name) return false;

	roster.emplace_back(task(name, days, complete));
	return true;
}

void Tasks::destroy(char const* name)
{
	auto task = roster.begin();
	while(task != roster.end())
		if(task->name == name)
			task = roster.erase(task);
}

const char** Tasks::getNames()
{
	names.clear();
	for(auto &current: roster)
	{
		names.emplace_back(current.name.c_str());
	}
	return names.data();
}

int Tasks::getSize() {return roster.size();}

task* Tasks::getTask(char const* name)
{
	for(auto &task: roster)
		if(task.name == name) return &task;
    return nullptr;
}