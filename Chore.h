#ifndef CHORE_H
#define CHORE_H

class Chore
{
    private:
    bool freeDay = 0;
    bool dishes = 0;
    bool surfaces = 0;
    bool sweep = 0;
    bool trash = 0;
    bool completedChore = 0;

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