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
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <thread>
#include <algorithm>
#include <string>

#include "libdabplus.h"

dab2eti::dab2eti(){
  first_frame = true;
}

dab2eti::~dab2eti(){
// TODO: gracefully stop receiver thread
}


bool dab2eti::setGain(int newgain){
  gain = newgain;
  return true;
}

bool dab2eti::setChannel(std::string channel){
  std::replace(channel.begin(), channel.end(), 'A','a');
  std::replace(channel.begin(), channel.end(), 'B','b');
  std::replace(channel.begin(), channel.end(), 'C','c');
  std::replace(channel.begin(), channel.end(), 'D','d');
  std::replace(channel.begin(), channel.end(), 'E','e');
  std::replace(channel.begin(), channel.end(), 'F','f');
  std::replace(channel.begin(), channel.end(), 'G','g');
  std::replace(channel.begin(), channel.end(), 'H','h');
  std::replace(channel.begin(), channel.end(), 'I','i');
  std::replace(channel.begin(), channel.end(), 'J','j');
  std::replace(channel.begin(), channel.end(), 'K','k');
  std::replace(channel.begin(), channel.end(), 'L','l');
  std::replace(channel.begin(), channel.end(), 'M','m');
  std::replace(channel.begin(), channel.end(), 'N','n');
  std::replace(channel.begin(), channel.end(), 'O','o');
  std::replace(channel.begin(), channel.end(), 'P','p');
  if (channel == "5a"){frequency = 174928000;}
  else if (channel == "5b"){frequency = 176640000;}
  else if (channel == "5c"){frequency = 178352000;}
  else if (channel == "5d"){frequency = 180064000;}
  else if (channel == "6a"){frequency = 181936000;}
  else if (channel == "6b"){frequency = 183648000;}
  else if (channel == "6c"){frequency = 185360000;}
  else if (channel == "6d"){frequency = 187072000;}
  else if (channel == "7a"){frequency = 188928000;}
  else if (channel == "7b"){frequency = 190640000;}
  else if (channel == "7c"){frequency = 192352000;}
  else if (channel == "7d"){frequency = 194064000;}
  else if (channel == "8a"){frequency = 195936000;}
  else if (channel == "8b"){frequency = 197648000;}
  else if (channel == "8c"){frequency = 199360000;}
  else if (channel == "8d"){frequency = 201072000;}
  else if (channel == "9a"){frequency = 202928000;}
  else if (channel == "9b"){frequency = 204640000;}
  else if (channel == "9c"){frequency = 206352000;}
  else if (channel == "9d"){frequency = 208064000;}
  else if (channel == "10a"){frequency = 209936000;}
  else if (channel == "10n"){frequency = 210096000;}
  else if (channel == "10b"){frequency = 211648000;}
  else if (channel == "10c"){frequency = 213360000;}
  else if (channel == "10d"){frequency = 215072000;}
  else if (channel == "11a"){frequency = 216928000;}
  else if (channel == "11n"){frequency = 217088000;}
  else if (channel == "11b"){frequency = 218640000;}
  else if (channel == "11c"){frequency = 220352000;}
  else if (channel == "11d"){frequency = 222064000;}
  else if (channel == "12a"){frequency = 223936000;}
  else if (channel == "12n"){frequency = 224096000;}
  else if (channel == "12b"){frequency = 225648000;}
  else if (channel == "12c"){frequency = 227360000;}
  else if (channel == "12d"){frequency = 229072000;}
  else if (channel == "13a"){frequency = 230784000;}
  else if (channel == "13b"){frequency = 232496000;}
  else if (channel == "13c"){frequency = 234208000;}
  else if (channel == "13d"){frequency = 235776000;}
  else if (channel == "13e"){frequency = 237488000;}
  else if (channel == "13f"){frequency = 239200000;}
  else if (channel == "la"){frequency = 1452960000;}
  else if (channel == "lb"){frequency = 1454672000;}
  else if (channel == "lc"){frequency = 1456384000;}
  else if (channel == "ld"){frequency = 1458096000;}
  else if (channel == "le"){frequency = 1459808000;}
  else if (channel == "lf"){frequency = 1461520000;}
  else if (channel == "lg"){frequency = 1463232000;}
  else if (channel == "lh"){frequency = 1464944000;}
  else if (channel == "li"){frequency = 1466656000;}
  else if (channel == "lj"){frequency = 1468368000;}
  else if (channel == "lk"){frequency = 1470080000;}
  else if (channel == "ll"){frequency = 1471792000;}
  else if (channel == "lm"){frequency = 1473504000;}
  else if (channel == "ln"){frequency = 1475216000;}
  else if (channel == "lo"){frequency = 1476928000;}
  else if (channel == "lp"){frequency = 1478640000;}
  else{
    frequency = 176640000; // dummy, just for testing
    return false;
  }
  std::cout << "frequency set to " << frequency << " for channel " << channel << std::endl;
  return true;
}

bool dab2eti::setFrequency(uint32_t freqhz){
  if (freqhz < 0){
    return false;
  }
  else{
    frequency = freqhz;
    return true;
  }
}

bool dab2eti::setFrequencyMhz(float freqmhz){
  setFrequency((uint32_t)(0.5 + freqmhz * 1000000.0));
}


void dab2eti::receiver(){
  // TODO: implement the receiver
  std::cout << "started the receiver thread..." << std::endl;
  while(1){
    sleep(2);
    std::cout << "receiver thread still running" << std::endl;
    std::cout << "freq: " << frequency << std::endl;
  }
}

etiFrame dab2eti::getEtiFrame(){
  etiFrame frame;
  if (first_frame){
    // start a separate thread that receives DAB and fills the 
    // fifo buffer with EIT frames
    std::thread receiverthread ([this]{receiver();});
    receiverthread.detach();
    first_frame = false;
  }

  // return one ETI frame and remove it from the fifo buffer
  while (etififo.empty()){
    std::cerr << "warning: buffer underrun in libdabplus: getEtiFrame(), will wait a second and try again" << std::endl;
    sleep(1);
  }
  frame = etififo.front();
  etififo.pop();
  return frame;
}
