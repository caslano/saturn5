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
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
*/