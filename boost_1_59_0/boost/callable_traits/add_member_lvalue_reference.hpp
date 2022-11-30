/*

@Copyright Barrett Adair 2015-2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_LVALUE_REFERENCE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_LVALUE_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_lvalue_reference_hpp
/*`
[section:ref_add_member_lvalue_reference add_member_lvalue_reference]
[heading Header]
``#include <boost/callable_traits/add_member_lvalue_reference.hpp>``
[heading Definition]
*/
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_lvalue_reference_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Reference member qualifiers are not supported by this configuration.");
};

#else
//->
template<typename T>
using add_member_lvalue_reference_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_lvalue_reference,

        detail::fail_when_same<typename detail::traits<T>::add_member_lvalue_reference,
            detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_lvalue_reference,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_lvalue_reference,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_lvalue_reference_impl {};

    template<typename T>
    struct add_member_lvalue_reference_impl <T, typename std::is_same<
        add_member_lvalue_reference_t<T>, detail::dummy>::type>
    {
        using type = add_member_lvalue_reference_t<T>;
    };
}
//->

template<typename T>
struct add_member_lvalue_reference
  : detail::add_member_lvalue_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member lvalue reference qualifier (`&`) to `T`, if not already present.
* If an rvalue reference qualifier is present, the lvalue reference qualifier replaces it (in accordance with reference collapsing rules).

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_lvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() & transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_lvalue_reference.cpp]
[add_member_lvalue_reference]
[endsect]
*/
//]

#endif


/* add_member_lvalue_reference.hpp
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
*/