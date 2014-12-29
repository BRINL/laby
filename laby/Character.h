//
//  Character.h
//  laby
//
//  Created by Loïc Brin on 25/12/2014.
//  Copyright (c) 2014 Loïc Brin. All rights reserved.
//

#ifndef __laby__Character__
#define __laby__Character__

#include <stdio.h>
#include "Labyrinthe.h"


class Character
{
public:
    Character(int s=0);
    int& getSalle();
    void progression(Labyrinthe& plateau, int numsal, int choix);
    
private:
    int salle; //salle où se trouve le personnage
};

#endif /* defined(__laby__Character__) */
