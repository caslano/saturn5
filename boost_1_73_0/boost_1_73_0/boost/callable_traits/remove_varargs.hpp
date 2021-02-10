/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP
#define BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_varargs_hpp
/*`
[section:ref_remove_varargs remove_varargs]
[heading Header]
``#include <boost/callable_traits/remove_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using remove_varargs_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_varargs,
        varargs_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_varargs_impl {};

    template<typename T>
    struct remove_varargs_impl <T, typename std::is_same<
        remove_varargs_t<T>, detail::dummy>::type>
    {
        using type = remove_varargs_t<T>;
    };
}

//->

template<typename T>
struct remove_varargs : detail::remove_varargs_impl<T> {};

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
* Removes C-style variadics (`...`) from the signature of `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                                 [`remove_varargs_t<T>`]]
    [[`int(...)`]                          [`int()`]]
    [[`int(int, ...)`]                     [`int(int)`]]
    [[`int (&)(...)`]                      [`int(&)()`]]
    [[`int (*)()`]                         [`int(*)()`]]
    [[`int(foo::*)(...)`]                  [`int(foo::*)()`]]
    [[`int(foo::*)(...) &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)(...) &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)(...) const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)(...) transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                               [(substitution failure)]]
    [[`int foo::*`]                        [(substitution failure)]]
    [[`int (* const)()`]                   [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_varargs.cpp]
[remove_varargs]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

/* remove_varargs.hpp
bkUcXKQVrtGWV68dc4wolhpG75be2wXRil5gd4pGHH5RoKlU5NpKC3jkJsL+fjmb3/VmYwJaUY7GTLo5q1iZpk4w0bfOyzaEXVrgCJIjD6PH8SOcXX2fG4NfLzgto5boPS0PqorDhH3wY5q17Sw1teAeT9GNtTi2c1aC+Z65jh5uAVqUVIsq0+6WKovxF/SSu57voYZL62Jt48Shgte01AZHkO+HSFOF/udB11sAkVFqm9DOjRZnQz2Kc0tEwKG4Viae11EfauoeC5qOO9N/tmonZV9zRJ8lK44Dzlvaezb4PPgbUEsDBAoAAAAIAC1nSlLpECmmGAQAACgJAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9zc2xiYWNrZW5kLmNVVAUAAbZIJGCtVG1P20gQ/u5fMU3F1U5NDJXupUC5ywXuikAB4XAIlcra2Jt4ymbXt7tOQEf/+82ubQj3xqmqrdjryczzzDwzu0n/610B9OHZK/O/jC56+4gzrT7x3P6zd5bdQ3NT1DW9nyNJ4DHkPovg+ZB7CH1I1rLsuXWWPUd07XJzj8RFXmduSRYKc5EjVd1pnJcWwlEE22/f/gCb8GbrzVYMB0wiF5BaLqdcz2PYK7zlp5Ld3g4M34+BW2Bi0EJN
*/