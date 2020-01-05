#ifndef __Helpers_H__
#define __Helpers_H__

namespace fw
{
    void OutputMessage(const char* message, ...);
    char* LoadCompleteFile(const char* filename, long* length);
    double GetSystemTime();
    double GetSystemTimeSinceGameStart();

    GLuint LoadTexture(const char* filename);
    void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);

    void Clamp(float& value, float min, float max);

} // namespace fw

#endif //__Helpers_H__
