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