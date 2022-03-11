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