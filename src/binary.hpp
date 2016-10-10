#pragma once

#include <stdint.h>

namespace kb {
  namespace binary {
    struct LittleEndian;
    struct BigEndian;
    typedef BigEndian Network;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    typedef LittleEndian Host;
#else
    typedef BigEndian Host;
#endif


    struct LittleEndian {
      static const bool IsLittleEndian = true;

      static uint16_t Uint16(const void *data);
      static uint32_t Uint32(const void *data);
      static uint64_t Uint64(const void *data);

      static void PutUint16(void *data, uint16_t value);
      static void PutUint32(void *data, uint32_t value);
      static void PutUint64(void *data, uint64_t value);
    };

    struct BigEndian {
      static const bool IsLittleEndian = false;

      static uint16_t Uint16(const void *data);
      static uint32_t Uint32(const void *data);
      static uint64_t Uint64(const void *data);

      static void PutUint16(void *data, uint16_t value);
      static void PutUint32(void *data, uint32_t value);
      static void PutUint64(void *data, uint64_t value);
    };

    inline
    uint16_t LittleEndian::Uint16(const void *data) {
      const uint8_t *d = (const uint8_t *)data;
      return uint16_t(d[0]) | uint16_t(d[1]) << 8;
    }

    inline
    uint32_t LittleEndian::Uint32(const void *data) {
      const uint8_t *d = (const uint8_t *)data;
      return uint32_t(d[0]) | uint32_t(d[1]) << 8 |
        uint32_t(d[2]) << 16 | uint32_t(d[3]) << 24;
    }

    inline
    uint64_t LittleEndian::Uint64(const void *data) {
      const uint8_t *d = (const uint8_t *)data;
      return uint64_t(d[0]) | uint64_t(d[1]) << 8 |
        uint64_t(d[2]) << 16 | uint64_t(d[3]) << 24 |
        uint64_t(d[4]) << 32 | uint64_t(d[5]) << 40 |
        uint64_t(d[6]) << 48 | uint64_t(d[7]) << 56;
    }

    inline
    void LittleEndian::PutUint16(void *data, uint16_t value) {
      uint8_t *d = (uint8_t *)data;
      d[0] = value;
      d[1] = value >> 8;
    }

    inline
    void LittleEndian::PutUint32(void *data, uint32_t value) {
      uint8_t *d = (uint8_t *)data;
      d[0] = value;
      d[1] = value >> 8;
      d[2] = value >> 16;
      d[3] = value >> 24;
    }

    inline
    void LittleEndian::PutUint64(void *data, uint64_t value) {
      uint8_t *d = (uint8_t *)data;
      d[0] = value;
      d[1] = value >> 8;
      d[2] = value >> 16;
      d[3] = value >> 24;
      d[4] = value >> 32;
      d[5] = value >> 40;
      d[6] = value >> 48;
      d[7] = value >> 56;
    }

    inline
    uint16_t BigEndian::Uint16(const void *data) {
      const uint8_t *d = (const uint8_t *)data;
      return uint16_t(d[1]) | uint16_t(d[0]) << 8;
    }

    inline
    uint32_t BigEndian::Uint32(const void *data) {
      const uint8_t *d = (const uint8_t *)data;
      return uint32_t(d[3]) | uint32_t(d[2]) << 8 |
        uint32_t(d[1]) << 16 | uint32_t(d[0]) << 24;
    }

    inline
    uint64_t BigEndian::Uint64(const void *data) {
      const uint8_t *d = (const uint8_t *)data;
      return uint64_t(d[7]) | uint64_t(d[6]) << 8 |
        uint64_t(d[5]) << 16 | uint64_t(d[4]) << 24 |
        uint64_t(d[3]) << 32 | uint64_t(d[2]) << 40 |
        uint64_t(d[1]) << 48 | uint64_t(d[0]) << 56;
    }

    inline
    void BigEndian::PutUint16(void *data, uint16_t value) {
      uint8_t *d = (uint8_t *)data;
      d[0] = value >> 8;
      d[1] = value;
    }

    inline
    void BigEndian::PutUint32(void *data, uint32_t value) {
      uint8_t *d = (uint8_t *)data;
      d[0] = value >> 24;
      d[1] = value >> 16;
      d[2] = value >> 8;
      d[3] = value;
    }

    inline
    void BigEndian::PutUint64(void *data, uint64_t value) {
      uint8_t *d = (uint8_t *)data;
      d[0] = value >> 56;
      d[1] = value >> 48;
      d[2] = value >> 40;
      d[3] = value >> 32;
      d[4] = value >> 24;
      d[5] = value >> 16;
      d[6] = value >> 8;
      d[7] = value;
    }

    struct Encoder {
      
    };
    struct Decoder {
      
    };
  }


}
