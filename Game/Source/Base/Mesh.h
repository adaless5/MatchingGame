#ifndef __Mesh_H__
#define __Mesh_H__

#include "VertexFormat.h"

class fw::ShaderProgram;
class Camera;

class Mesh
{
protected:
    GLuint m_VBO;
    unsigned int m_NumVerts;
    GLenum m_PrimitiveType;
    fw::AABB m_BoundingBox;

public:
    Mesh();
    ~Mesh();

    void Init(VertexFormat* pVerts, unsigned int numVerts, GLenum primitiveType);
    void Draw(Camera* pCamera, fw::ShaderProgram* pShader, fw::vec2 pos, GLuint textureID, fw::vec2 uvOffset = fw::vec2(0.0f, 0.0f), fw::vec2 uvScale = fw::vec2(1.0f, 1.0f));

    void GenerateTriangle();
    void GenerateCircle();
	void GenerateCursor(); 
	void GenerateCard(); 

    fw::AABB GetBoundingBox() { return m_BoundingBox; }
};

#endif //__Mesh_H__
