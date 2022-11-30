/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_APPLY_MEMBER_POINTER_HPP
#define BOOST_CLBL_TRTS_APPLY_MEMBER_POINTER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(apply_member_pointer)
BOOST_CLBL_TRTS_SFINAE_MSG(apply_member_pointer, members_cannot_have_a_type_of_void)
BOOST_CLBL_TRTS_SFINAE_MSG(apply_member_pointer, second_template_argument_must_be_a_class_or_struct)

namespace detail {

    template<typename T, typename C, bool = std::is_class<C>::value>
    struct make_member_pointer;

    template<typename T, typename C>
    struct make_member_pointer<T, C, true> {
        using type = typename std::remove_reference<T>::type C::*;
    };

    template<typename C>
    struct make_member_pointer<void, C, true> {
        using type = invalid_type;
    };

    template<typename T, typename C>
    struct make_member_pointer<T, C, false> {
        using type = error_type<T>;
    };

    template<typename T, typename C>
    using make_member_pointer_t = typename make_member_pointer<T, C>::type;
}

//[ apply_member_pointer_hpp
/*`
[section:ref_apply_member_pointer apply_member_pointer]
[heading Header]
``#include <boost/callable_traits/apply_member_pointer.hpp>``
[heading Definition]
*/

template<typename T, typename C>
using apply_member_pointer_t = //see below
//<-
    detail::sfinae_try<
        detail::fallback_if_invalid<
            typename detail::traits<T>::template apply_member_pointer<C>,
            typename detail::make_member_pointer<T, C>::type>,

        detail::fail_when_same<void, T, members_cannot_have_a_type_of_void>,

        detail::fail_if<!std::is_class<C>::value,
            second_template_argument_must_be_a_class_or_struct> >;

namespace detail {

    template<typename T, typename C, typename = std::false_type>
    struct apply_member_pointer_impl {};

    template<typename T, typename C>
    struct apply_member_pointer_impl <T, C, typename std::is_same<
        apply_member_pointer_t<T, C>, detail::dummy>::type>
    {
        using type = apply_member_pointer_t<T, C>;
    };
}

//->

template<typename T, typename C>
struct apply_member_pointer : detail::apply_member_pointer_impl<T, C> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` may be any type except `void`
* `C` must be a user-defined type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* When `T` is a function, function pointer (unqualified), or function reference, then the aliased type is a member function pointer of `C` with the same parameters and return type.
* When `T` is a member function pointer (unqualified)  of any type, the aliased type is a member function pointer of `C` with the same parameters and return type.
* Otherwise, the aliased type is a member data pointer equivalent to `std::remove_reference_t<T> C::*`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`apply_member_pointer_t<T, foo>`]]
    [[`int()`]                          [`int(foo::*)()`]]
    [[`int (&)()`]                      [`int(foo::*)()`]]
    [[`int (*)()`]                      [`int(foo::*)()`]]
    [[`int(bar::*)()`]                  [`int(foo::*)()`]]
    [[`int(bar::*)() &`]                [`int(foo::*)() &`]]
    [[`int(bar::*)() &&`]               [`int(foo::*)() &&`]]
    [[`int(bar::*)() const`]            [`int(foo::*)() const`]]
    [[`int(bar::*)() transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int bar::*`]                     [`int foo::*`]]
    [[`int`]                            [`int foo::*`]]
    [[`int &`]                          [`int foo::*`]]
    [[`const int &`]                    [`const int foo::*`]]
    [[`int (*const)()`]                 [`int (*const foo::*)()`]]
    [[`void`]                           [(substitution failure)]]
]

[heading Example Program]
[import ../example/apply_member_pointer.cpp]
[apply_member_pointer]
[endsect]
*/
//]
#endif

/* apply_member_pointer.hpp
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
*/