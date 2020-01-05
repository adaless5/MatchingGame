#ifndef __EventManager_H__
#define __EventManager_H__

namespace fw
{
    class Event;
    class GameCore;

    class EventManager
    {
    protected:
        std::queue<Event*> m_Queue;

    public:
        EventManager();
        ~EventManager();

        void AddEventToQueue(Event* pEvent);
        void ProcessEvents(GameCore* pGame);
    };

} // namespace fw

#endif //__EventManager_H__
