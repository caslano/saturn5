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
RdQ7EqI/SjpeRxzol8DnVnJdFtXFRJhePsM/RjSFuyWzk0XKLgpmCF0e6JZo4bS0npSBuEvysljozX0GsRM55DkN+d5tIM3hpEf+jguta75LFgDQbZCicyynI207TtvIN8G/3aB6ap8xQ/FHes8rGiJMkMakP0wX4AFJbHgYnqJY+1pjyWO+KoQVkFD9ib5gU0yi08VSjPb9LM3ajnNPCTalF9XHBR2QAcOxaAeVgcEVP6JwysK1SV6b2RxQ8VJjccqjyPCnRvKpWAduANfCdm1DVOUpi/vyKtp5omcklDKDMtHocIxEoyW0soa+HhEeum7E3WvwiGx7MWTzmNU1vnPrm8ZWBMH85CVvCqrMfc7lb7zUzWTmwzdvw2AUlqG2b3oGqSVVpojlN/lWhegvtrzgrf7mk2U9JK1iQl1+wcu9vHN/B0IOPRim+dGCfNuaJswc8UAE468QfSPBOZH6O8ii3UggaHOFbww/AseIaS4NTjV9IAHhJ50Fg5Nya0F4drr854U5LlrIP13/Ob7jgGIKRJ/Z2mCDSbrS4Siw+t/d0Zg6lbQe14hEqw==
*/