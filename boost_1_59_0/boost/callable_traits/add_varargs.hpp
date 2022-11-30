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
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
*/