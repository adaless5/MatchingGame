#ifndef __Ball_H__
#define __Ball_H__

#include "GameObject.h"

class Game;

class Ball : public GameObject
{
    const float BALL_SPEED_WHEN_HIT       = 120.0f; // Units per second
    const float BALL_FRICTION             = 100.0f; // Units per second

protected:
    float m_Speed;
    float m_Angle;

public:
    Ball(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position);
    ~Ball();

    virtual void Update(float deltaTime);
    
    virtual void OnCollision(GameObject* pOtherGameObject);
};

#endif //__Ball_H__
