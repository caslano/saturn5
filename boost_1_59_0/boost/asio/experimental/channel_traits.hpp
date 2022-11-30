//
// experimental/channel_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_CHANNEL_TRAITS_HPP
#define BOOST_ASIO_EXPERIMENTAL_CHANNEL_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <deque>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/experimental/channel_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

#if defined(GENERATING_DOCUMENTATION)

template <typename... Signatures>
struct channel_traits
{
  /// Rebind the traits to a new set of signatures.
  /**
   * This nested structure must have a single nested type @c other that
   * aliases a traits type with the specified set of signatures.
   */
  template <typename... NewSignatures>
  struct rebind
  {
    typedef user_defined other;
  };

  /// Determine the container for the specified elements.
  /**
   * This nested structure must have a single nested type @c other that
   * aliases a container type for the specified element type.
   */
  template <typename Element>
  struct container
  {
    typedef user_defined type;
  };

  /// The signature of a channel cancellation notification.
  typedef void receive_cancelled_signature(...);

  /// Invoke the specified handler with a cancellation notification.
  template <typename F>
  static void invoke_receive_cancelled(F f);

  /// The signature of a channel closed notification.
  typedef void receive_closed_signature(...);

  /// Invoke the specified handler with a closed notification.
  template <typename F>
  static void invoke_receive_closed(F f);
};

#else // defined(GENERATING_DOCUMENTATION)

/// Traits used for customising channel behaviour.
template <typename... Signatures>
struct channel_traits
{
  template <typename... NewSignatures>
  struct rebind
  {
    typedef channel_traits<NewSignatures...> other;
  };
};

template <typename R, typename... Args, typename... Signatures>
struct channel_traits<R(boost::system::error_code, Args...), Signatures...>
{
  template <typename... NewSignatures>
  struct rebind
  {
    typedef channel_traits<NewSignatures...> other;
  };

  template <typename Element>
  struct container
  {
    typedef std::deque<Element> type;
  };

  typedef R receive_cancelled_signature(boost::system::error_code, Args...);

  template <typename F>
  static void invoke_receive_cancelled(F f)
  {
    const boost::system::error_code e = error::channel_cancelled;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(e, typename decay<Args>::type()...);
  }

  typedef R receive_closed_signature(boost::system::error_code, Args...);

  template <typename F>
  static void invoke_receive_closed(F f)
  {
    const boost::system::error_code e = error::channel_closed;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(e, typename decay<Args>::type()...);
  }
};

template <typename R, typename... Args, typename... Signatures>
struct channel_traits<R(std::exception_ptr, Args...), Signatures...>
{
  template <typename... NewSignatures>
  struct rebind
  {
    typedef channel_traits<NewSignatures...> other;
  };

  template <typename Element>
  struct container
  {
    typedef std::deque<Element> type;
  };

  typedef R receive_cancelled_signature(std::exception_ptr, Args...);

  template <typename F>
  static void invoke_receive_cancelled(F f)
  {
    const boost::system::error_code e = error::channel_cancelled;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(
        std::make_exception_ptr(boost::system::system_error(e)),
        typename decay<Args>::type()...);
  }

  typedef R receive_closed_signature(std::exception_ptr, Args...);

  template <typename F>
  static void invoke_receive_closed(F f)
  {
    const boost::system::error_code e = error::channel_closed;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(
        std::make_exception_ptr(boost::system::system_error(e)),
        typename decay<Args>::type()...);
  }
};

template <typename R>
struct channel_traits<R()>
{
  template <typename... NewSignatures>
  struct rebind
  {
    typedef channel_traits<NewSignatures...> other;
  };

  template <typename Element>
  struct container
  {
    typedef std::deque<Element> type;
  };

  typedef R receive_cancelled_signature(boost::system::error_code);

  template <typename F>
  static void invoke_receive_cancelled(F f)
  {
    const boost::system::error_code e = error::channel_cancelled;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(e);
  }

  typedef R receive_closed_signature(boost::system::error_code);

  template <typename F>
  static void invoke_receive_closed(F f)
  {
    const boost::system::error_code e = error::channel_closed;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(e);
  }
};

template <typename R, typename T>
struct channel_traits<R(T)>
{
  template <typename... NewSignatures>
  struct rebind
  {
    typedef channel_traits<NewSignatures...> other;
  };

  template <typename Element>
  struct container
  {
    typedef std::deque<Element> type;
  };

  typedef R receive_cancelled_signature(boost::system::error_code);

  template <typename F>
  static void invoke_receive_cancelled(F f)
  {
    const boost::system::error_code e = error::channel_cancelled;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(e);
  }

  typedef R receive_closed_signature(boost::system::error_code);

  template <typename F>
  static void invoke_receive_closed(F f)
  {
    const boost::system::error_code e = error::channel_closed;
    BOOST_ASIO_MOVE_OR_LVALUE(F)(f)(e);
  }
};

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_CHANNEL_TRAITS_HPP

/* channel_traits.hpp
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
*/