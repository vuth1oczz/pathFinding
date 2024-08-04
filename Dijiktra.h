#pragma once
#include <SFML/Graphics.hpp>
#include "Location.h"
#include "Grid.h"
#include <vector>
#include <queue>
#include <thread>
#include "graphD.h"
#include <sstream>

void dijiktra(const Location& source, const Location& target, 
	const std::vector<std::vector<std::pair<int, double>>>& adj, 
	 Grid& grid, sf::RenderWindow& window );
void pathDijkstra(  Location source, Location target, const std::vector<std::vector<std::pair<int,double>>>& adj, Grid& grid,
	sf::RenderWindow& window);
