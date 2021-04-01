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
CQE5Y551Vda1wRnq4x5mHdGcIYvRhzvDo3DbSxDYxcVtm4hoMt/6IwKLnogksuIFdzzp1CDJc/J8GRctA01XSZv9xbgUyzBs1WFoF6bt4/EMETmKvv+5ctkZWQAC/uMuTfgnvCPvJ1pocV/SF1Qo0Ol2och0UG5dsL7+ZwUMM6bUew2o4wfFHHJj9/uihliyo4SjT048qwJEZQdrWOQU792LlH/T6BFPlFzUNYGodJF/Vx0gdrObom811KXKrA7d0XOm/zkb/pL2MTDPkFcv5IQIOgojoWS3y04a19/NKMUiDcbUKF4JRsEv+pnX7FrctiNV919E64LnlKGoNTuWTMzWwKSpdzM1yGhGmudac/45JJEzByhfQxyna5e0OxHMERWChksT+3leinJoQlocxyfnCxH9F+z9umyvk9YRpfIVpeeR1wPFUNhgGT6kT0VExi8vv6SVAwMsfa0abKdGmF+Le6gXAk7UhIZUmQv80URR9crz/hhOJTCoKluEs+SRmGYaJXVXwsutmpUuvpqhhr6yXDI5PI/HpHEzZdMcU0DU98+/VkmlM9hPFw==
*/