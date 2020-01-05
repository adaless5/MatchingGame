#ifndef __Vector_H__
#define __Vector_H__

namespace fw
{
    static const float PI = 3.1415927f;

    template<class TYPE>
    class TVec2
    {
    public:
        TYPE x, y;

        TVec2() { x = y = 0; }
        TVec2(TYPE value) { x = y = value; }
        TVec2(TYPE nx, TYPE ny) { x = nx; y = ny; }

        TVec2 operator+(const TVec2& o) const { return TVec2( x + o.x, y + o.y ); }
        TVec2 operator-(const TVec2& o) const { return TVec2( x - o.x, y - o.y ); }
        TVec2 operator*(const TVec2& o) const { return TVec2( x * o.x, y * o.y ); }

        TVec2 operator*(TYPE o) const { return TVec2( x * o, y * o ); }
        TVec2 operator/(TYPE o) const { return TVec2( x / o, y / o ); }

        void operator+=(const TVec2& o) { x += o.x, y += o.y; }

        void Set(TYPE nx, TYPE ny) { x = nx; y = ny; }
        TYPE Length() { return sqrtf( x*x + y*y ); }

        void Normalize() { x /= Length(); y /= Length(); }
    };

    typedef TVec2<float> vec2;
    typedef TVec2<int> ivec2;

} // namespace fw

#endif //__Vector_H__
