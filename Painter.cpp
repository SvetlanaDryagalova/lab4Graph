#include "Painter.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <random>

#include "Algorithm.h"


void drawNumber(std::vector<std::vector<int>>& image, int posX, int posY, int number) {
    std::vector<std::vector<std::vector<bool>>> nums = {
        { // 0
            {1, 1, 1, 1},
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1}
        },
        { // 1
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        { // 2
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {1, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 1, 1, 1}
        },
        { // 3
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {1, 1, 1, 1}
        },
        { // 4
            {1, 0, 0, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1}
        },
        { // 5
            {1, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {1, 1, 1, 1}
        },
        { // 6
            {1, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 1, 1, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1}
        },
        { // 7
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1}
        },
        { // 8
            {1, 1, 1, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1}
        },
        { // 9
            {1, 1, 1, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 1},
            {1, 1, 1, 1}
        }
    };

    if (number < 0 || number >= nums.size()) {
        std::cerr << "Invalid number: " << number << std::endl;
        return;
    }

    for (size_t i = 0; i < nums[number].size(); ++i) {
        for (size_t j = 0; j < nums[number][i].size(); ++j) {
            if (nums[number][i][j]) {
                drawPixel(image, posX + 2 * j, posY + 2 * i + 8, 0, 0, 0);
                drawPixel(image, posX + 2 * j + 1, posY + 2 * i + 8, 0, 0, 0);
                drawPixel(image, posX + 2 * j, posY + 2 * i + 9, 0, 0, 0);
                drawPixel(image, posX + 2 * j + 1, posY + 2 * i + 9, 0, 0, 0);
            }
        }
    }
}

void drawGraph(std::vector<std::vector<int>>& A, int numVertices, int iterations) {
	const int vertexRadius = 7; // point thickness
	const int edgeThickness = 3; // line thickness

	Algorithm fo;
	std::vector<std::vector<double>> positions = fo.graphDrawing(A, 30.0, iterations);
	int imageSize = fo.getImageSize();

	GraphPos(positions, imageSize * 0.85);

	std::vector<std::vector<int>> image(imageSize, std::vector<int>(imageSize, 255));

	for (size_t i = 0; i < positions.size(); ++i) {
		int x = static_cast<int>(positions[i][0]);
		int y = static_cast<int>(positions[i][1]);

		if (x >= 0 && x < imageSize && y >= 0 && y < imageSize) {
			drawVertex(image, x, y, vertexRadius, i + 1);
		}
	}

	for (size_t i = 0; i < numVertices; ++i) {
		for (size_t j = i + 1; j < numVertices; ++j) {
			if (A[i][j] == 1) {
				int x1 = static_cast<int>(positions[i][0]);
				int y1 = static_cast<int>(positions[i][1]);
				int x2 = static_cast<int>(positions[j][0]);
				int y2 = static_cast<int>(positions[j][1]);
				drawLine(image, x1, y1, x2, y2, edgeThickness);
			}
		}
	}
	BMP(image);
}


void drawLine(std::vector<std::vector<int>>& image, int x1, int y1, int x2, int y2, int thickness) {
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (true) {
		for (int i = -thickness / 2; i < thickness / 2; ++i) {
			int px = x1 + i;
			int py = y1 + i;
			if (px >= 0 && px < image.size() && py >= 0 && py < image[0].size()) {
				image[px][py] = (0, 0, 0);
			}
		}

		if (x1 == x2 && y1 == y2) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
	}
}




void BMP(const std::vector<std::vector<int>>& image) {
	std::ofstream outputFile("output.bmp", std::ios::binary);
	if (!outputFile) {
		std::cerr << "Error opening the input file." << std::endl;
		return;
	}
	int width = image.size();
	int height = image[0].size();
	int padding = (4 - (width * 3) % 4) % 4;
	int fileSize = 54 + (3 * width + padding) * height;

	
	unsigned char bmpHeader[54] = {
		'B', 'M',         
		fileSize & 0xFF, (fileSize >> 8) & 0xFF, (fileSize >> 16) & 0xFF, (fileSize >> 24) & 0xFF, 
		0, 0, 0, 0,       
		54, 0, 0, 0,      
		40, 0, 0, 0,      
		width & 0xFF, (width >> 8) & 0xFF, (width >> 16) & 0xFF, (width >> 24) & 0xFF, 
		height & 0xFF, (height >> 8) & 0xFF, (height >> 16) & 0xFF, (height >> 24) & 0xFF, 
		1, 0,             
		24, 0,            
		0, 0, 0, 0,      
		0, 0, 0, 0,       
		0, 0, 0, 0,       
		0, 0, 0, 0,       
		0, 0, 0, 0,      
		0, 0, 0, 0      
	};

	outputFile.write(reinterpret_cast<char*>(bmpHeader), 54);

	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			unsigned char color = static_cast<unsigned char>(image[x][y]);
			outputFile.write(reinterpret_cast<char*>(&color), sizeof(color));
			outputFile.write(reinterpret_cast<char*>(&color), sizeof(color));
			outputFile.write(reinterpret_cast<char*>(&color), sizeof(color));
		}
		for (int p = 0; p < padding; ++p) {
			outputFile.put(0);
		}
	}
	outputFile.close();
}


void drawPixel(std::vector<std::vector<int>>& image, int x, int y, int red, int green, int blue) {
    if (x >= 0 && x < image.size() && y >= 0 && y < image[x].size()) {
        int pixelColor = (red << 16) | (green << 8) | blue;
        image[x][y] = pixelColor;
    }
}


void drawVertex(std::vector<std::vector<int>>& image, int x, int y, int radius, int number) {
	for (int i = x - radius; i <= x + radius; ++i) {
		for (int j = y - radius; j <= y + radius; ++j) {
			if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius) {
				if (i >= 0 && i < image.size() && j >= 0 && j < image[0].size()) {
					image[i][j] = (0, 0, 0);
				}
			}
		}
	}

	int labelX = x - 4;
	int labelY = y + 4;
	std::string label = std::to_string(number);
	int digitWidth = 12;
	for (char c : label) {
		int digit = c - '0';
		drawNumber(image, labelX, labelY, digit);
		labelX += digitWidth - 2;
	}
}

void GraphPos(std::vector<std::vector<double>>& positions, int imageSize) {
    double minX = positions[0][0], minY = positions[0][1];
    double maxX = positions[0][0], maxY = positions[0][1];
    for (const auto& vertex : positions) {
        minX = std::min(minX, vertex[0]);
        minY = std::min(minY, vertex[1]);
        maxX = std::max(maxX, vertex[0]);
        maxY = std::max(maxY, vertex[1]);
    }

    double graphWidth = maxX - minX;
    double graphHeight = maxY - minY;

    double scaleX = (graphWidth > 0) ? imageSize / graphWidth : 1.0;
    double scaleY = (graphHeight > 0) ? imageSize / graphHeight : 1.0;


    for (auto& vertex : positions) {
        vertex[0] = (vertex[0] - minX) * scaleX;
        vertex[1] = (vertex[1] - minY) * scaleY;
    }
}
