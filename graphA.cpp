#include "graphA.h"
std::vector<std::vector<std::pair<int, double>>> graphA(Grid grid) {
	std::vector < std::vector<std::pair<int, double>>> adj;
	adj.resize(grid.getTileX() * grid.getTileY());
	int cnt = 0;
	for (int i = 0; i < grid.getTileX(); i++) {
		for (int j = 0; j < grid.getTileY();j++) {
			Location loc1 = { i - 1, j - 1 };
			Location loc2 = { i - 1, j };
			Location loc3 = { i - 1, j + 1 };
			Location loc4 = { i, j - 1 };
			Location loc5 = { i , j + 1 };
			Location loc6 = { i + 1, j - 1 };
			Location loc7 = { i + 1, j };
			Location loc8 = { i + 1, j + 1 };
			if (loc2.posx >= 0) adj[cnt].push_back({ grid.Node(loc2), 1 });
			if (loc4.posy >= 0) adj[cnt].push_back({ grid.Node(loc4), 1 });
			if (loc5.posy < grid.getTileY()) adj[cnt].push_back({ grid.Node(loc5),1 });
			if (loc7.posx < grid.getTileX()) adj[cnt].push_back({ grid.Node(loc7), 1 });
			if (loc1.posx >= 0 && loc1.posy >= 0) adj[cnt].push_back({ grid.Node(loc1), 1.41});
			
			if (loc3.posx >= 0 && loc3.posy < grid.getTileY()) adj[cnt].push_back({ grid.Node(loc3),1.41 });
			if (loc6.posx < grid.getTileX() && loc6.posy >= 0) adj[cnt].push_back({ grid.Node(loc6), 1.41 });
			if (loc8.posx < grid.getTileX() && loc8.posy < grid.getTileY()) adj[cnt].push_back({ grid.Node(loc8), 1.41 });
			cnt++;
		}
	}
	return adj;
}