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
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
*/