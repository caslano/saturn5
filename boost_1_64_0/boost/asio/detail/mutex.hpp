//
// detail/mutex.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MUTEX_HPP
#define BOOST_ASIO_DETAIL_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_mutex.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_mutex.hpp>
#else
# error Only Windows, POSIX and std::mutex are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_mutex mutex;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_mutex mutex;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_mutex mutex;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_mutex mutex;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_MUTEX_HPP

/* mutex.hpp
ZHFefgJ5nf7tvCjqIl+Nsq7xPajqFh/6jLnQeb4Q1Tgv/xJl3eQD2+5RXC+fgrrtJf4+mrrOT6Ct03+cF0Vd5KuR0zV+AttjbM+6p9itS7wOI3WTD/2v51Hn+fPo01V+EAt1m0/d652vS3wTNukGH/ic7TE/fCEW6grfjUFPuF4+8Xn7x9j4+9it6/wcBjlO9oK5RV/MLf8SY3WTD91nbDrPn0czxsYPoqXbfOr/XK8u8U0o6AYf+KLvKp3jC1HRFX4INd3mE17yXOsifx+1GBs/h4rO+o0NybWU+V40bG/x0fuNQRf4aqS41/wESranl8058rrEN6GgG/wvFB0zfPgr9tfhEzFXl/ibqOrwnajp8ENYq/1BSuk4ZDr8EeR0+HKM1TV+HE2dXtORbseeXcbPgw/oSEmHFyCnw+cP9Fkd/hym6HD3QR2pT4fPwDxdH9ThnzXfkZbq8LqDO1JDh/+N7br++o60EW1jaPIu7NZtHjjYPjrjEdin8zwRLV3kw4Z0pHFPan7fIR1pmq7wyi777I6/R64j/erQjrReFw7rSD/BbPuEzzu8Iy3S4U9jmW7wH4d2pE06O6IjlbDyn+acbzjSdh3++RuMU4f/iOT44SfQo2vDOtKH3tiRBtkn/HcM1eERR3WkvA7/BpN0+IPDO9IMHf4cKjr8FSzRhVxHugdrja3Nt76pIw3QLb7kzR1ppPOGO3o70gQdPh59OnzgMe6Lbh7bkRYe557G9fLit3Wkmu2Vt3ekU/Idqd/28M0Y/NRRbA7Rq8PXvMOc6/BX32kN6OK7rIHR5jzm7YSO9A+Ubc+N6UjnYKEu801YoRv8HCo6e3dHOhk1XeKbsEQ3eMjYjjTqX47DZQzWVX4Qa+3T5hPe05Gqusg3YJOuczrRetM5vhB1XeHPvNc4dZ3fO879cswSjzmpI43WdZ77vo40PZpfRjOOU+hIl6FfV/lxbNfp/R3pbAywf5l7P2CedYm7PuhcusD5CdaeLvOmk83hHsec6LqxxHb2/8/sSKt1+LvYrPOndPgz6xzf/iUefFpHKuoCfxr99qnw2Mn2s73ME043Bl3h6zBL1/hXmK0b/BxqOvuw+ccSXeKbUNcNPvAM90vn+Bw0dJlvwlrd4AOL5kfn+EJs0hX+HwY9fRR7r5xpXnT4o2d1pIIO96Gkw1dhtg6/hIW6drYxY3ucK4zdusUvoqXTlI50BNo6x9Wp2mfzH7HvuR1pq26fZ5zT7f9v64T/c35H2qBLH7NuP24NP2M++dYLrDPdnNHhzxTuSJN1med+yjqxf4Pf2meedXjRRdaMDr+Eog4Puti16fBRmKfDD6Gqa5d0pLMudS91g3/+ac+jc+XLHekWjNNN/tVnPJ863PtZa0OHr/uctaHDP8FOHf499unwntmO3zbnvBcjdZrTkW5E3Zw0+UnsM29tPvgLnhnbM74EDd3k1lzHibF90TVhtTHX+dnLHVcXr+hIF2Oa45d5+jzj1zV+HDt0utIzgpION1HW4cexUOe+1JGu/7L1pv0N02km9ugK/wM1nb7Skb6HDTr31Y40HtP/Ywx8KaboCt+AYbrOW9Cj2zzkKmPTOR6P0brIl6LfMau8Cnt1gx/GgPgsD5nv/axzPB69usiXYoKu8A0YrOu8BbN0i/djlM6u9k7GZF3khVika7wN83SbRyxw33WB52C+rvIGzNYt7vma7yyd54uwUlf451iqm/zRhe6XDt/zdc+CDu/GXl3+hvfeN533Wc0nLbI+dYXPv8YxdY1fwSad+5YxfNe91u3vdaRzF/te+6/9uY7ttodf833n0OHDkOxT4Kko2F7iORirK3wtirrGazBJN3gbcrrFz2M=
*/