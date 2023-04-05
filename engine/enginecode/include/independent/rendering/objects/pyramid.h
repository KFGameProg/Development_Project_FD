/** \file   pyramid.h */
#pragma once

class Pyramid {
public:
    Pyramid() {};
    float m_Vertices[8 * 16] = {
        //	<-----Position----->  <-----------Normal----------->  <----UV---->
            -0.5f, -0.5f, -0.5f,   0.f,      -1.f,      0.f,       0.f,  1.f,   // Base
             0.5f, -0.5f, -0.5f,   0.f,      -1.f,      0.f,       1.f,  1.f,
             0.5f, -0.5f,  0.5f,   0.f,      -1.f,      0.f,       1.f,  0.f,
            -0.5f, -0.5f,  0.5f,   0.f,      -1.f,      0.f,       0.f,  0.f,

            -0.5f, -0.5f, -0.5f,  -0.8944f,   0.4472f,  0.f,       0.f,  1.f,   // Left
            -0.5f, -0.5f,  0.5f,  -0.8944f,   0.4472f,  0.f,       0.f,  0.f,
             0.0f,  0.5f,  0.0f,  -0.8944f,   0.4472f,  0.f,       1.f,  0.f,

            -0.5f, -0.5f,  0.5f,   0.f,       0.4472f,  0.8944f,   0.f,  1.f,   // Front
             0.5f, -0.5f,  0.5f,   0.f,       0.4472f,  0.8944f,   0.f,  0.f,
             0.0f,  0.5f,  0.0f,   0.f,       0.4472f,  0.8944f,   1.f,  0.f,

             0.5f, -0.5f,  0.5f,   0.8944f,   0.4472f,  0.f,       0.f,  1.f,   // Right
             0.5f, -0.5f, -0.5f,   0.8944f,   0.4472f,  0.f,       0.f,  0.f,
             0.0f,  0.5f,  0.0f,   0.8944f,   0.4472f,  0.f,       1.f,  0.f,

             0.5f, -0.5f, -0.5f,   0.f,       0.4472f, -0.8944f,   0.f,  1.f,   // Back
            -0.5f, -0.5f, -0.5f,   0.f,       0.4472f, -0.8944f,   0.f,  0.f,
             0.0f,  0.5f,  0.0f,   0.f,       0.4472f, -0.8944f,   1.f,  0.f,
    };

    unsigned int m_Indices[3 * 6] = {
            0,1,2,
            2,3,0,
            4,5,6,
            7,8,9,
            10,11,12,
            13,14,15
    };

    virtual float* getVertices() { return m_Vertices; }
    virtual unsigned int* getIndices() { return m_Indices; }
    virtual int getVertexSize() { return sizeof(m_Vertices); }
    virtual int getIndexSize() { return sizeof(m_Indices); }
};