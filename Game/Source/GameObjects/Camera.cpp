#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "Game.h"

using namespace fw;

Camera::Camera(Game* pGame, fw::vec2 position, fw::vec2 projectionScale)
: GameObject( pGame, nullptr, nullptr, 0, position )
, m_ProjectionScale( projectionScale )
{
}
    
Camera::~Camera()
{
}
