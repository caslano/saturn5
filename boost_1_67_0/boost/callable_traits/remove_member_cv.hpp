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