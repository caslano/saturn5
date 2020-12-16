//
// detail/win_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)

#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit win_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit win_fenced_block(full_t)
  {
#if defined(__BORLANDC__)
    LONG barrier = 0;
    ::InterlockedExchange(&barrier, 1);
#elif defined(BOOST_ASIO_MSVC) \
  && ((BOOST_ASIO_MSVC < 1400) || !defined(MemoryBarrier))
# if defined(_M_IX86)
#  pragma warning(push)
#  pragma warning(disable:4793)
    LONG barrier;
    __asm { xchg barrier, eax }
#  pragma warning(pop)
# endif // defined(_M_IX86)
#else
    MemoryBarrier();
#endif
  }

  // Destructor.
  ~win_fenced_block()
  {
#if defined(__BORLANDC__)
    LONG barrier = 0;
    ::InterlockedExchange(&barrier, 1);
#elif defined(BOOST_ASIO_MSVC) \
  && ((BOOST_ASIO_MSVC < 1400) || !defined(MemoryBarrier))
# if defined(_M_IX86)
#  pragma warning(push)
#  pragma warning(disable:4793)
    LONG barrier;
    __asm { xchg barrier, eax }
#  pragma warning(pop)
# endif // defined(_M_IX86)
#else
    MemoryBarrier();
#endif
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)

#endif // BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP

/* win_fenced_block.hpp
d5P70ETTXczzcKm4t5D6eLAV7X1rpz5WLnPVR5XZ2dqpjxe66mMHleHGyjufr4t54YuLt9x11vsvrrMtQuqs3kett+om9ylKnTV9VJGeT/ectoFPYu6xdarUhNdZM6qKVl81TLK539vF/gBrMT0Rz1baIf53s+YwLrifMHs7PhV/v9qpuU/b9iZyZns192F1W65NOcvBHqNrWfev8huRby5r8X8R/k5vZHYhkyjvi+VG5tO0UJkDyCTZMsf3C3Fvn0J52+5Njne/H+t7+N97Uc7InF6PfYLufi703sXoWXpdA5Cx8UP2vXvade9mFFbk2PVGyvmzwDl5et8c+Xi1Mz4Tu6/OdyC73YyHnwXOwwtpC/vpmXFl+j5SjHnUbgsjpi24LdQ5E20XNI0a7gKTxnOfkTRHaxtVvo2rrdO2UP1biX0i9liJ7wy1m/jD2z1TN73iP0rbSSe+FurvhPe651PD2k7CmbYzK2Sek/zkuOcIkiTesyxnjmAENrttiqcurGmvbVMraZuyZTBqhYxLGL/Uv94FtxnR36/cbdDIsDZIzvJyzcmFvSvrWXylWl+KtB2qfMZVX/TddU60dkjDtDDns10t9gssP/+OidIW3S4yp1t9Qtsis1f4MfHvThuZJO3PQOp3mw5O+9PV7zu2lvZH5Yd0cNqHDFf7UN97EtYWmOctu0tAuH+Mrd9XKOWX+Ky7/JwJMsYs0cpQw3Uz82MDxN4sJj4mfE5K55vc/b7ZJ1exyQ4725sidnbMSVyTfOn2Kfu4d/SdGHEOKy3KHBb1K+QeJuu8/laJN8M3jni3opXfvn4bW2+3uHdQOWaeJD2/Z+ZplPdibzdL5OzdliLXRObDZB+C2At9pxJfpDm9sj8G5vSa6RzgrzZp/yd25zovkY4HPUH5M/kYaDntseTPtC2XyXUTDvkFjQOWil/TWucR+8p1W/hiSZsfs9l7htVB/Jyy7yNlPww/uyXJth7xRqrzfxfZxdSnRurGLJ7k+UJSMC7iHOFTcu1vzdyc9SfbPgL9060jzg0+IvJ36dyg695EnP/7qaShjDxhD6tPL1m3en7pLbMG+1pb9rzN/A70+8c7z+k4f/z5UebfVHZIR/bw2W3ogoRO/NfdPgucMo34/fcqvRdh338l77boOvGvYBQ8NeI33xXi30au76S1oKO2EY0u8sc2scLbCSO3wpFrkst0nEvO5Kemo+bdV/kHf2yC37ck3h8bV3sZ7O6o/cii1tKRnEtHEt8o9PpWJ30H6lz5id97gtPOiV/nTk7aKneFpcvIjOzkzBMuKgifJ0xRmfmOjG9RBYlG9Ola013dSedAF3ep1xyoE26PE27RffUK55RBYmedN2y86Lf+eH/UezXQkUtYxPlaLa1oZTKls1MmSyaYMgmLa6nGxY08L/JcpZZFZzNXecqSWZHnKh235HSMjleWH+Z8ZfjYZXKEucm0CPOII0PnJuucW9SJMPx0zQd8wv4GtNnVv3H+3Bw5C76J6dvMM6fybc27wQKx9/e0JE9dMCaM85ybMMlmr/U8sff1tPDEWZ0wkd4nXhKZZ6375Dw307bmWUHvkJ+ITGOzl/pLsd9sLTLn27FDW9x+xzV+5eqD7II5IP5Ngq8xLfga3uds/ynmvfRKsXulbZzchfn/rjreaXKOP7a55RrzdFC5+G5OO0K7FEtrck3U9x0Tpmc3bUcqtwQNlrXOq8zwbs5YqvLuYPeibqYNWe2q4yqzEpk2tkxc5a/sDyvmLLkwuQ2H4qr0+xKjjs1apQdM2/S635Gbhb6PiX2gsU8LfL/UurtB626qoxMD0+14yv15V91lY3VxQV5FYU55nvTpcl87HG/0Q2g=
*/