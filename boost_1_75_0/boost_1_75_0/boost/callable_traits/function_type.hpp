/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_FUNCTION_TYPE_HPP
#define BOOST_CLBL_TRTS_FUNCTION_TYPE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ function_type_hpp
/*`[section:ref_function_type function_type]
[heading Header]
``#include <boost/callable_traits/function_type.hpp>``
[heading Definition]
*/

template<typename T>
using function_type_t = //see below
//<-
    detail::try_but_fail_if_invalid<typename detail::traits<
            detail::shallow_decay<T>>::function_type,
        cannot_determine_parameters_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct function_type_impl {};

    template<typename T>
    struct function_type_impl <T, typename std::is_same<
        function_type_t<T>, detail::dummy>::type>
    {
        using type = function_type_t<T>;
    };
}

//->

template<typename T>
struct function_type : detail::function_type_impl<T> {};

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
* When `T` is a function, the aliased type is identical to `T`, except that the aliased function type will not have member qualifiers or the `transaction_safe` specifier.
* When `T` is a function pointer, the aliased type is equivalent to `std::remove_pointer_t<T>`.
* When `T` is a function reference, the aliased type is equivalent to `std::remove_reference_t<T>`.
* When `T` is a function object, the aliased type is a function type with the same return type and parameter list as `T`'s `operator()`.
* When `T` is a member function pointer, the aliased type is a function type with the same return type as `T`, and the first parameter is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`. The subsequent parameters, if any, are the parameter types of `T`.
* When `T` is a member data pointer, the aliased type is a function type returning the underlying member type of `T`, taking a single parameter, which is a `const` reference to the parent type of `T`.
* In all cases, the aliased function type will not have member qualifiers, and will not have the `transaction_safe` specifier.

[heading Input/Output Examples]
[table
    [[`T`]                              [`function_type_t<T>`]]
    [[`void(int)`]                      [`void(int)`]]
    [[`void(int) const`]                [`void(int)`]]
    [[`void(int) transaction_safe`]     [`void(int)`]]
    [[`void(*const &)(int)`]            [`void(int)`]]
    [[`void(&)(int)`]                   [`void(int)`]]
    [[`void(* volatile)()`]             [`void()`]]
    [[`int(foo::*)(int)`]               [`int(foo&, int)`]]
    [[`int(foo::*)(int) const`]         [`int(const foo&, int)`]]
    [[`void(foo::*)() volatile &&`]     [`void(volatile foo&&)`]]
    [[`int foo::*`]                     [`int(const foo&)`]]
    [[`const int foo::*`]               [`int(const foo&)`]]
    [[`int`]                            [(substitution failure)]]
]

[heading Example Program]
[import ../example/function_type.cpp]
[function_type]
[endsect]
*/
//]

#endif

/* function_type.hpp
yvY5hma+75fxtnv7lM/zKX/uZwM5bNwbuMxQp1NipcqlDRnIUlD4AKXMFvOjIM4Ld7hWx2uXdLwsZ/BV/SM0JeZRGR5cUC6F5YJSk9ED9Ydyaf9Cws8euIvyC/jcMfzcUe8leyt0kX8wz2PKmwcLv6XWGSUQwPKzQQ1CAIryJ2413JipLPsaCQ6eXuRRrTBf/9TICrPrpxZaYegYyBehBdbZS8f7legW4bSBTuJjhGEY75mk0ooBPzVaAd1++tdXQI3hIjCSxvL43xnTnouaMWk7fP+Pmg7LthZ4MY5eVP/zkeAgBl/AQXjj2a8//G3W8OkP/lgDe/EavaBgkn8AqdcuGPxwBvYBK32AFBstCC0/NAFC0w//FggRGWrWNXA98e+3Zsot/pO2O/IWa9b+CRPCiGuMp+blP4Gx96/4E1g53sV4T5Yp9+J5kAZu+t6gqzkNGyU1XiqPj/0hHn0BMs39/FlOF8PWeNPFWV9608XvvlNp7ndveJe1+pRd/x3S3Afktj/wKd/Op3zed1odzYve3pIm01s4UWdeODe1rHkcSCWIt0gmS9KITDKN+6taA0KHAeyVc4aWW63V2C60EuFvDGS3QpIWN0SRQdha+9sobC0VjJILtkO0mc8Bn5NfoYC1Cfy6dgVdE/j9EH4tWKHs4Dz3cqBuj/RYCoOK9DAvPnsFxbvdy+/v5PcXlyvVtmI1IYWf/7mcCn7N
*/