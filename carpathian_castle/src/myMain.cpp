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
#include "Button.h"
#include "Enigma.h"
#include "Text.h"
#include <iostream>
#include <vector>


int myMain()
{
    sf::RenderWindow window(sf::VideoMode(780, 352), "SFML window");
    sf::View view2(sf::Vector2f(390, 176), sf::Vector2f(780, 352));
    Assets gameAssets;
    std::vector<Object> objectsRoom1;
    std::vector<Object> v_doors;
    std::vector<Enigma> v_en;
    pugi::xml_document doc;
    pugi::xml_document doc_enigmas;
    if (pugi::xml_parse_result result = doc.load_file("resources/objects.xml"); !result)
    {
        std::cerr << "Could not open file objects.xml because " << result.description() << std::endl;
        return 1;
    }
    for (pugi::xml_node object : doc.children("Object")) {
        Object obj(object);
        std::string label = obj.getLabel();
        std::string type = obj.getCategory();
        gameAssets.addToMap(label, type);
        obj.setSprite(gameAssets.getTexturesMap().find(label)->second);
        if (obj.getCategory() != "opened_door") {
            objectsRoom1.push_back(obj);
            std::cerr << "is_locked : " << obj.getLock() << std::endl;
        }
        else {
            v_doors.push_back(obj);
        }
    }

    if (pugi::xml_parse_result result = doc_enigmas.load_file("resources/enigmas.xml"); !result) {
        std::cerr << "Could not open file enigmas.xml because " << result.description() << std::endl;
        return 1;
    }
    for (pugi::xml_node enigma : doc_enigmas.children("Enigma")) {
        Enigma en(enigma);
        v_en.push_back(en);
    }

    bool is_open = false;
    bool pop_up_open = false;
    bool pop_up_close = false;
    


    tmx::Map map;
    map.load("resources/dungeon_two_rooms.tmx");

    sf::CircleShape circle;
    Player player(400,250);
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(10);

    MapLayer ground(map, 0);
    MapLayer ground_when_opened(map, 1);
    MapLayer doors(map, 2);
    MapLayer walls(map, 3);
    MapLayer wall_decorations(map, 4);
    MapLayer objects(map, 5);

    //std::map<std::string, sf::Text> textMap;

    sf::Clock globalClock;
    while (window.isOpen())
    {
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
                std::string tmp = "Blabla ceci est un test : " + obj.getLabel();
                /*std::string label = "test";
                Text toto("toto");
                toto.setText(tmp, arial, 10, sf::Text::Bold, sf::Color::Red);
                std::cerr << "toto label : " << toto.getLabel() << std::endl;
                textMap.try_emplace(toto.getLabel(), toto.getText());*/
            }
        }

        //check if the player is near a door
        sf::Text text_door;
        if (player.isNearDoor(doors)) {
            text_door.setString("Press R to open the door");
            text_door.setFont(arial);
            text_door.setCharacterSize(10);
            text_door.setFillColor(sf::Color::White);
            text_door.setPosition(player.getX() - 60, player.getY() + 20);
        }

        //texts for the doors
        sf::Text text_door_close;
        text_door_close.setString("You don't have the right object to open this door");
        text_door_close.setFont(arial);
        text_door_close.setCharacterSize(10);
        text_door_close.setFillColor(sf::Color::White);
        text_door_close.setPosition(player.getX() - 60, player.getY() - 30);

        sf::Text text_door_open;
        text_door_open.setString("The door is open !");
        text_door_open.setFont(arial);
        text_door_open.setCharacterSize(10);
        text_door_open.setFillColor(sf::Color::White);
        text_door_open.setPosition(player.getX() - 60, player.getY() + 20);



        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (is_open == false) {
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
            }
            if (is_open == true) {
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Q)) {
                    player.goLeft(ground_when_opened);
                }

                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)) {
                    player.goRight(ground_when_opened);
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Z)) {
                    player.goUp(ground_when_opened);
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)) {
                    player.goDown(ground_when_opened);
                }
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) {
                int index = 0;
                for (Object& obj : objectsRoom1) {
                    index += 1;
                    if (obj.getBoxCollider().contains(player.getX(), player.getY())) {
                        if (obj.getLock()) {
                            window.setActive(false);
                            if (player.doEnigma()) {
                                obj.setLock(false);
                                std::cerr << "after enigma : " << obj.getLabel() << " : " << obj.getLock() << std::endl;
                            }
                            obj.setLock(false);
                            std::cerr << "getLock true" << std::endl;
                        }
                        else {
                            player.getInventory().push_back(obj);
                            objectsRoom1.erase(objectsRoom1.begin() + index - 1);
                            std::cerr << "getLock false" << std::endl;
                        }
                    }
                }
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)) {
                if (player.isNearDoor(doors)) {
                    if (player.getInventory().empty()) {
                        pop_up_close = true;
                        std::cerr << "inventory is empty" << std::endl;
                    }
                    for (Object& obj : player.getInventory()) {
                        if (obj.getLabel() == "bookBlue") {
                            is_open = true;
                            pop_up_open = true;
                        }
                    }
                    if (is_open == false) {
                        pop_up_close = true;
                    }
                }
            }
        }

        sf::Time duration = globalClock.getElapsedTime();
        ground.update(duration);
        circle.setPosition(player.getX(), player.getY());

        

        //set up the inventory text
        sf::Text text_inventory;
        std::string display = "Inventory : \n";
        for (Object& obj : player.getInventory()) {
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
        window.setView(view2);
        window.draw(ground);
        window.draw(walls);
        window.draw(wall_decorations);
        window.draw(objects);
        window.draw(text_object);
        window.draw(text_inventory);
        if (is_open == false) {
            window.draw(doors);
        }
        if (is_open == true) {
            for (Object& obj : v_doors) {
                window.draw(obj.getSprite());
            }
            window.draw(ground_when_opened);
            if (player.getY() > 330) {
                view2.setCenter(390, 518);
                text_inventory.setPosition(600, 370);
                window.draw(text_inventory);
            }

            if (player.getY() < 350) {
                view2.setCenter(390, 176);
            }
        }
        else {
            window.draw(text_door);
        }
        if (pop_up_open == true) {
            window.draw(text_door_open);
            if (player.isNearDoor(doors) == false) {
                pop_up_open = false;
            }
        }
        if (pop_up_close == true) {
            window.draw(text_door_close);
            if (player.isNearDoor(doors) == false) {
                pop_up_close = false;
            }
        }
        for (Object obj : objectsRoom1) {
            window.draw(obj.getSprite());
            //std::cerr << "lock state of objects : " << obj.getLock() << std::endl;
        }
        /*if (textMap.find("test") == textMap.end()) {
            std::cerr << "Key not found" << std::endl;
        }
        else {
            window.draw(textMap.find("toto")->second);
        }*/
        window.draw(circle);
        window.display();
    }

    return 0;
}
