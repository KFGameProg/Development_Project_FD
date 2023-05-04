/**\file   sphere.h */
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Engine
{
	class Sphere
	{
	public:
		Sphere();
		int getVertexSize();
		int getIndexSize();
		float* getVertexData();
		unsigned int* getIndexData();

	private:
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> normals;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
		float xSegment, ySegment;
		float xPos, yPos, zPos;
		bool oddRow = false;

		void calcVertices();
		void calcIndices();
		void build();

	protected:
		const unsigned int xSEGMENTS = 64, ySEGMENTS = 64;
		const float Pi = 3.14159265359f;
		const glm::vec3 sizeVec = glm::vec3(8.f);
	};
}
