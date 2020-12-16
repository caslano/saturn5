/*
@file is_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_noexcept_hpp
/*`[section:ref_is_noexcept is_noexcept]
[heading Header]
``#include <boost/callable_traits/is_noexcept.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_noexcept;

//<-
template<typename T>
struct is_noexcept : detail::traits<detail::shallow_decay<T>>::is_noexcept {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_noexcept;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_noexcept_v {
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
constexpr bool is_noexcept_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_noexcept::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none
*
[heading Behavior]
* `is_noexcept<T>::value` is `true` when either: 
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `noexcept` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `noexcept` specifier
* On compilers that support variable templates, `is_noexcept_v<T>` is equivalent to `is_noexcept<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_noexcept_v<T>`]]
    [[`int() const noexcept`]           [`true`]]
    [[`int(* const &)() noexcept`]      [`true`]]
    [[`int(&)() noexcept`]              [`true`]]
    [[`int(foo::*)() noexcept`]         [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_noexcept.cpp]
[is_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP

/* is_noexcept.hpp
9t9vlXij9fv/lemi9TazsvaxzX9RjCc5yTuc325FHlkRNX+f/TDdP8dv0u+SJX1vleXeoft5KIOUux+8HUv6Pp9yTy6acRr5VJa7uKRo/1oFOm6czBsbyXa+bHcyGvFvGno6+hvqv1ZBc73veRK/g9GAcg1CZ6MVqB4j0vk3kfSFsqZaUa6sBeCZ/41FxvbYr2jzu/ndJewo+iCbqTr6d6lhMsdnBHZD7Ocza8PFqD1zf/Crixgn489l+LZeFH9r3ybVYt0Cj2/xiw4b6rdGAT4314mgH0skT/v8FO3zXcTx83lmNrWZ9Fa+12mamL4PM9jmV5P5dwJ6BdrKsPZ9sMQfaSSRzynoZWgLQ/vezD/a0vcvS/p49q+56fs9RvW+f1DsF4vvswP4flzEwfd9ZX3fo30/XI8vp6GrsGx0+Pi+IPc00+fmPuv3DThnZJ/1NrM6nHpuh17z4huz/JZrXgwnW595wPRFimSg9dEx6Cl0vLZ0+pcrM7dyHb3Wcjwn5WdNLtZjrpXxI+VYNGS7q2wfxYp+BsdjZORe9n8dvzWT8jkjgx3OBsGO8OZVyq73verxHiz5dWfvQyn/qMjaHqPWcjykrD7H49oQ/U6OTjQO7eee/7x/v4tyT80tKs5VVdZC0fVNx+1OfQqTsNGEXSphGYQkmtfQLyXM0OPF5nbANViONvNN0dtmfK9zqThvTq6nHOlm/H6svddQhzF7VML6ckQ6yLlQKHuZbR6vt8UeoefCM/oq23GqLmF19P5ytMwybRJ7vH+Zapyn4T4OoQHWUokIsOZKjHn+yP7pa1d9OV7ryETOZn2fy0b7crwiXHK8inOzM7PymSTAURMq62uXTsN1XV+72sv2WP9rlXnetRV7jN53SR/o2mTeU9PE3s2s25c1dt83a75fyjduA1xXUgJcV/bAAWSeLmNPt91wy+D5Ludvqdm9bi/4oFcW4zRd3OEV258IverMs5cOefOHrLxxbXYwPiJjWzuXtLym81MFFWfvXvngOStb3CnjOoQXlk9f8P2udptfXTYortOHKY8pxdgK4XOilj/xxMzY48pvnLp+R/txPZW6RfK/t/+IPRW9e756+efvP5ttZL944GNnW8Pc4U+HN9iQ2b37k/2COh4xs3kaHfJXy34dNSo79sOMPZ3CCuN2nNVjL+U50+kOv/H4Z1z1FvxyV+t1W1snXj+8n/UYXL1Qd3hS0i1jP3nll5gx206PG3N93CbGOWS/ZrZo33Jd48vu/nn2/QtfWrSbi193CT/m/tWj3tt357Bvbr/iyjp3tLmOeeMyVrg4beKQH+bve+TV0T1HF1zw2AYZ1yF8V+oxcbMSL1ryaEzfi8J2/PYFz3id3eGvnP7q5n3fX7xn9uIWje9dMo66slDCYx+fu6QiPuOR80uH373g4bVbuA6JP6PDc4a9NHrn9A5tli+aO/v27znuEn7/xTMv7bTkgUnvN/51zfeJrSjkPsnnlIdPXxmxNXrV8HM+G5+/N+MG+v8d7vD+LXN/OOPkyR2dp06uO/fz3FeVWi7hb1zy4ebU3Lwbzv5uzsR7Wt8WxDxU9lefwHJtnmJ46tpuGSOtfB4kXHlsYXCsjo/L57nZGTbQ29EwCbaAXWEbmAx7we5wJOwJJ8JecDfcq/Szln4e5HfknZSd+neG6fxHwlZwFEyAU2E7OA0mw9EwBY6BA+GxcDQcC1GJf4KOPxFmwGnwRLgYngQv1Pbr4MnwATgeboCnwOfhBPgRzIKfw4kwnDJnw8PgVBgBp8GmMBe2gJNhirb3g9PM/dfPOzAvwP4XEK8JLNL7Xww7wBLYB86C/eBSvd+XwBGwFB4HZ8M8bZ+h7XPgmXA=
*/