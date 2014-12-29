#include "Graph.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"




void GestionClavier(sf::Sprite& sperso, sf::Vector2i& anim,sf::RenderWindow& window,int speed){
    enum Dir{Down,Left,Right,Up};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        anim.y=Up;
        sperso.move(0,-speed);
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        anim.y=Down;
        sperso.move(0,speed);
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        anim.y=Left;
        sperso.move(-speed,0);
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        anim.y=Right;
        sperso.move(speed,0);
    }
    
    /*Evite au personnage de sortir de la fenêtre*/
    if(sperso.getPosition().x<=0)sperso.setPosition(sf::Vector2f(0,sperso.getPosition().y));
    if(sperso.getPosition().y<=0)sperso.setPosition(sf::Vector2f(sperso.getPosition().x,0));
    if(sperso.getPosition().x>=window.getSize().x*0.88)sperso.setPosition(sf::Vector2f(window.getSize().x*0.88,sperso.getPosition().y));
    if(sperso.getPosition().y>=window.getSize().y*0.88)sperso.setPosition(sf::Vector2f(sperso.getPosition().x,window.getSize().y*0.88));
}


void anime(sf::Sprite& sperso, sf::Vector2i& anim,sf::RenderWindow& window,int speed)
{
    enum Dir{Left};
    anim.y=Left;
    sperso.move(-speed,0);
}
