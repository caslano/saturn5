//
// detail/handler_type_requirements.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_TYPE_REQUIREMENTS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_TYPE_REQUIREMENTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

// Older versions of gcc have difficulty compiling the sizeof expressions where
// we test the handler type requirements. We'll disable checking of handler type
// requirements for those compilers, but otherwise enable it by default.
#if !defined(BOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS)
# if !defined(__GNUC__) || (__GNUC__ >= 4)
#  define BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS 1
# endif // !defined(__GNUC__) || (__GNUC__ >= 4)
#endif // !defined(BOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS)

// With C++0x we can use a combination of enhanced SFINAE and static_assert to
// generate better template error messages. As this technique is not yet widely
// portable, we'll only enable it for tested compilers.
#if !defined(BOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT)
# if defined(__GNUC__)
#  if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#   if defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT 1
#   endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#  endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
# endif // defined(__GNUC__)
# if defined(BOOST_ASIO_MSVC)
#  if (_MSC_VER >= 1600)
#   define BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT 1
#  endif // (_MSC_VER >= 1600)
# endif // defined(BOOST_ASIO_MSVC)
# if defined(__clang__)
#  if __has_feature(__cxx_static_assert__)
#   define BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT 1
#  endif // __has_feature(cxx_static_assert)
# endif // defined(__clang__)
#endif // !defined(BOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS)

#if defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS)
# include <boost/asio/async_result.hpp>
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS)

# if defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT)

template <typename Handler>
auto zero_arg_copyable_handler_test(Handler h, void*)
  -> decltype(
    sizeof(Handler(static_cast<const Handler&>(h))),
    ((h)()),
    char(0));

template <typename Handler>
char (&zero_arg_copyable_handler_test(Handler, ...))[2];

template <typename Handler, typename Arg1>
auto one_arg_handler_test(Handler h, Arg1* a1)
  -> decltype(
    sizeof(Handler(BOOST_ASIO_MOVE_CAST(Handler)(h))),
    ((h)(*a1)),
    char(0));

template <typename Handler>
char (&one_arg_handler_test(Handler h, ...))[2];

template <typename Handler, typename Arg1, typename Arg2>
auto two_arg_handler_test(Handler h, Arg1* a1, Arg2* a2)
  -> decltype(
    sizeof(Handler(BOOST_ASIO_MOVE_CAST(Handler)(h))),
    ((h)(*a1, *a2)),
    char(0));

template <typename Handler>
char (&two_arg_handler_test(Handler, ...))[2];

template <typename Handler, typename Arg1, typename Arg2>
auto two_arg_move_handler_test(Handler h, Arg1* a1, Arg2* a2)
  -> decltype(
    sizeof(Handler(BOOST_ASIO_MOVE_CAST(Handler)(h))),
    ((h)(*a1, BOOST_ASIO_MOVE_CAST(Arg2)(*a2))),
    char(0));

template <typename Handler>
char (&two_arg_move_handler_test(Handler, ...))[2];

#  define BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT(expr, msg) \
     static_assert(expr, msg);

# else // defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT)

#  define BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT(expr, msg)

# endif // defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS_ASSERT)

template <typename T> T& lvref();
template <typename T> T& lvref(T);
template <typename T> const T& clvref();
template <typename T> const T& clvref(T);
#if defined(BOOST_ASIO_HAS_MOVE)
template <typename T> T rvref();
template <typename T> T rvref(T);
#else // defined(BOOST_ASIO_HAS_MOVE)
template <typename T> const T& rvref();
template <typename T> const T& rvref(T);
#endif // defined(BOOST_ASIO_HAS_MOVE)
template <typename T> char argbyv(T);

template <int>
struct handler_type_requirements
{
};

#define BOOST_ASIO_LEGACY_COMPLETION_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void()) asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::zero_arg_copyable_handler_test( \
          boost::asio::detail::clvref< \
            asio_true_handler_type>(), 0)) == 1, \
      "CompletionHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::clvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()(), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_READ_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, std::size_t)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const std::size_t*>(0))) == 1, \
      "ReadHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::lvref<const std::size_t>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_WRITE_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, std::size_t)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const std::size_t*>(0))) == 1, \
      "WriteHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::lvref<const std::size_t>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_ACCEPT_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::one_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0))) == 1, \
      "AcceptHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_MOVE_ACCEPT_HANDLER_CHECK( \
    handler_type, handler, socket_type) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, socket_type)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_move_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<socket_type*>(0))) == 1, \
      "MoveAcceptHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::rvref<socket_type>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_CONNECT_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::one_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0))) == 1, \
      "ConnectHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_RANGE_CONNECT_HANDLER_CHECK( \
    handler_type, handler, endpoint_type) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, endpoint_type)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const endpoint_type*>(0))) == 1, \
      "RangeConnectHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::lvref<const endpoint_type>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_ITERATOR_CONNECT_HANDLER_CHECK( \
    handler_type, handler, iter_type) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, iter_type)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const iter_type*>(0))) == 1, \
      "IteratorConnectHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::lvref<const iter_type>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_RESOLVE_HANDLER_CHECK( \
    handler_type, handler, range_type) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, range_type)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const range_type*>(0))) == 1, \
      "ResolveHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::lvref<const range_type>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_WAIT_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::one_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0))) == 1, \
      "WaitHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_SIGNAL_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, int)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const int*>(0))) == 1, \
      "SignalHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>(), \
            boost::asio::detail::lvref<const int>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_HANDSHAKE_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::one_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0))) == 1, \
      "HandshakeHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_BUFFERED_HANDSHAKE_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code, std::size_t)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::two_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0), \
          static_cast<const std::size_t*>(0))) == 1, \
      "BufferedHandshakeHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
          boost::asio::detail::lvref<const boost::system::error_code>(), \
          boost::asio::detail::lvref<const std::size_t>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_SHUTDOWN_HANDLER_CHECK( \
    handler_type, handler) \
  \
  typedef BOOST_ASIO_HANDLER_TYPE(handler_type, \
      void(boost::system::error_code)) \
    asio_true_handler_type; \
  \
  BOOST_ASIO_HANDLER_TYPE_REQUIREMENTS_ASSERT( \
      sizeof(boost::asio::detail::one_arg_handler_test( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>(), \
          static_cast<const boost::system::error_code*>(0))) == 1, \
      "ShutdownHandler type requirements not met") \
  \
  typedef boost::asio::detail::handler_type_requirements< \
      sizeof( \
        boost::asio::detail::argbyv( \
          boost::asio::detail::rvref< \
            asio_true_handler_type>())) + \
      sizeof( \
        boost::asio::detail::lvref< \
          asio_true_handler_type>()( \
            boost::asio::detail::lvref<const boost::system::error_code>()), \
        char(0))> BOOST_ASIO_UNUSED_TYPEDEF

#else // !defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS)

#define BOOST_ASIO_LEGACY_COMPLETION_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_READ_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_WRITE_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_ACCEPT_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_MOVE_ACCEPT_HANDLER_CHECK( \
    handler_type, handler, socket_type) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_CONNECT_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_RANGE_CONNECT_HANDLER_CHECK( \
    handler_type, handler, iter_type) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_ITERATOR_CONNECT_HANDLER_CHECK( \
    handler_type, handler, iter_type) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_RESOLVE_HANDLER_CHECK( \
    handler_type, handler, iter_type) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_WAIT_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_SIGNAL_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_HANDSHAKE_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_BUFFERED_HANDSHAKE_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#define BOOST_ASIO_SHUTDOWN_HANDLER_CHECK( \
    handler_type, handler) \
  typedef int BOOST_ASIO_UNUSED_TYPEDEF

#endif // !defined(BOOST_ASIO_ENABLE_HANDLER_TYPE_REQUIREMENTS)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_HANDLER_TYPE_REQUIREMENTS_HPP

/* handler_type_requirements.hpp
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
*/