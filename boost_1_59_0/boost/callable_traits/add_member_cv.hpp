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
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
*/