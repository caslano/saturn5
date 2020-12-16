//
// associated_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP
#define BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename>
struct associated_executor_check
{
  typedef void type;
};

template <typename T, typename E, typename = void>
struct associated_executor_impl
{
  typedef E type;

  static type get(const T&, const E& e) BOOST_ASIO_NOEXCEPT
  {
    return e;
  }
};

template <typename T, typename E>
struct associated_executor_impl<T, E,
  typename associated_executor_check<typename T::executor_type>::type>
{
  typedef typename T::executor_type type;

  static type get(const T& t, const E&) BOOST_ASIO_NOEXCEPT
  {
    return t.get_executor();
  }
};

} // namespace detail

/// Traits type used to obtain the executor associated with an object.
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type. The template parameter @c
 * Executor shall be a type meeting the Executor requirements.
 *
 * Specialisations shall meet the following requirements, where @c t is a const
 * reference to an object of type @c T, and @c e is an object of type @c
 * Executor.
 *
 * @li Provide a nested typedef @c type that identifies a type meeting the
 * Executor requirements.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t) and with return type @c type.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t,e) and with return type @c type.
 */
template <typename T, typename Executor = system_executor>
struct associated_executor
{
  /// If @c T has a nested type @c executor_type, <tt>T::executor_type</tt>.
  /// Otherwise @c Executor.
#if defined(GENERATING_DOCUMENTATION)
  typedef see_below type;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::associated_executor_impl<T, Executor>::type type;
#endif // defined(GENERATING_DOCUMENTATION)

  /// If @c T has a nested type @c executor_type, returns
  /// <tt>t.get_executor()</tt>. Otherwise returns @c ex.
  static type get(const T& t,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return detail::associated_executor_impl<T, Executor>::get(t, ex);
  }
};

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T>::get(t)</tt>
 */
template <typename T>
inline typename associated_executor<T>::type
get_associated_executor(const T& t) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T>::get(t);
}

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T, Executor>::get(t, ex)</tt>
 */
template <typename T, typename Executor>
inline typename associated_executor<T, Executor>::type
get_associated_executor(const T& t, const Executor& ex,
    typename enable_if<is_executor<
      Executor>::value>::type* = 0) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T, Executor>::get(t, ex);
}

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T, typename
 * ExecutionContext::executor_type>::get(t, ctx.get_executor())</tt>
 */
template <typename T, typename ExecutionContext>
inline typename associated_executor<T,
  typename ExecutionContext::executor_type>::type
get_associated_executor(const T& t, ExecutionContext& ctx,
    typename enable_if<is_convertible<ExecutionContext&,
      execution_context&>::value>::type* = 0) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T,
    typename ExecutionContext::executor_type>::get(t, ctx.get_executor());
}

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename Executor = system_executor>
using associated_executor_t = typename associated_executor<T, Executor>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP

/* associated_executor.hpp
ELWLLino09POIG6m+RwRdvP5B+kJtFJoJdslY0lyU28gV2Usrn7+SCbDGNVc28tby62xvbSPm8lIU0WMFGssHaAh91P4di0hjD0mj6LtawUs5juFZujA828EbV7YgAOVmvzZCw+I/FnDlgz4YtnuKBbktwHrLRaSW/NFmmJ7Fm9DhbHipyeL6NlGBxQmwn/VEMRoTqTVi53xdGc05Me8oMOyo1n/qFC89jmP3l+1JD9zM3N9+x8S+syYYfFRMhk5idnPHUovDJXY2n0n0abTgpkq2+jFjANM8qlgDv6Zwq2dz2D3OSV8H3OHNFwTYcTLKEMkAXrfw0lxaR5v9fmIHvMUvkZ1BOJeGODIO2/I1rizMNd2HLDPQpTFM2wpckVeRDzm2Sbhb/ZEKvj8gcstHoueMyFoanxF6WXS5HazgTa6yDKF3yI00VQwh10fhW4PT0z5poeqrnAaenARhU7o5GUTBqhP9Dc5uHUid2g29f5QpzmdJynZNZlMCmZRXv8ZAQ+5gXLXUvQqfmW7c82pSuMpqbvtJe4WC+Wt42iLyDna0vgCplNN2WWjRlye9pZJRO2F27lsfrJiI2Qvj8LB46Woy4ljLk+tSUu3FcIpeyimKBG2s+9R+PE5rNrhAVjKJpoYeh2Piwb4tnXHafBvDzVY+1N+4FP6cOEaJrpf4sHMHWaXBDnjjTyFs+18/yEjenN0L9s1TgWF43eyFerbyOmYgF9eb4XlkXPMMT4HmUbtrCQkna5q70brbQ3q+idCCfs5yXae4hrKyfi5Yxb3vxeHfeWL6YjNFZqRzuGasYgKHKbRslMD8NE+xuKiM+jWmD80uOkSNhaJ8PQSU5ozV5k5vk6BxP3Z8L91Dq/eDkX8l0qsUt9Ddkr5tC63jm5KDmD9FTM6NOcWNhq/ZRs3hdCXHVUs0/wZ/bb5w9LdnSk57wH873hiC7emwK7VNPP3WTqdsEuQK0X5xxeuCK/zJM1RPUgOjoTPhhIScf5MWz8xGhycz53jDtFB1aPsxZY3dL7sI03d3EcivwOZkUUadSs1Q8c+nQ6sDuDrYlXp0n+boJqpSONzNtHFXdLYXehMy2piUJrO+IgEcyQxSfKJbSKpmGq2q9MK1cyZyooZbIacYTIL5uH7l0t0beAd5RmPhN2abny+GkFd0u5Ud8CcP3omBMc5ElQquHdnZ+HA6rV30Y5n4bxW1wFtU3SYRtA07BTaylM/fEfTtxPYLeBUyqkdmPtwGdZeFbBmO3ta9CGVpbYOkvQ+cbLapIipJVvY1n/RKFu0EmdGGGPDqEw2+MwI4i4byZc9xuhjemyLSCj9q33Axq3KwOarZlzbYR4pSRTwqS/HQaypkv9d9gQOhrmIeTaHonq8SFZ9LZVu9uPz9PuhFd7DwxR1yGK6JmZtkqBsdVF+f6UpRsdlM/tAD1zatw8eMaupZEkwVxo7lmIeDeEmqxSgfCWPz3MdhrD3EWzqzd1YPn0La1e7QNnH+vmrwoeUbHWSa8p1opK94Kk3pBHSo8Rk1JxpXPdjarx8mG5mlvGVWqsgV7cI5QnadNfeGuP2jYHUCCMKONpLSt27sOLOOBpVIQWhbC/8/PaJeT8zpyGVZazAT+Bdd5QLzkclGBVKsG1Tf1JSQj5kDgSjzECY5iwKR/RowX3pzd+oP6iK5Ql6wZbVa2nF3zCo7VODlfgG/JI5yK9u30hTCoexo3oy+LdMiuu3X6P4Ce/5/xSaZ1yPbxvGz8soLcqozIzKSCIho9C/QiiS2c4mlTQkRWhPRRLSkCSKokiFkGhvhdAeEhooruP5Pe/vF/d9fT73eR3n93usTAmgJaeGkYFdOx2JnkXBW4SxeoLAySY=
*/