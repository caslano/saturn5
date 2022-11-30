//
// experimental/as_single.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_AS_SINGLE_HPP
#define BOOST_ASIO_EXPERIMENTAL_AS_SINGLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

/// A @ref completion_token adapter used to specify that the completion handler
/// arguments should be combined into a single argument.
/**
 * The as_single_t class is used to indicate that any arguments to the
 * completion handler should be combined and passed as a single argument.
 * If there is already one argument, that argument is passed as-is. If
 * there is more than argument, the arguments are first moved into a
 * @c std::tuple and that tuple is then passed to the completion handler.
 */
template <typename CompletionToken>
class as_single_t
{
public:
  /// Tag type used to prevent the "default" constructor from being used for
  /// conversions.
  struct default_constructor_tag {};

  /// Default constructor.
  /**
   * This constructor is only valid if the underlying completion token is
   * default constructible and move constructible. The underlying completion
   * token is itself defaulted as an argument to allow it to capture a source
   * location.
   */
  BOOST_ASIO_CONSTEXPR as_single_t(
      default_constructor_tag = default_constructor_tag(),
      CompletionToken token = CompletionToken())
    : token_(BOOST_ASIO_MOVE_CAST(CompletionToken)(token))
  {
  }

  /// Constructor.
  template <typename T>
  BOOST_ASIO_CONSTEXPR explicit as_single_t(
      BOOST_ASIO_MOVE_ARG(T) completion_token)
    : token_(BOOST_ASIO_MOVE_CAST(T)(completion_token))
  {
  }

  /// Adapts an executor to add the @c as_single_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c as_single_t as the default completion token type.
    typedef as_single_t default_completion_token_type;

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

  /// Type alias to adapt an I/O object to use @c as_single_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c as_single_t as its
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

//private:
  CompletionToken token_;
};

/// Adapt a @ref completion_token to specify that the completion handler
/// arguments should be combined into a single argument.
template <typename CompletionToken>
BOOST_ASIO_NODISCARD inline
BOOST_ASIO_CONSTEXPR as_single_t<typename decay<CompletionToken>::type>
as_single(BOOST_ASIO_MOVE_ARG(CompletionToken) completion_token)
{
  return as_single_t<typename decay<CompletionToken>::type>(
      BOOST_ASIO_MOVE_CAST(CompletionToken)(completion_token));
}

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/impl/as_single.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_AS_SINGLE_HPP

/* as_single.hpp
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
*/