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