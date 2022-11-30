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
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
*/