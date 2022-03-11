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