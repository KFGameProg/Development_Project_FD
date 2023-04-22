#include "engine_pch.h"
#include <glad/glad.h>
#include "include/independent/rendering/Utilities/grid.h"

// Constructors
Grid::Grid()
{
	makeVertices();
}

Grid::Grid(int widthIn, int heightIn, int stepSizeIn) :
   m_cellSize(stepSizeIn),
   m_width(widthIn),
   m_height(heightIn)
{
	makeVertices();
}

int Grid::getSize()
{
	return m_vertices.size();
}

float* Grid::getData()
{
	return m_vertices.data();
}


void Grid::makeVertices()
{
	/* triangle a b c
		   b
		   | \
		   a _ c


		 triangle d f e
		   f _ e
			 \ |
			   d

		 c == d
		 b == f
		 Duplicate vertices, you should add indexing

		a = (x,y,z)
		b = (x, y+1)
		c = (x+1,y)

		d = (x+1,y)
		e = (x, y+1)
		f = (x+1,y+1)

		 each vertex a, b,c, etc. will have 5 data:
		 x y z u v
		  */

	for (int z = 0; z < m_height - 1; z++) {
		float  offSetZ = z * m_cellSize;
		for (int x = 0; x < m_width - 1; x++) {
			float offSetX = x * m_cellSize;
			makeVertex(offSetX, offSetZ);  // a
			makeVertex(offSetX, offSetZ + m_cellSize);  // b
			makeVertex(offSetX + m_cellSize, offSetZ);   // c
			makeVertex(offSetX + m_cellSize, offSetZ);  //d
			makeVertex(offSetX, offSetZ + m_cellSize);  //e
			makeVertex(offSetX + m_cellSize, offSetZ + m_cellSize);  //f
		}
	}
}

void Grid::makeVertex(int x, int z)
{
	// x y z positions
	m_vertices.push_back((float)x); //xPos
	m_vertices.push_back(0.0f); //yPos - always 0 for now. Going to calculate this on GPU - could change to calclaute it here.
	m_vertices.push_back((float)z); //zPos

	// + TexCoords
	m_vertices.push_back((float)x / (m_width * m_cellSize));
	m_vertices.push_back((float)z / (m_height * m_cellSize));
}

