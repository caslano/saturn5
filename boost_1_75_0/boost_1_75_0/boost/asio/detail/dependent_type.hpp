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
7zGDvxof4umB2XHIkXEbbES51UTTq4/2HBb6TV33PT0vmwAP3afKJ2l7FdasioDvVPi6ub9vYyd6ATSAKhew8mwIqMnFmIUkxryhGD1u+9C5syiPnVs00XOL1t7qucXr6P194kKTuMai6AORyKrKfAMl3MgdmIGKAOnZW8EuGfebDo936lr9Aa3e3PE858TToecS5y4LZlDp9BCbkXpU2xTbpOgMzn+Lv+PZvqI4xdGz9Vfd//lsX25qKmh00+KCUa1x9GxfMnyIne27c2ro2b551i7P9l25rPVyzvYdm3KxuL+VZyieLjyz51cUqbytUJRH/ICPRbe30vtWsz6D7r8S84ul42LODjF/P05jLQYIYvSSGtm6IFYd56O/4Kw1fNghOJCvcSUsBNIpAdIZh1SuK7dWr0BDKY1eouhfKnycizHRwQoufqHrzmy8GiYqN60M8waVCBuhzrfwpMQORuHLzoIHt9nIhH8HgweHGWiy/txUa63QXcyvlpqTA9PF/ApfNP1bjRGEFaKA4UGDrGoE4TZiy0Dp+QGZkUEjCIeyCMLHmv1yBOEbYv4WTQThNjmCsPjSEYSLWAThNvLLVBpBuAWa1doka0WA92wjd7OESqhI70BRPo5FEC7BuAXRuhk76IYRhJs0EYTFPsV/oo0g7H1SF4wgrIJlGVlurcLkN0oA4QwaQLjwBz8LIMTHchpswmIIqyVrsRJG
*/