/*

@Copyright Barrett Adair 2015-2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_RVALUE_REFERENCE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_RVALUE_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_rvalue_reference_hpp
/*`
[section:ref_add_member_rvalue_reference add_member_rvalue_reference]
[heading Header]
``#include <boost/callable_traits/add_member_rvalue_reference.hpp>``
[heading Definition]
*/
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_rvalue_reference_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Reference member qualifiers are not supported by this configuration.");
};

#else
//->
template<typename T>
using add_member_rvalue_reference_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_rvalue_reference,

        detail::fail_when_same<typename detail::traits<T>::add_member_rvalue_reference,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_rvalue_reference,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_rvalue_reference,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_rvalue_reference_impl {};

    template<typename T>
    struct add_member_rvalue_reference_impl <T, typename std::is_same<
        add_member_rvalue_reference_t<T>, detail::dummy>::type>
    {
        using type = add_member_rvalue_reference_t<T>;
    };
}
//->


template<typename T>
struct add_member_rvalue_reference
  : detail::add_member_rvalue_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member rvalue reference qualifier (`&&`) to `T`, if not already present.
* If an lvalue reference qualifier is present, the lvalue reference qualifier remains (in accordance with reference collapsing rules).

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_rvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &&`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &&`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &&`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() && transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_rvalue_reference.cpp]
[add_member_rvalue_reference]
[endsect][/section:ref_add_member_rvalue_reference]
*/
//]

#endif

/* add_member_rvalue_reference.hpp
vhTLs+U/28yzxa+/f0uXYHul/0Im7T67HdahjD3kX5Sfw9DH0LzC/Jy5JXabsV+3DLJZiv7x24zlfGqP1D+uS7oGx/XfyGZWFlexHesUV9V3th1L+PHbjv26ZeW2Y73tSrOzgtP3Z/SLTPqChsulGKQfEyJdRSdQBh+bePv3RY6FiOMfkF1fQRyLFpXkeetK4+B4qm6yrZ9ZJPu7mP1fAtIxvRrpaByc/9oX4xoBaTt0dnDa/oLsLue0eauWYxnsqqRu7TqBuvVxFeqW3jusYQ1O2/foHwxI26WF3Dj0CqzEeW4fqWIS/+9CpO/gCdSx7wLq2GiNa2634Li6ecgdqTyuWhzO8T1SSXkcOYHy+K4K5fElzDgOG8o1ZRM5tG3fmlsnH9p+QfXtCNSUbeVrxe5AzP2/u/X23auWbhyTn743qenik29DOVPO/+6K3HXbGn3x6CdJcz54fuUTnU+fDeXQ9iZ+eLaV42rJ+TPvGP7JAwt6rO9y8OW/fbe2Q8U2l4tw/ORdoYj4tbbsbdr+32j7f6f+38ayPev7X94Jl6hdhx22/29Se82N+X+D/v8b3FG5rq4T0rVHVlhdKBNJ1HZvMlwAW8CFsA0shGfCIm2Wi+EIuAiOgj+Bk+FiOBMugUv1+FHx6xoamKvXjYUL9LofRnjsUHwEW8G/w0HwH3Aw/AKOgJ/BUeofp/6J6p8K/wJnqD8L/gkehatduqYFXqrXrw+X6vW/0ut/DTvAWpEYUYG14Uh4BhwLI+BE9U9V/wz1Z8Hv0c9Vfx78Fv9C9V8C/6XxycYd0fikanzsNlgJL7M4G0bDObA+vAg2gDkwEebCZnq8OZwLW6r/KHzLu7YCPqbXSYEH9Dq9Nd19YRLsB7vD/rAnnAD7wXPhEDgQjoSD4HiYDifBwfB8OATOgkPhXDgMFsPh8HI4Aq6AGXAVHA3XwzHwVjgWboaZ8F69/gNwPHxQj+/W40fhdJeuT4Almr46cKymb4fbk76HYBJ8GPaEu2A/uBcOgrvhUPgYLNDjen6dq08cQ5y/vp6/AUyAcTANJuh1kvQ6iXCI+keoX+ulzmvn3gtRL3l8yPk/gwnwc73//g7Pgf+GveFR2B9+CdPhP+FI+BUcC7+Gk+AxOF3tvmTBb2Cunkfrpc7xpoxC1Eu3pjdS0xul6Y2G58C6sDesA/vDGDhIjw9V/1GYhzui1xmn14mBM/U6U7ReToMJcDpMg+fDc2A27G3Jw/7wQm0vZsGhMAtmwGxTT3QOMRwVohxTNF2NNV1NNF1NNV0tNV3NNT0t4DA9fhRasrv0/JF6fott9fwz9H6eCSPghd78NvNZpW6LXicrv6H1e53zd4VvwjT194SHYG89PgO+BXPhO3ABfBeugp/Cm+Bf4c3wT1Ds7pMvO4EbPgqj4AuwFnwN1oUfw1j4DawHzyBO8bA5bAoHw+ZwAmwJZ8FUOBu2gotgW3gD7ABvhn+0rg8/hFvge3Ab/BvcAY/AJ+AX8Lfwn/AVPf5HeAz+Ff4L4lzfwH/DzpyfOLi6wLNhV9gN8r+2gzr/D6a7g9vBPZRHJ7gXdlH/2fBR2E2PT4G/hLPgPligNt5L4JPwSvgUXAH3wxvg0/BG+By8Gx6Cu+AbcLfaet8PX4XPqA34t+Hb8FP4B/h3eBg2tPIPtlFb7e3gx+a+1TltMDvEfTtR2w/8Un+nwsFwOhypx8fAKTBTj0+F0+AF6tf7VueWUaYh7tt9lIfF3+h99AJMhC9p+/ssbKL+pnA/TFV/K1gO26v/KHwed8R7PS23ZPlWrGu3eK42gpNhOzgFSjsBh8JZ+tzOhjlwNlwI58Clevw6mAc3wPnwVlgAn4GF8LewCL4=
*/