// Copyright 2018 Ulf Adams
//
// The contents of this file may be used under the terms of the Apache License,
// Version 2.0.
//
//    (See accompanying file LICENSE-Apache or copy at
//     http://www.apache.org/licenses/LICENSE-2.0)
//
// Alternatively, the contents of this file may be used under the terms of
// the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE-Boost or copy at
//     https://www.boost.org/LICENSE_1_0.txt)
//
// Unless required by applicable law or agreed to in writing, this software
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.

/*
    This is a derivative work
*/

#ifndef BOOST_JSON_DETAIL_RYU_DETAIL_D2S_HPP
#define BOOST_JSON_DETAIL_RYU_DETAIL_D2S_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/detail/ryu/detail/common.hpp>

// Only include the full table if we're not optimizing for size.
#if !defined(BOOST_JSON_RYU_OPTIMIZE_SIZE)
#include <boost/json/detail/ryu/detail/d2s_full_table.hpp>
#endif
#if defined(BOOST_JSON_RYU_HAS_UINT128)
typedef __uint128_t uint128_t;
#else
#include <boost/json/detail/ryu/detail/d2s_intrinsics.hpp>
#endif

BOOST_JSON_NS_BEGIN
namespace detail {

namespace ryu {
namespace detail {

constexpr int DOUBLE_POW5_INV_BITCOUNT = 122;
constexpr int DOUBLE_POW5_BITCOUNT = 121;

#if defined(BOOST_JSON_RYU_OPTIMIZE_SIZE)

constexpr int POW5_TABLE_SIZE = 26;

inline
std::uint64_t const
(&DOUBLE_POW5_TABLE() noexcept)[POW5_TABLE_SIZE]
{
    static constexpr std::uint64_t arr[26] = {
    1ull, 5ull, 25ull, 125ull, 625ull, 3125ull, 15625ull, 78125ull, 390625ull,
    1953125ull, 9765625ull, 48828125ull, 244140625ull, 1220703125ull, 6103515625ull,
    30517578125ull, 152587890625ull, 762939453125ull, 3814697265625ull,
    19073486328125ull, 95367431640625ull, 476837158203125ull,
    2384185791015625ull, 11920928955078125ull, 59604644775390625ull,
    298023223876953125ull //, 1490116119384765625ull
    };
    return arr;
}

inline
std::uint64_t const
(&DOUBLE_POW5_SPLIT2() noexcept)[13][2]
{
    static constexpr std::uint64_t arr[13][2] = {
    {                    0u,  72057594037927936u },
    { 10376293541461622784u,  93132257461547851u },
    { 15052517733678820785u, 120370621524202240u },
    {  6258995034005762182u,  77787690973264271u },
    { 14893927168346708332u, 100538234169297439u },
    {  4272820386026678563u, 129942622070561240u },
    {  7330497575943398595u,  83973451344588609u },
    { 18377130505971182927u, 108533142064701048u },
    { 10038208235822497557u, 140275798336537794u },
    {  7017903361312433648u,  90651109995611182u },
    {  6366496589810271835u, 117163813585596168u },
    {  9264989777501460624u,  75715339914673581u },
    { 17074144231291089770u,  97859783203563123u }};
    return arr;
}

// Unfortunately, the results are sometimes off by one. We use an additional
// lookup table to store those cases and adjust the result.
inline
std::uint32_t const
(&POW5_OFFSETS() noexcept)[13]
{
    static constexpr std::uint32_t arr[13] = {
        0x00000000, 0x00000000, 0x00000000, 0x033c55be, 0x03db77d8, 0x0265ffb2,
        0x00000800, 0x01a8ff56, 0x00000000, 0x0037a200, 0x00004000, 0x03fffffc,
        0x00003ffe};
    return arr;
}

inline
std::uint64_t const
(&DOUBLE_POW5_INV_SPLIT2() noexcept)[13][2]
{
    static constexpr std::uint64_t arr[13][2] = {
    {                    1u, 288230376151711744u },
    {  7661987648932456967u, 223007451985306231u },
    { 12652048002903177473u, 172543658669764094u },
    {  5522544058086115566u, 266998379490113760u },
    {  3181575136763469022u, 206579990246952687u },
    {  4551508647133041040u, 159833525776178802u },
    {  1116074521063664381u, 247330401473104534u },
    { 17400360011128145022u, 191362629322552438u },
    {  9297997190148906106u, 148059663038321393u },
    { 11720143854957885429u, 229111231347799689u },
    { 15401709288678291155u, 177266229209635622u },
    {  3003071137298187333u, 274306203439684434u },
    { 17516772882021341108u, 212234145163966538u }};
    return arr;
}

inline
std::uint32_t const
(&POW5_INV_OFFSETS() noexcept)[20]
{
    static constexpr std::uint32_t arr[20] = {
    0x51505404, 0x55054514, 0x45555545, 0x05511411, 0x00505010, 0x00000004,
    0x00000000, 0x00000000, 0x55555040, 0x00505051, 0x00050040, 0x55554000,
    0x51659559, 0x00001000, 0x15000010, 0x55455555, 0x41404051, 0x00001010,
    0x00000014, 0x00000000};
    return arr;
}

#if defined(BOOST_JSON_RYU_HAS_UINT128)

// Computes 5^i in the form required by Ryu, and stores it in the given pointer.
inline
void
double_computePow5(
    const std::uint32_t i,
    std::uint64_t* const result)
{
    const std::uint32_t base = i / POW5_TABLE_SIZE;
    const std::uint32_t base2 = base * POW5_TABLE_SIZE;
    const std::uint32_t offset = i - base2;
    const std::uint64_t* const mul = DOUBLE_POW5_SPLIT2()[base];
    if (offset == 0)
    {
        result[0] = mul[0];
        result[1] = mul[1];
        return;
    }
    const std::uint64_t m = DOUBLE_POW5_TABLE()[offset];
    const uint128_t b0 = ((uint128_t)m) * mul[0];
    const uint128_t b2 = ((uint128_t)m) * mul[1];
    const std::uint32_t delta = pow5bits(i) - pow5bits(base2);
    const uint128_t shiftedSum = (b0 >> delta) + (b2 << (64 - delta)) + ((POW5_OFFSETS()[base] >> offset) & 1);
    result[0] = (std::uint64_t)shiftedSum;
    result[1] = (std::uint64_t)(shiftedSum >> 64);
}

// Computes 5^-i in the form required by Ryu, and stores it in the given pointer.
inline
void
double_computeInvPow5(
    const std::uint32_t i,
    std::uint64_t* const result)
{
    const std::uint32_t base = (i + POW5_TABLE_SIZE - 1) / POW5_TABLE_SIZE;
    const std::uint32_t base2 = base * POW5_TABLE_SIZE;
    const std::uint32_t offset = base2 - i;
    const std::uint64_t* const mul = DOUBLE_POW5_INV_SPLIT2()[base]; // 1/5^base2
    if (offset == 0)
    {
        result[0] = mul[0];
        result[1] = mul[1];
        return;
    }
    const std::uint64_t m = DOUBLE_POW5_TABLE()[offset]; // 5^offset
    const uint128_t b0 = ((uint128_t)m) * (mul[0] - 1);
    const uint128_t b2 = ((uint128_t)m) * mul[1]; // 1/5^base2 * 5^offset = 1/5^(base2-offset) = 1/5^i
    const std::uint32_t delta = pow5bits(base2) - pow5bits(i);
    const uint128_t shiftedSum =
        ((b0 >> delta) + (b2 << (64 - delta))) + 1 + ((POW5_INV_OFFSETS()[i / 16] >> ((i % 16) << 1)) & 3);
    result[0] = (std::uint64_t)shiftedSum;
    result[1] = (std::uint64_t)(shiftedSum >> 64);
}

#else // defined(BOOST_JSON_RYU_HAS_UINT128)

// Computes 5^i in the form required by Ryu, and stores it in the given pointer.
inline
void
double_computePow5(
    const std::uint32_t i,
    std::uint64_t* const result)
{
    const std::uint32_t base = i / POW5_TABLE_SIZE;
    const std::uint32_t base2 = base * POW5_TABLE_SIZE;
    const std::uint32_t offset = i - base2;
    const std::uint64_t* const mul = DOUBLE_POW5_SPLIT2()[base];
    if (offset == 0)
    {
        result[0] = mul[0];
        result[1] = mul[1];
        return;
    }
    std::uint64_t const m = DOUBLE_POW5_TABLE()[offset];
    std::uint64_t high1;
    std::uint64_t const low1 = umul128(m, mul[1], &high1);
    std::uint64_t high0;
    std::uint64_t const low0 = umul128(m, mul[0], &high0);
    std::uint64_t const sum = high0 + low1;
    if (sum < high0)
        ++high1; // overflow into high1
    // high1 | sum | low0
    std::uint32_t const delta = pow5bits(i) - pow5bits(base2);
    result[0] = shiftright128(low0, sum, delta) + ((POW5_OFFSETS()[base] >> offset) & 1);
    result[1] = shiftright128(sum, high1, delta);
}

// Computes 5^-i in the form required by Ryu, and stores it in the given pointer.
inline
void
double_computeInvPow5(
    const std::uint32_t i,
    std::uint64_t* const result)
{
    const std::uint32_t base = (i + POW5_TABLE_SIZE - 1) / POW5_TABLE_SIZE;
    const std::uint32_t base2 = base * POW5_TABLE_SIZE;
    const std::uint32_t offset = base2 - i;
    const std::uint64_t* const mul = DOUBLE_POW5_INV_SPLIT2()[base]; // 1/5^base2
    if (offset == 0)
    {
        result[0] = mul[0];
        result[1] = mul[1];
        return;
    }
    std::uint64_t const m = DOUBLE_POW5_TABLE()[offset];
    std::uint64_t high1;
    std::uint64_t const low1 = umul128(m, mul[1], &high1);
    std::uint64_t high0;
    std::uint64_t const low0 = umul128(m, mul[0] - 1, &high0);
    std::uint64_t const sum = high0 + low1;
    if (sum < high0)
        ++high1; // overflow into high1
    // high1 | sum | low0
    std::uint32_t const delta = pow5bits(base2) - pow5bits(i);
    result[0] = shiftright128(low0, sum, delta) + 1 + ((POW5_INV_OFFSETS()[i / 16] >> ((i % 16) << 1)) & 3);
    result[1] = shiftright128(sum, high1, delta);
}

#endif // defined(BOOST_JSON_RYU_HAS_UINT128)

#endif // defined(BOOST_JSON_RYU_OPTIMIZE_SIZE)

} // detail
} // ryu

} // detail
BOOST_JSON_NS_END

#endif

/* d2s.hpp
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
*/