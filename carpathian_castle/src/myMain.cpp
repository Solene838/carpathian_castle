/* Adaptation of https://github.com/fallahn/tmxlite/blob/master/SFMLExample/src/main.cpp :
    - #include "SFMLOrthogonalLayer.hpp"
      becomes
      #include "SFMLOrthogonalLayer.h"
    - int main()
      becomes
      int myMain()
    - map.load("assets/demo.tmx");
      becomes
      map.load("resources/demo.tmx");
*/
/*********************************************************************
(c) Matt Marchant & contributors 2016 - 2019
http://trederia.blogspot.com
tmxlite - Zlib license.
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.
2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <tmxlite/Map.hpp>

#include "SFMLOrthogonalLayer.h"
#include "Player.h"
#include "Object.h"
#include "Assets.h"
#include <iostream>
#include <vector>

int myMain()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    Assets gameAssets;
    std::vector<Object> objectsRoom1;

    Object purse(540, 260, "purse");
    purse.setSprite(gameAssets.purse);
    objectsRoom1.push_back(purse);
    
    Object book1(360, 230, "bookBlue");
    book1.setSprite(gameAssets.bookBlue);
    objectsRoom1.push_back(book1);

    Object poster(100, 200, "poster");
    poster.setSprite(gameAssets.poster);
    objectsRoom1.push_back(poster);
    


    tmx::Map map;
    map.load("resources/dunjeon.tmx");

    sf::CircleShape circle;
    Player player(400,300);
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(10);

    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);
    MapLayer layerTwo(map, 2);
    MapLayer layerThree(map, 3);
    //MapLayer layerFour(map, 4);
    //MapLayer layerObjects(map, 5);

    

    sf::Clock globalClock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Q)) {
                player.goLeft();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)) {
                player.goRight();
            }

        }

        sf::Time duration = globalClock.getElapsedTime();
        layerZero.update(duration);
        circle.setPosition(player.getX(), player.getY());

        int x_tile = int(player.getX() / 32) + 1;
        int y_tile = int(player.getY() / 32) + 1;
        //std::cerr << "pos_x/pos_y : " << player.getX() << "/" << player.getY() << " x_tile/y_tile : " << x_tile << "/" << y_tile << std::endl;

        sf::Text text;
        sf::Font arial;
        arial.loadFromFile("resources/arial.ttf");

        //check if the player is near an object
        for (Object obj : objectsRoom1) {
            if (obj.getBoxCollider().contains(player.getX(), player.getY())) {
                text.setString("Press E to interact with the object");
                text.setFont(arial);
                text.setCharacterSize(10);
                text.setStyle(sf::Text::Bold);
                text.setFillColor(sf::Color::White);
                text.setPosition(obj.getX() - 60, obj.getY() - 20);
            }
        }
        


        window.clear(sf::Color::Black);
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.draw(layerThree);
        //window.draw(layerFour);
        //window.draw(layerObjects);
        window.draw(circle);
        window.draw(text);
        window.draw(purse.getSprite());
        window.draw(book1.getSprite());
        window.display();
    }

    return 0;
}
