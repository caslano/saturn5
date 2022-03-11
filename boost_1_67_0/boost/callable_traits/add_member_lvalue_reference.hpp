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