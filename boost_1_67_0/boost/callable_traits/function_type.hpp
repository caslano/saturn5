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