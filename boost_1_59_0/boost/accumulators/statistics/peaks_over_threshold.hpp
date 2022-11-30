///////////////////////////////////////////////////////////////////////////////
// peaks_over_threshold.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_PEAKS_OVER_THRESHOLD_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_PEAKS_OVER_THRESHOLD_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <boost/config/no_tr1/cmath.hpp> // pow
#include <sstream> // stringstream
#include <stdexcept> // runtime_error
#include <boost/throw_exception.hpp>
#include <boost/range.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/tail.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// threshold_probability and threshold named parameters
//
BOOST_PARAMETER_NESTED_KEYWORD(tag, pot_threshold_value, threshold_value)
BOOST_PARAMETER_NESTED_KEYWORD(tag, pot_threshold_probability, threshold_probability)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(pot_threshold_value)
BOOST_ACCUMULATORS_IGNORE_GLOBAL(pot_threshold_probability)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // peaks_over_threshold_impl
    //  works with an explicit threshold value and does not depend on order statistics
    /**
        @brief Peaks over Threshold Method for Quantile and Tail Mean Estimation

        According to the theorem of Pickands-Balkema-de Haan, the distribution function \f$F_u(x)\f$ of
        the excesses \f$x\f$ over some sufficiently high threshold \f$u\f$ of a distribution function \f$F(x)\f$
        may be approximated by a generalized Pareto distribution
        \f[
            G_{\xi,\beta}(x) =
            \left\{
            \begin{array}{ll}
                \beta^{-1}\left(1+\frac{\xi x}{\beta}\right)^{-1/\xi-1} & \textrm{if }\xi\neq0\\
                \beta^{-1}\exp\left(-\frac{x}{\beta}\right) & \textrm{if }\xi=0,
            \end{array}
            \right.
        \f]
        with suitable parameters \f$\xi\f$ and \f$\beta\f$ that can be estimated, e.g., with the method of moments, cf.
        Hosking and Wallis (1987),
        \f[
            \begin{array}{lll}
            \hat{\xi} & = & \frac{1}{2}\left[1-\frac{(\hat{\mu}-u)^2}{\hat{\sigma}^2}\right]\\
            \hat{\beta} & = & \frac{\hat{\mu}-u}{2}\left[\frac{(\hat{\mu}-u)^2}{\hat{\sigma}^2}+1\right],
            \end{array}
        \f]
        \f$\hat{\mu}\f$ and \f$\hat{\sigma}^2\f$ being the empirical mean and variance of the samples over
        the threshold \f$u\f$. Equivalently, the distribution function
        \f$F_u(x-u)\f$ of the exceedances \f$x-u\f$ can be approximated by
        \f$G_{\xi,\beta}(x-u)=G_{\xi,\beta,u}(x)\f$. Since for \f$x\geq u\f$ the distribution function \f$F(x)\f$
        can be written as
        \f[
            F(x) = [1 - \P(X \leq u)]F_u(x - u) + \P(X \leq u)
        \f]
        and the probability \f$\P(X \leq u)\f$ can be approximated by the empirical distribution function
        \f$F_n(u)\f$ evaluated at \f$u\f$, an estimator of \f$F(x)\f$ is given by
        \f[
            \widehat{F}(x) = [1 - F_n(u)]G_{\xi,\beta,u}(x) + F_n(u).
        \f]
        It can be shown that \f$\widehat{F}(x)\f$ is a generalized
        Pareto distribution \f$G_{\xi,\bar{\beta},\bar{u}}(x)\f$ with \f$\bar{\beta}=\beta[1-F_n(u)]^{\xi}\f$
        and \f$\bar{u}=u-\bar{\beta}\left\{[1-F_n(u)]^{-\xi}-1\right\}/\xi\f$. By inverting \f$\widehat{F}(x)\f$,
        one obtains an estimator for the \f$\alpha\f$-quantile,
        \f[
            \hat{q}_{\alpha} = \bar{u} + \frac{\bar{\beta}}{\xi}\left[(1-\alpha)^{-\xi}-1\right],
        \f]
        and similarly an estimator for the (coherent) tail mean,
        \f[
            \widehat{CTM}_{\alpha} = \hat{q}_{\alpha} - \frac{\bar{\beta}}{\xi-1}(1-\alpha)^{-\xi},
        \f]
        cf. McNeil and Frey (2000).

        Note that in case extreme values of the left tail are fitted, the distribution is mirrored with respect to the
        \f$y\f$ axis such that the left tail can be treated as a right tail. The computed fit parameters thus define
        the Pareto distribution that fits the mirrored left tail. When quantities like a quantile or a tail mean are
        computed using the fit parameters obtained from the mirrored data, the result is mirrored back, yielding the
        correct result.

        For further details, see

        J. R. M. Hosking and J. R. Wallis, Parameter and quantile estimation for the generalized Pareto distribution,
        Technometrics, Volume 29, 1987, p. 339-349

        A. J. McNeil and R. Frey, Estimation of Tail-Related Risk Measures for Heteroscedastic Financial Time Series:
        an Extreme Value Approach, Journal of Empirical Finance, Volume 7, 2000, p. 271-300

        @param quantile_probability
        @param pot_threshold_value
    */
    template<typename Sample, typename LeftRight>
    struct peaks_over_threshold_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef boost::tuple<float_type, float_type, float_type> result_type;
        // for left tail fitting, mirror the extreme values
        typedef mpl::int_<is_same<LeftRight, left>::value ? -1 : 1> sign;

        template<typename Args>
        peaks_over_threshold_impl(Args const &args)
          : Nu_(0)
          , mu_(sign::value * numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , sigma2_(numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , threshold_(sign::value * args[pot_threshold_value])
          , fit_parameters_(boost::make_tuple(0., 0., 0.))
          , is_dirty_(true)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty_ = true;

            if (sign::value * args[sample] > this->threshold_)
            {
                this->mu_ += args[sample];
                this->sigma2_ += args[sample] * args[sample];
                ++this->Nu_;
            }
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty_)
            {
                this->is_dirty_ = false;

                std::size_t cnt = count(args);

                this->mu_ = sign::value * numeric::fdiv(this->mu_, this->Nu_);
                this->sigma2_ = numeric::fdiv(this->sigma2_, this->Nu_);
                this->sigma2_ -= this->mu_ * this->mu_;

                float_type threshold_probability = numeric::fdiv(cnt - this->Nu_, cnt);

                float_type tmp = numeric::fdiv(( this->mu_ - this->threshold_ )*( this->mu_ - this->threshold_ ), this->sigma2_);
                float_type xi_hat = 0.5 * ( 1. - tmp );
                float_type beta_hat = 0.5 * ( this->mu_ - this->threshold_ ) * ( 1. + tmp );
                float_type beta_bar = beta_hat * std::pow(1. - threshold_probability, xi_hat);
                float_type u_bar = this->threshold_ - beta_bar * ( std::pow(1. - threshold_probability, -xi_hat) - 1.)/xi_hat;
                this->fit_parameters_ = boost::make_tuple(u_bar, beta_bar, xi_hat);
            }

            return this->fit_parameters_;
        }

        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that threshold did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & Nu_;
            ar & mu_;
            ar & sigma2_;
            ar & threshold_;
            ar & get<0>(fit_parameters_);
            ar & get<1>(fit_parameters_);
            ar & get<2>(fit_parameters_);
            ar & is_dirty_;
        }

    private:
        std::size_t Nu_;                     // number of samples larger than threshold
        mutable float_type mu_;              // mean of Nu_ largest samples
        mutable float_type sigma2_;          // variance of Nu_ largest samples
        float_type threshold_;
        mutable result_type fit_parameters_; // boost::tuple that stores fit parameters
        mutable bool is_dirty_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // peaks_over_threshold_prob_impl
    //  determines threshold from a given threshold probability using order statistics
    /**
        @brief Peaks over Threshold Method for Quantile and Tail Mean Estimation

        @sa peaks_over_threshold_impl

        @param quantile_probability
        @param pot_threshold_probability
    */
    template<typename Sample, typename LeftRight>
    struct peaks_over_threshold_prob_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef boost::tuple<float_type, float_type, float_type> result_type;
        // for left tail fitting, mirror the extreme values
        typedef mpl::int_<is_same<LeftRight, left>::value ? -1 : 1> sign;

        template<typename Args>
        peaks_over_threshold_prob_impl(Args const &args)
          : mu_(sign::value * numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , sigma2_(numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , threshold_probability_(args[pot_threshold_probability])
          , fit_parameters_(boost::make_tuple(0., 0., 0.))
          , is_dirty_(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty_ = true;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty_)
            {
                this->is_dirty_ = false;

                std::size_t cnt = count(args);

                // the n'th cached sample provides an approximate threshold value u
                std::size_t n = static_cast<std::size_t>(
                    std::ceil(
                        cnt * ( ( is_same<LeftRight, left>::value ) ? this->threshold_probability_ : 1. - this->threshold_probability_ )
                    )
                );

                // If n is in a valid range, return result, otherwise return NaN or throw exception
                if ( n >= static_cast<std::size_t>(tail(args).size()))
                {
                    if (std::numeric_limits<float_type>::has_quiet_NaN)
                    {
                        return boost::make_tuple(
                            std::numeric_limits<float_type>::quiet_NaN()
                          , std::numeric_limits<float_type>::quiet_NaN()
                          , std::numeric_limits<float_type>::quiet_NaN()
                        );
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                        boost::throw_exception(std::runtime_error(msg.str()));
                        return boost::make_tuple(Sample(0), Sample(0), Sample(0));
                    }
                }
                else
                {
                    float_type u = *(tail(args).begin() + n - 1) * sign::value;

                    // compute mean and variance of samples above/under threshold value u
                    for (std::size_t i = 0; i < n; ++i)
                    {
                        mu_ += *(tail(args).begin() + i);
                        sigma2_ += *(tail(args).begin() + i) * (*(tail(args).begin() + i));
                    }

                    this->mu_ = sign::value * numeric::fdiv(this->mu_, n);
                    this->sigma2_ = numeric::fdiv(this->sigma2_, n);
                    this->sigma2_ -= this->mu_ * this->mu_;

                    if (is_same<LeftRight, left>::value)
                        this->threshold_probability_ = 1. - this->threshold_probability_;

                    float_type tmp = numeric::fdiv(( this->mu_ - u )*( this->mu_ - u ), this->sigma2_);
                    float_type xi_hat = 0.5 * ( 1. - tmp );
                    float_type beta_hat = 0.5 * ( this->mu_ - u ) * ( 1. + tmp );
                    float_type beta_bar = beta_hat * std::pow(1. - threshold_probability_, xi_hat);
                    float_type u_bar = u - beta_bar * ( std::pow(1. - threshold_probability_, -xi_hat) - 1.)/xi_hat;
                    this->fit_parameters_ = boost::make_tuple(u_bar, beta_bar, xi_hat);
                }
            }

            return this->fit_parameters_;
        }

        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that threshold did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & mu_;
            ar & sigma2_;
            ar & threshold_probability_;
            ar & get<0>(fit_parameters_);
            ar & get<1>(fit_parameters_);
            ar & get<2>(fit_parameters_);
            ar & is_dirty_;
        }

    private:
        mutable float_type mu_;                     // mean of samples above threshold u
        mutable float_type sigma2_;                 // variance of samples above threshold u
        mutable float_type threshold_probability_;
        mutable result_type fit_parameters_;        // boost::tuple that stores fit parameters
        mutable bool is_dirty_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::peaks_over_threshold
//
namespace tag
{
    template<typename LeftRight>
    struct peaks_over_threshold
      : depends_on<count>
      , pot_threshold_value
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::peaks_over_threshold_impl<mpl::_1, LeftRight> impl;
    };

    template<typename LeftRight>
    struct peaks_over_threshold_prob
      : depends_on<count, tail<LeftRight> >
      , pot_threshold_probability
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::peaks_over_threshold_prob_impl<mpl::_1, LeftRight> impl;
    };

    struct abstract_peaks_over_threshold
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::peaks_over_threshold
//
namespace extract
{
    extractor<tag::abstract_peaks_over_threshold> const peaks_over_threshold = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(peaks_over_threshold)
}

using extract::peaks_over_threshold;

// peaks_over_threshold<LeftRight>(with_threshold_value) -> peaks_over_threshold<LeftRight>
template<typename LeftRight>
struct as_feature<tag::peaks_over_threshold<LeftRight>(with_threshold_value)>
{
    typedef tag::peaks_over_threshold<LeftRight> type;
};

// peaks_over_threshold<LeftRight>(with_threshold_probability) -> peaks_over_threshold_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::peaks_over_threshold<LeftRight>(with_threshold_probability)>
{
    typedef tag::peaks_over_threshold_prob<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::peaks_over_threshold<LeftRight> >
  : feature_of<tag::abstract_peaks_over_threshold>
{
};

template<typename LeftRight>
struct feature_of<tag::peaks_over_threshold_prob<LeftRight> >
  : feature_of<tag::abstract_peaks_over_threshold>
{
};

// So that peaks_over_threshold can be automatically substituted
// with weighted_peaks_over_threshold when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::peaks_over_threshold<LeftRight> >
{
    typedef tag::weighted_peaks_over_threshold<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_peaks_over_threshold<LeftRight> >
  : feature_of<tag::peaks_over_threshold<LeftRight> >
{};

// So that peaks_over_threshold_prob can be automatically substituted
// with weighted_peaks_over_threshold_prob when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::peaks_over_threshold_prob<LeftRight> >
{
    typedef tag::weighted_peaks_over_threshold_prob<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_peaks_over_threshold_prob<LeftRight> >
  : feature_of<tag::peaks_over_threshold_prob<LeftRight> >
{};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* peaks_over_threshold.hpp
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
*/