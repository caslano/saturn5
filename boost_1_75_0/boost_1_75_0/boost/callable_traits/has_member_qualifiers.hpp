/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP
#define BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_member_qualifiers_hpp
/*`[section:ref_has_member_qualifiers has_member_qualifiers]
[heading Header]
``#include <boost/callable_traits/has_member_qualifiers.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct has_member_qualifiers;

//<-
template<typename T>
struct has_member_qualifiers : detail::traits<
    detail::shallow_decay<T>>::has_member_qualifiers {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::has_member_qualifiers;
};

// older compilers don't support variable templates
#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_member_qualifiers_v {
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
constexpr bool has_member_qualifiers_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::has_member_qualifiers::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_member_qualifiers<T>` and is aliased by `typename has_member_qualifiers<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function with member qualifiers
  * `T` is a member function pointer with member qualifiers
  * `T` is a function object with a member-qualified `operator()`
* On compilers that support variable templates, `has_member_qualifiers_v<T>` is equivalent to `has_member_qualifiers<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_member_qualifiers_v<T>`]]
    [[`void() const`]                   [`true`]]
    [[`void() const transaction_safe`]  [`true`]]
    [[`void() volatile &&`]             [`true`]]
    [[`int(foo::*)() &`]                [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`void(foo::*&)() const`]          [`true`]]
    [[`void(foo::* const)() const`]     [`true`]]
    [[`void()`]                         [`false`]]
    [[`void() transaction_safe`]        [`false`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/has_member_qualifiers.cpp]
[has_member_qualifiers]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

/* has_member_qualifiers.hpp
rweW476EvdJVvOY2/uLT5XRv4s/fVltMe5mKLFMfTeGP8njtLLhKX0w979kj7Z1Kn97Bh3QnLzORX999RWmmE/b1ZV5hySv06cW8Yi6/j1S/+9NLUOF+XiGEt+jhvRn/Cg6uXBrJa/7MX3z7Mt0fellp6aWXlJ8FL9HbYl66kF+DeD8u4ODO3kEffeZlJea/2VjDb+/Vxho6XLYyDDRMyqY4w2W2mLNW8WyCKz1qgs39qN66yJPApT+yi2FElZ7HGwJlA4nh7qsRaxVLWUFfpJykOGAwlF6JN4y/Wo03RDrnoug8Nw+BsH1LnLDAV1CF11YI2QUx1X1db3ADuG+acZaU3qQItLiL5JjH4MIBL1NwofwkVUp6yftJijTvRe8nmdLYKIpApN68/41Bp0Ygng2GbBsbq4MgP8PoztD5rLWCO2mtVHGbfGI3blZzbYzA/zHDgms9z4LQ+iluP3W+ptAYeCW9e8Dbfnr5N2Q/RRpGJunLfKo8QlXwJecRtV+TdIMkBOxuZ4HGGKzit5BXgUndp79WjVG9+uk04RjY5FUHvIwUL38N7g45HCNcr9hVK6Qp93Nj1NdojFov74ZPo9mmLexgLUJtvbAvvF1ONO2IKXdpX24kWoxokpFv/UjPGjESrEg7zcML94i8WBqsk1a7CNfG9PXnEannhnLFIxKJHzUcg6xUnIFwn0h78oksRepeJAXqaofieNtU
*/