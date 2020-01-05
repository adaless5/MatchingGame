#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"

using namespace fw;

GameObject::GameObject(Game* pGame, Mesh* pMesh, ShaderProgram* pShader, GLuint textureID, fw::vec2 position)
: m_pGame( pGame )
, m_pMesh( pMesh )
, m_pShader( pShader )
, m_TextureID( textureID )
, m_Position( position )
, m_Radius( 2 )
{
}

GameObject::~GameObject()
{
}

fw::AABB GameObject::GetWorldAABB()
{
    return fw::AABB( m_Position + m_pMesh->GetBoundingBox().GetMin(),
                     m_Position + m_pMesh->GetBoundingBox().GetMax() );
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(Camera* pCamera)
{
	if( m_pMesh != 0 )
        m_pMesh->Draw( pCamera, m_pShader, m_Position, m_TextureID, m_UVOffset, m_UVScale);
}

bool GameObject::IsColliding(GameObject* pOtherGameObject)
{
    //float radii = m_Radius + pOtherGameObject->m_Radius;
    //if( (m_Position - pOtherGameObject->m_Position).Length() < radii )
    //    return true;

    if( GetWorldAABB().IsOverlapping( pOtherGameObject->GetWorldAABB() ) )
    {
        ImGui::Text( "OVERLAPPING!!!" );
        //return true;
    }

    return false;
}

void GameObject::OnCollision(GameObject* pOtherGameObject)
{
}