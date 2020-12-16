/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_cv_hpp
/*`
[section:ref_add_member_cv add_member_cv]
[heading Header]
``#include <boost/callable_traits/add_member_cv.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_cv_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_cv,

        detail::fail_when_same<typename detail::traits<T>::add_member_cv,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_cv,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_cv,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_cv_impl {};

    template<typename T>
    struct add_member_cv_impl <T, typename std::is_same<
        add_member_cv_t<T>, detail::dummy>::type>
    {
        using type = add_member_cv_t<T>;
    };
}

//->

template<typename T>
struct add_member_cv : detail::add_member_cv_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds member `const` and `volatile` qualifiers to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_cv_t<T>`]]
    [[`int()`]                          [`int() const volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_cv.cpp]
[add_member_cv]
[endsect]
*/
//]

#endif

/* add_member_cv.hpp
2xJTe75cV402NVR95lock2v5pfUW/SSUr2nNxb2Mvmu9c1q1yRJT+A5pVf3+pDVWZJqlyH1/se9ZojJcua3WsQOe81iX0zpmZGhPGgS1fdpGGZnGupfPE566RkR9bUt/kTmrxtoH0sMxTY+2DwdETuOv7YOtHZF8H6/53lZt1Gdovg/CvYr++srzvUQWEskTw7murbfnv2nbeRSipvmvMhmS/wnIvCLnyS8pWST9Ky0Dn5yWgZ6rpKBQZSb4ZCosg5dEJsqvXq89wXrtaX8lXWb96Csip+kIaquJd0BfKq+e52LjcPW0TH7HOY44lUWJVQxc0zn/VXecyf/UaM1/U/+NjMn/Ni6VoaEy+W+TI/+D21Jtv8+8Uez71Fj9Jr6efPWty9V2VOMXkIdj1d7HKM3DYbg3OW/mjY55qH0zxzxU3VEmD9+Seic6moc+GfKwxtLOdTgm1/Fbf/mRpjHSA8KQRX+XUxrlIe/Y71S9yOPud3rjlatrojOJUAfYDb6NbPmNdltFaVnF3shRd53srRAv1ets3hc/Ff+r7ruwMeC1BfH4BrFBY1ujyM4pvjWKeo6eZh3tP8Xvjgi8F3Qdusp3F/9k/F+Iv1lEiPvCrHf/XGTqc07aIHOOrkF28Ox9UmRMf5JHdXDfRmXTAmSXqGy61EHp7hnZPgGyZdrXrSey0t2bTE0YlWuzv3LbTZb8PnOO9IBzrNa14wn+5zDyGQHy6/EHvcur/ZSmcq0j7uC2Q9f+Snjoso2Q8yFssyHwtVz3jIhkzTuut6Qoy1c+ydombZTzdKCu1nKdgUvQbwkz5Xor3LWYgW/ZVsFontxzN4ltla51Y+p2jo6KjGchfFQt7z19TO1KeeW/RX6DJZ+4bEd0XGTbuouja8fWqi0yCSqTmkAcLJnYZWd4zzNd7Un0wh+Lv7vaBmujPFOJrT6xMdGc/2dC5LBFUbXvF+Sf7/uF2p14f4O/3YlM+7tv0B4j3EumnxvcFucFt8Xa1w22A7gkoP/LMamf1GOOeeox7ydS3+rJMVt91euthwn+YX7tz/O6Lj1dbVa2g+9b7eJGf1tppv2RvrJj+4Oe/54yb4j/bPW7Xbs3yZ5Ltj60nNlnK80mP96KC34g9X9RwB4zeSpvt1v5e/Enu4PuJ41PLbn+g4HxCXm/jEL+Aznfv8wzzKX9YGODQPRXql/Px2pHq67n0Zh+mei9NzrVrVPBvZGg8ilJ3npf9nZgve+M/wxbvf8pvBl3C+7WlOrX9bs2Bdf1/XqMQxV+56HsbP1ltf0RsMeOqWNqByBb7UtegPuQc6b/1G7TLc3/AVwSXMeStUwmit44Vw/+DsVp3dPzJTh+F71ewhuI7Y4D5PP6ZE/ZRCZER8Sm1ouuExvlsYOk5TJTy6byvAzOJ7uNmemNjH1N+bXHvYNsuSf9s+eWsHPbbNMKh3wuJ0CR57zS56jEZksde3sU0N/LbqzxIU8awRT4iNVn9sSHBAR8p84vyC+VLbcc73vVJWb6jKx/M35WAx5Qu0XMkZO93Fw2e3lJIuN2P8tf3XOKX/FcsTWp93+qyHzO97gYPztrCdo3GSjh5azH7SDP3MZ6D3tqEOfR+36kyD2GZheTv6xiNe+0hcjEi0yE+zlXVHB7oHXoQpGpK3VoJpl3iPrzM7ERNi02sl0FNsVU/hiyd4gdsJwgG2At8EfjLyV8Oe5OXCt9hi2swvd36/69lvg5P6v0+4HWywNNPcofodABPgnLkc2+xdSDUN+s9Ou747do1c9zTXb+Fq0yRdTJ1oH1w7TVN4vMDneg3T+rOdkgYbvccn6pN7P5Tuz43cq059eL3kNubz+zjmsRt52vPd9wq4SL3aw=
*/