/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_INVOCABLE_HPP
#define BOOST_CLBL_TRTS_IS_INVOCABLE_HPP

#include <boost/callable_traits/detail/core.hpp>
#include <boost/callable_traits/detail/is_invocable_impl.hpp>

namespace boost { namespace callable_traits {

//[ is_invocable_hpp
/*`[section:ref_is_invocable is_invocable]
[heading Header]
``#include <boost/callable_traits/is_invocable.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T, typename... Args>
struct is_invocable;

// inherits from either std::true_type or std::false_type
template<typename Ret, typename T, typename... Args>
struct is_invocable_r;

//<-
template<typename T, typename... Args>
struct is_invocable : detail::is_invocable_impl<T, Args...>::type {
    using type = typename detail::is_invocable_impl<T, Args...>::type;
};

template<typename Ret, typename T, typename... Args>
struct is_invocable_r
  : detail::is_invocable_r_impl<
        typename detail::is_invocable_impl<T, Args...>::type, Ret, T, Args...>::type
{
    using type = typename detail::is_invocable_r_impl<
        typename detail::is_invocable_impl<T, Args...>::type, Ret, T, Args...>::type;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T, typename... Args>
struct is_invocable_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

template<typename Ret, typename T, typename... Args>
struct is_invocable_r_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T, typename... Args>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_invocable_v = //see below
//<-
    detail::is_invocable_impl<detail::traits<T>, Args...>::type::value;
//->

// only available when variable templates are supported
template<typename Ret, typename T, typename... Args>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_invocable_r_v = //see below
//<-
    detail::is_invocable_r_impl<
        typename detail::is_invocable_impl<T, Args...>::type,
        Ret, T, Args...>::type::value;
#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* standalone c++11 implementation of c++17 `std::is_invocable`, `std::is_invocable_r`
[note ref-qualified overloads of `operator()` with different signatures are not handled correctly yet.]

[heading Example Program]
[import ../example/is_invocable.cpp]
[is_invocable]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_INVOCABLE_HPP

/* is_invocable.hpp
+tppVcYFEmdCtWV8U+K0o4ytzDJOkbBlrmnqPssyDg727Mck9ZBlGW+XOCdVW8bEEE8Zh6m3Lct4ekjVMtaVsIuq9eOn8vuLXLnV+HFESM1l3BJSsx9bhFYt410hHj8WqPWWZbwgpNKPj1qWcVctylgQ6injAPWRZRkfD1DG0aE1+7FzaM1+XCZxTnT1UN9YljEyTO5FQaequyzLOCGsahm/k7wXuyarRyzL+FJozX7sIXn/6Dpavel035NUDfekluY9yes6r22J5j3J+9qu1z8NcF+K9lkXx7yG+64V20iJbOYBIA4+DAdzT1oa4XtPSiPbybkFNd77Pek6qEo/PiTbq0JyXCnO/c8DRVmnsUSr131Jp3vQqFP5np6+vqabtnjze8L3yvaN9fzvJdH6W7XboqReBjvUCUa+8Zmr8ji/31S+NeRopIIcld/EPSnaHTaO57D6qq3+xm6ThjIHyRWjljicTocajp6PvoTGu8LUUcSLloPmjrcyjGs2X6wNV5vgFYZDveHoqB53NlQfOidTgxzqPjQmqMJoF/KS+pwrfFtSTA+rzzHV94cYdz6lzifVQ8bljrqqvZM42n9hcW7bbqM+K+UWMlPmAXW4amGEqdO5P62W7/9SZmL0aC71vMr9r5/2ydwG4t86YSrHKDRKjd2OOircmW+c46qnrnG9ZZwefIZyhDRUbUO+MWLCIlX3sCFqaVi00Vz77rzG7vRXcI44yPMTZxf2aaArSSVrPwY3ctsTuTcPVSdSiqmMPq1RVxsjHU41yzHJ+WnQ4SoheIHxdMgQ83vD3eU4DTXYlntgboych6q5/ib0VsmzmD11qn54uALGG/VUb31uNYwWe0gI9TldFRov4o8dxhHOZkFOdVRQC3V50Cx1WLBTjUTPCL6O665TxerrQh/J+9PQUNWCfYgNPSe0vuqJbTq23VK/zglzP2dcT70og6nGaONHp1M1dKU7i0PaqX2c+y05t8ej/vf91trncVKPXsQnRY5zHBcYXVwvqN9cy4zrghMdsdqvz8s+dAmpp75zNQz6zogM4dhrn34kZSyT/eutioz17N92o7erS/A449KQMMI8fqqQ39ka2kI1YUXlN1R7fDTPeEdl4ftljpHOPUHt1KTgVUbD0CB1QuhgdSNlb619+Jj8RkRIKL5to25Sr/BF16ONcHWJMT6og/bVRjn2X7liKEeuet6R7jyOq2KUqusaogpc4Wotz3bRur42l/x+ctZVrfDdGGcXwmcQHifnyoXi0/vx6WaonBwv50nO3SHhVPRwNQhfBno+ioRTpf7egi/PDO2pfRcuvzWSPKeoUo7sDbRitqpxRi+HQ+U5liiHM5Fzd4XjqyAHFTTcGa39ep/4fCF7nEi9cqgO+rw/Serfo0HRaqXzRc7BnehV7Nu7LtKTx3i0sq62l7o70IjSx+DBxlKXsVPHtG8zpHxZjsPwxSD1ltHOsb/+3SG2HhypnmoVfq1j1Dd9GC/XqU2qEXklocmE5xO+Wepl5zpuH16HD9fCCcZgY5BruPOSkGiVjA9PxYc/4RH/++Fhupxzpdycob73QvM736+IneOgyzlRtqf6xE/yyq+/2Hv62JO91nlbJfabLcvTQo7rBMvyzBG7wyxPkGwXWZbngxrKM1zSr7Esz6tiP9myPJ3kXAsyy1Mm8WdblufCBtWX5wexj6hSHvNZTX5viutF9ZvDqkyfSBynWabJsj3XskwpYp9VpUyVdflOsT/jPEad5AyUh4yXS/2dpqzsZ4g92tJ+qdjTLO3bPOdHQHsUbCzn8EmW9pnabpV/mdh7WabfJfaRlum7yfmeYmmfJvaBlvY1+noRyN4Ahsq1aJTerrw=
*/