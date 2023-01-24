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
FlOh70/QELoJwrXlF0n+6cLm9RGBIUz4JZqwjSwKeFlvZchNz4QenDBzFBgB9RZrvptYd2DZK3ByNXuuIif9mWKy5E8VHpkUwVv9SDS1YJbgHIVBNvqS3TgPkPfH1I3oBnLYBDBALve+GuwETrmvyJs/CcRJDJUsmdgcZfbWS/5bhM1tep700f17rIQBuZY4y/UP/Lqr4HxWz7uEUu7VTgO2tvt2Tc7UwVIbTnsmDsQQQDIFy9CKSxKqSgl2lCDdiU4nVztTfxlLUe+v3a5x9cIhbZlh6yqPEqqnAVNf/bbkjxB+OgudpHkBz1UUSeMn2tZFW0ULbRU3ADRg6qwHiHyzpzs46Z6Zj3wdPL9Qfb4bnlfZmFN9Pl573r2MP98Gz6ttbLn6XMlTn3+Izye7rXvg+U6Ywndno6wIJT7USvwRS1zOAypZA9z1bMGvD1mboPRGXKLWpoICavcpXEtEkxdnqptAMzel8I2vma0EWHD2LuiF9Cq4D6LjFgCJKcZoU6I1hHsvrJ5xv0PffHFkODfsmu6Ziptipl+VUdjhm6F5X1Muv5y1JyR/rvBINWE9r/wwxqs9Qk7d/iWOl0OXQdraZ2AJlA+S/HPKR0r+m9ZvU2d0Cc7ouG5tRjP1Fht6lzpHKqbPxDVdYWNfq1IdY/LSwMNUx1iVLR5BG++ri7VCxVCoZBsROsbWzsf1z1Tycsabr1aPqPFs7eLV
*/