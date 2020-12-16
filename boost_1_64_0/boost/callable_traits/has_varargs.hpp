/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VARARGS_HPP
#define BOOST_CLBL_TRTS_HAS_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_varargs_hpp
/*`[section:ref_has_varargs has_varargs]
[heading Header]
``#include <boost/callable_traits/has_varargs.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct has_varargs;

//<-
template<typename T>
struct has_varargs : detail::traits<
    detail::shallow_decay<T>>::has_varargs {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::has_varargs;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_varargs_v {
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
constexpr bool has_varargs_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::has_varargs::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_varargs<T>` and is aliased by `typename has_varargs<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's parameter list includes C-style variadics.
  * `T` is a pointer to a member function with C-style variadics in the parameter list.
  * `T` is a function object with a non-overloaded `operator()`, which has C-style variadics in the parameter list of its `operator()`.
* On compilers that support variable templates, `has_varargs_v<T>` is equivalent to `has_varargs<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_varargs_v<T>`]]
    [[`void(...)`]                      [`true`]]
    [[`void(int, ...) const`]           [`true`]]
    [[`void(* volatile)(...)`]          [`true`]]
    [[`void(&)(...)`]                   [`true`]]
    [[`void(foo::*)(...) const`]        [`true`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
]

[heading Example Program]
[import ../example/has_varargs.cpp]
[has_varargs]
[endsect]
*/
//]

#endif

/* has_varargs.hpp
frBtjpb7hQlV1lH3k5533D3jDpvwh/javtwfn5BiDffc7OnmOeTt40nS8NORmIVSZt5Y6y7T945C/rFAxlLoM3doG/bb7xP/JsfdZCVjH2xju8V+Rdzb1pPtVV/s3xN/BsVVWSNEP1nbz22iXx7/tKtTe3sbekf0+8V9yerr9b3bZ7lafrfPcAXHRuv4u6ynGd8Uux3YVYeNg9a7AuOlgd853Nre9TFLnV3p98u8+9e5Wr+uy2H9lsO6KKf1T07rlpzGHJzXVx2Q9Vt/W3J39bt3PVkwqf2rq3d2WfQPp/VVrV/3drbW2zmt55OzvWP0mUSfoxrhQuT2mOC6q3GwH1wDB8Cr4UB4AxwJb4FjYJKvnsLvw/HwDTgBDsKvC2HXWN0fG06BBXAq/BrMhL+D02EXOqsZMBteBNfDmfAwnA1XesgDuB7Og7fC+dDbhrjDa+BiGN+W8W3YCS6H17ejbOAP4OXwV3AlHMN6wRx4OcyFtTAPHoL58B1YACd4mQuBC+EquB4Ww35x1EH4KbgGzoMlsGu8Pz+mwwvhU+f40/88nALPPdef/hEwE94Ip8Mn4AzYroM//WlwJvwMnAV3wtmQTlfyIQXOg+vhfHg/XAhHdeQ5EU6Ci+GDcAk8CpfCKXRcl8BlcBl8FF4KX4XL4fhO/vwqhCvhizAHejr786kHzIPrYD68GRbA12Eh/ACugpld/PtNXwaL4WfhFfA2uAY+DEvgSVgJ06iHVXAQlO+M4TpY4Dq972YPl3AeOuIu5ds0ZCKyDKlG6hEZ80IShup6vAjr8BqRE8hAWW8XeZ1d5+HcRxYjuqaO9XRmDV3I+rlG5Cji5pf2GAxbJ6dr5JzXx1Uj2xD7urejiH2f302ypq35OraJtrVrL4atU9M1amZ92v2l0XG//6frk3n/L1+VN2aUbwDgX37/fzKZ35TA+T+6B9gxF89m8BAs9Z3RclHw/V9CZuGBxAcd+1y+7bwWdTPdzOXfI+Z7XA7nh6n+XDEvxny/mL+qZp66Zsmzl8zNJgbGCVZXF4Wc4yJuJohOvoxNVOUXFRbUlBRaZr71LdEpcOn4g7p5V/xYgnnhTJ+53pL7JtyBtjUOxesK88U/2Q/ngLi/yRVI9+/F/XhLzMZ9O/taAg3Tpe8fekaV+F1WU6pjKenwPdFb6krUuH1ZzHtdDcQv4F96mH+H9H1mYCc5A0nsMkLmqcpw63+H+5642+jq7OJMJvPet86cu5MIT4pOW91LjHrmMxP+EOySdH+xHEnzMWpeFuc1tJWwEvUdMvD+dbO4e8AVPI+rKnddoWXO33pE7l8j97+ZKusqilEKvAPLdbmE8wx2HQLzynKtn+mvO/bxnEvF7ofMZPfSOUu//Raxn65zs+KBKeNU8VPsQtJ0j/rRCRt3qD7+il14Hph1FlpvuOS4LbPO4wZJb7yp//v97cOslblTzEl639RDezmlq3+SD8+K/q1SJqQhPP5mXccBXdeRc4p5ySzbuo49vjwNO4NqHww/564BJoo7bZtqfwDSHrE37VH8aDR++NsUdlJ/q8VO24LuOzbQv0+fWf9BHcEsdeR/6h3o7Wvk3eLleye+2bXyl9/Zkr1265j7HvkvewcK9En6W9Ko9eJ2214yo2Fv6LPrA++G58GnYX/4WzgAxuJ+IGwLz4ed4BCYCofBS+FwmA9HwGo4Em6Bo+A1cBz8EhwPD8KJ8BCcBDNP8xk4+ozr/Ix7KPqMG72iV/SKXtHr//z6ZN7/deH/WVj3/7ht3X+67m9d4eHZTLmmp2/gM/j+n5+Xb97+Hd79VX+YOdP7G2L+0L0lxh3+rYDZH/c+0fmqe0OMvhMZfwY7v/MbnYHo+Oc=
*/