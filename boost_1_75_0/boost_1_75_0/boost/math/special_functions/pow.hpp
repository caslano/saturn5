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
ljW6e6/rC1MbkhaAL7eoEHaZ+Qx0IuWqj1qllBZR0MXzjKAvklP3UFtSVaku+Hb3F6He76eoCShzOA+4PZ5BLVxmL+8qlrrtL7WOaDCEcG0G2uatEWp39sLQRdzxdLRxeLdjMEKl0qOVyyC3h7u8kUG0oeRHFrmkU+DM5Ar764rJgusT0QH/NPZDlltv+1dd/0PwjHk4rEv38XQeV5GJNn30pS46kq2n/EPcoQLgPpkG6fUpMlNMvvjRRHWDV/soT2ZZ3/xbzPjjpba8Gx0GeYaKwLea9xtCIf9mpe3zyZfPsDg9O4NpLwFukzfLaPjVzxZhfDzwn63CP0AFdaOPjhxI258B+f3pebDDol7Vi8DrO14A+/2EvW/Q55EJiMc5ARP5+iVhn4/pvOFiyOlf/hIKbdTmC/q49I5tuTfKBnaEjzGYv6uk/S0GI5cL/v7dFN886yIn+OJ0R66z+yJR+PtxVmSutfsjanxXcDDqC/Q1uXlTuOD/x3pQsbXNu5Fna4hGw771g1Ev/ChI303pLrDsfZWmR91U2GxezJ1cLpx5w96gQqt5eN3GSJSW7aUs7AuGN7M07A/MtDjTmhqc6+h8n8XZwFtL4xcQ17iq1W5r6mjrpDY70liftozchTQa3UZtNQfih0oxlv3OxuNtzY7mdgfGMlkm33JBFdIcKzq6nE2rnA4lLctyWTHSYMvrcVvHENfW6mhCHPYF
*/