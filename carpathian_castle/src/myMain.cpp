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
#include <iostream>

int myMain()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::CircleShape circle;
    Player player(400,300);
    circle.setFillColor(sf::Color::Blue);
    circle.setRadius(10);

    tmx::Map map;
    map.load("../../../../resources/castle.tmx");
    std::cerr << "Number of tiles in the map x/y : " << map.getTileCount().x << "/" << map.getTileCount().y << std::endl;
    for (auto const& tileset : map.getTilesets()) {
        std::cerr << "Tileset name : " << tileset.getName() << std::endl;
        if (tileset.getName() != "Background_bis") {
            for (auto const& tile : tileset.getTiles()) {
                std::cerr << "Tile ID: " << tile.ID << " Tile pos_x/pos_y: " << tile.imagePosition.x << "/" << tile.imagePosition.y << std::endl;
                for (auto const& property : tile.properties) {
                    // std::cerr << "Tile property type : " << property.getType() << std::endl;
                    std::cerr << "Tile property name : " << property.getName() << std::endl;
                }
            }
        }
    }

    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);
    MapLayer layerTwo(map, 2);
    MapLayer layerThree(map, 3);
    MapLayer layerFour(map, 4);
    MapLayer layerFive(map, 5);

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
        std::cerr << "pos_x/pos_y : " << player.getX() << "/" << player.getY() << " x_tile/y_tile : " << x_tile << "/" << y_tile << std::endl;

        //get the tile corresponding to the position of the player
        //auto tile = layerTwo.getTile(x_tile, y_tile);
        //std::cerr << "tile id : " << tile.ID << std::endl;



        window.clear(sf::Color::Black);
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.draw(layerThree);
        window.draw(layerFour);
        window.draw(layerFive);
        window.draw(circle);
        window.display();
    }

    return 0;
}
