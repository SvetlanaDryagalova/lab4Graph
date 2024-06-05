#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <random>

    void drawNumber(std::vector<std::vector<int>>& image, int posX, int posY, int number);
    
    void drawGraph(std::vector<std::vector<int>>& A, int numVertices, int iterations);
    
    void drawLine(std::vector<std::vector<int>>& image, int x1, int y1, int x2, int y2, int thickness);
    
    void drawVertex(std::vector<std::vector<int>>& image, int x, int y, int radius, int number);
    
    void BMP(const std::vector<std::vector<int>>& image);
    
    void drawPixel(std::vector<std::vector<int>>& image, int x, int y, int red, int green, int blue);
    void GraphPos(std::vector<std::vector<double>>& positions, int imageSize);
    
