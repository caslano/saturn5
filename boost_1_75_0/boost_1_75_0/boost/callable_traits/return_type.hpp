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
RTtGNtEB/7Sj21wv2hE2V6EdAXP/c9qx+fhf0Y5Wg2gR6/n1XAyP/+DXGn79LoZox5cxzdOO7v9Tace7MU3Sjmd4s4ugWW+70bpnmrUbWZqyG63TNWc3cmf4t+mF+NiNpmS0xG50T62v3WjLQI3dyFvHvUzXIh33fPr/ozruyPQmdNw3e/8NHbdjulbHvfKXluq4qdeCjrtpIKFf32jkNTnHLYLbepUQt+V/FjCNh+B8lFHwcE7JVUJONYOsUM+atmzzmOvYStsj3TdUJ/Mp2N4SqbIqhkAOMKrB2VoQ2vino99g+xZPgCBajUI/vbClPsBe7KF/Q+1xjNx2AartTmUzYw8X+pmELedY4X3Cvl/sYonQb6sQV/a/ttBkpFC68wKrBV7ooNZO8Xd73A6HaXidM67OtPArNviR7kHrdTrakhcpLGjQhet0D7UHj0dncFhAhFFClKW2F3h18XE3hBx/HEKx5BR5M9o96FMw30WLOqsr2CGOMAoiIwu7nXHVGQZHv621XZzidke/EGnW2SCd3T06CIo4+223iwek289CfAWhAZv929ig9gk531+Qln/1/1H3HvBRVVnA+EySSSYQmKEMBAtGzWpcUKOxJBvLDCTwBiYQhUhUSpRiVFxRJmtYQMEQyfgYiS5rL1jBjmUl2AgtiSIkFCmCAoryxsElKJJQwvufcl+ZSQLR/b7f9/v7M7w37913y7nn
*/