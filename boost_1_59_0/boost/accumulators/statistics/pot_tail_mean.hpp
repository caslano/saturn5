///////////////////////////////////////////////////////////////////////////////
// pot_tail_mean.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_POT_TAIL_MEAN_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_POT_TAIL_MEAN_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/weighted_peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/pot_quantile.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // pot_tail_mean_impl
    //
    /**
        @brief Estimation of the (coherent) tail mean based on the peaks over threshold method (for both left and right tails)

        Computes an estimate for the (coherent) tail mean
        \f[
            \widehat{CTM}_{\alpha} = \hat{q}_{\alpha} - \frac{\bar{\beta}}{\xi-1}(1-\alpha)^{-\xi},
        \f]
        where \f$\bar[u]\f$, \f$\bar{\beta}\f$ and \f$\xi\f$ are the parameters of the
        generalized Pareto distribution that approximates the right tail of the distribution (or the
        mirrored left tail, in case the left tail is used). In the latter case, the result is mirrored
        back, yielding the correct result.
    */
    template<typename Sample, typename Impl, typename LeftRight>
    struct pot_tail_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef float_type result_type;

        pot_tail_mean_impl(dont_care)
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

            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_pot_quantile<LeftRight>
                  , tag::pot_quantile<LeftRight>
                >::type
            pot_quantile_tag;

            extractor<peaks_over_threshold_tag> const some_peaks_over_threshold = {};
            extractor<pot_quantile_tag> const some_pot_quantile = {};

            float_type beta_bar = some_peaks_over_threshold(args).template get<1>();
            float_type xi_hat   = some_peaks_over_threshold(args).template get<2>();

            return some_pot_quantile(args) - this->sign_ * beta_bar/( xi_hat - 1. ) * std::pow(
                is_same<LeftRight, left>::value ? args[quantile_probability] : 1. - args[quantile_probability]
              , -xi_hat);
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
// tag::pot_tail_mean
// tag::pot_tail_mean_prob
//
namespace tag
{
    template<typename LeftRight>
    struct pot_tail_mean
      : depends_on<peaks_over_threshold<LeftRight>, pot_quantile<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct pot_tail_mean_prob
      : depends_on<peaks_over_threshold_prob<LeftRight>, pot_quantile_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, unweighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_tail_mean
      : depends_on<weighted_peaks_over_threshold<LeftRight>, weighted_pot_quantile<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, weighted, LeftRight> impl;
    };
    template<typename LeftRight>
    struct weighted_pot_tail_mean_prob
      : depends_on<weighted_peaks_over_threshold_prob<LeftRight>, weighted_pot_quantile_prob<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::pot_tail_mean_impl<mpl::_1, weighted, LeftRight> impl;
    };
}

// pot_tail_mean<LeftRight>(with_threshold_value) -> pot_tail_mean<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_tail_mean<LeftRight>(with_threshold_value)>
{
    typedef tag::pot_tail_mean<LeftRight> type;
};

// pot_tail_mean<LeftRight>(with_threshold_probability) -> pot_tail_mean_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::pot_tail_mean<LeftRight>(with_threshold_probability)>
{
    typedef tag::pot_tail_mean_prob<LeftRight> type;
};

// weighted_pot_tail_mean<LeftRight>(with_threshold_value) -> weighted_pot_tail_mean<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_tail_mean<LeftRight>(with_threshold_value)>
{
    typedef tag::weighted_pot_tail_mean<LeftRight> type;
};

// weighted_pot_tail_mean<LeftRight>(with_threshold_probability) -> weighted_pot_tail_mean_prob<LeftRight>
template<typename LeftRight>
struct as_feature<tag::weighted_pot_tail_mean<LeftRight>(with_threshold_probability)>
{
    typedef tag::weighted_pot_tail_mean_prob<LeftRight> type;
};

// for the purposes of feature-based dependency resolution,
// pot_tail_mean<LeftRight> and pot_tail_mean_prob<LeftRight> provide
// the same feature as tail_mean
template<typename LeftRight>
struct feature_of<tag::pot_tail_mean<LeftRight> >
  : feature_of<tag::tail_mean>
{
};

template<typename LeftRight>
struct feature_of<tag::pot_tail_mean_prob<LeftRight> >
  : feature_of<tag::tail_mean>
{
};

// So that pot_tail_mean can be automatically substituted
// with weighted_pot_tail_mean when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_tail_mean<LeftRight> >
{
    typedef tag::weighted_pot_tail_mean<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_tail_mean<LeftRight> >
  : feature_of<tag::pot_tail_mean<LeftRight> >
{
};

// So that pot_tail_mean_prob can be automatically substituted
// with weighted_pot_tail_mean_prob when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::pot_tail_mean_prob<LeftRight> >
{
    typedef tag::weighted_pot_tail_mean_prob<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_pot_tail_mean_prob<LeftRight> >
  : feature_of<tag::pot_tail_mean_prob<LeftRight> >
{
};

}} // namespace boost::accumulators

#endif

/* pot_tail_mean.hpp
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
*/