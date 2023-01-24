/*
@file remove_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(remove_noexcept)
BOOST_CLBL_TRTS_SFINAE_MSG(remove_noexcept, cannot_remove_noexcept_from_this_type)

//[ remove_noexcept_hpp
/*`
[section:ref_remove_noexcept remove_noexcept]
[heading Header]
``#include <boost/callable_traits/remove_noexcept.hpp>``
[heading Definition]
*/

template<typename T>
using remove_noexcept_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_noexcept,
        cannot_remove_noexcept_from_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_noexcept_impl {};

    template<typename T>
    struct remove_noexcept_impl <T, typename std::is_same<
        remove_noexcept_t<T>, detail::dummy>::type>
    {
        using type = remove_noexcept_t<T>;
    };
}

//->

template<typename T>
struct remove_noexcept : detail::remove_noexcept_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`

[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the `noexcept` specifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_noexcept_t<T>`]]
    [[`int() const noexcept`]           [`int() const`]]
    [[`int(*)() noexcept`]              [`int(*)()`]]
    [[`int(&)() noexcept`]              [`int(&)()`]]
    [[`int(foo::*)() noexcept`]         [`int(foo::*)()`]]
    [[`int() const`]                    [`int() const`]]
    [[`int(*)()`]                       [`int(*)()`]]
    [[`int(&)()`]                       [`int(&)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_noexcept.cpp]
[remove_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP

/* remove_noexcept.hpp
fIo3KTwgcPon+F07iiU4spMyvYJ4jk2sqZ2tiv1JpbaSSCryewrEssBhCGNTcEtHWj5INLZCMRk3mrMnZxfRLvPyzrTLnD06KgbyLBxEuDDwqZKJTYG7XM7twNjMJzweJFmavF5VPFhkO07w1DlEugjIhpnUkTI4CiPBtCGhO1imbrPxdBEPtQHhzVbsEEvExHoBjs54zEVCWLG0N5d10LNNyDlvymLszHA5a6q2SHA/VYBif1KZdHgMlS2TXs2lX4XS81CLg7mzDlz1RNbs4qQIuzgv0i7+gMC+4RYiVFNHkDw9nq2dyOyHwYJpWPEGzCaj419mdBFEO3rYwpXZTIwUcqYZYf4iJ6EdORxsi/Gshws7Kib6WDYzXL5gnD0aDMN3ukAEBus2vWCkyD3GKA3sjKT7ZjAgY7lrXeBsCGI0IBLYajS39aIxbhtGFcHY4jxBFMTC+hGPJsmlt3BbpNdYdq9WxtJNHksHZSwFeMq7Opw9XuMp6tDceJ7O9zueG7v7jOfO/JaM5/4G3/HssPkbz5lVlzY3te2bG8uOhX7H0rarz1iWLmzJWFZc9B3LuQSNnZjbokXDbWqfLCgbg3cxksQBpmsmzwnWxexPcA/TS4N/C8L+gZ0YirjNo+ZAyg80S4UDy4Onvp2xYP5n3hluu96D/la7a5ICmX3tlF5E23OmVeuc7lFV7EeVDqjxOdaRzQ8F67AbH57h
*/