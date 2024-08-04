#pragma once
#include <SFML/Graphics.hpp>
#include "Location.h"
#include "Grid.h"
#include <vector>
#include <queue>
#include <thread>
#include "graphA.h"
#include "math.h"
#include <sstream>
struct node {
	int number_node;
	double fCost = 0;
	double gCost = INF;
	double hCost = INF;

};
double distance(const Location& currNode, const Location& target);
void A_star(const Location& source, const Location& target,
	const std::vector<std::vector<std::pair<int, double>>>& adj,
	Grid& grid, sf::RenderWindow& window);
void pathA_star(Location source, Location target, 
	const std::vector<std::vector<std::pair<int, double>>>& adj, 
	Grid& grid, sf::RenderWindow& window);