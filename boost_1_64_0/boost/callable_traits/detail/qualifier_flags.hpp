/*
Defines `qualifier_flags`

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_QUALIFIER_FLAGS_HPP
#define BOOST_CLBL_TRTS_QUALIFIER_FLAGS_HPP

#include <boost/callable_traits/detail/config.hpp>

namespace boost { namespace callable_traits { namespace detail {
    
//bit qualifier_flags used to signify cv/ref qualifiers
using qualifier_flags = std::uint32_t;

/*
    | && &  V  C |
--------------------------------------------
0   | 0  0  0  0 | default
1   | 0  0  0  1 | const
2   | 0  0  1  0 | volatile
3   | 0  0  1  1 | const volatile
--------------------------------------------
4   | 0  1  0  0 | &
5   | 0  1  0  1 | const &
6   | 0  1  1  0 | volatile &
7   | 0  1  1  1 | const volatile &
--------------------------------------------
8   | 1  0  0  0 | &&
9   | 1  0  0  1 | const &&
10  | 1  0  1  0 | volatile &&
11  | 1  0  1  1 | const volatile &&

*/

// Flag representing the default qualifiers on a type 
// or member function overload.
constexpr qualifier_flags default_ = 0;

// Flag representing a const qualifier on a type or
// member function overload.
constexpr qualifier_flags const_ = 1;

// Flag representing a volatile qualifier on a type
// or member function overload.
constexpr qualifier_flags volatile_ = 2;

#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

constexpr qualifier_flags lref_ = default_;
constexpr qualifier_flags rref_ = default_;
#else

// Flag representing an lvalue reference type, or
// an lvalue-reference-qualified member function
// overload.
constexpr qualifier_flags lref_ = 4;

// Flag representing an lvalue reference type, or
// an rvalue-reference-qualified member function
// overload.
constexpr qualifier_flags rref_ = 8;

#endif //#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

constexpr qualifier_flags cv_ = 3;

template<qualifier_flags Flags>
using remove_const_flag = std::integral_constant<
    qualifier_flags, Flags & ~const_>;

template<qualifier_flags Flags>
using is_const = std::integral_constant<bool,
    (Flags & const_) != 0>;

template<qualifier_flags Flags>
using remove_volatile_flag = std::integral_constant<
    qualifier_flags, Flags & ~volatile_>;

template<typename U, typename T = typename std::remove_reference<U>::type>
using cv_of = std::integral_constant<qualifier_flags,
    (std::is_const<T>::value ? const_ : default_)
    | (std::is_volatile<T>::value ? volatile_ : default_)>;

template<typename T>
using ref_of = std::integral_constant<qualifier_flags,
    std::is_rvalue_reference<T>::value ? rref_
    : (std::is_lvalue_reference<T>::value ? lref_
        : default_)>;

//bit-flag implementation of C++11 reference collapsing rules
template<qualifier_flags Existing,
         qualifier_flags Other,
         bool AlreadyHasRef = (Existing & (lref_ | rref_)) != 0,
         bool AlreadyHasLRef = (Existing & lref_) == lref_,
         bool IsAddingLRef = (Other & lref_) == lref_
>
using collapse_flags = std::integral_constant<qualifier_flags,
    !AlreadyHasRef ? (Existing | Other)
        : (AlreadyHasLRef ? (Existing | (Other & ~rref_))
            : (IsAddingLRef ? ((Existing & ~rref_) | Other )
                : (Existing | Other)))>;

template<typename T> struct flag_map { static constexpr qualifier_flags value = default_; };
template<typename T> struct flag_map<T &> { static constexpr qualifier_flags value = lref_; };
template<typename T> struct flag_map<T &&> { static constexpr qualifier_flags value = rref_; };
template<typename T> struct flag_map<T const> { static constexpr qualifier_flags value = const_; };
template<typename T> struct flag_map<T const &> { static constexpr qualifier_flags value = const_ | lref_; };
template<typename T> struct flag_map<T const &&> { static constexpr qualifier_flags value = const_ | rref_; };
template<typename T> struct flag_map<T volatile> { static constexpr qualifier_flags value = volatile_; };
template<typename T> struct flag_map<T volatile &> { static constexpr qualifier_flags value = volatile_ | lref_; };
template<typename T> struct flag_map<T volatile &&> { static constexpr qualifier_flags value = volatile_ | rref_; };
template<typename T> struct flag_map<T const volatile> { static constexpr qualifier_flags value = const_ | volatile_; };
template<typename T> struct flag_map<T const volatile &> { static constexpr qualifier_flags value = const_ | volatile_ | lref_; };
template<typename T> struct flag_map<T const volatile &&> { static constexpr qualifier_flags value = const_ | volatile_ | rref_; };

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_QUALIFIER_FLAGS_HPP

/* qualifier_flags.hpp
XDdG45OBjqQJegmi5xpH1+8gP4ve9pDfQdIk7AzCDf0dZKqEke2ZRLv6mxDfQXwSzp1le7M3o51K1u8gKb/sO8iq0eY7iEta6ncQvdauZPMdZH+F7yCqU9Dc/g7SyR5MG1GV7yCrxwR+BykWOc1q7PgOcsuYgO8gyCf+DnKeuKeo7Nf/z30HWdTS7Hstvwt1DDTpdLNOKGfhXJmH4TY+h17gGGgLkTc4+119L1Bd+l3e/03apah/1ed3rumLu4pbpMMtV9zmcJ1+4jZXZROOjKEeIs9TW2q+Z9rZPqzSY6irTw8cQ10kcncr/gRjqKtEp32V2vJQY6jOZ/6fNH+m6Dee8Zj78HfA5I8cnxBcn8z7y3GNewtS3dTBk8+7GBE872JfK31G0/eudO1TMjJNPBbPk2Li2qeoXvOAZ64YbQsnilsTWjOP9I8W11qPKfte0TCgXgyrxNkU8r4Q4llzResyRZ+njF54UQLtVvB9aE+vbaecXdJO7wVdaY+6MU43AlOIWUfMd2CewrxvxVT6Gals/IR2mXGiRn4fLxMnPa/UGe82Ke7l4PBYjTcPx9MXF+drcZDx8NXca1hKWXtcq46/PU6wKtMO+8uNd5wpN5L+lZmjY8e1SD8AzlCFfEwrxhUyxwXEdfaipdqumLZiFOkmdV91h3OvzE3HtMf0xNh7a98v7j6H3zFaf22/E1Q2uq7nwUb701HcnWvciV+ZionPWaIzyfISo2hMEqYzJig+lc73sro+KqjujwmoczuZsCbUOrdd2+YDjnSUKXKW+zv/+6J3vVWL/7Ueqt8Yt/cidWvtrKPme2aN8cFt8Ryz/jtG3KZL3V1E3he01X45esRJx48aISeI/+xfNVakbWdA+mW3M3Pp5OfDdMffzvEm/QLGBuIDxwZUL8w1rdSt0vkdX4mxgQ7tzZwEfvjR+JY642teFF2/l6lugiPOuRpn4yb5lEfafIyRNjYs7J/Qb+U67kU3reW3waxb4++mtFeOe3Ef52DPhUXldfNj0a9fPu6h5TBW3HlLmaD796DTxmroCEemleq92/42ONxl6qp+twp2D9yrfHa5+0nzO3C8Re4FO2c6SbzErpGxIy7qN8nYyfUD52R21P0KdPxvMmYXf5RMMGmqYzXu7cEO0etnNXaOjYtdU9PPmXdW45Zgns23izyUPkHHCMnjDOLUIM5fhurXiqrVnGf9qHBHnf9VdZr4IJ8b8DzUpLOOgWqbOAez0T/3Y6KmgX51c5tP0Ep0pum9234aVqj7I203rhJr2jtpJ/zzKbNIf9N2tRG9LkHvEHlsklJedtJFZ6I+Oxod8x2vvbifFfI9ZA46nUVnapAObYGjDJ8qOmNd45yjenGwuej1PWlZDlHfkSvW9wn6otJan0+S9fycnXa+cD+Oownc9lRBN/SeTOrmepbAMNxLxT1a5EyjXy/Uenh1b2T6p4djTz4POWg9/K86t8Yuz0lpZh9m+Y3Ub/2HTbot5mO/6zM1OoHj900mIfPP5TuX6saqbHSDz2ox6fOF1g2R0U8QfZ/ruSgfoYuGykY3+Hu/eZ+KFPeWyD7z7SpM7HjDwib4W3+M5mkt0Um26qq/TIe/GtiW30tukfM72TcSv1MqXqsKz+kh5wY4xw81L9GXXw1M/6a0kZPsvDwnp2Bxvn9486TXjbVqyxji4ZcsrpGXsyhHvIn9Ldh/LPYy10AcnHVxS3rFccwziEemice5sxfN0gefgHOs8vIXmnPrbP1Ut/Kkbo0d/aUEZ7dFuFft+0RZnZLrB6dxUF8p1wlI9yZdg8Y79btYiX2/MtiZlb/EfY4Reicd73RtDyUOev7UoW5lim/r2PbTOidxa1k=
*/