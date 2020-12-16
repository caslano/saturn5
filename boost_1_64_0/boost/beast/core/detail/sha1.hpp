//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SHA1_HPP
#define BOOST_BEAST_DETAIL_SHA1_HPP

#include <boost/beast/core/detail/config.hpp>
#include <cstdint>
#include <cstddef>

// Based on https://github.com/vog/sha1
/*
    Original authors:
        Steve Reid (Original C Code)
        Bruce Guenter (Small changes to fit into bglibs)
        Volker Grabsch (Translation to simpler C++ Code)
        Eugene Hopkinson (Safety improvements)
        Vincent Falco (beast adaptation)
*/

namespace boost {
namespace beast {
namespace detail {

namespace sha1 {

static std::size_t constexpr BLOCK_INTS = 16;
static std::size_t constexpr BLOCK_BYTES = 64;
static std::size_t constexpr DIGEST_BYTES = 20;

} // sha1

struct sha1_context
{
    static unsigned int constexpr block_size = sha1::BLOCK_BYTES;
    static unsigned int constexpr digest_size = 20;

    std::size_t buflen;
    std::size_t blocks;
    std::uint32_t digest[5];
    std::uint8_t buf[block_size];
};

BOOST_BEAST_DECL
void
init(sha1_context& ctx) noexcept;

BOOST_BEAST_DECL
void
update(
    sha1_context& ctx,
    void const* message,
    std::size_t size) noexcept;

BOOST_BEAST_DECL
void
finish(
    sha1_context& ctx,
    void* digest) noexcept;

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/sha1.ipp>
#endif

#endif

/* sha1.hpp
HKR5h+p6/SdxjzL0s14SzD6T/GnG/hLqh2OvNxnu10/Y0M5tgvS32QRBPmxrjNeyXvj1h/SwXsRwfSPGKnoNsjes+2uQ/9/WGp+tNcU/K5U1tiPixt77219/W107bd49Pz36kVBrmT/8tcDua3tDrRE+e2t+ffM1fCfiGL/CMV+zmfM1HwdGAK9VgXWY7ZQbRTlzHWYT+MKBnwJGc14+lvPxccC7gUM4T59G/3TgTmAG3Xre8J3Q6atn+jYxfddQbi8onXKvUC5B5v1xcX5vGOf1pgGvBJ7Peb2Pcl4PpK7m2eGlXP+1DngNcD3wemAFz2TeAPwU5/k+zXm++4HVwD2c73uY8T0OvAL4S7qRXmSCY2DgDUxvP8mf71rIdYsX8YzzJcCJXM81neu5ZnL+cg7wEuBcru9aCLwUuIThy7k+rJ7rwjbTn+v8OFZEvWE69Do/rp8YwfUT44H3A6cCd3N+tBk4n+u7yrmu62PAR7heeC/wRuCjvF+r4piF46oKD1DW5/muTJbTGOYvm/mbCCwBTgKWAecBa4BTmK9czsNO4/3OBd7MectHOG/5GOWe5HzkDzgf+QxwNvB54Bzgr3gW+GHyvwIcC4z0iFuXn3o/dPkNYvkNYfkls/yGs/xSmL+RzN8Ill8qyy+N5TeS5ZfIfCYBN9Nfr3NgOtKZDnOe/nbOu27n/PgdwOF0c30vn5XQAeXN9b03UW4b2+0nmJ9PMj83c73NLcDz6N4Zpro0z9mV88LN+UrnXGUuaM3s0POQnIM0zxTXc4lZIHMO8RbgXhDnB2Vu8BTIMSfIuUA9D2jM+/EcchDn+WR+j3N5eg6vCuQ4o5xzdTI/x7k5hAfm4mQeLgvkNu92AMT5NmOezX6+eT3POA/Mm3U+Zxa/UObK9DzZYJCeE3OZD+NcmMyDZQOD577c57maQJjbCnlmujk3lQfyz0Wt4dxTE+gU5l9S7o9S+aAq0HZQC+gQ6AQoZTfOW9/dO0fTe/VevVfv1Xv1Xr1X7/Uv9q4ErKoiCs8DURJCQEQQQwRTUVTEJSwzXKMwwyUjswAVhEJ8sZSt0m677XtR2b7Rbrvtthmt2irte2GZ0d5/z/vfcO9797Ik0vYu3/C/mTkzd86Z5d4zM/dM4PrvXp22/l/cMev/NycrvXb7QpD+hlrW4TKA30GhTv/culZA662O51LvJ/QRLs6ZM32qPlsW62XVJvtnjB8o/unwzxV/gisa9Cmk5/mXen1sttCkyD1ymQf8prW9Uk0/A/G5Et9X6Gdq+iSef+ihxy1MZ/CTxnQGfzRpFWw9VZYe4TnPnjw+KrR7Q27bMQwcfGGEzcfq03DLOlBilIEdcw475IkwyMd05n6KhFFmpM3T63MiF71mB34kDKQyZz5ayox4n3WktcFKrhO5jrSc60j1X9i2DS4jOa8jfSDpKlQG/k/V60jMr4V1pN5fWteR9v6y49aRen1pWUfS/eKiEH6TRXtgxUAXFk5qQG/ineaI/XlOJs9XCf2errkqTF0N9zDcFrhoDBfkn3n2Z1+xrlHn6PhElcy+coX493UdiPLeBPcU3O9wfVzhqrn/uPUCbDL7z6WSLt9VjP93wr0I1xVtNtnVTbFP8V4JLbb7uK9k/RtUCfosu6slLHwbt3mw5NfmySfr82Eph1IxPvsNVna1b8sFX9vVZ8v7LCq+tm3HzMu5HV//tbUdb/y649rxtV/rdmw9J47r6pFBXFcHftsT/m9s+cayqJzQ78f7QPKeKuk2uR7EPTbB7eLqqg6DOwvuUTjKgvnHm2zlSbZs04yHRAeybQ4U/0+uJ4z/cJPRppbDXQj3DJyvTGMp01pJF+EaD4rp+OI5mrI=
*/