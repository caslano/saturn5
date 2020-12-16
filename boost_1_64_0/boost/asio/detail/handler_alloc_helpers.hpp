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
BeG7fSEvQQSoA+RNiBzqCvIPEGW3nS/jfQJiwK1HHkHUUSe/gtcoxKB7LHJ2J+bns7jekO+4BXOCutbAfNyKNtQB8rNvw5ygziF/DuGjdnngG7gOUbt8L2Iz6tQ3cR6+hfOKOoN8wp2YN3cs38H9HLED61vIT2ji84jbJvISRMWNB3kToubGjPwpRBV1Hfl2RMPNFfK9iCF3jN/D+2HExM/hekO+ALEGdQ35sd/H9YQ6gzwdcQRqZPycAM4Fape/jZiK2uUfI6ahTv0g4b0Y0cTYXJ6FGEbt8hqEhz4N5MPvwhjcMSK/6Id4LcP6APlmxFbULeSpd+O57fojXzmM+Udd+TGOCXEHapfvRtyF2uXun2D72yeH+a2IDtQufwVxBOrgp7geduO8oG4iv+xnOJeoc8jnIXpQV5C/icihTv884Z2JqKF2eepvMQbULs9E3IG6/ju8J/k9rjfULtcQa1C7vAuxGXXqD/icgthTxzb34J6EyF6LMSAf8UfMFWqX1yP2oHZ5EDHxuslh3vwn9EPt8mWIY1G7fBuiB7XLv0L0ona57T5c26hLyE8f0+bVsc3sfm3eNkQF613+2dg2bztql9vHtXm7UAfIXe1t+J3pyWH+LqKE2uWvHtDmbUWdOrDNe/NB6Hc9jhH5mGSbd8TnUSNveEyb14G6gXzRY9HnWtTIH3tcG35vF+cU+ZiJbd4AHutyFtFA7fIKxDBqlwOEh/4uH/n4Nm8i6uQT2ry3IO5C7SN/D3EPau+Jbd6cjjZvs9vOk9q8DyB2Y30NedzBOF7UKeQ8ohO1y7nJbd6xqJHx/0GiDbXLWxH9qEtPafP6UpgfN2bksU9r85LXYgzIhyHaUaeRj0OMbMd+kWcgUljvI69FdKAuIV+B8FDXkG9EpDHOBvLdrg/qFvLYQzA21EnkwxAp1Gnk4xBJd1zIMxDtqH3ktYiWO7/IVyA8dy6Qb0SMYH0D+W7EMOoW8tinY/tu/MiHIdJu/MhvREzDY12+GtGL2uWbEGvc2JBPOhThxoz8vGe0eSe78SCvQPR8HmNAvv0wzCnqzDPbvE2IftQuP+ZZbd561C6/CLENdR35dkQ36ibyvYgsau/wNu/ZiHvcdpCPek6bt8etf26b9wTEHahTz8V6xG7XB/ktiLtQ55CXIIIbcB6Rv4XoQO3y4S/AfKJ2OesCdfaFbd6XECXULr9lCq5P1C73Iuqo68hPPrLNK6LOIG9EjPnC5DC//ihsH7XLx74I1zlql9+E6EHdRD6sC9tCnUGehuhH7SN/CrEGdQN5wouxXdQuZ16C6w+1y2Ne2ubtQF1BfsPRbd4Q6gD5EsQwape3I1qoXT7gZbg2duCcIi9CpFCXkIcQd2D8LeSul2Nu3bEj9yN2oS4hb0fsRt1EvuEVGAce62XavFcj+lHnkD+PSKNuIo9/JfaBOoV8ESKHuo58D2I9apd//So8H1G7PPEYPN9Ru/xKxC7UNeRvI4ZRu/zaY3HdonZ5GiL5RRw78vhX47pFnUZ+B+Jo1C6PP67Nm4ra5SMQ01D7yBcg+lG7/DtECbXLE16DuUWdQe7txn5R15EPex3uP6gD5E2Iutsv8qcQg64Pcnoqnl83Yq6Qe4/H9lHXkL+LmILa5aedgOsZtcsnIXKoA+Q7EYtQe2/A8wUxyT32DViP8G7CeUG++U04R277J+K5jBhxfZB3I8qoXX7tSRg/apd/jNiBOvNmzPlbcd5vQv8ebANxKGqXD34bxoba5e2ILGrv7W3eSxG9qF1egViE2uUrECXUDeS172jzLkNdR74Tsd099uQ2bzJiG+o08vGIO1D7yGchdqGuIF+L2OG2g/wzxF3use/EYxE=
*/