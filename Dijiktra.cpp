#include "Dijiktra.h"
#define INF 10e9
bool Visited[1000];
int Parents[1000];
struct CompareSecond {
	bool operator()(const std::pair<int, double>& a, const std::pair<int, double>& b) {
		return a.second > b.second; 
	}
};

void dijiktra(const Location& source, const Location& target, 
	const std::vector<std::vector<std::pair<int, double>>>& adj, Grid& grid,
	sf::RenderWindow& window) {
	std::priority_queue <std::pair<int, double>, std::vector<std::pair<int, double>>,CompareSecond > q;
	sf::Clock  clock;
	std::vector<double> dis(grid.getTileX() * grid.getTileY() + 1, INF);
	int s = grid.Node(source);
	bool isTarget = false;
	dis[grid.Node(source)] = 0;
	q.push({ s,0 });
	Visited[s] = true;
	
	
	while (!q.empty() && !isTarget) {
		
		std::pair<int, double> top = q.top();
		q.pop();
		int u = top.first;
		double kc = top.second;
		grid.setColourVisited(grid.getLoc(u));
		sf::Time time;
		std::stringstream ssD;
		time = clock.getElapsedTime();
		ssD << time.asMilliseconds();
		grid.setUpClockD(grid.clockD, ssD.str());
		grid.drawGrid();
		window.display();
		if (kc > dis[u]) continue;
		for (std::pair<int, double> it : adj[u])
		{
			window.draw(grid.clockD);
			window.display();
			int v = it.first;
			double w = it.second;
			if (grid.getLoc(v) == target)
			{
				Visited[v] = true;
				Parents[v] = u;
				isTarget = true;
				break;
			}
			if (!Visited[v] && grid.getTileColour(grid.getLoc(v)) != grid.getOBSColor()) {
				if (grid.kiem_tra(v)) {
					if (dis[v] > dis[u] + w) {
						Visited[v] = true;
						dis[v] = dis[u] + w;
						q.push({ v, dis[v] });
						Parents[v] = u;
						grid.setColourVisiting(grid.getLoc(v));
						
					}
				}
				else {
					Visited[v] = true;
					grid.setColourVisiting(grid.getLoc(v));
					grid.setColourVisited(grid.getLoc(v));
					
				}
			}
			
		}
		
	}
	return;
}
void pathDijkstra(  Location source, Location target, const std::vector<std::vector<std::pair<int,double>>>& adj, 
	Grid& grid, sf::RenderWindow& window) {
	int s = grid.Node(source);
	int t = grid.Node(target);
	memset(Visited, false, sizeof(Visited));
	memset(Parents, 0, sizeof(Parents));
	dijiktra(source, target, adj, grid, window);
	
	if (!Visited[t]) return;
	else 
	{
		std::vector<int> nodePathD;
		while (t != s) {
			t = Parents[t];
			nodePathD.push_back(t);
		}
		nodePathD.pop_back();
		reverse(nodePathD.begin(), nodePathD.end());
		for (int x : nodePathD) {
			grid.setColorPath(grid.getLoc(x));
		}
	}
}