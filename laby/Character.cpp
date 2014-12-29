//
//  Character.cpp
//  laby
//
//  Created by Loïc Brin on 25/12/2014.
//  Copyright (c) 2014 Loïc Brin. All rights reserved.
//

#include "Character.h"

#include<iostream>
#include "Labyrinthe.h"

int chartoint(char c);

Character::Character(int s)
{
    salle=s;
}

int& Character::getSalle()
{
    return salle;
}




void Character::progression(Labyrinthe& plateau, int numsal, int choix)
{
    if (choix==100){}
    else {
        salle=plateau[numsal].getPorte(choix).arrivee;
    }
}

