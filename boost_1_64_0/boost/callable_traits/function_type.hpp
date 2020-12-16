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
Nr+fARfD2XApLIKXwCtUvwLm6HxlPvwCLIA3wjWQOJm9Ww5Y+hsNP9D4dYb3a/wqtLzWwmRYqemv0/nVapgJ18G5cD1cqvdXwA3w02reAa+E98JN8Jtq/5CaH4Gb4c90/rhJ7/9WzW/Dq+AJWGfWK+jvp5Z9Xdh6hS4a/yTYDSbDNNgN9oddtf6kwpFq/67kH6L1aKP62x4uVn+H6B4ZQ9Wf4XAwHAE/BUfCafACOB2Og0vgaFio5rfcpzev2nBDW9m/IcKeDU77NZi5V92fwczBmr0ZwuZi368In4+NuE8Dc7QOezU4zNmyd4PO2556/4bwvRuY3zV7NmTyw7UMCezdMBBmVum8b9jeDTsw2/dv2IfZvoeDzgvLXg5N0L6fA3PEzfdzaDZXHLq3wybiJXPHzfd3kHnkDFiPTnCPByQ98j4PzDWbfR7SEZ1zln0eSqDu8xC2x0OzeWizp8Mxn71vnwbCd9jXQeapD3O/CPv4EehA3dNB5q4bYbP5a93n4SAcMs3MYeteD/a57NPb7yGw10M1tO33YPZ6cF8VK3PfozJPPf9t2/eBeXCz9wONMXT/h86YN6Fjnxs/Zp8fd9gHYv9XYprtA9F83tzsC2HbEyLyXLruCyFz6o2wO2ntjh17QpzxfhCR9oJIh/a5+ZmYM6B9Twidq4+4L0Td6NC9IeoxZ2J+3TdPfwX7OSATkRXIJuR2pBFpuiI6jx+9olf0il7RK3pFr+j1n3Z9QvP/uWdz/v+w7AGg59a4dHxG5ym7INf75in94/OBoW7zrXiksevZroB+Yvg8kZmvWCj348380I+TWzePGTYObeai2+ncext15EHqiH96iX3ufaOJe3GnZnFX3Tb8l8m3VKc+KybwzRV+NRsbr4iOjZ/1sXGnMfBtMgZ+392J312YdfyJ/rPqJ8dV7+3z7xujTvDIGHLWHdPf+lrJqPohR378x79/foDT2PXZG6P2jx9rG9S2XBQ2ftxNx2+7w0TYA3Yx47KYzfixtgdtU0Vh48dJ6PmYDD0wBfrq/Io13tMak3P61uHFX37y3zu4X2v9Nw/pr53d7x5WvNa6bx9O97uHna/9a98+3P/af+b3D5uoZ7vWRMdFolf0il7RK3pFr+j177vcSOXH+P5flMv/Co4EPmv7AB6y7QO4Q/da2+9iXQe8CVb79gEs9O8hU5TL/yPTfcskL2B+PuKeYLxHq36mWbPdb5Xs2eKSPXp0/58K1Z9j9CeIeS7mVNUPrvG27R1m9NPFvBRzguhfLfoXhe15tcDo1+mZmJxELPqjXF3ZpyxR3eg6cnIldF8p3Jp9pY5j1jixFra6vKA8uA6/Gj+BS8wmDA9+TWMfF90rTuw6WF7jR7EZF2mSezehjzk8jvjRMXDWiNgXWj3FDodcQd3V1kP4/7aVIPGs7Cl7HNWwX0LIGc13yEImyoBS0/2yzNrJH+hYTEPEWk6gojuh4x5Zf+uSMZAj+v2EfV/CF82+M4Sjdk1mnTzlqXZvwYvC9rw6buxMmZjzmUkT9qTJtt8V6cFO0hOyhrNa91fLpF6nwx6wFvcJRVIfpDFJfS6vLAycObgusDcknukZ1hLufHHjidU6rn7MM3VsyRWyR5o5+2/oGv1OwdQviZ/4N9CXPnF/jvg3x/iXL+4XYs4T/+5Wc9A/r5ZfO6s2pF5kF8uZrmKXqHYb1C4Ju6LAHp8SzuyYG6z+LnGvfdctotsRXdyr3UrRjY95yOotup3U/mGfLjFJVbt2SJXobnVNsjjrwLpF4nEFYcZzb7nci41J1fASkHvE7vOuWGs8a8/mujTe3EMk7W3wQ+Itdn/3+2EF/OiM7Ba7n2ObS80v88dd7/U=
*/