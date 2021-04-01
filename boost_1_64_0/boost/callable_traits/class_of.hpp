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
pJGC10/JyBhoIf/jFrH2lLE/kbypbpm1vrmXcx1gVuBoKdECPoBAu9a5PC8laYPeX1VvtpQgm4QSUgdAnp0nImSQV2gkjOMyST7LQfxY/L7Z6asR0Oy14UZnEJ6IwkUi3D3EJzT/Cn6B2JrlES2D50iezwJ/5Ii5F/ic6/+0zviyy48N3eA8ctRwvzqrRcnh4vkbgFZXTycPq3LVlg9jzaupl6Fo6vUHv6QoHLRGW3C2llhYiJazjYb5PZ1ncbXxeiFxgIxD9J6XjZBdkabHixcAk4xmesnlpmEc4EELogs62GsmeWdmAr+QWvRrjiko3gmxDX1t5VpAukQXCWpR+6O5Ha6SeAlAg/vbqr0OqqB+FOViFVm29qxRhKcrqIo4RwhhpGoeGEqHldYk92vQyU/U7Nx1+1tyXT1TrwWdQ34X8Bs9ZQ3OaPrG+QVuUryovUhQqJ7nevChRVkLWoFOgNby23MIM1n+QU/Umc9s0JB5IpPSMTBGvP5Rf/sCxZd8DgsX9e4YGDRM0+fLMx5vSlcek2kCmY+atqOhe42HlPWF9sRyiimDUj0+tw==
*/