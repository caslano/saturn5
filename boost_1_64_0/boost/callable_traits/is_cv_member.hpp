/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_cv_member_hpp
/*`[section:ref_is_cv_member is_cv_member]
[heading Header]
``#include <boost/callable_traits/is_cv_member.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_cv_member;

//<-
template<typename T>
struct is_cv_member
    : detail::traits<detail::shallow_decay<T>>::is_cv_member {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_cv_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_cv_member_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_cv_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_cv_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_cv_member<T>::value` is `true` when either:
  * `T` is a function type with both `const` and `volatile` member qualifiers
  * `T` is a pointer to a member function with both `const` and `volatile` member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has both `const` and `volatile` member qualifiers
* On compilers that support variable templates, `is_cv_member_v<T>` is equivalent to `is_cv_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_cv_member_v<T>`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const volatile &`]         [`true`]]
    [[`int(foo::* const &)() const volatile`] [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_cv_member.cpp]
[is_cv_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP

/* is_cv_member.hpp
k76pTh+n0zeT9Gzr9BNMX8uxFQlDx3q9Y9AIRsKusBFMhdFwMGwMh8OG8Bi9fRyM8lq3JUZ/D7uyvyhxRh01FJ0yw+4vssUWW2yxxRZbbLHlvyOHtP2fm33Qxv9v93oPYK9u/7dBpR2BHk8DotC37VurtQAkDTlZtX+13bL9a9rNNiO/qO153nY9H3sN+3HnX9xG1u/V6/Yg5fFr+8UvkvnFjy4ennPO8NOfPvOFPV3OvrGPp+1HOl1m8a9IMNpX/11ft90ioHznGzaGkTBOb7eEDWC413j8QrtdZYsttthiiy222GKLLbbYckjlkLb/s0uKDlb7/1av+f/leux7sG7/90fH0P6N8Gv/8/O1mv8v6cjFog/AtFvP/zfjWM7/N+3W8/+J4zv/P9qMm5s9Y1ZBSebEWZOU73sApKn63v2sAO8MpPjFnef1zsDqxv+cdwZiCSs1w/z2W78jPsvifYJx0q/x9rSZy77++PvJtx9x6d7P7v5xt/Rr7PcVHBzgfYIo3a/REPaH0RbvE6yx+zFsscUWW2yxxRZbbLHFln+JHNr2/8F7//9G3f73nvueqtv/R6LptCt3dfZr/9fy/X9PuiOt2v+m3br9b8axbP+bduv2P3Fq//6/d9xStv3nH5jtfokbuN3f4B++VoBu7/vPYzDrwSZXoHqAdqlaD/bXAut6QDrreiD2musBcazrgdhrrgfpXWpfD9K71L4eEDdgPWj0L68H5cGB60FZ1XqQUpt6UFZDPSirRT0oq6EelNWiHpQdQD0oO4B6UGZRDxr/S+tBZf/fpdL/l782KbO0ftQNW/IaZid3mfui7v8zr4PsSID+v2jd/xcDj4SxkHT6HLNO11Kna6XTxXulK6smXaJO116n6wjjAvQ3vkZ/YwXastDud7TFFltsscUWW/6YHNr2/8Tsg9X+v95r/n+pbv/308/7PdBR7vf//dr//HyN8/89afpZPuubdu9nffM537RbPudre7XP+cQxn8cnVPPsnuQXl+do/V4BJH59/fyeUsPz+4AAz+9DA7xXkO79/K7DMgI8u08I8Ow+pZrn9OflOb3duevXr3kt5rGvUyY06NO5YTP9fbnKfdTHVwX4vlw9GAUbwgawJYyBCXq7PYyGPXT4EdWM5w+2n6ttscUWW2yxxRZbbLHFlv+oHLL2v/7jYLT/Y1V4ZH/anC2DDNqRZvP+2NRjMlQUtgFuWyO37dhhQ0YOlP6CK7zmC2To/oIE3V/QFE0lzQqXb3/B4FzZi9T8GdnTlJ5/XwKlTZ+aVzJCj2Lpb8Pp9E291pUrzM/KKyjJLS3R/QeVcRIkzpAIndfYrImV3/NL3x/Ha75/dl7hlNwiycjsSzDjHdB6g+759Enmd9V89yMaW4rZF7C/7NG6j2CIhO8vb6xPP4FXGXX7PlX7e2eoEjk5jDQwHbr9XV6NvzPHMNM/p9jL55OLsgpydKjpc51HH4lHuQP6Cr/reJ9Y+92Ms13isE9Vjt8w4jiD3HFah+ljoNN0w+7JV5FvQQ556u9IVoi9Y9j+b/QVd1NIa13+lGC3fX1wiOpvjDT6G8scFxntXIOMmUH9jQ7EKSCPBfKbN4c66fm4R4Ww3kWI6ucMVq+4QlQcKSeGBCuv/Lt6579d8r+TfwcYI4w+xiLHNUYH1wCjMKiP5B9NnFGS/6ZQB3lfZASr1xzBqpHLoe4hfC8pj8BSZ//+yb4NpVzRkm5xqNdvJ1d+f7AxzBP7NZKvVxzzG4UxsLvEedMvTmZJVx1nKr/zgcR5wtVXfeb0jtPN61uHPWQ/411O1czlDptGuqcl3QWu6ep+n3QUwFyz8TqJc6ErTz3mEyfZK06w5H28q6c=
*/