///////////////////////////////////////////////////////////////////////////////
// p_square_cumulative_distribution.hpp
//
//  Copyright 2005 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/parameter/keyword.hpp>
#include <boost/range.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace accumulators
{
///////////////////////////////////////////////////////////////////////////////
// num_cells named parameter
//
BOOST_PARAMETER_NESTED_KEYWORD(tag, p_square_cumulative_distribution_num_cells, num_cells)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(p_square_cumulative_distribution_num_cells)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // p_square_cumulative_distribution_impl
    //  cumulative_distribution calculation (as histogram)
    /**
        @brief Histogram calculation of the cumulative distribution with the \f$P^2\f$ algorithm

        A histogram of the sample cumulative distribution is computed dynamically without storing samples
        based on the \f$ P^2 \f$ algorithm. The returned histogram has a specifiable amount (num_cells)
        equiprobable (and not equal-sized) cells.

        For further details, see

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param p_square_cumulative_distribution_num_cells.
    */
    template<typename Sample>
    struct p_square_cumulative_distribution_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        // for boost::result_of
        typedef iterator_range<typename histogram_type::iterator> result_type;

        template<typename Args>
        p_square_cumulative_distribution_impl(Args const &args)
          : num_cells(args[p_square_cumulative_distribution_num_cells])
          , heights(num_cells + 1)
          , actual_positions(num_cells + 1)
          , desired_positions(num_cells + 1)
          , positions_increments(num_cells + 1)
          , histogram(num_cells + 1)
          , is_dirty(true)
        {
            std::size_t b = this->num_cells;

            for (std::size_t i = 0; i < b + 1; ++i)
            {
                this->actual_positions[i] = i + 1.;
                this->desired_positions[i] = i + 1.;
                this->positions_increments[i] = numeric::fdiv(i, b);
            }
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

                // complete the initialization of heights by sorting
                if (cnt == b + 1)
                {
                    std::sort(this->heights.begin(), this->heights.end());
                }
            }
            else
            {
                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
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
                    ++this->actual_positions[i];
                }

                // update desired position of markers 2 to num_cells + 1
                // (desired position of first marker is always 1)
                for (std::size_t i = 1; i < b + 1; ++i)
                {
                    this->desired_positions[i] += this->positions_increments[i];
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
                // actual_positions[i] / cnt (y-axis of histogram)

                std::size_t cnt = count(args);

                for (std::size_t i = 0; i < this->histogram.size(); ++i)
                {
                    this->histogram[i] = std::make_pair(this->heights[i], numeric::fdiv(this->actual_positions[i], cnt));
                }
            }
            //return histogram;
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
            ar & positions_increments;
            ar & histogram;
            ar & is_dirty; 
        }

    private:
        std::size_t num_cells;            // number of cells b
        array_type  heights;              // q_i
        array_type  actual_positions;     // n_i
        array_type  desired_positions;    // n'_i
        array_type  positions_increments; // dn'_i
        mutable histogram_type histogram; // histogram
        mutable bool is_dirty;
    };

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// tag::p_square_cumulative_distribution
//
namespace tag
{
    struct p_square_cumulative_distribution
      : depends_on<count>
      , p_square_cumulative_distribution_num_cells
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::p_square_cumulative_distribution_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::p_square_cumulative_distribution
//
namespace extract
{
    extractor<tag::p_square_cumulative_distribution> const p_square_cumulative_distribution = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(p_square_cumulative_distribution)
}

using extract::p_square_cumulative_distribution;

// So that p_square_cumulative_distribution can be automatically substituted with
// weighted_p_square_cumulative_distribution when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::p_square_cumulative_distribution>
{
    typedef tag::weighted_p_square_cumulative_distribution type;
};

template<>
struct feature_of<tag::weighted_p_square_cumulative_distribution>
  : feature_of<tag::p_square_cumulative_distribution>
{
};

}} // namespace boost::accumulators

#endif

/* p_square_cumul_dist.hpp
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
*/