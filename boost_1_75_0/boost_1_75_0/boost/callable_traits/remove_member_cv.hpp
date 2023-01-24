/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CV_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_CV_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_cv_hpp
/*`
[section:ref_remove_member_cv remove_member_cv]
[heading Header]
``#include <boost/callable_traits/remove_member_cv.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_cv_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_cv,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_cv_impl {};

    template<typename T>
    struct remove_member_cv_impl <T, typename std::is_same<
        remove_member_cv_t<T>, detail::dummy>::type>
    {
        using type = remove_member_cv_t<T>;
    };
}

//->

template<typename T>
struct remove_member_cv : detail::remove_member_cv_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes member `const` and/or `volatile` qualifiers from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_cv_t<T>`]]
    [[`int() const volatile`]           [`int()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)()`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() &`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_cv.cpp]
[remove_member_cv]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CV_HPP

/* remove_member_cv.hpp
gpuJMkdyhGCghc5WtSYTUQWqauNQVctkDdSMYL8gvc39tymy/oEJys9dE7j9P4muNfz6XRKpA9fdRtd9/PkueB6fRIIQJx1fqqSjRy+ZdHR2itV45uspJA+rCeWD7bgON0s1k5FEwBphCAeGQjGOhJcn0KwC8xqMXqtyHi/0P5UeeHKm/6HLmW4CO89n7+OEnGSN26nxImnxZGWRn5ROPkmLvIgvqGnPI0XoJheeqi281afw9ViY9Xf5VJkiFBFFOCk996QXRQh9HijCk5winCSKsL83mtRBBJ9+TKfY+o4ptj5K2JC1GSeTjTnpGMAitBVN5jGcTMwebH77OTaZ3+i8irvN5tHBGFL4pVEhBklF8ODrOPSdXiTwVODBizttR2E0h6WXbATrgfB16JlDzDqMwqUFF2YIHvHoNt8jIKkBTmXKB1bGWgALchEehIJnkjtJaOBL5jXbeY+dixFga046hmcUm/KXk63uGMlOBAytLK9ZYgPf4zMqOj1/bdFCXBDcYQewlpPV6gQ4My5cE4OZttSgK2S9cXaGJfhiqMFr6YEohk7ME+OUZfHhWEL3r8YR+l/Dl8nn4+i6VS26cCwVeX8cShy0NmBloLSRDHHQkYq0YRfPMc2uDhWELyG/KayNzXrOTDdgXAJj4iCDcKfJkGwmgY0YRvMFu17EHB+fieTlM8lDhAJzdLV0/CnwVbrnhiSgg6MKHz7Y
*/