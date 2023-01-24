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
GHSf76xKkHm0Jsh82AQMMr+MW1cmDVODzJEK1gYy8DAR9vrd/uRi1ZhyWGNMEZ1lUsBzemj3Bocro5CpX7jlctitpNyhiCZOKQRLJyQh5idQQB5eNR+6HBWcHsZjiClSPd4rUj3V8leR6m1nU9TzWw/StSENop/r0+huCX+6mF+r05QwavsDEJtdcS2FSZemUVD1Zl6xiN+Pf1CpEPEAPXoZv/AcrziQt9yXXx9Vv3BsFnxhFi84nbc4hX8hid+fekCpsAErDOEVqh6ggpX8WvYAhovvkbrymkX8xfu8Y4H8+Qq1xbtn8fGrj8bOolIP89qz+XUHDEDaHE0fL+LDGc/fjuLXFSo8jNjbJ3mFJx6kZh/lFf/H79urXz48EypM4RXO8a6d4lcbr3gT9uMGXuoL/nY3v/Z8UDmbNNLnbNKVwoLjRKUM7eLkTMmJDpFpcefii/RA3aIhUDTDiNHqSUYMVZfPGmyHWQkwRMSU+1IrVFTJqZEkR6ifba0mQi5kbZeAZuQxv/M+8SpSX50RsOPYfSvkv00QqwV39yWl5MHqjgEG160uQwtuMR5OJL0+C3Vquk2Ujv/+J2ZkZs063yfDt4A9OoFHIQK9hpOcpMw+cli5LdaVEe3KEMhnad6cEswj2PXpMiFxWqS73zjvUTlFqMd8+D0DtpeC6eYgBn7fHE35QXL5VF5+DS+POWrTBIp+k+PHP3xPE/2G
*/