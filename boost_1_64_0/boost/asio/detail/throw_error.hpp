//
// detail/throw_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_ERROR_HPP
#define BOOST_ASIO_DETAIL_THROW_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

BOOST_ASIO_DECL void do_throw_error(const boost::system::error_code& err);

BOOST_ASIO_DECL void do_throw_error(const boost::system::error_code& err,
    const char* location);

inline void throw_error(const boost::system::error_code& err)
{
  if (err)
    do_throw_error(err);
}

inline void throw_error(const boost::system::error_code& err,
    const char* location)
{
  if (err)
    do_throw_error(err, location);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/throw_error.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_THROW_ERROR_HPP

/* throw_error.hpp
Ng5Ka/haZlU4TWKFD2Dxtb8EffZMKvkHEk5fywfdNZ7eVbfyvz8eHJvj/1Nltss8vledbu96oQ4+1nI09fK6KShZ8blVjHjdNCG/doPN8O6TanVK5bv1CDwa68X6r6Xxm4gpP23TFeKjAbMZIOw+Tcr/kasyU/EkWXafxDiUVzsy+jTAZw6s/RzzLq+8D4+RjrqGefk2f0Hj21Tew34pfHbTbgUA9jQgHHGKihReOgLchJitajJfv5O/A0K2CL+1B1bA4s73euqdavmdd35lCHHh8Y6kdwPCaQXEuNDbVA6x9qoQyNqmBoJ73zAJ6pO8MLJj8VOla+lYF7LMaHHjZyoJqH4rcvZcMJ0TziDMOvalDmsKrKpb3BmsMgEOJI1VKT4wJIWMc4o31rPU6AXSZXYlAKLo7KyRswdOwlO+ROPwUGtsrxYFLnrU1BRN9UccF+NOHLxW+CBimzup7o47+LGR24LQyQCNDz1c+s39yNRu5SAYJRYHUTB2YccZqo8tdpZGgu4u1r8cQ1GgUDmG074i3DKyTQD7tHv3FmkroWW6EWT0XpCqFntxtg==
*/