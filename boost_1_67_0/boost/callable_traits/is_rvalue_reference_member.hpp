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