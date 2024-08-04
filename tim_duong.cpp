#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"
#include "Location.h"
#include "graphh.h"
#include "BFS.h"
#include "Dijiktra.h"
#include "A_star.h"

int main()
{
    sf::Mouse mouse;
    sf::RenderWindow window(sf::VideoMode(900, 420), "Grid",sf::Style::Close| sf::Style::Resize);
    Grid grid(420, 420, mouse, window);
    std::vector<std::vector<int>> adj = graph(grid);
    std::vector<std::vector<std::pair<int, double>>> ADJ = graphD(grid);
    Location PosSrc;
    Location PosTarget;
    std::vector<int> OBS;
    window.setPosition(sf::Vector2i(100, 100));

    sf::VertexArray line(sf::LinesStrip,2);
    line[0].position = sf::Vector2f(420, 0);
    line[1].position = sf::Vector2f(420, 200);
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;
    sf::VertexArray line2(sf::LinesStrip, 2);
    line2[0].position = sf::Vector2f(420, 200);
    line2[1].position = sf::Vector2f(900, 200);
    line2[0].color = sf::Color::White;
    line2[1].color = sf::Color::White;

    sf::VertexArray line3(sf::LinesStrip, 2);
    line3[0].position = sf::Vector2f(900, 0);
    line3[1].position = sf::Vector2f(900, 200);
    line3[0].color = sf::Color::White;
    line3[1].color = sf::Color::White;

    sf::VertexArray line4(sf::LinesStrip, 2);
    line4[0].position = sf::Vector2f(420, 0);
    line4[1].position = sf::Vector2f(900, 0);
    line4[0].color = sf::Color::White;
    line4[1].color = sf::Color::White;

    
    sf::RectangleShape buttonBFS;
    buttonBFS.setPosition(sf::Vector2f(450, 230));
    buttonBFS.setFillColor(sf::Color::White);
    buttonBFS.setSize(sf::Vector2f(50, 30));

    sf::RectangleShape buttonDijkstra;
    buttonDijkstra.setPosition(sf::Vector2f(600, 230));
    buttonDijkstra.setFillColor(sf::Color::White);
    buttonDijkstra.setSize(sf::Vector2f(90, 30));

    sf::RectangleShape buttonA_Star;
    buttonA_Star.setPosition(sf::Vector2f(750, 230));
    buttonA_Star.setFillColor(sf::Color::White);
    buttonA_Star.setSize(sf::Vector2f(80, 30));

    sf::RectangleShape buttonReset;
    buttonReset.setPosition(sf::Vector2f(450, 300));
    buttonReset.setFillColor(sf::Color::White);
    buttonReset.setSize(sf::Vector2f(65, 30));

    sf::RectangleShape buttonResetAll;
    buttonResetAll.setPosition(sf::Vector2f(600, 300));
    buttonResetAll.setFillColor(sf::Color::White);
    buttonResetAll.setSize(sf::Vector2f(100, 30));

    sf::RectangleShape buttonRandom;
    buttonRandom.setPosition(sf::Vector2f(750, 300));
    buttonRandom.setFillColor(sf::Color::White);
    buttonRandom.setSize(sf::Vector2f(120, 30));

    sf::CircleShape source;
    source.setPosition(sf::Vector2f(535, 350));
    source.setRadius(20);
    source.setFillColor(sf::Color::Green);
    source.setOutlineThickness(3);
    source.setOutlineColor(sf::Color::White);

    sf::CircleShape target;
    target.setPosition(sf::Vector2f(710, 350));
    target.setRadius(20);
    target.setFillColor(sf::Color::Red);
    target.setOutlineThickness(3);
    target.setOutlineColor(sf::Color::White);

    while (window.isOpen())
    {
        int x = window.getPosition().x;
        int y = window.getPosition().y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            grid.createObsRandom();
            OBS = grid.getObs();

        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            if (grid.check(x,y)) {
                grid.setObstacle();
                OBS = grid.getObs();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && grid.check(x,y)) {
                grid.setSrc();
                PosSrc = grid.getSrcPos();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && grid.check(x,y)) {
                grid.setTarget();
                PosTarget = grid.getTargetPos();

            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            pathBFS(PosSrc, PosTarget, adj, grid, window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pathDijkstra(PosSrc, PosTarget, ADJ, grid, window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            pathA_star(PosSrc, PosTarget, ADJ, grid, window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            grid.resetGrid(grid);
        }

        if (grid.checkBFS(x,y)) {
            buttonBFS.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (grid.checkST())
                    pathBFS(PosSrc, PosTarget, adj, grid, window);
                else grid.hien_thi_thong_bao();
              
            }
        } else buttonBFS.setFillColor(sf::Color::White);
       
        if (grid.checkDijkstra(x,y)) {
            buttonDijkstra.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (grid.checkST())
                    pathDijkstra(PosSrc, PosTarget, ADJ, grid, window);
                else grid.hien_thi_thong_bao();
            }
        } else buttonDijkstra.setFillColor(sf::Color::White);

        if (grid.checkA_Star(x, y)) {
            buttonA_Star.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (grid.checkST())
                    pathA_star(PosSrc, PosTarget, ADJ, grid, window);
                else grid.hien_thi_thong_bao();
            }
        }else  buttonA_Star.setFillColor(sf::Color::White);
            
        if (grid.checkReset(x, y)) {
            buttonReset.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
                grid.resetGrid(grid);
        } else buttonReset.setFillColor(sf::Color::White);
        
        if (grid.checkResetAll(x, y)) {
            buttonResetAll.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                grid.resetAllGrid(grid);
        } else  buttonResetAll.setFillColor(sf::Color::White);

        if (grid.checkRandom(x, y)) {
            buttonRandom.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                grid.createObsRandom();
        }
        else  buttonRandom.setFillColor(sf::Color::White);

        if (grid.checkSource(x, y)) {
            source.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                grid.setCheckSrc();
                while (!grid.getCheckSrc()) {
                    grid.setSrcWithMouse();
                    PosSrc = grid.getSrcPos();
                   
                }
            }
        }
        else source.setFillColor(sf::Color::Green);

        if (grid.checkTarget(x, y)) {
            target.setFillColor(sf::Color(171, 219, 227));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                grid.setCheckTarget();
                while (!grid.getCheckTarget()) {
                    grid.setTargetWithMouse();
                    PosTarget = grid.getTargetPos();

                }
            }
        }
        else target.setFillColor(sf::Color::Red);
           

       
    grid.drawGrid();
    window.draw(line);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
   
    window.draw(buttonBFS);
    window.draw(buttonDijkstra);
    window.draw(buttonA_Star);
    window.draw(buttonReset);
    window.draw(buttonResetAll);
    window.draw(buttonRandom);
    window.draw(source);
    window.draw(target);
    grid.setUp();
    grid.drawText();
    window.display();

    
}

        return 0;
    }