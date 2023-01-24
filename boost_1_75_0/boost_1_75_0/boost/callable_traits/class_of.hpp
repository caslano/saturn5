/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_class_of_HPP
#define BOOST_CLBL_TRTS_class_of_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ class_of_hpp
/*`
[section:ref_class_of class_of]
[heading Header]
``#include <boost/callable_traits/class_of.hpp>``
[heading Definition]
*/

template<typename T>
using class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<detail::shallow_decay<T>>::class_type,
        type_is_not_a_member_pointer>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct class_of_impl {};

    template<typename T>
    struct class_of_impl <T, typename std::is_same<
        class_of_t<T>, detail::dummy>::type>
    {
        using type = class_of_t<T>;
    };
}

//->

template<typename T>
struct class_of : detail::class_of_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is the parent class of the member. In other words, if `T` is expanded to `U C::*`, the aliased type is `C`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`class_of_t<T>`]]
    [[`int foo::*`]                     [`foo`]]
    [[`void(foo::* const &)() const`]           [`foo`]]
]

[heading Example Program]
[import ../example/class_of.cpp]
[class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_class_of_HPP

/* class_of.hpp
1jrFCqe4U1o6mURiFGxGhflqO6z5OlQG11Ms9PpKuuQr2k6+l7ajR4nTnc87aSZMLVRVns1t5IqVckVkuiV0BGghdDprNNd3bIUM4QqJzEBxKa6CZJpFbZDkqspOnazswMGyh2RNB2OMkqBl5SDkF2pJXIYecjKsDEfWdCpVEN9Xa1BGLboL1Rdj6QXvXJ0q/RO8Gmk6DfqMDvL8wBinsIlJWPSzVs25blagP8reAjVnPafqQUEqVZ/njSuv/qLiimt9gRYRC7R80xQKgKyQNfsCzjnfm0ycs0Am9k7In20eRa3C05o49oANYm1AMCqWJmThfX8BSZOx+TJbLqMhEWTri1f71Qpb4KTJnaLRolK85iRZrXKoBqsQNXRLXLYK9pg3shfooMxa22L1qjGvYXD8LEBlMqr0FuIxT6rxUragN0KNQXVhojpSk3Eadj0mZYMHvadD3MqYDsDwz0Skcrm3BRMZT5PLtGecJls5xlKJrW8Dx/WlKSAgNQ6kBtjlp5b278aVKYtY5RDvjgLWmnc1+66Ysawm7nvSsRMvBUgKjJbpFRihZhovMdCoaum1UiNI9ZBw3ghSzmzyzOPIvfcUYERdmuZpJi86Xw7+xyGJk6PuTlgEw3D3jwEPiNvwo4fpKxU55/Um226GpPnXMAUHBZcn9E2LxApHufkF5A4F0oJ3vLnDd98SdyjgeJZ0jPF0FCQKpCSfsut9
*/