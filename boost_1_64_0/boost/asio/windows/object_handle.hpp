//
// windows/object_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011 Boris Schaeling (boris@highscore.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_object_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an object handle.
typedef basic_object_handle<> object_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP

/* object_handle.hpp
SSqDdZwpYzvE2UX9YHR3jFLZrOfHQtvWmYQvlkvVn43rHcUqm/U9JuW95/CqOLwNPGW0c/TRe+DvSly8Mw4ljIeuWC/HMj1n8iXPnpoXbhN/hrMb9k6XOjpgzwv7XeSFdtKv72Cn8UY9/mkSlotZh30qjn8t4fGn8R39UpzH99lkRxvLc6CHjF83SI8G+s7kbyg/Avw263bZv9fy6o8iT1Lg7yz0a68TfoTME/mi5/hIwy9jmlnCMlzL3da65Fl03Zaw3MD417iDzxv24UvL7PX6i9TjbS03tyyhnKOs6Sz9MsPFPWVdh88co+ICz7CTkmaFM3R9GNhTXs55/6LrhURrvfENX8vbz29lvdh/S5ewvzhmzjvoZz3nLqaf9don9O2lnsnW/vONsPVV8+ZBefzujSIznR5VHSvo/s5AH73PPgv00aFlwbLiLXnb8m1p4QeRYR3NdYHmueNLZX5hj7WR1DHLks+nxrSYgNy+QtJ+40nkmL+ySOpobwMitL6LtGEVnikNwIFoA+fjdmmDS/Nb9u/YvxzXnZKundQl3VIXt/teyGupiw475nwuVmymKrRD+OETd1AGdFV1WJfia0Um/4u9M4GPqrjj+Lw9spuTHBhCCBDuAAFCwhEgQAgg4Q4EJEBoCGQhERICCRg5wyGHAmLFiqKSliuilqhY0SqiooCggiAgUKGKLSr1AEQUrP29//539u1mN4BCer3JZ/LdmTcz75qZN//5z4H68GPlilKmlBu3G2dY4pS91l6Koy1SRGH6oi78xGQyRyj1fdYb3rcuVO73m6D87J+qOK7fQN+PvSKc88clyh+3+dTAeJBdWBHNUZdMI/8U0yLUO1fEEKw70Fl+Sx6hPPKiMOLP8S2ZSedPsNyrrDTV47rjVbrPOcFzRRtDA1MHMcf8R8Mg32QfRxszhfLW3daOShefblariOR32pnSD/FrCNksC+ewYZU8R54ZRc+3vaxf9tH9rPd5XKS7vMv2mjZIjeUsl3EaPnRvWaY9YrTRkc4EOqfJ3yIuy3bse/dz/uRxU7GUTl2j+h6TNO9xWcAsE8KQPNSW8nRro0u+0tRpne+j5yR8RLQcizKLviVBGErd05JmecnoOL+ygtuwnJdepnBrzXCTPNZkIeVp/3Ba7xPSquaaCsXPNYL4OrvRfeAatdfU3nlNb1PZSMQ1YawU54tSeq5f+ZjQ1uDvICp/km9Qu9romQgvZbaT5tl/Sc/Mh8dgIF2ubxzvc/gyrhP4nj/netRR/6yncrGCylO05nxNjAX+ql+sxq+TuaVreW7nLM/L6B7NeL+N8d15y89RP/6OnnGorOffovKcSOffrknbWS5TpLwXT3XIHRgP8pyyQ2ltUEzdZHnsu8i+hl0Iyuwl5U3Dq6ZLxr3WSUqK35PK9/4ZimM8xygK1yzoWeV+pZ9xtcFg6evjKJtP0bkfCHtCyfL9wH+lxSEDfkP5IDLwLWhcQxUTJCmDaKWE+Tu+TSspj12VbZPudJ09ApsofzTnWVLMjrbeffa6wKeNMs7s+L5H0Pu4EGAQRsgqPX18rQkmx7fiNcpH00U4v7scuo79AR2En1iMNdgcdWIDeoZ3ybE4Ly+3j9FKEfe4vJ8ETbl4mq65C3JCQ/kutjpkEb7v+g/y2vacF96mOAvMPK5RvqtXxDHKG8kav9mBrmUyXnPufEqnO2r1JvLc//yt63fzBXL3lfnWl/LNT4qjnbGY0lhlcNQVU6ls/tkaxHn0K3pWLWXZjaRn6WdS+2IyrtEXU+bsiyF3ueyLKaR+mArheZ25aMXb2BJvYzlu/RiSBTR2ZULj1XlN7ro82CSWjBAf+a31NibE2xgYb2Npbnw=
*/