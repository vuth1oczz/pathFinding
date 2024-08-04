#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Location.h"
#include <stdlib.h>
#include <thread>
class Grid {
private:
    std::vector<sf::RectangleShape> TileMap;
    std::vector<int> Obstacles;

    const sf::Mouse mouse;
    sf::RenderWindow& window;
    
    static constexpr int TileDimension = 15;
    static constexpr int OutlineThickness = 1.5;
    const int screenwidth;
    const int screenheight;
    Location srcPos;
    Location targetPos;
    bool srcPoscheck = false;
    bool targetPoscheck = false;
    int NumTilesX;
    int NumTilesY;
    int numOBS = 0;
    sf::Color openTileColour = sf::Color::White;
    sf::Color obstacleTileColour = sf::Color::Black;
    sf::Color srcTileColour = sf::Color::Green;
    sf::Color targetTileColour = sf::Color::Red;
    sf::Color visitedTileColour = sf::Color::Blue;
    sf::Color visitngTileColour = sf::Color::Cyan;
    sf::Color pathColor = sf::Color::Yellow;

    sf::Text textBFS;
    sf::Text textD;
    sf::Text textA;
    sf::Text textReset;
    sf::Text textResetALL;
    sf::Text textRandom;
    sf::Text textSource;
    sf::Text textTarget;
    sf::Text textDepcri;
    
    sf::Font font;

    
    
    
public:

    Grid(int Width, int Height, sf::Mouse mouse, sf::RenderWindow& createwindow) : screenwidth(Width),
        screenheight(Height), mouse(mouse), window(createwindow)
    {

        NumTilesX = screenwidth / TileDimension;
        NumTilesY = screenheight / TileDimension;

        for (int i = 0; i < NumTilesX * NumTilesY; ++i) {
            TileMap.emplace_back(sf::Vector2f(TileDimension, TileDimension));
        }

        for (int x = 0; x < NumTilesX; ++x) {
            for (int y = 0; y < NumTilesY; ++y) {
                TileMap[x * NumTilesX + y].setPosition(sf::Vector2f(x * TileDimension, y * TileDimension));
                TileMap[x * NumTilesX + y].setFillColor(openTileColour);
                TileMap[x * NumTilesX + y].setOutlineColor(sf::Color::Black);
                TileMap[x * NumTilesX + y].setOutlineThickness(-OutlineThickness);
            }
        }
    }
    bool targetCheck = false;
    bool srcCheck = false;
    sf::Text clockBFS ;
    sf::Text clockA;
    sf::Text clockD;
    bool getCheckSrc();
    void setCheckSrc();
    bool getCheckTarget();
    void setCheckTarget();
    void drawGrid();
    void updateTarget(Location loc);
    void updateSrc(Location loc);
    void setObstacle();
    void setTarget();
    void setSrc();
    void setSrcWithMouse();
    void setTargetWithMouse();
    void setColourVisited(const Location& loc);
    void setColourVisiting(const Location& loc);
    void setColorPath(const Location& loc);
    void setColor_nonOBS(const Location& loc);
    void resetGrid(Grid grid);
    void resetAllGrid(Grid grid);
    void createObsRandom();
    Location getSrcPos();
    Location getTargetPos();
    std::vector<int> getObs();
    std::tuple<int, int> getTileNum();
    int getTileX();
    int getTileY();
    sf::Color getOBSColor();
    bool outofBounds(int x, int y);
    sf::Color getTileColour(const Location& loc);
    int Node(const Location& loc);
    Location getLoc(const int& NODE);
    int getNumOBS();
    bool kiem_tra(int v);
    bool check(int window_x, int window_y);
    bool checkBFS(int window_x, int window_y);
    bool checkDijkstra(int window_x, int window_y);
    bool checkA_Star(int window_x, int window_y);
    bool checkReset(int window_x, int window_y);
    bool checkResetAll(int window_x, int window_y);
    bool checkRandom(int window_x, int window_y);
    bool checkSource(int window_x, int window_y);
    bool checkTarget(int window_x, int  window_y);
    bool checkST();
    int hien_thi_thong_bao();
    int setUpTextSource(sf::Text& text);
    int setUpTextTarget(sf::Text& text);
    int setUpTextBFS(sf::Text& text);
    int setUpTextD(sf::Text& textD);
    int setUpTextA(sf::Text& textA);
    int setUpTextReset(sf::Text& text);
    int setUpTextResetAll(sf::Text& text);
    int setUpTextRandomOBS(sf::Text& text);
    int setUpTextDepcri(sf::Text& text);
    int setUpClockBFS(sf::Text& text, std::string str);
    int setUpClockD(sf::Text& text, std::string str);
    int setUpClockA(sf::Text& text, std::string str);
    void drawText();
    void setUp();
    
  
};

