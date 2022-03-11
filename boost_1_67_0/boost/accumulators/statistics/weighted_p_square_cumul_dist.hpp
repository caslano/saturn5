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