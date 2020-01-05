#ifndef __GameEvent_H__
#define __GameEvent_H__

#include "Event.h"

namespace fw
{
    enum class GameEventType
    {
        Win,
        Death,
    };

    class GameEvent : public Event
    {
    protected:
        GameEventType m_GameEventType;

    public:
        GameEvent(GameEventType type)
        {
            m_GameEventType = type;
        }

        virtual std::string GetType() { return "GameEvent"; }

        GameEventType GetGameEventType() { return m_GameEventType; }
    };

} // namespace fw

#endif //__GameEvent_H__
