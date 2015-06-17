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


class etioutput: public dab2eti{
public:
  static void my_eti_callback(uint8_t* eti);
};


void etioutput::my_eti_callback(uint8_t* eti){
  // WARNING: The pointer eti will always point to the same
  // address, but with changing data. It is necessary
  // to finish processing or to copy the data away before
  // returning from this function.
  
  //std::cout << "I am in eti_callback" << (unsigned long) eti << std::endl;
  fwrite(eti,1,6144,stdout); // output the ETI frame to stdout
}

int main(){
  etioutput myreceiver;
  myreceiver.setEtiCallback(etioutput::my_eti_callback);
  myreceiver.setChannel("12C");
  myreceiver.startReceiver(); // will start the dab receiver in a separate
                              // thread and continue. my_eti_callback
                              // will be called from that thread for each
                              // ETI frame received
  
  while(1){ // wait forever, or implement something more interesting below
     sleep(10);
  }
}
