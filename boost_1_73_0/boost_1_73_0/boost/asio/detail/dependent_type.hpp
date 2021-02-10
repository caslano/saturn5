//
// detail/dependent_type.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP
#define BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename DependsOn, typename T>
struct dependent_type
{
  typedef T type;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

/* dependent_type.hpp
9xCtxsEf0AIGoVNEAGFK1vFiMOYaDgjo9+95KdwskQiX8LTggNOSR68vq/Vu+Gi7xG1FC2NASNgMaIJUAMc/jYylXcLqQ9MWxRdf/slJxe0mRTvBY4DSGV06ldIHTelvC7g1zWGnGtcz7hSjCEe6DuQEOidQCzgbq3jFGiOdJtpKj+iqn0QLLtlfgFeq5jiM6NqGcgS8KgG6YhXvPUc8QAN5yweLCBDP+EJ8zkBTFmvHBhUImxr1aaQ+gjO1o5TvkCnSugeYfTIWBF5ripImoptzCvJCv0WMni5Md+f9uYh1kQDBcXc2tTrr4Dy59ut1V9uvCkhJZzmrLTUqgIfWIBMNhUHIjqqkxsQYBTtgPsuX/I9tmMEo4FtqcitLa6r3HgJnDIGM2QcFEfBzZkuRQFT6MJWjtR3xRGPML2vYy3YYlbj0Sz8UhP5gzzBfhqzP6kQwtlDjPzth4J0LxgX4cJgQGkNUmaaxBDBHMNxWObvySpV8I7zH2xBOOPRdD2ENzeCYElNBwQLDYCuMXMHWhFv8ALMKM+xK7RoGKMSoAYK9iBlkZCwAFRZPqipYygEwkKPx9wIjTNGdKd7/dRV/e9Z+WfW3vVqbBhIW/5yqHQC+XiVBIj2SAZ08/uSagqjgoxuqOfpZvsAsXSlf
*/