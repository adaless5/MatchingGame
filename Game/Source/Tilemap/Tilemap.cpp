#include "GamePCH.h"
#include "Tilemap.h"
#include "Base/Mesh.h"
#include "GameObjects/Camera.h"
#include "SpriteSheet/SpriteSheet.h"
#include <time.h>

Tilemap::Tilemap(char* filename, SpriteSheet* spritesheet)
{
	srand(time(NULL)); 

    m_pMesh = new Mesh();
    m_pMesh->GenerateCard();

    m_pShader = new fw::ShaderProgram( "Data/Shaders/texture.vert", "Data/Shaders/texture.frag" );
	m_TextureID = fw::LoadTexture("Data/Textures/Bomberman.png");

	m_pSpriteSheet = spritesheet; 

    // Create properties.
    m_Props = new TileProperties[(int)TileType::NumTypes];
    m_Props[(int)TileType::CardBack].m_pMesh = m_pMesh;
    m_Props[(int)TileType::CardBack].m_pShader = m_pShader;
    m_Props[(int)TileType::CardBack].m_TextureID = m_TextureID;
    m_Props[(int)TileType::CardBack].m_IsWalkable = true;
    m_Props[(int)TileType::CardBack].m_Filename = "CardBack.png";

    m_Props[(int)TileType::Square].m_pMesh = m_pMesh;
    m_Props[(int)TileType::Square].m_pShader = m_pShader;
    m_Props[(int)TileType::Square].m_TextureID = m_TextureID;
    m_Props[(int)TileType::Square].m_IsWalkable = false;
	m_Props[(int)TileType::Square].m_Filename = "Square.png";

	m_Props[(int)TileType::Circle].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Circle].m_pShader = m_pShader;
	m_Props[(int)TileType::Circle].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Circle].m_IsWalkable = true;
	m_Props[(int)TileType::Circle].m_Filename = "Circle.png";

	m_Props[(int)TileType::Star].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Star].m_pShader = m_pShader;
	m_Props[(int)TileType::Star].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Star].m_IsWalkable = true;
	m_Props[(int)TileType::Star].m_Filename = "Star.png";

	m_Props[(int)TileType::Hexagon].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Hexagon].m_pShader = m_pShader;
	m_Props[(int)TileType::Hexagon].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Hexagon].m_IsWalkable = true;
	m_Props[(int)TileType::Hexagon].m_Filename = "Hexagon.png";

	m_Props[(int)TileType::Triangle].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Triangle].m_pShader = m_pShader;
	m_Props[(int)TileType::Triangle].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Triangle].m_IsWalkable = true;
	m_Props[(int)TileType::Triangle].m_Filename = "Triangle.png";
	
	m_Props[(int)TileType::Trapezoid].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Trapezoid].m_pShader = m_pShader;
	m_Props[(int)TileType::Trapezoid].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Trapezoid].m_IsWalkable = true;
	m_Props[(int)TileType::Trapezoid].m_Filename = "Trapezoid.png";
	
	m_Props[(int)TileType::Diamond].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Diamond].m_pShader = m_pShader;
	m_Props[(int)TileType::Diamond].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Diamond].m_IsWalkable = true;
	m_Props[(int)TileType::Diamond].m_Filename = "Diamond.png";
	
	m_Props[(int)TileType::Plus].m_pMesh = m_pMesh;
	m_Props[(int)TileType::Plus].m_pShader = m_pShader;
	m_Props[(int)TileType::Plus].m_TextureID = m_TextureID;
	m_Props[(int)TileType::Plus].m_IsWalkable = true;
	m_Props[(int)TileType::Plus].m_Filename = "Plus.png";

	m_Props[(int)TileType::NoType].m_pMesh = m_pMesh;
	m_Props[(int)TileType::NoType].m_pShader = m_pShader;
	m_Props[(int)TileType::NoType].m_TextureID = m_TextureID;
	m_Props[(int)TileType::NoType].m_IsWalkable = false;
	m_Props[(int)TileType::NoType].m_Filename = "Cleared.png";

    // Load JSON layout file.
    long fileLen;    
    char* fileContents = fw::LoadCompleteFile( filename, &fileLen );
    cJSON* jRoot = cJSON_Parse( fileContents );

    m_MapSize.x = cJSON_GetObjectItem( jRoot, "mapW" )->valueint;
    m_MapSize.y = cJSON_GetObjectItem( jRoot, "mapH" )->valueint;
    m_TileSize.x = (float)cJSON_GetObjectItem( jRoot, "tileW" )->valuedouble;
    m_TileSize.y = (float)cJSON_GetObjectItem( jRoot, "tileH" )->valuedouble;

    m_Layout = new TileType[m_MapSize.x * m_MapSize.y];

    cJSON* jLayout = cJSON_GetObjectItem( jRoot, "layout" );
    int sizeY = cJSON_GetArraySize( jLayout );
    assert( sizeY == m_MapSize.y );

    for( int y=0; y<sizeY; y++ )
    {
        cJSON* jRow = cJSON_GetArrayItem( jLayout, y );
        int sizeX = cJSON_GetArraySize( jRow );
        assert( sizeX == m_MapSize.x );

        for( int x=0; x<sizeX; x++ )
        {
            TileType type = (TileType)cJSON_GetArrayItem( jRow, x )->valueint;

            int index = (m_MapSize.y-1 - y) * m_MapSize.x + x;
            m_Layout[index] = type;
        }
    }

    delete[] fileContents;
}

Tilemap::~Tilemap()
{
    for( int i=0; i<(int)TileType::NumTypes; i++ )
    {
        glDeleteTextures( 1, &m_Props[i].m_TextureID );
    }

    delete m_pMesh;
    delete m_pShader;

    delete[] m_Props;
    delete[] m_Layout;
}

void Tilemap::Draw(Camera* pCamera)
{
    for( int y=0; y<m_MapSize.y; y++ )
    {
        for( int x=0; x<m_MapSize.x; x++ )
        {
            int tileIndex = y * m_MapSize.x + x;
            TileType type = m_Layout[tileIndex];
            TileProperties* pProp = &m_Props[(int)type];

            vec2 pos( x * m_TileSize.x, y * m_TileSize.y );
            pos += m_TileSize / 2;

            pProp->m_pMesh->Draw( pCamera, pProp->m_pShader, pos, pProp->m_TextureID, m_pSpriteSheet->GetSpriteProperties(pProp->m_Filename).m_UVOffset, m_pSpriteSheet->GetSpriteProperties(pProp->m_Filename).m_UVScale);
        }
    }
}

bool Tilemap::IsTileWalkable(vec2 worldPos)
{
    int tx = (int)(worldPos.x / m_TileSize.x);
    int ty = (int)(worldPos.y / m_TileSize.y);

    if( tx < 0 || tx >= m_MapSize.x ) return false;
    if( ty < 0 || ty >= m_MapSize.y ) return false;

    int tileIndex = ty * m_MapSize.x + tx;
    TileType type = m_Layout[tileIndex];
    return m_Props[(int)type].m_IsWalkable;
}

void Tilemap::SetLayout(int index)
{
	m_Layout[index] = m_HiddenLayout[index]; 
}

void Tilemap::SetBackLayout(int index1, int index2)
{
	m_Layout[index1] = TileType::CardBack; 
	m_Layout[index2] = TileType::CardBack; 
}

void Tilemap::FoundMatch(int index1, int index2)
{
	m_Layout[index1] = TileType::NoType; 
	m_Layout[index2] = TileType::NoType; 
}

TileType Tilemap::GetTileType(int index)
{
	return m_Layout[index];
}

void Tilemap::RandomizeHiddenLayout()
{
	for (int i = 0; i < LAYOUT_SIZE; i++)
	{
		int randomindex = rand() % LAYOUT_SIZE;
		do
		{
			randomindex = rand() % LAYOUT_SIZE;

		} while (randomindex == i);

		TileType temp = m_HiddenLayout[i]; 

		m_HiddenLayout[i] = m_HiddenLayout[randomindex]; 
		m_HiddenLayout[randomindex] = temp; 
	}
}

bool Tilemap::CheckForWin()
{
	for (int i = 0; i < LAYOUT_SIZE; i++)
	{
		if (m_Layout[i] != TileType::NoType)
		{
			break; 
		}
		else if (i == LAYOUT_SIZE - 1)
		{
			OutputDebugString("GameWon"); 
			return true;
		}
	}

	return false;
}

void Tilemap::ResetTileMap()
{
	for (int i = 0; i < LAYOUT_SIZE; i++)
	{
		m_Layout[i] = TileType::CardBack; 
	}

	RandomizeHiddenLayout(); 
}
