#include "schedules.h"

int Schedules::addAssignment(char const* username, char const* taskname)
{
	auto selected_task = tasks.getTask(taskname);
	if(selected_task == nullptr) return 1;

	for(auto &selected: roster)
	{
		if(selected.User->name == username) 
		{
			selected.assigned.push_back(selected_task); 
			return 0;
		}
	}

	auto selected_user = users.getUser(username);
	if(selected_user == nullptr) return 2;

	roster.emplace_back(selected_user, selected_task);
	return 0;
}

pair<list<assignment>::const_iterator, list<assignment>::const_iterator> Schedules::getAssignments()
{
	return make_pair(roster.cbegin(), roster.cend());
}

list<assignment>::const_iterator Schedules::getIter() {return roster.cbegin();}
list<assignment>::const_iterator Schedules::getEnd() {return roster.cend();}

void Schedules::nextAssignments()
{
	for(auto &current: roster)
	{
        if(current.Task == nullptr) break;
		else if(current.Task->completeTask||current.User->absent) 
		{
			current.Task->completeTask = false;
			current.last_task = current.Task->name.c_str();
			current.Task = nullptr;
		}
		else current.User->amtIncomplete++;
	}
	
	for(auto &current: roster)
	{
		if(current.User->absent) continue;
		auto task = current.assigned.front();
		while(task->name.c_str() != current.last_task && current.Task == nullptr) // This was the crash point...
		{
			current.assigned.push_back(task);
			current.assigned.erase(current.assigned.cbegin());
			bool valid = true;
			for(auto &others: roster) if(others.Task == task) valid = false;
			if(valid) current.Task = task;
		}
	}
}

void Schedules::removeAssignment(char const* username, char const* taskname)
{
	if(roster.empty())
	{
		return;
	}
	auto begin = roster.begin(); // gets beggining of roster and saves it as begin
	auto end = roster.end(); // gets end of roster and saves it so we know when to stop in our for loop

	for(; begin != end; begin++)
	{
		if(begin->User->name == username && begin->Task->name == taskname)
		{
			begin = roster.erase(begin);
		}
		
	}
}

// erase an assigned task from a user
void Schedules::removeTaskFromUser(char const* username, char const* taskname)
{
	assignment *selected = nullptr;
	for(auto &current: roster) 
		if(current.User->name == username) 
			selected = &current;

	if(selected == nullptr) return;
	if(selected->Task->name == taskname) selected->Task = nullptr;

	auto task = selected->assigned.begin();
	while(task != selected->assigned.end())
		if((*task)->name == taskname) 
			task = selected->assigned.erase(task);
}

void Schedules::dataSave()
{
	//list<user>* listUser = rU->rosterPtr;

		 
	std::fstream out_stream; // create ostream
	out_stream.open("practice2.txt"); // open the save file
	list<task>::iterator current_task; // create iterator for tasks
	list<user>::iterator current_user; // create iterator for users
	list<assignment>::iterator current_assignment;
	if (out_stream.is_open())
	{
		out_stream << "tSTART,"; // Indicator for start of task data
		for (current_task = tasks.roster.begin(); current_task != tasks.roster.end(); ++current_task)
		{
			out_stream << current_task->name << "," << current_task->dayLimit << "," << current_task->completeTask << ",";
		}
		out_stream << "END,"; // End of task data

		out_stream << "uSTART,"; // Indicator for start of user data
		for (current_user = users.roster.begin(); current_user != users.roster.end(); ++current_user)
		{
			out_stream << current_user->name << "," << current_user->absent << "," << current_user->amtIncomplete << ",";
			/*
			for (auto current = current_assignment->assigned.begin(); current != current_assignment->assigned.end(); ++current)
			{
				out_stream << (*current)->name << ",";
			}
			*/
		}
		out_stream << "END,"; // End of user data

		/*
		out_stream << "aSTART,"; // Indicator for start of user data
		for (current_assignment = roster.begin(); current_assignment != roster.end(); ++current_user)
		{
			out_stream << current_assignment->User->name << "," << current_assignment->Task->name << ",";
		}
		out_stream << "END," << std::endl; // End of assignment data
		*/
	}
	else
	{
		std::cout << "Error\n";
	}
	out_stream.close(); // close file
}


void Schedules::dataLoad()
{
	std::ifstream input("practice2.txt");
	std::string temp;
	std::string name;
	int dayLimit;
	bool complete;
	bool absent;
	int incomplete;
	while(getline(input, temp, ','))
	{
		if(temp == "tSTART")
		{
			getline(input, temp, ',');
			while(temp != "END")
			{
				name = temp;
				getline(input, temp, ',');
				dayLimit = stoi(temp);
				getline(input, temp, ',');
				complete = stoi(temp);
				tasks.create(name.c_str(), dayLimit, complete);
				getline(input, temp, ',');
			}
		}
		if(temp == "uSTART")
		{
			getline(input, temp, ',');
			while(temp != "END")
			{
				name = temp;
				getline(input, temp, ',');
				absent = stoi(temp);
				getline(input, temp, ',');
				incomplete = stoi(temp);
				users.create(name.c_str(), 0, 0);
				getline(input, temp, ',');
			}
		}
	}
	input.close();
}
	