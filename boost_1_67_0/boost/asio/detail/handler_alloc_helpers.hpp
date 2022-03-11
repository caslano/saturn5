//
// detail/handler_alloc_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_ALLOC_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_ALLOC_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/handler_alloc_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_allocate and asio_handler_deallocate must be made from
// a namespace that does not contain any overloads of these functions. The
// boost_asio_handler_alloc_helpers namespace is defined here for that purpose.
namespace boost_asio_handler_alloc_helpers {

template <typename Handler>
inline void* allocate(std::size_t s, Handler& h)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return ::operator new(s);
#else
  using boost::asio::asio_handler_allocate;
  return asio_handler_allocate(s, boost::asio::detail::addressof(h));
#endif
}

template <typename Handler>
inline void deallocate(void* p, std::size_t s, Handler& h)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  ::operator delete(p);
#else
  using boost::asio::asio_handler_deallocate;
  asio_handler_deallocate(p, s, boost::asio::detail::addressof(h));
#endif
}

} // namespace boost_asio_handler_alloc_helpers

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename T>
class hook_allocator
{
public:
  typedef T value_type;

  template <typename U>
  struct rebind
  {
    typedef hook_allocator<Handler, U> other;
  };

  explicit hook_allocator(Handler& h)
    : handler_(h)
  {
  }

  template <typename U>
  hook_allocator(const hook_allocator<Handler, U>& a)
    : handler_(a.handler_)
  {
  }

  T* allocate(std::size_t n)
  {
    return static_cast<T*>(
        boost_asio_handler_alloc_helpers::allocate(sizeof(T) * n, handler_));
  }

  void deallocate(T* p, std::size_t n)
  {
    boost_asio_handler_alloc_helpers::deallocate(p, sizeof(T) * n, handler_);
  }

//private:
  Handler& handler_;
};

template <typename Handler>
class hook_allocator<Handler, void>
{
public:
  typedef void value_type;

  template <typename U>
  struct rebind
  {
    typedef hook_allocator<Handler, U> other;
  };

  explicit hook_allocator(Handler& h)
    : handler_(h)
  {
  }

  template <typename U>
  hook_allocator(const hook_allocator<Handler, U>& a)
    : handler_(a.handler_)
  {
  }

//private:
  Handler& handler_;
};

template <typename Handler, typename Allocator>
struct get_hook_allocator
{
  typedef Allocator type;

  static type get(Handler&, const Allocator& a)
  {
    return a;
  }
};

template <typename Handler, typename T>
struct get_hook_allocator<Handler, std::allocator<T> >
{
  typedef hook_allocator<Handler, T> type;

  static type get(Handler& handler, const std::allocator<T>&)
  {
    return type(handler);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#define BOOST_ASIO_DEFINE_HANDLER_PTR(op) \
  struct ptr \
  { \
    Handler* h; \
    op* v; \
    op* p; \
    ~ptr() \
    { \
      reset(); \
    } \
    static op* allocate(Handler& handler) \
    { \
      typedef typename ::boost::asio::associated_allocator< \
        Handler>::type associated_allocator_type; \
      typedef typename ::boost::asio::detail::get_hook_allocator< \
        Handler, associated_allocator_type>::type hook_allocator_type; \
      BOOST_ASIO_REBIND_ALLOC(hook_allocator_type, op) a( \
            ::boost::asio::detail::get_hook_allocator< \
              Handler, associated_allocator_type>::get( \
                handler, ::boost::asio::get_associated_allocator(handler))); \
      return a.allocate(1); \
    } \
    void reset() \
    { \
      if (p) \
      { \
        p->~op(); \
        p = 0; \
      } \
      if (v) \
      { \
        typedef typename ::boost::asio::associated_allocator< \
          Handler>::type associated_allocator_type; \
        typedef typename ::boost::asio::detail::get_hook_allocator< \
          Handler, associated_allocator_type>::type hook_allocator_type; \
        BOOST_ASIO_REBIND_ALLOC(hook_allocator_type, op) a( \
              ::boost::asio::detail::get_hook_allocator< \
                Handler, associated_allocator_type>::get( \
                  *h, ::boost::asio::get_associated_allocator(*h))); \
        a.deallocate(static_cast<op*>(v), 1); \
        v = 0; \
      } \
    } \
  } \
  /**/

#define BOOST_ASIO_DEFINE_TAGGED_HANDLER_ALLOCATOR_PTR(purpose, op) \
  struct ptr \
  { \
    const Alloc* a; \
    void* v; \
    op* p; \
    ~ptr() \
    { \
      reset(); \
    } \
    static op* allocate(const Alloc& a) \
    { \
      typedef typename ::boost::asio::detail::get_recycling_allocator< \
        Alloc, purpose>::type recycling_allocator_type; \
      BOOST_ASIO_REBIND_ALLOC(recycling_allocator_type, op) a1( \
            ::boost::asio::detail::get_recycling_allocator< \
              Alloc, purpose>::get(a)); \
      return a1.allocate(1); \
    } \
    void reset() \
    { \
      if (p) \
      { \
        p->~op(); \
        p = 0; \
      } \
      if (v) \
      { \
        typedef typename ::boost::asio::detail::get_recycling_allocator< \
          Alloc, purpose>::type recycling_allocator_type; \
        BOOST_ASIO_REBIND_ALLOC(recycling_allocator_type, op) a1( \
              ::boost::asio::detail::get_recycling_allocator< \
                Alloc, purpose>::get(*a)); \
        a1.deallocate(static_cast<op*>(v), 1); \
        v = 0; \
      } \
    } \
  } \
  /**/

#define BOOST_ASIO_DEFINE_HANDLER_ALLOCATOR_PTR(op) \
  BOOST_ASIO_DEFINE_TAGGED_HANDLER_ALLOCATOR_PTR( \
      ::boost::asio::detail::thread_info_base::default_tag, op ) \
  /**/

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_ALLOC_HELPERS_HPP

/* handler_alloc_helpers.hpp
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
*/