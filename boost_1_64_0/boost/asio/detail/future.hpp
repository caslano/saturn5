//
// detail/future.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUTURE_HPP
#define BOOST_ASIO_DETAIL_FUTURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#if defined(BOOST_ASIO_HAS_STD_FUTURE)
# include <future>
// Even though the future header is available, libstdc++ may not implement the
// std::future class itself. However, we need to have already included the
// future header to reliably test for _GLIBCXX_HAS_GTHREADS.
# if defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  if defined(_GLIBCXX_HAS_GTHREADS)
#   define BOOST_ASIO_HAS_STD_FUTURE_CLASS 1
#  endif // defined(_GLIBCXX_HAS_GTHREADS)
# else // defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  define BOOST_ASIO_HAS_STD_FUTURE_CLASS 1
# endif // defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#endif // defined(BOOST_ASIO_HAS_STD_FUTURE)

#endif // BOOST_ASIO_DETAIL_FUTURE_HPP

/* future.hpp
KiFXJmo8nYGYM2fbEfbOhpEWYpNk+6JiXvyh8Pd7kumZlhCZ7USciG9EhegQYb7KyitIyXX4uN3h0qqKqPD/audmLn1sc6lDfe+laJ9PyIi4Ve8Se25RtqPZraK5PCu/diQf/MGO3VXGghm6P3LFZQW3zRKEt2df+tO/mRMuuh8ywARul4uyyAmSv854GmThDQJ5uc9v1o2nGnYrpuMtHhif6pszhLnZaLt6TgENg/Jp5zX/IJ+Dx9in4GSd2pHZdLf/ZnK0+Q9Ep3h74kgieXw2zc2ZJQ89NzIpSnYtlC651MJ378YenAVpuhbXNxwMIGhYSR90gBUiNc3t9rdrLq/BqiJUTjzXpsl84EV8o+tx/D6+WRdfK1MPoFdbVu+juOL6ngex4PbwyOJg6VeRsEb/dSnA2zrtaqUCUyy1Zg/WRD0dniP7PTHtFwoaDT+0l91M2QGoeBKJNeqPpxz5f2ZAVX/nqiqbPmqRA4MR1WB+/GOhJbDvDXk2bi+8e4wiquwiaxHRPlnogQIEfU6nS7WAeCI0o8532QntZ8BeMMsQdePTbmakUKiE0Q==
*/