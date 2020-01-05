#ifndef __Event_H__
#define __Event_H__

namespace fw
{
    class Event
    {
    public:
        Event() {}
        virtual ~Event() {}

        virtual std::string GetType() = 0;
    };

} // namespace fw

#endif //__Event_H__
