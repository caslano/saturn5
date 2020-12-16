/*
@file is_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_transaction_safe_hpp
/*`[section:ref_is_transaction_safe is_transaction_safe]
[heading Header]
``#include <boost/callable_traits/is_transaction_safe.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_transaction_safe;

//<-
template<typename T>
struct is_transaction_safe : detail::traits<
    detail::shallow_decay<T>>::is_transaction_safe {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_transaction_safe;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_transaction_safe_v {
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
constexpr bool is_transaction_safe_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_transaction_safe::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none
*
[heading Behavior]
* `is_transaction_safe<T>::value` is `true` when either: 
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `transaction_safe` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `transaction_safe` specifier
* On compilers that support variable templates, `is_transaction_safe_v<T>` is equivalent to `is_transaction_safe<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_transaction_safe_v<T>`]]
    [[`int() const transaction_safe`]   [`true`]]
    [[`int(*)() transaction_safe`]      [`true`]]
    [[`int(&)() transaction_safe`]      [`true`]]
    [[`int(foo::* const)() transaction_safe`] [`true`]]
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
[import ../example/is_transaction_safe.cpp]
[is_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP

/* is_transaction_safe.hpp
PppO3xzmmvvyJ9gC7VSDa25dvBF3Eb4h/myd1zYfsn20oKj6NWf1Z2+I3Gmi5zrezmmB/GlB/STtY9OGsqabqP1Dax0mTsJ2/BYZV5vUlvRM0YuJXtjmaaBt5J+bxnl//nnpuwQjronO/YnQ10alhwNtVL5g1o/M/ReK3HemD2Xm4C+x7SRlRJr7SQue+8+XcKyTwdnNlZGYFnaueUvkku13H/t9KX1h5/W7JL2ZSZZ0WlXSp5mjkFE7nXau34o/9BPG3I+15yH5FlEk+3SR7OtFsk8XyQ7dL/8u2c9lh26X6B8fO/b5p363sfOkjZtGJ2ze9WTvSHrGSPb4Itmni6QnjaTf/On60/B2D3+6Xbyfaicxkt3DA6JP03smvVerpXuqNhm/m612vObBdFgEW8JzYSdYDHvBEjhA44dreAIsgyfDcpgHK2AZXACXwIVwmea7AlbC1XAxvBWeAZ+GS+Ar8Hdwj9qD+xQug99p/gNwtwncn8i5iE81tLHxu2PVvtpgPa/hel4jYQacCTvAUbArHA27aXw/eDzEm/FwLpwASzW9Ek6EK+EkPZ+T4O3wZLgBToZb4SnwXTgVvg+nwY/hdPgFnAG/hjnQOJSv57fZ6G8zfE7PsTHcaPyuPnLJMBE2gl49zxTYDA6ArWA67A6bw8GwBRwGW8JxKncibAVPha1hMTwGnq7pi2AneA7sAVdq+BoN3w57widhf7hV8x2Q/tPfNXiRnkc9GR841Qc3hI/C5nATbA0fg+3hdtgFPqv98gQcAzfruHsS5mp6EdwCz9B8Z7v0xvuN/m7AJjJeoOh7/W65tt+lOj4uhx3hH2BfeAUcCK+Eo+FVcCy8X8f9KjgdXqvteJ3W53pYrnJnwZvhZXA1vApugH/U9HXwDvggvA1uhmvgFrgWvgjXwffgnfAwvA/6zmU9rAM3wER4P9wOsZ93RBt7qjP+zdnY+3+1r7cJnfpu/CF84oLaptOCqI496qIu6qIu6qIu6qIu6qIu6qIu6qLut+5+Ff1/eVnpz/Htvwxs+7VlgTGRxSePoVy+1LagNKdbZveeOQtzixbkGyMy3yCzMkSmV4/eQTLtkcn+Mkime2bPvkEy3/pkvgqS6ZHZp3uQzD+R2fF1kEzPzH7Bx/rOJ/NtkEzvbj2D6/wvn8y/gmT6dusXfKzvfTKOIzKBN01LynK69fNLWZnd1WV6qYiV2VNdJnAw2WexLMWIbuhrJ5JuIpLOJZJuJZLu43/vG0759Xzx79z3xZANV91229SPd5w87cZ9eyPpdCLpPiLpjCLp2iLp1H66LiyCDi6CLiyyDi7WU7WGO4p1wDz8UvwN+IfxO/H78XUXsk6IPx5fhF+J34jfjf8O32JRbTMMX4BfgV+P/7E14dTtsbIuPBAG1oa3h6wJT9ke+4uvCy/ZHmvXhVfz/6aZ5INv4d3rw18TLoJNn42ttk7cibhwa8WyThxpjfg/WB9e4loXns4xI6wN23XhCmTs2nDIunDomnDURV3URV3URV3URV3U/f+4X+f5//Syip9p///vXPv/V8YbcYsT2P8Op8Gpvr3Mf3ftZZaDu23NFBa7bHOpbGfj1f2cn0q4S8JlJj5+f3yi7nV1zNuf+fdjJpouYiNoqdH90SF7b7+T/M0T3jDr4t4lv93rLPEDVc4xM6S8baYNZa6kzKqySq09vW8kT9cEsVNjy+gX1gbSRJve29p8+lLCgxL03INsGU0ifb+kj0wIZ3/usY98aSZmirnKk6b743tI3AOx9dhBVmFuiRkYWxxqI0zacMmHyNF+YdrOJT/EtlnKP8TeYdw/zYUx58dOtm10nOR71wwm7xryetVm38lS/nvxneI=
*/