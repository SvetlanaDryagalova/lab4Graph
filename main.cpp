//Дрягалова Светлана
//Б18

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <random>
#include "Painter.h"
#include "Algorithm.h"

int main() {
	std::ifstream inputFile("input.txt");
	int cVertices, cEdges;
	inputFile >> cVertices >> cEdges;

	std::vector<std::vector<int>> aoMatrix(cVertices, std::vector<int>(cVertices, 0));
	for (int i = 0; i < cEdges; ++i) {
		int u, v;
		inputFile >> u >> v;

		aoMatrix[u][v] = 1;
		aoMatrix[v][u] = 1;
	}
	drawGraph(aoMatrix, cVertices, 1000);
	return 0;
}
