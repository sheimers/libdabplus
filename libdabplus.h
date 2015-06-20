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


#define AUTO_GAIN -100
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
  void startReceiver();
  void stopReceiver();
  void setEtiCallback(void(*cb)(uint8_t*));
 


 private:
  void receiver();
  static uint32_t frequency; // receiving frequency in Hz
  static int gain;           // integer, 10 times the gain in db ()
  bool first_frame;
  static bool new_frequency;
  static bool new_gain;
  static std::queue<etiFrame> etififo;

  // lines below borrowed from dab2eti.c by David May

  static void eti_callback(uint8_t* eti);
  static int do_sdr_decode(struct dab_state_t* dab, int frequency);
  static int do_wf_decode(struct dab_state_t* dab, int frequency);
  static void *demod_thread_fn(void *arg);
  
  /* Wavefinder state */
  struct wavefinder_t  wf;

  /* RTL-SDR device state */
  static struct sdr_state_t sdr;
  static rtlsdr_dev_t *dev;
  void (*client_eti_callback)(uint8_t*); // callback function that can be implemented in the client to replace eti_callback()

};
