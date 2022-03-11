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