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
JoYQkyv90plgm6iFKRF19VeI3tDsXXtu3Z0QwhoPTbe2GULchF/ZCAtWdOTjy2/25winj41pEPQcuz/p+YdsbRCu+dkyb+t4tkF4/nRk1o0ueuO71uXEr4+YuCMdK9G4rGUFEX1z7Jo9o6YJhZjal5PBMZVo9oZHFIlCfBmbrnVj2r4xqrePgfGptoEKYRr+xDWPOB9XzmfTtQ27VzsfQ3M01ifH1O4Q24jj1juAFcLzjzyDQ98f6z3HubZq7b5CnNU3UiF+Pw4xxZwfhbBsD+tjVBOwg+hES+wQRyHq58OyfaqSUc2kIOLadm7tgHppXRs3hjXSTd/6NDF936yF+OQfbGv7CNu81ceu4zs9p+YZxFcvju9C55l+j4Mw3R9AjA0Xg2uOdHyD2t7gUJtHhGsa/ZuazWqDwBe8Z9JeemYfT/yPwYRw0IYxPiLnnomd1/KnpRHvUOoJ4Y1IGPv0Tc0ziIie6dY+64jwh4Z9Xa+mNgin79SWLxEJMwrpzIdIyDykhFgC2eL7LiKCXlHeFDv7l7pdFLuuR5QB5TWaWM9oQLuAIp/PcZ5vfIA/Gx81HAYHA+uLmuJwYCynZDXj4iT5nDdwNW3iTKv45Oex4Q+RsLEMqV5YRAnxA5xPtzPrltE+KDKbE2t64IKY
*/