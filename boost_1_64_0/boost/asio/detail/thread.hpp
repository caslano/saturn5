//
// detail/thread.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_HPP
#define BOOST_ASIO_DETAIL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_thread.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
#  include <boost/asio/detail/wince_thread.hpp>
# elif defined(BOOST_ASIO_WINDOWS_APP)
#  include <boost/asio/detail/winapp_thread.hpp>
# else
#  include <boost/asio/detail/win_thread.hpp>
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_thread.hpp>
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
# include <boost/asio/detail/std_thread.hpp>
#else
# error Only Windows, POSIX and std::thread are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_thread thread;
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
typedef wince_thread thread;
# elif defined(BOOST_ASIO_WINDOWS_APP)
typedef winapp_thread thread;
# else
typedef win_thread thread;
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_thread thread;
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
typedef std_thread thread;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THREAD_HPP

/* thread.hpp
zET+NPN++Rp+Ss7xHWmQkW/mOMbQ4TF17mKvn79Wan+s4/jCAR3Pn13HEl7X51/mPaqdNckhTvfxERkfKKc/H+PwfZkV8B4S9H2f5jj/hk6q4vNvrM0nbv6N7/omnO48PyVtc8XnpxCmrPkpnP9556f48hRzRmie5rSnjkyeRKWuhlak1NU1P+8wn6j7cZQ58TnOeXrf4fpu4PrGOF+flLr7NY4pp9zHHEe5P1+n/HLvKfnKaByar+lqPMHky8GUgeLPzvaP4X0dxrXZy/KYQ5qTSHO1a5pUt5TlhC6hZbn6OOqb+Bzr+0CT0GssQLbY9RrzZuRnmbH40Hl4/voWmxj/O9IgOW/Pw+gK5IH0gutbbGVIIyhfa5uG5itL2a245EuasmvZl5bTjkuPox1P6FJ+O/b1HxvP9sbwKomcBTfLnoSrV/r2JKzYmKw3XHPtH4H/pZWiG3Ge0y3yHcyY0dvaf6fHP+cxh4KU92Yj39KMGb2i/Q945JuUnzYMM2MzH+nzs/X5UcQXbxUQn6rHXryL4SfEBfcrmS6US3tjkyDtjfPyPSnP/nd0fIuZ58y4uIfvY+KpJ7VQTY/5RskxhPm1lnHjgHcB0WX/XceV5tF+/qqhZYdZwXskpkjaqfo6vyHlK7zvad653mqQ3uhz2muZx8nHufLeyEF9bLRH5S7bulbrdB6lPe+nwofzfaCMb+KTQvdTbCRyP5zlmyc9UOt0Cj9z1+n44m7SzDe/eUxSdF2HPRVFrj9yA1vrPRUfMLrcIJlsZO5oqWVud5MpQuZyr668qekLgmS2IXOZkomdW8/0wUHX/T4yg3WZFL6ZFJ8cUiYp+KPxp5s9HsvXtai507QD/7oP+GuIf9rEaRwqXx8TPJ+6EHrn5+r7w9z7o/Qx3cb1u3Gj+wPHBQfb/DLPlQ+H3948V+e1Kt3ngzrPi3Wbn/rzz5edyQnmm25vv+v+hwYe+cO+vWs3tU3fwTGdr7cz7u9zeH12u6IWJa9+9eOtZ/3881kruldjRefpnqj5smXNi91rmxe7A7l3ZV7saNs+kvK3tl3M4+916n40f3v7qS0evQciY3He4zXwZ9j+vsz29+W2v+l3dNgL1UeY7W/6aBPnCPn7HtWXyt+NcKPk75k4s8fjKv+6lVuC5pFdaF/fUuTiRc5tvczSMOLbb4ndq9jbbhH7jV0i9yRyjeHTsBncCTvDYjgS7oG/gwfg1fAVWAhfk70hS+Ay+Dp8EL4BH4Nvwa0Sbo+E2wffh6Uy3/gr+CH8N/wz/FHOq7L/BNaEn8Ez4UHJzyFLbCvhPyQ/2uZM8nNY5lV+DXvDb+AAmUd5hcyjzIM/wmvhT3AeVC9Xd4MouA5Gw02wKtwK4+BT4t8Bq8Dnxb+Ea0iED8NqcL3Mq9wFVXrPw5oe8g9TYClU4b6A1eFfYQyUeuXl1r1eu9nXfS2jnXS2ybUJIz49j1zkTsXtOM555FtwRRLfXqmnU1TWJL4bZA/VebC++M8Q/zlwPhwGF8Cr4EI4G94Ibxf/neJfBm+SPUoXwfvF/7D4ryftW+B8uFiFgwvgY/BW+AS8Ta67oyW2AnCGlFcMbCHXnY9cmjon895nwsvgtRI+yxI9OrxZwifAyyV8FvV8CrwSNodTYWuYDzvBbDgU5sBRMBdeLucnwzw4U/ykR6WIrhuO1+nJN56kdzVyyj8T1oKzYD14LTwdzoaN4WLYDBbCc+Fc2BHOg73hfDhA5IbCG+EV4pf6Fv2x0leH1vdtkt7tkk4RbAHvhJ3hXTAdLoUj4N3wErgMjofL4TR4L8yFK+A8eD+8Ga6Bt8G1cBV8ROZBb4BPwE1wO9wM98Ftct3LLdGRwkVy3ck=
*/