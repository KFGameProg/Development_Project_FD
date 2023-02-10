#pragma once

class Cube {
public:
    Cube() {};
    float m_Vertices[8 * 24] = {
        //  <-----Position----->  <-----Normal---->  <-----UV---->
             0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   0.f,   0.f,
             0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   0.f,   0.5f,
            -0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   0.33f, 0.5f,
            -0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   0.33f, 0.f,
                                                     
            -0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   0.33f, 0.5f,
             0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   0.66f, 0.5f,
             0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   0.66f, 0.f,
            -0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   0.33,  0.f,
                                                     
            -0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   1.f,   0.f,
             0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   0.66f, 0.f,
             0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   0.66f, 0.5f,
            -0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.0f,  0.5f,
                                                     
             0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   0.f,   0.5f,
             0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   0.f,   1.0f,
            -0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   0.33f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   0.3f,  0.5f,
                                                     
            -0.5f,  0.5f,  0.5f,  -1.f,  0.f,  0.f,   0.66f, 0.5f,
            -0.5f,  0.5f, -0.5f,  -1.f,  0.f,  0.f,   0.33f, 0.5f,
            -0.5f, -0.5f, -0.5f,  -1.f,  0.f,  0.f,   0.33f, 1.0f,
            -0.5f, -0.5f,  0.5f,  -1.f,  0.f,  0.f,   0.66f, 1.0f,
                                                     
             0.5f, -0.5f, -0.5f,   1.f,  0.f,  0.f,   1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,   1.f,  0.f,  0.f,   1.0f,  0.5f,
             0.5f,  0.5f,  0.5f,   1.f,  0.f,  0.f,   0.66f, 0.5f,
             0.5f, -0.5f,  0.5f,   1.f,  0.f,  0.f,   0.66f, 1.0f
    };

    unsigned int m_Indices[3 * 12] = {
        0,1,2,
        2,3,0,
        4,5,6,
        6,7,4,
        8,9,10,
        10,11,8,
        12,13,14,
        14,15,12,
        16,17,18,
        18,19,16,
        20,21,22,
        22,23,20
    };

    virtual float* getVertices() { return m_Vertices; }
    virtual unsigned int* getIndices() { return m_Indices; }
    virtual int getVertexSize() { return sizeof(m_Vertices); }
    virtual int getIndexSize() { return sizeof(m_Indices); }
protected:
    
};