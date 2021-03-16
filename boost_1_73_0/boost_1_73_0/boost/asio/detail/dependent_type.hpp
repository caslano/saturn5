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
YyBtk9dDEzjZpUzgZJdyhARbxGwls1uYtTFrZ/bPzH7IbDezf2N2kNlvmb3H7A/MvmT2f8xw8F+wvrpilzC7lFmYWQWzBmarmG1gFmf2FLNnmHUwe5XZfzI7zuwvzD6zznXxuS7FSjpL9VjBZHiveFOe0d3V3QnF2fwX3ytnhrCb9gSWV5bZr4v4SBwjvFX1q0vEuEXCT5ZNrhBwzjbnyT50FK/hInJJD2NzvDrUKri6rffLsGXGZ8QvQrX3dhw=
*/