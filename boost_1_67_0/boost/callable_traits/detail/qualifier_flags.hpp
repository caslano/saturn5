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
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
*/