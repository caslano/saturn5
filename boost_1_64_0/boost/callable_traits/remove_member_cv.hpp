/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CV_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_CV_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_cv_hpp
/*`
[section:ref_remove_member_cv remove_member_cv]
[heading Header]
``#include <boost/callable_traits/remove_member_cv.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_cv_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_cv,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_cv_impl {};

    template<typename T>
    struct remove_member_cv_impl <T, typename std::is_same<
        remove_member_cv_t<T>, detail::dummy>::type>
    {
        using type = remove_member_cv_t<T>;
    };
}

//->

template<typename T>
struct remove_member_cv : detail::remove_member_cv_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes member `const` and/or `volatile` qualifiers from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_cv_t<T>`]]
    [[`int() const volatile`]           [`int()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)()`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() &`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_cv.cpp]
[remove_member_cv]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CV_HPP

/* remove_member_cv.hpp
Kl3oBCb7JBBz0xZjpIbRYEjLchdTKwxdLBTpwyWz3j4yH32YIMRP43NqjAHlWQDlGL8ceRhcal4xKJZwWFXYKcawikbmNdmor12rZfuTKu6TK5C8D11xpCeui6qmgcekmrsofCL1ZeAR0KffMkKkEiwqAIww8Qi2A4bPZMav0YYlmhTGkzLxh4sqljklK4tsXhHb1g2P3hvTa1NW+lZ3Y0h8b9R6ulDR7L3dzp45TV/lQaoIIvisqavjWmLwD5Qrr3J7yHNbEAtBDKItiScH6MZ+syyVNyqsGds8kd81BT74WRNmw4JhY3KlHmiZVZYYihSpYzh6qwBr6iI46X1Wchxiz3Midx9oa9B2iFudTfGQD5xqNpCVZ63EqeE7/N32IiF+RXDiwhjU7lhdUcNCHjbA9VPqo7Jjdwl5VJrQxMzpNKhJurJbPHbY1y0VRRdtixOl3CKk566IoCo9Szt35lNgNd/+zS1sXCGRCtiU/mqA8zHhv3eiwpfAcpkbGO/oc5rKQGADkh5CUlBuitNoL9ziuwuWOXtn7536d9+BT2RyljnRutVSvz320A==
*/