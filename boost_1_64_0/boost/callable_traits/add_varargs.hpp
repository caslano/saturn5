/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_VARARGS_HPP
#define BOOST_CLBL_TRTS_ADD_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_varargs_hpp
/*`
[section:ref_add_varargs add_varargs]
[heading Header]
``#include <boost/callable_traits/add_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using add_varargs_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_varargs,
        varargs_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_varargs_impl {};

    template<typename T>
    struct add_varargs_impl <T, typename std::is_same<
        add_varargs_t<T>, detail::dummy>::type>
    {
        using type = add_varargs_t<T>;
    };
}
//->

template<typename T>
struct add_varargs : detail::add_varargs_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds C-style variadics (`...`) to the signature of `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_varargs_t<T>`]]
    [[`int()`]                          [`int(...)`]]
    [[`int(int)`]                          [`int(int, ...)`]]
    [[`int (&)()`]                      [`int(&)(...)`]]
    [[`int (*)()`]                      [`int(*)(...)`]]
    [[`int (*)(...)`]                   [`int(*)(...)`]]
    [[`int(foo::*)()`]                  [`int(foo::*)(...)`]]
    [[`int(foo::*)() &`]                [`int(foo::*)(...) &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)(...) &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)(...) const`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)(...) transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (*&)()`]                     [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_varargs.cpp]
[add_varargs]
[endsect]
*/
//]

#endif

/* add_varargs.hpp
ffxG/0gF+m1Vv53qt1d9/EY/rsxZv7HqN1H9pqqP3+inVaDfUvVTVb+V6uM3+pkV6CeqfpLqJ6s+zlduZc71q0j1L9H6VWrT21zmXN7LVW+Flvcqm97hCvQuU72fqN4VPj363c5616veGtVb78sf+qPO+XOx6i3Q/Fmo+YPf6JdVoL9R9Tep/k9VH7/R31yB/kWqP0/181Qfv9Evr0B/hurPVP0LVR+/0T9cgf5s1Z+j+jmij9+nT2E6609R/amqPw0mqX9mlOu0zAF1mP8ZNPfzM1zwnE+n+Z72+Z01O7fTzOv0m9Npn89pn8uJS7fP33Seu7kdFzxfM3iuZvA8zdBzNIPnZ5p5mVWakxk4H9N5LqaZh+k3B7PckrfNuewy1My1DJhnWf35lQ5zKx3mVQbNpdR5lMFzKJdeFjB3sppzJiubIznWf27kKZkXmYGzz4MMnv/oN/fRzHucznqVpbjtuEM41+AYV0fcZNwS3FbcQdwxXOqQGNdY3BLcVtwB3DFcs6HsN4IrHfrjXfsS/oV/4V/4F/6Ff+Hff9k7E8CoijMAv012OTZRQoAkhCscAnIG5C5ggIBcQjhFQXJDIrnIAQEBY6FIK9XUE1sVrGhptTW1VGm9YqWKLa3UUqtVa9patZZWaqm1Sm2//fff2bebfYFQtNc+/fky8/65j31vZt5M9Ipe0St6Ra//p+uTWv9fVTbC9wHAv7T+v48V37GWOaE9U1zMv/imfxYWcupWMeeTzSpbVZ6dW1Nr9UfnqRTGkh108ouyqxk7NXqNU1WPo5vWFZaQsMBRgWtR9OvdiV79NNXTrcvC1EQvD72MTNXTo6DCFQeh9+WepN/oTampLiJ2xfm5YbrGz7QZAV1fVlQWVlWFKvZEr7Ez4/eiJ9stFq7KrSmp9t3UuN3tC9PmT1m1ybWCvOq8EtRM/h6aEkmP3FW/JvjSOTOSjskO0qlxMnpTmJ0rzqthoUT2IubssourC0tRtulasyLoLpWt6ALaJvwsdE35FhZXVFfNqCwvNcVr8q4xXG9h4doayi8Q1T5avlmzw/RsaemjfllzAjqLpM7bkzxM41VvdGZVVdUUVk4pK1hECnJL5tWU5hVWBtSNvjU3oD+falA5rbCyuniV1IUZ5ZWluSYag7S+Vhh9m+q0ovLifPJKUz8oUEYXq65keGHlrALKCSdEw+TTSNVtQNfU29yKqpoSX3WMWLamnqTMDPXfVBPV2UudS5vXXEe9MmGnzw/Jg4WF68pJVXF5mU9ZsyE83/YYN6Hq/qzQ9Gk87iEeCVkh8TDtx16nrAUmHpXFq9n5srq8MqSMtR5ULAht404ZNUzrlrUwoD+ncMPiytyyqpA+ydY3aFmovuYHjkx7sOWD9g2LmvVz6NtKWh2Ycjb6Pm9XVxYWGnfNqscgLee0xc3CMAnHF1+Rm3KpaFm3WTk2LW6e51k1eSXF+XZt6qmmN2tJc/1gxOf7MitQ+Cb+Mxc7ptlU2WHavpqWtKjbrG9uWGr0p89plu3EQetAxiU2PfXSqb4cN7pZuVVV68srC1quL3uWhdSXSMry7Vxn2965Rfrtg8Jqixzw9debZW1F5A7b8q+VAI5rJZKI0yH8OSJ9QwktswSHoeubXncIu1HDdvgBOO2w02ZFCruDhJ3TPnLYRzZI2BF/kFsT9vHpzcI261maHMK2rpSwHTp1fGlFvidc7JzvK7wOadfwmz1gtDLsuhnNw56g+f6iQ9hNmu/NH0pOHW4q4b7RlXX3F/nCLcZ1ZRlB4zb025SsOId0b44UduvqeV3zem7CPeQQboLmd9jDJO5PP9yEzObhztC8nhvvUM82SbjhP/JnnPbjF0eo6xo=
*/