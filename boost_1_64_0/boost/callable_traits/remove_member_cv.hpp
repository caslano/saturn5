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
y0vV+jSHmbCJlttUy0uHYyU9UK7eT8NpYcrtrPsRusBWsCfsAjNhP9gNDoM9YLamH4D2/lTviymXNqNc6HMn6f6GUzT/VHg8nAZz4HSYB3NgCZwJK+BseDbMg7fCuXADLICbYCHcBk+DO+E8+CacD/fAYvgRXAQPwUr4DVwMv4e/030iZ8FUuJR/GfBCOABeDCfDS2ApvBxeAq+At8JVcDO8Fr4Ib4R/gzfD/Zr+A7wVNvRwzcBW8E7YEa6BXeBaOBZeB+fB67VdK+29AL8J2l91YZHxu776/tcgeBw8Fp4Is+AUOFTbcxg8HQ6HS+Fo+Hs4Bp4Hj4c3wvHwdjjRPQ7l94NzDjNeNurxH9Zx9wgcBTfBk+ETsBQ+DSvhNrjzf3EfyRm1o3tJarCXpO6Z2K3HH48vwq/A34V/4czovpKoi7qoi7qoi7qoi7qoi7qo+/9zv47+P7c472fS/8916f9ZkxDXDl8P3wp/us9IzPOBdfJZxRX55RVyfNJcekrCVo+p8umu9e5ZhRXl/nTENb2JK72ipFTzF9j8qSa5Kn9JRUXJfKMyhVamsanNujVBU5hy5PffRYdr16Wps8aNsmvRUk+Jy7Zx/rp5iZti47Q+Ifqq7HgjbrzHoInHw72032bbfvpxwPycvPJcDN0Vz843Qe1YsqDCtmMgX2+rc/hSwvU99a3OgY6Ymy/pY638SKvjSnjBF45xyZeWFS5U3bmVH2b1FLEi/5CGeUP8RV/499IPsYmi48gvL8/liKrPsmUMsTb2HCkjwePV92JtnhxZ57fHelTknnXrtSjLpUP2mFD9h7Ul9r3IJXqS1R7ZQQk/5hxtLnMC5WWGlHeBlrfA4BhveSWE9T3uof52st8NOEXOu7nxnYM30eCKF8zPmZczazGjX88hBXaUfO86kfQuqZJ+0PGV81KqpHPhlMzXgvzn6bjrlVdSnG+sLYoxUo/uXIexIptpSLNl5RXO5VrkP5K22fGntZAxGFzX8aT1krrslrq814wEGQsMRZUU25Ral3cknXlIy86Cx3Kd1YfbaY8c/HT8yGSOREMUhfj5+C2Jfv1RLkxI1j0YHhPOWTuUxlNlh/KpF0N0zp7AdSvXiMQVeAI6JbkOJK7UxslYl+u2kjjGL3FV4zeNeMYYbSvxQWOUchgvwbookadCtD1xQf1o948skLKkD+W4m618VV9RjrQzfUB8UB/Y+ekdSaP9Q/SYKxPCz8/rXwrML6Xl+QvySo4wPyP/o/Mz6T86P5N+5Pl5/Uv/O/Nzf22/6bWMuObafl61YbI/XPvlyJgKqwsWeXJHmIc1vaE99xI9d/pN3ZHfrU+W/UfB45tzsbZ6rzzKiGur55KhY6HFy3ouchIRx4DKNYs0Bkj/0TFA+pHHQIuX/3fGQO/AGNCl6HRtt8YBOzbudtPOj7AXQGUbR+p/0n+5/u9tGsh5bKprxL3sULbyU9+92stqIzX4PFz95B/jxtjfP80zVsPsInxFbL2EtZ3xsMhe43xrFuv5BvL3VRnHbN4heyOoa1JoG9m9Z3+SPDc5juMvJ9uW001lqsrJMglu+6d238TfRf55tQVj5SnBK+f7mfyOaVO49rDdKfnucuo4izXO5kU/67htlJYsKMZOq/7ePyX5LnH2m9Z8h6CuyXdide+Yzc+RJ1p7zdt0/+EBfOBbOC/hs0KI5/e0ZvuxvHJ9BMa4uy+5RkLGT3bw+JFvwwySehpD20j4BVdY5hcdX30TVTfr4T4GjoF7kNnxio4vbVNvyLiSaDu2AvKt9PtC3KtJuJunF38TncN6z+WY6a+K3Z9q85VX7/G+kHxtPdjlQk98r6NjT8tv6b/HMyZ0PpP8BVY=
*/