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
#include <boost/mpl/greater_equal.hpp>


namespace boost {
namespace math {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code, only triggered in release mode and /W4
#endif

namespace detail {


template <int N, int M = N%2>
struct positive_power
{
    template <typename T>
    static T result(T base)
    {
        T power = positive_power<N/2>::result(base);
        return power * power;
    }
};

template <int N>
struct positive_power<N, 1>
{
    template <typename T>
    static T result(T base)
    {
        T power = positive_power<N/2>::result(base);
        return base * power * power;
    }
};

template <>
struct positive_power<1, 1>
{
    template <typename T>
    static T result(T base){ return base; }
};


template <int N, bool>
struct power_if_positive
{
    template <typename T, class Policy>
    static T result(T base, const Policy&)
    { return positive_power<N>::result(base); }
};

template <int N>
struct power_if_positive<N, false>
{
    template <typename T, class Policy>
    static T result(T base, const Policy& policy)
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
    static T result(T base, const Policy& policy)
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
    typedef typename mpl::greater_equal<
                         boost::integral_constant<int, N>,
                         boost::integral_constant<int, 0>
                     >::type is_positive;

    typedef power_if_positive<N, is_positive::value> type;
};


}  // namespace detail


template <int N, typename T, class Policy>
inline typename tools::promote_args<T>::type pow(T base, const Policy& policy)
{ 
   typedef typename tools::promote_args<T>::type result_type;
   return detail::select_power_if_positive<N>::type::result(static_cast<result_type>(base), policy); 
}


template <int N, typename T>
inline typename tools::promote_args<T>::type pow(T base)
{ return pow<N>(base, policies::policy<>()); }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}  // namespace math
}  // namespace boost


#endif

/* pow.hpp
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
*/