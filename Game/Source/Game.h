#ifndef __Game_H__
#define __Game_H__

class Ball;
class Camera;
class GameObject;
class ImGuiManager;
class Mesh;
class Player;
class PlayerController;
class Tilemap;
class SpriteSheet; 

class Game : public fw::GameCore
{
protected:
    fw::ImGuiManager* m_pImGuiManager;

    fw::ShaderProgram* m_pShaderColor;
    fw::ShaderProgram* m_pShaderTexture;
    Mesh* m_pMeshTriangle;
	Mesh* m_pMeshCursor; 
    GLuint m_TextureBall;
	GLuint m_TextureAtlas; 

    Tilemap* m_pTilemap;

    Player* m_pPlayer;
    Camera* m_pCamera;

    PlayerController* m_pController;

	SpriteSheet* m_pSpriteSheet; 

public:
    Game(fw::Framework* pFramework);
    virtual ~Game();

    virtual void Init() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void CheckForCollisions();

    // Getters.
    float GetWorldWidth() { return 100.0f; }
    float GetWorldHeight() { return 100.0f; }
};

#endif //__Game_H__
