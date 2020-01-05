#include "FrameworkPCH.h"

namespace fw
{
    void OutputMessage(const char* message, ...)
    {
    #define MAX_MESSAGE 1024
        char szBuff[MAX_MESSAGE];
        va_list arg;
        va_start(arg, message);
        vsnprintf_s( szBuff, sizeof(szBuff), _TRUNCATE, message, arg );
        va_end(arg);

        szBuff[MAX_MESSAGE-1] = 0; // vsnprintf_s might do this, but docs are unclear.
        OutputDebugString( szBuff );
    }

    double GetSystemTime()
    {
        unsigned __int64 freq;
        unsigned __int64 time;

        QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
        QueryPerformanceCounter( (LARGE_INTEGER*)&time );

        double timeseconds = (double)time / freq;

        return timeseconds;
    }

    double GetSystemTimeSinceGameStart()
    {
        static double starttime = -1;

        if( starttime == -1 )
            starttime = GetSystemTime();

        return GetSystemTime() - starttime;
    }

    char* LoadCompleteFile(const char* filename, long* length)
    {
        char* filecontents = 0;

        FILE* filehandle;
        errno_t error = fopen_s( &filehandle, filename, "rb" );

        if( filehandle )
        {
            fseek( filehandle, 0, SEEK_END );
            long size = ftell( filehandle );
            rewind( filehandle );

            filecontents = new char[size+1];
            fread( filecontents, size, 1, filehandle );
            filecontents[size] = 0;

            if( length )
                *length = size;

            fclose( filehandle );
        }

        return filecontents;
    }

    GLuint LoadTexture(const char* filename)
    {
        unsigned char* pngbuffer;
        unsigned int width, height;
        long filesize;
        unsigned char* filebuffer = (unsigned char*)LoadCompleteFile( filename, &filesize );
        unsigned int result = lodepng_decode32( &pngbuffer, &width, &height, filebuffer, filesize );
        delete[] filebuffer;
        assert( result == 0 );

        Flip32BitImageVertically( pngbuffer, width, height );

        GLuint texhandle = 0;
        glGenTextures( 1, &texhandle );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texhandle );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        glBindTexture( GL_TEXTURE_2D, 0 );

        free( pngbuffer );

        return texhandle;
    }

    void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height)
    {
        // flip the image in buffer.  Assumes RGBA 32 bit.

        {
            // temp allocation big enough for one line
            unsigned int* temp;
            temp = new unsigned int[width];
            int linesize = width * sizeof(unsigned int);

            unsigned int* buffer32 = (unsigned int*)buffer;
            for( unsigned int y=0; y<height/2; y++ )
            {
                int LineOffsetY = y*width;
                int LineOffsetHminusY = (height-1-y)*width;

                memcpy( temp, &buffer32[LineOffsetY], linesize );
                memcpy( &buffer32[LineOffsetY], &buffer32[LineOffsetHminusY], linesize );
                memcpy( &buffer32[LineOffsetHminusY], temp, linesize );
            }

            delete[] temp;
        }

        // slower but one less memory allocation.
        //{
        //    unsigned int* pngbuffer32 = buffer;
        //    for( unsigned int y=0; y<height/2; y++ )
        //    {
        //        int LineOffsetY = y*width;
        //        int LineOffsetHminusY = (height-1-y)*width;

        //        for( unsigned int x=0; x<width; x++ )
        //        {
        //            int tempcolor = pngbuffer32[LineOffsetY + x];
        //            pngbuffer32[LineOffsetY + x] = pngbuffer32[LineOffsetHminusY + x];
        //            pngbuffer32[LineOffsetHminusY + x] = tempcolor;
        //        }
        //    }
        //}
    }

    void Clamp(float& value, float min, float max)
    {
        if( value < min )
            value = min;
        else if( value > max )
            value = max;
    }

} // namespace fw
