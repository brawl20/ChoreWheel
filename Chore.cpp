#include "Chore.h"


// Getter function definitions

bool Chore::getFreeDay()
{
    return freeDay;
}
bool Chore::getDishes()
{
    return dishes;
}
bool Chore::getSurfaces()
{
    return surfaces;
}
bool Chore::getSweep()
{
    return sweep;
}
bool Chore::getTrash()
{
    return trash;
}
bool Chore::getCompletedChore()
{
    return completedChore;
}

// Getter function definitions

void Chore::setFreeDay(bool newFreeDay)
{
    freeDay = newFreeDay;
}
void Chore::setDishes(bool newDishes)
{
    dishes = newDishes;
}
void Chore::setSurfaces(bool newSurfaces)
{
    surfaces = newSurfaces;
}
void Chore::setSweep(bool newSweep)
{
    sweep = newSweep;
}
void Chore::setTrash(bool newTrash)
{
    trash = newTrash;
}
void Chore::setCompletedChore(bool newCompletedChore)
{
    completedChore = newCompletedChore;
}