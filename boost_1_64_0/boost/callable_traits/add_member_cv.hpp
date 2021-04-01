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
/AxrQG02UI2V1/a0XDtfK7XsY8Kg9hZybiKZy0NF8hrhv8+tLiUnE9qyv69omL+69sTna6z5zjuMnOmREX0YWJ8emFfnoIa+24mNM65ZIC98Sr5q7KySNXRo2Gud5iels/O+2nUTVAj/67WlbkQqzaVqW6BzSv1pWn+2P7sE0W3Jw6Nof1YJuHomzm64OhTkSRnFMUn0ZFHn4Aq467+ckZSrRlnfnh2OzebEbXc9YtpCnY8DbA0zCP2ubDaKNz8P9XUnnsGwaiOl+ZFEzUoBrNaVGwOQw17fA9TEzdCMEeUf5vsSJH2xR359GlyZe2oEyZAuDpUGw28x/h2oA8rcD0LzK20q2QzKsHZxCjQikt7zE/TC/h2xR0F8wHJ4DFAQhyfeQGeSLLa7FLfu/2PDwmBeU7KYjjzYjmnvO1vexnWdzqY1+ua++8HgW3ahawH38aWjQVqO5k5J7Yo4dHFWY2uBpR6j8BJAu5HnX0RIJq/tnFyJGua5T1PbpxkPCxzX3LIBeyzL3EmoYuUmBC9Ri4chd3T7YlRUVzPCTfklNd+QJb+bb21/Oc9xgA==
*/