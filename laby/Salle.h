//
//  Salle.h
//  laby
//
//  Created by Loïc Brin on 25/12/2014.
//  Copyright (c) 2014 Loïc Brin. All rights reserved.
//

#ifndef __laby__Salle__
#define __laby__Salle__

#include <stdio.h>
#include<cstdlib>
#include<string>

using namespace std;

typedef struct
{
    int arrivee;
    char direction;
}
couloir;

class Salle
{
public:
    Salle();
    Salle(Salle & S);
    virtual ~Salle();
    void affecter(int i, couloir C);
    couloir getPorte(int i);
    
private:
    couloir portes[4];
};

#endif // SALLE_H

