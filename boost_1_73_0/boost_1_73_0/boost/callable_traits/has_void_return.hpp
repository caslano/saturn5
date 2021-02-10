/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP
#define BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_void_return_hpp
/*`[section:ref_has_void_return has_void_return]
[heading Header]
``#include <boost/callable_traits/has_void_return.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct has_void_return;

//<-
template<typename T>
struct has_void_return
    : std::is_same<typename detail::traits<
        detail::shallow_decay<T>>::return_type, void> {};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_void_return_v {
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
constexpr bool has_void_return_v = //see below
//<-
    std::is_same<typename detail::traits<
        detail::shallow_decay<T>>::return_type, void>::value;

#endif

}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_void_return<T>` and is aliased by `typename has_void_return<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's return type is `void`.
  * `T` is a pointer to a member function whose return type is `void`.
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` function returns `void`.
* On compilers that support variable templates, `has_void_return_v<T>` is equivalent to `has_void_return<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_void_return_v<T>`]]
    [[`void()`]                         [`true`]]
    [[`void(int) const`]                [`true`]]
    [[`void(* const &)()`]              [`true`]]
    [[`void(&)()`]                      [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`int(*)()`]                       [`false`]]
    [[`int(*&)()`]                      [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`void* foo::*`]                   [`false`]]
]

[heading Example Program]
[import ../example/has_void_return.cpp]
[has_void_return]
[endsect]
*/
//]

#endif

/* has_void_return.hpp
6RXKRdzLwfTsCB3V83/wFs+/H4xG/mLw4scfxOBV8FwM5PcvD8WrFy9/lIH/U4e35YGXSTTgwql8l+b3pw3bu3LB0+nIlIfJj0qD2IhsiM0TIc1lnBVr5EViUi98CFENSykQdUUBjKdF6qPhKSnp9mLy8vnhIecKewsZzO+qvmOFEKKTFwo8culsS+QnlIGn+/sCvZKiVLd0VkD1mxdXiDrJxEt96fN0QCAfZN7iN1lK7/dKo2b9+u3l5d7HY86RvMSsLjOdFpwxpdJJgZox0twcVh5bYp1QKvyfdNGObS6ptMw92bUJVuT9ioC/6h9JLONFnx7S0Kd91Gme9fZYzk4F9u1Pr3hEjnZ30/Q0l2PwaGe4LwoBVWFA0O2ybHr9mobADYAFWofWb/1+X6/26IRGvZ42ndAICgwSGjLzj8yMuUKTjfJpdBycNp76TyWct1T8rA8imYAJrMGDeX+sX0MBL1t3te94uc+U9t1uKc+eaTG1pqCvdW2U/9iEzHiwCGP5ICIqHpJ01eVYbASheo2Xmj3ynpe6PctT6QQGRSl1NuMdwxQlEQC0a3R3T2oSmaXe0uQ/eDnFgwsajmSUJvc9zZMzUJtoCUpDMTxumaD1aIzgzVAdyCLobmssV5ITb3M1jVCexkLLsasJ
*/