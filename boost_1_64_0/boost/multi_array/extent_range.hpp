// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_EXTENT_RANGE_HPP
#define BOOST_MULTI_ARRAY_EXTENT_RANGE_HPP

#include <utility>

namespace boost {
namespace detail {
namespace multi_array {

template <typename Extent, typename SizeType>
class extent_range : private std::pair<Extent,Extent> {
  typedef std::pair<Extent,Extent> super_type;
public:
  typedef Extent index;
  typedef SizeType size_type;

  extent_range(index start, index finish) :
    super_type(start,finish) { }

  extent_range(index finish) :
    super_type(0,finish) { }

  extent_range() : super_type(0,0) { }

  index start() const { return super_type::first; }

  index finish() const { return super_type::second; }

  size_type size() const { return super_type::second - super_type::first; }
};

} // namespace multi_array
} // namespace detail 
} // namespace boost


#endif

/* extent_range.hpp
nclkLTpqtF87DqM48cP1tt971u33gkqf26QyI3BuLn3zupxtxZRtXXJujeU0yyDtKvFVLOfViwnfrT+VeWpWZnX2Fu9xw/4m7Q88+7imfdPwIB5bKGNb3rbhqnzwHPXb/chVuazdv5dykQevR86ATrxLXo4ij/fhpnIs49lWmSZ/t87LRuTz/toUwbK+aBOTaeNifkY3I5f1cUMEdb9c8a/SNSHv+n7TFsJF3a0WQt/kZSWzsLz8bDC1akeIbb0pYOi5gN2i/lsIDMO3NfHb8UsP7o8p6MmCvRZZrSu91b7f6/6Kh5mGdl+/b4e6nnm/Nk79uijp+9/9Nu/7aeDEaele/90TMnetwTyg+qTqZlU0hvoc+t/RN1SFUNb36v7a/72M5M/gg7rEf5twCytNwU5kDtxP+wlLDnnS1oTX4zwWcwd42F7mJUX5eRF/0AYTBx8viaOLeMMNiZytI8hhoxD7fmhwsPch52+jyDHdmVjuSxtNDrZsFgP38CbJA9+zzq5syjpXt9P+Z+TMwO9ok9XN9e+6wHMdGLwRH91S4yRpqR7TPgY4+I1JRddp45x955sM4tS/wHpU3/0YzG1pSiR28U2bcvUYgZwzLZzaX46c9GZNDr61rfc0WjjoJye2K7cCD8cJ7erHtL7bik90VQx1jKXMOTAx0DZ/huFYZExjzy0YDkVRL4FRHW8yOF15lI3i226JOB/vtP8BzuLodqq2YVZmwDupdmro/TM2RhXCcSzHDsLrj5Vbj1EPIek+io4fkDbcuXkuDPj6RAry5bdxK39titNxPjxl8mW+ZBeb70BPk40GZYgtdm0gMpifSVmtMhHC2zbCeSofC/PTQGO+NJNnZoLYY+tGwu1d2x7HGX+wPW7Q9tvUwh9sFDxjdeO32NnV0LWKKC2Frml2vn3Lt/kZp7SI4sTJbDG2PLv6vMkVecq8amh42L2Sj/UZXHMetHM7iEpXwDGacbnPA414oii9XN5CmHiCs0cdqtm72qkfzKD3Bw8ausIgiosk99p1wVYJKEulUdShs1L7dW+1TfptH0DWwPo6vvwmv2eNn2vD4fxp7dt/2n1lfcGczN+GVb+/F34334aV2Mzd5VpEYRAISF2Vxu/ucFh+7w5PPHdWXUGTFygB02P+BsCmYAk611nodug+/wJgrK9jYVRnx31ZwtMUeoe7HAG8Tp3IXVG/a534oYj420YpPiOrbWX5+QTfspHi6IDB8fAkxVkHIePhJuBAk6gzAN6TXh8/vBnxKgEDP7AFcVYpuBfcjmNpcP64CeU13x49x3GuhNhE3BR59MFfxM8xvBmL8MjNEFcNaRZi51Gbb+U4KKDprxr4Wh0X745a/uYUl+2Uxvc3MV1Ast6++0MGrbfheAl5s/ShlKfOFMi7EAt9/8+3+PwEtxrK1F23X1SPe+c+z8Y9O02yrMjFDJwrn5/mZzNXv2Xcl3Ts0HXDTOjhpRp2x/SZw1ifaaRyfiwCK3diLwqF+7iH15ldXluZ7pCMz8hFHGZf6prX5yP/9kV6PrJIC8tOEldEbpVoV/Mu03I9zHf9II1DW+ggJ13tv3jRl1g8kaK0U6f0hRs9YULqrrXSeyWU/4g8T500jyLFt9yajnmg5X5YGIVpkaSOeJgZC+gKzeu+Isry1JXmTaOxca2U5WH0CyyGlFN4ceSGguZXaO4VmoeHp3niysYSifkZuENesYU6A3kbOaYwH4isgYk5dbdZ48ca+OqkbJrsnbHH6LlXNm3qQz08TLCp50/Mg158D1phuIapP0ER/66B110G8X0jHIejcRQ/beLdlc5zSd52jRK8OkKF2GmKrXUlPItjwq6NgOku3WXj2UmNoa0=
*/