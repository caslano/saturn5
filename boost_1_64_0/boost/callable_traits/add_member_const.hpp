/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_const_hpp
/*`
[section:ref_add_member_const add_member_const]
[heading Header]
``#include <boost/callable_traits/add_member_const.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_const_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_const,

        detail::fail_when_same<typename detail::traits<T>::add_member_const,
            detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_const,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_const,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_const_impl {};

    template<typename T>
    struct add_member_const_impl <T, typename std::is_same<
        add_member_const_t<T>, detail::dummy>::type>
    {
        using type = add_member_const_t<T>;
    };
}

//->

template<typename T>
struct add_member_const : detail::add_member_const_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member `const` qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_const_t<T>`]]
    [[`int()`]                          [`int() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_const.cpp]
[add_member_const]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP




/* add_member_const.hpp
fTgVHoYz4IdwLvwznK/+heq/Dn4Gb4Cfwzvg3+Dd8B/wS/gV/BZ+DWPIu2OwAfw3bAu/hefA/8DeMNLN9WE0nAFrw3xYBxbAevBKWB+ugQ3gjTAR3g2T4FMwGb4AG8P3YFP4GWwG/wZbwq/gUa4bRTl+AaPhS7AjbE14H9gGZsC2cAxsb2wj6bcX/Y6TGWAb6Sy13ZMGm8A+sCfsC6fAfnAaHAQvhUPg5XAovB0Og3fADPgAHAV3w9HwcTgWvg7Pgx/CCWb/fH2P128QmQH7569RW17r4DB4AxwFb4QFcJPtfj+o5/k2xP1+m7Y7d2g93gLvhPfAB+BWuBNug4/AO+Hv4F3wTXifaX/0PQqOcGp/VK5I5XpVIleucsm4vAC5VJvc4SrK0Qc1cqTZJ6fp2FkNm0Wnev683YZRblzMj8qOUVlcTJXm24e2ZXTq7Bj9GG0YVWC/qEq2i37IdotOtc2iH5q9oqraKjpZawXiepKvcTEn1VbRLs7/Li4qHjtEuJm4lbiduIO4L3GJCbQfuGzcatxO3KGE8LqC8C/8C//Cv/Av/Ptf/52q+f/FxSc+/7+FKzY+whoramGtx1ZjT1nFXLawgAkaEh5JeFxbe7g1jlFqBcv6gYdTXL55Jm4d1MXVk2+jhCWh71k/MHzixKwFhVg10jMRlxJj2+4pzrBfXOV7+XvHUHa5nb7tO401VP+beXXtOIT+ll79sRunMYhpMsbx3Ytn/6FH35g37nq26Vcxcyb8zGmMwOkbvtM3+ZM/BuTZj0DrhNaVIzj7fgT/Unv138Lm8Dt4JvwP7AvdVKaBMAJup/KU98JuKI7vHaG+Zzh+y5jOsVKcbe3/aV33fyrX/B/Pen/bWv9K1/l7vx2k4QLW9ldrXX8la/orXc/ve8+v2ru989r941+zH7Be/6Ss1Q9Yp18j792h3rnTYMC6/ErX5PMOzQBa+D04/Av/wr/wL/wL/8K//83fqXr/L7j0xN//rff3y1NcZo7vJ/r+fq3O8V2K28e6lNQ1Zu3i8IJL5y4gtrnDsP6qy/8d9wAe7VZdm238XuIvdp2rawwntLSkSY5tPdUYkWlk1lOVir+Od40eP7LAZgd3oITnMFYebeau55OuK3AluPkpVVvzbq1x51q2Ne5qRz/0/r3GbsJbuo9Arn73mIErJ54HNd/sm8XKHNzcuVKcrhDrDhMk31SXM2I/WWQiRIYdhVVmjE2mO6Wl6yslnVeR3jLcsmrYfQ+0Q5ph21M/ML0HInUumaZ3oaY3c23o9FJbK02v6HLGAc7pNTJ9Sa+Ws0nvCtxK3NU1nGbvmv0FUWaehvxa4vbz54hTmmXJfhEbUGfp3vv2NJn7Q/VTq7z+3Sl+TBGT32NaJjKXC9nUdQ7xY0vt4nxPLPNzg+On5aL681lxHCsyQxqrnYB5OmfayDQUnYn4u4t/K6mqbbc9YF1GZDKNzkLmvzWwy+RKeyJ2BVSGFDWzcgeZvQ1FprCUe5CTmTy8TuRa2e0KoOtvmyMZ/b8k+vR1Dac5xw6R72LOkRZwjjytu4+3kHVkF9vtKMwRuUXeOePUyarXQVOetjpIHnNM8ljXmxsbB1xWbQL7jkmeJet6MvKIY748aqJryki7Hte0B9SfHrovQInWnwLcc8Qt7oaK6g9Vh/WKRS7H+qP6Ga40LeeoOGMjxqwRbCMyM1ytyUHNU9VrKDptbHZitP5oeIFlaV3qxhdy95QuLMqStYV+a5D3S5lJhM35J4l+G7OGhDJjbL/q+y0EllseJG1+dlCKYBufHRSzPukLkdO4BpRDqtoPGKPlMAT3Atfa7FgOpRRDDoUqBeFUDqo/0Nxvf/Q8r9HT9tUrw5U=
*/