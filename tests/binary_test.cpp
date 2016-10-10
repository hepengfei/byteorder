#include "binary.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Binary, Uint16) {
  const char data[3] = { 0x12, 0x34, 0x0 };
  char buffer[3] = { 0x0 };
  uint16_t valueLittleEndian = 0x3412;
  uint16_t valueBigEndian = 0x1234;

  ASSERT_EQ(valueLittleEndian, kb::binary::LittleEndian::Uint16(data));
  ASSERT_EQ(valueLittleEndian, kb::binary::Host::Uint16(data));

  ASSERT_EQ(valueBigEndian, kb::binary::BigEndian::Uint16(data));
  ASSERT_EQ(valueBigEndian, kb::binary::Network::Uint16(data));

  kb::binary::LittleEndian::PutUint16(buffer, valueLittleEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));

  kb::binary::BigEndian::PutUint16(buffer, valueBigEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));
}

TEST(Binary, Uint32) {
  const char data[5] = { 0x12, 0x34, 0x56, 0x78, 0x0 };
  char buffer[5] = { 0x0 };
  uint32_t valueLittleEndian = 0x78563412;
  uint32_t valueBigEndian = 0x12345678;

  ASSERT_EQ(valueLittleEndian, kb::binary::LittleEndian::Uint32(data));
  ASSERT_EQ(valueLittleEndian, kb::binary::Host::Uint32(data));

  ASSERT_EQ(valueBigEndian, kb::binary::BigEndian::Uint32(data));
  ASSERT_EQ(valueBigEndian, kb::binary::Network::Uint32(data));

  kb::binary::LittleEndian::PutUint32(buffer, valueLittleEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));

  kb::binary::BigEndian::PutUint32(buffer, valueBigEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));
}
TEST(Binary, Uint64) {
  const unsigned char data[9] = { 0x12, 0x34, 0x56, 0x78,
                                  0x9a, 0xbc, 0xde, 0xf0, 0x0 };
  unsigned char buffer[9] = { 0x0 };
  uint64_t valueLittleEndian = 0xf0debc9a78563412ULL;
  uint64_t valueBigEndian = 0x123456789abcdef0ULL;

  ASSERT_EQ(valueLittleEndian, kb::binary::LittleEndian::Uint64(data));
  ASSERT_EQ(valueLittleEndian, kb::binary::Host::Uint64(data));

  ASSERT_EQ(valueBigEndian, kb::binary::BigEndian::Uint64(data));
  ASSERT_EQ(valueBigEndian, kb::binary::Network::Uint64(data));

  kb::binary::LittleEndian::PutUint64(buffer, valueLittleEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));

  kb::binary::BigEndian::PutUint64(buffer, valueBigEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));
}
