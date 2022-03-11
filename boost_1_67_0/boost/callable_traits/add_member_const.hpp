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