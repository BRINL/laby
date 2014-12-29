//
//  Labyrinthe.h
//  laby
//
//  Created by Loïc Brin on 25/12/2014.
//  Copyright (c) 2014 Loïc Brin. All rights reserved.
//

#ifndef __laby__Labyrinthe__
#define __laby__Labyrinthe__

#include <stdio.h>
#include "Salle.h"


class Labyrinthe
{
public:
    Labyrinthe(int n);
    Labyrinthe(Labyrinthe & L);
    Labyrinthe& operator=(Labyrinthe & L);
    virtual ~Labyrinthe();
    Salle& operator[](int i);
    void initialiser(ifstream& fichier);
    static int chartoint(char c);
protected:
    int nbsalles;
    Salle* plan;
private:
    bool is_lettre(char a);
    
};

#endif // LABYRINTHE_H
