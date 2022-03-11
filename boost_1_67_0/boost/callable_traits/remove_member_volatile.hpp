/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_volatile_hpp
/*`
[section:ref_remove_member_volatile remove_member_volatile]
[heading Header]
``#include <boost/callable_traits/remove_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_volatile_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_volatile_impl {};

    template<typename T>
    struct remove_member_volatile_impl <T, typename std::is_same<
        remove_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = remove_member_volatile_t<T>;
    };
}

//->

template<typename T>
struct remove_member_volatile : detail::remove_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `volatile` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_volatile_t<T>`]]
    [[`int() volatile`]                 [`int()`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() volatile &`]       [`int(foo::*)() &`]]
    [[`int(foo::*)() volatile &&`]      [`int(foo::*)() &&`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() const`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_volatile.cpp]
[remove_member_volatile]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

/* remove_member_volatile.hpp
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
*/