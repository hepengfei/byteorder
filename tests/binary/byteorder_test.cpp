#include "binary/byteorder.hpp"

#include <gmock/gmock.h>

using namespace kb::binary;

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

  ASSERT_THAT(byteorder::CastFrom<Network>(bigEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT(byteorder::CastFrom<Host>(littleEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT(byteorder::CastTo<Network>(littleEndian),
              testing::Eq(bigEndian));

  ASSERT_THAT(byteorder::CastTo<Host>(littleEndian),
              testing::Eq(littleEndian));

  ASSERT_THAT((byteorder::Cast<Host, Host>(littleEndian)),
              testing::Eq(littleEndian));

  ASSERT_THAT((byteorder::Cast<Host, Network>(littleEndian)),
              testing::Eq(bigEndian));

  ASSERT_THAT((byteorder::Cast<Network, Host>(bigEndian)),
              testing::Eq(littleEndian));

  ASSERT_THAT((byteorder::Cast<Network, Network>(bigEndian)),
              testing::Eq(bigEndian));
}
