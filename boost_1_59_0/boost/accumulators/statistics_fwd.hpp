///////////////////////////////////////////////////////////////////////////////
// statistics_fwd.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATISTICS_FWD_HPP_EAN_23_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATISTICS_FWD_HPP_EAN_23_11_2005

#include <boost/mpl/apply_fwd.hpp> // for mpl::na
#include <boost/mpl/print.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/extractor.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// base struct and base extractor for quantiles
namespace tag
{
    struct quantile
      : depends_on<>
    {
        typedef mpl::print<class ____MISSING_SPECIFIC_QUANTILE_FEATURE_IN_ACCUMULATOR_SET____ > impl;
    };
}
namespace extract
{
    extractor<tag::quantile> const quantile = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(quantile)
}
using extract::quantile;

///////////////////////////////////////////////////////////////////////////////
// base struct and base extractor for *coherent* tail means
namespace tag
{
    struct tail_mean
      : depends_on<>
    {
        typedef mpl::print<class ____MISSING_SPECIFIC_TAIL_MEAN_FEATURE_IN_ACCUMULATOR_SET____ > impl;
    };
}
namespace extract
{
    extractor<tag::tail_mean> const tail_mean = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_mean)
}
using extract::tail_mean;

namespace tag
{
    ///////////////////////////////////////////////////////////////////////////////
    // Variates tags
    struct weights;
    struct covariate1;
    struct covariate2;

    ///////////////////////////////////////////////////////////////////////////////
    // Statistic tags
    struct count;
    template<typename VariateType, typename VariateTag>
    struct covariance;
    struct density;
    template<typename Feature>
    struct error_of;
    struct extended_p_square;
    struct extended_p_square_quantile;
    struct extended_p_square_quantile_quadratic;
    struct kurtosis;
    struct max;
    struct mean;
    struct immediate_mean;
    struct mean_of_weights;
    struct immediate_mean_of_weights;
    template<typename VariateType, typename VariateTag>
    struct mean_of_variates;
    template<typename VariateType, typename VariateTag>
    struct immediate_mean_of_variates;
    struct median;
    struct with_density_median;
    struct with_p_square_cumulative_distribution_median;
    struct min;
    template<int N>
    struct moment;
    template<typename LeftRight>
    struct peaks_over_threshold;
    template<typename LeftRight>
    struct peaks_over_threshold_prob;
    template<typename LeftRight>
    struct pot_tail_mean;
    template<typename LeftRight>
    struct pot_tail_mean_prob;
    template<typename LeftRight>
    struct pot_quantile;
    template<typename LeftRight>
    struct pot_quantile_prob;
    struct p_square_cumulative_distribution;
    struct p_square_quantile;
    struct p_square_quantile_for_median;
    struct skewness;
    struct sum;
    struct sum_of_weights;
    template<typename VariateType, typename VariateTag>
    struct sum_of_variates;
    struct sum_kahan;
    struct sum_of_weights_kahan;
    template<typename VariateType, typename VariateTag>
    struct sum_of_variates_kahan;
    template<typename LeftRight>
    struct tail;
    template<typename LeftRight>
    struct coherent_tail_mean;
    template<typename LeftRight>
    struct non_coherent_tail_mean;
    template<typename LeftRight>
    struct tail_quantile;
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate;
    template<typename LeftRight>
    struct tail_weights;
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct right_tail_variate;
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct left_tail_variate;
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct tail_variate_means;
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct absolute_tail_variate_means;
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct relative_tail_variate_means;
    struct lazy_variance;
    struct variance;
    template<typename VariateType, typename VariateTag>
    struct weighted_covariance;
    struct weighted_density;
    struct weighted_kurtosis;
    struct weighted_mean;
    struct immediate_weighted_mean;
    template<typename VariateType, typename VariateTag>
    struct weighted_mean_of_variates;
    template<typename VariateType, typename VariateTag>
    struct immediate_weighted_mean_of_variates;
    struct weighted_median;
    struct with_density_weighted_median;
    struct with_p_square_cumulative_distribution_weighted_median;
    struct weighted_extended_p_square;
    struct weighted_extended_p_square_quantile;
    struct weighted_extended_p_square_quantile_quadratic;
    template<int N>
    struct weighted_moment;
    template<typename LeftRight>
    struct weighted_peaks_over_threshold;
    template<typename LeftRight>
    struct weighted_peaks_over_threshold_prob;
    template<typename LeftRight>
    struct weighted_pot_quantile;
    template<typename LeftRight>
    struct weighted_pot_quantile_prob;
    template<typename LeftRight>
    struct weighted_pot_tail_mean;
    template<typename LeftRight>
    struct weighted_pot_tail_mean_prob;
    struct weighted_p_square_cumulative_distribution;
    struct weighted_p_square_quantile;
    struct weighted_p_square_quantile_for_median;
    struct weighted_skewness;
    template<typename LeftRight>
    struct weighted_tail_quantile;
    template<typename LeftRight>
    struct non_coherent_weighted_tail_mean;
    template<typename LeftRight>
    struct weighted_tail_quantile;
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct weighted_tail_variate_means;
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct absolute_weighted_tail_variate_means;
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct relative_weighted_tail_variate_means;
    struct lazy_weighted_variance;
    struct weighted_variance;
    struct weighted_sum;
    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates;
    struct rolling_window_plus1;
    struct rolling_window;
    struct rolling_sum;
    struct rolling_count;
    struct rolling_mean;
} // namespace tag

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // Statistics impls
    struct count_impl;

    template<typename Sample, typename VariateType, typename VariateTag>
    struct covariance_impl;

    template<typename Sample>
    struct density_impl;

    template<typename Sample, typename Feature>
    struct error_of_impl;

    template<typename Sample, typename Variance>
    struct error_of_mean_impl;

    template<typename Sample>
    struct extended_p_square_impl;

    template<typename Sample, typename Impl1, typename Impl2>
    struct extended_p_square_quantile_impl;

    template<typename Sample>
    struct kurtosis_impl;

    template<typename Sample>
    struct max_impl;

    template<typename Sample>
    struct median_impl;

    template<typename Sample>
    struct with_density_median_impl;

    template<typename Sample>
    struct with_p_square_cumulative_distribution_median_impl;

    template<typename Sample>
    struct min_impl;

    template<typename Sample, typename SumFeature = tag::sum>
    struct mean_impl;

    template<typename Sample, typename Tag = tag::sample>
    struct immediate_mean_impl;

    template<typename N, typename Sample>
    struct moment_impl;

    template<typename Sample, typename LeftRight>
    struct peaks_over_threshold_prob_impl;

    template<typename Sample, typename Impl, typename LeftRight>
    struct pot_quantile_impl;

    template<typename Sample, typename Impl, typename LeftRight>
    struct pot_tail_mean_impl;

    template<typename Sample>
    struct p_square_cumulative_distribution_impl;

    template<typename Sample, typename Impl>
    struct p_square_quantile_impl;

    template<typename Sample>
    struct skewness_impl;

    template<typename Sample, typename Tag = tag::sample>
    struct sum_impl;

    template<typename Sample, typename Tag>
    struct sum_kahan_impl;

    template<typename Sample, typename LeftRight>
    struct tail_impl;

    template<typename Sample, typename LeftRight>
    struct coherent_tail_mean_impl;

    template<typename Sample, typename LeftRight>
    struct non_coherent_tail_mean_impl;

    template<typename Sample, typename LeftRight>
    struct tail_quantile_impl;

    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate_impl;

    template<typename Sample, typename Impl, typename LeftRight, typename VariateTag>
    struct tail_variate_means_impl;

    template<typename Sample, typename MeanFeature>
    struct lazy_variance_impl;

    template<typename Sample, typename MeanFeature, typename Tag>
    struct variance_impl;

    template<typename Sample, typename Weight, typename VariateType, typename VariateTag>
    struct weighted_covariance_impl;

    template<typename Sample, typename Weight>
    struct weighted_density_impl;

    template<typename Sample, typename Weight>
    struct weighted_kurtosis_impl;

    template<typename Sample>
    struct weighted_median_impl;

    template<typename Sample>
    struct with_density_weighted_median_impl;

    template<typename Sample, typename Weight>
    struct with_p_square_cumulative_distribution_weighted_median_impl;

    template<typename Sample, typename Weight, typename Tag>
    struct weighted_mean_impl;

    template<typename Sample, typename Weight, typename Tag>
    struct immediate_weighted_mean_impl;

    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_peaks_over_threshold_impl;

    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_peaks_over_threshold_prob_impl;

    template<typename Sample, typename Weight>
    struct with_p_square_cumulative_distribution_weighted_median_impl;

    template<typename Sample, typename Weight>
    struct weighted_extended_p_square_impl;

    template<typename N, typename Sample, typename Weight>
    struct weighted_moment_impl;

    template<typename Sample, typename Weight>
    struct weighted_p_square_cumulative_distribution_impl;

    template<typename Sample, typename Weight, typename Impl>
    struct weighted_p_square_quantile_impl;

    template<typename Sample, typename Weight>
    struct weighted_skewness_impl;

    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_impl;

    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_kahan_impl;

    template<typename Sample, typename Weight, typename LeftRight>
    struct non_coherent_weighted_tail_mean_impl;

    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_tail_quantile_impl;

    template<typename Sample, typename Weight, typename Impl, typename LeftRight, typename VariateType>
    struct weighted_tail_variate_means_impl;

    template<typename Sample, typename Weight, typename MeanFeature>
    struct lazy_weighted_variance_impl;

    template<typename Sample, typename Weight, typename MeanFeature, typename Tag>
    struct weighted_variance_impl;

    template<typename Sample>
    struct rolling_window_plus1_impl;

    template<typename Sample>
    struct rolling_window_impl;

    template<typename Sample>
    struct rolling_sum_impl;

    template<typename Sample>
    struct rolling_count_impl;

    template<typename Sample>
    struct rolling_mean_impl;
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// stats
//      A more descriptive name for an MPL sequence of statistics.
template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature, mpl::na)>
struct stats;

template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature, mpl::na)>
struct with_error;

// modifiers for the mean and variance stats
struct lazy {};
struct immediate {};

// modifiers for the variance stat
// struct fast {};
// struct accurate {};

// modifiers for order
struct right {};
struct left {};
// typedef right default_order_tag_type;

// modifiers for the tail_variate_means stat
struct absolute {};
struct relative {};

// modifiers for median and weighted_median stats
struct with_density {};
struct with_p_square_cumulative_distribution {};
struct with_p_square_quantile {};

// modifiers for peaks_over_threshold stat
struct with_threshold_value {};
struct with_threshold_probability {};

// modifiers for extended_p_square_quantile and weighted_extended_p_square_quantile stats
struct weighted {};
struct unweighted {};
struct linear {};
struct quadratic {};

// modifiers for p_square_quantile
struct regular {};
struct for_median {};

// modifier for sum_kahan, sum_of_weights_kahan, sum_of_variates_kahan, weighted_sum_kahan
struct kahan {};

}} // namespace boost::accumulators

#endif

/* statistics_fwd.hpp
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
*/