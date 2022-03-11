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