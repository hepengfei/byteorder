#pragma once

#include <stdint.h>

#include "byteorder.hpp"

namespace kb {

  template<typename Endian>
  struct Binary {
    uint16_t Uint16(const char *data);
    uint32_t Uint32(const char *data);
    uint64_t Uint64(const char *data);

    void PutUint16(char *data, uint16_t value);
    void PutUint32(char *data, uint32_t value);
    void PutUint64(char *data, uint64_t value);
  };

  template<>
  struct Binary<big_endian> {
    uint16_t Uint16(const char *data);
    uint32_t Uint32(const char *data);
    uint64_t Uint64(const char *data);

    void PutUint16(char *data, uint16_t value);
    void PutUint32(char *data, uint32_t value);
    void PutUint64(char *data, uint64_t value);
  };

  template<>
  struct Binary<little_endian> {
    uint16_t Uint16(const char *data);
    uint32_t Uint32(const char *data);
    uint64_t Uint64(const char *data);

    void PutUint16(char *data, uint16_t value);
    void PutUint32(char *data, uint32_t value);
    void PutUint64(char *data, uint64_t value);
  };


  uint16_t Binary<little_endian>::Uint16(const char *data) {
    return uint16_t(data[0]) | uint16_t(data[1]) << 8;
  }


  uint32_t Binary<little_endian>::Uint32(const char *data) {
    return uint32_t(data[0]) | uint32_t(data[1]) << 8 |
      uint32_t(data[2]) << 16 | uint32_t(data[3]) << 24;
  }


  uint64_t Binary<little_endian>::Uint64(const char *data) {
    return uint64_t(data[0]) | uint64_t(data[1]) << 8 |
      uint64_t(data[2]) << 16 | uint64_t(data[3]) << 24 |
      uint64_t(data[4]) << 32 | uint64_t(data[5]) << 40 |
      uint64_t(data[6]) << 48 | uint64_t(data[7]) << 56;
  }


  void Binary<little_endian>::PutUint16(char *data, uint16_t value) {
    data[0] = value;
    data[1] = value >> 8;
  }


  void Binary<little_endian>::PutUint32(char *data, uint32_t value) {
    data[0] = value;
    data[1] = value >> 8;
    data[2] = value >> 16;
    data[3] = value >> 24;
  }


  void Binary<little_endian>::PutUint64(char *data, uint64_t value) {
    data[0] = value;
    data[1] = value >> 8;
    data[2] = value >> 16;
    data[3] = value >> 24;
    data[4] = value >> 32;
    data[5] = value >> 40;
    data[6] = value >> 48;
    data[7] = value >> 56;
  }


  uint16_t Binary<big_endian>::Uint16(const char *data) {
    return uint16_t(data[1]) | uint16_t(data[0]) << 8;
  }


  uint32_t Binary<big_endian>::Uint32(const char *data) {
    return uint32_t(data[3]) | uint32_t(data[2]) << 8 |
      uint32_t(data[1]) << 16 | uint32_t(data[0]) << 24;
  }


  uint64_t Binary<big_endian>::Uint64(const char *data) {
    return uint64_t(data[7]) | uint64_t(data[6]) << 8 |
      uint64_t(data[5]) << 16 | uint64_t(data[4]) << 24 |
      uint64_t(data[3]) << 32 | uint64_t(data[2]) << 40 |
      uint64_t(data[1]) << 48 | uint64_t(data[0]) << 56;
  }


  void Binary<big_endian>::PutUint16(char *data, uint16_t value) {
    data[0] = value >> 8;
    data[1] = value;
  }


  void Binary<big_endian>::PutUint32(char *data, uint32_t value) {
    data[0] = value >> 24;
    data[1] = value >> 16;
    data[2] = value >> 8;
    data[3] = value;
  }


  void Binary<big_endian>::PutUint64(char *data, uint64_t value) {
    data[0] = value >> 56;
    data[1] = value >> 48;
    data[2] = value >> 40;
    data[3] = value >> 32;
    data[4] = value >> 24;
    data[5] = value >> 16;
    data[6] = value >> 8;
    data[7] = value;
  }

}
