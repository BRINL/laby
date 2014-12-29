////////////////// STANDARD LIBRARY /////////////////

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<limits>

///////////////// SFML /////////////////

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

///////////////// FICHIERS HEADER /////////////////

#include "ResourcePath.hpp"
#include "Graph.h"
#include "Character.h"
#include "Labyrinthe.h"
#include "Salle.h"


using namespace std;



int nombresalles(ifstream & fichier);
int yarr(char x, int sizex, int sizey);
int xarr(char x, int sizex, int sizey);

void newroom(sf::Texture& texture, sf::RectangleShape& RN, sf::RectangleShape& RE, sf::RectangleShape& RS ,sf::RectangleShape& RO, sf::Sprite& sprite_perso, int s, sf::Font& font, sf::RenderWindow& window, int xposperso, int yposperso, string& numsal, sf::Text& text, int nbSalles, bool doors[4]);

bool is_lettre(char a){return (a>='a'&&a<='z')||(a>='A'&&a<='Z');}



int main(int, char const**)
{
    int speed=3;
   
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Rainbeau Warrior", sf::Style::Close);
    
    // size of the windows ; they will be used to define areas
    int sizex=window.getSize().x ;
    int sizey=window.getSize().y ;
    
    // Position of the windows
    window.setPosition(sf::Vector2i(200,200));
    
    // Set number of image each second
    window.setFramerateLimit(60);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "OldeEnglish.ttf"))
    {
        return EXIT_FAILURE;
    }
    
    // Strings to display
    string numsal="Salle 0";
    sf::Text text(numsal, font, 30);
    text.setPosition(sizex*0.75,sizey*0.88);
    text.setColor(sf::Color::Black);
    
    string gamename="Rainbow Warrior";
    sf::Text gamen(gamename, font, 30);
    gamen.setPosition(sizex*0.23,sizey*0.45);
    gamen.setColor(sf::Color::Black);
    
    string bravo="Azatoth runs away, you win !";
    sf::Text bravot(bravo, font, 27);
    bravot.setPosition(sizex*0.05,sizey*0.10);
    bravot.setColor(sf::Color::Black);
    

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "laby.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "parquet.jpg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    sprite.scale(0.4,0.4);
    

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "horror.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Music music2;
    if (!music2.openFromFile(resourcePath() + "victory.ogg"))
    {
        return EXIT_FAILURE;
    }


    // Play the music
    music.play();
    music.setLoop(1);


    // Load the character
    sf::Texture perso;
    sf::Sprite sprite_perso;
    sprite_perso.setPosition(sizex*0.5, sizey*0.5);
    
    
    // Animation
    enum Dir{Up,Down,Right,Left};
    sf::Vector2i anim(1,Down);
    
    // Limit time before refreshing
    bool updateAnim=false;
    sf::Clock time;
    
    // Loading the characters
    if(!perso.loadFromFile(resourcePath() + "perso.png"))
    {
        return EXIT_FAILURE;
    }
    perso.setSmooth(true);
    sprite_perso.setTexture(perso);
    sprite_perso.setTextureRect(sf::IntRect(anim.x*32,anim.y*32,32,32));
    
    sf::Texture azatoth;
    sf::Sprite sprite_azatoth;
    sprite_azatoth.setPosition(sizex*0.45, sizey*0.15);
    if(!azatoth.loadFromFile(resourcePath() + "azatoth.png"))
    {
        return EXIT_FAILURE;
    }
    azatoth.setSmooth(true);
    sprite_azatoth.setTexture(azatoth);
    sprite_azatoth.setTextureRect(sf::IntRect(anim.x*32,anim.y*32,32,32));
    
    ifstream fichier(resourcePath() + "plan.pln", ios::in);
    int NbSalles;
    NbSalles=nombresalles(fichier);
    
    Labyrinthe plateau(NbSalles);
    plateau.initialiser(fichier);
    fichier.close();
    Character hero(0);
    int choix = 0;
    static int s=hero.getSalle();

    // Transparent color
    sf::Color transp(255, 0, 0, 0);
    
    // Doors
    sf::RectangleShape trans;
    trans.setSize(sf::Vector2f(sizex,sizey));
    trans.setPosition(0,0);
    trans.setRotation(0);
    trans.setFillColor(transp);
    
    sf::RectangleShape rectN;
    rectN.setSize(sf::Vector2f(0.33*sizex,0.033*sizey));
    rectN.setPosition(0.33*sizex,0);
    rectN.setRotation(0);
    rectN.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectS;
    rectS.setSize(sf::Vector2f(0.33*sizex,0.033*sizey));
    rectS.setPosition(0.33*sizex,(1-0.033)*sizey);
    rectS.setRotation(0);
    rectS.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectO;
    rectO.setSize(sf::Vector2f(0.33*sizex,0.033*sizey));
    rectO.setPosition(0.033*sizex,0.33*sizey);
    rectO.setRotation(90);
    rectO.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectE;
    rectE.setSize(sf::Vector2f(0.33*sizex,0.033*sizey));
    rectE.setPosition(sizex,0.33*sizey);
    rectE.setRotation(90);
    rectE.setFillColor(sf::Color::Black);
    bool doors[4];
    doors[0]=(plateau[0].getPorte(0).arrivee==-1);
    doors[1]=(plateau[0].getPorte(1).arrivee==-1);
    doors[2]=(plateau[0].getPorte(2).arrivee==-1);
    doors[3]=(plateau[0].getPorte(3).arrivee==-1);
    if(doors[0]){rectN.setFillColor(transp);}else{rectN.setFillColor(sf::Color::Black);}
    if(doors[1]){rectE.setFillColor(transp);}else{rectE.setFillColor(sf::Color::Black);}
    if(doors[2]){rectS.setFillColor(transp);}else{rectS.setFillColor(sf::Color::Black);}
    if(doors[3]){rectO.setFillColor(transp);}else{rectO.setFillColor(sf::Color::Black);}
    
    
    while (window.isOpen())
    {

        
        // Process events
        sf::Event event;
        
        // Coordonnates of the character (arrival)
        int arrx;
        int arry;
        
        while (window.pollEvent(event))
        {
            trans.setFillColor(transp);
            sizex=window.getSize().x ;
            sizey=window.getSize().y ;
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            
            // If a key is pressed
            if (event.type==sf::Event::KeyPressed){updateAnim=true;}
            else {updateAnim=false;};
            
            
            // Taking the south door (2)
            if(sprite_perso.getPosition().y>=sizey*(1-0.13) && sprite_perso.getPosition().x>=sizex*0.33 &&  sprite_perso.getPosition().x<=sizex*(0.66) && (plateau[s].getPorte(2).arrivee!=-1))
            {
                arrx=xarr(plateau[s].getPorte(2).direction, sizex, sizey);
                arry=yarr(plateau[s].getPorte(2).direction, sizex, sizey);
                hero.progression(plateau, s, 2);
                numsal = "Salle " + to_string(hero.getSalle());
                bool doors[4];
                doors[0]=(plateau[hero.getSalle()].getPorte(0).arrivee==-1);
                doors[1]=(plateau[hero.getSalle()].getPorte(1).arrivee==-1);
                doors[2]=(plateau[hero.getSalle()].getPorte(2).arrivee==-1);
                doors[3]=(plateau[hero.getSalle()].getPorte(3).arrivee==-1);
                newroom(texture, rectN, rectE, rectS, rectO, sprite_perso, hero.getSalle(), font, window, arrx, arry, numsal,text, NbSalles, doors);
                trans.setFillColor(sf::Color::Black);
            }
            
            // Taking the north door (0)
            else if(sprite_perso.getPosition().y<=sizey*(0.033) && sprite_perso.getPosition().x>=sizex*0.33 &&  sprite_perso.getPosition().x<=sizex*(0.66) && plateau[s].getPorte(0).arrivee!=-1)
            {
                arrx=xarr(plateau[s].getPorte(0).direction,sizex, sizey);
                arry=yarr(plateau[s].getPorte(0).direction,sizex, sizey);
                hero.progression(plateau, s, 0);
                numsal = "Salle " + to_string(hero.getSalle());
                bool doors[4];
                doors[0]=(plateau[hero.getSalle()].getPorte(0).arrivee==-1);
                doors[1]=(plateau[hero.getSalle()].getPorte(1).arrivee==-1);
                doors[2]=(plateau[hero.getSalle()].getPorte(2).arrivee==-1);
                doors[3]=(plateau[hero.getSalle()].getPorte(3).arrivee==-1);
                newroom(texture, rectN, rectE, rectS, rectO,  sprite_perso, hero.getSalle(), font, window, arrx, arry, numsal,text, NbSalles, doors);
                trans.setFillColor(sf::Color::Black);
            }
            
            
            // Taking the west door (3)
            else if(sprite_perso.getPosition().y>=sizey*0.33 && sprite_perso.getPosition().y<=sizey*0.66 &&  sprite_perso.getPosition().x<=sizex*(0.13) && (plateau[s].getPorte(3).arrivee!=-1))
            {
                arrx=xarr(plateau[s].getPorte(3).direction, sizex, sizey);
                arry=yarr(plateau[s].getPorte(3).direction, sizex, sizey);
                hero.progression(plateau, s, 3);
                numsal = "Salle " + to_string(hero.getSalle());
                bool doors[4];
                doors[0]=(plateau[hero.getSalle()].getPorte(0).arrivee==-1);
                doors[1]=(plateau[hero.getSalle()].getPorte(1).arrivee==-1);
                doors[2]=(plateau[hero.getSalle()].getPorte(2).arrivee==-1);
                doors[3]=(plateau[hero.getSalle()].getPorte(3).arrivee==-1);
                newroom(texture, rectN, rectE, rectS, rectO, sprite_perso, hero.getSalle(), font, window, arrx, arry, numsal,text,NbSalles, doors);
                trans.setFillColor(sf::Color::Black);
            }
            
            
            // Taking the east door (1)
            else if(sprite_perso.getPosition().y>=sizey*0.33 && sprite_perso.getPosition().x>=sizex*(1-0.13) &&  sprite_perso.getPosition().y<=sizey*(0.66) && (plateau[s].getPorte(1).arrivee!=-1))
            {
                arrx=xarr(plateau[s].getPorte(1).direction, sizex, sizey);
                arry=yarr(plateau[s].getPorte(1).direction, sizex, sizey);
                hero.progression(plateau, s, 1);
                numsal = "Salle " + to_string(hero.getSalle());
                bool doors[4];
                doors[0]=(plateau[hero.getSalle()].getPorte(0).arrivee==-1);
                doors[1]=(plateau[hero.getSalle()].getPorte(1).arrivee==-1);
                doors[2]=(plateau[hero.getSalle()].getPorte(2).arrivee==-1);
                doors[3]=(plateau[hero.getSalle()].getPorte(3).arrivee==-1);
                newroom(texture, rectN, rectE, rectS, rectO, sprite_perso, hero.getSalle(), font, window, arrx , arry, numsal,text, NbSalles, doors);
                trans.setFillColor(sf::Color::Black);
            }
            s=hero.getSalle() ;

    }
    
        
    GestionClavier(sprite_perso,anim,window,speed);

    
    if (updateAnim)
    {
       if(time.getElapsedTime().asMilliseconds()>60)
       {
           anim.x++;
           if (anim.x*32>=perso.getSize().x)
           {
                anim.x=0;
           }
           else
           {
                sprite_perso.setTextureRect(sf::IntRect(anim.x*32,anim.y*32,32,32));
           }
           time.restart();
       }
    }
        
        if (updateAnim)
        {
            if(time.getElapsedTime().asMilliseconds()>60)
            {
                anim.x++;
                if (anim.x*32>=azatoth.getSize().x)
                {
                    anim.x=0;
                }
                else
                {
                    sprite_azatoth.setTextureRect(sf::IntRect(anim.x*32,anim.y*32,32,32));
                }
                time.restart();
            }
        }

    // Clear screen
    window.clear();
    
    // Draw the rooms
    window.draw(sprite);
    window.draw(gamen);
    window.draw(sprite_perso);
    window.draw(rectN);
    window.draw(rectS);
    window.draw(rectO);
    window.draw(rectE);
    window.draw(trans);
    
    // Draw the string
    window.draw(text);
    if (hero.getSalle()==NbSalles-1)
    {
        anime(sprite_azatoth,anim,window,2);
        if (sprite_azatoth.getPosition().x<0){window.draw(bravot);speed=0;}
        window.draw(sprite_azatoth);
        ;
    }
        
    // Update the window
    window.display();
    }
    return EXIT_SUCCESS;
}


void newroom(sf::Texture& texture, sf::RectangleShape& RN, sf::RectangleShape& RE, sf::RectangleShape& RS ,sf::RectangleShape& RO, sf::Sprite& sprite_perso, int s, sf::Font& font, sf::RenderWindow& window, int xposperso, int yposperso, string& numsal, sf::Text& text, int nbSalles, bool doors[4])
{
    //Nouveau parquet
    if (s==nbSalles-1)
    {
       if (!texture.loadFromFile(resourcePath() + "parquet2.jpg"))
       {
           return EXIT_FAILURE;
       }
       sf::Sprite sprite(texture);
       sprite.scale(0.4,0.4);
    }
    
    //Nouvelle position du personnage
    sprite_perso.setPosition(xposperso,yposperso);
    
    //Nouvelles portes
    sf::Color transp(255, 0, 0, 0);
    if(doors[0]){RN.setFillColor(transp);}else{RN.setFillColor(sf::Color::Black);}
    if(doors[1]){RE.setFillColor(transp);}else{RE.setFillColor(sf::Color::Black);}
    if(doors[2]){RS.setFillColor(transp);}else{RS.setFillColor(sf::Color::Black);}
    if(doors[3]){RO.setFillColor(transp);}else{RO.setFillColor(sf::Color::Black);}
    
    //Nouveau texte
    text.setString(numsal);
    window.display();
    {
        return EXIT_SUCCESS;
    }
}

int nombresalles(ifstream & fichier){
    int n=0;//On compte le nombre de salles
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
            if(salle1>n){n=salle1;}
            if(salle2>n){n=salle2;}
        }
        getline(fichier,ligne);
    }
    return n+1; //Les salles sont numérotées de 0 à n
}

int xarr(char x, int sizex, int sizey)
{
    switch(x)
    {
        case 'N':return sizex*0.5;
        case 'E': return sizex*(1-0.14);
        case 'S':return sizex*0.5;
        case 'O': return sizex*0.13;
    }
}

int yarr(char x, int sizex, int sizey)
{
    switch(x)
    {
        case 'N':return sizey*0.13;
        case 'E': return sizey*0.5;
        case 'S':return sizey*(1-0.14);
        case 'O': return sizey*0.5;
    }
}

