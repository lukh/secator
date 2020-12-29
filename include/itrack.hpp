#include <vector>
#include <map>

class ZeSeqData{
    uint8_t note;
    uint8_t vel;
};


template<typename Timebase_t, typename SeqData_t>
class Event{
    using SeqData = SeqData_t;
    Timebase_t  timestamp;
    std::vector<SeqData_t>  seq_data;
}

template <typename Event_t>
class ITrack{
    using Events = std::list<Event_t>;
    using Timebase_t = Event_t::Timebase_t:

    Timebase_t sequence(){
        if(event == events.end()) {
            return;
        }
        
        for(typename Event_t::SeqData sd : event.seq_data){
            play(sd)
        }

        event++;
        
        return event.timestamp;
    }


    Timebase_t synchronise(Timebase_t time){
        for (auto const& i : events) {
            if(i.timestamp >= time){
                event = i;
                return i.timestamp;
            }
        }

        return Timebase_t();
    }


    Events events;
    Events::iterator event;
};
