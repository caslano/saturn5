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
gmpoh+Af6COkQy10wgkI1DCukAnzoRjqoRuittG3bcjbhixoh8iXmSOYDXlQDs0QeAU5kAbFUAmtEFaLDJgKOVAGjdAFk7bTH8iCEqiCXdAJgVdZRzAO0iAX1kA9dEAfJL2GPKiDRuiBYB3jBbOhFMqhFk5AxA7kQQrMh+IdyNzBEEDTDvq7A9kQ9kf6C0VQAdXQCO3QA5E7aQPyoBSqoBk6Iboe+ZAGuVBcj/x6ZNcjG/ogqYExbUB+A+PaQBsNtNFAGw3Ib0D2nxgXyII8KIdd0AnRr/MMMB+KoRI6IGoX6xQyoAzqoAXaIbibdQ+TIB0KoRTKoWo3sqEZ2qATTkDCn3kOmA8FsAY2QA10QDeE/YU2IQOKoAIaoQdGNbJOYDYUQjnUQnPj2cQicwHj9tDGHuTvQT7U72GcIOoNxgjmQg7kQxlUQyN0wag3GSfIghKogmbohOgm5MJ8KIYaaIIOiNuLbMjYi3wo2ovcvciFdgj+FbkwGWZDIZRCMwTeQjZkwnzIhQ1QD63QDVHNjAnEQRLkQxlUQDU0QheM2kcbkAXlsAui/8aYwHwogEqogXqI+jsyYSrMhVVQAXXQCF0Q2YJMmA0lUArNLWcT88iGFMjcj2wo3o/8/cjfz7jsZ11C2D/oO8TBVMiAHMiHVVANXdADwbdpD8bDZEiHQiiHtrfPJW2iYRykQCYUQw3UQwd0Q9gBxukAz3SAtg7Q1gHaOsCzHeC5DtDeAdr5J+MFk2AyZEEpVMEuCLxDO5ACuVAJrdAHYW08E2RAEayCaqiDHog8iExIh8KDyDvImB3kGaDzIHsBAv9ivcI4SIBcKIAm6IOoQzwDZEDOIdqBikO0AV0QbGecYDbkQQmUttNO+9kkLeMEKZB5GLmHGSOoP8wzHGacDtMGhP2beYEMmAs5UAGN0A5dEPwP7UA65EEhlEMtNEMnRHfQFqRBJhRDDTRBN4S9y3hBHGRADqyC6ndpC1qgC0a9x3xAFuRBCZRCM7RBJyT8lzZgDdRAN8R1MlYwF4qgAtph1BHm4QiyjiAHyiHwPv2FBMiEXNgATdANUR/QV0iCHMiHOmiHYBdzC+NhEqRDFhRCCZRCFeyCTjgBEUdpC9KO0hYUH6XfRxn/o7TxIfJhFZRBI3RB8BjyYTZkQekxZEJEN+MMuVAMa6ASOqAbxhxHJkw9jtzjjO9xZB5HJkR+hEzIgjwoh1pohjbohHEf008ogA1QCa3QAVEnkAtzoQhWQQV0QQ+MOol8SD+JfCg5ifyTyD7JOEDEJ4w7zP8EuVDzCXKhG/og6hTyIQOKoALaoQcie5ALWT3Ig06I6EUepPUyHr30F+p7kdeLvF7kfcp4wFTIgSKogEbogeBp+gyTIB3yoASqYBd0QkQfbUAa5MIaqIEm6ICoftqAOEiCnH7agbJ+2oEeGH+GNiALSqAcaqENogeQPYBcaIKoQEggDuZCDhTBKqiGOmiEduiBYEhIYDLMhhKogl3QCYHzQgLRkABpkAnFsAFqoBX6IOr8kEDG+bQH+VBxPm1BC7RDD0QGQwKjYFKQtiALSoO0BW1wIkhboSGBlFDagVxYA5WhtAX1obRzQUhgDGRA2QW0AXXQAsEhyB+CbMgbgmwoH4J86ByCfIgIow1ICKOdMNoJQ34Y8qEpjOcJQ354SGBqOM8SzriF8yzhjBe0hyN/KPKHIh+qoBbahiIbAsOQC5lQPAy5UA/dEBaBPMiPYB4i6HsEcqElgvEYHhJIh6zhyIUSqIJm6IToC0MC86EA1kAN1EMrjPkcfYW5sArKoAXaYXwk8wqzoRSqIpEJgREhgXEjkDkCWSPoH0R9nvUCc6EMKqAdeiDyIvo=
*/