// Kolmogorov-Smirnov 1st order asymptotic distribution
// Copyright Evan Miller 2020
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The Kolmogorov-Smirnov test in statistics compares two empirical distributions,
// or an empirical distribution against any theoretical distribution. It makes
// use of a specific distribution which doesn't have a formal name, but which
// is often called the Kolmogorv-Smirnov distribution for lack of anything
// better. This file implements the limiting form of this distribution, first
// identified by Andrey Kolmogorov in
//
// Kolmogorov, A. (1933) "Sulla Determinazione Empirica di una Legge di
// Distribuzione." Giornale dell' Istituto Italiano degli Attuari
//
// This limiting form of the CDF is a first-order Taylor expansion that is
// easily implemented by the fourth Jacobi Theta function (setting z=0). The
// PDF is then implemented here as a derivative of the Theta function. Note
// that this derivative is with respect to x, which enters into \tau, and not
// with respect to the z argument, which is always zero, and so the derivative
// identities in DLMF 20.4 do not apply here.
//
// A higher order order expansion is possible, and was first outlined by
//
// Pelz W, Good IJ (1976). "Approximating the Lower Tail-Areas of the
// Kolmogorov-Smirnov One-sample Statistic." Journal of the Royal Statistical
// Society B.
//
// The terms in this expansion get fairly complicated, and as far as I know the
// Pelz-Good expansion is not used in any statistics software. Someone could
// consider updating this implementation to use the Pelz-Good expansion in the
// future, but the math gets considerably hairier with each additional term.
//
// A formula for an exact version of the Kolmogorov-Smirnov test is laid out in
// Equation 2.4.4 of
//
// Durbin J (1973). "Distribution Theory for Tests Based on the Sample
// Distribution Func- tion." In SIAM CBMS-NSF Regional Conference Series in
// Applied Mathematics. SIAM, Philadelphia, PA.
//
// which is available in book form from Amazon and others. This exact version
// involves taking powers of large matrices. To do that right you need to
// compute eigenvalues and eigenvectors, which are beyond the scope of Boost.
// (Some recent work indicates the exact form can also be computed via FFT, see
// https://cran.r-project.org/web/packages/KSgeneral/KSgeneral.pdf).
//
// Even if the CDF of the exact distribution could be computed using Boost
// libraries (which would be cumbersome), the PDF would present another
// difficulty. Therefore I am limiting this implementation to the asymptotic
// form, even though the exact form has trivial values for certain specific
// values of x and n. For more on trivial values see
//
// Ruben H, Gambino J (1982). "The Exact Distribution of Kolmogorov's Statistic
// Dn for n <= 10." Annals of the Institute of Statistical Mathematics.
// 
// For a good bibliography and overview of the various algorithms, including
// both exact and asymptotic forms, see
// https://www.jstatsoft.org/article/view/v039i11
//
// As for this implementation: the distribution is parameterized by n (number
// of observations) in the spirit of chi-squared's degrees of freedom. It then
// takes a single argument x. In terms of the Kolmogorov-Smirnov statistical
// test, x represents the distribution of D_n, where D_n is the maximum
// difference between the CDFs being compared, that is,
//
//   D_n = sup|F_n(x) - G(x)|
//
// In the exact distribution, x is confined to the support [0, 1], but in this
// limiting approximation, we allow x to exceed unity (similar to how a normal
// approximation always spills over any boundaries).
//
// As mentioned previously, the CDF is implemented using the \tau
// parameterization of the fourth Jacobi Theta function as
//
// CDF=theta_4(0|2*x*x*n/pi)
//
// The PDF is a hand-coded derivative of that function. Actually, there are two
// (independent) derivatives, as separate code paths are used for "small x"
// (2*x*x*n < pi) and "large x", mirroring the separate code paths in the
// Jacobi Theta implementation to achieve fast convergence. Quantiles are
// computed using a Newton-Raphson iteration from an initial guess that I
// arrived at by trial and error.
//
// The mean and variance are implemented using simple closed-form expressions.
// Skewness and kurtosis use slightly more complicated closed-form expressions
// that involve the zeta function. The mode is calculated at run-time by
// maximizing the PDF. If you have an analytical solution for the mode, feel
// free to plop it in.
//
// The CDF and PDF could almost certainly be re-implemented and sped up using a
// polynomial or rational approximation, since the only meaningful argument is
// x * sqrt(n). But that is left as an exercise for the next maintainer.
//
// In the future, the Pelz-Good approximation could be added. I suggest adding
// a second parameter representing the order, e.g.
//
// kolmogorov_smirnov_dist<>(100) // N=100, order=1
// kolmogorov_smirnov_dist<>(100, 1) // N=100, order=1, i.e. Kolmogorov's formula
// kolmogorov_smirnov_dist<>(100, 4) // N=100, order=4, i.e. Pelz-Good formula
//
// The exact distribution could be added to the API with a special order
// parameter (e.g. 0 or infinity), or a separate distribution type altogether
// (e.g. kolmogorov_smirnov_exact_distribution).
//
#ifndef BOOST_MATH_DISTRIBUTIONS_KOLMOGOROV_SMIRNOV_HPP
#define BOOST_MATH_DISTRIBUTIONS_KOLMOGOROV_SMIRNOV_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/special_functions/jacobi_theta.hpp>
#include <boost/math/tools/tuple.hpp>
#include <boost/math/tools/roots.hpp> // Newton-Raphson
#include <boost/math/tools/minima.hpp> // For the mode

namespace boost { namespace math {

namespace detail {
template <class RealType>
inline RealType kolmogorov_smirnov_quantile_guess(RealType p) {
    // Choose a starting point for the Newton-Raphson iteration
    if (p > 0.9)
        return RealType(1.8) - 5 * (1 - p);
    if (p < 0.3)
        return p + RealType(0.45);
    return p + RealType(0.3);
}

// d/dk (theta2(0, 1/(2*k*k/M_PI))/sqrt(2*k*k*M_PI))
template <class RealType, class Policy>
RealType kolmogorov_smirnov_pdf_small_x(RealType x, RealType n, const Policy&) {
    BOOST_MATH_STD_USING
    RealType value = RealType(0), delta = RealType(0), last_delta = RealType(0);
    RealType eps = policies::get_epsilon<RealType, Policy>();
    int i = 0;
    RealType pi2 = constants::pi_sqr<RealType>();
    RealType x2n = x*x*n;
    if (x2n*x2n == 0.0) {
        return static_cast<RealType>(0);
    }
    while (1) {
        delta = exp(-RealType(i+0.5)*RealType(i+0.5)*pi2/(2*x2n)) * (RealType(i+0.5)*RealType(i+0.5)*pi2 - x2n);

        if (delta == 0.0)
            break;

        if (last_delta != 0.0 && fabs(delta/last_delta) < eps)
            break;

        value += delta + delta;
        last_delta = delta;
        i++;
    }

    return value * sqrt(n) * constants::root_half_pi<RealType>() / (x2n*x2n);
}

// d/dx (theta4(0, 2*x*x*n/M_PI))
template <class RealType, class Policy>
inline RealType kolmogorov_smirnov_pdf_large_x(RealType x, RealType n, const Policy&) {
    BOOST_MATH_STD_USING
    RealType value = RealType(0), delta = RealType(0), last_delta = RealType(0);
    RealType eps = policies::get_epsilon<RealType, Policy>();
    int i = 1;
    while (1) {
        delta = 8*x*i*i*exp(-2*i*i*x*x*n);

        if (delta == 0.0)
            break;

        if (last_delta != 0.0 && fabs(delta / last_delta) < eps)
            break;

        if (i%2 == 0)
            delta = -delta;

        value += delta;
        last_delta = delta;
        i++;
    }

    return value * n;
}

}; // detail

template <class RealType = double, class Policy = policies::policy<> >
    class kolmogorov_smirnov_distribution
{
    public:
        typedef RealType value_type;
        typedef Policy policy_type;

        // Constructor
    kolmogorov_smirnov_distribution( RealType n ) : n_obs_(n)
    {
        RealType result;
        detail::check_df(
                "boost::math::kolmogorov_smirnov_distribution<%1%>::kolmogorov_smirnov_distribution", n_obs_, &result, Policy());
    }

    RealType number_of_observations()const
    {
        return n_obs_;
    }

    private:

    RealType n_obs_; // positive integer
};

typedef kolmogorov_smirnov_distribution<double> kolmogorov_k; // Convenience typedef for double version.

#ifdef __cpp_deduction_guides
template <class RealType>
kolmogorov_smirnov_distribution(RealType)->kolmogorov_smirnov_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

namespace detail {
template <class RealType, class Policy>
struct kolmogorov_smirnov_quantile_functor
{
  kolmogorov_smirnov_quantile_functor(const boost::math::kolmogorov_smirnov_distribution<RealType, Policy> dist, RealType const& p)
    : distribution(dist), prob(p)
  {
  }

  boost::math::tuple<RealType, RealType> operator()(RealType const& x)
  {
    RealType fx = cdf(distribution, x) - prob;  // Difference cdf - value - to minimize.
    RealType dx = pdf(distribution, x); // pdf is 1st derivative.
    // return both function evaluation difference f(x) and 1st derivative f'(x).
    return boost::math::make_tuple(fx, dx);
  }
private:
  const boost::math::kolmogorov_smirnov_distribution<RealType, Policy> distribution;
  RealType prob;
};

template <class RealType, class Policy>
struct kolmogorov_smirnov_complementary_quantile_functor
{
  kolmogorov_smirnov_complementary_quantile_functor(const boost::math::kolmogorov_smirnov_distribution<RealType, Policy> dist, RealType const& p)
    : distribution(dist), prob(p)
  {
  }

  boost::math::tuple<RealType, RealType> operator()(RealType const& x)
  {
    RealType fx = cdf(complement(distribution, x)) - prob;  // Difference cdf - value - to minimize.
    RealType dx = -pdf(distribution, x); // pdf is the negative of the derivative of (1-CDF)
    // return both function evaluation difference f(x) and 1st derivative f'(x).
    return boost::math::make_tuple(fx, dx);
  }
private:
  const boost::math::kolmogorov_smirnov_distribution<RealType, Policy> distribution;
  RealType prob;
};

template <class RealType, class Policy>
struct kolmogorov_smirnov_negative_pdf_functor
{
    RealType operator()(RealType const& x) {
        if (2*x*x < constants::pi<RealType>()) {
            return -kolmogorov_smirnov_pdf_small_x(x, static_cast<RealType>(1), Policy());
        }
        return -kolmogorov_smirnov_pdf_large_x(x, static_cast<RealType>(1), Policy());
    }
};
} // namespace detail

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const kolmogorov_smirnov_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const kolmogorov_smirnov_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   // In the exact distribution, the upper limit would be 1.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const kolmogorov_smirnov_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_FPU_EXCEPTION_GUARD
   BOOST_MATH_STD_USING  // for ADL of std functions.

   RealType n = dist.number_of_observations();
   RealType error_result;
   static const char* function = "boost::math::pdf(const kolmogorov_smirnov_distribution<%1%>&, %1%)";
   if(false == detail::check_x_not_NaN(function, x, &error_result, Policy()))
      return error_result;

   if(false == detail::check_df(function, n, &error_result, Policy()))
      return error_result;

   if (x < 0 || !(boost::math::isfinite)(x))
   {
      return policies::raise_domain_error<RealType>(
         function, "Kolmogorov-Smirnov parameter was %1%, but must be > 0 !", x, Policy());
   }

   if (2*x*x*n < constants::pi<RealType>()) {
       return detail::kolmogorov_smirnov_pdf_small_x(x, n, Policy());
   }

   return detail::kolmogorov_smirnov_pdf_large_x(x, n, Policy());
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const kolmogorov_smirnov_distribution<RealType, Policy>& dist, const RealType& x)
{
    BOOST_MATH_STD_USING // for ADL of std function exp.
   static const char* function = "boost::math::cdf(const kolmogorov_smirnov_distribution<%1%>&, %1%)";
   RealType error_result;
   RealType n = dist.number_of_observations();
   if(false == detail::check_x_not_NaN(function, x, &error_result, Policy()))
      return error_result;
   if(false == detail::check_df(function, n, &error_result, Policy()))
      return error_result;
   if((x < 0) || !(boost::math::isfinite)(x)) {
      return policies::raise_domain_error<RealType>(
         function, "Random variable parameter was %1%, but must be between > 0 !", x, Policy());
   }

   if (x*x*n == 0)
       return 0;

   return jacobi_theta4tau(RealType(0), 2*x*x*n/constants::pi<RealType>(), Policy());
} // cdf

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<kolmogorov_smirnov_distribution<RealType, Policy>, RealType>& c) {
    BOOST_MATH_STD_USING // for ADL of std function exp.
    RealType x = c.param;
   static const char* function = "boost::math::cdf(const complemented2_type<const kolmogorov_smirnov_distribution<%1%>&, %1%>)";
   RealType error_result;
   kolmogorov_smirnov_distribution<RealType, Policy> const& dist = c.dist;
   RealType n = dist.number_of_observations();

   if(false == detail::check_x_not_NaN(function, x, &error_result, Policy()))
      return error_result;
   if(false == detail::check_df(function, n, &error_result, Policy()))
      return error_result;

   if((x < 0) || !(boost::math::isfinite)(x))
      return policies::raise_domain_error<RealType>(
         function, "Random variable parameter was %1%, but must be between > 0 !", x, Policy());

   if (x*x*n == 0)
       return 1;

   if (2*x*x*n > constants::pi<RealType>())
       return -jacobi_theta4m1tau(RealType(0), 2*x*x*n/constants::pi<RealType>(), Policy());

   return RealType(1) - jacobi_theta4tau(RealType(0), 2*x*x*n/constants::pi<RealType>(), Policy());
} // cdf (complemented)

template <class RealType, class Policy>
inline RealType quantile(const kolmogorov_smirnov_distribution<RealType, Policy>& dist, const RealType& p)
{
    BOOST_MATH_STD_USING
   static const char* function = "boost::math::quantile(const kolmogorov_smirnov_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   RealType n = dist.number_of_observations();
   if(false == detail::check_probability(function, p, &error_result, Policy()))
      return error_result;
   if(false == detail::check_df(function, n, &error_result, Policy()))
      return error_result;

   RealType k = detail::kolmogorov_smirnov_quantile_guess(p) / sqrt(n);
   const int get_digits = policies::digits<RealType, Policy>();// get digits from policy,
   std::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.

   return tools::newton_raphson_iterate(detail::kolmogorov_smirnov_quantile_functor<RealType, Policy>(dist, p),
           k, RealType(0), boost::math::tools::max_value<RealType>(), get_digits, m);
} // quantile

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<kolmogorov_smirnov_distribution<RealType, Policy>, RealType>& c) {
    BOOST_MATH_STD_USING
   static const char* function = "boost::math::quantile(const kolmogorov_smirnov_distribution<%1%>&, %1%)";
   kolmogorov_smirnov_distribution<RealType, Policy> const& dist = c.dist;
   RealType n = dist.number_of_observations();
   // Error check:
   RealType error_result;
   RealType p = c.param;

   if(false == detail::check_probability(function, p, &error_result, Policy()))
      return error_result;
   if(false == detail::check_df(function, n, &error_result, Policy()))
      return error_result;

   RealType k = detail::kolmogorov_smirnov_quantile_guess(RealType(1-p)) / sqrt(n);

   const int get_digits = policies::digits<RealType, Policy>();// get digits from policy,
   std::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.

   return tools::newton_raphson_iterate(
           detail::kolmogorov_smirnov_complementary_quantile_functor<RealType, Policy>(dist, p),
           k, RealType(0), boost::math::tools::max_value<RealType>(), get_digits, m);
} // quantile (complemented)

template <class RealType, class Policy>
inline RealType mode(const kolmogorov_smirnov_distribution<RealType, Policy>& dist)
{
    BOOST_MATH_STD_USING
   static const char* function = "boost::math::mode(const kolmogorov_smirnov_distribution<%1%>&)";
   RealType n = dist.number_of_observations();
   RealType error_result;
   if(false == detail::check_df(function, n, &error_result, Policy()))
      return error_result;

    std::pair<RealType, RealType> r = boost::math::tools::brent_find_minima(
            detail::kolmogorov_smirnov_negative_pdf_functor<RealType, Policy>(),
            static_cast<RealType>(0), static_cast<RealType>(1), policies::digits<RealType, Policy>());
    return r.first / sqrt(n);
}

// Mean and variance come directly from
// https://www.jstatsoft.org/article/view/v008i18 Section 3
template <class RealType, class Policy>
inline RealType mean(const kolmogorov_smirnov_distribution<RealType, Policy>& dist)
{
    BOOST_MATH_STD_USING
   static const char* function = "boost::math::mean(const kolmogorov_smirnov_distribution<%1%>&)";
    RealType n = dist.number_of_observations();
    RealType error_result;
    if(false == detail::check_df(function, n, &error_result, Policy()))
        return error_result;
    return constants::root_half_pi<RealType>() * constants::ln_two<RealType>() / sqrt(n);
}

template <class RealType, class Policy>
inline RealType variance(const kolmogorov_smirnov_distribution<RealType, Policy>& dist)
{
   static const char* function = "boost::math::variance(const kolmogorov_smirnov_distribution<%1%>&)";
    RealType n = dist.number_of_observations();
    RealType error_result;
    if(false == detail::check_df(function, n, &error_result, Policy()))
        return error_result;
    return (constants::pi_sqr_div_six<RealType>()
            - constants::pi<RealType>() * constants::ln_two<RealType>() * constants::ln_two<RealType>()) / (2*n);
}

// Skewness and kurtosis come from integrating the PDF
// The alternating series pops out a Dirichlet eta function which is related to the zeta function
template <class RealType, class Policy>
inline RealType skewness(const kolmogorov_smirnov_distribution<RealType, Policy>& dist)
{
    BOOST_MATH_STD_USING
   static const char* function = "boost::math::skewness(const kolmogorov_smirnov_distribution<%1%>&)";
    RealType n = dist.number_of_observations();
    RealType error_result;
    if(false == detail::check_df(function, n, &error_result, Policy()))
        return error_result;
    RealType ex3 = RealType(0.5625) * constants::root_half_pi<RealType>() * constants::zeta_three<RealType>() / n / sqrt(n);
    RealType mean = boost::math::mean(dist);
    RealType var = boost::math::variance(dist);
    return (ex3 - 3 * mean * var - mean * mean * mean) / var / sqrt(var);
}

template <class RealType, class Policy>
inline RealType kurtosis(const kolmogorov_smirnov_distribution<RealType, Policy>& dist)
{
    BOOST_MATH_STD_USING
   static const char* function = "boost::math::kurtosis(const kolmogorov_smirnov_distribution<%1%>&)";
    RealType n = dist.number_of_observations();
    RealType error_result;
    if(false == detail::check_df(function, n, &error_result, Policy()))
        return error_result;
    RealType ex4 = 7 * constants::pi_sqr_div_six<RealType>() * constants::pi_sqr_div_six<RealType>() / 20 / n / n;
    RealType mean = boost::math::mean(dist);
    RealType var = boost::math::variance(dist);
    RealType skew = boost::math::skewness(dist);
    return (ex4 - 4 * mean * skew * var * sqrt(var) - 6 * mean * mean * var - mean * mean * mean * mean) / var / var;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const kolmogorov_smirnov_distribution<RealType, Policy>& dist)
{
   static const char* function = "boost::math::kurtosis_excess(const kolmogorov_smirnov_distribution<%1%>&)";
    RealType n = dist.number_of_observations();
    RealType error_result;
    if(false == detail::check_df(function, n, &error_result, Policy()))
        return error_result;
    return kurtosis(dist) - 3;
}
}}
#endif

/* kolmogorov_smirnov.hpp
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
*/