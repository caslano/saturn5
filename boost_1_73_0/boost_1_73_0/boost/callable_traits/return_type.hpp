/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_RESULT_OF_HPP
#define BOOST_CLBL_TRTS_RESULT_OF_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(return_type)
BOOST_CLBL_TRTS_SFINAE_MSG(return_type, unable_to_determine_return_type)

//[ return_type_hpp
/*`
[section:ref_return_type return_type]
[heading Header]
``#include <boost/callable_traits/return_type.hpp>``
[heading Definition]
*/

template<typename T>
using return_type_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<detail::shallow_decay<T>>::return_type,
        unable_to_determine_return_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct return_type_impl {};

    template<typename T>
    struct return_type_impl <T, typename std::is_same<
        return_type_t<T>, detail::dummy>::type>
    {
        using type = return_type_t<T>;
    };
}

//->

template<typename T>
struct return_type : detail::return_type_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function
  * function pointer
  * function reference
  * member function pointer
  * member data pointer
  * user-defined type with a non-overloaded `operator()`
  * type of a non-generic lambda

[heading Behavior]
* When the constraints are violated, a substitution failure occurs.
* The aliased type is the return type of `T`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`return_type_t<T, std::tuple>`]]
    [[`void()`]                         [`void`]]
    [[`float(*)()`]                     [`float`]]
    [[`const char*(&)()`]               [`const char *`]]
    [[`int(foo::*)() const`]            [`int`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/return_type.cpp]
[return_type]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_RESULT_OF_HPP

/* return_type.hpp
SjRg1MyumOZAa4E5l4YXwAwU3OQap/SBEmzJYYaCw+j07Opo/GsMqxLz0oHcqRpMqWpRQMmWHDTPOS4bjIppC2pG4QReoLEEWFtUckDcHCzXC+MwHD0TRgFbMhRsSkTMQmltZXaSJK+1oOyTQuUmybvyB6VdPFRyRUks2B2oyoJVUBseg/OMYaEKnLk3CULGqp4KNGX8mA1RySJRGgwXwmFRHHLTpM0hbeWJnRtUlDFa9zJKGke1KtXiiSPp6FBmtZZERDqQU6FI5hhqWXDtnX3lHUWrqRf4X1vzmG8BSlIy0BumcJT2YMoMmhgujybvTy8mcDk8Px+OJ1dw+gsMx1cO7PhofECtRyLTwG8rzQ2Ra8BFJZAXLefXu5Ig6cPewWE62nf0aalWBt5PJmcpdYbNOawoFciJW1rIubbGi0vNo9FgAowRwOUcJXeddOnBXtLBJcFLlLmoCw57zBiKHpT7a7bc3lX8qcnYAtXfTAKnf7VplHNnW4ej4Wsm0NkT35yhhDQ92eTSTWpBu2bqHFyXNP+9Rk22mdLN1BtGInM/KUrfQEhzLTgztC0k9+KkJ9TB/IZLt3/8SE05zaCc4bwmpKibCN+gZi74bQOqpLjzsKZRtEvk+8G33w22vKaC0ai98LEBSRcgKb5g
*/