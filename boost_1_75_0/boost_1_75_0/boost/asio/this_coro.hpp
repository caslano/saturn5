//
// this_coro.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_THIS_CORO_HPP
#define BOOST_ASIO_THIS_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace this_coro {

/// Awaitable type that returns the executor of the current coroutine.
struct executor_t
{
  BOOST_ASIO_CONSTEXPR executor_t()
  {
  }
};

/// Awaitable object that returns the executor of the current coroutine.
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr executor_t executor;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) executor_t executor;
#endif

} // namespace this_coro
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_THIS_CORO_HPP

/* this_coro.hpp
IMratMrlPi1vpbCxRC9HqbFHnSZoI+sGPm1rH50BIAMUDvbD5qLztbwNJn/ts2TNoRwDghb026o6y0DuqPv3PoN3a33E3RjrVxre5WV8HtL2gjPMyhAYq9jL5wI5AtrF1nF08PlNv2F8ENLrfBih59kHJR6Afz7+Xa1PoA+NgzEy0PNcElaTPv76EyR1Gklr4CcyfHx3wyXDy0fCsBB+kDoVCfPD9DC6CSuGLTLTJP8iG1DQYpazXFuwnOWs1BasZDnIR/G8x6EzeJ59EJj/8veRMcoiDampTq3aTVacVUO6TyjY2uYVzNULeyFHRwzmQ84Djoe5+MRUInQS89kWmP86lZtJ+tR/Ua6SFip2HxX7ulmsMXffUKGn2owZCn6ZgTfMz50opQlK3HY/3doHt8M6ScCHRllXGTzysbm4sUrRpl+b/zaU80Iz/Mm6XfmWEVslrYYFcis/PtVKI6bEe+EXYsGVBePgWwCPH+gvLFMp63b18HOYlV0MjsCleBfLljzoNa17rF6/xG9/goJLoGb4lDYX9zSbi+m1BGwAwlWATBSlWdkyKdAqYfRCLQtD6yrjWLXk5c31oVC73RrlQx0WnGo33IHSjl/m9/4cE6CmOoaUHKahWWA+JrZoVmXkc9g9LV8KxmoJoua3qRzB9iIQ2d3PHfg+zWByVS5qksdimS+YzyQ6TxNa4BfuwEMYLiapBgcZE2hz6YXP
*/