#include "Grid.h"
void Grid::drawGrid() 
{
        for (auto tile : TileMap) {
            window.draw(tile);
        }
    }
void Grid::updateTarget(Location loc) {
        targetPos.posx = loc.posx;
        targetPos.posy = loc.posy;
        targetCheck = true;
    }
void Grid::updateSrc(Location loc) {
        srcPos.posx = loc.posx;
        srcPos.posy = loc.posy;
        srcCheck = true;
    }
void Grid::setCheckSrc() {
    srcPoscheck = false;
}
void Grid::setCheckTarget() {
    targetPoscheck = false;
}
bool Grid::getCheckSrc() {
    return srcPoscheck;
}
bool Grid::getCheckTarget() {
    return targetPoscheck;
}
void Grid::setObstacle() {
        int mouseposx = mouse.getPosition(window).x;
        int mouseposy = mouse.getPosition(window).y;
    
        int x = (int)(mouseposx / TileDimension);
        int y = (int)(mouseposy / TileDimension);
        Location mouseLoc = { x,y };
        int nodeOBS = x * NumTilesX + y;
        if (outofBounds(x, y)) return;
        if (getTileColour(mouseLoc) == targetTileColour || getTileColour(mouseLoc) == srcTileColour) return;
        TileMap[x * NumTilesX + y].setFillColor(obstacleTileColour);
       // TileMap[x * NumTilesX + y].setOutlineColor(sf::Color::White);
        Obstacles.push_back(nodeOBS);
                
    }
void Grid::setTarget() {
    int mouseposx = mouse.getPosition(window).x;
    int mouseposy = mouse.getPosition(window).y;

    int x = (int)(mouseposx / TileDimension);
    int y = (int)(mouseposy / TileDimension);
    if (outofBounds(x, y)) return;
    Location newTarget = { x,y };
    Location prevTarget = this->targetPos;
    TileMap[prevTarget.posx * NumTilesY + prevTarget.posy].setFillColor(openTileColour);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        TileMap[x * NumTilesY + y].setFillColor(targetTileColour);
        updateTarget(newTarget);
    }

}
void Grid::setSrc() {
    int mouseposx = mouse.getPosition(window).x;
    int mouseposy = mouse.getPosition(window).y;

    int x = (int)(mouseposx / TileDimension);
    int y = (int)(mouseposy / TileDimension);
    Location newSrc = { x,y };
    Location prevSrc = this->srcPos;
    TileMap[prevSrc.posx * NumTilesX + prevSrc.posy].setFillColor(openTileColour);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        TileMap[x * NumTilesX + y].setFillColor(srcTileColour);
        updateSrc(newSrc);
       
    }

}

void Grid::setTargetWithMouse() {
    int mouseposx = mouse.getPosition(window).x;
    int mouseposy = mouse.getPosition(window).y;

    int x = (int)(mouseposx / TileDimension);
    int y = (int)(mouseposy / TileDimension);
    if (outofBounds(x, y)) return;
    Location newTarget = { x,y };
    Location prevTarget = this->targetPos;
    TileMap[prevTarget.posx * NumTilesY + prevTarget.posy].setFillColor(openTileColour);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        TileMap[x * NumTilesY + y].setFillColor(targetTileColour);
        updateTarget(newTarget);
        targetPoscheck = true;
    }

}
void Grid::setSrcWithMouse() {
    int mouseposx = mouse.getPosition(window).x;
    int mouseposy = mouse.getPosition(window).y;

    int x = (int)(mouseposx / TileDimension);
    int y = (int)(mouseposy / TileDimension);
    Location newSrc = { x,y };
    Location prevSrc = this->srcPos;
    TileMap[prevSrc.posx * NumTilesX + prevSrc.posy].setFillColor(openTileColour);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        TileMap[x * NumTilesX + y].setFillColor(srcTileColour);
        updateSrc(newSrc);
        srcPoscheck = true;
    }

}
void Grid::setColourVisited(const Location& loc) {
    if (loc == srcPos || loc == targetPos) return;
    TileMap[loc.posx * NumTilesX + loc.posy].setFillColor(visitedTileColour);
}
void Grid::setColourVisiting(const Location& loc) {
    if (loc == srcPos || loc == targetPos) return;
    TileMap[loc.posx * NumTilesX + loc.posy].setFillColor(visitngTileColour);
}
void Grid::setColorPath(const Location& loc) {
    TileMap[loc.posx * NumTilesX + loc.posy].setFillColor(pathColor);
}
void Grid::setColor_nonOBS(const Location& loc) {
    TileMap[loc.posx * NumTilesX + loc.posy].setFillColor(sf::Color::Red);
}
Location Grid::getSrcPos() {
    return srcPos;
}
Location Grid::getTargetPos() {
    return targetPos;
}
std::vector<int> Grid::getObs() {
    return Obstacles;
}
std::tuple<int, int> Grid::getTileNum() {
    return std::make_tuple(NumTilesX, NumTilesY);
}
int Grid::getTileX() {
    return NumTilesX;
}
int Grid::getTileY() {
    return NumTilesY;
}
sf::Color Grid::getOBSColor() {
    return obstacleTileColour;
}
bool Grid::outofBounds(int x, int y)
{
    if (x < 0 || y < 0 || x >= screenwidth || y >= screenheight) {
        return true;
    }
    return false;
}
sf::Color Grid::getTileColour(const Location& loc) {
    return TileMap[loc.posx * NumTilesX + loc.posy].getFillColor();

}
int Grid::Node(const Location& loc) {
    return loc.posx * NumTilesX + loc.posy;
}
Location Grid::getLoc(const int& NODE) {
    Location loc;
    loc.posx = NODE / NumTilesX;
    loc.posy = NODE % NumTilesX;
    return loc;
}

int Grid::getNumOBS() {
    return numOBS;
}
bool Grid::kiem_tra(int v) {
    if (getTileColour(getLoc(v)) == srcTileColour) return 1;
    if (getTileColour(getLoc(v)) == targetTileColour) return 1;
    if ((0 <= v && v <= 27) || (756 <= v && v <= 784)) return 1;
    else  if ((getTileColour(getLoc(v - 28)) == getOBSColor() &&
        getTileColour(getLoc(v + 1)) == getOBSColor() ) ||
        (getTileColour(getLoc(v + 28)) == getOBSColor() &&
            getTileColour(getLoc(v - 1)) == getOBSColor()) ||
        (getTileColour(getLoc(v - 28)) == getOBSColor() &&
            getTileColour(getLoc(v - 1)) == getOBSColor()) ||
        (getTileColour(getLoc(v + 28)) == getOBSColor() &&
            getTileColour(getLoc(v + 1)) == getOBSColor())
        ) return 0;
    else return 1;

}
void Grid::resetGrid(Grid grid){
    for (auto& tile : TileMap)
    {
        if (
            tile.getFillColor() == grid.pathColor ||
            tile.getFillColor() == grid.visitedTileColour || 
            
            tile.getFillColor() == grid.visitngTileColour 
             )
            {
                    tile.setFillColor(sf::Color::White);
                    Obstacles.clear();
        }
    }
   
}
void Grid::resetAllGrid(Grid grid) {
    for (auto& tile : TileMap)
    {
        if (tile.getFillColor() == grid.obstacleTileColour || 
            tile.getFillColor() == grid.targetTileColour || 
            tile.getFillColor() == grid.pathColor ||
            tile.getFillColor() == grid.visitedTileColour ||
            tile.getFillColor() == grid.srcTileColour ||
            tile.getFillColor() == grid.visitngTileColour
            )
        {
            tile.setFillColor(sf::Color::White);
            Obstacles.clear();
        }
    }
    srcCheck = false;
    targetCheck = false;

}
void Grid::createObsRandom() {
    int b = 100;
    int a = 90;
    int numberObs = rand() % (b - a + 1) +a ;
    std::vector<int> randomOBS;
    for (int i = 0; i < numberObs; i++) {
        int number = rand() % 784 + 1;
        Obstacles.push_back(number);
        randomOBS.push_back(number);
    }
    for (int i : randomOBS) {
        TileMap[i].setFillColor(getOBSColor());
    }
 
}
bool Grid::check(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;
    return window_x <= x && x <= window_x +520 && window_y <= y && y <=window_y+ 900;
}
bool Grid::checkBFS(int window_x, int window_y) {
        int x = mouse.getPosition().x;
        int y = mouse.getPosition().y;
        if (window_x +460 <= x && x <= window_x + 510 && window_y + 260  <= y && y <= window_y + 290)  return 1;
        else return 0;
}
bool Grid::checkA_Star(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;

    if (window_x +750 <= x && x <= window_x +850 && window_y+260 <= y && y <= window_y + 290) return 1;
    else return 0;
}
bool Grid::checkDijkstra(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;
    
    if (window_x +600 <= x && x <= window_x +690 && window_y +260 <= y && y <= window_y+290) return 1;
    else return 0;
}
bool Grid::checkReset(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;

    if (window_x + 460 <= x && x <= window_x + 525 && window_y + 330 <= y && y <= window_y + 360) return 1;
    else return 0;
}
bool Grid::checkResetAll(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;

    if (window_x + 600 <= x && x <= window_x + 700 && window_y + 330 <= y && y <= window_y + 360) return 1;
    else return 0;
}
bool Grid::checkRandom(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;

    if (window_x + 750 <= x && x <= window_x + 850 && window_y + 330 <= y && y <= window_y + 360) return 1;
    else return 0;
}
bool Grid::checkSource(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;
    if ((x - 560 - window_x) * (x - 560 - window_x ) + (y - 400 - window_y ) * (y - 400 - window_y) <= 400) return 1;
    else return 0;
}
bool Grid::checkTarget(int window_x, int window_y) {
    int x = mouse.getPosition().x;
    int y = mouse.getPosition().y;
    if ((x - 735 - window_x) * (x - 735 -window_x) + (y - 400 - window_y) * (y - 400 - window_y) <= 400) return 1;
    else return 0;
}
int Grid::setUpTextBFS(sf::Text &textBFS) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    textBFS.setFont(font);
    textBFS.setString("BFS");
    textBFS.setPosition(sf::Vector2f(460, 230));
    textBFS.setFillColor(sf::Color(238, 238, 228));
    textBFS.setOutlineColor(sf::Color::Black);
    textBFS.setOutlineThickness(2);
    textBFS.setCharacterSize(25);
}
int Grid::setUpTextD(sf::Text& textD) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    textD.setFont(font);
    textD.setString("Dijkstra");
    textD.setPosition(sf::Vector2f(610 , 230));
    textD.setFillColor(sf::Color(238, 238, 228));
    textD.setOutlineColor(sf::Color::Black);
    textD.setOutlineThickness(2);
    textD.setCharacterSize(25);
}
int Grid::setUpTextA(sf::Text& textA) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    textA.setFont(font);
    textA.setString("A_Star");
    textA.setPosition(sf::Vector2f(760, 230));
    textA.setFillColor(sf::Color(238, 238, 228));
    textA.setOutlineColor(sf::Color::Black);
    textA.setOutlineThickness(2);
    textA.setCharacterSize(25);
}
int Grid::setUpTextReset(sf::Text& textReset) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    textReset.setFont(font);
    textReset.setString("Reset");
    textReset.setPosition(sf::Vector2f(460, 300));
    textReset.setFillColor(sf::Color(238, 238, 228));
    textReset.setOutlineColor(sf::Color::Black);
    textReset.setOutlineThickness(2);
    textReset.setCharacterSize(25);
}
int Grid::setUpTextResetAll(sf::Text& textResetAll) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    textResetAll.setFont(font);
    textResetAll.setString("Reset All");
    textResetAll.setPosition(sf::Vector2f(610, 300));
    textResetAll.setFillColor(sf::Color(238, 238, 228));
    textResetAll.setOutlineColor(sf::Color::Black);
    textResetAll.setOutlineThickness(2);
    textResetAll.setCharacterSize(25);
}
int Grid::setUpTextRandomOBS(sf::Text& text) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString("Random OBS");
    text.setPosition(sf::Vector2f(760, 300));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(25);
}

int Grid::setUpTextTarget(sf::Text& text) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString("S");
    text.setPosition(sf::Vector2f(550, 355));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(25);
}

int Grid::setUpTextSource(sf::Text& text) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString("T");
    text.setPosition(sf::Vector2f(725, 355));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(25);
}
int Grid::setUpTextDepcri(sf::Text &text) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString("Depcription: \n Right- click on button S then left-click on the map where you want to set up Source\n\n Right - click on button T then left - click on the map where you want to set up Target\n\n Right-click on button BFS to run BFS Algorithm\n\n Right-click on button Dijkstra to run Dijkstra Algorithm\n\n   Right-click on button A_star to run A_star Algorithm ");
    text.setPosition(sf::Vector2f(430, 2));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(12);

}
int Grid::setUpClockBFS(sf::Text& text, std::string strClock) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString(strClock + " ms");
    text.setPosition(sf::Vector2f(460, 210));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(15);
}
int Grid::setUpClockD(sf::Text& text, std::string strClock) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString(strClock + " ms");
    text.setPosition(sf::Vector2f(610, 210));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(15);
}
int Grid::setUpClockA(sf::Text& text, std::string strClock) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString(strClock + " ms");
    text.setPosition(sf::Vector2f(760, 210));
    text.setFillColor(sf::Color(238, 238, 228));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(15);
}
void Grid::drawText() {
    
    window.draw(textDepcri);
    window.draw(textSource);
    window.draw(textTarget);
    window.draw(textRandom);
    window.draw(textReset);
    window.draw(textResetALL);
    window.draw(textA);
    window.draw(textD);
    window.draw(textBFS);
}
void Grid::setUp() {
    setUpTextBFS(textBFS);
    setUpTextD(textD);
    setUpTextA(textA);
    setUpTextReset(textReset);
    setUpTextResetAll(textResetALL);
    setUpTextRandomOBS(textRandom);
    setUpTextSource(textSource);
    setUpTextTarget(textTarget);
    setUpTextDepcri(textDepcri);
}
bool Grid::checkST() {
    if (targetCheck && srcCheck) return 1;
      else return 0;
}
int Grid::hien_thi_thong_bao() {
    sf::RenderWindow window_annouce(sf::VideoMode(450, 100), "Warning", sf::Style::Close | sf::Style::Resize);
    window_annouce.setPosition(sf::Vector2i(350, 210));
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        return -1;
    }
    text.setFont(font);
    text.setString("Error:: target not found, source not found");
    text.setPosition(sf::Vector2f(80, 40));
    text.setFillColor(sf::Color::Red);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(15);
    while (window_annouce.isOpen()) {
        sf::Event event;
        while (window_annouce.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_annouce.close();
        }
        window_annouce.draw(text);
        window_annouce.display();
    }
}
 
