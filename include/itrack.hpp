#include <list>
#include <vector>


template<typename Timebase_t, typename SeqData_t>
class Event{
    public:
        using Timebase = Timebase_t;
        using SeqData = SeqData_t;
        Timebase_t  timestamp;
        std::vector<SeqData_t>  seq_data;
};

template <typename Implementation, typename Event_t>
class ITrack{
    public:
        using Events = typename std::list<Event_t>;
        using EventsIterator = typename std::list<Event_t>::iterator;
        using Timebase = typename Event_t::Timebase;

        Timebase sequence(){
            if(event == events.end()) {
                return;
            }
            
            for(typename Event_t::SeqData sd : event.seq_data){
                play(sd);
            }

            event++;
            
            return event.timestamp;
        }


        Timebase synchronise(Timebase time){
            for (auto const& i : events) {
                if(i.timestamp >= time){
                    event = i;
                    return i.timestamp;
                }
            }

            return Timebase();
        }

    private:
        Events events;
        EventsIterator event;
};
