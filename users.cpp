#include "users.h"

// Assign new user to current roster.
bool Users::create(char const* name, bool absent, int incomplete)
{
	for(auto task: roster)
		if(task.name == name) return false;

	roster.emplace_back(user(name, absent, incomplete));
	return true;
}

void Users::destroy(const char* name)
{
	auto user = roster.begin();
	while(user != roster.end())
		if(user->name == name)
			user = roster.erase(user);
	
}

user* Users::getUser(char const* name)
{
	for(auto &user: roster) 
		if(user.name == name) return &user;
    return nullptr;
}

void Users::rename(char const* username, char const* newname)
{
	for(auto user: roster) 
		if(user.name == username) 
			user.name = newname;
}
/*
list<string*>::const_iterator Users::getNames()
{
    if(names.size() != roster.size())
    {
        names.clear();
	    for(auto current = roster.begin(); current != roster.end(); current++)
		    names.emplace_back(&(current->name));
    }
    return names.cbegin();
}
*/

const char** Users::getNames()
{
	names.clear();
	for(auto &current: roster)
	{
		names.push_back(current.name.c_str());
	}
	return names.data();
}

int Users::getSize() {return roster.size();}

int Users::incomp()
{
	return 1;
}

/*
void inline user_completedTask(vector<Users>* users, int userVecNum, int taskVecNum) // logic used when a task is completed
{
	user_removeTask(users, userVecNum, taskVecNum);
}

void inline user_incompletedTask(vector<Users>* users, vector<Tasks>* taskToBeAssigned) // logic used when a task is not completed
{
	user_assignTask(users, taskToBeAssigned);
}
*/