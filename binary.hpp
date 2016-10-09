#pragma once

#include <stdint.h>

#include "byteorder.hpp"

namespace kb {

  template<typename Byte, typename Endian>
  struct Binary {
    uint16_t Uint16(const Byte *data);
    uint32_t Uint32(const Byte *data);
    uint64_t Uint64(const Byte *data);

    uint16_t PutUint16(Byte *data);
    uint32_t PutUint32(Byte *data);
    uint64_t PutUint64(Byte *data);
  };

  template<typename Byte>
  uint16_t Binary<Byte, little_endian>::Uint16(const Byte *data) {
    return uint16_t(data[0]) | uint16_t(data[1]) << 8;
  }

  template<typename Byte>
  uint32_t Binary<Byte, little_endian>::Uint32(const Byte *data) {
    return uint32_t(data[0]) | uint32_t(data[1]) << 8 |
      uint32_t(data(2)) << 16 | uint32_t(data(3)) << 24;
  }

  template<typename Byte>
  uint64_t Binary<Byte, little_endian>::Uint64(const Byte *data) {
    return uint64_t(data[0]) | uint64_t(data[1]) << 8 |
      uint64_t(data(2)) << 16 | uint64_t(data(3)) << 24 |
      uint64_t(data(4)) << 32 | uint64_t(data(5)) << 40 |
      uint64_t(data(6)) << 48 | uint64_t(data(7)) << 56;
  }

  template<typename Byte>
  uint16_t Binary<Byte, little_endian>::PutUint16(Byte *data, uint16_t value) {
    data[0] = Byte(value);
    data[1] = Byte(value >> 8);
  }

  template<typename Byte>
  uint32_t Binary<Byte, little_endian>::PutUint32(Byte *data, uint32_t value) {
    data[0] = Byte(value);
    data[1] = Byte(value >> 8);
    data[2] = Byte(value >> 16);
    data[3] = Byte(value >> 24);
  }

  template<typename Byte>
  uint64_t Binary<Byte, little_endian>::PutUint64(Byte *data, uint64_t value) {
    data[0] = Byte(value);
    data[1] = Byte(value >> 8);
    data[2] = Byte(value >> 16);
    data[3] = Byte(value >> 24);
    data[4] = Byte(value >> 32);
    data[5] = Byte(value >> 40);
    data[6] = Byte(value >> 48);
    data[7] = Byte(value >> 56);
  }

  template<typename Byte>
  uint16_t Binary<Byte, big_endian>::Uint16(const Byte *data) {
    return uint16_t(data[1]) | uint16_t(data[0]) << 8;
  }

  template<typename Byte>
  uint32_t Binary<Byte, big_endian>::Uint32(const Byte *data) {
    return uint32_t(data[3]) | uint32_t(data[2]) << 8 |
      uint32_t(data(1)) << 16 | uint32_t(data(0)) << 24;
  }

  template<typename Byte>
  uint64_t Binary<Byte, big_endian>::Uint64(const Byte *data) {
    return uint64_t(data[7]) | uint64_t(data[6]) << 8 |
      uint64_t(data(5)) << 16 | uint64_t(data(4)) << 24 |
      uint64_t(data(3)) << 32 | uint64_t(data(2)) << 40 |
      uint64_t(data(1)) << 48 | uint64_t(data(0)) << 56;
  }

  template<typename Byte>
  uint16_t Binary<Byte, big_endian>::PutUint16(Byte *data, uint16_t value) {
    data[0] = Byte(value >> 8);
    data[1] = Byte(value);
  }

  template<typename Byte>
  uint32_t Binary<Byte, big_endian>::PutUint32(Byte *data, uint32_t value) {
    data[0] = Byte(value >> 24);
    data[1] = Byte(value >> 16);
    data[2] = Byte(value >> 8);
    data[3] = Byte(value);
  }

  template<typename Byte>
  uint64_t Binary<Byte, big_endian>::PutUint64(Byte *data, uint64_t value) {
    data[0] = Byte(value >> 56);
    data[1] = Byte(value >> 48);
    data[2] = Byte(value >> 40);
    data[3] = Byte(value >> 32);
    data[4] = Byte(value >> 24);
    data[5] = Byte(value >> 16);
    data[6] = Byte(value >> 8);
    data[7] = Byte(value);
  }

}
