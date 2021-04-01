/*
@file add_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_ADD_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(add_noexcept)
BOOST_CLBL_TRTS_SFINAE_MSG(add_noexcept, cannot_add_noexcept_to_this_type)

#ifndef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
template<typename T>
struct add_noexcept_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "noexcept types not supported by this configuration.");
};

template<typename T>
struct add_noexcept {
    static_assert(std::is_same<T, detail::dummy>::value,
        "noexcept types not supported by this configuration.");
};

#else

//[ add_noexcept_hpp
/*`
[section:ref_add_noexcept add_noexcept]
[heading Header]
``#include <boost/callable_traits/add_noexcept.hpp>``
[heading Definition]
*/

template<typename T>
using add_noexcept_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_noexcept,
        cannot_add_noexcept_to_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_noexcept_impl {};

    template<typename T>
    struct add_noexcept_impl <T, typename std::is_same<
        add_noexcept_t<T>, detail::dummy>::type>
    {
        using type = add_noexcept_t<T>;
    };
}
//->

template<typename T>
struct add_noexcept : detail::add_noexcept_impl<T> {};

//<-
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a `noexcept` specifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                                    [`add_noexcept_t<T>`]]
    [[`int()`]                                [`int() noexcept`]]
    [[`int (&)()`]                            [`int(&)() noexcept`]]
    [[`int (*)()`]                            [`int(*)() noexcept`]]
    [[`int(foo::*)()`]                        [`int(foo::*)() noexcept`]]
    [[`int(foo::*)() &`]                      [`int(foo::*)() & noexcept`]]
    [[`int(foo::*)() &&`]                     [`int(foo::*)() && noexcept`]]
    [[`int(foo::*)() const transaction_safe`] [`int(foo::*)() const transaction_safe noexcept`]]
    [[`int(foo::*)() noexcept`]               [`int(foo::*)() noexcept`]]
    [[`int`]                                  [(substitution failure)]]
    [[`int foo::*`]                           [(substitution failure)]]
    [[`int (*&)()`]                           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_noexcept.cpp]
[add_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_NOEXCEPT_HPP

/* add_noexcept.hpp
LXipWbG4Hnxf2aGHFgphjhMoytew506qGyyokdFkuNhHcTK/aKMxeKWkGYNLP5vGERdsWzzBWcSWZYchhsqj6/19Urq6JmIpeAXVmX46x9YWSgtRPm+6fqPObsKHI4ZtKI8pDXGqcx8/253yRFBM0fdNk+vUQKSN+azd0qpC5uW8zZfQVTO7xmSle1ahgxi8UzgUQtmFH3znPJt8RnskDN+Hrf4HGZFgpFNOxB+l42drLaxV7/hT6XsN4rlQb4l6njMemToBq+80k1L+Ixzvdj3Lzx8l5P/09umHFYRyWny3Jw/urilTnWDs+lLOO6u0jgZru8cjwONmALoXkwucOs5sT7AjfDEQO1QFgRq4zO/59zO/FdbhNs62DtLb7Tjd5Guf9rY3h9n+sb23QRG4/a70afKo0ToEC4G7CKUHQLUVenHV8Z+r9cspqN0aeg0gm/fsjGdLtsNbniRpD3vZrtaeXJMM5vTEbZveS8OTsi9pmA7CzsH7/qaIfFpqun2UHx3xVQP0g9N0nr91ksF0JphFQ2UCFPaQv2cnYa6vw2yeoB/bcsZTVzhLEw==
*/