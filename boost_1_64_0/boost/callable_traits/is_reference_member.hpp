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
EzYvDmSOmYWv7vnS/4v094W82LB6XFL+aavE2sRpdfZhVP7TbZmSLd5uwCepKXCU18nj187efw9cbE6o3AvC5AUcF+xafmKp5EQ53jzijbMCwce14UF3tN3uxg5O1laWvPOtl1/DQcr/misSTGo3lLRddSM9Kk1yXcGkBD64mjH6f26zWqtJGFRN7xxgLrJnp6Q0u3Omj1UTzKxfnyjwFkzcgsU7T39c1at/42qPVQTq5g8S0trU3nJI0tyz9PVV4qKm1ldxa+I4JEXMKElxdFJI7tlVTpRAglTFMK2W5sG6rWA/1j09b/9PHGA3s8c+bdNgAKCH9fjXIpci7lUJKZm851QdwLvYenWmi/5NONpmYclK3XjXZlT85uTARc56R2cPKdZoy6nhEJYwULxgbv4OjizCty7a/C6W1tFxegF4oYJE2eO/KRS19jtHN8HiMw4ITBZD93rVVtq5GKetV2CkJLwmMuxDZRUgQppOvGAw5mZh0KLl9tbqTdq4hEFfHgOgAlD8YyAwgRAKhj8wJXJ6Qhye/ak9SJjK9jv9dzcs6hwNGL+aMZnczw==
*/