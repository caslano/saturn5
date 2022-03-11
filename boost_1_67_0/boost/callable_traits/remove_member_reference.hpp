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