///////////////////////////////////////////////////////////////////////////////
// weighted_median.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEDIAN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEDIAN_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/weighted_p_square_quantile.hpp>
#include <boost/accumulators/statistics/weighted_density.hpp>
#include <boost/accumulators/statistics/weighted_p_square_cumul_dist.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the \f$P^2\f$ quantile estimator

        The \f$P^2\f$ algorithm for weighted samples is invoked with a quantile probability of 0.5.
    */
    template<typename Sample>
    struct weighted_median_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        weighted_median_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return weighted_p_square_quantile_for_median(args);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // with_density_weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the density estimator

        The algorithm determines the bin in which the \f$0.5*cnt\f$-th sample lies, \f$cnt\f$ being
        the total number of samples. It returns the approximate horizontal position of this sample,
        based on a linear interpolation inside the bin.
    */
    template<typename Sample>
    struct with_density_weighted_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        with_density_weighted_median_impl(Args const &args)
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
                range_type histogram = weighted_density(args);
                typename range_type::iterator it = histogram.begin();
                while (this->sum < 0.5 * cnt)
                {
                    this->sum += it->second * cnt;
                    ++it;
                }
                --it;
                float_type over = numeric::fdiv(this->sum - 0.5 * cnt, it->second * cnt);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
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
    // with_p_square_cumulative_distribution_weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the \f$P^2\f$ cumulative distribution estimator

        The algorithm determines the first (leftmost) bin with a height exceeding 0.5. It
        returns the approximate horizontal position of where the cumulative distribution
        equals 0.5, based on a linear interpolation inside the bin.
    */
    template<typename Sample, typename Weight>
    struct with_p_square_cumulative_distribution_weighted_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        with_p_square_cumulative_distribution_weighted_median_impl(dont_care)
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

                range_type histogram = weighted_p_square_cumulative_distribution(args);
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
// tag::weighted_median
// tag::with_density_weighted_median
// tag::with_p_square_cumulative_distribution_weighted_median
//
namespace tag
{
    struct weighted_median
      : depends_on<weighted_p_square_quantile_for_median>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_median_impl<mpl::_1> impl;
    };
    struct with_density_weighted_median
      : depends_on<count, weighted_density>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_density_weighted_median_impl<mpl::_1> impl;
    };
    struct with_p_square_cumulative_distribution_weighted_median
      : depends_on<weighted_p_square_cumulative_distribution>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_p_square_cumulative_distribution_weighted_median_impl<mpl::_1, mpl::_2> impl;
    };

}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_median
//
namespace extract
{
    extractor<tag::median> const weighted_median = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_median)
}

using extract::weighted_median;
// weighted_median(with_p_square_quantile) -> weighted_median
template<>
struct as_feature<tag::weighted_median(with_p_square_quantile)>
{
    typedef tag::weighted_median type;
};

// weighted_median(with_density) -> with_density_weighted_median
template<>
struct as_feature<tag::weighted_median(with_density)>
{
    typedef tag::with_density_weighted_median type;
};

// weighted_median(with_p_square_cumulative_distribution) -> with_p_square_cumulative_distribution_weighted_median
template<>
struct as_feature<tag::weighted_median(with_p_square_cumulative_distribution)>
{
    typedef tag::with_p_square_cumulative_distribution_weighted_median type;
};

}} // namespace boost::accumulators

#endif

/* weighted_median.hpp
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
*/