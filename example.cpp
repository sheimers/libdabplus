#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <thread>
#include <algorithm>
#include <string>


#include "libdabplus.h"



int main(){
  etiFrame frame;
  dab2eti myreceiver;
  myreceiver.setChannel("8D");
  while(1){
    std::cout << "about to request an ETI frame..." << std::endl;
    frame = myreceiver.getEtiFrame();
    fwrite(&frame.data,1,frame.frameSize,stdout);
    sleep(5);
  }
}
