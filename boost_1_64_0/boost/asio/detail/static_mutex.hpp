//
// detail/static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_static_mutex.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_static_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_static_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_static_mutex.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_NULL_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_WIN_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_POSIX_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_STD_STATIC_MUTEX_INIT
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP

/* static_mutex.hpp
K31vb7HmmXHn539gzVsxE5lixxEziefAbM2VJ1Xfbg/oPZb/482Vy870bM2Vp1Vv8V2rq7RcilxxD+Qa5caeayqZTcgUOWuY05PTmRV7Nj25bhz/Q24061Zz28Edz/T5Bq7o6wg+q7Uaj6OeMedf/8VTvsg2n7IlGfYsa274TKu/N25+T7Pmd6sOCtlv7pvfv7JmU+Lm75t/OXT+PoO58teujfucBGjaN5S/heZ83KT2ZK9v3kp+IPLK2+roPIss48qDWrz3b0S996QTeptOEefaZ/eLPZc8awBp9pbOJdeRB8PGjDh1iucc+HYDfM4mf+vIz4HHPZ09HtkPyugfG77GvA8zfcNXUV6hy51MGD/OjA6j7OmchAxbzoz87PllhZ47G6LiMe0w4oGfikd4jUCGzYuQP5Hpv9cnfu3Npla/+OlseP/0l534Z8NjfuRnw7cbUPPZ8KE4LR0QG6fbsLDGjdPw0yZPyc+dwIVX3rscbhkYG6c1X6FM4Z7vXQ55x8eG73Zkt8SGT0keP3xbakjzLV8hzW8ZWPs0P+gTp0Xkwx43TqNGjB8xaei4/PFDT9cNGibMTzb3uZ/iK6Q57vm+xztOiA3fZaac7PMNn1I9XhhlL366Y37k6f5k89qn+9qBsfG636zTd+MVsXR0NqfX++yJUV9JYdZa7Ni7KqLiNOEw4oR/MXHCD91VERmncSfGxulh8632jZO9HcrWp0ktbBuYbYTsVvR+F6LCPbUW4W6ucOMmYZSbUeF81yecvyacM33DGS7zm2LTHjtHXuZxz7fMbx8UG75Hka32DV/44+VfPmRP3660Fr7fLmSO/NuFnzHfLvyJ++1aM9i/7K/xjZ+9qCVu3NYcuuxjfuT3tNSm7IfybMGQ2Dg9yLMt/nFSPRW3XGGvhu/DV6inNtXivpZQvCpyHBeaJjN+Kpr+3R4nXs4eYgbkGPkIz4JXRvX11L7+3Np5JklxxA2tW7ZtLo1JanFM6D6Ue94xMucHveOW3v2Abd+z4yCufAer/4HWIDOqZ/V3EJ4fR7TjW2kP0fPW/ecTmgZu5FaY2cGRCUvsfHwuZo3eNmYPJIXPRSJmHr83/FX7WbV++nWj1xhuri3jsySvuxite1WBsHs2sm5ZHWPDMlr6YOBqo1cfYpEtXxWFJR73tlr33rf9h4WYTzmZfkVX0z9b/AZTOOmp1ff49w0lvwD57Ua+3pJguBxFyqxG5suOyDRcclf0Hr+Qv01Poc1h+uFL55qFj8wfdUqKWp8Qd91DHnTy6D47lrcG/zJO0bqHrKXfi173YNSPeNY+4JwjtYT5nw+6Of3M+zLQ97K/Gbu2yj6b3dt5NjPD4UFRelTkOt9ZPcLP75Vdo3K62/FwxcmOi/PMee9yDtm/TXfucrLxNGmR3GioLSuBjuPG9xsQ0LOB4Wf9Qs96h5/1DT07LvysT+hZ2/Cz7NCzpu6zvieGxrpyw3086d13P6Lf3YZNmNaOA1ufJbYgvh84732FHXp23vNgi4ixZ8nUlVnE2LPMGtQ4Xhkae8a+d+xZ+lkRY1A7h4bH5JqI9ZCb6YRVC1ydb2S98HfCrZcusnLjFf6QvZbSc1uU1Qe1Xsuzf7gW98mqXx36bhw9D+zfcB7YDfY8sNMTxxb1ePs39xTuXdrzivMnjjt6HtjXfR6YuZelY1DrsVo6Z2lNDDjfjz38bpFgv0/u7+3h33bca4MZFzV1V/g3443O7+3my+H53byH4/73A9jX78qA3SdpZR5FXeP5vdLz+yee39d5fl8d/m33qM7R/S536XcCaoV+p5jw6Xcn1Eb97oe6Xr8/Q63T70nE8Q79rkgI3Rmjs0a0J3ROxB0J1o8=
*/