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