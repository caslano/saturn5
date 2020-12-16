//
// detail/select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/socket_select_interrupter.hpp>
#elif defined(BOOST_ASIO_HAS_EVENTFD)
# include <boost/asio/detail/eventfd_select_interrupter.hpp>
#else
# include <boost/asio/detail/pipe_select_interrupter.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef socket_select_interrupter select_interrupter;
#elif defined(BOOST_ASIO_HAS_EVENTFD)
typedef eventfd_select_interrupter select_interrupter;
#else
typedef pipe_select_interrupter select_interrupter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

/* select_interrupter.hpp
Klb5Br9i+TrH1dQ0/aFuPn12KgHYTt2vnhhdbnKDsXfZkb6v1Q7LxP6pg1fLqhHcGieXiv8/WLZm+N4x21ax+J/UumehZ3tlXcQhfmRZ2iv85S8pCTSgSBE37Vgp4f6GPNwlYe9MhCPC4oUU662kfmh/+Z0MOfB1/QC0v5Fhf6B9OBhIiZ+Af5fFL4qfFQ4kBPyGPRYfRj12R7g6yBBrEO492APF4XBgaLhNQmhI/Or4nqr1Bk369+Fvy5NFWc47mV+VNE7hO1IuuiFCxzfB3hK60UKX7aYbKnSUo48K3WChG+mmGyZ0LNN/CV0HoRtjaNkioi84xTeL8M5fBN9usvoF4Qdx2+LmT0sveifpUDf6/uVE3gfaPkI3QB4+nW2/A0xtJnS5STYPi5SiVQOU3SLvEyc9YlFyVzri3AzzRFe0iVZtE0LxujyidR7ebx8gft4f7k7rgS6a+DzOX+eqMOp9EjutkTIs25otw34ptJlMtxn2jJgyaZ9k0cHHlEnbiP9gyfde5HlLF1PeHOUpb5r6sY79MNb3PDVZk7zgrr/TNeGDLJO7WCa5yRFlUlVcW+3d/5C2n1UGcRFl8L74d3SN56Xi1t1IEzefuF0lbjWol9a4dzak5mnSZqrF/frIt8UlroPi15prX3hLXOwzjDFwU+k5PlDoK5dW2e9BrU3WsnA76g2OdpT2WOJ8a+9eoZlAuxlvW3mz6SDqKOd0xNpLvcU9NiEwo4n1LNKXgP4iRd82N3I9i3MIqVOZk3yEOu3zFeqV+j3yP+qA/D+BdT2rqw5MlbOcce7ZHXlpL2/fFWA3Mx7Fxj7mkrKqgtriIujzqqrVimhtU2/mZEhasP9axoK976n91QVzdbgFeDe56MLSiDv7TzAd6RpET/JxMvhI0tGoNlJjOBnG/tZT3iJtekz5ar74d24q3VafEWf1i+obTCvL7GZWQCH7uJkwncZifGJaV9bqgkJ3oWUTSWvBhPqlS0vt9JLeIVvfKfYBzjBT+ICWrRsWmt7W/Pd2sWdLmG7dJcwsVWOlDr79idCMsXXHYu9BHZKEGV9z4Sxonuz2uV1osri+a4bJsPj049hyKMvR1q33kHJk/uk+zXZnHm2ZCfmAO/MR9XaYM61nJT0j6YKuYqy7X8/ooVOSDM/uxH+OUoOR1FHR0LKC6bnjJ02aP3nBArjGlIv6Cf1O1pkZvh/9IbmIvQN1jdHvNb0s/jnQQKR5hGHfRVkpBf6pagwS/6eQn3Jjhw4HdzNc55hyUm/0HtvBmzu6azkpIdQ9Pi6+P0SkjvFT8e+F4VBC21C0jHRzN9R3d8pI80RGCiYEh8T3FRkp1CIZ6QpJ28RmZaTrhG5kszLSD4VuQLMy0t1Cd0aEjGSPiQ/io2EkcH3SqclKqg+ojpKNvOUg8IinHHRzbx35Cz791uwu8mBhx2geLJgzMYoHyXOgZ7/AfmKz2I8btTIewg3pfS9FuY0HjYundJlSZn9AaEbQboaZTN6NHqOfE//FrjH6Svn2aiPFMUYHha6779eUea7rGsWb7v0k1OU9L3HFWX3bDySekDUmbxP/gO9MTQM3Z5oZH74DBa3V1z0pYeb6IspBeNDUD38pNO/jS2v4zopVfjLX6KneZOtltqGKhEBcfIjNaAb+XcVm5GxH0vYOQfY60ovtqHEHGtJw1ZDGWg0JtC1pS2dLWuY225ZmC11Os23pW0KX1Wxbqkzxbkv2XgspE9Ezs13ht922qptpW4WG/XYqytulg26M0dbAS662dk1Hq62J/TXb7hqjd/TRH7+AMuwsVebI/K5OVtvDh0pKDOdb3eRZtjvSdrbWMH4j9knQEvoi26rV3/9aaEYb/ak=
*/