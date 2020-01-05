#ifndef __Player_H__
#define __Player_H__

#include "GameObject.h"

class Mesh;
class PlayerController;
class Tilemap;
class SpriteSheet; 

class Player : public GameObject
{
protected:
    Tilemap* m_pTilemap;
    PlayerController* m_pController;
	SpriteSheet* m_pSpriteSheet; 
    int m_PlayerNumber;
	int m_PlayerSelectionIndex; 
	int m_CurrentPositionIndex = 0;
	int m_SelectionCounter = 0;
	int m_FirstSelection = 0; 
	int m_SecondSelection = 0; 
	bool m_CardSelected = false; 
	float m_SelectionTimer = 0.0f; 
	bool m_CursorIsActive = true; 

public:
    Player(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, SpriteSheet* spritesheet, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController);
    ~Player();

    virtual void Update(float deltaTime);
    bool FitsOnTilemap(vec2 newPos);
	void FlipSelectedCard(); 
	void ResetSelectionTimer(); 
	void ActivateCursor(); 
	void MakeCardSelection(); 
	void TimerHandler(float deltatime);
	void CheckIfWon(); 
};

#endif //__Player_H__
