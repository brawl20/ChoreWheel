#include "load.h"

using namespace std;


/* NOTES:
Still need to implement how to load data for a assignment list
*/
void load::dataLoad(list<task>* rT, list<user>* rU, list<assignment>* rS) // rT = pointer to the fundamental task list, rU = pointer to the fundamental user list, rS = pointer to the assignment list
{
	fstream ifs;
	ifs.open("practice4.txt");

	while (!ifs.eof())
	{
		char startChars[50]; // buffer for holding the beginning of a line
		char startTsequence[50] = "tSTART"; // char sequence for indicating start of tasks data line
		char startUsequence[50] = "uSTART"; // char sequence for indicating start of users data line
		char startSsequence[50] = "sSTART"; // char sequence for indicating start of schedule data line
		int swtGoto; // "switch Goto"
		char myNameBuff[50]; // buffer for holding the name of something
		char myDaysBuff[10]; // buffer for holding the number of days a task has to complete
		char endSequence[4] = "END"; // char sequence for indicating end of a data line
		int myDays;

		ifs.getline(startChars, 50, ',');
		// since switch only accepts enums or ints, a comparison must be done using strcmp that will feed swtGoto a integer. If it does/not find a match
		if (!strcmp(startChars, startTsequence)) swtGoto = 1; // assigns "1" to swtGoto if it finds the char string matching startTsequence
		else if (!strcmp(startChars, startUsequence)) swtGoto = 2; // assigns "2" to swtGoto if it finds the char string matching startUsequence
		else if (!strcmp(startChars, startSsequence)) swtGoto = 3; // assigns "3" to swtGoto if it finds the char string matching startSsequence
		else swtGoto = 0;

		switch (swtGoto)
		{
		case 1:
			while (!ifs.eof()) // while not end of file...
			{
				ifs.getline(myNameBuff, 50, ','); // get next character sequence up to the ","
				if (!strcmp(endSequence, myNameBuff)) // if the character string matches endSequence, end the current iteration
				{
					cout << "FOUND END!" << endl;
					break;
				}
				ifs.getline(myDaysBuff, 10, ','); // get number of days to complete
				myDays = atoi(myDaysBuff); // convert from c-str to int
				task myTask(myNameBuff, myDays); // create new instance
				cout << "myName: " << myTask.name << endl;
				cout << "myDays: " << myTask.dayLimit << endl;
				rT->push_back(myTask); // save instance to roster
			}
			ifs.ignore(); // ignoring the \n
			break;
		case 2:
			while (!ifs.eof()) // while not at end of file...
			{
				ifs.getline(myNameBuff, 50, ','); // get name
				if (!strcmp(endSequence, myNameBuff))
				{
					cout << "FOUND END!" << endl;
					break;
				}

				user myUser(myNameBuff); // create new instance
				cout << "myUser: " << myUser.name << endl;
				rU->push_back(myUser); // save instance to roster
			}
			ifs.ignore(); // ignore the \n
			break;
		case 3:
			// FIXME: For Schedule Data
			break;
		default:
			break;
		}


	}
	ifs.close();
}