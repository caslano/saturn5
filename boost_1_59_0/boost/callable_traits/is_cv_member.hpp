/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_cv_member_hpp
/*`[section:ref_is_cv_member is_cv_member]
[heading Header]
``#include <boost/callable_traits/is_cv_member.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_cv_member;

//<-
template<typename T>
struct is_cv_member
    : detail::traits<detail::shallow_decay<T>>::is_cv_member {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_cv_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_cv_member_v {
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
constexpr bool is_cv_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_cv_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_cv_member<T>::value` is `true` when either:
  * `T` is a function type with both `const` and `volatile` member qualifiers
  * `T` is a pointer to a member function with both `const` and `volatile` member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has both `const` and `volatile` member qualifiers
* On compilers that support variable templates, `is_cv_member_v<T>` is equivalent to `is_cv_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_cv_member_v<T>`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const volatile &`]         [`true`]]
    [[`int(foo::* const &)() const volatile`] [`true`]]
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
[import ../example/is_cv_member.cpp]
[is_cv_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP

/* is_cv_member.hpp
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
*/