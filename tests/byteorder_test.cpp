#include "byteorder.hpp"

#include <gmock/gmock.h>

TEST(byteorder, EndianUint16) {
  const char data[3] = { 0x12, 0x34, 0x0 };
  char buffer[3] = { 0x0 };
  uint16_t valueLittleEndian = 0x3412;
  uint16_t valueBigEndian = 0x1234;

  ASSERT_EQ(valueLittleEndian, byteorder::LittleEndian::Uint16(data));
  ASSERT_EQ(valueLittleEndian, byteorder::Host::Uint16(data));

  ASSERT_EQ(valueBigEndian, byteorder::BigEndian::Uint16(data));
  ASSERT_EQ(valueBigEndian, byteorder::Network::Uint16(data));

  byteorder::LittleEndian::PutUint16(buffer, valueLittleEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));

  byteorder::BigEndian::PutUint16(buffer, valueBigEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));
}

TEST(byteorder, EndianUint32) {
  const char data[5] = { 0x12, 0x34, 0x56, 0x78, 0x0 };
  char buffer[5] = { 0x0 };
  uint32_t valueLittleEndian = 0x78563412;
  uint32_t valueBigEndian = 0x12345678;

  ASSERT_EQ(valueLittleEndian, byteorder::LittleEndian::Uint32(data));
  ASSERT_EQ(valueLittleEndian, byteorder::Host::Uint32(data));

  ASSERT_EQ(valueBigEndian, byteorder::BigEndian::Uint32(data));
  ASSERT_EQ(valueBigEndian, byteorder::Network::Uint32(data));

  byteorder::LittleEndian::PutUint32(buffer, valueLittleEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));

  byteorder::BigEndian::PutUint32(buffer, valueBigEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));
}
TEST(byteorder, EndianUint64) {
  const unsigned char data[9] = { 0x12, 0x34, 0x56, 0x78,
                                  0x9a, 0xbc, 0xde, 0xf0, 0x0 };
  unsigned char buffer[9] = { 0x0 };
  uint64_t valueLittleEndian = 0xf0debc9a78563412ULL;
  uint64_t valueBigEndian = 0x123456789abcdef0ULL;

  ASSERT_EQ(valueLittleEndian, byteorder::LittleEndian::Uint64(data));
  ASSERT_EQ(valueLittleEndian, byteorder::Host::Uint64(data));

  ASSERT_EQ(valueBigEndian, byteorder::BigEndian::Uint64(data));
  ASSERT_EQ(valueBigEndian, byteorder::Network::Uint64(data));

  byteorder::LittleEndian::PutUint64(buffer, valueLittleEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));

  byteorder::BigEndian::PutUint64(buffer, valueBigEndian);
  ASSERT_THAT(buffer, testing::ElementsAreArray(data));
}

TEST(byteorder, Swap) {
  uint8_t uint8 = 0xf0;
  uint8_t uint8Swap = 0xf0;
  ASSERT_THAT(byteorder::Swap(uint8), testing::Eq(uint8Swap));

  uint16_t uint16 = 0x3412;
  uint16_t uint16Swap = 0x1234;
  ASSERT_THAT(byteorder::Swap(uint16), testing::Eq(uint16Swap));

  uint32_t uint32 = 0x78563412;
  uint32_t uint32Swap = 0x12345678;
  ASSERT_THAT(byteorder::Swap(uint32), testing::Eq(uint32Swap));

  uint64_t uint64 = 0xf0debc9a78563412ULL;
  uint64_t uint64Swap = 0x123456789abcdef0ULL;
  ASSERT_THAT(byteorder::Swap(uint64), testing::Eq(uint64Swap));
}

TEST(byteorder, Cast) {
  uint64_t littleEndian = 0xf0debc9a78563412ULL;
  uint64_t bigEndian = 0x123456789abcdef0ULL;

  ASSERT_THAT(byteorder::Hton(littleEndian),
              testing::Eq(bigEndian));

  ASSERT_THAT(byteorder::Ntoh(bigEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT(byteorder::CastFrom<byteorder::Network>(bigEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT(byteorder::CastFrom<byteorder::Host>(littleEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT(byteorder::CastTo<byteorder::Network>(littleEndian),
              testing::Eq(bigEndian));

  ASSERT_THAT(byteorder::CastTo<byteorder::Host>(littleEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT((byteorder::Cast<byteorder::Host, byteorder::Host>(littleEndian)),
              testing::Eq(littleEndian));

  ASSERT_THAT((byteorder::Cast<byteorder::Host, byteorder::Network>(littleEndian)),
              testing::Eq(bigEndian));

  ASSERT_THAT((byteorder::Cast<byteorder::Network, byteorder::Host>(bigEndian)),
              testing::Eq(littleEndian));

  ASSERT_THAT((byteorder::Cast<byteorder::Network, byteorder::Network>(bigEndian)),
              testing::Eq(bigEndian));
}
