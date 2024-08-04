#include "graphh.h"
std::vector<std::vector<int>> graph(Grid grid) {
    std::vector<std::vector<int>> adj;
    adj.resize(grid.getTileX() * grid.getTileY());
    int cnt = 0;
    int NumTilesX = grid.getTileX();
    int NumTilesY = grid.getTileY();
    for (int i = 0; i < NumTilesX; i++) {
        for (int j = 0; j < NumTilesY;j++) {
            Location loc1 = { i - 1, j - 1 };
            Location loc2 = { i - 1, j };
            Location loc3 = { i - 1, j + 1 };
            Location loc4 = { i, j - 1 };
            Location loc5 = { i , j + 1 };
            Location loc6 = { i + 1, j - 1 };
            Location loc7 = { i + 1, j };
            Location loc8 = { i + 1, j + 1 };
            if (loc2.posx >= 0) adj[cnt].emplace_back(grid.Node(loc2));
            if (loc4.posy >= 0) adj[cnt].emplace_back(grid.Node(loc4));
            if (loc5.posy < NumTilesY) adj[cnt].emplace_back(grid.Node(loc5));
            if (loc7.posx < NumTilesX) adj[cnt].emplace_back(grid.Node(loc7));
            if (loc1.posx >= 0 && loc1.posy >= 0) adj[cnt].push_back(grid.Node(loc1));
          
            if (loc3.posx >= 0 && loc3.posy < NumTilesY) adj[cnt].push_back(grid.Node(loc3));
           
           
           
            if (loc6.posx < NumTilesX && loc6.posy >= 0) adj[cnt].push_back(grid.Node(loc6));
            if (loc8.posx < NumTilesX && loc8.posy < NumTilesY) adj[cnt].push_back(grid.Node(loc8));


            cnt++;
        }
    }
    return adj;
}


