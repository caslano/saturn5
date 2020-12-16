/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP
#define BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_void_return_hpp
/*`[section:ref_has_void_return has_void_return]
[heading Header]
``#include <boost/callable_traits/has_void_return.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct has_void_return;

//<-
template<typename T>
struct has_void_return
    : std::is_same<typename detail::traits<
        detail::shallow_decay<T>>::return_type, void> {};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_void_return_v {
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
constexpr bool has_void_return_v = //see below
//<-
    std::is_same<typename detail::traits<
        detail::shallow_decay<T>>::return_type, void>::value;

#endif

}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_void_return<T>` and is aliased by `typename has_void_return<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's return type is `void`.
  * `T` is a pointer to a member function whose return type is `void`.
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` function returns `void`.
* On compilers that support variable templates, `has_void_return_v<T>` is equivalent to `has_void_return<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_void_return_v<T>`]]
    [[`void()`]                         [`true`]]
    [[`void(int) const`]                [`true`]]
    [[`void(* const &)()`]              [`true`]]
    [[`void(&)()`]                      [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`int(*)()`]                       [`false`]]
    [[`int(*&)()`]                      [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`void* foo::*`]                   [`false`]]
]

[heading Example Program]
[import ../example/has_void_return.cpp]
[has_void_return]
[endsect]
*/
//]

#endif

/* has_void_return.hpp
AfeJuV3sDl4L+oidi2cWib87l1Hq1a453KmzXo7Jse6MvVrik+9fx1CFt+b9q5O4eVnepxaYcOa5b7R6xFwbe46VKvbMuove92LPY+T1q4weT3X1ivG9+9Xav4vQd79EHYNoFL+Os81gktm394DY1cQsJ8xEPWN41FifXVXMGutZ+/iBxsUl4wR1xpzuCa6hoISgGSOwuUnCzQ6bm2Gxj1nT3Dstfe/mqqYwzXcC4e/yMkf2qLidIuMSMscm8XyA2alH/DqYfj3G/04uOvzVIDofuLpYn8OdPw7fELuYmC6unbb32tryyhFSDrJOOk90LowJ3id+6ZaZm86U/L/INYzT+RI1fj8UN9tce6zzSC92JvwPXW7W5j/PW5PNPypiuhnvOHecT+9ys/7kJ2Ku1vdqzpeQtK+IeYyW/hS+JYk79Z+a1c76FmdJ/sTvHpuZ4332RWHhjTD+dxT/L7NStT6/LP7PcT/EOuhHXXHWkph9riTRDYaRYN1HjXhB2wAnr0sY14TmYbrkoawrXy7uzgvNQ/I4SdM8S/KwKnYaK2tnuQbGBPL28xK3iezNyVnZWtZHxK8vYbaXaxfM/jJ9Stz8wew9zXiDyKM+OY19xs+14gHhSJqC5gY1J1qejlP9f/ebO++CEZbajQvapQfshhm7keMDducH7cYF7HoF7cYG7DoH7cYE7NoH7UYH7GKDdqMCdtVjjN3IgN3qoJ2J82VBOxPnhcZuhInz9KDdOJPeoJ2J8+CgnYlz36DdaHM2fITxnKII4zkV4eM5qltrxnPoM9WuzjaWE7DbYfbnl/6o2dhNWdj588wTyvUSFacDfAauJpysTwV/fwoKg789NW1C14Px26O655t+fIOYH3BrPx/yTdgco9/XrB+rEvOV7uA6mErT14yZxD1WvPM27UrSMdR1on+XuxHbytgYMx6XnKF70QfbHOmcIt9evCBu9se252TgLE5w/ZWVwZccO6xHXJPpDXdYN8ZkWK/A0tjJVk8Ne9VEn5tdsSmMphy3vmf9wNVofTnmSfM7+Fnx8+KQ9TtJ6naFuF0dG0sf/W3XA65U/a2sEDffcR/jG5A7Y2KtLHeszX2B6RPjJS09bPfyTf/10YXyG227l2fy4I9yz+5nronvG3Jv2mnvrUNZh5y1kmDqIOUZVo8y9Qz8J7UefU3rUc4UU494hmmxHqEbdt68mL/YvB7p80ud3L/erfVK3afZ0l5pyiNpahufe74hudf1oOtbpjw2i5u97ttIy3SeIj5CI1L9eVH0vq31Z7v1Guzv2m59m/pzEl4bM9l6PuZGq8xefyTMzdSfx60/8jt90PVD6ysxj5vy2Cp+Jkdc/3VM3D7o8sU3Vcv23in+dtKOUboZ3Hk35vTPpj+dsvxfGc/tscNnP+Hp78z96wO70v5wXVJuxe5r+/53jefWBZ5/9Z2gEQ41e4Xhltu94VKfGrwEjoOXwevV/CU1N8DlcD9cAX8NL4dvwmz4DsyFHX3PfrALlLUisBCWwdVwPSyCH8Fi6IqhjKEbroFtYSlMhmWwG6yAGXAtzINVcBOshrvhrbABroP74Qafu1i/uS/0mdPhRjgKboHXwqvgdbDOl054NbwDboV3w23w93A7PAF3wHQ3fTacCK+F8+BOuABeBw/BevgcvNXsMa+/V/ob2RhYBxh2hvsYOByOhcVwHPwKHA//CCfAxToOfhWcBA/ByZpfF8JLYQa8D06Bf4Kytob4T4MbYSZ8Fk6HcbrGaCG8CH4DzoZPwDkaf8pe+0X6Zo1/J2Svxv9cjX8SXAaT4W0wBTbBrnrmeSrMhd3gQ7A79BC/HnA67Am/CnvBl2GalmNveBXsA3fCvvA=
*/