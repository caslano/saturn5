/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP
#define BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_member_qualifiers_hpp
/*`[section:ref_has_member_qualifiers has_member_qualifiers]
[heading Header]
``#include <boost/callable_traits/has_member_qualifiers.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct has_member_qualifiers;

//<-
template<typename T>
struct has_member_qualifiers : detail::traits<
    detail::shallow_decay<T>>::has_member_qualifiers {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::has_member_qualifiers;
};

// older compilers don't support variable templates
#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_member_qualifiers_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool has_member_qualifiers_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::has_member_qualifiers::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_member_qualifiers<T>` and is aliased by `typename has_member_qualifiers<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function with member qualifiers
  * `T` is a member function pointer with member qualifiers
  * `T` is a function object with a member-qualified `operator()`
* On compilers that support variable templates, `has_member_qualifiers_v<T>` is equivalent to `has_member_qualifiers<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_member_qualifiers_v<T>`]]
    [[`void() const`]                   [`true`]]
    [[`void() const transaction_safe`]  [`true`]]
    [[`void() volatile &&`]             [`true`]]
    [[`int(foo::*)() &`]                [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`void(foo::*&)() const`]          [`true`]]
    [[`void(foo::* const)() const`]     [`true`]]
    [[`void()`]                         [`false`]]
    [[`void() transaction_safe`]        [`false`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/has_member_qualifiers.cpp]
[has_member_qualifiers]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

/* has_member_qualifiers.hpp
t4TytFKGbXxqKip372HiuxRbMdEWB9dqFwvXVf2dFWTS5llCLdRBG0EdNb43/gBQSwMECgAAAAgALWdKUuMTTu5kCwAA7BsAACYACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3NtdHAtbXVsdGkuY1VUBQABtkgkYK1Z+3Paxhb+3X/FKZ0m4IAMTtI2tuMpxXbK1DYem0wm9+aOZpFWRq1eVysZc9v87/c7u6sHhDTpTGkaxOrseT++3Rzs/3OfPdqnL35c/b+LD771jps8/U16xW5q1/2TzH/Y9QHfXxJyQM2WP90efXnLn9TVW1wr5YSfXfdLgj6wbvzXAe/84PIjVrCNd07SbJ2H98uCupMejV69+pEGdDg8HPbpTCShjOiukMlC5vd9OvH1yk9L8fjoKHnaJ1mQiBzLar4MFak0KFYil4TnKPRkoqRPQpEvlZeHC/wIEyqWkoIwkjSZ3byfXr/p02oZektmsk5LUsu0jHxaigdJufRk+GB4ZCIvKA2wHcz9UBVgWBZhmjiQLamQeayYB4sXkUpJPIgwEgsIEgUtiyJTRwcHXplH0P7ATz114FXmO8siri15DyVisaY0K6hIqVSyT0zZpzj1w4C/4RAsZuUiCtWy32gDUYl/kOakZBQxL+wL
*/