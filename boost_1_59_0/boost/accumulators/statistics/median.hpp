///////////////////////////////////////////////////////////////////////////////
// median.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MEDIAN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MEDIAN_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/p_square_quantile.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/accumulators/statistics/p_square_cumul_dist.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // median_impl
    //
    /**
        @brief Median estimation based on the \f$P^2\f$ quantile estimator

        The \f$P^2\f$ algorithm is invoked with a quantile probability of 0.5.
    */
    template<typename Sample>
    struct median_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        median_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return p_square_quantile_for_median(args);
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };
    ///////////////////////////////////////////////////////////////////////////////
    // with_density_median_impl
    //
    /**
        @brief Median estimation based on the density estimator

        The algorithm determines the bin in which the \f$0.5*cnt\f$-th sample lies, \f$cnt\f$ being
        the total number of samples. It returns the approximate horizontal position of this sample,
        based on a linear interpolation inside the bin.
    */
    template<typename Sample>
    struct with_density_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        with_density_median_impl(Args const &args)
          : sum(numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , is_dirty(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                std::size_t cnt = count(args);
                range_type histogram = density(args);
                typename range_type::iterator it = histogram.begin();
                while (this->sum < 0.5 * cnt)
                {
                    this->sum += it->second * cnt;
                    ++it;
                }
                --it;
                float_type over = numeric::fdiv(this->sum - 0.5 * cnt, it->second * cnt);
                this->median = it->first * over + (it + 1)->first * (1. - over);
            }

            return this->median;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
            ar & is_dirty;
            ar & median;
        }


    private:
        mutable float_type sum;
        mutable bool is_dirty;
        mutable float_type median;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // with_p_square_cumulative_distribution_median_impl
    //
    /**
        @brief Median estimation based on the \f$P^2\f$ cumulative distribution estimator

        The algorithm determines the first (leftmost) bin with a height exceeding 0.5. It
        returns the approximate horizontal position of where the cumulative distribution
        equals 0.5, based on a linear interpolation inside the bin.
    */
    template<typename Sample>
    struct with_p_square_cumulative_distribution_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        with_p_square_cumulative_distribution_median_impl(dont_care)
          : is_dirty(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                range_type histogram = p_square_cumulative_distribution(args);
                typename range_type::iterator it = histogram.begin();
                while (it->second < 0.5)
                {
                    ++it;
                }
                float_type over = numeric::fdiv(it->second - 0.5, it->second - (it - 1)->second);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }
        
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & is_dirty;
            ar & median;
        }

    private:

        mutable bool is_dirty;
        mutable float_type median;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::median
// tag::with_densisty_median
// tag::with_p_square_cumulative_distribution_median
//
namespace tag
{
    struct median
      : depends_on<p_square_quantile_for_median>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::median_impl<mpl::_1> impl;
    };
    struct with_density_median
      : depends_on<count, density>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_density_median_impl<mpl::_1> impl;
    };
    struct with_p_square_cumulative_distribution_median
      : depends_on<p_square_cumulative_distribution>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_p_square_cumulative_distribution_median_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::median
// extract::with_density_median
// extract::with_p_square_cumulative_distribution_median
//
namespace extract
{
    extractor<tag::median> const median = {};
    extractor<tag::with_density_median> const with_density_median = {};
    extractor<tag::with_p_square_cumulative_distribution_median> const with_p_square_cumulative_distribution_median = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(median)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(with_density_median)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(with_p_square_cumulative_distribution_median)
}

using extract::median;
using extract::with_density_median;
using extract::with_p_square_cumulative_distribution_median;

// median(with_p_square_quantile) -> median
template<>
struct as_feature<tag::median(with_p_square_quantile)>
{
    typedef tag::median type;
};

// median(with_density) -> with_density_median
template<>
struct as_feature<tag::median(with_density)>
{
    typedef tag::with_density_median type;
};

// median(with_p_square_cumulative_distribution) -> with_p_square_cumulative_distribution_median
template<>
struct as_feature<tag::median(with_p_square_cumulative_distribution)>
{
    typedef tag::with_p_square_cumulative_distribution_median type;
};

// for the purposes of feature-based dependency resolution,
// with_density_median and with_p_square_cumulative_distribution_median
// provide the same feature as median
template<>
struct feature_of<tag::with_density_median>
  : feature_of<tag::median>
{
};

template<>
struct feature_of<tag::with_p_square_cumulative_distribution_median>
  : feature_of<tag::median>
{
};

// So that median can be automatically substituted with
// weighted_median when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::median>
{
    typedef tag::weighted_median type;
};

template<>
struct feature_of<tag::weighted_median>
  : feature_of<tag::median>
{
};

// So that with_density_median can be automatically substituted with
// with_density_weighted_median when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::with_density_median>
{
    typedef tag::with_density_weighted_median type;
};

template<>
struct feature_of<tag::with_density_weighted_median>
  : feature_of<tag::with_density_median>
{
};

// So that with_p_square_cumulative_distribution_median can be automatically substituted with
// with_p_square_cumulative_distribution_weighted_median when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::with_p_square_cumulative_distribution_median>
{
    typedef tag::with_p_square_cumulative_distribution_weighted_median type;
};

template<>
struct feature_of<tag::with_p_square_cumulative_distribution_weighted_median>
  : feature_of<tag::with_p_square_cumulative_distribution_median>
{
};

}} // namespace boost::accumulators

#endif

/* median.hpp
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
*/