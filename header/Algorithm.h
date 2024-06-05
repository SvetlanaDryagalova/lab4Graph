#ifndef ALHORITHM_H
#define ALHORITHM_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <random>

class Algorithm {
public:
    std::vector<std::vector<double>> graphDrawing(const std::vector<std::vector<int>>& A, double k, int iterations);
    int getImageSize() const;
private:
    const int imageSize = 1200;
    void initializeRandPos(std::vector<std::vector<double>>& positions);
    void computeF(const std::vector<std::vector<int>>& A, const std::vector<std::vector<double>>& positions, std::vector<std::vector<double>>& forces, double k);
    void updatePos(std::vector<std::vector<double>>& positions, std::vector<std::vector<double>>& forces);
};
#endif
