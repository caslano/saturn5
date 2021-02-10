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
fKZL42/smEz0jq/x3e3kZt5v8a49+E4+zauDg4CjomghgCWCMjGBY2ifYVuw1q6ws5G6jV/4VGCzbAcC6jn6AGk89luJhlaaWNT63Z6Pz87G83FVd0VqmFViBV1ML88pSzXAZ4V0H2M45nxV8rCAi7fXk/l0dt3fAjRf48BKwT49aVrq12x8e3M5G+N0OLqs3T3HQbh1QEPjhrNx7EBmcX9jXqhxrqeWaaZ7Ii9d86obGzm6gVacbzGfc98cpXiamMFtinolEdlEez4SRdU8q7mDPDNQoZUUlodKwUOYTFisdXpwouCMjlKOydyViJVYf6KtJalUfbIxCI0g6AZbNl9UUGoLyeAbLjJYKfDZ2/gykHVjaZWHhdxak4+ezMyaGeGPAU/BwahZyz3zrCc4w2xMr2N2RMugwAe7GiSRpuJzIu/TmEXTak0td/0KTKYYe6FAEcvmrsfcAGXo8Mq4jujizP3X+e2s+8RYZpFha1Ub9+mytq/XiLvjeyhSZVjoyx7rO66bLEKgRJ6W1fixki1Jg+Csa1rrG8BtI9CWqA504warKmZ9yzWnGpebKO+Q3KKsoJehBJct4lNA+b3qXu9zJhDJSMldZNaitm7faYkVQjQMPtZ+veds2o6dPhTqW6dcJCqQTThjbxP8
*/