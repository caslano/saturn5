//
// experimental/as_tuple.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_AS_TUPLE_HPP
#define BOOST_ASIO_EXPERIMENTAL_AS_TUPLE_HPP

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
/// arguments should be combined into a single tuple argument.
/**
 * The as_tuple_t class is used to indicate that any arguments to the
 * completion handler should be combined and passed as a single tuple argument.
 * The arguments are first moved into a @c std::tuple and that tuple is then
 * passed to the completion handler.
 */
template <typename CompletionToken>
class as_tuple_t
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
  BOOST_ASIO_CONSTEXPR as_tuple_t(
      default_constructor_tag = default_constructor_tag(),
      CompletionToken token = CompletionToken())
    : token_(BOOST_ASIO_MOVE_CAST(CompletionToken)(token))
  {
  }

  /// Constructor.
  template <typename T>
  BOOST_ASIO_CONSTEXPR explicit as_tuple_t(
      BOOST_ASIO_MOVE_ARG(T) completion_token)
    : token_(BOOST_ASIO_MOVE_CAST(T)(completion_token))
  {
  }

  /// Adapts an executor to add the @c as_tuple_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c as_tuple_t as the default completion token type.
    typedef as_tuple_t default_completion_token_type;

    /// Construct the adapted executor from the inner executor type.
    template <typename InnerExecutor1>
    executor_with_default(const InnerExecutor1& ex,
        typename constraint<
          conditional<
            !is_same<InnerExecutor1, executor_with_default>::value,
            is_convertible<InnerExecutor1, InnerExecutor>,
            false_type
          >::type::value
        >::type = 0) BOOST_ASIO_NOEXCEPT
      : InnerExecutor(ex)
    {
    }
  };

  /// Type alias to adapt an I/O object to use @c as_tuple_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c as_tuple_t as its
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
/// arguments should be combined into a single tuple argument.
template <typename CompletionToken>
BOOST_ASIO_NODISCARD inline
BOOST_ASIO_CONSTEXPR as_tuple_t<typename decay<CompletionToken>::type>
as_tuple(BOOST_ASIO_MOVE_ARG(CompletionToken) completion_token)
{
  return as_tuple_t<typename decay<CompletionToken>::type>(
      BOOST_ASIO_MOVE_CAST(CompletionToken)(completion_token));
}

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/impl/as_tuple.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_AS_TUPLE_HPP

/* as_tuple.hpp
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
*/