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