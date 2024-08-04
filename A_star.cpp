#include "A_star.h"
bool visitedA[1000];
int parentsA[10000];
struct CompareFcost {
	bool operator()(const node& a, const node& b) {
		return  a.fCost > b.fCost;
	}
};
double distance(const Location& a, const Location& b) {
	double x = a.posx - b.posx;
	double y = a.posy - b.posy;
	return sqrtf(x * x + y * y);
}
void A_star(const Location& source, const Location& target,
	const std::vector<std::vector<std::pair<int, double>>>& adj,
	Grid& grid, sf::RenderWindow& window) {
	sf::Clock clock;
	std::priority_queue <node, std::vector<node>, CompareFcost > q;

	std::vector<double> gCost(grid.getTileX() * grid.getTileY() +1, INF);
	std::vector<double> hCost(grid.getTileX() * grid.getTileY() +1, INF);
	std::vector<double> fCost(grid.getTileX() * grid.getTileY() +1 , 0);

	int s = grid.Node(source);
	bool isTarget = false;
	double Src_hCost = distance(source, target);
	node srcNode = { s, Src_hCost, 0, Src_hCost };
	gCost[s] = 0;
	hCost[s] = Src_hCost;
	q.push(srcNode);
	visitedA[s] = true;
	while (!q.empty() && !isTarget) {
		node curr = q.top();
		q.pop();
		int current_number_node = curr.number_node;
		double fcost_curr = curr.fCost;
		double gCost_curr = curr.gCost;
		double hCost_curr = curr.hCost;
		grid.setColourVisited(grid.getLoc(current_number_node));
		sf::Time time = clock.getElapsedTime();
		std::stringstream ssA_star;
		ssA_star << time.asMilliseconds();
		grid.setUpClockA(grid.clockA, ssA_star.str());
		grid.drawGrid();
		window.display();

		for (std::pair<int, double> neighbour : adj[current_number_node])
		{
			window.draw(grid.clockA);
			window.display();
			int nodeVisiting = neighbour.first;
			if (grid.getLoc(nodeVisiting) == target)
			{
				visitedA[nodeVisiting] = true;
				parentsA[nodeVisiting] = current_number_node;
				isTarget = true;
				break;
			}
			if (!visitedA[nodeVisiting] && grid.getTileColour(grid.getLoc(nodeVisiting)) != grid.getOBSColor()) {
				if (grid.kiem_tra(nodeVisiting)) {
					double estimatedgCost = gCost_curr + distance(grid.getLoc(nodeVisiting), grid.getLoc(current_number_node));
					if (estimatedgCost <= gCost[nodeVisiting]) {
						visitedA[nodeVisiting] = true;
						parentsA[nodeVisiting] = current_number_node;
						gCost[nodeVisiting] = estimatedgCost;
						hCost[nodeVisiting] = distance(grid.getLoc(nodeVisiting), target);
						fCost[nodeVisiting] = gCost[nodeVisiting] + hCost[nodeVisiting];
						node a = { nodeVisiting ,fCost[nodeVisiting], gCost[nodeVisiting],hCost[nodeVisiting] };

						q.push(a);

						grid.setColourVisiting(grid.getLoc(nodeVisiting));

					}


				}
				else {
					visitedA[nodeVisiting] = true;
					grid.setColourVisiting(grid.getLoc(nodeVisiting));
					grid.setColourVisited(grid.getLoc(nodeVisiting));

				}
			}

		}
	}
	return;

}
void pathA_star(Location source, Location target,
	const std::vector<std::vector<std::pair<int, double>>>& adj,
	Grid& grid, sf::RenderWindow& window) {
	int s = grid.Node(source);
	int t = grid.Node(target);
	memset(visitedA, false, sizeof(visitedA));
	memset(parentsA, 0, sizeof(parentsA));
    A_star(source, target, adj, grid, window);
	if (!visitedA[t]) return;
	else
	{
		std::vector<int> nodePathD;
		while (t != s) {
			t = parentsA[t];
			nodePathD.push_back(t);
		}
		nodePathD.pop_back();
		reverse(nodePathD.begin(), nodePathD.end());
		for (int x : nodePathD) {
			grid.setColorPath(grid.getLoc(x));
		}
	}
}