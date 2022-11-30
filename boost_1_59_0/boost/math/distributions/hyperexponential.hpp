//  Copyright 2014 Marco Guazzone (marco.guazzone@gmail.com)
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This module implements the Hyper-Exponential distribution.
//
// References:
// - "Queueing Theory in Manufacturing Systems Analysis and Design" by H.T. Papadopolous, C. Heavey and J. Browne (Chapman & Hall/CRC, 1993)
// - http://reference.wolfram.com/language/ref/HyperexponentialDistribution.html
// - http://en.wikipedia.org/wiki/Hyperexponential_distribution
//

#ifndef BOOST_MATH_DISTRIBUTIONS_HYPEREXPONENTIAL_HPP
#define BOOST_MATH_DISTRIBUTIONS_HYPEREXPONENTIAL_HPP

#include <boost/math/tools/cxx03_warn.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/exponential.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/tools/is_detected.hpp>
#include <cstddef>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>
#include <type_traits>
#include <initializer_list>


#ifdef _MSC_VER
# pragma warning (push)
# pragma warning(disable:4127) // conditional expression is constant
# pragma warning(disable:4389) // '==' : signed/unsigned mismatch in test_tools
#endif // _MSC_VER

namespace boost { namespace math {

namespace detail {

template <typename Dist>
typename Dist::value_type generic_quantile(const Dist& dist, const typename Dist::value_type& p, const typename Dist::value_type& guess, bool comp, const char* function);

} // Namespace detail


template <typename RealT, typename PolicyT>
class hyperexponential_distribution;


namespace /*<unnamed>*/ { namespace hyperexp_detail {

template <typename T>
void normalize(std::vector<T>& v)
{
   if(!v.size())
      return;  // Our error handlers will get this later
    const T sum = std::accumulate(v.begin(), v.end(), static_cast<T>(0));
    T final_sum = 0;
    const typename std::vector<T>::iterator end = --v.end();
    for (typename std::vector<T>::iterator it = v.begin();
         it != end;
         ++it)
    {
        *it /= sum;
        final_sum += *it;
    }
    *end = 1 - final_sum;  // avoids round off errors, ensures the probs really do sum to 1.
}

template <typename RealT, typename PolicyT>
bool check_probabilities(char const* function, std::vector<RealT> const& probabilities, RealT* presult, PolicyT const& pol)
{
    BOOST_MATH_STD_USING
    const std::size_t n = probabilities.size();
    RealT sum = 0;
    for (std::size_t i = 0; i < n; ++i)
    {
        if (probabilities[i] < 0
            || probabilities[i] > 1
            || !(boost::math::isfinite)(probabilities[i]))
        {
            *presult = policies::raise_domain_error<RealT>(function,
                                                           "The elements of parameter \"probabilities\" must be >= 0 and <= 1, but at least one of them was: %1%.",
                                                           probabilities[i],
                                                           pol);
            return false;
        }
        sum += probabilities[i];
    }

    //
    // We try to keep phase probabilities correctly normalized in the distribution constructors,
    // however in practice we have to allow for a very slight divergence from a sum of exactly 1:
    //
    if (fabs(sum - 1) > tools::epsilon<RealT>() * 2)
    {
        *presult = policies::raise_domain_error<RealT>(function,
                                                       "The elements of parameter \"probabilities\" must sum to 1, but their sum is: %1%.",
                                                       sum,
                                                       pol);
        return false;
    }

    return true;
}

template <typename RealT, typename PolicyT>
bool check_rates(char const* function, std::vector<RealT> const& rates, RealT* presult, PolicyT const& pol)
{
    const std::size_t n = rates.size();
    for (std::size_t i = 0; i < n; ++i)
    {
        if (rates[i] <= 0
            || !(boost::math::isfinite)(rates[i]))
        {
            *presult = policies::raise_domain_error<RealT>(function,
                                                           "The elements of parameter \"rates\" must be > 0, but at least one of them is: %1%.",
                                                           rates[i],
                                                           pol);
            return false;
        }
    }
    return true;
}

template <typename RealT, typename PolicyT>
bool check_dist(char const* function, std::vector<RealT> const& probabilities, std::vector<RealT> const& rates, RealT* presult, PolicyT const& pol)
{
    BOOST_MATH_STD_USING
    if (probabilities.size() != rates.size())
    {
        *presult = policies::raise_domain_error<RealT>(function,
                                                       "The parameters \"probabilities\" and \"rates\" must have the same length, but their size differ by: %1%.",
                                                       fabs(static_cast<RealT>(probabilities.size())-static_cast<RealT>(rates.size())),
                                                       pol);
        return false;
    }

    return check_probabilities(function, probabilities, presult, pol)
           && check_rates(function, rates, presult, pol);
}

template <typename RealT, typename PolicyT>
bool check_x(char const* function, RealT x, RealT* presult, PolicyT const& pol)
{
    if (x < 0 || (boost::math::isnan)(x))
    {
        *presult = policies::raise_domain_error<RealT>(function, "The random variable must be >= 0, but is: %1%.", x, pol);
        return false;
    }
    return true;
}

template <typename RealT, typename PolicyT>
bool check_probability(char const* function, RealT p, RealT* presult, PolicyT const& pol)
{
    if (p < 0 || p > 1 || (boost::math::isnan)(p))
    {
        *presult = policies::raise_domain_error<RealT>(function, "The probability be >= 0 and <= 1, but is: %1%.", p, pol);
        return false;
    }
    return true;
}

template <typename RealT, typename PolicyT>
RealT quantile_impl(hyperexponential_distribution<RealT, PolicyT> const& dist, RealT const& p, bool comp)
{
    // Don't have a closed form so try to numerically solve the inverse CDF...

    typedef typename policies::evaluation<RealT, PolicyT>::type value_type;
    typedef typename policies::normalise<PolicyT,
                                         policies::promote_float<false>,
                                         policies::promote_double<false>,
                                         policies::discrete_quantile<>,
                                         policies::assert_undefined<> >::type forwarding_policy;

    static const char* function = comp ? "boost::math::quantile(const boost::math::complemented2_type<boost::math::hyperexponential_distribution<%1%>, %1%>&)"
                                       : "boost::math::quantile(const boost::math::hyperexponential_distribution<%1%>&, %1%)";

    RealT result = 0;

    if (!check_probability(function, p, &result, PolicyT()))
    {
        return result;
    }

    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    // A possible (but inaccurate) approximation is given below, where the
    // quantile is given by the weighted sum of exponential quantiles:
    RealT guess = 0;
    if (comp)
    {
        for (std::size_t i = 0; i < n; ++i)
        {
            const exponential_distribution<RealT,PolicyT> exp(rates[i]);

            guess += probs[i]*quantile(complement(exp, p));
        }
    }
    else
    {
        for (std::size_t i = 0; i < n; ++i)
        {
            const exponential_distribution<RealT,PolicyT> exp(rates[i]);

            guess += probs[i]*quantile(exp, p);
        }
    }

    // Fast return in case the Hyper-Exponential is essentially an Exponential
    if (n == 1)
    {
        return guess;
    }

    value_type q;
    q = detail::generic_quantile(hyperexponential_distribution<RealT,forwarding_policy>(probs, rates),
                                 p,
                                 guess,
                                 comp,
                                 function);

    result = policies::checked_narrowing_cast<RealT,forwarding_policy>(q, function);

    return result;
}

}} // Namespace <unnamed>::hyperexp_detail


template <typename RealT = double, typename PolicyT = policies::policy<> >
class hyperexponential_distribution
{
    public: typedef RealT value_type;
    public: typedef PolicyT policy_type;


    public: hyperexponential_distribution()
    : probs_(1, 1),
      rates_(1, 1)
    {
        RealT err;
        hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
                                    probs_,
                                    rates_,
                                    &err,
                                    PolicyT());
    }

    // Four arg constructor: no ambiguity here, the arguments must be two pairs of iterators:
    public: template <typename ProbIterT, typename RateIterT>
            hyperexponential_distribution(ProbIterT prob_first, ProbIterT prob_last,
                                          RateIterT rate_first, RateIterT rate_last)
    : probs_(prob_first, prob_last),
      rates_(rate_first, rate_last)
    {
        hyperexp_detail::normalize(probs_);
        RealT err;
        hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
                                    probs_,
                                    rates_,
                                    &err,
                                    PolicyT());
    }
    private: template <typename T, typename = void>
             struct is_iterator
             {
                 static constexpr bool value = false;
             };

             template <typename T>
             struct is_iterator<T, boost::math::tools::void_t<typename std::iterator_traits<T>::difference_type>>
             {
                 // std::iterator_traits<T>::difference_type returns void for invalid types
                 static constexpr bool value = !std::is_same<typename std::iterator_traits<T>::difference_type, void>::value;
             };

    // Two arg constructor from 2 ranges, we SFINAE this out of existence if
    // either argument type is incrementable as in that case the type is
    // probably an iterator:
    public: template <typename ProbRangeT, typename RateRangeT, 
                      typename std::enable_if<!is_iterator<ProbRangeT>::value && 
                                              !is_iterator<RateRangeT>::value, bool>::type = true>
            hyperexponential_distribution(ProbRangeT const& prob_range,
                                          RateRangeT const& rate_range)
    : probs_(std::begin(prob_range), std::end(prob_range)),
      rates_(std::begin(rate_range), std::end(rate_range))
    {
        hyperexp_detail::normalize(probs_);

        RealT err;
        hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
                                    probs_,
                                    rates_,
                                    &err,
                                    PolicyT());
    }

    // Two arg constructor for a pair of iterators: we SFINAE this out of
    // existence if neither argument types are incrementable.
    // Note that we allow different argument types here to allow for
    // construction from an array plus a pointer into that array.
    public: template <typename RateIterT, typename RateIterT2, 
                      typename std::enable_if<is_iterator<RateIterT>::value || 
                                              is_iterator<RateIterT2>::value, bool>::type = true>
            hyperexponential_distribution(RateIterT const& rate_first, 
                                          RateIterT2 const& rate_last)
    : probs_(std::distance(rate_first, rate_last), 1), // will be normalized below
      rates_(rate_first, rate_last)
    {
        hyperexp_detail::normalize(probs_);

        RealT err;
        hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
                                    probs_,
                                    rates_,
                                    &err,
                                    PolicyT());
    }

      // Initializer list constructor: allows for construction from array literals:
public: hyperexponential_distribution(std::initializer_list<RealT> l1, std::initializer_list<RealT> l2)
      : probs_(l1.begin(), l1.end()),
        rates_(l2.begin(), l2.end())
      {
         hyperexp_detail::normalize(probs_);

         RealT err;
         hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
            probs_,
            rates_,
            &err,
            PolicyT());
      }

public: hyperexponential_distribution(std::initializer_list<RealT> l1)
      : probs_(l1.size(), 1),
        rates_(l1.begin(), l1.end())
      {
         hyperexp_detail::normalize(probs_);

         RealT err;
         hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
            probs_,
            rates_,
            &err,
            PolicyT());
      }

    // Single argument constructor: argument must be a range.
    public: template <typename RateRangeT>
    hyperexponential_distribution(RateRangeT const& rate_range)
    : probs_(std::distance(std::begin(rate_range), std::end(rate_range)), 1), // will be normalized below
      rates_(std::begin(rate_range), std::end(rate_range))
    {
        hyperexp_detail::normalize(probs_);

        RealT err;
        hyperexp_detail::check_dist("boost::math::hyperexponential_distribution<%1%>::hyperexponential_distribution",
                                    probs_,
                                    rates_,
                                    &err,
                                    PolicyT());
    }

    public: std::vector<RealT> probabilities() const
    {
        return probs_;
    }

    public: std::vector<RealT> rates() const
    {
        return rates_;
    }

    public: std::size_t num_phases() const
    {
        return rates_.size();
    }


    private: std::vector<RealT> probs_;
    private: std::vector<RealT> rates_;
}; // class hyperexponential_distribution


// Convenient type synonym for double.
typedef hyperexponential_distribution<double> hyperexponential;


// Range of permissible values for random variable x
template <typename RealT, typename PolicyT>
std::pair<RealT,RealT> range(hyperexponential_distribution<RealT,PolicyT> const&)
{
    if (std::numeric_limits<RealT>::has_infinity)
    {
        return std::make_pair(static_cast<RealT>(0), std::numeric_limits<RealT>::infinity()); // 0 to +inf.
    }

    return std::make_pair(static_cast<RealT>(0), tools::max_value<RealT>()); // 0 to +<max value>
}

// Range of supported values for random variable x.
// This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
template <typename RealT, typename PolicyT>
std::pair<RealT,RealT> support(hyperexponential_distribution<RealT,PolicyT> const&)
{
    return std::make_pair(tools::min_value<RealT>(), tools::max_value<RealT>()); // <min value> to +<max value>.
}

template <typename RealT, typename PolicyT>
RealT pdf(hyperexponential_distribution<RealT, PolicyT> const& dist, RealT const& x)
{
    BOOST_MATH_STD_USING
    RealT result = 0;

    if (!hyperexp_detail::check_x("boost::math::pdf(const boost::math::hyperexponential_distribution<%1%>&, %1%)", x, &result, PolicyT()))
    {
        return result;
    }

    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    for (std::size_t i = 0; i < n; ++i)
    {
        const exponential_distribution<RealT,PolicyT> exp(rates[i]);

        result += probs[i]*pdf(exp, x);
        //result += probs[i]*rates[i]*exp(-rates[i]*x);
    }

    return result;
}

template <typename RealT, typename PolicyT>
RealT cdf(hyperexponential_distribution<RealT, PolicyT> const& dist, RealT const& x)
{
    RealT result = 0;

    if (!hyperexp_detail::check_x("boost::math::cdf(const boost::math::hyperexponential_distribution<%1%>&, %1%)", x, &result, PolicyT()))
    {
        return result;
    }

    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    for (std::size_t i = 0; i < n; ++i)
    {
        const exponential_distribution<RealT,PolicyT> exp(rates[i]);

        result += probs[i]*cdf(exp, x);
    }

    return result;
}

template <typename RealT, typename PolicyT>
RealT quantile(hyperexponential_distribution<RealT, PolicyT> const& dist, RealT const& p)
{
    return hyperexp_detail::quantile_impl(dist, p , false);
}

template <typename RealT, typename PolicyT>
RealT cdf(complemented2_type<hyperexponential_distribution<RealT,PolicyT>, RealT> const& c)
{
    RealT const& x = c.param;
    hyperexponential_distribution<RealT,PolicyT> const& dist = c.dist;

    RealT result = 0;

    if (!hyperexp_detail::check_x("boost::math::cdf(boost::math::complemented2_type<const boost::math::hyperexponential_distribution<%1%>&, %1%>)", x, &result, PolicyT()))
    {
        return result;
    }

    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    for (std::size_t i = 0; i < n; ++i)
    {
        const exponential_distribution<RealT,PolicyT> exp(rates[i]);

        result += probs[i]*cdf(complement(exp, x));
    }

    return result;
}


template <typename RealT, typename PolicyT>
RealT quantile(complemented2_type<hyperexponential_distribution<RealT, PolicyT>, RealT> const& c)
{
    RealT const& p = c.param;
    hyperexponential_distribution<RealT,PolicyT> const& dist = c.dist;

    return hyperexp_detail::quantile_impl(dist, p , true);
}

template <typename RealT, typename PolicyT>
RealT mean(hyperexponential_distribution<RealT, PolicyT> const& dist)
{
    RealT result = 0;

    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    for (std::size_t i = 0; i < n; ++i)
    {
        const exponential_distribution<RealT,PolicyT> exp(rates[i]);

        result += probs[i]*mean(exp);
    }

    return result;
}

template <typename RealT, typename PolicyT>
RealT variance(hyperexponential_distribution<RealT, PolicyT> const& dist)
{
    RealT result = 0;

    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    for (std::size_t i = 0; i < n; ++i)
    {
        result += probs[i]/(rates[i]*rates[i]);
    }

    const RealT mean = boost::math::mean(dist);

    result = 2*result-mean*mean;

    return result;
}

template <typename RealT, typename PolicyT>
RealT skewness(hyperexponential_distribution<RealT,PolicyT> const& dist)
{
    BOOST_MATH_STD_USING
    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    RealT s1 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i}
    RealT s2 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i^2}
    RealT s3 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i^3}
    for (std::size_t i = 0; i < n; ++i)
    {
        const RealT p = probs[i];
        const RealT r = rates[i];
        const RealT r2 = r*r;
        const RealT r3 = r2*r;

        s1 += p/r;
        s2 += p/r2;
        s3 += p/r3;
    }

    const RealT s1s1 = s1*s1;

    const RealT num = (6*s3 - (3*(2*s2 - s1s1) + s1s1)*s1);
    const RealT den = (2*s2 - s1s1);

    return num / pow(den, static_cast<RealT>(1.5));
}

template <typename RealT, typename PolicyT>
RealT kurtosis(hyperexponential_distribution<RealT,PolicyT> const& dist)
{
    const std::size_t n = dist.num_phases();
    const std::vector<RealT> probs = dist.probabilities();
    const std::vector<RealT> rates = dist.rates();

    RealT s1 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i}
    RealT s2 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i^2}
    RealT s3 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i^3}
    RealT s4 = 0; // \sum_{i=1}^n \frac{p_i}{\lambda_i^4}
    for (std::size_t i = 0; i < n; ++i)
    {
        const RealT p = probs[i];
        const RealT r = rates[i];
        const RealT r2 = r*r;
        const RealT r3 = r2*r;
        const RealT r4 = r3*r;

        s1 += p/r;
        s2 += p/r2;
        s3 += p/r3;
        s4 += p/r4;
    }

    const RealT s1s1 = s1*s1;

    const RealT num = (24*s4 - 24*s3*s1 + 3*(2*(2*s2 - s1s1) + s1s1)*s1s1);
    const RealT den = (2*s2 - s1s1);

    return num/(den*den);
}

template <typename RealT, typename PolicyT>
RealT kurtosis_excess(hyperexponential_distribution<RealT,PolicyT> const& dist)
{
    return kurtosis(dist) - 3;
}

template <typename RealT, typename PolicyT>
RealT mode(hyperexponential_distribution<RealT,PolicyT> const& /*dist*/)
{
    return 0;
}

}} // namespace boost::math

#ifdef _MSC_VER
#pragma warning (pop)
#endif
// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>
#include <boost/math/distributions/detail/generic_quantile.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_HYPEREXPONENTIAL

/* hyperexponential.hpp
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
*/