/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_APPLY_RETURN_HPP
#define BOOST_CLBL_TRTS_APPLY_RETURN_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(apply_return)
BOOST_CLBL_TRTS_SFINAE_MSG(apply_return, invalid_types_for_apply_return)

namespace detail {

    template<typename T, typename R>
    struct apply_return_helper {
        using type = typename detail::traits<T>::template apply_return<R>;
    };

    //special case
    template<typename... Args, typename R>
    struct apply_return_helper<std::tuple<Args...>, R> {
        using type = R(Args...);
    };
}

//[ apply_return_hpp
/*`
[section:ref_apply_return apply_return]
[heading Header]
``#include <boost/callable_traits/apply_return.hpp>``
[heading Definition]
*/

template<typename T, typename R>
using apply_return_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::apply_return_helper<T, R>::type,
        invalid_types_for_apply_return>;

namespace detail {

    template<typename T, typename R, typename = std::false_type>
    struct apply_return_impl {};

    template<typename T, typename R>
    struct apply_return_impl <T, R, typename std::is_same<
        apply_return_t<T, R>, detail::dummy>::type>
    {
        using type = apply_return_t<T, R>;
    };
}
    //->

template<typename T, typename R>
struct apply_return : detail::apply_return_impl<T, R> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must one of the following:
  * `std::tuple` template instantiation
  * function
  * function pointer
  * function reference
  * member function pointer
  * member data pointer
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* When `T` is `std::tuple<Args...>`, the aliased type is `R(Args...)`.
* When `T` is a function, function pointer, function reference, or member function pointer, the aliased type's return type is `R`, but is otherwise identical to `T`.
* When `T` is a member data pointer of class `foo` to a `U` type (such that `T` is `U foo::*`), the aliased type is `R foo::*`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`apply_return_t<T, float>`]]
    [[`std::tuple<int, int>`]           [`float(int, int)`]]
    [[`int()`]                          [`float()`]]
    [[`int (&)()`]                      [`float(&)()`]]
    [[`int (*)()`]                      [`float(*)()`]]
    [[`int (*)(...)`]                   [`float(*)()`]]
    [[`int(foo::*)()`]                  [`float(foo::*)()`]]
    [[`int(foo::*)() &`]                [`float(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`float(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`float(foo::*)() const`]]
    [[`int(foo::*)() transaction_safe`] [`float(foo::*)() transaction_safe`]]
    [[`int foo::*`]                     [`float foo::*`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[/import ../example/apply_return.cpp]
[apply_return]
[endsect]
*/
//]
#endif

/* apply_return.hpp
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
*/