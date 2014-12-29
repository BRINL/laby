//
//  Salle.cpp
//  laby
//
//  Created by Loïc Brin on 25/12/2014.
//  Copyright (c) 2014 Loïc Brin. All rights reserved.
//

#include"Salle.h"
#include<string>
#include<cstdlib>
#include<iostream>

using namespace std;

Salle::Salle()
{
    for(int i=0;i<4;i++)
    {
        portes[i].arrivee=-1;
    }
}


Salle::Salle(Salle& S)//constructeur de copie
{
    for(int i=0;i<4;i++)
    {
        portes[i]=S.portes[i];
    }
}

Salle::~Salle()
{
}


couloir Salle::getPorte(int i)
{
      return portes[i];
}


void Salle::affecter(int i, couloir C)
{
    //affecter le couloir C à la porte i
    portes[i%4]=C;
}
