/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_LVALUE_REFERENCE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_LVALUE_REFERENCE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_lvalue_reference_member_hpp
/*`[section:ref_is_lvalue_reference_member is_lvalue_reference_member]
[heading Header]
``#include <boost/callable_traits/is_lvalue_reference_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_lvalue_reference_member;

//<-
template<typename T>
struct is_lvalue_reference_member
    : detail::traits<detail::shallow_decay<T>>::is_lvalue_reference_member {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_lvalue_reference_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_lvalue_reference_member_v {
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
constexpr bool is_lvalue_reference_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_lvalue_reference_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_lvalue_reference_member<T>::value` is `true` when either:
  * `T` is a function type with a '&' member qualifier
  * `T` is a pointer to a member function with a '&' member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a '&' member qualifier
* On compilers that support variable templates, `is_lvalue_reference_member_v<T>` is equivalent to `is_lvalue_reference_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_lvalue_reference_member_v<T>`]]
    [[`int() &`]                        [`true`]]
    [[`int(foo::* const)() const &`]    [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_lvalue_reference_member.cpp]
[is_lvalue_reference_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_LVALUE_REFERENCE_MEMBER_HPP

/* is_lvalue_reference_member.hpp
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
*/