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