#include "Person.h"
#include <iostream>


int main()
{
    Person* People;
    int peopleCount = 0;
    std::cout << "Please tell me how many people are going to be doing chores:";
    std::cin >> peopleCount;
    People = new Person[peopleCount];
    for(int i = 0; i < peopleCount; i++)
    {
        std::cout << "Please enter name of person " << i+1 << ":";
        std::cin >> People[i].name;
        std::cout << People[i].name << " ADDED SUCCESSFULLY \n" ;
    }
    //TO:DO Think of an algorithm to set all the chores initially.

    return 0;
}