#ifndef __VertexFormat_H__
#define __VertexFormat_H__

struct VertexFormat
{
    float x, y;
    unsigned char r, g, b, a;
    float u, v;

    VertexFormat()
    {
        x = 0;
        y = 0;
        r = 0;
        g = 0;
        b = 0;
        a = 0;
        u = 0;
        v = 0;
    }

    VertexFormat(float nx, float ny, unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na, float nu, float nv)
    {
        x = nx;
        y = ny;
        r = nr;
        g = ng;
        b = nb;
        a = na;
        u = nu;
        v = nv;
    }
};

#endif //__VertexFormat_H__

