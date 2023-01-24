///////////////////////////////////////////////////////////////////////////////
// pot_quantile.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <boost/parameter/keyword.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/weighted_peaks_over_threshold.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // pot_quantile_impl
    //
    /**
        @brief Quantile Estimation based on Peaks over Threshold Method (for both left and right tails)

        Computes an estimate
        \f[
            \hat{q}_{\alpha} = \bar{u} + \frac{\bar{\beta}}{\xi}\left[(1-\alpha)^{-\xi}-1\right]
        \f]
        for a right or left extreme quantile, \f$\bar[u]\f$, \f$\bar{\beta}\f$ and \f$\xi\f$ being the parameters of the
        generalized Pareto distribution that approximates the right tail of the distribution (or the mirrored left tail,
        in case the left tail is used). In the latter case, the result is mirrored back, yielding the correct result.
    */
    template<typename Sample, typename Impl, typename LeftRight>
    struct pot_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef float_type result_type;

        pot_quantile_impl(dont_care)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_peaks_over_threshold<LeftRight>
                  , tag::peaks_over_threshold<LeftRight>
                >::type
            peaks_over_threshold_tag;

            extractor<peaks_over_threshold_tag> const some_peaks_over_threshold = {};

            float_type u_bar    = some_peaks_over_threshold(args).template get<0>();
            float_type beta_bar = some_peaks_over_threshold(args).template get<1>();
            float_type xi_hat   = some_peaks_over_threshold(args).template get<2>();

            return this->sign_ * (u_bar + beta_bar/xi_hat * ( std::pow(
                    is_same<LeftRight, left>::value ? args[quantile_probability] : 1. - args[quantile_probability]
                , -xi_hat
              ) - 1.));
        }
    
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sign_;
        }

    private:
        short sign_; // if the fit parameters from the mirrored left tail extreme values are used, mirror back the result
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::pot_quantile<>
// tag::pot_quantile_prob<>
// tag::weighted_pot_quantile<>
// tag::weighted_pot_quantile_prob<>
//
namespace tag
{
    template<typename LeftRight>
    struct pot_quantile
      : depends_on<peaks_over_threshold<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct pot_quantile_prob
      : depends_on<peaks_over_threshold_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_quantile
      : depends_on<weighted_peaks_over_threshold<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, weighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_quantile_prob
      : depends_on<weighted_peaks_over_threshold_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_quantile_impl<mpl::_1, weighted, LeftRight> impl;
    };
}

// pot_quantile<LeftRight>(with_threshold_value) -> pot_quantile<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_quantile<LeftRight>(with_threshold_value)>
{
    typedef tag::pot_quantile<LeftRight> type;
};

// pot_quantile<LeftRight>(with_threshold_probability) -> pot_quantile_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_quantile<LeftRight>(with_threshold_probability)>
{
    typedef tag::pot_quantile_prob<LeftRight> type;
};

// weighted_pot_quantile<LeftRight>(with_threshold_value) -> weighted_pot_quantile<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_quantile<LeftRight>(with_threshold_value)>
{
    typedef tag::weighted_pot_quantile<LeftRight> type;
};

// weighted_pot_quantile<LeftRight>(with_threshold_probability) -> weighted_pot_quantile_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_quantile<LeftRight>(with_threshold_probability)>
{
    typedef tag::weighted_pot_quantile_prob<LeftRight> type;
};

// for the purposes of feature-based dependency resolution,
// pot_quantile<LeftRight> and pot_quantile_prob<LeftRight> provide
// the same feature as quantile
template<typename LeftRight>
struct feature_of<tag::pot_quantile<LeftRight> >
  : feature_of<tag::quantile>
{
};

template<typename LeftRight>
struct feature_of<tag::pot_quantile_prob<LeftRight> >
  : feature_of<tag::quantile>
{
};

// So that pot_quantile can be automatically substituted
// with weighted_pot_quantile when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_quantile<LeftRight> >
{
    typedef tag::weighted_pot_quantile<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_quantile<LeftRight> >
  : feature_of<tag::pot_quantile<LeftRight> >
{
};

// So that pot_quantile_prob can be automatically substituted
// with weighted_pot_quantile_prob when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_quantile_prob<LeftRight> >
{
    typedef tag::weighted_pot_quantile_prob<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_quantile_prob<LeftRight> >
  : feature_of<tag::pot_quantile_prob<LeftRight> >
{
};

}} // namespace boost::accumulators

#endif

/* pot_quantile.hpp
Tm88Qa2d/tnonzWJSMleSzmEjgs6kIUb1prsxJEpvZdBbKnMnQHEfZI5HIWYI/XUEiLoelBV6VKn3AegsZoprBsdo1OEgZs5MVkIvMiJqUJg/Uw4PMgRxDGUKDy6BrWfVdYuoE23YAnb9S99oPC+RbO9BMqPvxXhaIeW0FL1m6ML5qxtAH/VagB86VtRgFdGGGAl0X7Ny3Qov23Of9fnuFmH8+2JxOUrY19pLxmHOqS0ue4UCxUDR/3UbJayGgdPQ0o5UYgKvUkdYxHW/tMPoa/LrWxq1aW8NinYfIqXvqSC3smfV5yPkTY2UJYcvxGwK1cT0088P2F1yiydZu9nOnTgfNMYG86dko1Np0CHTepOmyIlRw4nPWFtHGMzSzvrOV+0EbV5nkD/YdS9k6u17eRquUTjWKulWOYeCOKfr9UF07PpI6rEKIgV10Y+/yBgMgQtqcQCQu47Qzm1vE3w623n0RhUhf8mQ3WGxbCywKIZ4EJ9XHXMWChNFS+3EBG5jeYx62XAQak1AHaORY3ECwAJLPbTwYcI4PJ/TDDGKLUKHx/0/5TsP3+VsNrXAk3Vk4YPoVZ1Q7YiHy0+Rwj+I1xInusnBIZYkBglBOZywX2GG7IPBJ37CDw3uZT1XlZIryXQdp4EbDsVbj6pyt9sXB4vd0qjzvlTr/JexUbhqx4FaEO1V1HmE7WMTgcQjZGvauTqlP/Vh2OYpYSK
*/