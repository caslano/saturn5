/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_UTILITY_HPP
#define BOOST_CLBL_TRTS_DETAIL_UTILITY_HPP

#include <boost/callable_traits/detail/config.hpp>
#include <boost/callable_traits/detail/sfinae_errors.hpp>
#include <boost/callable_traits/detail/qualifier_flags.hpp>

namespace boost { namespace callable_traits { namespace detail {

struct cdecl_tag{};
struct stdcall_tag{};
struct fastcall_tag{};
struct pascal_tag{};

struct invalid_type { invalid_type() = delete; };
struct reference_error { reference_error() = delete; };

template<typename T>
using error_type = typename std::conditional<
    std::is_reference<T>::value, reference_error, invalid_type>::type;

#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
struct abominable_functions_not_supported_on_this_compiler{};
#endif

// used to convey "this type doesn't matter" in code
struct dummy {};

// used as return type in failed SFINAE tests
struct substitution_failure : std::false_type{};

template<bool Value>
using bool_type = std::integral_constant<bool, Value>;

// shorthand for std::tuple_element
template<std::size_t I, typename Tup>
using at = typename std::tuple_element<I, Tup>::type;

template<typename T, typename Class>
using add_member_pointer = T Class::*;

template<typename L, typename R, typename ErrorType>
 using fail_when_same = fail_if<std::is_same<L, R>::value, ErrorType>;

template<typename T, typename ErrorType,
    typename U = typename std::remove_reference<T>::type>
using try_but_fail_if_invalid = sfinae_try<T,
    fail_when_same<U, invalid_type, ErrorType>,
    fail_when_same<U, reference_error,
        reference_type_not_supported_by_this_metafunction>>;

template<typename T, typename ErrorType,
    typename U = typename std::remove_reference<T>::type,
    bool is_reference_error = std::is_same<reference_error, U>::value>
using fail_if_invalid = fail_if<
    std::is_same<U, invalid_type>::value || is_reference_error,
    typename std::conditional<is_reference_error,
        reference_type_not_supported_by_this_metafunction, ErrorType>::type>;

template<typename T, typename Fallback>
using fallback_if_invalid = typename std::conditional<
    std::is_same<T, invalid_type>::value, Fallback, T>::type;

template<typename T, template<class> class Alias, typename U = Alias<T>>
struct force_sfinae {
    using type = U;
};

template<typename T>
using shallow_decay = typename std::remove_cv<
    typename std::remove_reference<T>::type>::type;

template<typename T>
struct is_reference_wrapper_t {
    using type = std::false_type;
};

template<typename T>
struct is_reference_wrapper_t<std::reference_wrapper<T>> {
    using type = std::true_type;
};

template<typename T>
using is_reference_wrapper =
    typename is_reference_wrapper_t<shallow_decay<T>>::type;

template<typename T, typename = std::true_type>
struct unwrap_reference_t {
    using type = T;
};

template<typename T>
struct unwrap_reference_t<T, is_reference_wrapper<T>> {
    using type = decltype(std::declval<T>().get());
};

// removes std::reference_wrapper
template<typename T>
using unwrap_reference = typename unwrap_reference_t<T>::type;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_UTILITY_HPP

/* utility.hpp
GVdU8tmq+lf9q/5V/6p/1b//1t+/5f1f1rzICMCvfv//0vH+X6TPrLX1Xmrp3P2t3e25+znFxTlLs/ILnGvAc4mlWV+iurUd8/fRNnul2e41TrruIHCdt1wjaF8Uwg3aR2pbmJ7v5WUsFtaBC/17Spj4T+fWFy/Kzzp3TP8hhGfGIRZykFhOsWOdjPppb8Yj3hb5G09U+boEvSdbt43Z3+iQyD95YmS9kO4FmcUqYsc7+bgeslewWTP0hvh5wHOGNc6jYxoabiszfnKR+BmGr0HRJbp+oihCxjbM+/yfxM+nnvI9HOeYNd+7TpW1wirb4Q0P3OfKsVdJqugTH5HN9R36/r3+SEddC7pD9J8gZeqpne1nJHHu6Nhn5NzZhXnzz2V7A8nDRF3vfY/4f87y8dYykfu+yEpmDmiUuns0/tGewZTMxVzjNtwekbPCzBrk/CW6wdUpOj5zmvgZ7hHZxKe/Y92S5ouOGxWKfpRHZKM/2HHPebNncoFYXTv5jOhvs9jFm5QcqWsq1R9xa824SqTO98/CPIPZr3/fHStrmMw6IF3OE3Kc5LYeOk5SXCz74q824yKO8ov9xvK1LX49KSuUQ2Qth0H1Zn94xX2CFlNvsk8z9Yb987PKz4Mw5Xr+4kWmztj68aZMLxV5GDKr1UxdkzOyzPrHc0RnCLmp69ZNOLGONmTh7GXaxswy7p1POrakZ2jqvRNXsXPuFU9cKqz3l2sFrGkaFVFxX7Ce+D9s0oc9r3UPH5dxUfSqtveX2/64B0LE4VhAHFjXG2qv4X9CHCbUqBiHbvH+iDjjIMXELQ7o/fI42GW1tt/BMVcw3T4fysRhIXHgWEjZw8N1jZnqdnVd550qbg3M+s4GIqfSGkVVOt7OtXo97XjrZiMdMHX0u9m5/joWEO+Fi9iqbbomoVvcVb+Dow6KstYd4x6y7qi7WT83KLbyZ7AFrZ/TeiXXP2kd2lfTfW+9rc77D72OXfXCHPeFrvO5ooplS+8l6JlCwgyId6SemXeFfiNdgVnif6ZwxlszzG0PtddF72yri1nfbfttESoP1T3RrN9+WeR5Vi/i5Tifh31HxZ9pb18QvcXWQHsfDxNWY8s+c6q/9jmDYiu/dtaZVsOC8j0Wu0yTfiZOAXU2r1bFMxeWkoZFvUwaUl7mz8gaMHzomImjT5qH1WP7Fcf2114qY+alL4TNr738k6IPu3w66ME7H6oe2/81Y/up9vuKvhNFBs2POKDzI16FteBr8DjcaT+767sI/qSfugXKOm39FpAAu8BE2BM2g6fDJDgBJsNs2Bzmw5Zwln4rmAtbwyLYFq6AneBamAZvgN3h/bCXzg/uDf8I+8MjcAA8BgfCv8LBOh94CAyDQ2EDOALGwjGwMRwHk+FEmArPgqfCPDgUzobDYRGcAM+BuXApXA6Xw9VwFbwQroElcC3cAtfBa+H58FZ4AdwOF8D7YDHcBfPhHjgDPg5XwGfgeXA/PBUegD3ga7A9/AZeCGuRLxfBOvBiM99Uny31WTgyaL7prTo//DYo8z1hMtwBO8A7NB+3wwHwTjgO3gUnq55drg7rdcJcytUWLVfXQB+81uHv2An8Xab+Lld/JcYfv56h/e1Uf/eqv/sc83zqqb+u6s85z+d69bcVJsHfwXR4k8N/tvrv4OL/AZ2/9DBs4Vjn9wg09e8E8b5Sr79J430VtOdN7VR/V6g/M29K1w0mwr2wIyyFo+ETWv/2wyy4Dy6Az2j92m/ipX0XjHCJ1wsarxdhOHwJHq7+NvU/+W3ququYE4Q5hPkaU28z84YwwzCzMJdgtmH2ba7+hlX9q/5V/6p/1b/qX/Wv+lf9q/79v/3+Ld//Z84=
*/