//
// detail/socket_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_SOCKET_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#if defined(BOOST_ASIO_WINDOWS) \
  || defined(__CYGWIN__) \
  || defined(__SYMBIAN32__)

#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class socket_select_interrupter
{
public:
  // Constructor.
  BOOST_ASIO_DECL socket_select_interrupter();

  // Destructor.
  BOOST_ASIO_DECL ~socket_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  BOOST_ASIO_DECL void recreate();

  // Interrupt the select call.
  BOOST_ASIO_DECL void interrupt();

  // Reset the select interrupter. Returns true if the reset was successful.
  BOOST_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  socket_type read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // Open the descriptors. Throws on error.
  BOOST_ASIO_DECL void open_descriptors();

  // Close the descriptors.
  BOOST_ASIO_DECL void close_descriptors();

  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // byte will be written on the other end of the connection and this
  // descriptor will become readable.
  socket_type read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // byte may be written to this to wake up the select which is waiting for the
  // other end to become readable.
  socket_type write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/socket_select_interrupter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)
       // || defined(__CYGWIN__)
       // || defined(__SYMBIAN32__)

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_SOCKET_SELECT_INTERRUPTER_HPP

/* socket_select_interrupter.hpp
n8ZO/kj+R8Fp3FgSJ28k09Gd02m63+jLgxcHgpqzUz7J3dwod43/RXZ9Q8X8WQTK6/9m61Yn4pbqrpGfYMt8Mxvu32VaeyYqRSXnBtxy1NhdB8Vju6zFMesPI/M3vC7xNOtXz2DPQEvNHztuYz3iPUzKcJ7LTfvOdKMs1PWUhZwmSFAHXBlea2/LxoNat73Cv3ycigjv8qBG1TZvg3btfQnx9Z75syZO2VnnU3Y26HwflR237JFuPHPTzT7v797/rzQLz31rbtGmhVtPkA72mXd+ZkfC0fmWb2u+5Tw735J6U89jBgb+uD5v/ON1Rh3b7ol48ydf3xlL/66zfw53fsZ/XuXw522ce1H0rdV3fk7UvShtNd7ZDjbRuF8LR697YfQN0vdzTtS9MB00vtxZ49pddDZLV43/DtD4bw9YpPvmSzWPUibzi2AfeBnsB5c4z3WPmupcfQvmRN2jdqIZF9P432ka35uh8b2FGt+7XPfO3aBxvV/q7J4tcCJ8Ek7SvMkU+AKcpnHAM+AejeO9ofG7zzRe1z3ojMsNhQXwdDgLToDF8Ax4uuZP5sDFsETzJ8Ngqnc8b/Ohx/SSbjt6V8h/69jef+p9IUfvCjnyMb//tPtCvs6xv2/rrpDUB0kPVO6D/51jdt9a/79i/ryKr6H/b/aN/GoIbQUmxhMDCyqrCsqKCuYV2ecbeJ71J/u8oqpgVmlxwNnzf1XvgLvWdZ/GC7qi6uuO9XuMeztt32zCsDH5syqLC+YVzskvo3/m9EVsH8p2jtQPkrzWRc5oa8xnEXv1yyLNtaZT65S1p0Dm7tjBWPVdBwb0d4g9pVW2T2HD4/ZbCQPPnDCo36p+g/U3Yi9ZXor2+CY4/dNCuNGc8++kQR55lp87dVLuhMkjzBbScBw860gbB0Lyfd11p0usflhCWL5q3vzKKq3/Dclnu2tYq63+NI/87NKCcyvds3irrPm4hMnBpUo3uaF0vcf2mwvdNcgTXfOe7lrcRVY/PiE8ZlFWMNem0YhGpo3TxQ1X0PYn1wQixjescEg2O0p2nWQTbfkomHduIOzuwCjZDZJ9204YV9hFtK3U933Ryr0V7IfkYJ6egStuH1hrqFtpr+33lcYJvDMtGKPqRmk/jtWB75r2GS9z8x5m7WPHtAacBjAiJSExA3ZL68RO+MSkSDfD+5PutG6mU/7Q8+sBq38h0JoSU8Cs9lL8uFnrujeS5loDHOqX2/OBtybS28f/q3ubdYsT3XI9QesWjWqncG5ErgXhTKzelNaRfyZ0jVsQdsxLMduAusa4U6d6d3pqvZg1kEY1llu7kF1pZJssds8hmCq5kEyPZKcfyrnAr3nW0tv4bPCuY9e6zC9eNPHvIT07nV8y+jTrZl/spyGbr312BVIbG1lln+m5lInXZOMP32eTaKqbPP69a/1rpLqFuNv0z7T1wUy3CvA/G+D8lyLPBqj2rIsH9tky95l9H+2zFe4zvXM8W4Wed4pnvFOyu8Yd/3LeG4116JneD411JNp6yb4HEfswd6u+yVad2x21DpOKl2Prm0K+ImXzK2yZmo69TajrbP7Wj7hTwJanWtw5EgrDijqqSBWGoaacDKSs+YSBLaEmqDH7GBo79Z7sDKW/mGHL7J4UylOdUJkdxLrjGsMX3tsQsY8hcsy3izZZJnu+1Y+Zb9Uu/zDnm9xQuO+ydeOCCs94r+wlH2pv5jDvPsS7bFnAjahwbYkTrqx44bLFJH64sr6mcFFV2L9xyuNRqDObUO78w5U/yxmC9ey7MI2U8sri8DdOdrsE4tWd5dY8Vfpg4ByrT/StK7NCdWUq5bFuqK4cEFNXxq0vlF55nvTKi1++7LjiTLc=
*/