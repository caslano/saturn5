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
Wu9DWiWw11r0i/YqQKTFqOAzwZbdexQCG7ojT5yzJJFblgM6ri5y6/evkGDKOhNd5AUIMfU+KUtZbSXmQm9aSDYnHmcJWQShlzahc6iP9JyXBHxPIxxh+jR8A7/UcS/cx179FKz1WhVhet3SlhX3QMVUowH6AFnpGC7sLX3MEsJVs376X6PM2Hn81NCb+t0oSw0m6quepL/DHBzZD5HoD8q79G1RVjIHjXDo9yMhUSF/nPlnyjXWEYvMbi4S0E+JgvOnD0QR1RbG3iZgr/AcfQUUafTlH9eo92ZGj46QvuDDUr7Yx0ck39UXa0R1OsOkEddh82s7UBdbfFNdSVxXYbSuM7iuaVczfYK8aCKprGJSUQdf6SmkGcir/+o5YzQVniModSVh+Mg/NkUWf4N6mDAnLjEJ06+9JZh2/SjwFUutzGaJcYMUHrAgO73EglxtQ5Kh7wkWJOvPBDyGplYRM2IPAx3ff/LH+sU8qZkSO5CUCjnh5Wib/Fo9b9X9dHDJT3tvIb7XGrTvvNoO/ZonCLeI0HeDcT2fKMFZMgD9Met9Z0ka/gb+yenjnbOOZuJfTXdYzWBugbpFzmDbETBzkMi9lTtRxZ06wlBZ95TSlPYmDb0Tn2cvjZ3bwJ3RcBvEBTzHBuoR56wnyKNV0qI1CHPn12tNFjgVq8uHF4nVJZ9Wl0snhS7G6pI5QT8LZTVcj5kVNHftAlQRHJpqZHleZhnPC9IksSDdpMdRlrP1OU+ZG9HTaJ+TQ4S7hvi/NRSxAQ3GCNHfr6NRsJjo1DkCVkuiZaomUEE8+PEPCCK9BwilYT4OG2/iJx5loqZtjBTjdjG9sj05ay5NvWVzmcHm+UOzuCHu90EX3BSskSALQsEOr/axnvg3MYuexfP0HNnabvrq10AsNLALTwaKVUWgOMS9Uih6pUB/HNvY+u+As/ZXBp6XeY5ZvUHMZ2uQVg+90WYR4LnYSPyETPxnKyujJEgXOQKDsF0OcaDHAfoTO2GK4Y0whbDESR/6RHTlJctoFgA9F53Is5jOj6CNYYH+yau0Rui3vSmWjKJ7mBw5XV+ko7DjEAY9u9NyfpzFCvq3I1zyDSxl1d6hGo5bKDC5lds9ykFh62aJpqyzCCisSNN64g96o01/+l3ZdElz16xk4Hq90u7qZWa7mbNNuwUdyL1Ny8VZ+kPPoCkyxD9uk77lb8aScceFtGS8wgZSb+t3l5hT++mylsLoSnFNtJpEUQ1atmOpsSMsoKHwO2x2lEXhOD7f3xeFqwi8Fcug4LeLTS3HFYd053hofjy+pDyOJ2HJqz/wupiEd3lDEzYomi6E3jBsjCvq7tfuTPdrv0lt6OnX9sK2d1oCf2Et3kqsZ746+DZHYRKnVXNKIkWq8nomyU6ukXvY0VYWOaw9n25OWBHKflI/E/QL1lMrNG9RnWjeonol45Wqic/BkdEFXG432PRVI3/D0fi04uNtfGB78i/88Tt9uJmYxhXOuN7LI+Nih566mI020YWUT8yT+mWPCIq8miyCVtgR+U9EgvqBEJwaq6Q0VU8LyifVtxlDh0eeRFJK8IxM0JfViZkORD0ULYVSlMgUu/dyChdSTGmZYpxMUSdSeGhTc4KMR+qrZFXnyWQvi2Rqq2QjZLLeMtk9SKYOnpSLcoENAyeUYjIEosgwUGY4DfL2wZPGOO99gOfQXf7Q+eHwERbo6xYFS0tLm760vRvebSNlYT9b7Y2rnEO+LspA9lNXHMHZIYNnNB6L+kJ5dq6II1yohncIbB6YmUt3VS8/whJZicx37z7CMmTSGCQbChu0jBynd41e/ZAoaO2eCC6dXolo55w7IxF5yzoyvbJc1HjE8yJh5R4=
*/