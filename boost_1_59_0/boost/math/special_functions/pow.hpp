//   Boost pow.hpp header file
//   Computes a power with exponent known at compile-time

//  (C) Copyright Bruno Lalande 2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


#ifndef BOOST_MATH_POW_HPP
#define BOOST_MATH_POW_HPP


#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/promotion.hpp>


namespace boost {
namespace math {

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code, only triggered in release mode and /W4
#endif

namespace detail {


template <int N, int M = N%2>
struct positive_power
{
    template <typename T>
    static BOOST_CXX14_CONSTEXPR T result(T base)
    {
        T power = positive_power<N/2>::result(base);
        return power * power;
    }
};

template <int N>
struct positive_power<N, 1>
{
    template <typename T>
    static BOOST_CXX14_CONSTEXPR T result(T base)
    {
        T power = positive_power<N/2>::result(base);
        return base * power * power;
    }
};

template <>
struct positive_power<1, 1>
{
    template <typename T>
    static BOOST_CXX14_CONSTEXPR T result(T base){ return base; }
};


template <int N, bool>
struct power_if_positive
{
    template <typename T, class Policy>
    static BOOST_CXX14_CONSTEXPR T result(T base, const Policy&)
    { return positive_power<N>::result(base); }
};

template <int N>
struct power_if_positive<N, false>
{
    template <typename T, class Policy>
    static BOOST_CXX14_CONSTEXPR T result(T base, const Policy& policy)
    {
        if (base == 0)
        {
            return policies::raise_overflow_error<T>(
                       "boost::math::pow(%1%)",
                       "Attempted to compute a negative power of 0",
                       policy
                   );
        }

        return T(1) / positive_power<-N>::result(base);
    }
};

template <>
struct power_if_positive<0, true>
{
    template <typename T, class Policy>
    static BOOST_CXX14_CONSTEXPR T result(T base, const Policy& policy)
    {
        if (base == 0)
        {
            return policies::raise_indeterminate_result_error<T>(
                       "boost::math::pow(%1%)",
                       "The result of pow<0>(%1%) is undetermined",
                       base,
                       T(1),
                       policy
                   );
        }

        return T(1);
    }
};


template <int N>
struct select_power_if_positive
{
    using type = power_if_positive<N, (N >= 0)>;
};


}  // namespace detail


template <int N, typename T, class Policy>
BOOST_CXX14_CONSTEXPR inline typename tools::promote_args<T>::type pow(T base, const Policy& policy)
{ 
   using result_type = typename tools::promote_args<T>::type;
   return detail::select_power_if_positive<N>::type::result(static_cast<result_type>(base), policy); 
}

template <int N, typename T>
BOOST_CXX14_CONSTEXPR inline typename tools::promote_args<T>::type pow(T base)
{ return pow<N>(base, policies::policy<>()); }

#ifdef _MSC_VER
#pragma warning(pop)
#endif

}  // namespace math
}  // namespace boost


#endif

/* pow.hpp
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
*/