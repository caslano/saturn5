/*
@file remove_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(remove_noexcept)
BOOST_CLBL_TRTS_SFINAE_MSG(remove_noexcept, cannot_remove_noexcept_from_this_type)

//[ remove_noexcept_hpp
/*`
[section:ref_remove_noexcept remove_noexcept]
[heading Header]
``#include <boost/callable_traits/remove_noexcept.hpp>``
[heading Definition]
*/

template<typename T>
using remove_noexcept_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_noexcept,
        cannot_remove_noexcept_from_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_noexcept_impl {};

    template<typename T>
    struct remove_noexcept_impl <T, typename std::is_same<
        remove_noexcept_t<T>, detail::dummy>::type>
    {
        using type = remove_noexcept_t<T>;
    };
}

//->

template<typename T>
struct remove_noexcept : detail::remove_noexcept_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`

[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the `noexcept` specifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_noexcept_t<T>`]]
    [[`int() const noexcept`]           [`int() const`]]
    [[`int(*)() noexcept`]              [`int(*)()`]]
    [[`int(&)() noexcept`]              [`int(&)()`]]
    [[`int(foo::*)() noexcept`]         [`int(foo::*)()`]]
    [[`int() const`]                    [`int() const`]]
    [[`int(*)()`]                       [`int(*)()`]]
    [[`int(&)()`]                       [`int(&)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_noexcept.cpp]
[remove_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_NOEXCEPT_HPP

/* remove_noexcept.hpp
7Y/uUMaHfQaW5+5q4+MZ3SuwDabAZ2EL+ALsCV/S83oZjoA74Gj4KlwEd8GL4V/hZfANuAq+C1fDvfAe+B7cAqmz6Mg/0G8if6T13g97wy9gNjwIJ8FDcBo8DOfDr+DF8Bt4CfwWXqb5roTfwxvgD/Bm6OF4t8MYeDeMhethPPwzTIBPwVpwG3yRfM/Co/T6yrLPZzi5voK/Of07/UbTWbANXKp7ZZbBMfB8OAUuhzPgBbAIXqztdSm8FV6u7fQH+CC8Gj4Or4HPw1XwdbgF7oPXw8/gzbCDfmupO7wd9tdwFrwTzoR3w9lwDSyAa6F8fxMug+vhpXAjfAA+BJ+Bj2h7bII74GNwJ3wcvgk3w33wSfgJfAp+Ac+FB+EWa/tG7/f1OSA7xPbNKNq7ATwepsIT4Eh4MhwDJ8NsDU/W8AF4l9H7a9hIx3eyfLPK77oilwIzYXPYDWbAHnAgHAYHw+FwPOwFK2AfuBr2hethf/gEHAC3wYHwb/BY+K7KfaD5PtFyqZSU2wAS1nbQ+0G4JEw7tEQuHbaBPWBHeBxsC0+C7eBM2B6epunyu2PvqRizvnDI786tutfiNtgY3g5T4FrYFN4JO8O7YKbG94JrYB8ND9AwezSOaG9oJvEXnFX7/3qfxm9xj8YN9MlG/Av4ffjv8I3Orm0y8aPweWdH92hEXdRF3a/jfi39//z8/17/72Vt8Wmx626Mx0ih5QaXRvwzvvgPbHxOyZw52HovNxmk1UvkN//T0LQc/8tSuHSVudIlg5XmisLSokIOa8tYFTY9RxY+AmXcIDJzCsswO+CXLCzOy6+UfQonuGwX7PQYcafi6+FPwW/36eLWBNbGRg4ff9zQnNm8ExLQgySJHmT2rCB9nMh77fvtX0r4WA1jUX2tL1zb9b3zXF0DCuRtaL8zflDCQzQcLu8sSSuwx02035HfL+FhGrZ5f0y3FPReR5Ksbeu5Ba0rUd+gd8hmyVp3k7V6z6nvhXXXcINmwe/QDkvQ5/AYv66pPUxHZubaUBsH2l30lduevcu+gebpYHWfF0k4LuYzkxBpnU3ztJU8xeRZ7m+XmIMmzpWnPHeO6z36c0Umw/nENND2DpTTWnROK6VOdu0zz/3eWeo9/v5PpRX64H1lTrT5Rzgep5mUscpdhtrtT9fz/HIdsrR0L85rDK2+xQxGx9/d/d4Y5QW9NxY6Pu167WdS1kxnuuOx+TND8t9lrO0EnNrv1/X9S0UuPuZz46m27+Mk0t+W8s9ywq3NXy9tka7r7DgJD0c/vM2upSdK3Cynluls96wMv9cXlx20fu8V+aoyEnnbIpNc1cvp6bKvMIcpJs/aXxgj5XqsXf7xEh4u594y3uCwD1/utxshzwBybh+7ypvdjT9WR7dC2mao5wB/Kzir0PqLztDW+WonuaqcgvzZ82Tu7K86g2ulrG88ceRKxXfED8CPxU/Dz8Ofib8Yf72py7pCLGNjKufu36fwOX65t8oe9yRO+CT8yfgT8dcQ9yoe4v1xuWrX//dqs3vUj66fxyX529i0LiqR19lEPzHt3mA92VKXXf+A3YULgtaoQ9+X02uPuFV2LZ5rSvOutnFcIxp3l2u+Cn1fe0XIO/tp+AxkS+8LzDeF5VUzTfj9MSJLTvvupu0vO69YGa/b5khOaW55eb59nzXbVVa434+Jkh70zjt9c+R33kP3mHiD3nevqmsa8dnWRnpQ/aQdp1RvR2ub5sN6RtzHMcxpcA88BtnV1dtxTm55hZj5oUHDtafm6WT3G70g4UdjWjKGxzq1fqydNW97ySvrcxJ+IqaNiaHeCRHbP03nr20if6WnHWd3ghNvPnLO074JlN1W5zp2e/0=
*/