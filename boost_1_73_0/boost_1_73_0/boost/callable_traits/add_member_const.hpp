/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_const_hpp
/*`
[section:ref_add_member_const add_member_const]
[heading Header]
``#include <boost/callable_traits/add_member_const.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_const_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_const,

        detail::fail_when_same<typename detail::traits<T>::add_member_const,
            detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_const,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_const,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_const_impl {};

    template<typename T>
    struct add_member_const_impl <T, typename std::is_same<
        add_member_const_t<T>, detail::dummy>::type>
    {
        using type = add_member_const_t<T>;
    };
}

//->

template<typename T>
struct add_member_const : detail::add_member_const_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member `const` qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_const_t<T>`]]
    [[`int()`]                          [`int() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_const.cpp]
[add_member_const]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP




/* add_member_const.hpp
GMMC2zp1+upmHjCbnJsAbPEzyzBXvg3XJS4wcDUIsmXeBJ68UmAcaKIstDm2dpmnlCyHyRYLcvbcjuN1CCBFERfX0cF8xRi3Ed0Y6FCPWXquC0FraE8w6tCo9ZcQR+H4aMqz38h2Iuwyp/CFGBZFAId9YLdUlzdBybRKRlXXkL/1EIJeLLCjAhaIOjRkErtSeOnYqFrKdbGRfAHMOofiIGS9odZJB7BxS5Gwg/Zx4TqHXnYOO4eueSMEVioLpOUu7hTXTyot53PK+fQq8lSraS8AzaXN5PLyYFX+xqb8LMTa8AX8Vrxx0zzJgdmaE5g64DcbRlfmKycAmyGwNR2rsTkVSYKENKvHXsnHntaWLsDR2c3Eq5moRfhRPktlweAFYgnDmcDWn2dxnmom+wkOztfO62KLUbMKwTBcylAfYSutjnvtzKv8JcMq4EK7F7rCx9EF4ulNemXPWF2qK00LuuxfXWDAYifxq6EmtwOYPD11jLKRy9vBGTex94CAPC2VpZse/ataSU87entzNexhOO1fbU3EONiidRsomK2FhrdoQD3Kd1l1PKdn3AQyTTXKUBzH1mMN/6gWcqtYWPMEr4B2Dk6EsoEvNL630aI5ekgGR/RPU/C9+k8tTJs6s2yrVR+2qcyL65Y+kFAD
*/