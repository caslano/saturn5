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