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
2WnYN7i6asYn3kmLKJMmfWb9yiLoXiTA+1Bqq2Iet6QzO3UJF2LWhh28lVRa13uN/PM4lZMc277YQK61ZcQqLpUJrOy/R5PLiw+3o9HEpcOXj34cT2e83qhy7+hTO8bKJDvdit1XXbUrJ6D+VQkp30bMmuwSz3jc5B0EMV7KVGoBQoHFBLtjJIWbn3mdsZw1CzjCbUFwKw+X7BSOTMVsd+jdTrxg3SgfCxBYrrqEsnMwFDShYSntNr1WvDyZgoGgDi61M7+GrTLux40Hysd055apcSqJD4xapjLquCjxuK/cwumT3uVEg9b4QZw3uF/T7AG6ZxWvagyvq5KdPBxc3lyMq4W0vns7mP3YRWahOngHRiyGo8lsWjHb1g7P1sDhb4E6LxJo18uFXfVs1msY0M3luglyny0XPh3hIa4kXtBCLDbVqoGYZNiVXdIr6xEDvbtIbN1Ctm6oEoH9eD24vPLTeQloHj79ZOvXETd9dGmQJI2sgQNQh4Bqs/M+AmnmSTW3CiMP2E4PuuUxzKcRFA6xWjfw1y1gfqupsKvJwb8AATCq5RIgGvGBdZfGvCg8KFM3StzYlIOwR1lWKI0S5ptgdfNxRZ8jjL6HDB/OqS+6x93jbWQrZhU4ltdPijD7c87+DJxXG+EcIH/t
*/