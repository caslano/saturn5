//
// detail/object_pool.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/