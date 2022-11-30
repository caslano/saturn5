/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_rvalue_reference_member_hpp
/*`[section:ref_is_rvalue_reference_member is_rvalue_reference_member]
[heading Header]
``#include <boost/callable_traits/is_rvalue_reference_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_rvalue_reference_member;

//<-
template<typename T>
struct is_rvalue_reference_member : detail::traits<
    detail::shallow_decay<T>>::is_rvalue_reference_member {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_rvalue_reference_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_rvalue_reference_member_v {
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
constexpr bool is_rvalue_reference_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_rvalue_reference_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_rvalue_reference_member<T>::value` is `true` when either: 
  * `T` is a function type with a '&&' member qualifier
  * `T` is a pointer to a member function with a '&&' member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a '&&' member qualifier
* On compilers that support variable templates, `is_rvalue_reference_member_v<T>` is equivalent to `is_rvalue_reference_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_rvalue_reference_member_v<T>`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*)() &&`]               [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::* volatile)() const`]   [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_rvalue_reference_member.cpp]
[is_rvalue_reference_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP

/* is_rvalue_reference_member.hpp
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
*/