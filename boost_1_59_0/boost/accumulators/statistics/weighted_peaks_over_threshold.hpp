///////////////////////////////////////////////////////////////////////////////
// weighted_peaks_over_threshold.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_PEAKS_OVER_THRESHOLD_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_PEAKS_OVER_THRESHOLD_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <boost/throw_exception.hpp>
#include <boost/range.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp> // for named parameters pot_threshold_value and pot_threshold_probability
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/tail_variate.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // weighted_peaks_over_threshold_impl
    //  works with an explicit threshold value and does not depend on order statistics of weighted samples
    /**
        @brief Weighted Peaks over Threshold Method for Weighted Quantile and Weighted Tail Mean Estimation

        @sa peaks_over_threshold_impl

        @param quantile_probability
        @param pot_threshold_value
    */
    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_peaks_over_threshold_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Weight, Sample>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef boost::tuple<float_type, float_type, float_type> result_type;

        template<typename Args>
        weighted_peaks_over_threshold_impl(Args const &args)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
          , mu_(sign_ * numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , sigma2_(numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , w_sum_(numeric::fdiv(args[weight | Weight()], (std::size_t)1))
          , threshold_(sign_ * args[pot_threshold_value])
          , fit_parameters_(boost::make_tuple(0., 0., 0.))
          , is_dirty_(true)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty_ = true;

            if (this->sign_ * args[sample] > this->threshold_)
            {
                this->mu_ += args[weight] * args[sample];
                this->sigma2_ += args[weight] * args[sample] * args[sample];
                this->w_sum_ += args[weight];
            }
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty_)
            {
                this->is_dirty_ = false;

                this->mu_ = this->sign_ * numeric::fdiv(this->mu_, this->w_sum_);
                this->sigma2_ = numeric::fdiv(this->sigma2_, this->w_sum_);
                this->sigma2_ -= this->mu_ * this->mu_;

                float_type threshold_probability = numeric::fdiv(sum_of_weights(args) - this->w_sum_, sum_of_weights(args));

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
            ar & sign_;
            ar & mu_;
            ar & sigma2_;
            ar & threshold_;
            ar & fit_parameters_;
            ar & is_dirty_;
        }

    private:
        short sign_;                         // for left tail fitting, mirror the extreme values
        mutable float_type mu_;              // mean of samples above threshold
        mutable float_type sigma2_;          // variance of samples above threshold
        mutable float_type w_sum_;           // sum of weights of samples above threshold
        float_type threshold_;
        mutable result_type fit_parameters_; // boost::tuple that stores fit parameters
        mutable bool is_dirty_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // weighted_peaks_over_threshold_prob_impl
    //  determines threshold from a given threshold probability using order statistics
    /**
        @brief Peaks over Threshold Method for Quantile and Tail Mean Estimation

        @sa weighted_peaks_over_threshold_impl

        @param quantile_probability
        @param pot_threshold_probability
    */
    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_peaks_over_threshold_prob_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Weight, Sample>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef boost::tuple<float_type, float_type, float_type> result_type;

        template<typename Args>
        weighted_peaks_over_threshold_prob_impl(Args const &args)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
          , mu_(sign_ * numeric::fdiv(args[sample | Sample()], (std::size_t)1))
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

                float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? this->threshold_probability_ : 1. - this->threshold_probability_ );

                std::size_t n = 0;
                Weight sum = Weight(0);

                while (sum < threshold)
                {
                    if (n < static_cast<std::size_t>(tail_weights(args).size()))
                    {
                        mu_ += *(tail_weights(args).begin() + n) * *(tail(args).begin() + n);
                        sigma2_ += *(tail_weights(args).begin() + n) * *(tail(args).begin() + n) * (*(tail(args).begin() + n));
                        sum += *(tail_weights(args).begin() + n);
                        n++;
                    }
                    else
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
                }

                float_type u = *(tail(args).begin() + n - 1) * this->sign_;


                this->mu_ = this->sign_ * numeric::fdiv(this->mu_, sum);
                this->sigma2_ = numeric::fdiv(this->sigma2_, sum);
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

            return this->fit_parameters_;
        }

    private:
        short sign_;                                // for left tail fitting, mirror the extreme values
        mutable float_type mu_;                     // mean of samples above threshold u
        mutable float_type sigma2_;                 // variance of samples above threshold u
        mutable float_type threshold_probability_;
        mutable result_type fit_parameters_;        // boost::tuple that stores fit parameters
        mutable bool is_dirty_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_peaks_over_threshold
//
namespace tag
{
    template<typename LeftRight>
    struct weighted_peaks_over_threshold
      : depends_on<sum_of_weights>
      , pot_threshold_value
    {
        /// INTERNAL ONLY
        typedef accumulators::impl::weighted_peaks_over_threshold_impl<mpl::_1, mpl::_2, LeftRight> impl;
    };

    template<typename LeftRight>
    struct weighted_peaks_over_threshold_prob
      : depends_on<sum_of_weights, tail_weights<LeftRight> >
      , pot_threshold_probability
    {
        /// INTERNAL ONLY
        typedef accumulators::impl::weighted_peaks_over_threshold_prob_impl<mpl::_1, mpl::_2, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_peaks_over_threshold
//
namespace extract
{
    extractor<tag::abstract_peaks_over_threshold> const weighted_peaks_over_threshold = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_peaks_over_threshold)
}

using extract::weighted_peaks_over_threshold;

// weighted_peaks_over_threshold<LeftRight>(with_threshold_value) -> weighted_peaks_over_threshold<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_peaks_over_threshold<LeftRight>(with_threshold_value)>
{
    typedef tag::weighted_peaks_over_threshold<LeftRight> type;
};

// weighted_peaks_over_threshold<LeftRight>(with_threshold_probability) -> weighted_peaks_over_threshold_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_peaks_over_threshold<LeftRight>(with_threshold_probability)>
{
    typedef tag::weighted_peaks_over_threshold_prob<LeftRight> type;
};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* weighted_peaks_over_threshold.hpp
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
*/