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
PjwL3gzn8f8t2n4fPAeWw/lwKzwXfggXQBdlPB+GwYWwE1wEu8ClMAleAvvAxbA/vBBmaPsp2q6/sa2fg+T5iP3X39j2W1M2HraECbpeofMGwbYwDbY389PPIzAjQH7RxIuETeAQGAeHwWbwGNgUjtHbu2EhulTnd7LOry7M0fldRjwnvAKGwuWwPrxSl/cq2A2uhN3hdfq4XQ8HwBVwMLwRjtPx9Npf+l5DHdC/6732V19dL/rDLnAA7A0Hwv4wFQ6Hg+AEmAaz4VGwnLxWd3Cop9CdaFxHh0pH56Hr0B3oBMK7M0aYgZagm9Bt6B40gnHDlmh3dCiaj85DL0PL0I1oOboHdXVxqER0LFqKLkRXow+gm9Ad6F604eHEQ8eiOWgJWoZuQrehFWhckkN1QvuiJ6P56Dx0JboRfQ11rWKfYAUa3pU80bFoDjoXXYKuQZ9CX0M/QvegrmTKgCagfdEMtAQ9F12BlqFPoa+hqhtx0QS0LzoBnYsuQdegG9FydAe6Bw1lbDUG7YuOQPPRpegGdBv6GboXjeiBX9EkdAA6AS1E56FL0V2Mx4YX1VGJ6Ah0CroQXVlkj9PaYosttthiiy222GKLLbbYYov6u8f/M3OLPBMA/tz4f3PW9+vtHqdCnco9TMU4QeakWQXZJcVkLfY+2K68z9teRNFmFBBB5g9caH47QPqURAah9dB+aO9G9HF65g+kjRmTmT8jKydT50RZis25AE+Qw5OiNb9jWjlmEWoc+JiCRR+4ZV/3DOmrPyckcfeua87JO3vD/M3JbZt9adXHbtU3bjU2cfDGFHRfpfa1HAOqhW9fZbzu+2wLm8F2sCNMhEfAjrAf7ASXwCnF9Aeh3v1229Chfv1xY3WfW6L0sREH9e5Hy9F9ZHtQ7/4w3ddl9nHF6P4s/36s1cV2f5Qttthiiy222GKLLbbY8s8SFzr1L2z/F/B/ZukR3boWuhv/f67t7267n++1jn+4nru7w0EucCvs1pztHzxz6EdlZvDDmTm5RXyHLrOwKG96rnsSr8zvbEICg5ktUXrO4g+SZrOjI//qeZI6n2i2zfhdzXmqpv1wyWMU2/V/dG/vwJms2yhhhrr0J3dYR+88zPWBRpAmXNJMNxrodQzTzXw7sU0cM48OkkcnySOj0Fx/yYzfXvI8ju0wyfNe1vt1eaeh8L7fGSSd+e3ApWx7x032ipvkF/dKtuuYcXP1vjKHea87zkozXYpfuhX6Nx6Nk7WkSjgU5hzUw6XM5zsq0w7wS7tap41sJmknVu7/WOLeIWm/MirTDvVLW6bTlkBzrirdMknwN4n3hEPXCaTEXLeqSPLt5TjMtBVOx4fmeszni72Dt70rjtPHjXln4o9Yo+pxTJU5rWdJ+oH8tlk2c12aARL3aNXQM4+aMJ2eXqo59D81I86aaOaWoecF0EWNPbqWv8tRbw5A+6IJjT08Fp4AO8AX4Dp0OWraNM+Krvl78IepoMgr3eUke3r82PZ8yx3/uNeu0d9xN7dxp/6O+/6w5MqwhbCThFHfddhSr7CuOuxKrzASy2+uMMNyJc5qtql3bFPvdLoyiCMJk/rk865InJ4fX4cdiYYVaC+uLfN+9rm2sDR4blFWSW5mRuFMfY77np9cR3Sa1ipK19ebZPtjVlZzeqeZaV5bzDQtzOvEDbL9hXqRf3Vd5q+CiXklxeY6YtdKnJ2qXF9/ppj5xPmfd+Y16yqxf6a2qDB9PalM00R5nRNmnf9ebFl6mxL84t4OV/vrcJ5em5t5nRI3W2/vj9uW+huKfadX/d2p6+WmCKlnaM3zxd11jTwr65r5zkMTvzozdH8YPja/ZarXWtI+JCzDr454r9c=
*/