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
VFhGPUQmX8vIq9PWzGHMiqN8qrD3vXdOCWknXyXtujd3kE1HLb/gcslwKBdjs6u2XI/5tcQbfkA5/YpyOVhJueiSZMeyaXONrNWK1LLR800y+cYXR42Qbw1PE9H5daR1zlh5cWFKvs0emlm3R57PlSXb6JJVAzjSSHSfifStuSnK9851n2Lda7bw8+Ll3F47gNQDKOFPRgasT5bwBYQ3l/B9kTFmrfQcYyekn4TdFqntAj+9V3Sec5mEr6XWpUt+3S/6RE/Tlg413povvvoXJ7qP2+JF8+nyrVeMkfCVEc0Y6fWueV0nxxpYeSN1pbP4d/vOwbXJeTPvdPBqM18eP3eD+GNcP6W+tiV8UQo5ru3IAlxEQ7PWlTMyhtLI40/k+Pdq/+NSdEbyfxLHslR3cYqHS2Ax/Ad6rdAv9p1TXNt4DyP1WBv8yOF8a7GzXRWvk8yUOu+WNVDTrvNfA7Xe/54y9xl1jmPUOdv9RFlxjLIKbM/0vjlH56Z1wj3SkvNeH3jfVH0dv0c3ScKntDRlbdY1/EPCW5l5aaUple83o2mztesnto9/Tc1B+1+da/a4zDV7edWs+y9fXXTDsXmb6q9b8ug/T/5csx/afv0/lrlmTnPK9Fs3/Svft/rMgG/de3WM+1ewu45d94FPwFGwHI6HT8IL4FNwJnwa5sNnYImOUS+GL8Hr4bPwFvgc3Aafh9vh4/BF+Gt4AB6AOgdN+xi0/RpP+xy07TqX6X7YFT4Az4E74Bi4E2bCh+AsuAvOgT+H8+BuWAofgZfBPXrd6RH6XNf+Q6ba1xob4fs23AO20/R3gPNhR1gIO8G1sDO8CXaFD8Cz4U6YBnfBHvAXsCf8FRwE34Pp8D9wCIy0+mqwCewLW8J+8FzYHw6BI+E8OApeAkfDRXAMvBaOg+vgZHgnnAofgNPgU3A6fA6eDz+GF8BP4Xnwa5gJG5H2ibAZnAm7wWzYG86G/WEOHAZz4Qg4F2bCeXAKvBjOgAthISyGi+ESeAO8DG6Al8Nb4VJ4J1wGn4LL4R/hSvhnWAJrR/Ich7FwFawPr4GN4GrYDF4L+8Hr4AC4Bo6Da+FCeAMshDfBJXADvAJuhMvgzXANvA1ugLfDB+HP4KPwTngQ3gVfg5vhm3ALfB/eDT+A90Dda0ufiTxntV7b99p6RedyHYTx8FXYBr6m9+Uhre+vw9Ifyb7j/yvfxKPC+40f97fv8H7jJ/5dO7zf+Il/wz6u79cD+XaMSxzEN+VB4e/H4V/4F/6Ff+Ff+Bf+hX/hX/j3Q/2dovH/3FwZ/j/x8f95tv3/Dus8+PtxDXF3Wv9be4gtN+Mxw/LnzS0ptW//p/ZA3k1wIbMw12YjQPWSXck6PthL/De5GvF3jNohnCRjNLm5dtt+OSI3HX+9wD3/jK2fgSJzNWnF7geuNeM5tQnPJz3NdPx+PmQcTVztxMrHiq1xrrzlZpzLjPuQNsZ9SFvA+FWGVdi6Xq4r7AMfsuK6InR+5RZmXZRfMHuBy3n8SnV74dc88/Ozi9BKtZOjY6jo583OL5DwMUa/uxkP7i7+zsZeK5aR2Bjsosu85ZQM00Smo1tt0us50oLsvyZac+UlrJGxZ88XVrMvV7xVXyS8NyP1EWbMObCcjb1BkX0qZNo2NZRze+zJab1IF/kWcu2XUzzXto3/GruBiTr2uSAFCRz/izsfl6x2KNZXMvZZZhv7JF5+dWJXiDkeeyHlwTEpD5k3UG7sVvjyXOuU2hXUvNNxUtIUsp6xll9+LXScNEnHSctXhq5nZpjUuZ6pbnxw2Wj4qxIeZcZJC0/iOGnocbfw+Onxjp9+LuOnV2375ZBFu3t/8236Sw++8f3L/U8=
*/