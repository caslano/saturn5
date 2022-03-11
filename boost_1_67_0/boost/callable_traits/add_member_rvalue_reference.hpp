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
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
*/