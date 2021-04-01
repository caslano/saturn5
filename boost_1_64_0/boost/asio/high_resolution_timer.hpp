//
// high_resolution_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP
#define BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the high resolution clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::high_resolution_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<
    chrono::high_resolution_clock>
  high_resolution_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

/* high_resolution_timer.hpp
5WYfnw+zzL7KNQoI1Ib9sjIr+WZ/3q+CQiviS752u8o+MQSXLHFBJbifov/08ufPmS4lcHJHUZwlta3prpfgasBSeC2U2vS1TGyZiuTCfn2PAmCk5/hhPvyllHw82lcobojosZ29XyBLeaLx8Db9SV/Qqn2NAFxefdnIRuaNGkMDuFxkljqsfqrXaHYjNVzvWPo7vtViDhAypYWpiVr7Gs74WhpCle9pQjlqlFidUw2O3SSDEZaq1ApjvUp1/emQg7LHhh2lb6fdFLU79fBNXI1aX7pTk/ynLgviPzEBROOuu05jmRT8bPhWruwhqOW4KtXkev9vo0O1Zz0otfmh/unusR94KObQ//qdP8UN/1q1yEBtpCVoohzfPE45CqXrhWmaUBdzzszmrmmjAJrU6PyYESQ+Ec3WH+DVC/djGss9ccEVuHqhzMLSbDTAOL6qP4kLRL0LJ9uv8yGXuzHAAB3ksN8UZp7p9RLPjpxMHGGgeHVwF/X0FrrmMvF65WfmpR1GMBxbkHedv+lUrcUBM1umGttDcOqWHHQS113JOX4QC+kZk0WlVG4AzA==
*/