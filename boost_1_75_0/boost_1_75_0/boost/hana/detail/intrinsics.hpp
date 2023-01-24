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
E3LcF7zo4sQZIS3kA+luxDNKTnO7mp41RknL6NOpzd7rYOopZcCkFhcZcJWtGv2ZP1mIlHBbstw9We7e20NL6dlxSkbOiJzuMYR2Mi+loYkQ5uvgxJFIoY/oEm5eRTI5T86EcGXMGvCvkPOsHdLeHyKZeoEqlEzdCpm6gG6MTM/9kJFJjpEJhOlJ4uwaSqYLCpm6SZF0OTLdIn4LMl2IkUlmZOqlZLrph1oyjT6NBNp7LRKoIq/aZItWLQAIzNzdUe63/fojXy7OyTdpuc7WuXliQajhgixvtmCeH5AWKfgM5HkacnVHMbsdmTrd9Oj008DVpLV2E/Sk0dJqtO5fXFKINNa3yXJ4lPSgBvReK52oDt3/hD5RSNwZ1IdjTiFg0ch6xThBzqvORWuLubqqBPKIKWyw9gm5enhfbkbbk2gjFiUl+kOSeYs1YGxeBZpZgSs0FRu+JfhVgtA1BRrJXz0IQq2AHAp+kmDcT4rMJP1t6LjGJbvR667QocOcoM2h6PoidPgwHh0Qf0eHftK3Baa1o+8S9NQHgVCNCJRVIPO94Z9YT4j8QPD+gQTSqrcPLNYXDYju6NH7o7Iz6slbndUKgzwojkKwi9z1uomY9ohFPcBCj/0AWQj0yV4ML4pYO8iSPSZSE53eIpVBmN6OTejs7m8fhYHT7T3SAzRJr1HxFjS6kSJsB33SV9PjNcw7Ue+OAtpTkFhBE9DL
*/