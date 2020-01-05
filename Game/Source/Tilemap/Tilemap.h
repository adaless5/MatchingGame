#pragma once

#include <string>

class Mesh;
class Camera;
class SpriteSheet; 

enum class TileType
{
    CardBack,
    Square,
	Circle,
	Star,
	Hexagon, 
	Triangle, 
	Trapezoid,
	Diamond, 
	Plus, 
	NoType,
    NumTypes
	
};

struct TileProperties
{
    Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    GLuint m_TextureID;
    bool m_IsWalkable;
	std::string m_Filename; 
};

class Tilemap
{
protected:
    ivec2 m_MapSize;
    vec2 m_TileSize;

    Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
	GLuint m_TextureID;

	const int LAYOUT_SIZE = 16; 

    TileType* m_Layout;
	TileType m_HiddenLayout[16] = {
		TileType::Square,   TileType::Square,   TileType::Circle,    TileType::Circle,
		TileType::Star,     TileType::Star,     TileType::Hexagon,   TileType::Hexagon,
		TileType::Triangle, TileType::Triangle, TileType::Trapezoid, TileType::Trapezoid,
		TileType::Diamond,  TileType::Diamond,  TileType::Plus,      TileType::Plus
	};

    TileProperties* m_Props;
	SpriteSheet* m_pSpriteSheet; 

public:
    Tilemap(char* filename, SpriteSheet* spritesheet);
    virtual ~Tilemap();

    void Draw(Camera* pCamera);
    bool IsTileWalkable(vec2 worldPos);
	void SetLayout(int index); 
	void SetBackLayout(int index1, int index2); 
	void FoundMatch(int index1, int index2);
	TileType GetTileType(int index); 
	void RandomizeHiddenLayout(); 
	bool CheckForWin();
	void ResetTileMap(); 
};