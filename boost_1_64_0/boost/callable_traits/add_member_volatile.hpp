/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_volatile_hpp
/*`
[section:ref_add_member_volatile add_member_volatile]
[heading Header]
``#include <boost/callable_traits/add_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_volatile_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_volatile,

        detail::fail_when_same<typename detail::traits<T>::add_member_volatile,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_volatile,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_volatile_impl {};

    template<typename T>
    struct add_member_volatile_impl <T, typename std::is_same<
        add_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = add_member_volatile_t<T>;
    };
}
//->

template<typename T>
struct add_member_volatile : detail::add_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member volatile qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_volatile_t<T>`]]
    [[`int()`]                          [`int() volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_volatile.cpp]
[add_member_volatile]
[endsect][/section:ref_add_member_volatile]
*/
//]

#endif

/* add_member_volatile.hpp
C4yh5ZfS/iz/iHQZmaLMC+3VAp81vIqiWLJsyTLSLCzJxG731XLiG7dnBv8V+MfuCMi3Fd2nlNXQ7/KJVaVX5Au1QD8T2isnyA1AZs5nAo/uJhuqNgfNgMdqxnHLwoPr4eCSfMCCs+UzfhGx0uvgVm8HrUB0LSKtUE5/He42pQ9ZZz2D51NkjlUgr/JlDb1SkxBNU9IU4iIRIMj78WVDSo76TkXrncHlhaJZijkb6fo+TMkW9Kv7Y6OW8Rhl0J1DDCPZdZpJvMV67FlA2pD2B699N5n7a3u0MnAcvricTNy7oSeZUUm83aCL5eh5cmK1C+C3VmYLs+0L/mWGSsYtZmH+Hc5v6d052rVZesoy4gDSDohZrkEh7ascRnPnsx9js0k1JeWXSMSr+jopT5ziCrxLUUTbYeStZSM80peHaCHabdXD2de0AU0ZmruV53sSq/sFJynG1hE+U5vv/MncNKPRPNlR36Jt9b3/b0gmBTmQhCkp9d4RCrXgNOUaMl4hi3OSqCZdTr2DxV/hu9/uxWl32zR0LQdxJimdp1t/Y+OOap40fXLyaE91vQ==
*/