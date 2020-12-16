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
BRybcF+zsSpW9bNGTaqRLqL5wSK9r/NrP4bwa+g0+9nR3TR+TRufc6NofD7AoJSi25yClS84JK/a+JytBbXxaYsgBgE7BuYMqqd1O5NLEw6P9SOYxgefJ/qZ6/cSNivi2WJX1hGPlwvGjgaIJPNGBm9dgMFr4fS/rzF4LXIyvrJOO8svHJtosWlq6tQJQZRYiGHGIP+GXFrj6z+X1//hptf/W42tf+N6mm9Y/4+aZM2oavImXfXtqfqQNTNLC2pjMrlexkS4Nx4UYbA0ZZWtPB4YRBmPS/c0tsoLphFE8w0YCSscYfGZeyeBdhg4TkDzfqiDFhUKWm1dCGhf1Alo2cqGSLg+CoXrn58blu4cTZH9lC5d4gdbhOm7WsL4wbD0hrD01VGh4f7RoeFRlrDvo8LSo8PqDwu3jAlLDws7KRyuz8RD0RfkvRx/ds3Rjz9H2j3rMV7VwDmioeL0NMBM+itxU012s/YD1Z8gxPpJTIeqMzfQ9pt4MSAHFqBpF8ezBZRIHAnLWtRBFpNxuKC9y5ddT0ySb1icv31mZicMaE2cCw7myCG8L+cAS/YO+v2UTyvEUkFFOijlPaSkbWLZELjcOLX1ilrKeQBxoAFMCFEu/3o23+KvZHKp+8qREcXjaE3TgHGjKHre8BNhonq86vRWH/UdlJCjEVtcgrSKK7YL0VVzldgTqw0/c62k/79eqBangWpxGqiWHI1q4WK4QA2621YTdECB3DPXH1AP4fAmrN5cNe3dWiGjyTg/y1dwgI9mRFDWC0KB5e0QlKydEdRTHWr8WumYLz/gjuEU9ac1qIPuOUmgKqn/9iKG1ak0xYKRdA64hfizqe9TI/7zylXN+Bn0r3IPBmb3ZVfqszudZSyqzOzAfLZVvynTVcy9lC1gzTE/nx3YycRaU2KWr+Z9Sv2nSSeTuL9RZEac+q/V0sHF6wwd/M9dzHLHkDrHcEq9cx0N8xBM98FxtAAcCjYOK6V8VUu6NRW2tE2AgYai33tS4O/oEyVm1y+J5Nxfpq7Ly96/luAbACwmZzCFoMHqZTnp6lN8HjOMHdCq/h8DHfqtQzoUVB1NdTmRzIYx/Z/UWe9yH6hZ72nGk/Bo6c4hUYNbSzk3mGJxp9EMT6I21+EAkLK9z2rqG7mPVes+zGQ6cJdgJrQvatpSrqclF3347g59k5gp4KAruoKOoU0jFWHMX5v5BLVBw8/7xP99LXeEUwgzMe169B3EQWjhyDgypr9DzAaPOMhssNYBs0HAWQPqTQ4ru1ELOqr4wPKpg60HK8d96mjCevD4DtiOYr+QWVt7YvYLHbCfi/z2udW6/LYrWtPkaVhJaXPsF96tC5TrCpa7EpKqxu0X0kpPgf1Co+e7LX6oPYHz3XSo0AXOXO+u0s9cv0D0Mc53k0qDx67fr2rO+e66/cG6/JV6XYWo62jnu2+8EayoZNWpON8Nsw95+UDtidqHbP+m1mgfcv9PgcnkX6VTooX7a5tjH+KuC7EPmbTyv8g+BPTckcRQeu+X0PCbYWGnMSx3z4f71+v3nTah4X5mkytjhbt1DusMO5U16os58aam/OwJfSrlG8vb9y2XR19Ufw+iMry+lYb08jcj0xcY0nt8HJlebEjPbST9dkP6hLWR6dmG9D+uiUzvYUh/Z19keowh/cNFken79gfTtzdS/kpDugX9cyz/2fMkv+asdPHXsqAxobvt4Vcs7acQmaW0huYoXdjkiFb/Bd7w13u1NujrCCjxAkqaX1xWa1YjRHDQgTkuqPfl7lG/weangLgaOIU1ZH2Fy2vaw6SB3tJrWnnqe71JXLk1q4GImvuqAhTza1W8I0J1h71l6e6A5bJxuYH7Jew=
*/