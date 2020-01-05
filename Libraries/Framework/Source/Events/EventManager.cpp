#include "FrameworkPCH.h"

namespace fw
{
    EventManager::EventManager()
    {
    }

    EventManager::~EventManager()
    {
        while( m_Queue.empty() == false )
        {
            delete m_Queue.front();
            m_Queue.pop();
        }
    }

    void EventManager::AddEventToQueue(Event* pEvent)
    {
        m_Queue.push( pEvent );
    }

    void EventManager::ProcessEvents(GameCore* pGame)
    {
        while( m_Queue.empty() == false )
        {
            Event* pEvent = m_Queue.front();
            m_Queue.pop();

            pGame->OnEvent( pEvent );

            delete pEvent;
        }
    }

} // namespace fw
