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
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
*/