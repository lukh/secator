#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include <array>
#include <tuple>

#include "itrack.hpp"

template<class Timebase, class ...Tracks>
class Sequencer{
    public:
        // TODO: find a way to validate  Tracks::Timebase are equals to Timebase

        Sequencer(): curr_timestamp() {}
        //Sequencer(Tracks ...t): tracks(std::make_tuple(t...)) {}

        template <int index>
        auto getTrack(){
            return & std::get<index>(tracks);
        }


        template<size_t I = 0>
        void synchronize(Timebase tb){
            auto t = std::get<I>(tracks);

            timestamps[I] = t.synchronize(tb);

            if constexpr(I+1 != sizeof...(Tracks))
                synchronize<I+1>(tb);
        }

        template<size_t I = 0>
        void step() {
            auto t = std::get<I>(tracks);
            
            if(curr_timestamp == timestamps[I]){
                timestamps[I] = t.sequence();
            }

            if constexpr(I+1 != sizeof...(Tracks)){
                step<I+1>();
            }
            else{
                curr_timestamp ++;
            }
        }


    private:
        std::tuple<Tracks...> tracks;

        Timebase curr_timestamp;
        std::array<Timebase, sizeof...(Tracks)> timestamps;
};


#endif //SEQUENCER_HPP