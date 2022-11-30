/*
@file add_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_ADD_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(add_noexcept)
BOOST_CLBL_TRTS_SFINAE_MSG(add_noexcept, cannot_add_noexcept_to_this_type)

#ifndef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
template<typename T>
struct add_noexcept_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "noexcept types not supported by this configuration.");
};

template<typename T>
struct add_noexcept {
    static_assert(std::is_same<T, detail::dummy>::value,
        "noexcept types not supported by this configuration.");
};

#else

//[ add_noexcept_hpp
/*`
[section:ref_add_noexcept add_noexcept]
[heading Header]
``#include <boost/callable_traits/add_noexcept.hpp>``
[heading Definition]
*/

template<typename T>
using add_noexcept_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_noexcept,
        cannot_add_noexcept_to_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_noexcept_impl {};

    template<typename T>
    struct add_noexcept_impl <T, typename std::is_same<
        add_noexcept_t<T>, detail::dummy>::type>
    {
        using type = add_noexcept_t<T>;
    };
}
//->

template<typename T>
struct add_noexcept : detail::add_noexcept_impl<T> {};

//<-
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
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
* Adds a `noexcept` specifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                                    [`add_noexcept_t<T>`]]
    [[`int()`]                                [`int() noexcept`]]
    [[`int (&)()`]                            [`int(&)() noexcept`]]
    [[`int (*)()`]                            [`int(*)() noexcept`]]
    [[`int(foo::*)()`]                        [`int(foo::*)() noexcept`]]
    [[`int(foo::*)() &`]                      [`int(foo::*)() & noexcept`]]
    [[`int(foo::*)() &&`]                     [`int(foo::*)() && noexcept`]]
    [[`int(foo::*)() const transaction_safe`] [`int(foo::*)() const transaction_safe noexcept`]]
    [[`int(foo::*)() noexcept`]               [`int(foo::*)() noexcept`]]
    [[`int`]                                  [(substitution failure)]]
    [[`int foo::*`]                           [(substitution failure)]]
    [[`int (*&)()`]                           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_noexcept.cpp]
[add_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_NOEXCEPT_HPP

/* add_noexcept.hpp
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
*/