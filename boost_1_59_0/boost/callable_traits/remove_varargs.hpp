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
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
*/