/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ARGS_HPP
#define BOOST_CLBL_TRTS_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ args_hpp
/*`[section:ref_args args]
[heading Header]
``#include <boost/callable_traits/args.hpp>``
[heading Definition]
*/

template<typename T, template<class...> class Container = std::tuple>
using args_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<
            detail::shallow_decay<T>>::template expand_args<Container>,
        cannot_expand_the_parameter_list_of_first_template_argument>;

namespace detail {

    template<typename T, template<class...> class Container,
        typename = std::false_type>
    struct args_impl {};

    template<typename T, template<class...> class Container>
    struct args_impl <T, Container, typename std::is_same<
        args_t<T, Container>, detail::dummy>::type>
    {
        using type = args_t<T, Container>;
    };
}

//->

template<typename T,
    template<class...> class Container = std::tuple>
struct args : detail::args_impl<T, Container> {};

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
* When `T` is a function, function pointer, or function reference, the aliased type is `Container` instantiated with the function's parameter types.
* When `T` is a function object, the aliased type is `Container` instantiated with the `T::operator()` parameter types.
* When `T` is a member function pointer, the aliased type is a `Container` instantiation, where the first type argument is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`, such that the first type is equivalent to `boost::callable_traits::qualified_class_of_t<T>`. The subsequent type arguments, if any, are the parameter types of the member function.
* When `T` is a member data pointer, the aliased type is `Container` with a single element, which is a `const` reference to the parent class of `T`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`args_t<T>`]]
    [[`void(float, char, int)`]         [`std::tuple<float, char, int>`]]
    [[`void(*)(float, char, int)`]      [`std::tuple<float, char, int`]]
    [[`void(&)(float, char, int)`]      [`std::tuple<float, char, int`]]
    [[`void(float, char, int) const &&`][`std::tuple<float, char, int>`]]
    [[`void(*)()`]                      [`std::tuple<>`]]
    [[`void(foo::* const &)(float, char, int)`] [`std::tuple<foo&, float, char, int>`]]
    [[`int(foo::*)(int) const`]         [`std::tuple<const foo&, int>`]]
    [[`void(foo::*)() volatile &&`]     [`std::tuple<volatile foo &&>`]]
    [[`int foo::*`]                     [`std::tuple<const foo&>`]]
    [[`const int foo::*`]               [`std::tuple<const foo&>`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/args.cpp]
[args]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ARGS_HPP

/* args.hpp
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
*/