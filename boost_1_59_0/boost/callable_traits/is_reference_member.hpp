/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_REFERENCE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_REFERENCE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_reference_member_hpp
/*`[section:ref_is_reference_member is_reference_member]
[heading Header]
``#include <boost/callable_traits/is_reference_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_reference_member;

//<-
template<typename T>
struct is_reference_member : detail::traits<
    detail::shallow_decay<T>>::is_reference_member {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_reference_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_reference_member_v {
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
constexpr bool is_reference_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_reference_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_reference_member<T>::value` is `true` when either:
  * `T` is a function type with a '&' or '&&' member qualifier
  * `T` is a pointer to a member function with a '&' or '&&' member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a '&' or '&&' member qualifier
* On compilers that support variable templates, `is_reference_member_v<T>` is equivalent to `is_reference_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_reference_member_v<T>`]]
    [[`int() &`]                        [`true`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::* const)() &&`]         [`true`]]
    [[`int(foo::*)(...) volatile &`]    [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_reference_member.cpp]
[is_reference_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_REFERENCE_MEMBER_HPP

/* is_reference_member.hpp
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
*/