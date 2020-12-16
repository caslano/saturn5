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
vydY1tuXJP44y3rbrolvvV0dU30dmSP2NMt6u1vsg/3LY9oXyO+tMqzK84XYQ8zyZMv2uZblGSD2PP/ymPbbxJ5sWB3PPWIfYHm8u8fK8ba0ny32WZbH88VY+X1Lu5Jreqpl/iPEPt6yPiwRe4Glf8LlOfFXy/z7in2IpX2+2Est7b+IPc3SPqCZ297b0j5H7BmW+3en2BdWqe+1aTMlWvbjea8V6tXm0O2iWcGSxuedifzGgftEy1v5tYcKDqxPtLxVzX2i5a1q7hMtb1W7PlEd74C+P/J39InuaqZE0nSf6F2h4m8eov39feB9op48hlXncx1nq7XPzTiba/S5xGNPrPpA08W+KzRQH2gkzIp326+iJ7OPMYw+ysWO+UYjVx/jhKA+Zh/oPZLHUukDXcv181v6QLs5Q9Qj9IHuCwpRA0NC/NuAZv7OBHfay+ih6msMNfoaCxwLjYauvsbxQX3NPtBSyf9R6YdcTMvrBfpA67t4DqZ/8G1SNvPvA9X9wa0k3TLLPtDLdLmr6wMdL3HKq+0DDY+XY+rqr14K2J8TCU+ROJG0Veua/TnfSN6nufLVTVX7c/Q1dIvEmenKVnc4rZ6NDpe8B9Mvts2yz+kuXcY+6lXLMqqEqmVcKulOp1/sRssyTpc4Ra4cdbtlGV+uRRlHJXjKmKq2WJZxRYAydpWw0+gnvsWyjIcl1OzHmQk1l3FXQs1+TG1TtYyvSLrSav24NqFmPzZoU3MZl7bxlDFNbbYs4wcByljcpub6mN6mZj/eW4sy9mzrjlM/aIa6xrKM57atWsYYCSuhf3OlZRm/b1Ppx1sty3ii5LPTdZTa9Kf6QKOxJVrcg5Is7kEp1dyD9sAJqPMC97zbiM/vWT7mm/Wjux79wIWPpqZkKnX54e7wZluz6+afcvT8d8MWFCa0T7+J/paO7vBblk8as8711TuP3Nx239WXLbyZvv9O7nDHzXmtE8784YjYvbGRjdZPfEt/O8ocF+XUD/Dtp1iHZ/5uU9gUNoMt9PZuWG6O8cn4oUhj9Cmd/itulrHwW9gM/gSHE/ln+DX8BV7noOywOy/c/Qrfgr/By90F4XdWwDC4EYbD8iBPeprUkn4drIAZIZ70P8Pf4IOhnvRPwAj4EoyCn8AG0KC8DWET2AgeDqP1fjEGrft3pQ9aZCg6Qo9NDyT/ODgYDodpsAQeBa+HQ+DjcBh8AQ6HP8KjYSuDfGB7OBJ2gqNgCjwG9obpMAeOhvPhsfAKeBLcSRnGwWud+Bye7KJmwzyYBRfDbLgV5sC3YC6MwW+TYR6cAmfBPHgTnApfhtPgTpgPv4MzYDr+LYRj4Ux4ESyCN8Ji+DosgW/CWVDh/1NhE3gaPAmWwiw4G54J58D74Fz4DDwLPgfnweUcn7Oh+7jMh1nwXHgRPA/eCBfAt+D58H24EIYxNXwR7AuXwPHwIrgEXgzXwqXwdXgJ/Akug53r0u6HE+HlcDa8Al4Pr4Q74VVwF7wWNgnnnIHXwJvgq/Bm+ClcCWOpL7fC4+AquALeBm+B90Lzm2utrM+7j4lXD34Cm8LPYAu9rc87/VxH3Qtw3j2gz7sN+rzbCNvAp+AQEj0NP4bPwCXUp2dhO+rTJvgy3Ax3wufgIgq2BS6Dr8E74RtwfRD56HryDLw02JNPjxBPPq/DzXBQKPno47oFroBvw1vgO/Au+D7sTvnKmN+/BXV/621TJ4fa09mhQnsGqT1dHTL/fwc218w6KglNR0tm2u8D2GKLLbbYYosttthiiy3/DXGhBX/d/H9Wap+UW+TBQVv7fykN0eTKcSv97b8paAPNS7Bs/C3IPY6SetxRmSPTRmZOKsrNlf77JdiYm2I=
*/