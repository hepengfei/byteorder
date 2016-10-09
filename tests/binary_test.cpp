#include "binary.hpp"

#include <gtest/gtest.h>

TEST(Binary, Uint16) {
  uint16_t value = 0x1234;
  uint16_t valueBigEndian = 0x3412;

  kb::Binary<kb::host_byteorder> little;
  uint16_t decode = little.Uint16((char*)&value);
  ASSERT_EQ(value, decode);

  uint16_t encode = 0;
  little.PutUint16((char*)&encode, value);
  ASSERT_EQ(value, encode);

  kb::Binary<kb::big_endian> big;
  decode = big.Uint16((char*)&value);
  ASSERT_EQ(valueBigEndian, decode);

  encode = 0;
  big.PutUint16((char*)&encode, value);
  ASSERT_EQ(valueBigEndian, encode);
}
