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
trWwJZ3xslTkac78mCPiGdeUZdYifUI+6mbL01AmZoBZSr/KPAVgYsZMlFdCu+40PV8KL0QBL1qeycVn99JMNDKithh8pTLteeTByCMHhpusoOuDETjuTNmo765HhwoWdo/X4zY8wW1Y2gPsydcdYhfGC/Pqe+EJhoK4FIHGSEam1HYbmpiUJ2nSdq8nzmzpCwem3eTfvjaY5Ms0HMVUExCtjVU6eRRVOsWT0utKfCchXcsqFCDlKIiQbPILWV/RRC1iBdBu8u7U6djbux3iaqwhZhXGHIFmbmUqxOAplaZcp3K0ZB4oV67lkfg/2fANb3YHK1Yed7XEwB5wtzNV+t/ngTynphteSYcuYBJHZyrPYzvSANWmpIJClUrZelMkq0+lV3mlFF7JTJVSnHk/ppshNaa5HzxhMAdEfgtndspK9KFSAynYgHK00cEgOHtyPaXhxC5jJk7wCz73bIMn5gge9BRl4ML66ChUz025NsIZIIPW9Xr8hms5CTN55IJD8IZdPBmsk4wfEuIZoZKYlS8uLGGYnCMZ/qiawSRF0V3JiXBBOEfRQ70Q9UdAriwwidoXeMByMCfcZioqRaOW1LVdkK42FpOJpunYkKdVsUFZYKDglOpyMRAbGt0LJnCbM7AE/Y3wqoopagXW4hDs7NJlHNuSpUMLwAFi7rUZ4GeUCl8zQOSd2w0lpIkNgYi4H2FPWY8SRKHemlMT
*/