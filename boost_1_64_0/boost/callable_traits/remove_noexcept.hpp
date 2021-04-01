/*
@file remove_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(remove_noexcept)
BOOST_CLBL_TRTS_SFINAE_MSG(remove_noexcept, cannot_remove_noexcept_from_this_type)

//[ remove_noexcept_hpp
/*`
[section:ref_remove_noexcept remove_noexcept]
[heading Header]
``#include <boost/callable_traits/remove_noexcept.hpp>``
[heading Definition]
*/

template<typename T>
using remove_noexcept_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_noexcept,
        cannot_remove_noexcept_from_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_noexcept_impl {};

    template<typename T>
    struct remove_noexcept_impl <T, typename std::is_same<
        remove_noexcept_t<T>, detail::dummy>::type>
    {
        using type = remove_noexcept_t<T>;
    };
}

//->

template<typename T>
struct remove_noexcept : detail::remove_noexcept_impl<T> {};

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
* Removes the `noexcept` specifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_noexcept_t<T>`]]
    [[`int() const noexcept`]           [`int() const`]]
    [[`int(*)() noexcept`]              [`int(*)()`]]
    [[`int(&)() noexcept`]              [`int(&)()`]]
    [[`int(foo::*)() noexcept`]         [`int(foo::*)()`]]
    [[`int() const`]                    [`int() const`]]
    [[`int(*)()`]                       [`int(*)()`]]
    [[`int(&)()`]                       [`int(&)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_noexcept.cpp]
[remove_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP

/* remove_noexcept.hpp
CG9aRv5CESm+7JxPPVYloZg8kNhiIJxIvB80Sy2sK8OZFBsgklhWrNfkKa8fIqduwFA+HzDIfeErltU7XpfS5iWJe1h335akXWdSDH6C+2riWZ5OITDOn8uoLXgshZypFRUoCRet8khr2Xzi0GhUknulez2iuofIms0SQHN66i3qJNo8Wo5ZaKD33mdnfClNQx9eBJguE66h3/od+6pG7uURTr3Y86n6GxEos2B1fckbVqwO46pKNZrm5NlUy80MhJit6JqX5kvhrXUy2g+BTvr1/dcD8f8IU1bsi/CFguT/RZzVVz4933g+Bn/T5TqseTbVQ4E/+lkOj1B2hOCI4bg8jW8ZvsTVJv3wWaVkYf9zgdcE7nk43zKKxBzWZ+cnKoqz3eAZL+YPaABtEIVFu6GMztZnQiadixpN7OcjP30xxiggUzqllIVoe6LjDKfeVFBf+knPqrvtEo2Sn8NEBo0902J+JkxB26sOSWkp1rXKcL3wS8DEUn+h8pXYesJbtNIztAc/0mEKUCFKBglriN/MSgA8O30+sFr8guquMRxqFSaUK/o8G6RT+g==
*/