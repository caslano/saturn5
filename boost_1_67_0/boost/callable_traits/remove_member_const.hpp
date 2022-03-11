/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_const_hpp
/*`
[section:ref_remove_member_const remove_member_const]
[heading Header]
``#include <boost/callable_traits/remove_member_const.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_const_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_const,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_const_impl {};

    template<typename T>
    struct remove_member_const_impl <T, typename std::is_same<
        remove_member_const_t<T>, detail::dummy>::type>
    {
        using type = remove_member_const_t<T>;
    };
}

//->

template<typename T>
struct remove_member_const : detail::remove_member_const_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `const` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() const`]                    [`int()`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() &`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() volatile`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_const.cpp]
[remove_member_const]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP

/* remove_member_const.hpp
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
*/