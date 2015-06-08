/*
This file is part of libdabplus
Libdabplus is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Libdabplus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libdabplus.  If not, see <http://www.gnu.org/licenses/>.

C++ library wrapper by Stefan Heimers 2015, the actual DAB
demodulation and decoding is implemented by other people, please see
the headers of each source code file in the ../dabtools and ../rtl-sdr
directory which need to be downloaded separately

*/

#include <iostream>
#include <stdint.h>
#include <queue>
#include <unistd.h>

#define AUTO_GAIN -100
#define DEFAULT_FREQUENCY 227360000
#define MAX_ETI_SIZE 6144   // TODO: check if enough for ETI-NI (V.11), 
                            // should be fine for ETI-NI (G.703) and ETI-NA (G.704)

enum etiType {ETI_NI_G703,ETI_NI_V11,ETI_NA};

struct etiFrame {
  uint16_t frameSize;
  uint8_t data[MAX_ETI_SIZE];
  etiType type;
};

class dab2eti {

public:
  dab2eti();
  ~dab2eti();
  bool setGain(int newgain);  
  bool setChannel(std::string channel);
  bool setFrequency(uint32_t freqhz);
  bool setFrequencyMhz(float freqmhz);
  etiFrame getEtiFrame();

private:
  uint32_t frequency; // receiving frequency in Hz
  int gain;
  bool first_frame;
  std::queue<etiFrame> etififo;
};
