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