/*!
@file
Defines macros for commonly used type traits.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_INTRINSICS_HPP
#define BOOST_HANA_DETAIL_INTRINSICS_HPP

#include <boost/hana/config.hpp>


// We use intrinsics if they are available because it speeds up the
// compile-times.
#if defined(BOOST_HANA_CONFIG_CLANG)
#   if __has_extension(is_empty)
#       define BOOST_HANA_TT_IS_EMPTY(T) __is_empty(T)
#   endif

#   if __has_extension(is_final)
#       define BOOST_HANA_TT_IS_FINAL(T) __is_final(T)
#   endif

// TODO: Right now, this intrinsic is never used directly because of
//       https://llvm.org/bugs/show_bug.cgi?id=24173
#   if __has_extension(is_constructible) && false
#       define BOOST_HANA_TT_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#   endif

#   if __has_extension(is_assignable)
#       define BOOST_HANA_TT_IS_ASSIGNABLE(T, U) __is_assignable(T, U)
#   endif

#   if __has_extension(is_convertible)
#       define BOOST_HANA_TT_IS_CONVERTIBLE(T, U) __is_convertible(T, U)
#   endif
#endif

#if !defined(BOOST_HANA_TT_IS_EMPTY)
#   include <type_traits>
#   define BOOST_HANA_TT_IS_EMPTY(T) ::std::is_empty<T>::value
#endif

#if !defined(BOOST_HANA_TT_IS_FINAL)
#   include <type_traits>
#   define BOOST_HANA_TT_IS_FINAL(T) ::std::is_final<T>::value
#endif

#if !defined(BOOST_HANA_TT_IS_CONSTRUCTIBLE)
#   include <type_traits>
#   define BOOST_HANA_TT_IS_CONSTRUCTIBLE(...) ::std::is_constructible<__VA_ARGS__>::value
#endif

#if !defined(BOOST_HANA_TT_IS_ASSIGNABLE)
#   include <type_traits>
#   define BOOST_HANA_TT_IS_ASSIGNABLE(T, U) ::std::is_assignable<T, U>::value
#endif

#if !defined(BOOST_HANA_TT_IS_CONVERTIBLE)
#   include <type_traits>
#   define BOOST_HANA_TT_IS_CONVERTIBLE(T, U) ::std::is_convertible<T, U>::value
#endif

#endif // !BOOST_HANA_DETAIL_INTRINSICS_HPP

/* intrinsics.hpp
0Y8aI5+97mEyZEqcMxQtFaTwNOK5lmwQpSOjkxHtkJDmG5P3ZQScxybvs+PmP+Z8YyMYrdajh8C4gf4HbQjsYih/vEjvrlD02zXEwpu1u8LrOp50myQA+XYIJXhoCiNVHmdcJadyuietBEMcx3Fg2lxgssYbE9xFJkh3mc4M5V2jESk6wGnRj0kOyMW8TbF0yBvDIPYwkd6U/B6l8Rv999bzgDt+8cYo2i9wi4Df68FgIC7sQrfhHZrUOcK+j7jb53gFuwXmJcQtdEpm9nDFm/FvglDEBPEMoEnpRsYEzY99DBCPCy0Kg0gOp6nyT87vG+aeVPv0fO+gzoeHmRAxUCY5RPE0fn4sbuvIyzuYw0rz8zSQhxse7UTUQBb9dxr6BW7cKFovqBt8ebNyJ95sPU/viSqlIIXO4AAgWNLxlrd1596TkurN58r3yuZ2lTLt6CmxcnYweTj4pGQvNYMaR4Doo48YQI/O2kQCLXEOhD8xqGjtOR269C+bo/Pe4Mp51+l2q8ffVB8ZBrr99+umOr1BM4sAIv/kU25Zm4gJhs74sE3B3Ovd8Wq9jOf3rLbwIwpyY6A12fX0S/DN4F56ViJpcIOLtuESUVtdMfcUcRQpbFtZtGQ9mE+pKiFcWDjJ6TXXkPgrvX+Z9/5k
*/