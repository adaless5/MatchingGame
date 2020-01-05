#include "GamePCH.h"

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet()
{

}

SpriteSheet::~SpriteSheet()
{

}

void SpriteSheet::Init(char* filename, GLuint textureID)
{
	m_TextureID = textureID; 

	long fileLen;
	char* fileContents = fw::LoadCompleteFile(filename, &fileLen); 
	cJSON* jRoot = cJSON_Parse(fileContents); 

	m_SpriteSheetWidth = (float)cJSON_GetObjectItem(jRoot, "width")->valuedouble; 
	m_SpriteSheetHeight = (float)cJSON_GetObjectItem(jRoot, "height")->valuedouble; 

	cJSON* jFiles = cJSON_GetObjectItem(jRoot, "Files"); 

	m_ArraySize = cJSON_GetArraySize(jFiles); 

	for (int i = 0; i < m_ArraySize; i++)
	{
		cJSON* jSpriteInfo = cJSON_GetArrayItem(jFiles, i); 
		std::string filename = (std::string)cJSON_GetObjectItem(jSpriteInfo, "filename")->valuestring; 
		float origw = (float)cJSON_GetObjectItem(jSpriteInfo, "origw")->valuedouble; 
		float origh = (float)cJSON_GetObjectItem(jSpriteInfo, "origh")->valuedouble; 
		float posx = (float)cJSON_GetObjectItem(jSpriteInfo, "posx")->valuedouble; 
		float posy = (float)cJSON_GetObjectItem(jSpriteInfo, "posy")->valuedouble; 

		SpriteProperties spriteProp;
		spriteProp.m_Name = filename; 
		spriteProp.m_UVOffset = fw::vec2(posx / m_SpriteSheetWidth, posy / m_SpriteSheetHeight); 
		spriteProp.m_UVScale = fw::vec2(origw / m_SpriteSheetWidth, origh / m_SpriteSheetHeight); 

		m_SpriteProperties.push_back(spriteProp); 
	}

	delete[] fileContents; 
}

SpriteProperties SpriteSheet::GetSpriteProperties(std::string name)
{
	for (int i = 0; i < m_ArraySize; i++)
	{
		if (m_SpriteProperties[i].m_Name == name)
		{
			return m_SpriteProperties.at(i); 
		}
	}
	return SpriteProperties();
}
