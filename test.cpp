#include <cstdint>
#include <iostream>

#include "include/sequencer.hpp"


using namespace std;

using ZeData = uint8_t;

using ZeEvent = Event<uint8_t, ZeData>;

class ZeTrack: public ITrack<ZeTrack, ZeEvent>{
    public:
        void play(uint8_t data){
            cout << int(data) << ", ";
        }
};



using ZeSequencer = Sequencer<uint8_t, ZeTrack>;



int main(int argc, char **argv){
    ZeSequencer seq;


    auto t1 = seq.getTrack<0>();
    t1->set(6, 46);
    t1->set(1, 41);
    t1->set(5, 45);
    t1->set(2, 42);
    t1->set(3, 43);
    t1->set(4, 44);


    t1->set(2, 52);


    cout << "test" << endl;
    for(auto const &i: t1->events){
        cout << int(i.timestamp) << " > " << int(i.data) << endl;
    }


    seq.synchronize(5);

    for(int i = 0; i < 20; i ++){
        cout << "STEP = " << i << " : ";
        seq.step();
        cout << endl;
    }

    return 0;
}
