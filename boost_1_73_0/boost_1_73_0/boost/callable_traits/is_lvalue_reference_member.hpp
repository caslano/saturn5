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
CZHrAuVhOFkIUfP4G0Bhh+pWffC9yKUZqvqojCbSQs8NIjEAOgCti27R3YGCxxEwjCIvkiIps0/ATC7j9EHuRl8bhJaBIdmCiNW7zVf2BF697B1vX+78H1BLAwQKAAAACAAtZ0pSRDmMT6gJAADYFgAAJAAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvc210cC1zc2wuY1VUBQABtkgkYK1Ya3PTSBb9nl9x19QudlCcB2SAJFB4HGdx4cQp21mKWqZcbakV9yBL2u5WgmeY/77ndkuWEjJFtnbMw3p038e5r9Pe3f7rPlu0TT/8zN2/OT74djsudfarDO3Dq+fzb+T/YNdnfP9IyS7VW77NO/TjLd+o7bbMSy0nfD2f/0jRZ7aN/9vlnZ/nfIkn2MY7+1m+1up6aand79D+69evaIcO9g72AjoVqZIJTa1MF1JfB3QSuSfvluLr166RbwOSlkTSLUXNlsqQyWJ7K7QkXCcqlKmREQlDkTShVgvcqJTsUlKsEkn98eWn4cU/A7pdqnDJQtZZQWaZFUlES3EjSctQqhsvIxfaUhZjO4RHylgILKzK0i50S7JSrwzLYPUiMRmJG6ESsYAiYWlpbW6OdnfDQiewfjfKQrMbVu53l3a18eQTjFiJNWW5
*/