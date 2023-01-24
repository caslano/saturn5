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
G0QSGaIZzl4mk8R6u3jKDqe2ZwmI2tcgsjNO1Jt4Ux2gRZ2Mz23nMXweezPNRVs92Wohn8gLE2jl1hEtkBBt0QRBIcr8xSGOyz+oD01FSfGegkKOx/t1iIfVfvFnt9Q6lfBnnVo/O6tal96OnALy1N1dayJuJT8YxQhPXcwuxqDqOOkhZ+qhJw3UTh4dbVynTJCzHmbn1yASF9HUlLM9hYfbrHASoJ93KnOkG0Uwt/C5ms+LpPPrTH41OtQ5aaQXT+2i0Ytdytbac/j16RKPxJC4RBZMM1SlQ4C7zacEnu6nzfhAOHw8FPVdOHh8Nx48XiVrsUyw+saNA6/KO5L5MDxKByvZlErh8inVJCKBWr3WDko46P0Pm+W6XagIaLm1DIbsN1TLmV6ty/NkPqbqztQvgiUJF/FsHkYrkoZcso2mpEL6Q+XRamj/tMDGmjSDZ0cO7zZ4rZDWjmxM6xW093RW0N4p1jvE75l4zOWYaugGobtBWoUSEIiZJdLmsYp8WildkUvyaQkH43OLkRSOuZmfQPiMtvDvOd6F76XCV8iFp2sLl/kUHrIYxFmeuNpWCehfLgV2VXcgrsAlMM/IQFWmKrrkHZMVXTC04rm/zjJpYWfcWu5g5Ut0ijpTot15/4LqfBnMvuSE3PW2Egy5Lpf+uNjg1cGXRJgPxZEWyugfPMHe5HlqJjG1h4Hyp9c5KDn6NO2uwfX2qB4Z
*/