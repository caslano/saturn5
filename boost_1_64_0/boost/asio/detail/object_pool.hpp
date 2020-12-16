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
Zbda50Ot47bcoNb7V63jttxneY9aj2v5BcsjlpO2YJYPW55pOX/Lf+f++E8v+da8XmzZ0f3OnscFIfbPcqZlm+Xxlke2YZaXLQ+q9XpY3q/W+9dyeNs7O943L+8DlsBplsdYrrQ81nK15RmW32V5vOXTLb/UaZ2f5YjlBGAJTLCcbHmi5RTLNssfsGxYPsOy3bLfsvyPlv2PcF4sdSHMcuiRd/a6+d7h/Vc9yv5ZAmo93qPv7PFWWeezxvLp7/DxDoes9/xjmCXJcrrlLMtTHsUsTY9hljbLSyxnW+O988R8Weuvsxyx1r+g1u2s7fdafvIdPs+/tzRZx3dbvsRyhuWY5fMt2x/FLGdbTrPWT7L8fsuJal0sX2ttPxTCLAOWn7NcodZ5tbZ79B2+r//R0myNI8/yFZZdlm8OYZaDOk59TiwvsdwQwixhy72WeyyblotD/93zbLKON+Mdvt+efofPy9l6cv8j/CxJvzdNEjecXJfVRQfTZPiUdXZ+5sdYJy2gi84/64bvSZPgQyfXPcrP2vq708Q4ZbsFnI+vMU2cHSfXhR7juA+kSWr7yXXPsc52P9tuPLnuZdZ5mhhf5ylj2U4/yDFOWTeDdT7WpW46uS6fdbbmNDlwyv7qWBdhf51tJ9c9xDrzvjTJPGXdk6xz3pcW/zso/ndQ/O+g+N9B8b+D/oUl/nfQv7bE/w7695b430H/3SX+d1D876B3Ynmn/w7aJMu9/sLi4qrSipJKaZOSKq/3jS9ls363orDcq1/KooUXFFx4wfnFZWU875LlrfIuL632e6vm1nor/Asra6qKvNJ92oK3rl0k8gTrjcoq/+havv6mzKlaafhnF32hprTKO6eywu+t0/U/Pb5+gbfMW1h9Yr08e3zt5d6KBYUVxZXlIt85vibLW+2vqlz5Ge9KOXh8zUKvP6ew2ucurCosl/4Tn/O7qyprj6/70RvrPlftrdJPfv/4mrl1OkBdIbtO7L1IJfIUXxNzqryFfq/uXnb/1fF1Fc+iNYLS5RW6grP5nrXnippyHUBpsbeqepHMzsqf7Z53YiY/L3O8Vf6rDG/FQn9llVfeL/r1nLLKau/xFTJVdI3uRF1aUlrEKKrnWdt/UnRtdmlF8SnfPfFNOVd0bVaNUTa6/uQmb8yt6/jnue5/45uSLazVyXrrNzkjg5UrZc6Cz7vzrNPZMOb4ZBd5q6sXMabKFQv9hf7SygrZNcaa8quWXect8s/jjqoqH/3WIik5bT7bFy73XlZZt0g+t3DughOz85BwtNrRE1zmrcqrzPNxDYr5E/zE+uMr8ipHvy9y07iFK0r9Rb4TK947Jotbye89/tVO0Ut44qvOMdmjQ7COzfU6dBpjXLiS27c8r7TcK7eMO/mF7rHMSzGrBbpdbmG1f25VVSVHPX/cwr/6+tnR/fiLc7hby9j+Sv169OMrDa+8Z/yiqlIdBN+q1e/MryyuKeO+YmMdxRZdp3M4mweRsYn8auz8mjJ/6WUr/QxjEbfRHF9hlawRvUusz0nPGL2GuaXLqgqrVsrXxuZWFhZbX80W+fqpX3OMmjcfdy4Tz/9rnt5Ho3uVm0Y7u7SqWkeu41o3uuZKLv3xFX8cZw2F6/LG+GTwr+dwdvUb0zY74bM13qqVbm/V6KWvKOJOquFWqpIP6mfm1FRV8XKwbp55xTJuLGvzSouu1824FzPHXl5WuaywbL63vLJqpd5XNczNRXyWh6O2tKqyopzP5xdWlRYu0/FNHzNX9z6Hyea+LVvIXac3ojw2NtdbWOt9y/qlY+dVsKqwrPSGN39zdkXxQqO04vhAJhy/p96yg7NOnoV1W3IScv+4vLLq2WVllUUiD2o=
*/