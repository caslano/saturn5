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
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
*/