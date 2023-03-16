#include <engine_pch.h>
#include <glad/glad.h>
#include "include/independent/rendering/normalMapper.h"

namespace Engine
{
	NormalMapper::NormalMapper()
	{

	}

	void NormalMapper::calculateTanAndBitan(float* vertexData, int length, unsigned int* indexData, int indLength)
	{
		extractVertices(vertexData, length);
		computeTanAndBitan(indexData, indLength);
		unPackVertices();
	}

	std::vector<float> NormalMapper::getUpdatedVertexData()
	{
		return updatedVertexData;
	}

	void NormalMapper::unPackVertices()
	{
		for (vertex v : vertices) {

			int stride = 14;

			float vertexData[] = {
				v.pos.x, v.pos.y, v.pos.z,
				v.normal.x, v.normal.y, v.normal.z,
				v.uv.x, v.uv.y,
				v.tan.x, v.tan.y, v.tan.z,
				v.biTan.x, v.biTan.y, v.biTan.z,
			};

			for (int i = 0; i < stride; i++) {
				updatedVertexData.push_back(vertexData[i]);
			}
		}
	}

	void NormalMapper::extractVertices(float* vertexData, int length)
	{
		vertex v;
		for (int i = 0; i < length; i = i + 8)
		{
			v.pos = glm::vec3(vertexData[i], vertexData[i + 1], vertexData[i + 2]);
			v.normal = glm::vec3(vertexData[i + 3], vertexData[i + 4], vertexData[i + 5]);
			v.uv = glm::vec2(vertexData[i + 6], vertexData[i + 7]);
			v.tan = glm::vec3(1.0f);
			v.biTan = glm::vec3(1.0f);

			vertices.push_back(v);
		}
	}

	void NormalMapper::computeTanAndBitan(unsigned int* indexData, int indLength)
	{
		for (int i = 0; i < indLength; i = i + 3)
		{
			vertex& a = vertices.at(indexData[i]);
			vertex& b = vertices.at(indexData[i + 1]);
			vertex& c = vertices.at(indexData[i + 2]);

			glm::vec3 deltaPos1 = b.pos - a.pos;
			glm::vec3 deltaPos2 = c.pos - a.pos;

			glm::vec2 deltaUV1 = b.uv - a.uv;
			glm::vec2 deltaUV2 = c.uv - a.uv;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

			glm::vec3 thisTangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
			glm::vec3 thisBiTangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

			a.tan = a.tan + thisTangent;
			a.biTan = a.biTan + thisBiTangent;

			b.tan = b.tan + thisTangent;
			b.biTan = b.biTan + thisBiTangent;

			c.tan = c.tan + thisTangent;
			c.biTan = c.biTan + thisBiTangent;

			for (vertex& v : vertices) {
				v.tan = glm::normalize(v.tan);
				v.biTan = glm::normalize(v.biTan);
			}
		}
	}
}
