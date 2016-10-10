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

TEST(Decoder, Integers) {
  const unsigned char data[] = { 0x12, 0x34, 0x56, 0x78,
                                 0x9a, 0xbc, 0xde, 0xf0 };
  const size_t len = sizeof(data);

  typedef kb::binary::Decoder<kb::binary::LittleEndian> LittleEndianDecoder;

  LittleEndianDecoder decoder1(data, len);
  for (size_t i = 0; i < len; ++i) {
    ASSERT_THAT(decoder1.Uint8(), testing::Eq(data[i]));
  }

  LittleEndianDecoder decoder2(data, len);
  ASSERT_THAT(decoder2.Uint16(), testing::Eq(0x3412));
  ASSERT_THAT(decoder2.Uint16(), testing::Eq(0x7856));
  ASSERT_THAT(decoder2.Uint16(), testing::Eq(0xbc9a));
  ASSERT_THAT(decoder2.Uint16(), testing::Eq(0xf0de));
  ASSERT_THAT(decoder2.Uint16(), testing::Eq(0x0));
}

TEST(Decoder, String) {
  const unsigned char data[] = { 0x5, 0x0, 0x0, 0x0,
                                 'H', 'e', 'l', 'l', 'o' };
  const size_t len = sizeof(data);

  typedef kb::binary::Decoder<kb::binary::LittleEndian> LittleEndianDecoder;

  LittleEndianDecoder decoder1(data, len);
  std::string str1 = decoder1.String();
  ASSERT_THAT(str1, testing::Eq("Hello"));

  LittleEndianDecoder decoder2(data, len);
  uint32_t len2 = decoder2.Uint32();
  ASSERT_THAT(len2, testing::Eq(5));
  std::string str2 = decoder2.String(len2);
  ASSERT_THAT(str2, testing::Eq("Hello"));
}

TEST(Decoder, Varint32Rtmfp) {
  const unsigned char data[] = {
    0x5,
    0x85, 0x5,
    0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x5 // bad data
  };
  const size_t len = sizeof(data);
  const uint32_t value[] = {
    0x5,
    (0x5 << 7 | 0x5),
    (0x5 << 14 | 0x5 << 7 | 0x5),
    (0x5 << 21 | 0x5 << 14 | 0x5 << 7 | 0x5),
    0                           // for bad data
  };

  typedef kb::binary::Decoder<kb::binary::LittleEndian> LittleEndianDecoder;

  LittleEndianDecoder decoder1(data, len);
  for (size_t i = 0; i < sizeof(value) / sizeof(value[0]); ++i) {
    ASSERT_THAT(decoder1.Varint32Rtmfp(), value[i]);
  }
  ASSERT_THAT(decoder1.Error(), testing::Eq(kb::binary::E_BAD_VARINT));
}

TEST(Decoder, Varint64Rtmfp) {
  const unsigned char data[] = {
    0x5,
    0x85, 0x5,
    0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x5,
    0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x5, // bad data
  };
  const size_t len = sizeof(data);
  const uint64_t value[] = {
    0x5ULL,
    (0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 21 | 0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 28 | 0x5ULL << 21 | 0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 35 | 0x5ULL << 28 | 0x5ULL << 21 | 0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 42 | 0x5ULL << 35 | 0x5ULL << 28 | 0x5ULL << 21 | 0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 49 | 0x5ULL << 42 | 0x5ULL << 35 | 0x5ULL << 28 | 0x5ULL << 21 | 0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    (0x5ULL << 56 | 0x5ULL << 49 | 0x5ULL << 42 | 0x5ULL << 35 | 0x5ULL << 28 | 0x5ULL << 21 | 0x5ULL << 14 | 0x5ULL << 7 | 0x5ULL),
    0                           // for bad data
  };

  typedef kb::binary::Decoder<kb::binary::LittleEndian> LittleEndianDecoder;

  LittleEndianDecoder decoder1(data, len);
  for (size_t i = 0; i < sizeof(value) / sizeof(value[0]); ++i) {
    ASSERT_THAT(decoder1.Varint64Rtmfp(), value[i]) << "i = " << i;
  }
  ASSERT_THAT(decoder1.Error(), testing::Eq(kb::binary::E_BAD_VARINT));
}
