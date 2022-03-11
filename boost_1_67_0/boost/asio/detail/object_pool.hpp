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
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
*/