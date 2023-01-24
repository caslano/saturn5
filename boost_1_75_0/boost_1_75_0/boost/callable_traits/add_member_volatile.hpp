/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_volatile_hpp
/*`
[section:ref_add_member_volatile add_member_volatile]
[heading Header]
``#include <boost/callable_traits/add_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_volatile_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_volatile,

        detail::fail_when_same<typename detail::traits<T>::add_member_volatile,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_volatile,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_volatile_impl {};

    template<typename T>
    struct add_member_volatile_impl <T, typename std::is_same<
        add_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = add_member_volatile_t<T>;
    };
}
//->

template<typename T>
struct add_member_volatile : detail::add_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member volatile qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_volatile_t<T>`]]
    [[`int()`]                          [`int() volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_volatile.cpp]
[add_member_volatile]
[endsect][/section:ref_add_member_volatile]
*/
//]

#endif

/* add_member_volatile.hpp
vm8EAfmMDQ6EZwOaAIKpjQqEjIBmgNAQrgVCWejfAEKaFghcf3CbDV8E80RcD1aqcEjzhUM0h8PNoQSHaIBDJVnJ3tpKfYJRSb9XBvof4tWh6hBf0TczxK5eQ/ypdYuHqDFYKKNcSaM07adRxkquCnmUsu3Ce6CxfKBJrWmgsTDQM7pGE35da68Jl+mo0u/+7H2BnLgaNc0NWHIE+i8Mglhfy5bOCMYRMhOh6WJq2pTb9YLHo6xtUi2NF8Ck7l6LtEFvR6WS6NtiMgMzkvTNY6QGVpMa2HiPq7hb6l1K5PbhskCdlO4674H8z6XIYWfAozvpUQOTxKUk+n16J1X5hV+/36nQtyTwuL2petzilsgetzE80UHO9Bt05HK7wc5mlvTyXNWuYGOUwzZAcDt7esyGViARkn0q6Sr27LDUYwfateHtUSNsbZs+VIdp1TFN4lDe3tWa9kLQ3ed2hnjM642UWoyXDuHSXw89ppQLCcu4nn3HBO7H/ngg6HT8GOV6ly68ptMpLroh/JxKPPBygCncFmLqYzvG0MzZmaEYnCIk8pnBMxBE6Bnawd5C3IPORPLODOXIVR+iHQ7f33VY4TLOG2j72AjWYE+NWSX3O6ZdsIl3EFA+D6FWb5BbuEFtYQzgxK4s8mMiTSc/JuZHe5hPpnkHXe/l94YdxMQm7uT747zPWnonqg4MhguOh5MPaOQzfMLzdKiu1jtc
*/