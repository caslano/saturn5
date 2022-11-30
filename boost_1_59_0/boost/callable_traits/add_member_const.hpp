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
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
*/