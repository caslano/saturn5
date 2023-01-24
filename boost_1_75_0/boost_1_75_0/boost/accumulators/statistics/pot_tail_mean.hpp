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
InPA9a2sh0vP4qGjBPFvGnHOy4z9BHEzpSItZL6p+TOLNX9wGnZ6lpTZ4JbvdNGHwcw3pU56ojhHHjENXrQ74ddfbgpy6cHHXsnlXFRELZTkwyBJM7EqsULQpByi3SFb5TQL4Ind52Idz4eJ+D/my4EmsQIaMs8FZwae4cHMo8ozObxdt+dgvIoLe6xpHpQ56VNvJw5oPnykEFgOL0Aj8fadHLi3Rdz3t8O4G6H93fAKegQ9Ue72bIkHJOG+YZY03kIEH+uV6uHRwYYsPGMyzKqSp1hBrs2nB1qQ0rF2wrYxysl79cNMhWWBZ06hi/CKMuVeYF86wbw/UJFub+vU/FeUfgrFcQPeIt3phUdwZ8Iry3iWAvz7JP8Ww8DDl4hAMtGzLpi5VnnHQ6Omv488rLEa2MkPUIVStoio6Qhe8OgaEF3v/S1eePIyvDDgqRi7ZwBBTNCtaQwM6nDa3YVraQTq9jzGWYsLFyzywtfOI4sfmvvIg3MSDWm8qIW7FCOt/Enl79Sgej8+K8dnK+mzhx7xEvn6B7w4nEsvjuPFqfNc3/0LFswnfDmx6F5/8zhh3btuIM3xwtpxOMibJywf5W++R1ifSk+F9iC6QZ/Nnk013nWHobAfcnpzxwrmL7jPa2hD5vPx5nYqW5iL1Cqk7kVqGaU84RnqvNxIPSmDDfx30OChOASjoyosCeoI+9hD1O2bc9HG/AWPzE2k
*/