#include <iostream>
#include <stdint.h>

#define AUTO_GAIN -100
#define DEFAULT_FREQUENCY 

enum etiType {ETI_NI_G703,ETI_NI_V11,ETI_NA};

struct etiFrame {
  int size;
  uint8_t *data;
  etiType type;
};

class dab2eti {

public:
  dab2eti();
  ~dab2eti();
  bool setGain(int newgain);  
  bool setChannel(std::string channel);
  bool setFrequency(int freqhz);
  bool setFrequencyMhz(float freqmhz);
  etiFrame getEtiFrame();

private:
  int frequency; // receiving frequency in Hz
  int gain;
  bool first_frame;
};
