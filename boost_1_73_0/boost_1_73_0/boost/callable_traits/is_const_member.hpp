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
K4UGhsL+7NnGSc+0ZxvScou21MQHmljrx7WC+ZS0PDp5e3tJ+zxEju2vK9qPq9+8QRVhFLl5mSQ8FF/T6PjTQMSZq9tE6xWzcBXQVEH79TRR2M8OPf5cQTVZpP3b/HSanKq9r0XcR+lCRG6YhEWX1XffXM5+Hl+6Z+cXY0yfXk2JbXqDFGptyHVYUQHf8HqvnaYjvStub9MdeGtf/MnGwyofK7jBWcYuDjCbgYVzDTDQD9D9TN41OilZAKB2eaGvIzG7mbv46lOHkQWgrsYWrVHb6VXitoAC+ABGQ37ylAOYh14RrSvYgAacAqYWHE6g1RXCi1cK9iHebEwNTDQkqvDY1Xh6acYmJMcMd1eAjHbgGFyhm4JDY0bKzEaURQrOGdoewEr7GMAoTG/MeQ4oOchEsTQg2pJhaPhQ1gOiNcwwzlgN4fsaoNpjR3u/OXUQzL2/x7TymSB2aMbTexUy6MfT2nAzk8kTqBGtTOJHzDVK08yhOzMcCbNohB+eduYL56XzUscxhlFAdQVH0tHsviKQ7D6X3dfXTqwjN/ah5yqlpkb6xrbQHJBCr4wwLzyhdMtaQ/Pc+NS3LjEGMdhh9zFysT6SsnaTQQB9ANai4lKN7GRNv4fYmAaGUa2IY+zaKN6mql2RZfBat633
*/