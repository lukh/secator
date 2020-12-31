#include <list>
#include <algorithm>

template<typename Timebase_t, typename Data_t>
class Event{
    public:
        using Timebase = Timebase_t;
        using Data = Data_t;

        Timebase_t timestamp;
        Data_t data;

        Event(): timestamp(), data() {}
        Event(const Timebase &tb, const Data &data): 
            timestamp(tb), data(data) {}

        bool operator< (const Event<Timebase_t, Data_t> & b) const {
            return timestamp < b.timestamp;
        }

        bool operator< (Timebase_t tb) const {
            return timestamp < tb;
        }
};

template <typename Implementation, typename Event_t>
class ITrack{
    public:
        using Events = typename std::list<Event_t>;
        using EventsIterator = typename std::list<Event_t>::iterator;
        using Timebase = typename Event_t::Timebase;

        using Data = typename Event_t::Data;

        ITrack(): event(events.begin()) {}


        Timebase sequence(){
            if(event == events.end()) {
                return Timebase();
            }
            
            static_cast<Implementation *>(this)->play((*event).data);

            event++;
            
            return (*event).timestamp;
        }


        Timebase synchronize(Timebase time){
            for (auto i = events.begin(); i != events.end(); ++i) {
                if((*i).timestamp >= time){
                    event = i;
                    return (*i).timestamp;
                }
            }

            return Timebase();
        }

        void set(Timebase timestamp, Data data){
            auto lb = std::lower_bound(events.begin(), events.end(), timestamp);
            Event_t & lb_ev = *lb; 


            if(lb == events.end() || timestamp != lb_ev.timestamp){
                events.insert(lb, Event_t(timestamp, data));
            }

            else{
                lb_ev.data = data;
            }
        }

    // private:
        Events events;
        EventsIterator event;
};
