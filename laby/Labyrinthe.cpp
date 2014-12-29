#include<iostream>
#include<fstream>

#include "Labyrinthe.h"


using namespace std;


Labyrinthe::Labyrinthe(int n)
{
    nbsalles=n;
    plan=new Salle[n];
}

Labyrinthe::Labyrinthe(Labyrinthe& L)//constructeur de copie
{
    nbsalles=L.nbsalles;
    plan=new Salle[nbsalles];
    for(int i=0;i<nbsalles;i++){
        plan[i]=L.plan[i];
    }
}

Labyrinthe& Labyrinthe::operator=(Labyrinthe& L)//opérateur de copie
{
    if(nbsalles!=L.nbsalles){
        delete[] plan;
        nbsalles=L.nbsalles;
        plan=new Salle[nbsalles];
    }
    for(int i=0;i<nbsalles;i++){plan[i]=L.plan[i];}
    return(*this);
}


Labyrinthe::~Labyrinthe()
{
    delete[]plan;
}


Salle& Labyrinthe::operator[](int i) //acces à la salle i
{
    if(i<nbsalles)
    {
        return plan[i];
    }
    else{cerr<<"oucct oef range"<<nbsalles;cout << i << endl ;}
}


void Labyrinthe::initialiser(ifstream& fichier)
{
    fichier.clear();
    fichier.seekg(0, ios::beg);//on se replace au début du fichier
    string ligne; //déclaration d'une chaine qui contient la ligne lue
    getline(fichier,ligne);//La première ligne n'est pas intéressante
    getline(fichier,ligne);
    while(ligne!="finPlan"){
        if(ligne.size()!=0 && is_lettre(ligne[0])){
            int esp=ligne.find(" ");//emplacement du caractère espace : fin du nom
            int point1=ligne.find(".");//emplacemen du premier point
            int point2=ligne.substr(point1+3).find(".");//emplacement du point après le tiret
            int salle1=atoi(ligne.substr(esp+1,point1-esp-1).c_str());//numéro de la première salle concernée
            int salle2=atoi(ligne.substr(point1+3,point2).c_str());//numéro de la seconde ligne concernée
            couloir C1,C2;
            C1.arrivee=salle2;
            C1.direction=ligne[point1+4+point2];// mur par lequel on arrive dans la salle 2 depuis la salle1.
            C2.arrivee=salle1;
            C2.direction=ligne[point1+1];// mur par lequel on passe de la salle 1 à la salle 2.
            
            plan[salle1].affecter(chartoint(ligne[point1+1]),C1);
            plan[salle2].affecter(chartoint(ligne[point1+4+point2]),C2);
        }
        getline(fichier,ligne);
    }
}

bool Labyrinthe::is_lettre(char a)
{
    return (a>='a'&&a<='z')||(a>='A'&&a<='Z');
}//teste si un caractère est une lettre

int Labyrinthe::chartoint(char c)
{
    switch(c)
    {
        case 'N':return 0;
        case 'E': return 1;
        case 'S':return 2;
        case 'O': return 3;
        default : cerr<<"Plan incorrect"<<endl;
            return -1;
    }
}
