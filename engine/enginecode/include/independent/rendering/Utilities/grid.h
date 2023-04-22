/** \file   grid.h */
#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Grid
{
public:
	// Constructers 
	Grid(int widthIn, int heightIn, int stepSizeIn);
	Grid();
	int getSize();
	float* getData();

private:
	std::vector<float> m_vertices;
	unsigned int m_VAO, m_VBO;
	// No. of cells 
	int m_cellSize = 1;  // Cell size in grid and default values
	int m_width = 30;     // Wide
	int m_height = 30;    // High
	
	// Calculate vertex positions and UV values
	void makeVertices();
	void makeVertex(int x, int z);
};
#endif
