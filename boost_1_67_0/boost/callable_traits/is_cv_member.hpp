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