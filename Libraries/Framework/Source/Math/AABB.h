#ifndef __AABB_H__
#define __AABB_H__

#include "Vector.h"

namespace fw
{
    class AABB
    {
    protected:
        vec2 m_Min;
        vec2 m_Max;

    public:
        AABB(vec2 min, vec2 max)
        {
            Set( min, max );
        }

        void Set(vec2 min, vec2 max)
        {
            assert( min.x <= max.x );
            assert( min.y <= max.y );

            m_Min = min;
            m_Max = max;
        }

        vec2 GetMin() { return m_Min; }
        vec2 GetMax() { return m_Max; }

        bool IsOverlapping(const AABB& o) const
        {
            // ------         ------
            // |this|         |this|
            // ------         ------
            //        -------
            //        |other|
            //        -------
            // ------         ------
            // |this|         |this|
            // ------         ------
            if( this->m_Max.x < o.m_Min.x )
                return false;
            if( this->m_Min.x > o.m_Max.x )
                return false;
            if( this->m_Max.y < o.m_Min.y )
                return false;
            if( this->m_Min.y > o.m_Max.y )
                return false;

            return true;
        }
    };

} // namespace fw

#endif //__AABB_H__
