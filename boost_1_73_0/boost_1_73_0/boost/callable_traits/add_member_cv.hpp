/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_cv_hpp
/*`
[section:ref_add_member_cv add_member_cv]
[heading Header]
``#include <boost/callable_traits/add_member_cv.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_cv_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_cv,

        detail::fail_when_same<typename detail::traits<T>::add_member_cv,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_cv,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_cv,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_cv_impl {};

    template<typename T>
    struct add_member_cv_impl <T, typename std::is_same<
        add_member_cv_t<T>, detail::dummy>::type>
    {
        using type = add_member_cv_t<T>;
    };
}

//->

template<typename T>
struct add_member_cv : detail::add_member_cv_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds member `const` and `volatile` qualifiers to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_cv_t<T>`]]
    [[`int()`]                          [`int() const volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_cv.cpp]
[add_member_cv]
[endsect]
*/
//]

#endif

/* add_member_cv.hpp
dr1QObrnkJ4Cc81Hsemm30q7AVrm6t+3/clm9mWY5KH7zQoDl/xQijhLwBt17dctG2hiuvCboANPO8cgOrlayC6X6FPFFyIsy2JAIqUb1aWm74aHG5jfdRxTgWreswh7WdPzWPrFAowLHMS639PgvT/n8AutA16Wgt3/KmVSny+1EDSmRR5H/lobal4cKuJgdbZYUpMnJq+pmN905YoiFWdWmlIXW803UTmoclrESnhG6Cxf45XNVh4bJzzQ+at41cCuJGBwpTKU8UfzuaheCfNtRtoEcFvwi4np/wFQSwMECgAAAAgALWdKUnRpK/+QBAAAOAoAACUACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3NtdHAtZXhwbi5jVVQFAAG2SCRgrVZ/T+NGEP0/n2KaqmocmYSjldrjl4oCtNFBkiOJrkhI1sYe4+3Zu77ddQIq9907s7ZJaK+iqs5AbG923pt5M7PDsP/1rg704dUr8n8RXXT3FjOj/8DYfXl3FD1B/UNWd3R/jWQIW5OnKIDXTZ6g502ihuWYn6PoNaI79o0/hmx5F/EjrZAZW450+WjkfeagNwrgzdu3P8MeHOwf7IdwLpTEHOYO1QrNfQjHiV/5JRMPDwOLpyGgA5EPGqhFJi1YnbqN
*/