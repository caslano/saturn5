//
// detail/handler_alloc_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/thread_info_base.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/handler_alloc_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_allocate and asio_handler_deallocate must be made from
// a namespace that does not contain any overloads of these functions. The
// boost_asio_handler_alloc_helpers namespace is defined here for that purpose.
namespace boost_asio_handler_alloc_helpers {

#if defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Handler>
inline void error_if_hooks_are_defined(Handler& h)
{
  using boost::asio::asio_handler_allocate;
  // If you get an error here it is because some of your handlers still
  // overload asio_handler_allocate, but this hook is no longer used.
  (void)static_cast<boost::asio::asio_handler_allocate_is_no_longer_used>(
    asio_handler_allocate(static_cast<std::size_t>(0),
      boost::asio::detail::addressof(h)));

  using boost::asio::asio_handler_deallocate;
  // If you get an error here it is because some of your handlers still
  // overload asio_handler_deallocate, but this hook is no longer used.
  (void)static_cast<boost::asio::asio_handler_deallocate_is_no_longer_used>(
    asio_handler_deallocate(static_cast<void*>(0),
      static_cast<std::size_t>(0), boost::asio::detail::addressof(h)));
}
#endif // defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Handler>
inline void* allocate(std::size_t s, Handler& h,
    std::size_t align = BOOST_ASIO_DEFAULT_ALIGN)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return aligned_new(align, s);
#elif defined(BOOST_ASIO_NO_DEPRECATED)
  // The asio_handler_allocate hook is no longer used to obtain memory.
  (void)&error_if_hooks_are_defined<Handler>;
  (void)h;
# if !defined(BOOST_ASIO_DISABLE_SMALL_BLOCK_RECYCLING)
  return boost::asio::detail::thread_info_base::allocate(
      boost::asio::detail::thread_context::top_of_thread_call_stack(),
      s, align);
# else // !defined(BOOST_ASIO_DISABLE_SMALL_BLOCK_RECYCLING)
  return aligned_new(align, s);
# endif // !defined(BOOST_ASIO_DISABLE_SMALL_BLOCK_RECYCLING)
#else
  (void)align;
  using boost::asio::asio_handler_allocate;
  return asio_handler_allocate(s, boost::asio::detail::addressof(h));
#endif
}

template <typename Handler>
inline void deallocate(void* p, std::size_t s, Handler& h)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  aligned_delete(p);
#elif defined(BOOST_ASIO_NO_DEPRECATED)
  // The asio_handler_allocate hook is no longer used to obtain memory.
  (void)&error_if_hooks_are_defined<Handler>;
  (void)h;
#if !defined(BOOST_ASIO_DISABLE_SMALL_BLOCK_RECYCLING)
  boost::asio::detail::thread_info_base::deallocate(
      boost::asio::detail::thread_context::top_of_thread_call_stack(), p, s);
#else // !defined(BOOST_ASIO_DISABLE_SMALL_BLOCK_RECYCLING)
  (void)s;
  aligned_delete(p);
#endif // !defined(BOOST_ASIO_DISABLE_SMALL_BLOCK_RECYCLING)
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
        boost_asio_handler_alloc_helpers::allocate(
          sizeof(T) * n, handler_, BOOST_ASIO_ALIGNOF(T)));
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