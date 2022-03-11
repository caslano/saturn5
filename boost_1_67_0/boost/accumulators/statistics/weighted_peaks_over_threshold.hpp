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