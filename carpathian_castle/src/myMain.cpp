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
#include "Pickable.h"
#include "Door.h"
#include "UIObjects.h"
#include <iostream>
#include <vector>


int myMain()
{
    sf::RenderWindow window(sf::VideoMode(780, 352), "SFML window");
    sf::View view2(sf::Vector2f(390, 500), sf::Vector2f(780, 352));
    Assets gameAssets;
    std::vector<Pickable> objectsRoom1;
    std::vector<Door> v_doors_room1;
    std::vector<Door> v_doors_room2;
    std::vector<UIObjects> ui;
    std::vector<Enigma> v_en;
    pugi::xml_document doc;
    pugi::xml_document doc_enigmas;
    if (pugi::xml_parse_result result = doc.load_file("resources/objects.xml"); !result)
    {
        std::cerr << "Could not open file objects.xml because " << result.description() << std::endl;
        return 1;
    }

    for (pugi::xml_node pickable : doc.children("Pickable")) {
        Pickable pic(pickable);
        std::string label = pic.getLabel();
        std::string category = pic.getCategory();
        gameAssets.addToMap(label, category);
        pic.setSprite(gameAssets.getTexturesMap().find(label)->second);
        objectsRoom1.push_back(pic);
        std::cerr << "is_locked : " << pic.getLock() << std::endl;
    }

    for (pugi::xml_node door : doc.children("Doors")) {
        Door d(door);
        std::string label = d.getLabel();
        std::string category = d.getCategory();
        gameAssets.addToMap(label, category);
        d.setSprite(gameAssets.getTexturesMap().find(label)->second);
        if (d.getRoom() == 1) {
            v_doors_room1.push_back(d);
        }
        else if (d.getRoom() == 2) {
            v_doors_room2.push_back(d);
        }
    }

    for (pugi::xml_node uiobject : doc.children("UIObjects")) {
        UIObjects u(uiobject);
        std::string label = u.getLabel();
        std::string category = u.getCategory();
        gameAssets.addToMap(label, category);
        u.setSprite(gameAssets.getTexturesMap().find(label)->second);
        ui.push_back(u);
    }

    if (pugi::xml_parse_result result = doc_enigmas.load_file("resources/enigmas.xml"); !result) {
        std::cerr << "Could not open file enigmas.xml because " << result.description() << std::endl;
        return 1;
    }
    for (pugi::xml_node enigma : doc_enigmas.children("Enigma")) {
        Enigma en(enigma);
        v_en.push_back(en);
    }

    bool room1_is_open = false;
    bool room2_is_open = false;
    bool pop_up_open = false;
    bool pop_up_close = false;
    bool main_menu = true;
    bool pause = false;
    bool dead = false;
    int id_room_in = 0;

    tmx::Map map;
    map.load("resources/dungeon_two_rooms.tmx");

    sf::CircleShape circle;
    Player player(400,550, 3);
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(10);

    sf::Texture heart;
    heart.loadFromFile("resources/Sprite/heart.png");


    MapLayer ground(map, 0);
    MapLayer ground_when_opened(map, 1);
    MapLayer peaks(map, 2);
    MapLayer doors(map, 3);
    MapLayer walls(map, 4);
    MapLayer wall_decorations(map, 5);
    MapLayer objects(map, 6);


    sf::Clock globalClock;
    while (window.isOpen())
    {
        sf::Text text_object;
        sf::Font arial;
        arial.loadFromFile("resources/arial.ttf");

        //check if the player is near an object
        for (Pickable obj : objectsRoom1) {
            if (obj.getBoxCollider().contains(player.getX(), player.getY())) {
                text_object.setString("Press E to interact with the object : " + obj.getLabel());
                text_object.setFont(arial);
                text_object.setCharacterSize(10);
                text_object.setStyle(sf::Text::Bold);
                text_object.setFillColor(sf::Color::White);
                text_object.setPosition(obj.getX() - 60, obj.getY() - 20);
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

        sf::Text title;
        title.setString("Carpathian castle");
        title.setFont(arial);
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::White);
        title.setPosition(200, 80);

        sf::Text game_over;
        game_over.setString("Game Over");
        game_over.setFont(arial);
        game_over.setCharacterSize(50);
        game_over.setFillColor(sf::Color::White);
        game_over.setPosition(200, 50);

        Button start_button("Start", { 300, 75 }, 45, sf::Color::White, sf::Color::Black);
        start_button.setPosition({ 390, 216 });
        start_button.setFont(arial);

        Button quit("Quit", { 250, 40 }, 20, sf::Color::White, sf::Color::Black);
        quit.setPosition({ 390, 568 });
        quit.setFont(arial);

        Button return_main_menu("Return to main menu", { 250, 40 }, 20, sf::Color::White, sf::Color::Black);
        return_main_menu.setPosition({ 390, 442 });
        return_main_menu.setFont(arial);

        sf::RectangleShape fade(sf::Vector2f(780, 352));
        fade.setOrigin(390, 176);
        fade.setPosition(390, 176);
        fade.setFillColor(sf::Color(0, 0, 0, 150));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (room1_is_open == false) {
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Q) && dead == false && pause == false) {
                    player.goLeft(ground);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D) && dead == false && pause == false) {
                    player.goRight(ground);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Z) && dead == false && pause == false) {
                    player.goUp(ground);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S) && dead == false && pause == false) {
                    player.goDown(ground);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
            }
            if (room1_is_open == true) {
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Q) && dead == false && pause == false) {
                    player.goLeft(ground_when_opened);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D) && dead == false && pause == false) {
                    player.goRight(ground_when_opened);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Z) && dead == false && pause == false) {
                    player.goUp(ground_when_opened);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S) && dead == false && pause == false) {
                    player.goDown(ground_when_opened);
                    if (player.isOnPeaks(peaks)) {
                        player.setHealth(player.getHealth() - 1);
                    }
                }
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)) {
                int index = 0;
                for (Pickable& obj : objectsRoom1) {
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
                    for (Pickable& obj : player.getInventory()) {
                        if (obj.getLabel() == "bookBlue") {
                            room1_is_open = true;
                            pop_up_open = true;
                        }
                        else if (obj.getLabel() == "poster") {
                            room2_is_open = true;
                            pop_up_open = true;
                        }
                    }
                    if (room1_is_open == false) {
                        pop_up_close = true;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (start_button.isMouseOver(window) && main_menu == true) {
                    main_menu = false;
                }
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                pause = !pause;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (quit.isMouseOver(window) && pause == true) {
                    exit(0);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (return_main_menu.isMouseOver(window) && (pause == true || dead == true)) {
                    main_menu = true;
                    pause = false;
                }
            }

            if (return_main_menu.isMouseOver(window)) {
                return_main_menu.setBackColor(sf::Color::Green);
            }

        }

        sf::Time duration = globalClock.getElapsedTime();
        ground.update(duration);
        circle.setPosition(player.getX(), player.getY());

        

        //set up the inventory text
        sf::Text text_inventory;
        std::string display = "Inventory : \n";
        for (Pickable const& obj : player.getInventory()) {
            display += obj.getLabel();
            display += "\n";
        }
        text_inventory.setString(display);
        text_inventory.setFont(arial);
        text_inventory.setCharacterSize(20);
        text_inventory.setStyle(sf::Text::Bold);
        text_inventory.setFillColor(sf::Color::White);
        text_inventory.setPosition(600, 370);
        window.setView(view2);

        if (main_menu == true) {
            player.setHealth(3);
            dead = false;
            view2.setCenter(390, 176);
            window.clear(sf::Color::Black);
            start_button.drawTo(window);
            window.draw(title);
        }
        if (main_menu == false) {
            window.clear(sf::Color::Black);
            view2.setCenter(390, 500);
            if (room1_is_open == true) {
                window.draw(ground_when_opened);
                window.draw(walls);
                window.draw(wall_decorations);
                window.draw(peaks);
                window.draw(doors);
                window.draw(text_door);
                window.draw(objects);
                window.draw(text_object);
                window.draw(text_inventory);

                if (player.getY() > 330) {
                    id_room_in = 0;
                    view2.setCenter(390, 500);
                    text_inventory.setPosition(600, 370);
                    window.draw(text_inventory);
                    for (Door& obj: v_doors_room1) {
                        window.draw(obj.getSprite());
                    }
                    ui[0].setPosition(600, 560);
                    ui[0].setSprite(gameAssets.getTexturesMap().find(ui[0].getLabel())->second);
                    ui[1].setPosition(620, 560);
                    ui[1].setSprite(gameAssets.getTexturesMap().find(ui[1].getLabel())->second);
                    ui[2].setPosition(640, 560);
                    ui[2].setSprite(gameAssets.getTexturesMap().find(ui[2].getLabel())->second);
                }

                if (player.getY() < 350) {
                    id_room_in = 1;
                    text_inventory.setPosition(600, 50);
                    window.draw(text_inventory);
                    view2.setCenter(390, 176);
                    for (Door& obj : v_doors_room1) {
                        window.draw(obj.getSprite());
                    }
                    ui[0].setPosition(600, 300);
                    ui[0].setSprite(gameAssets.getTexturesMap().find(ui[0].getLabel())->second);
                    ui[1].setPosition(620, 300);
                    ui[1].setSprite(gameAssets.getTexturesMap().find(ui[1].getLabel())->second);
                    ui[2].setPosition(640, 300);
                    ui[2].setSprite(gameAssets.getTexturesMap().find(ui[2].getLabel())->second);
                }
            }
            else if (room2_is_open) {
                for (Door& obj : v_doors_room2) {
                    window.draw(obj.getSprite());
                }
            }
            else {
                window.draw(ground);
                window.draw(walls);
                window.draw(wall_decorations);
                window.draw(peaks);
                window.draw(objects);
                window.draw(text_object);
                window.draw(text_inventory);
                window.draw(doors);
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
            for (Pickable obj : objectsRoom1) {
                window.draw(obj.getSprite());
            }
            if (player.getHealth() == 3) {
                window.draw(ui[0].getSprite());
                window.draw(ui[1].getSprite());
                window.draw(ui[2].getSprite());
            }
            if (player.getHealth() == 2) {
                window.draw(ui[0].getSprite());
                window.draw(ui[1].getSprite());
            }
            if (player.getHealth() == 1) {
                window.draw(ui[0].getSprite());
            }


            window.draw(circle);

            if (pause == true) {
                if (id_room_in == 0) {
                    fade.setPosition(390, 500);
                    quit.setPosition({ 390, 568 });
                    return_main_menu.setPosition({ 390, 442 });
                }
                if (id_room_in == 1) {
                    fade.setPosition(390, 176);
                    quit.setPosition({ 390, 300 });
                    return_main_menu.setPosition({ 390, 130 });
                }
                window.draw(fade);
                quit.drawTo(window);
                return_main_menu.drawTo(window);
            }

            if (player.getHealth() == 0) {
                dead = true;
                if (id_room_in == 0) {
                    fade.setPosition(390, 500);
                    return_main_menu.setPosition({ 390, 442 });
                    game_over.setPosition(250, 340);
                }
                if (id_room_in == 1) {
                    fade.setPosition(390, 176);
                    return_main_menu.setPosition({ 390, 130 });
                    game_over.setPosition(250, 20);
                }
                window.draw(fade);
                window.draw(game_over);
                return_main_menu.drawTo(window);
            }
        }  
        window.display();
    }

    return 0;
}
