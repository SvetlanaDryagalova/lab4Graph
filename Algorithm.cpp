#include "Algorithm.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <random>

std::vector<std::vector<double>> Algorithm::graphDrawing(const std::vector<std::vector<int>>& A, double k, int iterations) {
	std::vector<std::vector<double>> positions(A.size(), std::vector<double>(2));
	std::vector<std::vector<double>> f(A.size(), std::vector<double>(2));

	initializeRandPos(positions);

	for (int iter = 0; iter < iterations; ++iter) {
		computeF(A, positions, f, k);
		updatePos(positions, f);
	}
	return positions;
}

int Algorithm::getImageSize() const {
	return imageSize;
}

void Algorithm::initializeRandPos(std::vector<std::vector<double>>& positions) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, imageSize);

	for (auto& pos : positions) {
		pos[0] = dis(gen);
		pos[1] = dis(gen);
	}
}

void Algorithm::computeF(const std::vector<std::vector<int>>& A, const std::vector<std::vector<double>>& positions, std::vector<std::vector<double>>& forces, double k) {
	double temp = 1.0;

	for (size_t i = 0; i < positions.size(); ++i) {
		for (size_t j = i + 1; j < positions.size(); ++j) {
			double dx = positions[i][0] - positions[j][0];
			double dy = positions[i][1] - positions[j][1];
			double dist = std::sqrt(dx * dx + dy * dy);

			if (A[i][j] == 1) {
				double attrForce = (dist * dist) / k;
				forces[i][0] -= attrForce * (dx / dist);
				forces[i][1] -= attrForce * (dy / dist);
				forces[j][0] += attrForce * (dx / dist);
				forces[j][1] += attrForce * (dy / dist);
			}
			else {
				double repForce = (k * k) / dist;
				forces[i][0] += repForce * (dx / dist);
				forces[i][1] += repForce * (dy / dist);
				forces[j][0] -= repForce * (dx / dist);
				forces[j][1] -= repForce * (dy / dist);
			}
		}
	}
	for (size_t i = 0; i < positions.size(); ++i) {
		double forceNormik = std::sqrt(forces[i][0] * forces[i][0] + forces[i][1] * forces[i][1]);
		if (forceNormik >= 2.0) {
			double appForceNormik = std::min(forceNormik, temp);
			forces[i][0] = forces[i][0] / forceNormik * appForceNormik;
			forces[i][1] = forces[i][1] / forceNormik * appForceNormik;
		}
	}
	if (temp > 1) {
		temp *= 0.97;
	}
	else {
		temp = 1;
	}
}

void Algorithm::updatePos(std::vector<std::vector<double>>& positions, std::vector<std::vector<double>>& forces) {
	for (size_t i = 0; i < positions.size(); ++i) {
		positions[i][0] += forces[i][0];
		positions[i][1] += forces[i][1];
		positions[i][0] = std::max(0.0, std::min(positions[i][0], static_cast<double>(imageSize)));
		positions[i][1] = std::max(0.0, std::min(positions[i][1], static_cast<double>(imageSize)));
	}
}
