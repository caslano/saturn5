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
f39v77P+nLYCXj7LjqjFVrbqZ2eAjp86F1vUHpQIXRmpO/WyfsiLYDaW9NKsLJ0Hl57DcXEtd4anR+i4YfQyXDz/aWd/P1rsvHj1Uuy8jp+LHfnT4YF4/eLwlYyjdy3epuMQcUMydJto1GKnxYKn15EvHxTMRv/KK6yX+itCBchVjjxKGHLuO+pGoVCWUiCGVdZkEZIPkaLJWf/w+cEBB56xQsLxu6orlUoIsdHWQIaW3fsa+Qq1Ebruv0DCUpK5hs8GmKB+cT48H5BMwyySEc8OhPFG6oa8/lKGXyqL6ucXV6PR1h/HnCG6QFUUuUsKzpfCuJRQqfXa5hpeHpeLXToZ9Zuco1mXmWSyQoeyXaaX1UG1gL82N+lKrhYB3WQqom3MEZ13tljPgwZsl7eh/YoMbT+8puOkHENGM78jYQVMhQNxu8266c0b2gOrAGlwNjTu3ftt97RDJ7Tf6TjXCVVtMWZoj4X/wcJYKiy5Uzy1jTtva6R+qZTzlkpeiUEiUwiBN7jw74/daxgQ5uu2w44fB7yyfPewlmfPnJqNpVi/sbU2HrccRvTTtM3Ae8T7V5MRbXOzOi7vOH2Im9gbdzuYjz8c16HhlXOD6W5pGyREYYqnltdyEh3/WQhru52l9W239gIy9txb1znf
*/