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
EmkL4R/8OmV2NbUhwnV3CPe1DXoLQJdjHD/o/BTbiGrciVC5AyJJrp3enBg4n1/Aymc/aZDniHq+GW3qek7KTtByjFE7sZQzAehE+6RpUdmowSVBfvZC2QC8nDSlAXiisOJ7Fw8EP064hqN3aG25HEG9gYyuYwmWIoRFWZE28mldS4X85SuWkOf8MPp1jODwjJqLyQFLZRwoDw/q19cyS5iEAtOaDLfrirH1fHtp/fcaJcN69qdFL4ldn/0U9Di0B3uD/T2TuBRkpQ1cG7LHAK9nZWSWpFy4qH1zcvLNRyu/pmfWbaAaShT3/6VGfulGa17lfPwxl+JjbsjllYakPa2rgSCk0oz7pK9sW7YvQw1IzC5IPOsOple761VLnrvUUETwf/2HjcrCK3JFSz8yR89akl52tXRAIcWD4IKdza/vrUpes/VhQ3hBIKcZwRNDELuE/ZV6GjDroTocVDfey4rjBw1MN6Yjiiwp5PRrXaYu+gPINybfsXhAkAR0DHiKnf66F9HQF82Y4wEeRHF+Z7Nxd10RNPg0LSCr/B8r7INXQsssznHTMAzrTA==
*/