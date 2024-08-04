#include "BFS.h"
#include <iostream>
#include <conio.h>
#include <sstream>
bool visited[1000];
int parents[1000];
void BFS(const Location& srcPos, const Location& targetPos,
    const std::vector<std::vector<int>>& adj,
    Grid& grid, sf::RenderWindow& window) {
    sf::Clock clock;
    std::queue<int> q;
    int S = grid.Node(srcPos);
    int T = grid.Node(targetPos);
    bool isTargetReached = false;
    q.push(S);
    visited[S] = true;
    
    while (!q.empty() && !isTargetReached) {
        sf::Time time = clock.getElapsedTime();
        int cur = q.front();
       
        std::stringstream ssWindow;
        ssWindow << time.asMilliseconds();
        grid.setUpClockBFS(grid.clockBFS, ssWindow.str());
        grid.drawGrid();
        window.display();
        if (grid.kiem_tra(cur)) {
            Location curLoc = grid.getLoc(cur);
            q.pop();
            grid.setColourVisited(curLoc);
           
            if (curLoc == targetPos) {
                isTargetReached = true;
                continue;
            }
            for (int v : adj[cur])
            {
                window.draw(grid.clockBFS);
                window.display();
                if (!visited[v] && grid.getTileColour(grid.getLoc(v)) != grid.getOBSColor())
                {
                    q.push(v);
                    parents[v] = cur;
                    visited[v] = true;
                    grid.setColourVisiting(grid.getLoc(v));
                }
               
            }
           
        }
        else {
            q.pop();
            visited[cur] = true;
            grid.setColourVisiting(grid.getLoc(cur));
            grid.setColourVisited(grid.getLoc(cur));
        }
        
    }
    return;

}
void pathBFS(Location source, Location target, const std::vector<std::vector<int>>& adj, Grid& grid,
    sf::RenderWindow& window) {
    int s = grid.Node(source);
    int t = grid.Node(target);
    memset(visited, false, sizeof(visited));
    memset(parents, 0, sizeof(parents));
    BFS(source, target, adj, grid, window);
    if (!visited[t]) return;
    else {
        std::vector<int> nodePath;
        while (t != s) {
            t = parents[t];
            nodePath.push_back(t);
        }
        nodePath.pop_back();
        reverse(nodePath.begin(), nodePath.end());
        for (int x : nodePath) {
            grid.setColorPath(grid.getLoc(x));
           
        }
    }
}