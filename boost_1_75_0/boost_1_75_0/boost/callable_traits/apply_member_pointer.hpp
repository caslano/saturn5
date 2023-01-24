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
8+CGizSC6ZcCIwLxSMTcefgOkwtSZn/w/4DGwOgD2j8hYby5DhDbbR68IVhux2MepIPRpA9iz6/VPu9Gz7vB+Tja50E6Gr0dR999byVIXijR2RdcBNnLlPM0LCtT0Q6G37hF64UQkFywTE0RkV4NwOb9qQLMtbFEOxslWgbV5jLAzHKZQZXIDGrhTGJQJTIJHYr9jKJm4WlNf3SSMAA8eJY9nFbPGOY1yESxe53OkAj4aRf4QCmKgAd5f2FtVqLaxqTRSfVIdLDSuXOAgGXSgicYSVWeHv0zEAgKtPZmF5iXp5YRGSKJdykERUlXrgZtltfo81ugrjYQiBAG1UKk3N1dkMQVq2nJGb2oQlfLu2vpUkwXzGIOBzsvpV+yF/SyLgjklYqithYVNTR7nI2Q6xTLdcgNGIFNVvJlMmsS+EXK5K6L2ARrEypJlq8JYi9iW08ph6+6sZcQ6rGRah2mOLAEUULnXoRO9tkxYSWnHjOGYS/pxFnG1jeu1LJ1/BpHkwn1OJ/Uafda9UUcveD9q+IvoK0qbVvcJGTNuajP6KTiEUOgW+73eCCMMUXj8HH3nxAO/PldH1GhieNV/ckIteEqaRQZY2nFGvWYgnGsZ5mAC0a4x/6AvmeVxMeyz5tyc9ohnefJ2u/6gwCUrY51DJbfSFzFnaoZa6pmrCr9Y8VB4GDiRp7Jj7jR9GmxWWvhCIbWqDV9xRZNgQ32
*/