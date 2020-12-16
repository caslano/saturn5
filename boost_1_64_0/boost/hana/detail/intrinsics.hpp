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
5LdLpd2n+NxBcrdWahlpumWWpjesmt/ZKjwVFX+z2aRUXWMaCnGdDO3qJNqkae+fHM2Y00xe0ZBS9L2Fid80OxmNJBxJoQ/yDk9KJ4Q7hTBl4k0m7Yut0+4p/hHtcD3/L+MWnwf4q5dxp7hYOuHaZ4HyElnQ/P+C43/fgmM7a4f//rXA4mL/L/H19aV3ta7A0tt/64raNL8IK6X3pv2j3mP2J3tXHh93UcV/bdM0hQKbzTZNkSNNoZSCpQ1QCih0k2zapWkSd5O2ILLk2LZLk+w2u+mBCAgooBxFDkGRU0QBURBQ5FJukPu+71MBARUE8fjOb97M7/1efrtNwY9/+CGfz36y896bN2/ezLyZeTPzdoRBBEcwNvT/jctjYk5t+Ln6hkLp7TUKj5a/4DhrdnCc2zZxfH8PV+j/N+LC9co6PJMO6/QVU5xhfzdt7zgrtnacA/Aed4stHGfdlo5zF/5vh/SBm2maf1Q7zmmgC/q7foz3fQyjWVLhp0tXOs6bkOfQaY7z5CTHeRb/38e7kBenOs43pjvOoyjv+3ifFt7Zcd5FvW7YynH6axzn15s6zpao31l4Dt68rePEkW+3kOY5DjxvL3eclyFn306Oc0HVcPnORx7595vNve8L8Pkx5DkWPLZD+SHgxkOutnGO8wjKySE9drzjXIb67A5d9m4KHGTeFDp9HGWav7M3gbys/HnQy4kToFuS9T7gDkT9P4G8q0Abhk63BKyAsieAbg3K2xv12Rk0P0L970d934MOZo0GH8BHOciLdmmEPH+PgBb4Rcj7NSD+Cr1X7QD9TocOa3R5uwI2iDKuBe93UN42wP0T5Z2+oyfjy6SHwW0c5wXkV39nom57opyZKGPi1h7t9qyuc6GDW8Oo4zY6vUmdhxtdgbanfna4AzkhwxEVkB396kp8ThwLWaYZasAg1/rxrG1mOM55ZV56NnA7VQAGPV7H6B4fR3ql+uwC3mdA7uehjw8hD/+7CDKsCANXqZ9EXIK6bof/PaA/AXV5H7hK5Iui7F+iHxzIdHQc2vEZ/J8zAfrCJ7YD/qOPblWLvgWd8L9LwePn01Ae2uyDbdBndvZwL6GchdB/qb9ToPNb8BmohX7rIDPauFe1Ldr5rHI/7R7UznejnHvo+8Osrx+KurRO1t8n4fsE1Cu2CfSNdCf0u89W6EuQby0+i6Z7P707FXr9Icp/Ct9TEzx+uyH/i+DH/86o8af3Hw95oOta6O/P+C7/rkB/+gi8r6rU6RPQ188d56d5Z4b+fyzkewH0m0H/Dzmf/33+9/nf53+f/33+9/nf53+f/33+9/nf53+f//1f/a0zEQf8YQHW8bgDB4i4A18VcQcOpLgDXyO6huIxDnTYB4S/a4qZggWcxctIeeXiuxeroUvI003yHBzS8vSQPL1E11wqvgxOGNODvng3QQiri2VMpmVMphVCpgzJtJxkOoRkWinoxoh4Ef1EN6DpisRZXAudGXH1d6OznOGP79vq76ViA+Hlp+Fj05ZXvpT+PkXMI8VziHiexGPdUNwalV4FfIWTyeeHoPye9GAB+jXwkJMfch9HaoQLHwS8xsJxf4HoC4DXOqgOpVcjPd3p7U7BFb+CYEr3swBTcUSUjsbBl7YmxJxuzupdcWcVxRXWuhXzkm5/CIjlYeKrtLJYHhbA+9G6knFpYk3xdjil13E2Akb6/LrhM0rrU8f7yhUGqY6HAs9kcryYMYPLeubW17tA1N+D97YmXSCPGbN2t1mzyDwQfLGmzQxC7TiQtbwPc+Hp3oyV1WG81WkQzm8SaX1RII7jnII6HxpkcmXaTUlevJnB9PJMHkco6d54E+eXyUF2vzwDPnzX7pA=
*/