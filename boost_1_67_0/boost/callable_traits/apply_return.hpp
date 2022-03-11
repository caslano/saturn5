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