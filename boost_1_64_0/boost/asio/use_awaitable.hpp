//
// use_awaitable.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_USE_AWAITABLE_HPP
#define BOOST_ASIO_USE_AWAITABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/awaitable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A completion token that represents the currently executing coroutine.
/**
 * The @c use_awaitable_t class, with its value @c use_awaitable, is used to
 * represent the currently executing coroutine. This completion token may be
 * passed as a handler to an asynchronous operation. For example:
 *
 * @code awaitable<void> my_coroutine()
 * {
 *   std::size_t n = co_await my_socket.async_read_some(buffer, use_awaitable);
 *   ...
 * } @endcode
 *
 * When used with co_await, the initiating function (@c async_read_some in the
 * above example) suspends the current coroutine. The coroutine is resumed when
 * the asynchronous operation completes, and the result of the operation is
 * returned.
 */
template <typename Executor = executor>
struct use_awaitable_t
{
  /// Default constructor.
  BOOST_ASIO_CONSTEXPR use_awaitable_t()
  {
  }

  /// Adapts an executor to add the @c use_awaitable_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c use_awaitable_t as the default completion token type.
    typedef use_awaitable_t default_completion_token_type;

    /// Construct the adapted executor from the inner executor type.
    executor_with_default(const InnerExecutor& ex) BOOST_ASIO_NOEXCEPT
      : InnerExecutor(ex)
    {
    }
  };

  /// Type alias to adapt an I/O object to use @c use_awaitable_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c use_awaitable_t as its
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

/// A completion token object that represents the currently executing coroutine.
/**
 * See the documentation for boost::asio::use_awaitable_t for a usage example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr use_awaitable_t<> use_awaitable;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) use_awaitable_t<> use_awaitable;
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/use_awaitable.hpp>

#endif // defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_USE_AWAITABLE_HPP

/* use_awaitable.hpp
sadn8F7SubfW6q2w+jxGOFddSrpSeCgsoF4nt+Bkrk2lzS2TvjNC5z7YLOWmaWf8J3l3jnUhzQhvhYXbimlc+yodfFkGLyUNf88aPw3gHl9vbGTd+wM+GX5Z9VzWd8dxLEE5sbZezc9+LOodgs3///3/7zxslKKcSbv76DT30Snuo9u4j+bfu6v76Ij+u4fcPdpo9Qxt5IoM9pDu/IE1ZzMNAWmxUxM4ddjx1+vsoVtcHV1d2xzXnjjji99/VL67iGdmDetB/Fj98950xPreG3eX/hf4uP2UEd+le71225LEFup6T2N7dpaTtJNwd6CHsdeI4JsyXLcSPRZEVBs735pGv1Ofol3Zp6nX+LEtL7UCKk354m8ozdQteOybe5UFaP3GGGD59shw75524mzMiG8PsXXGFzL4E+nOWn1gYRF9k0QZI5sbuD/gfn9pfn8pfn9tnF/0/Wy28cEMTuFZ0DU/kXrbWF2959H61WWYOWi6jfMQf4drus+ZcP+qWbZFhm2RZlvw791sC+pR7TFQlX1Sjo5gxNYXzcWPUI6N2kcdcXTstXzTUke6dpa63EPUuU0kkHb96WcxeUsGvyCdMSX9pLDguV3kuiF5L9H79P4kgx2k66as+DauH/MqfiGpImUqTPsUzih+5u5uUsUZbsXUjzIo384znp9ZMmtDODRm4njN1PzNOr6x+G2mXP0fdWE/5DfMPJf9zI69avzI6nSxqVU6au+eXScGf5rBq0nTUieFefWP+KyZGyN9b1FknqhxcgL2eZFsXEJlhBD5/uqw34jPH0m6sqNsOH/6P8w/fR+Uf/UR9I/Y6Fs60WYAWawn5X5u7001Hp6/8s8MfkMaVPkVHpp/6F8ZvIG0R+UXfH46SMYNp+6jq3rHtbKgT9stm/ugU7EsUk1Z4BfmzD/OM/92Z/5w8deQek0aKQBTPLx5izxA/pxbVLrx//AmyI1By/4hbtXv0BuxL5HFA1uzuFLKs7AIfgpM7ESWYPvxHl+SxSOWZpH4pdXuQbjreyWl0lSsxUb4AQrzfHbFroB7ilLx+omsxdfbZcgNv5W6zbch153FEOk65hUbpstd7F2LsrhBygnEdP7u47gOxx4Ac0rkypUx667Q7Aksv5/ln8jyT8LU8iyeuSKLNb8SnnOxBMB8YD4wHwLyxVYnKWvkqjLQVMdkqeLGhxuMfA57Au2oYu+SZ6zzsMk46o+LI0oL8nlq1qk2rlOOjV6rt06JX7eBjiyuIo3+WtpOYWotC5SZ6vvz9vYo2h/J2PFZPLIvi3t+bY3RRnBX9mpRaXa9M64+N/L6umP+873j96wQex3ssdHn9XtwnlA5Qnge30b8cn4Pl0BHoJe5KXjvK7r28JioEoP+zWieErltyJ7zht+E3tOzGCdd8RsZJ4JFmPPcc68I/g+8E3N9vyv2mma8hu+X31uto/gVXMS6d8DpYfN8uN8t7nHZPsvZPst3u3qVozcuIqx/okt25tYC51bnJqTySdIZRye/5UR/N8YGs/grKfFbr817mmlrmkHncM6xB3LT7txKn9kmnRSAKT7euS35gOWAvEBeUOXJ95N09neB9/JlzmzH6v16zjRp+cD5VO6SNzn8+7qXc028ueofLtBWmnYAlWdwr7qTfip+Z/uPKLnYJedn0W9wUgA2N79rX5QGyB/kA1VG+H2MAsdRnuMoh+X7zTgy7ZNm+6S8M13jLzbvswECvDj31I2077awK5O4ctQ5m2qTOGRMk/lT+3wI1xfKenRp4Ho0Foflu+Mtc3x3jNjf/8QeTI5k8ZnnZnHZ7+22f4eLrdqdxfUGJwVgKr8np5AvyEOlqecjzi2H8RWHl2RxNmloxpY=
*/