#pragma once

#include <stdint.h>
#include <stddef.h>

#include <string>

namespace binary {
  enum {
    E_NIL = 0,
    E_OVERFLOW,
    E_BAD_VARINT,
  };

  template <typename Endian>
  struct Decoder {
    Decoder(const void *data, size_t len)
      : _data((const uint8_t*)data), _len(len), _offset(0), _error(0) {}

    uint8_t Uint8();
    uint16_t Uint16();
    uint32_t Uint32();
    uint64_t Uint64();

    int8_t Int8() { return int8_t(Uint8()); }
    int16_t Int16() { return int16_t(Uint16()); }
    int32_t Int32() { return int32_t(Uint32()); }
    int64_t Int64() { return int64_t(Uint64()); }

    uint32_t Varint32Rtmfp();
    uint64_t Varint64Rtmfp();

    const uint8_t *Data(size_t len);

    std::string String(size_t len) {
      const char *data = (const char*)Data(len);
      if (data == NULL) {
        return std::string();
      }
      return std::string(data, len);
    }

    std::string String() { return String(Uint32()); }

    size_t Used() const { return _offset; }
    size_t Left() const { return _len - _offset; }
    void Skip(size_t bytes) { _offset += bytes; }
    int Error() const { return _error; }

  protected:
    void setError(int error) { _error = error; }

  private:
    const uint8_t *_data;
    size_t _len;
    size_t _offset;
    int _error;
  };

  template <typename Endian>
  inline
  uint8_t Decoder<Endian>::Uint8() {
    if (Error()) {
      return 0;
    }
    if (Left() < 1) {
      setError(E_OVERFLOW);
      return 0;
    }

    uint8_t value = *(_data + _offset);
    Skip(1);
    return value;
  }

  template <typename Endian>
  inline
  uint16_t Decoder<Endian>::Uint16() {
    if (Error()) {
      return 0;
    }
    if (Left() < 2) {
      setError(E_OVERFLOW);
      return 0;
    }

    uint16_t value = Endian::Uint16(_data + _offset);
    Skip(2);
    return value;
  }

  template <typename Endian>
  inline
  uint32_t Decoder<Endian>::Uint32() {
    if (Error()) {
      return 0;
    }
    if (Left() < 4) {
      setError(E_OVERFLOW);
      return 0;
    }

    uint32_t value = Endian::Uint32(_data + _offset);
    Skip(4);
    return value;
  }

  template <typename Endian>
  inline
  uint64_t Decoder<Endian>::Uint64() {
    if (Error()) {
      return 0;
    }
    if (Left() < 8) {
      setError(E_OVERFLOW);
      return 0;
    }

    uint64_t value = Endian::Uint64(_data + _offset);
    Skip(8);
    return value;
  }

  template <typename Endian>
  inline
  const uint8_t *Decoder<Endian>::Data(size_t len) {
    if (Error()) {
      return NULL;
    }
    if (Left() < len) {
      setError(E_OVERFLOW);
      return NULL;
    }
    const uint8_t *value = _data + _offset;
    Skip(len);
    return value;
  }

  template <typename Endian>
  inline
  uint32_t Decoder<Endian>::Varint32Rtmfp() {
    uint32_t value = 0;
    const int maxBytes = 4;
    for (int i = 0; i < maxBytes && !Error(); ++i) {
      uint8_t bit7 = Uint8();
      value = (value << 7) | (bit7 & 0x7F);

      if ((bit7 & 0x80) == 0) {
        return value;
      }
    }

    if (!Error()) {
      setError(E_BAD_VARINT);
    }

    return 0;
  }

  template <typename Endian>
  inline
  uint64_t Decoder<Endian>::Varint64Rtmfp() {
    uint64_t value = 0;
    const int maxBytes = 9;
    for (int i = 0; i < maxBytes && !Error(); ++i) {
      uint8_t bit7 = Uint8();
      value = (value << 7) | (bit7 & 0x7F);

      if ((bit7 & 0x80) == 0) {
        return value;
      }
    }

    if (!Error()) {
      setError(E_BAD_VARINT);
    }

    return 0;
  }

} // binary

