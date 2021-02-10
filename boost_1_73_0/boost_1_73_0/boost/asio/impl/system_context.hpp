//
// impl/system_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline system_context::executor_type
system_context::get_executor() BOOST_ASIO_NOEXCEPT
{
  return system_executor();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

/* system_context.hpp
hmxdFJD9zOkeEk1RmaNX6yqR95/H5jdQSwMECgAAAAgALWdKUpvtiiwHAQAAoAEAACoACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9uZXRyYy1maWxlLmRVVAUAAbZIJGBNkEFLxDAQhe/5Fe+osC0oiFBEWESxsJ704nHaTLeBbCYkad3+e5N2V7wl4c33vslB3LGB4xT6ajCW1Ttb3+DTc2+GBW/t4RWDhC2h9iGHn0rO0Ymf1V5r1g0e6/u7+kF9TInP5b6FXyjxUcLSoJ+CVVVVqa/RRIhPRhzyKZqTsRSQBFW1Du3A5559QhopYZEJPshsNOcHhqc04oa6KDZXqawV2FIyM98WRomsFBTDDVGqEUeZrMYUuQa+M7QnB3F2QbzsKY7Vv1HPAcbN0lNRrdEOiDxzIHsVXT/rskoEBb6K6p0qHpZiKlT8GGvRcSnXtVJt2l6oK0t1yx9vQ+UCM1ysTBn4BVBLAwQKAAAACAAtZ0pSM6yLO50AAADoAAAALgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL25ldHJjLW9wdGlvbmFsLmRVVAUAAbZIJGA1jkEOgjAURPc9xRzAcgCWunGBidHgis0XPtBY+kn7m8jtJQjbyZs3
*/