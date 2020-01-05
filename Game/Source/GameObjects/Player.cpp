#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Tilemap/Tilemap.h"
#include "SpriteSheet/SpriteSheet.h"

using namespace fw;

Player::Player(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, SpriteSheet* spritesheet, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController)
: GameObject( pGame, pMesh, pShader, textureID, position)
, m_PlayerNumber( playerNum )
, m_pTilemap( pTilemap )
, m_pController( pController )
{
	m_pSpriteSheet = spritesheet; 

	m_UVOffset = m_pSpriteSheet->GetSpriteProperties("Cursor.png").m_UVOffset; 
	m_UVScale = m_pSpriteSheet->GetSpriteProperties("Cursor.png").m_UVScale; 

	m_pTilemap->RandomizeHiddenLayout(); 
	m_PlayerSelectionIndex = ((int)m_Position.y / 25) * 4 + ((int)m_Position.x / 25);
}
    
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	m_CurrentPositionIndex = ((int)m_Position.y / 25) * 4 + ((int)m_Position.x / 25);

	//Player Movement
    float speed = 30;
    vec2 dir( 0, 0 );
    if( m_pController->m_Up )
        dir.y = 1;
    if( m_pController->m_Down )
        dir.y = -1;
    if( m_pController->m_Left )
        dir.x = -1;
    if( m_pController->m_Right )
        dir.x = 1;

	// X check.
	vec2 newPosition = m_Position + vec2(dir.x, 0) * speed * deltaTime;
	m_Position = newPosition;

	// Y check.
	newPosition = m_Position + vec2(0, dir.y) * speed * deltaTime;
	m_Position = newPosition;

	// Get the world width and height
	float worldWidth = m_pGame->GetWorldWidth();
	float worldHeight = m_pGame->GetWorldHeight();

	//Limit Player Movement Beyond bounds of playable area
	Clamp(m_Position.x, 0.0f, worldWidth);
	Clamp(m_Position.y, 0.0f, worldHeight);

	//Card Selection Logic
	ActivateCursor(); 
	MakeCardSelection(); 
	FlipSelectedCard(); 
	TimerHandler(deltaTime); 
	ResetSelectionTimer(); 

	CheckIfWon();

	//Debugging Stuff
    /*ImGui::Begin( "Player Stuff" );
    ImGui::Text( "Hello" );
    ImGui::Text( "Position (%f, %f)", m_Position.x, m_Position.y );
	ImGui::Text("Selection Counter (%i)", m_SelectionCounter);
    ImGui::DragFloat( "X", &m_Position.x );
    ImGui::DragFloat( "Y", &m_Position.y );
    ImGui::End();*/
}

bool Player::FitsOnTilemap(vec2 newPos)
{
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x-2.0f, newPos.y-4.0f ) ) == false ) return false;
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x-2.0f, newPos.y+4.0f ) ) == false ) return false;
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x+2.0f, newPos.y+4.0f ) ) == false ) return false;
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x+2.0f, newPos.y-4.0f ) ) == false ) return false;
    return true;
}

void Player::FlipSelectedCard()
{
	if (m_CardSelected && !m_CursorIsActive)
	{
		m_PlayerSelectionIndex = ((int)m_Position.y / 25) * 4 + ((int)m_Position.x / 25);
		if (m_pTilemap->GetTileType(m_PlayerSelectionIndex) == TileType::NoType)
		{
			m_CardSelected = false;
			m_CursorIsActive = true;
		}
		else
		{
			m_pTilemap->SetLayout(m_PlayerSelectionIndex);

			if (m_SelectionCounter == 0)
			{
				m_FirstSelection = m_PlayerSelectionIndex;
			}
			else if (m_SelectionCounter == 1)
			{
				m_SecondSelection = m_PlayerSelectionIndex;
			}

			m_SelectionCounter++;

			m_CardSelected = false;
		}
	}
}

void Player::ResetSelectionTimer()
{
	if (m_SelectionTimer >= 3.0f)
	{
		if (m_pTilemap->GetTileType(m_FirstSelection) == m_pTilemap->GetTileType(m_SecondSelection))
		{
			m_pTilemap->FoundMatch(m_FirstSelection, m_SecondSelection);
		}
		if (m_pTilemap->GetTileType(m_FirstSelection) != m_pTilemap->GetTileType(m_SecondSelection))
		{
			m_pTilemap->SetBackLayout(m_FirstSelection, m_SecondSelection);

		}
		m_SelectionCounter = 0;
		m_SelectionTimer = 0.0f;
		m_CursorIsActive = true;
	}
}

void Player::ActivateCursor()
{
	if (m_CurrentPositionIndex != m_PlayerSelectionIndex)
	{
		m_CursorIsActive = true;
	}
}

void Player::MakeCardSelection()
{
	if (m_pController->m_Select && m_CursorIsActive == true && m_SelectionCounter < 2)
	{
		m_CardSelected = true;
		m_CursorIsActive = false;
	}
}

void Player::TimerHandler(float deltatime)
{
	if (m_SelectionCounter > 1)
	{
		m_SelectionTimer += deltatime;
	}
}

void Player::CheckIfWon()
{
	if (m_pTilemap->CheckForWin() == true)
	{
		m_pTilemap->ResetTileMap(); 
	}
}
