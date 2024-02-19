/*
 * Serial.h
 *
 *  Created on: Jan 3, 2023
 *      Author: igor
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_


#include <cstdlib>
#include "Object.h"


class Serial: public Object{


  unsigned int writeTimeout;
  unsigned int readTimeout;


public:

  static const unsigned int DefaultWriteTimeout = 100; /* ms */
  static const unsigned int DefaultReadTimeout = 100; /* ms */
  static const uint8_t D_UART_MAGIC = 0x5E;
  static const uint8_t D_UART_MAGIC_END = 0x03;

  virtual uint32_t available() = 0;
  virtual uint32_t write(void * buffer, size_t length) = 0;
  virtual uint32_t read(void * buffer, size_t length) = 0;
  virtual void clearRxBuffer() = 0;


  explicit inline
  Serial(const char * name)
  : Object(name)
  {
    setWriteTimeout(DefaultWriteTimeout);
    setReadTimeout(DefaultReadTimeout);
  }


  inline unsigned int
  getWriteTimeout() const {
    return writeTimeout;
  }


  inline void
  setWriteTimeout(unsigned int writeTimeout) {
    this->writeTimeout = writeTimeout;
  }


  inline unsigned int
  getReadTimeout() const {
    return readTimeout;
  }


  inline void
  setReadTimeout(unsigned int readTimeout) {
    this->readTimeout = readTimeout;
  }


  inline bool
  write(unsigned char byte) {
    return write(&byte, sizeof (unsigned char));
  }


  inline int
  read() {
    unsigned char byte;

    auto ok = read(&byte, sizeof (unsigned char));

    return ok ? byte : -1;
  }

  inline uint16_t
  crc_buf(uint8_t *buffer, size_t length) {
    uint16_t     crc;
    size_t       i;

    crc = 0;

    for (i = 0; i < length; i++) {
      crc = crc_byte(crc, buffer[i]);
    }

    return crc;
  }


  inline uint16_t
  crc_byte(uint16_t crc, char c) {
    int i;

    crc ^= (uint16_t) c << 8;

    for (i = 0; i < 8; i++) {
      if (crc & 0x8000) {
  	crc = (crc << 1) ^ 0x1021;
      } else {
  	crc <<= 1;
      }
    }

    return crc;
  }
};




#endif /* INC_SERIAL_H_ */
