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