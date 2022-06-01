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

    Object purse(240, 260, "purse");
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
    Player player(400,250);
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(10);

    MapLayer ground(map, 0);
    MapLayer layerOne(map, 1);
    MapLayer layerTwo(map, 2);
    MapLayer layerThree(map, 3);

    

    sf::Clock globalClock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Q)) {
                player.goLeft(ground);
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)) {
                player.goRight(ground);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Z)) {
                player.goUp(ground);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)) {
                player.goDown(ground);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) {
                int index = 0;
                for (Object obj : objectsRoom1) {
                    index += 1;
                    if (obj.getBoxCollider().contains(player.getX(), player.getY())) {
                        player.getInventory().push_back(obj);
                        objectsRoom1.erase(objectsRoom1.begin() + index - 1);
                    }
                }
            }
        }

        sf::Time duration = globalClock.getElapsedTime();
        ground.update(duration);
        circle.setPosition(player.getX(), player.getY());

        sf::Text text_object;
        sf::Font arial;
        arial.loadFromFile("resources/arial.ttf");

        //check if the player is near an object
        for (Object obj : objectsRoom1) {
            if (obj.getBoxCollider().contains(player.getX(), player.getY())) {
                text_object.setString("Press E to interact with the object : " + obj.getLabel());
                text_object.setFont(arial);
                text_object.setCharacterSize(10);
                text_object.setStyle(sf::Text::Bold);
                text_object.setFillColor(sf::Color::White);
                text_object.setPosition(obj.getX() - 60, obj.getY() - 20);
            }
        }

        //set up the inventory text
        sf::Text text_inventory;
        std::string display = "Inventory : \n";
        for (Object obj : player.getInventory()) {
            display += obj.getLabel();
            display += "\n";
        }
        text_inventory.setString(display);
        text_inventory.setFont(arial);
        text_inventory.setCharacterSize(20);
        text_inventory.setStyle(sf::Text::Bold);
        text_inventory.setFillColor(sf::Color::White);
        text_inventory.setPosition(600, 50);


        window.clear(sf::Color::Black);
        window.draw(ground);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.draw(layerThree);
        window.draw(circle);
        window.draw(text_object);
        window.draw(text_inventory);
        for (Object obj : objectsRoom1) {
            window.draw(obj.getSprite());
        }
        window.display();
    }

    return 0;
}
