/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP
#define BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_member_qualifiers_hpp
/*`[section:ref_has_member_qualifiers has_member_qualifiers]
[heading Header]
``#include <boost/callable_traits/has_member_qualifiers.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct has_member_qualifiers;

//<-
template<typename T>
struct has_member_qualifiers : detail::traits<
    detail::shallow_decay<T>>::has_member_qualifiers {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::has_member_qualifiers;
};

// older compilers don't support variable templates
#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_member_qualifiers_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool has_member_qualifiers_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::has_member_qualifiers::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_member_qualifiers<T>` and is aliased by `typename has_member_qualifiers<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function with member qualifiers
  * `T` is a member function pointer with member qualifiers
  * `T` is a function object with a member-qualified `operator()`
* On compilers that support variable templates, `has_member_qualifiers_v<T>` is equivalent to `has_member_qualifiers<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_member_qualifiers_v<T>`]]
    [[`void() const`]                   [`true`]]
    [[`void() const transaction_safe`]  [`true`]]
    [[`void() volatile &&`]             [`true`]]
    [[`int(foo::*)() &`]                [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`void(foo::*&)() const`]          [`true`]]
    [[`void(foo::* const)() const`]     [`true`]]
    [[`void()`]                         [`false`]]
    [[`void() transaction_safe`]        [`false`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/has_member_qualifiers.cpp]
[has_member_qualifiers]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

/* has_member_qualifiers.hpp
kDiuoz5UGjcpSKm4KXYN55SpA+wuIeHqvQd9bnAhaVW7STa7jroGcKra+cLrrHYV4u8xxl++JrrFLv/5S9eI/dOSvlKXf/xkq9j9XexKtJ+5ymZXjt0QX1tXO184KTomc5vYDXKxy5Qpv1HIr2xxSla7W0Q3z0X6je445EPRjRXdMpff7kbRvdHVw6oS3TUu/5q968W+t5aFvxL9RconW/PJJeXfIHrttb/jCxxjd4PYpfh6bGN3rtgl+3ottdO6S3xcxEftKEmJC3YTjd0A6Z/H1Fwt4V4gaTnHlSR2LpfPbp/o3R9zLfb+vnwKttrG6AXEDj/dzeymuOKb2V3tSrDZ6fdY4XuGST24TPLlTek/60/Rf9Zp/5mk/Sf9Dmbtd4J9qPaD2ndgl276u1oz1pxjOY3hOo+9umVvqvEffO6+hoEvuzMvTXimflfsAecxYt1jSX8P5RmB8gzdY2kOKufDbHgFLIB1cBX8DCyGt8E18BuwBL6k5s4uv3k69Jlz1LwRroc3wQ3mvDItD9O3h54PNkjXfI6Ee+AYeC8cC5+E4+BcHI+HW+EE+AU4EY6P8e85tRNmwGfU/Jaa3bF+cw84Q9dCPjrFzZilf3yx3RgP43H+8awGxqeORMeoolf0il7R63/6+rj3/8+tql7BDDYvSb43/3/9vf9gsmX2jq3Q96S1Sf5nwUxY0RO/Z/nf+6csWpxdVVidTeDyPlPWU9+x9f2oAnaYLXuZJun7kbpdbd7Z/5gt36eZ96Wxor9Mv2kNfcfn2Vvdl8p9d9h34VnG/8Xmfamf+Dc15P0oSd9BfFf6Innf8LazNnuTbO8yi8T+De8kq0jsi/V7l59c7LPvFbfOGmX02yHPiP0Rb3/rKq++V4n9VPHnce8wq8rYx/uey0X/KW9X6wt+/9V+lOg/6e1u7fTKu5K+56SuxB4fA2F2Rn4kug97Z1uz1Q+//UXzfPZ/9E63Crw9JUx9ZxH7KxO2WB+4j3p+5p4U94Jb/ZPn8jFy/+K466xu6p/f/n4J5zVvN6vexCkN+xs1TvIsrnYbJL9rzPtTP+QHopfmj7vaHZSwXvWeb93i1fcisR+2WN5Dje5AJFnsOsXdYZ0jup3VftdsyVuX5qvYPSL+vkQ53Gbyewj2HcWPo5TDBrG/Qu33i/53vSnUAdHX59cR8/3lyWyiX1/tV0mYt3d+y7q/U0+N4yjkMtGfntDbGu857Hne/ZA31aPpkvvXi7tr9f3G3556S93v4JL3ILW7T+K5O0bfccVurbj9jiVlonZTJTxv3CBrvTeQ1xORb4puiSV+ql03CaerS9MhdqPF/SPeVGuHuC9T+5cl/BtdvveZOn2fqYGWz09tg1vn+nTe9c60Vnl76jvO+5KPpfGbeLd+yvWA+6M2D8d2jNtq9lT+nPi7xErVfZFvEv3e515u/SJmS+zgtu97fxMzlXu++CWJ/0M7LWeH0OdcI61VMa/FfNvzdde9bUdY3dvdENMpLtG1IX6kFXvOGzGXJsxzHeVL1PmJY6zGxCEW8ZG6WDNHzlBImGX93f0lT1xMbLv9uHvVTXwkrT+WfPqKpG+ljIetkTEv9pq09RUb8S84bjJG/DzeIdaa6JnqWeW5zzvVw33TZ1wg9z/sMNBK8SzwLPMc8fbkfrAvGCT3VyVMtmI9z3h+437D2577wbafKvfLE263nnY/7XnWPSbuMTf3zfjHAyb8Ofif73nYO0bD12/L5H6/hBlWO0+dZ5TnPe9f3fb2f7fc35Rwg/Wo+yXPy+6pcfdxP9jOH5L7eQm11oPuJ7g/kPsavrTtWf5y75BgjfXM8+R5Gr2DTPj9kMlyv3PCJMvrqfBkeF72duA=
*/