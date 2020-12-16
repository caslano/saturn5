/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_const_member_hpp
/*`[section:ref_is_const_member is_const_member]
[heading Header]
``#include <boost/callable_traits/is_const_member.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_const_member;

//<-
template<typename T>
struct is_const_member
    : detail::traits<detail::shallow_decay<T>>::is_const_member {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_const_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_const_member_v {
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
constexpr bool is_const_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_const_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_const_member<T>::value` is `true` when either:
  * `T` is a function type with a `const` member qualifier
  * `T` is a pointer to a member function with a `const` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `const` member qualifier
* On compilers that support variable templates, `is_const_member_v<T>` is equivalent to `is_const_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_const_member_v<T>`]]
    [[`int() const`]                    [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const & transaction_safe`] [`true`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*&)() const`]           [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int(foo::* const)() const`]      [`true`]]
    [[`int()`]                          [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_const_member.cpp]
[is_const_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP

/* is_const_member.hpp
cdgPfgTP87knXv3h1+BguOI05wdC1shE18S0OF9wjPyJL/NaA8ui8wbRK3pFr+gVvaJX9Ipe0St6Ra/oFb3+O69PaP4/P+8szf9/1zb/36DfqD2lZ/M+hhT7BlMuCI6bE/Kp5/8vCJ4lvQjzLWIuYJwvJuJegbPQuUN07gnO/Yu5R7P5eT0PWe9vtKrws9m8NzrFYTpes668IGRvtI9EJ9nYuZHuMtbZzazDPyo65faxcTM38rLcO9eMlX9DzEPRxU8dK98ndgPIb6+ed6Bzoq04izd8vm5chL32MiLMy80Mm4PTvaN0Dq7gf2qsfZ6MtY89kdQ/+0drXclv7m0/8Jkp3/rvGmtfZmm91XbYqPtNzNVKkaBjpJ1gD9gFXg5TYA1MhRthd7gL9oSPwbToWuezMnaZGR2zjF7R65/snQlAFFUYgN/sLpdiAioi4gkqniFepOaBkkdqaFaUGSKgoogIWGhWlmWaVmaH3VlZWllSmV1WdmtZ0WVWVnZfVmZWVpR9++9j3F12AMvsmr9+P+b9771988+b4x3zxhZbbLHFFltsOeTt/+yD9v7/eq/3/zdSeIQZ7syFgHVgbnPyTvKa/1/L9/89afrpueyEd/Ws3daU2dHEIcxQW5JlnTJlsSaAzqOPub5/XcljuxHofQD9frpO08OYoJ7Vc6qZ5S7pHjHGq8GEHqaSjcEWawQwp9/MI8lcE0BJ+s8NvzUA5DdHYW8r9lsNZn37zNMnH3POfWHlNt69khlL0408//f+zbUPgiS/Twxz/r5XXua7BRZz/VP84s7ze/e/ct5qlPzGC8YrxFob4P3/KN2/MUfifYj9WbOPY5SEGUYndVvA9wNCxf6i4ba1NOeL6rmvYgs2+0/WSR2IMefRB8n2Z9gvVWsJD7AegNl3c4nk9RWxHvFZr75MwnfRg/MQZRbfm3WA489/Zrmylddak7fLb9f3f8fe9MVxksdOenYe9erHQWvZj5MeoB8nI8C86wkW79FPsXiPvjDAe/Slvu/RS9i8APOxC//D79KftVDKc/Gvl0c+3mnDlKfaTrt606in/139QZ9Vns/6urwRxqLbvb6/2AY2h0NhCzgRtoRTYStYBOPhGthG9wclwu2wAzTIvDMMh11gFEyCrWEybAe7wV6wO+wPe8AhsBc8Gx4Bl8G+8G7YD26FA+E7MBV+BAfBT+Fg+A1MgxVwuN0/dVD6p3Ls/ilbbLHFFltsOeTyV3//jw//5+fn8QXA6fn57sX4Dtb3/+5pzDOb7geYp+cB9NLf9UlGxzcnXPcD6DK4f75rcorZGWDVF6DTJVu287Vd2uTxAd7zT/fLY0Tzqt/2M+3+bXTv9+a92sWFAdbdM9vbfnFLvb6LNzzC09YbehDbevEB3rGdAkeY78TVvp0n7bfK75hJ++fuw6975bUB3ds+8VWvbcXfLH9A2hVe+yjHGfH9rnsj/X34aJgMY6B844w3/rqj5W+45Fl0of28aYsttthiiy222GKLLbb8T+WQtv+n5xUfrHUA13q9B7BBr+sRr9v/sWgGbdEVh/u2/3Nyq30PQMePtWr3a3uDgG36dNMeb7a9r9TjrIkHcb78CN91Z0wfbHQE9kG5rw9qfBeivAYflNfgg3I/H1xzCH1Q4VQip6D19dz0ccRVvv1A5jcho0wfzCrOLTqaEH5D/KDTkFMvva/1JN7EvJJic/xdx2lkvr/RSLaHqXZ6zP5EL/9E6/dGoiTO0eTLVx9R7TedV5Tpt6tqMUYf7eM3cx9M39WTcCmz6bsTTd/59r18IX0v4S2a5fQ+6+yKe1XaRWmu40d5+l7IS9dt6pfXdaOT/ruV7ntpDWNhPGyutyvTl1c=
*/