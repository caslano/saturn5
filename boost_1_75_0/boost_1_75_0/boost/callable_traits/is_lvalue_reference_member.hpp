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
3GvXC718xua176VEY0RyD0Uj1lfzyYh1Two3YkEZKfwzMmJ91qQRK15uZ/rNYEQK50Yk5fHITWREipe2f6rdAENvw4c2swXm2U+bMV4Jyn6Nm+C7kfy7yuP9G+m7guT4VGu8SpReziN7Ep8IQZySqBqvfjUp+kcj583n+I4chHz2vbbA3FCCeJood+GLTzQf4uENOmXNgtMGaMfqwf6cNkNUp03KXO60eT+PnDbqxpcdMxptfPFjpSo9rCXbY2djc8nSklxvyvrbBlp2yXzZpW7G4SSzOt2pToqU4lOnZIN3gpdBVCdFtVKN3KxaqXLa6sjLrJqoHtvgZaL6bZOviapc+syp3fjSdO6I1m01G1/KOO0+Ge2TOII2vizehIIDJo7w2vhyJoPcNUXR3Da1HSPDaaO9T8YIjbumGn/Jdqn8MN+MEZqNL9VaycT/xpcbr/Xa+NJ79KG/ZZeatcyP0NX7O7URtEvtO9SMXWrmRr7x5eMQtE/sOdiEh8aU+wXm8PNrnioOVFcKMiSNNQUBVdGmBXxl5QM8JdEPC7z5xPCPvFMSFX2GyJdKfKVQWudTvgMvX8jLL6TyheoSVfjKks9UvhLVphFf2bXOi6/c/JlBVp+1fEUKGMWZygTUPbl5VgFEnU5RPIpDsUCqN6RS9co+l6eoAMWIynYnupPtTmhenwrlBmNsqSnvKpqqVL1GkXzmU4P6JXed7E/2
*/