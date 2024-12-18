#include "save.h"
/* Notes
* Need to implement how to save the assignment list data
*/
void save::dataSave(list<task>* rT, list<user>* rU)
{
	fstream ofs; // create ostream
	ofs.open("practice2.txt"); // open the save file
	list<task>::iterator itT; // create iterator for tasks
	list<user>::iterator itU; // create iterator for users
	if (ofs.is_open())
	{
		ofs << "tSTART,"; // Indicator for start of task data
		for (itT = rT->begin(); itT != rT->end(); ++itT)
		{
			ofs << itT->name << "," << itT->dayLimit << ",";
		}
		ofs << "END," << endl; // End of task data

		ofs << "uSTART,"; // Indicator for start of user data
		for (itU = rU->begin(); itU != rU->end(); ++itU)
		{
			ofs << itU->name << ",";
		}
		ofs << "END," << endl; // End of user data
	}
	else
	{
		cout << "Error\n";
	}
	ofs.close(); // close file
}