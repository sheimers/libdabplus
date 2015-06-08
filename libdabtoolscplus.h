#include <iostream>

#define AUTO_GAIN -100
#define DEFAULT_FREQUENCY 

class dab2eti {

public:
  dab2eti();
  ~dab2eti();
  bool setGain(std::string channel);  
  bool setChannel(std::string channel);
  bool setFrequency(int freq);
  bool setFrequencyMhz(float freq);
   getEtiFrame();

private:
  int frequency; // receiving frequency in Hz
  int gain;
};
