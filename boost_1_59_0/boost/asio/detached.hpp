//
// detached.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETACHED_HPP
#define BOOST_ASIO_DETACHED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A @ref completion_token type used to specify that an asynchronous operation
/// is detached.
/**
 * The detached_t class is used to indicate that an asynchronous operation is
 * detached. That is, there is no completion handler waiting for the
 * operation's result. A detached_t object may be passed as a handler to an
 * asynchronous operation, typically using the special value
 * @c boost::asio::detached. For example:
 *
 * @code my_socket.async_send(my_buffer, boost::asio::detached);
 * @endcode
 */
class detached_t
{
public:
  /// Constructor. 
  BOOST_ASIO_CONSTEXPR detached_t()
  {
  }

  /// Adapts an executor to add the @c detached_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c detached_t as the default completion token type.
    typedef detached_t default_completion_token_type;

    /// Construct the adapted executor from the inner executor type.
    executor_with_default(const InnerExecutor& ex) BOOST_ASIO_NOEXCEPT
      : InnerExecutor(ex)
    {
    }

    /// Convert the specified executor to the inner executor type, then use
    /// that to construct the adapted executor.
    template <typename OtherExecutor>
    executor_with_default(const OtherExecutor& ex,
        typename constraint<
          is_convertible<OtherExecutor, InnerExecutor>::value
        >::type = 0) BOOST_ASIO_NOEXCEPT
      : InnerExecutor(ex)
    {
    }
  };

  /// Type alias to adapt an I/O object to use @c detached_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c detached_t as its
  /// default completion token type.
  template <typename T>
  static typename decay<T>::type::template rebind_executor<
      executor_with_default<typename decay<T>::type::executor_type>
    >::other
  as_default_on(BOOST_ASIO_MOVE_ARG(T) object)
  {
    return typename decay<T>::type::template rebind_executor<
        executor_with_default<typename decay<T>::type::executor_type>
      >::other(BOOST_ASIO_MOVE_CAST(T)(object));
  }
};

/// A @ref completion_token object used to specify that an asynchronous
/// operation is detached.
/**
 * See the documentation for boost::asio::detached_t for a usage example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr detached_t detached;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) detached_t detached;
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/detached.hpp>

#endif // BOOST_ASIO_DETACHED_HPP

/* detached.hpp
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
*/