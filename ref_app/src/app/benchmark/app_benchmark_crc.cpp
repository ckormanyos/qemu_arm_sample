///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// cd /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/qemu_arm_sample

#include <array>
#include <cstddef>
#include <cstdint>

#define MY_PROGMEM

namespace math { namespace checksums { namespace crc {

template<typename InputIterator>
constexpr auto crc32_mpeg2(InputIterator first, InputIterator last) -> std::uint32_t;

template<typename InputIterator>
constexpr auto crc32_mpeg2(InputIterator first, InputIterator last) -> std::uint32_t
{
  // Name            : CRC-32/MPEG-2
  // Polynomial      : 0x04C11DB7
  // Initial value   : 0xFFFFFFFF
  // Test: '1'...'9' : 0x0376E6E7

  // ISO/IEC 13818-1:2000
  // Recommendation H.222.0 Annex A

  // CRC32/MPEG2 Table based on nibbles.
  constexpr std::array<std::uint32_t, std::size_t { UINT8_C(16) }> table =
  {{
    UINT32_C(0x00000000), UINT32_C(0x04C11DB7),
    UINT32_C(0x09823B6E), UINT32_C(0x0D4326D9),
    UINT32_C(0x130476DC), UINT32_C(0x17C56B6B),
    UINT32_C(0x1A864DB2), UINT32_C(0x1E475005),
    UINT32_C(0x2608EDB8), UINT32_C(0x22C9F00F),
    UINT32_C(0x2F8AD6D6), UINT32_C(0x2B4BCB61),
    UINT32_C(0x350C9B64), UINT32_C(0x31CD86D3),
    UINT32_C(0x3C8EA00A), UINT32_C(0x384FBDBD)
  }};

  // Set the initial value and loop through the input data stream.

  std::uint32_t crc { UINT32_C(0xFFFFFFFF) };

  for( ; first != last; ++first)
  {
    const std::uint_fast8_t the_byte { static_cast<std::uint_fast8_t>((*first) & UINT8_C(0xFF)) };

    std::uint_fast8_t index { };

    // Perform the CRC32/MPEG2 algorithm.
    index =
      static_cast<std::uint_fast8_t>
      (
        static_cast<std::uint_fast8_t>
        (
          static_cast<std::uint_fast8_t>(crc >> static_cast<unsigned>(UINT8_C(28))) ^ static_cast<std::uint_fast8_t>(the_byte >> static_cast<unsigned>(UINT8_C(4)))
        )
        & UINT8_C(0x0F)
      );

    crc =
      static_cast<std::uint32_t>
      (
        static_cast<std::uint32_t>(std::uint32_t(crc << 4U) & UINT32_C(0xFFFFFFF0)) ^ table[index]
      );

    index =
      static_cast<std::uint_fast8_t>
      (
        static_cast<std::uint_fast8_t>
        (
          static_cast<std::uint_fast8_t>(crc >> static_cast<unsigned>(UINT8_C(28))) ^ static_cast<std::uint_fast8_t>(the_byte)
        )
        & UINT8_C(0x0F)
      );

    crc =
      static_cast<std::uint32_t>
      (
        static_cast<std::uint32_t>
        (
          static_cast<std::uint32_t>(crc << static_cast<unsigned>(UINT8_C(4))) & UINT32_C(0xFFFFFFF0)
        )
        ^ table[index]
      );
  }

  return crc;
}

} } } // namespace math::checksums::crc

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC))

namespace app { namespace benchmark {

auto run_crc() -> bool;

} } // namespace app::benchmark

auto app::benchmark::run_crc() -> bool
{
  static constexpr std::array<std::uint8_t, std::size_t { UINT8_C(9) }> app_benchmark_crc_data MY_PROGMEM =
  {{
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  }};

  const std::uint32_t
    app_benchmark_crc
    {
      math::checksums::crc::crc32_mpeg2(app_benchmark_crc_data.cbegin(), app_benchmark_crc_data.cend())
    };

  const bool result_is_ok { app_benchmark_crc == static_cast<std::uint32_t>(UINT32_C(0x0376E6E7)) };

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
constexpr std::uint32_t app_benchmark_standalone_foodcafe { static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE)) };

extern "C"
{
  extern volatile std::uint32_t app_benchmark_standalone_result;

  auto app_benchmark_run_standalone() -> bool;

  [[nodiscard]]
  auto app_benchmark_get_standalone_result() noexcept -> bool;

  auto app_benchmark_run_standalone() -> bool
  {
    bool result_is_ok { true };

    for(unsigned i = 0U; i < 64U; ++i)
    {
      result_is_ok = (app::benchmark::run_crc() && result_is_ok);
    }

    app_benchmark_standalone_result =
      static_cast<std::uint32_t>
      (
        result_is_ok ? app_benchmark_standalone_foodcafe : static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))
      );

    return result_is_ok;
  }

  [[nodiscard]]
  auto app_benchmark_get_standalone_result() noexcept -> bool
  {
    return
    {
      app_benchmark_standalone_result == static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE))
    };
  }
}

auto main() -> int
{
  bool result_is_ok { true };

  result_is_ok = (::app_benchmark_run_standalone       () && result_is_ok);
  result_is_ok = (::app_benchmark_get_standalone_result() && result_is_ok);

  return (result_is_ok ? 0 : -1);
}

extern "C"
{
  volatile std::uint32_t app_benchmark_standalone_result { };
}
#endif // APP_BENCHMARK_STANDALONE_MAIN

#endif // APP_BENCHMARK_TYPE_CRC
