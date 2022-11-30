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
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
*/