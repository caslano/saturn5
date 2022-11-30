/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_reference_hpp
/*`
[section:ref_remove_member_reference remove_member_reference]
[heading Header]
``#include <boost/callable_traits/remove_member_reference.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_reference_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_reference,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_reference_impl {};

    template<typename T>
    struct remove_member_reference_impl <T, typename std::is_same<
        remove_member_reference_t<T>, detail::dummy>::type>
    {
        using type = remove_member_reference_t<T>;
    };
}

//->

template<typename T>
struct remove_member_reference
  : detail::remove_member_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occuers if the constraints are violated.
* Removes member `&` or `&&` qualifiers from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() &`]                        [`int()`]]
    [[`int(foo::*)() &`]                [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() const`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_reference.cpp]
[remove_member_reference]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

/* remove_member_reference.hpp
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
*/