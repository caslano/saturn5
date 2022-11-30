///////////////////////////////////////////////////////////////////////////////
// weighted_p_square_cumul_dist.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_P_SQUARE_CUMUL_DIST_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_P_SQUARE_CUMUL_DIST_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/range.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/p_square_cumul_dist.hpp> // for named parameter p_square_cumulative_distribution_num_cells

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_p_square_cumulative_distribution_impl
    //  cumulative distribution calculation (as histogram)
    /**
        @brief Histogram calculation of the cumulative distribution with the \f$P^2\f$ algorithm for weighted samples

        A histogram of the sample cumulative distribution is computed dynamically without storing samples
        based on the \f$ P^2 \f$ algorithm for weighted samples. The returned histogram has a specifiable
        amount (num_cells) equiprobable (and not equal-sized) cells.

        Note that applying importance sampling results in regions to be more and other regions to be less
        accurately estimated than without importance sampling, i.e., with unweighted samples.

        For further details, see

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param p_square_cumulative_distribution_num_cells
    */
    template<typename Sample, typename Weight>
    struct weighted_p_square_cumulative_distribution_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<typename histogram_type::iterator> result_type;

        template<typename Args>
        weighted_p_square_cumulative_distribution_impl(Args const &args)
          : num_cells(args[p_square_cumulative_distribution_num_cells])
          , heights(num_cells + 1)
          , actual_positions(num_cells + 1)
          , desired_positions(num_cells + 1)
          , histogram(num_cells + 1)
          , is_dirty(true)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty = true;

            std::size_t cnt = count(args);
            std::size_t sample_cell = 1; // k
            std::size_t b = this->num_cells;

            // accumulate num_cells + 1 first samples
            if (cnt <= b + 1)
            {
                this->heights[cnt - 1] = args[sample];
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights by sorting
                if (cnt == b + 1)
                {
                    //std::sort(this->heights.begin(), this->heights.end());

                    // TODO: we need to sort the initial samples (in heights) in ascending order and
                    // sort their weights (in actual_positions) the same way. The following lines do
                    // it, but there must be a better and more efficient way of doing this.
                    typename array_type::iterator it_begin, it_end, it_min;

                    it_begin = this->heights.begin();
                    it_end   = this->heights.end();

                    std::size_t pos = 0;

                    while (it_begin != it_end)
                    {
                        it_min = std::min_element(it_begin, it_end);
                        std::size_t d = std::distance(it_begin, it_min);
                        std::swap(*it_begin, *it_min);
                        std::swap(this->actual_positions[pos], this->actual_positions[pos + d]);
                        ++it_begin;
                        ++pos;
                    }

                    // calculate correct initial actual positions
                    for (std::size_t i = 1; i < b; ++i)
                    {
                        this->actual_positions[i] += this->actual_positions[i - 1];
                    }
                }
            }
            else
            {
                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if (this->heights[b] <= args[sample])
                {
                    this->heights[b] = args[sample];
                    sample_cell = b;
                }
                else
                {
                    typename array_type::iterator it;
                    it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // increment positions of markers above sample_cell
                for (std::size_t i = sample_cell; i < b + 1; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // determine desired marker positions
                for (std::size_t i = 1; i < b + 1; ++i)
                {
                    this->desired_positions[i] = this->actual_positions[0]
                                               + numeric::fdiv((i-1) * (sum_of_weights(args) - this->actual_positions[0]), b);
                }

                // adjust heights of markers 2 to num_cells if necessary
                for (std::size_t i = 1; i < b; ++i)
                {
                    // offset to desire position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if ( ( d >= 1. && dp > 1. ) || ( d <= -1. && dm < -1. ) )
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        // try adjusting heights[i] using p-squared formula
                        float_type h = this->heights[i] + sign_d / (dp - dm) * ( (sign_d - dm) * hp + (dp - sign_d) * hm );

                        if ( this->heights[i - 1] < h && h < this->heights[i + 1] )
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if (d>0)
                            {
                                this->heights[i] += hp;
                            }
                            if (d<0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                // creates a vector of std::pair where each pair i holds
                // the values heights[i] (x-axis of histogram) and
                // actual_positions[i] / sum_of_weights (y-axis of histogram)

                for (std::size_t i = 0; i < this->histogram.size(); ++i)
                {
                    this->histogram[i] = std::make_pair(this->heights[i], numeric::fdiv(this->actual_positions[i], sum_of_weights(args)));
                }
            }

            return make_iterator_range(this->histogram);
        }

        // make this accumulator serializeable
        // TODO split to save/load and check on parameters provided in ctor
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & num_cells;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
            ar & histogram;
            ar & is_dirty; 
        }

    private:
        std::size_t num_cells;            // number of cells b
        array_type  heights;              // q_i
        array_type  actual_positions;     // n_i
        array_type  desired_positions;    // n'_i
        mutable histogram_type histogram; // histogram
        mutable bool is_dirty;
    };

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_p_square_cumulative_distribution
//
namespace tag
{
    struct weighted_p_square_cumulative_distribution
      : depends_on<count, sum_of_weights>
      , p_square_cumulative_distribution_num_cells
    {
        typedef accumulators::impl::weighted_p_square_cumulative_distribution_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_p_square_cumulative_distribution
//
namespace extract
{
    extractor<tag::weighted_p_square_cumulative_distribution> const weighted_p_square_cumulative_distribution = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_p_square_cumulative_distribution)
}

using extract::weighted_p_square_cumulative_distribution;

}} // namespace boost::accumulators

#endif

/* weighted_p_square_cumul_dist.hpp
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
*/