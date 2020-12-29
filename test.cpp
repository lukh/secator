#include <cstdint>
#include <iostream>

#include "include/itrack.hpp"


using namespace std;

using ZeData = uint8_t;

using ZeEvent = Event<uint8_t, ZeData>;

class ZeTrack: public ITrack<ZeTrack, ZeEvent>{
    public:
        void play(uint8_t data){

        }
};



int main(int argc, char **argv){
    cout << "Coucou" << endl;
    return 0;
}
