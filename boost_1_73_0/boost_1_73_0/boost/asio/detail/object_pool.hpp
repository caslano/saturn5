//
// detail/object_pool.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OBJECT_POOL_HPP
#define BOOST_ASIO_DETAIL_OBJECT_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Object>
class object_pool;

class object_pool_access
{
public:
  template <typename Object>
  static Object* create()
  {
    return new Object;
  }

  template <typename Object, typename Arg>
  static Object* create(Arg arg)
  {
    return new Object(arg);
  }

  template <typename Object>
  static void destroy(Object* o)
  {
    delete o;
  }

  template <typename Object>
  static Object*& next(Object* o)
  {
    return o->next_;
  }

  template <typename Object>
  static Object*& prev(Object* o)
  {
    return o->prev_;
  }
};

template <typename Object>
class object_pool
  : private noncopyable
{
public:
  // Constructor.
  object_pool()
    : live_list_(0),
      free_list_(0)
  {
  }

  // Destructor destroys all objects.
  ~object_pool()
  {
    destroy_list(live_list_);
    destroy_list(free_list_);
  }

  // Get the object at the start of the live list.
  Object* first()
  {
    return live_list_;
  }

  // Allocate a new object.
  Object* alloc()
  {
    Object* o = free_list_;
    if (o)
      free_list_ = object_pool_access::next(free_list_);
    else
      o = object_pool_access::create<Object>();

    object_pool_access::next(o) = live_list_;
    object_pool_access::prev(o) = 0;
    if (live_list_)
      object_pool_access::prev(live_list_) = o;
    live_list_ = o;

    return o;
  }

  // Allocate a new object with an argument.
  template <typename Arg>
  Object* alloc(Arg arg)
  {
    Object* o = free_list_;
    if (o)
      free_list_ = object_pool_access::next(free_list_);
    else
      o = object_pool_access::create<Object>(arg);

    object_pool_access::next(o) = live_list_;
    object_pool_access::prev(o) = 0;
    if (live_list_)
      object_pool_access::prev(live_list_) = o;
    live_list_ = o;

    return o;
  }

  // Free an object. Moves it to the free list. No destructors are run.
  void free(Object* o)
  {
    if (live_list_ == o)
      live_list_ = object_pool_access::next(o);

    if (object_pool_access::prev(o))
    {
      object_pool_access::next(object_pool_access::prev(o))
        = object_pool_access::next(o);
    }

    if (object_pool_access::next(o))
    {
      object_pool_access::prev(object_pool_access::next(o))
        = object_pool_access::prev(o);
    }

    object_pool_access::next(o) = free_list_;
    object_pool_access::prev(o) = 0;
    free_list_ = o;
  }

private:
  // Helper function to destroy all elements in a list.
  void destroy_list(Object* list)
  {
    while (list)
    {
      Object* o = list;
      list = object_pool_access::next(o);
      object_pool_access::destroy(o);
    }
  }

  // The list of live objects.
  Object* live_list_;

  // The free list.
  Object* free_list_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_OBJECT_POOL_HPP

/* object_pool.hpp
FHoLSI/+U0UlCFYHUn2eqgBLdQZv1TiIkV0RCagOnhUxzChaH5fu5/7L/pFoJMtJtrU6EU3QyUZZ/lnXtjKtWtNY2hTFwJ9nGnnv6VHUe/vCWlztjOgptTOieEObbKxGgLv2K+lmbU6w1t14Cv3bOXq5s9PHZH5FjQ5DkFD8QpoZDWy2jxqr6yOw2n7bHdi0k+b8tl+6ssQFnA9Yqhb8eEZEwoAw/m7tEIg95HAehUqEiowbxqMzUC3OxmPLJ7f4FnNO6KmFleYXKo66qtrFsLggcqXADBzqhUF6E3ji9DjVZjRAwyUyct1Bb2P2XtS6pS4J13kJVOmQ4YbwjM4mZd6omqbDRy5M2QfZ5hAHRo26w9rQmZwKrHr4BRayaWWhkqOttuM1OkLOrWIVqqJHndF3qpE+ag0JBVU4w8zOjEopugaE4EGtcJ1A7UIsS8ebFlpNKAQClqM5LQgYrr3j1HVj+eNmO9HANSp6o9bGQR9ua6gxgRkx2tYJc7Oc60PnhaJslIVcm3X9WE067Nryy4xEUmV7ermayGXxwA6j2SUu0AtebAH0FGQ+163wgvOrxBfPMGTX+EMEMFE3n/paemF2iAuOaSNvzoJ6fyxSkeoSOZeI9F+l29Zxzq6V51sVueM2hJmWch/coysV
*/