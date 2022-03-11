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