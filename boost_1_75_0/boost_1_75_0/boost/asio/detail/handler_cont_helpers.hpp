//
// detail/handler_cont_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_continuation_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_is_continuation must be made from a namespace that
// does not contain overloads of this function. This namespace is defined here
// for that purpose.
namespace boost_asio_handler_cont_helpers {

template <typename Context>
inline bool is_continuation(Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return false;
#else
  using boost::asio::asio_handler_is_continuation;
  return asio_handler_is_continuation(
      boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_cont_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

/* handler_cont_helpers.hpp
igtDPPwClGptV98R6yx9Xvu74bUtb0K4E8RBTabC90i5h7Lm8+twY2qwWUqM9LavUo6qvpAKud1Y97ysSpkfAyVkNa7NdGJFhaVy5dMMfd7vsIaqtoRN4EcKHNZ2oGdqo6/AwTuUR6SCY+I5pkXWdsUOZMAv35hoZKFen0F1plGbrYxZIURBEoJ0NDdDbI1x0qhbT/RWZkxiovpBLGiHalLY3pnC5MxcB58k72zUYpvmpyi2me4yFWIKm9vhilGGsB84hEYN51WwqBHjGmifL1YKqMPLZRqN5cHQme8NrMZSYJWuV17EKi/DXSIxrDrWP6x6OhJWIRZqhUflEw0UVJ2LQdVIeD4RL37UQOHU8/XXTA+b+odTBqZQRFqRmWvnpyFzCHZAXkLTWXvdNKieghv5i5XtZiGWey23Q7GyqT0QkNzcoMN4M/sC1TSyCXr2pvSJ/HE9gWEW3xxo90g5qyEi/09ClPYQGcQ4JZbJKwYKtz2tQvhtiINCHFbklLfep8Vhnbwd4jB/4nW+YYZArJNf4pujLMJA7JwKMSsqEjsq19djJHb0eyKxJ+v7RWItWiR2KBKJ3VrfNxI7ZYjEgBvQboL9/9UnpipJP8jCKsyH+IliCMOq0HmbR8rn1+tMyX0CmLLKgkwZA97eXuQr7vFVtkFE4L/TIhc+pdr4CdzuOS57qa+yAyIaeZZ6WQhKlW0QooAEVYjdagwV
*/