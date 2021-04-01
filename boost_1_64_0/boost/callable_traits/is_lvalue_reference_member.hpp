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
v8zOLXAWCMN0CucquOqq15F6OAXwWuAC1ImRb24RPx3bBTUpVj4cLTviNMV4LkpMG7Pn+b0m0Zao0+1dHPPaS6R4DLqz6hC7d4PSEcZmQ7F9+gIldPjxXQ2D9JiLnIK5pdycpwWHLAbyNAlMZynPJHtIvQ2H3c/N1AdoqnDhh4QX1mhUtaMHh86kTXIMXhnKdjWKd47KWLdmGNRCXetBOltj3t1cuUQnqewqPFzJOV/oDbE0lNR43RRWnCKOzuVV0nizrPJzlj1XcZtwFTdB5oARhFxB0h8oTi/1Oxdz0A4FtB9h+ugh8aa1vJkZlcHeztB+m6hqxWV5KDl4lDff2nVuGnKgkluNuXrkONA17aQfHBNoUGfntB7c0srALwzHLpxmBFJbBVE94eX3NX/VSl1s8MTS9uVir4OVTQlVCZWSVOoME3fqT5xsapgMIpllCNOIiWGBazXl+zKWlyKHkc9k1sN0bqz2HSY+pQoTZYxojAjwhElZ+2LaA9jF49JjNztFWaQCMJz3Oz9LJ1K6YNh8IlwKnnVh27yK4EDqXqNgPaOPWz9cJl6RGg==
*/