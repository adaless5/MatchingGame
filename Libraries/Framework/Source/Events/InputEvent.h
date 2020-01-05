#ifndef __InputEvent_H__
#define __InputEvent_H__

#include "Event.h"

namespace fw
{
    enum class InputDevice
    {
        Keyboard,
        Mouse,
    };

    enum class InputState
    {
        Pressed,
        Released,
        Moved,
    };

    class InputEvent : public Event
    {
    protected:
        InputDevice m_Device;
        InputState m_State;
        union
        {
            int m_KeyCode;
            int m_MouseButtonID;
        };
        ivec2 m_Position;

    public:
        InputEvent(InputState state, int keyCode)
        {
            m_Device = InputDevice::Keyboard;
            m_State = state;
            m_KeyCode = keyCode;
        }

        InputEvent(InputState state, int mouseButtonID, ivec2 position)
        {
            m_Device = InputDevice::Mouse;
            m_State = state;
            m_MouseButtonID = mouseButtonID;
            m_Position = position;
        }

        virtual std::string GetType() { return "InputEvent"; }

        InputDevice GetDevice() { return m_Device; }
        InputState GetState() { return m_State; }
        int GetKeyCode() { return m_KeyCode; };
        int GetMouseButtonID() { return m_MouseButtonID; };
        ivec2 GetPosition() { return m_Position; };
    };

} // namespace fw

#endif //__InputEvent_H__
