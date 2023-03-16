#ifndef NORMALMAPPER_H
#define NORMALMAPPER_H

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>

namespace Engine
{
	struct vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 tan;
		glm::vec3 biTan;
	};

	class NormalMapper
	{
	public:
		NormalMapper();
		void calculateTanAndBitan(float* vertexData, int length, unsigned int* indexData, int indLength);
		std::vector<float> getUpdatedVertexData();

	private:
		void unPackVertices();
		void extractVertices(float* vertexData, int length);
		void computeTanAndBitan(unsigned int* indexData, int indLength);
		std::vector<vertex> vertices;
		std::vector<float> updatedVertexData;
	};
}
#endif // NORMALMAPPER_H
