#pragma once

#include <string>

struct SpriteProperties
{
	std::string m_Name; 
	fw::vec2 m_UVOffset; 
	fw::vec2 m_UVScale; 
};

class SpriteSheet
{
public:
	SpriteSheet(); 
	~SpriteSheet(); 

	void Init(char* filename, GLuint textureID); 
	SpriteProperties GetSpriteProperties(std::string name); 

	GLuint m_TextureID; 

protected:

	std::vector<SpriteProperties> m_SpriteProperties; 
	float m_SpriteSheetWidth = 0;
	float m_SpriteSheetHeight = 0; 

	int m_ArraySize = 0; 
};