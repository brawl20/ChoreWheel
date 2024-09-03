#ifndef CHORE_H
#define CHORE_H

class Chore
{
    private:
    bool freeDay;
    bool dishes;
    bool surfaces;
    bool sweep;
    bool trash;
    bool completedChore;

    public:
    //Getters
    bool getFreeDay();
    bool getDishes();
    bool getSurfaces();
    bool getSweep();
    bool getTrash();
    bool getCompletedChore();

    // Setters
    void setFreeDay(bool newFreeDay);
    void setDishes(bool newDishes);
    void setSurfaces(bool newSurfaces);
    void setSweep(bool newSweep);
    void setTrash(bool newTrash);
    void setCompletedChore(bool newCompletedChore);
};

#endif