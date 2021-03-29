#include "AI.h"
#include <iostream>
#include "Models/enums.h"
#include <string>

using namespace std;

Answer *AI::turn(Game *game)
{

    /*
    string v = to_string(viewDist);

    string xx = to_string(me -> getX());
    string yy = to_string(me -> getY());
    string all = xx + ":" + yy;

    if (me->getType() == KARGAR)
        return new Answer(UP, all, 5);
    else
        return new Answer(DOWN, all, 5);


    CellType home;
    */

    Ant* me = game->getAnt();
    cout << me->getHealth() << " " << me->getTeam() << endl;

    int hx = game -> getBaseX();   // home x
    int hy = game -> getBaseY();   // home y

    int viewDist = me->getViewDistance();


    int targetX = -1, targetY = -1;

    if (me->getType() == KARGAR)
    {
        for (int i = 0; i < viewDist; i++)
        {
            for (int j = 0; j < viewDist; j++)
            {
                Cell* cell = game->getAnt()->getNeighborCell(i, j);

                if (me -> getType() == KARGAR && cell->getType() != WALL)
                {
                    targetX = cell->getX();
                    targetY = cell->getY();
                    break;
                }
            }
            if (targetX != -1)
                break;
        }
    }

    if (targetX == -1) {
        return new Answer(UP, "bala", 5);
    }

    int x = me->getX();
    int y = me->getY();

    Direction direction = CENTER;

    if (me -> getCurrentResource()-> getType() != NONE)
    {
        if (hx > x) {
            direction = RIGHT;
        }
        else if (hx < x) {
            direction = LEFT;
        }
        else if (hy > y) {
               direction = UP;
        }
        else{
            direction = DOWN;
        }
        return new Answer(direction, "I found a resource and I'm going to get it! :)", 10);
        // TODO for blocks
    }

    else
    {
        Cell* next;

        if (targetX > x)
        {
            next = me -> getNeighborCell(x + 1, y);

            if (next -> getType() == WALL)    // RIGHT is block
            {
                next = me -> getNeighborCell(x, y + 1);
                direction = UP;
                if (next -> getType() == WALL)    // UP is block
                {
                    next = me -> getNeighborCell(x, y - 1);
                    direction = DOWN;
                    if (next -> getType() == WALL)    // DOWN is block
                    {
                        direction = LEFT;
                    }
                }
            }
            else
            {
                direction = RIGHT;
            }
        }
        else if (targetX < x)
        {
            next = me -> getNeighborCell(x - 1 , y);
            if (next -> getType() == WALL)    // LEFT is block
            {
                next = me -> getNeighborCell(x, y + 1);
                direction = UP;
                if (next -> getType() == WALL)    // UP is block
                {
                    next = me -> getNeighborCell(x, y - 1);
                    direction = DOWN;
                    if (next -> getType() == WALL)    // DOWN is block
                    {
                        direction = RIGHT;
                    }
                }
            }
            else
            {
                direction = LEFT;
            }
        }
        else if (targetY > y)
        {
            next = me -> getNeighborCell(x, y + 1);
            if (next -> getType() == WALL)     // UP is block
            {
                next = me -> getNeighborCell(x - 1, y);
                direction = LEFT;
                if (next -> getType() == WALL)    // LEFT is block
                {
                    next = me -> getNeighborCell(x, y - 1);
                    direction = DOWN;
                    if (next -> getType() == WALL)    // DOWN is block
                    {
                        direction = RIGHT;
                    }
                }
            }
            else
            {
                direction = UP;
            }
        }
        else
        {
            next = me -> getNeighborCell(x, y - 1);

            if (next -> getType() == WALL)     // DOWN is block
            {
                next = me -> getNeighborCell(x - 1, y);
                direction = LEFT;
                if (next -> getType() == WALL)    // LEFT is block
                {
                    next = me -> getNeighborCell(x, y + 1);
                    direction = UP;
                    if (next -> getType() == WALL)    // UP is block
                    {
                        direction = RIGHT;
                    }
                }
            }
            else
            {
                direction = DOWN;
            }
        }
        return new Answer(direction, "I found a resource and I'm going to get it! :)", 10);
    }
    /*
     else{
        if (targetX > x) {
            direction = RIGHT;
        }
        else if (targetX < x) {
            direction = LEFT;
        }
        else if (targetY > y) {
            direction = UP;
        }
        else {
            direction = DOWN;
        }
        return new Answer(direction, "I found a resource and I'm going to get it! :)", 10);
    }
    */
}
