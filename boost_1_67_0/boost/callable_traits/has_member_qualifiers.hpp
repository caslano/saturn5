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