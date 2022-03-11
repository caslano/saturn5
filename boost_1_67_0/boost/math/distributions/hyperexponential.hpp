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


#include <boost/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/exponential.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/type_traits/has_pre_increment.hpp>
#include <cstddef>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
# include <initializer_list>
#endif

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

    // Two arg constructor from 2 ranges, we SFINAE this out of existence if
    // either argument type is incrementable as in that case the type is
    // probably an iterator:
    public: template <typename ProbRangeT, typename RateRangeT>
            hyperexponential_distribution(ProbRangeT const& prob_range,
                                          RateRangeT const& rate_range,
                                          typename boost::disable_if_c<boost::has_pre_increment<ProbRangeT>::value || boost::has_pre_increment<RateRangeT>::value>::type* = 0)
    : probs_(boost::begin(prob_range), boost::end(prob_range)),
      rates_(boost::begin(rate_range), boost::end(rate_range))
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
    public: template <typename RateIterT, typename RateIterT2>
            hyperexponential_distribution(RateIterT const& rate_first, 
                                          RateIterT2 const& rate_last, 
                                          typename boost::enable_if_c<boost::has_pre_increment<RateIterT>::value || boost::has_pre_increment<RateIterT2>::value>::type* = 0)
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

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
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
#endif // !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)

    // Single argument constructor: argument must be a range.
    public: template <typename RateRangeT>
    hyperexponential_distribution(RateRangeT const& rate_range)
    : probs_(boost::size(rate_range), 1), // will be normalized below
      rates_(boost::begin(rate_range), boost::end(rate_range))
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

#ifdef BOOST_MSVC
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