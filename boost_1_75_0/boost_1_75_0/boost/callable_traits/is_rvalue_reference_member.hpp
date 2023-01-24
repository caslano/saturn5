/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_rvalue_reference_member_hpp
/*`[section:ref_is_rvalue_reference_member is_rvalue_reference_member]
[heading Header]
``#include <boost/callable_traits/is_rvalue_reference_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_rvalue_reference_member;

//<-
template<typename T>
struct is_rvalue_reference_member : detail::traits<
    detail::shallow_decay<T>>::is_rvalue_reference_member {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_rvalue_reference_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_rvalue_reference_member_v {
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
constexpr bool is_rvalue_reference_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_rvalue_reference_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_rvalue_reference_member<T>::value` is `true` when either: 
  * `T` is a function type with a '&&' member qualifier
  * `T` is a pointer to a member function with a '&&' member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a '&&' member qualifier
* On compilers that support variable templates, `is_rvalue_reference_member_v<T>` is equivalent to `is_rvalue_reference_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_rvalue_reference_member_v<T>`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*)() &&`]               [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::* volatile)() const`]   [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_rvalue_reference_member.cpp]
[is_rvalue_reference_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP

/* is_rvalue_reference_member.hpp
NtLJkMf+C2yqZrWXfnfHe0C/niL6ZbOQctf7Jq7cbcTtexllNHCEfpknMVn266DeMKUMjYmbW/FcehtaEWiSdyZEXauHX/EUHquk+g2b/UKwTpo/iWb60VZAM33C4ZyVXnbEcfglw5YcypsT2yhvTqy09JNAOW/OL2/KEeJXQQQtZEF/9g2yIH5u9IoPh1fjrjUwGdO6CeyHNnEnG+JKqjOmH1oPX04l62EfB1kPnSulg2vIdPg6SgGsP2C/s/Urx+oT6LjOWGlAX8z7qtx3fSuQzsDKlJawBmzuW/6EPQn08vu+fqyFGPztXCtNx+9l3KB8S7UVZlP1bX3wW/Jt4ZtkIcyW+q6hFDmxaGabPxuRCqGLhjnFOCjhAV74wsswWAZGEpFNH5tCB86lYhPs9Q4GMefTJ7e8ITcNFgiccW4LnBCVDLauZb0veOQcbI1DuDvB+VHTaLEkSytnQ69ZWae4AxlnhbR+HClax/WyXcUmuTKqXRn1kP8Gze42Bi2zcwrn3AVpygKqks68pmHbrT3me97GvjMYmbtRhWXSVG2FrbzCMl7heqqwTLX+Od5WI7afCyacj8WQbVY95zWveO36t8D2Z6vi0Qi43KTNg+WA7ZGs5XDZ8mcLV8x+UcHcfMeAkAQHW0jnu3mUcCNT7ko0+L30FnYtvOZpnVLcbTbcFYxh4bu68eDsYwZ+DJU2Ojsj0i4+pdj6bJFq
*/