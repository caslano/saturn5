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
Fap79dCmbs0wfn0c8DY6uL6gVC1aUOraLxXrGTO0EOtpywwcRZ2H6v++HNmsbxWbbHq3pxPLFJcjyqz3epWsqBjtgikkSuPFr/nwSHnzmEf/OB8od+6XOXRt4pG16QPw8toboD1ovNNNiQOOs41PGC7uKEPhjrjB+/i5UFWb/F90Fg1wEI92TPb9dxIlzs2sHQ+b+iYx6m+qZxMgf2hkYd++umL6UQSgtC66WqRdb/DLHGs99Ndzr4qSULqYqXF7u8+31pLAWG3SpFODR/EJsTma/vfk9H7hs/iHSDnh4L+vOF/DmbL2AvJUC4MR+yKYPqU3xE81SdeQTkJPclIQ9xwc6lmkduix27HJ4zVls8H2m7f/0N/W96ZxmDbqPql2A8eGEadNaYtqrPEjsRSlWNhBWHd7UzXhQmQI1vcl+EvyS8PCpvIc/pSqSB+ywDpI9B/NQUMgtHsn3Doq4LY0c+MVQHGy1FR9quX8tgRMFUgVvdXEnTEZ/gy1+Y1CQoHYBzA3xyROmAAuUA35foi8aQR65JYGbqDWXiLONihhqHra5eXg0wOr905PxA==
*/