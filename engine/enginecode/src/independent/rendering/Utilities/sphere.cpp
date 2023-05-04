#include "engine_pch.h"
#include <glad/glad.h>
#include "independent/rendering/objects/sphere.h"

namespace Engine
{
	// Construct and build sphere object  
	Sphere::Sphere()
	{
		calcVertices();
		calcIndices();
		build();
	}

	void Sphere::calcVertices()
	{
		for (unsigned int x = 0; x <= xSEGMENTS; ++x)
		{
			for (unsigned int y = 0; y <= ySEGMENTS; ++y)
			{
				xSegment = (float)x / (float)xSEGMENTS;
				ySegment = (float)y / (float)ySEGMENTS;
				xPos = std::cos(xSegment * 2.f * Pi) * std::sin(ySegment * Pi);
				yPos = std::cos(ySegment * Pi);
				zPos = std::sin(xSegment * 2.f * Pi) * std::sin(ySegment * Pi);
				
				positions.push_back(glm::vec3(xPos, yPos, zPos)/ sizeVec);
				uv.push_back(glm::vec2(xSegment, ySegment));
				normals.push_back(glm::vec3(xPos, yPos, zPos) / sizeVec);
			}
		}
	}

	void Sphere::calcIndices()
	{
		for (unsigned int y = 0; y < ySEGMENTS; ++y)
		{
			if (!oddRow) // even rows: y == 0, y == 2; and so on
			{
				for (unsigned int x = 0; x <= xSEGMENTS; ++x)
				{
					m_indices.push_back(y * (xSEGMENTS + 1) + x);
					m_indices.push_back((y + 1) * (xSEGMENTS + 1) + x);
				}
			}
			else
			{
				for (int x = xSEGMENTS; x >= 0; --x)
				{
					m_indices.push_back((y + 1) * (xSEGMENTS + 1) + x);
					m_indices.push_back(y * (xSEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}
	}

	void Sphere::build()
	{
		for (unsigned int i = 0; i < positions.size(); ++i)
		{
			m_vertices.push_back(positions[i].x);
			m_vertices.push_back(positions[i].y);
			m_vertices.push_back(positions[i].z);
			if (normals.size() > 0)
			{
				m_vertices.push_back(normals[i].x);
				m_vertices.push_back(normals[i].y);
				m_vertices.push_back(normals[i].z);
			}
			if (uv.size() > 0)
			{
				m_vertices.push_back(uv[i].x);
				m_vertices.push_back(uv[i].y);
			}
		}
	}

	// Return object data
	int Sphere::getVertexSize()
	{
		return m_vertices.size();
	}

	int Sphere::getIndexSize()
	{
		return static_cast<unsigned int>(m_indices.size());
	}

	float* Sphere::getVertexData()
	{
		return m_vertices.data();
	}

	unsigned int* Sphere::getIndexData()
	{
		return m_indices.data();
	}
}
