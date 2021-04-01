//
// detail/scoped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCOPED_PTR_HPP
#define BOOST_ASIO_DETAIL_SCOPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class scoped_ptr
{
public:
  // Constructor.
  explicit scoped_ptr(T* p = 0)
    : p_(p)
  {
  }

  // Destructor.
  ~scoped_ptr()
  {
    delete p_;
  }

  // Access.
  T* get()
  {
    return p_;
  }

  // Access.
  T* operator->()
  {
    return p_;
  }

  // Dereference.
  T& operator*()
  {
    return *p_;
  }

  // Reset pointer.
  void reset(T* p = 0)
  {
    delete p_;
    p_ = p;
  }

  // Release ownership of the pointer.
  T* release()
  {
    T* tmp = p_;
    p_ = 0;
    return tmp;
  }

private:
  // Disallow copying and assignment.
  scoped_ptr(const scoped_ptr&);
  scoped_ptr& operator=(const scoped_ptr&);

  T* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCOPED_PTR_HPP

/* scoped_ptr.hpp
ac8Gf2coR0MU5EhTZu1bl3sNmz19bsvrTJJCYovPU+haHrGJpm4d6yPsWS1zx+KViSmLv7psy9HWFBGCETR4wyQnJwHoBI6ct6Hoq+Zpyy0SOvf+NQzbio8QsQjvyu+Xi5GwnkkEjeO5gtmgeTZVxp4b3bS+u+vIVNgox1JnLtBPNIpHW0KgXu6MQzw2usqk1j+xbDmS7vbXt7DyPfSp1TyDZo6ZgkFnvj+5NmgSiTPimXZnhwrc+Xwsaab+NR+29Z8+Mglrqernjye+jdEG34ffnndO4FBxRuVqnQc028QsduEMINd5RyCEyDKUGBo0gy/Qoh7+hWINQG9s3jY8woELhOqWn01lAFUvvTZk0vcYTvwNEWXUutDE8ocY15IFojL1xK0WysryAGtS4lCzFKYzxaoTJJKN057tjk9mPVJQtvgxJMyie27cUT+8Us39YmBBCjwZPKD8GXOPFlU5AO6mcde/LXYyJ01g0hown8PqNHope7PQV60PUuxvLuMIR6ozxIPzqp6/Tba3HEWYitK3xxv4SV1H6prxWLE8mxAUxh66vpacNQ6BTA==
*/