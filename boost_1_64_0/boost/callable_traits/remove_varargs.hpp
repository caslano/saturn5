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
dA9mNo9epp76RrdTARbQVn0EUtBk7FSXSfk80qXhjaFnzwPaUjRva3upY1J82nfx7Dk/ruGRpZBrnC+B48dA5lyHR7uZ2qPELQit/OOFIOJRG1J5fL0pd9GUc0OgPrk6YgLzqe0yVjl5UfyL/wAfAoy99JJxbVG4z5O1ED1rhwAhNpRQPnSv+rH6SyItF/8Mt1bg1kJ/s4/TS36RJg3blSiZ/R+tuRKcfQ5IV6NKRN+gnqWKJ4abgm8qm+/BD7gS7CWMse1TBncFyZ2RzsdQ+Ok3dEuz0HPDG1Y6gL0Ei5JRCNQyB9p05rgLz8xJgjY8oU1SMIAd7kD+B6/hD5n8mJJqRAaXcBVW4WnZowKFD2KiQQ5WM7dMybdq0PrZNVKYznlYoPBNwED5ebQ4dL3njKWuQSDgokR7brNY3P6M1o7i9btADfFsOnO7bBcxPT82sYm3DDzsGxzPqRacfWmAFQA9GkpW1g5rROSoPaUNK80THaXS6Lfbtlaa+ogBJMsGnoflIeUF/0H5bBTltD0axxGSokz6qtpl/sRq3ur+dvZVhYGTq9LzVPP4LA==
*/