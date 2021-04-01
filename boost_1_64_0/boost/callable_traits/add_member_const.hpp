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
urNZ2yE3jJdsWJT+Xk87x17bOEm0NRZ2mBZnRfMAOVS0rJk8O+5ipIDX/MdpfPNMHxZ0Wygms7NluRHpdRD0s5i/p3LxmFySaCZEvD/OY1BWWYfodrjcxkPJ6G5CFw+HLmB8mWn2n/Aa1H37XqlF+ZhexFH/M7LjqoQEA42YMBFu7/f/LLlc5A4DJ392AJyVGW/PvB4wQjV1AkDSIeyyaRuVaSkgNQIxRo27ACmHFcYEFppBAL4qpnEPx/ctFm1RHDiwGtJNJrOrfSVn5dOnIHxP89KsoJJWq6Py5mU8y7YEXodCrGxteVzTDA6RuM2pDcNXdE6wUNQdzma5tDpHhKEEgEdZzKEVLexzVsYD+9C3KbGyoR8l9G2kb4vnSidjj9CiqXIgQwZ7KbH+zZwC1elXI9tAlJLm/E912b2Vs0auGqzOrynt5WfzyZUW8SVritTHrkauP9c+IUXFBBYuvU5AJL8873dRBZNwyvSQfB4qRHQda9wu2Fs7cZ2DMac9dTJDk1Q9fOqoI80XYyOYL0dEKKSc5BWzRn3lzQXTPKZJB6rEJhxbuAYcsg==
*/