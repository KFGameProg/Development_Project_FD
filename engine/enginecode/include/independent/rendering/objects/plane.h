#pragma once

class Plane {
public:
	Plane() {};
	float m_Vertices[8 * 4] = {
	//  <---Position----> <----Normal---> <---UV--->
		-5.f,  0.f, -5.f,  0.f, 1.f, 0.f,  0.f, 0.f,
		 5.f,  0.f, -5.f,  0.f, 1.f, 0.f,  0.f, 1.f,
		 5.f,  0.f,  5.f,  0.f, 1.f, 0.f,  1.f, 1.f,
		-5.f,  0.f,  5.f,  0.f, 1.f, 0.f,  1.f, 0.f
	};

	unsigned int m_Indices[3 * 2] = {
		3,2,1,
		3,1,0
	};

	virtual float* getVertices() { return m_Vertices; }
	virtual unsigned int* getIndices() { return m_Indices; }
	virtual int getVertexSize() { return sizeof(m_Vertices); }
	virtual int getIndexSize() { return sizeof(m_Indices); }

};