#ifndef __Camera_H__
#define __Camera_H__

#include "GameObject.h"

class Game;

class Camera : public GameObject
{
protected:
    fw::vec2 m_ProjectionScale;

public:
    Camera(Game* pGame, fw::vec2 position, fw::vec2 projectionScale);
    ~Camera();

    fw::vec2 GetProjectionScale() { return m_ProjectionScale; }
};

#endif //__Camera_H__
