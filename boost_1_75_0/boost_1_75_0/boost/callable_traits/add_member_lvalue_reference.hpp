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
uPBfIj8vl2G9edz+YB1PCagcN4GZKrrxkig7mMCCnIgJRPCxDfKjPIvNukv0ChoVAFHmcHoUEkK61pfgQvbArn15X75jMBsswyGy0T5tDpbTptRsZfySgXLZsH7fmfJuR1BeoweQjUZQXom/hyEoe+Dv671B6drkC8pt7xEo6wObBOWPgX5AeSiwEShT4PnOwKZBGbLvkkE5N7A5UN4FYGEiVDBt9LGaPnn3M/bbbM3ZCCcu6DNC2Vv4FaD7C2BHdWTArnmSUQEG5l/vEwpMeZEI5iJPMANnRwTz+/jbiGBeg79BV9WA+ZeNvmCe/C7PxoM2hPkA5hAOZpkkvkMpIAnM8qm1rwTwrI+TFXCGyOAsrghGt8NfgnMygHOyFpxjArzB+YUXOOHMQgUzvfJJeAPrj/YALGDlDFivR1xVa8qLQmA90gBAiUBgPYS/2yCw7sPfOm+czGsErAHvELA+0TcJrDf0foC1TN80sMTySwaWXd8csCApeEuA9Xk7XMaQFxpDghktBRr7KTyuNSQgzovyiQfEIqwUWpgKDGLbQnIOpZHgMy9Wce1xFvHtXiT5h/cSB6ig2wmVeHFW0lMbXCEzRnU5PRjEX6yk4r2peA/+tJNc/ANe3MBfzKbiZyvwcrKCF1vEi31bQdeRVKyCipXJxabxYkUVGtukxj5B7OmDlxT2lOLATXdgmZincCdXOAlJAgpJFSAkCfGx
*/