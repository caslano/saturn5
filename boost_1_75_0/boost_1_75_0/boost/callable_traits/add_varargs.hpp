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
5bfO2BVyJ7otMnQXQM5zv0e41cABZmjQAt9JKSOb4Da2xewCH0e2zW1lS9SNvMxcLzJymLPLI8RtgT4wIX7GeQN7HsH+F8sYzQjDyOddptFbgGq3MzbHpQI7a7mUuxCROVaq3ObNcKLPEjLHcmRe1QCxOVNiIRY7FQ6JcDst0ks+lc5TfmKnhVd6kCpZ+EgEylK/oMGgcKp5PRpxqg2/e3Gqfg2QnGajL6eCNX98MT+QsBajF/AbtpgTYABqZRW/gXZrO3nM7fj3XLaV+E09fnP5SpQK3k3FGYNTBoIZXaK7cu5+qOiORbLxIbzOll8ng6AARVZRkWriKkTWdks/o5qWh60R5XOI70L3MAH49O46OoFycncdHfE8vjuGy6To6WjGEsm6FSGbUQJU8ayWKt6CVLEjm7unP8K5K5Gqt8LXMkqAoIYvMjDFcCeessaW+4nX4dProV9AGwWD1wKIOeJajtRxOaeOP3fUUse09/ADkdK6Ld6UrsNvNM+RfJ4XXsB5jmR1hlCdCOkxnzpHz1CdCF5nPNWJwBFs2B6o41mMGEWplOu8fcYLFSIvGLzoIeCAtAhSlVQRSbyL0SA6GIcO58yDG+35nCu64sBuAxIuuhMxzCJAjzm18q7DipMi+AtkWx7zO+ehm9QqW7avOMRymTC2w1bghIUKad8sj4eSLyUrlkoLTNoMFIiIFzrFHWzlSLNSgU5bi3UY
*/