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