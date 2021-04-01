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
ouU5ABEtELVAd6TUdE89uJsww6n3tpQst+OysigDwy/vZbUrW/9T+f9pkIpKhso5TppdYDSmMvuGRMErJtLh1H+s1WMpiyPAxEyNss3dgSn5B+eGQzWiZaHXROFuEAHFrRaO6tAp+2syjh5qTshEbcy9eRhjxcsX56GlLJJbp8/dgoUrp4htC3EX4uzefn7nnBFDmsOlvnbPHmmTRQU/W0fkHea2kAxYISCERocf7k4lXF/+VnxNJ9etWDB/tBmo/q0wJjpnRBHaj7uzTkn56AKBm2Koj9++D64bpbooVIflSREtOblmeUTlwPl3PO5wvZMO0cFGZ73mWehxdUL7ulNZb1Ze7tU3N4mMWIcDVAN3obTrlsAXsjfhx6hOZyAjAfXnptFUKR8hP/TpZukz2DJsLSzc5GX8TCA6ntqZ0J57rwt1/HvrSKjpmwGjhjuN/7Vr45iVuZMsGz5y9dfDDzRtFFgtX7c5j9gMCAmBsH4UpX0TfVLAUXiPf0Kc0zIy6yywSQrRZi0pMriI/SSqlw/b0hijl4lmkLO7hd/Fi50RDaYzyi6FggvArA==
*/