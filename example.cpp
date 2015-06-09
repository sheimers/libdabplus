#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <thread>
#include <algorithm>
#include <string>
#include <rtl-sdr.h>

extern "C" {
#include "../dabtools/src/dab.h"
#include "../dabtools/src/input_sdr.h"
#include "../dabtools/src/input_wf.h"
}

#include "libdabplus.h"



int main(){
  etiFrame frame;
  dab2eti myreceiver;
  myreceiver.setChannel("12C");
  while(1){
    frame = myreceiver.getEtiFrame();
    fwrite(&frame.data,1,frame.frameSize,stdout);
  }
}
