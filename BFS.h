#pragma once
#include <SFML/Graphics.hpp>
#include "Location.h"
#include <vector>
#include "Grid.h"
#include "graphh.h"
#include <queue>
#include <thread>
//bool visited[1000];
//int parents[1000];
void BFS(const Location& srcPos, const Location& targetPos, const std::vector<int> obstacles,
    const std::vector<std::vector<int>>& adj,
    Grid& grid, sf::RenderWindow& window);
void pathBFS(Location source, Location target, const std::vector<std::vector<int>>& adj, Grid& grid,
    sf::RenderWindow& window);

