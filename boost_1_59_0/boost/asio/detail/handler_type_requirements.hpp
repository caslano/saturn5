//
// detail/handler_type_requirements.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    (BOOST_ASIO_MOVE_OR_LVALUE(Handler)(h)()),
    char(0));

template <typename Handler>
char (&zero_arg_copyable_handler_test(Handler, ...))[2];

template <typename Handler, typename Arg1>
auto one_arg_handler_test(Handler h, Arg1* a1)
  -> decltype(
    sizeof(Handler(BOOST_ASIO_MOVE_CAST(Handler)(h))),
    (BOOST_ASIO_MOVE_OR_LVALUE(Handler)(h)(*a1)),
    char(0));

template <typename Handler>
char (&one_arg_handler_test(Handler h, ...))[2];

template <typename Handler, typename Arg1, typename Arg2>
auto two_arg_handler_test(Handler h, Arg1* a1, Arg2* a2)
  -> decltype(
    sizeof(Handler(BOOST_ASIO_MOVE_CAST(Handler)(h))),
    (BOOST_ASIO_MOVE_OR_LVALUE(Handler)(h)(*a1, *a2)),
    char(0));

template <typename Handler>
char (&two_arg_handler_test(Handler, ...))[2];

template <typename Handler, typename Arg1, typename Arg2>
auto two_arg_move_handler_test(Handler h, Arg1* a1, Arg2* a2)
  -> decltype(
    sizeof(Handler(BOOST_ASIO_MOVE_CAST(Handler)(h))),
    (BOOST_ASIO_MOVE_OR_LVALUE(Handler)(h)(
      *a1, BOOST_ASIO_MOVE_CAST(Arg2)(*a2))),
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
template <typename T> T rorlvref();
#else // defined(BOOST_ASIO_HAS_MOVE)
template <typename T> const T& rvref();
template <typename T> const T& rvref(T);
template <typename T> T& rorlvref();
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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
        boost::asio::detail::rorlvref< \
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