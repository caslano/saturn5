/*

@Copyright Barrett Adair 2015-2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_RVALUE_REFERENCE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_RVALUE_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_rvalue_reference_hpp
/*`
[section:ref_add_member_rvalue_reference add_member_rvalue_reference]
[heading Header]
``#include <boost/callable_traits/add_member_rvalue_reference.hpp>``
[heading Definition]
*/
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_rvalue_reference_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Reference member qualifiers are not supported by this configuration.");
};

#else
//->
template<typename T>
using add_member_rvalue_reference_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_rvalue_reference,

        detail::fail_when_same<typename detail::traits<T>::add_member_rvalue_reference,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_rvalue_reference,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_rvalue_reference,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_rvalue_reference_impl {};

    template<typename T>
    struct add_member_rvalue_reference_impl <T, typename std::is_same<
        add_member_rvalue_reference_t<T>, detail::dummy>::type>
    {
        using type = add_member_rvalue_reference_t<T>;
    };
}
//->


template<typename T>
struct add_member_rvalue_reference
  : detail::add_member_rvalue_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member rvalue reference qualifier (`&&`) to `T`, if not already present.
* If an lvalue reference qualifier is present, the lvalue reference qualifier remains (in accordance with reference collapsing rules).

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_rvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &&`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &&`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &&`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() && transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_rvalue_reference.cpp]
[add_member_rvalue_reference]
[endsect][/section:ref_add_member_rvalue_reference]
*/
//]

#endif

/* add_member_rvalue_reference.hpp
jYcbjt2X7OP61DEu/aYY4Y589BVZ1/uxyTrn9Mn3XJN1S7yp2Vhr7nzSeAy56k6m0/aGj+ezDYiUrgcwH/qfq+pcJeu8oK5+Xoiqjp7Dtjc1qJ5p0dkLXic8QmmeET2xr5+Gvx5wX9dDdsL6Sj2L0WuWFRSPM9rWGp/8DaIP5J6FVknWm1NmXkfIVO9R0euOaoofi1OpXV3mR53evufSe5XNFPd9MQR9ahbKYD2XP7dUhgdh
*/