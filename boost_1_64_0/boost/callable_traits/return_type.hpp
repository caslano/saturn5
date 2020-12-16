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
z4TJcBYcDGfDdDgHZsG5sBDeBBfAefBOuADugovgAfU/BFfCF+Aq+DZcDN+BC+FJOB9azguvW3jbvHLWbsxRzGlMxHzGXc8v9z+/nuHlGiefTF4FGyv/dkG5ixovnza/3CWPmS8kzGrMw5jjmO8x8QvYtxczA7MRc3hB6bj50qP0KD1Kj0s5fpHx/5NyCgovw/5/nnH+uzzrlvCR4bQk1tS81JZXtdIx/Pfj97W/X2rBlHydI/AA/kmv2f1btUrUsL/Cb8YxPz9b2N34z/MN26athk2ryXvi635+trB7CJvm49+6vfe8e/FL/r2fny3sPs/1+vi3adVSw+7Hr+JxPz8NWwf/HaSroaSZOQrjWHfIN8uMzNe/DyDD5dtlNh4PIMNl2mX2B5LhcuwyRwPI6CXJHInO0ZYZA3rOackRVgSrDKYr17x6XfHY/cIEiUT7w7Qu0HYMgrYd28eZDnMFPsfWoOcgYy7xHIeCnGN/0HOQsZd4jnh34HMcDnYOCuZSr+PmIOc4FvQcFOxFnsM7fppuZjlm6F53aTCRc5w055Do6f+Swg6035XKNjJ9bmVv89j7OgP02ahsGytG+9+qimwT51CubgJSB2gN8K6XlbRB1viz9eWMzcnKzdR+G29cHXScbIn+FLNWaKSco7nzLloxHrEyte/TG74V4ZAz54u2rVuZn5ppG9e5T+KZ46hqufzD+KxVFKdjWXuL/E3IlqOnKMST56wfUQ87/vgcEX/iMmF13xgdqxcq/h2czzicfHun6pg97zmjbOlMT7XvXxUh4RKd5RxVuVbcTDor268tq8A2hsMp/lWL/H32DdI9NNfjr2NmHok16zVK3sdr3j8o7mMkLfaxMzoHIj0/f6YZh/iSxBfwmnRMQvqYMfyvo+ePFfl5VhwVtpknFGkdDfNZdyhSr+E6kUnGtZ0ZBzF7vdZNWStS+8DX6xh8Wx9gtrhh17rRUexlZe2ypW7uOW6+nrJ22d8YQxtSO9QZIWuEesbSRqnMaWR6IRPhmvdiROVQH7+wMPWLXFAnwl1V/HQMoawp2jlKjKxdNhR2xXRX0wNzQPvo0iw5gu6ROczSPTJ1vKuOj8DuM9/Cb66F3FfitsuvH66+PkdO2p8jJR/3EjYeUjcIK3XDjD96UNyoF366Z6POOdiJvm6gRPfQ4F9C9/AQCKx7kDXj6QZjby72ma7nrZBAfcYq38HMTegg9omujVzp51am06t7Xhf3OsF0j8ZzddHeqoF0j+rCdiKX59pM/EMdP6nu8YZvpzrTe766kubH5T6aasYobN2EH63qfmkLqKeGIv+T+K9yxqqeGmrChATUU1PF7wFky1hXUkKsiYWeGmD0VK2Nem/46ykds9JEws9x7eQaRzlCyUPczTlr+espo5dbiv801zbCXeEY4BQ9a8K9h6Yc56+vzL3e546i+zqUv2A6q7dHRv0nkKdhqpsY90Qc2Pk9R64tXtwII+1rD4pbeDAdZuaBvCPlss9yUhY9zf7A3vTXM+clv4xOjIf10QnusqQvAp0i+mJ+rfAyLIgYj1YJieSfu1xERDkr0Pi2ppK2FKNbiIf1Bo3e+TqiRhkfv3lev5iFQyPcseKn40yD6p1uarobg91PD824gB5Ks+mh/X566DE/PXQ4gB46GkQPfR1AD5lPB5vOmWB0juom40ZZ6Pj9tndo30Csr17qoeOeZ3n6dpSJyKzeXEIv8eIYUC+pbGMzNuWg2JNdj1nOQHpJ5dsavfSC2Hu4VlE3yzpqO73jk1Lu9LjfwYjWvGC6SePqKPVtfwDdFKf337Mid41rqOWW0VNrONc71gCn6iiNpzXhkTfnriXpP+ino8K2yL5+avc=
*/