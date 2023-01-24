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
kRYxp0P18m4scxWXQbkt9Gmc0bdXTPj2oQnfckx93r/lmI4D0nT+Fuvpz3C2h3robeVjW3EmWC1R6dtSWkd8T/DfzfcE/4V8TzjTM8aYi0/5OeZsCc1Qjf40bDHu3zLhSdK2YzrtUt5qYbjdpx4z6MPSFjMMe3KdRMfy+Z7g7+R7msc5PL9E0/rzc1rLpYwDGJs2tPvEMca38bER66j6a1Pfthp9+6pB1e/9r4t+nq73jWhO9QkDJpP5nmDr53uiOc+eMGA7mu9pfhsY/rQeG2IMOpx5wqC3VWeJudt6Z0Sfq7YZfZbOh7WJZUaZaOymBlVfg/sWG7T0vje1/hPcqloM2Fa3mHCM71NMtIj6U32mQR+eNeHe6i1ivTxRb6yXaxcbaz/h9Yg1XtFiwOGyFmO+BC4RbNNbxHwtErgh1sgrVoNWJ88w1shIE759tdm4L9ws6nnBotFbWrNx3C7BP8eEwzlWo86rtG/DSQYtHbEoYu+e8brYf8Mfas9pTb1y3BhX/nFRz+Djx8xw8B034Fx9QsDwSr0M4e2HFqM/m7cYdU6YJvapEYsj1kv/48a4th2je4JbEeMVjX3zsWOMz2uPaW0R7kmmtp7dZMDw042ib/MXR4y94XVBw5fq9dBYio4Z6+JZvieYjD5mwLnBhG8NJrqRuUm0tevViP1i9WuirSc+aDHjw6GjBh1I5/oJDo38nGA4ocWgjRPU
*/