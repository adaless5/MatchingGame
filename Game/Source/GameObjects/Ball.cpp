#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ball.h"
#include "Game.h"

using namespace fw;

Ball::Ball(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position)
: GameObject( pGame, pMesh, pShader, textureID, position )
, m_Speed( 0 )
, m_Angle( 0 )
{
}
    
Ball::~Ball()
{
}

void Ball::Update(float deltaTime)
{
    // Calculate the ball's velocity based on the speed and the angle.
    float anglerad = m_Angle * PI / 180;
    vec2 velocity = vec2( cosf(anglerad), sinf(anglerad) ) * m_Speed;
        
    // Apply the velocity to the Ball's position.
    m_Position += velocity * deltaTime;
    
    // Get the world width and height.
    float worldWidth = m_pGame->GetWorldWidth();
    float worldHeight = m_pGame->GetWorldHeight();

    // Vertical bounds check.
    if( m_Position.y + GetRadius() > worldHeight )
    {
        // Calculate the ball's reflected angle.
        m_Angle = atan2f( -velocity.y, velocity.x ) * 180 / PI;
            
        // Make sure the ball isn't still intersecting with the wall.
        m_Position.y = worldHeight - GetRadius() - 1.0f;
    }
    else if( m_Position.y - GetRadius() < 0.0f )
    {
        // Calculate the ball's reflected angle.
        m_Angle = atan2f( -velocity.y, velocity.x ) * 180 / PI;

        // Make sure the ball isn't still intersecting with the wall.
        m_Position.y = GetRadius() + 1.0f;
    }

    // Horizontal bounds check.
    if( m_Position.x - GetRadius() < 0.0f )
    {
        // Calculate the ball's reflected angle.
        m_Angle = atan2f( velocity.y, -velocity.x ) * 180 / PI;
            
        // Make sure the ball isn't still intersecting with the wall.
        m_Position.x = GetRadius() + 1.0f;
    }
    else if( m_Position.x + GetRadius() > worldWidth )
    {
        // Calculate the ball's reflected angle.
        m_Angle = atan2f(velocity.y, -velocity.x) * 180 / PI;
            
        // Make sure the ball isn't still intersecting with the wall.
        m_Position.x = worldWidth - GetRadius() - 1.0f;
    }

    // Slow down the ball.
    m_Speed -= BALL_FRICTION * deltaTime;
    if( m_Speed < 0 )
        m_Speed = 0;
}

void Ball::OnCollision(GameObject* pOtherGameObject)
{
    vec2 dir = m_Position - pOtherGameObject->GetPosition();
    dir.Normalize();

    m_Angle = atan2f( dir.y, dir.x ) / PI * 180.0f;
    m_Speed = BALL_SPEED_WHEN_HIT;
}
