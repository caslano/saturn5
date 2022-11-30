///////////////////////////////////////////////////////////////////////////////
// extended_p_square.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_EXTENDED_SINGLE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_EXTENDED_SINGLE_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/times2_iterator.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{
///////////////////////////////////////////////////////////////////////////////
// probabilities named parameter
//
BOOST_PARAMETER_NESTED_KEYWORD(tag, extended_p_square_probabilities, probabilities)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(extended_p_square_probabilities)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // extended_p_square_impl
    //  multiple quantile estimation
    /**
        @brief Multiple quantile estimation with the extended \f$P^2\f$ algorithm

        Extended \f$P^2\f$ algorithm for estimation of several quantiles without storing samples.
        Assume that \f$m\f$ quantiles \f$\xi_{p_1}, \ldots, \xi_{p_m}\f$ are to be estimated.
        Instead of storing the whole sample cumulative distribution, the algorithm maintains only
        \f$m+2\f$ principal markers and \f$m+1\f$ middle markers, whose positions are updated
        with each sample and whose heights are adjusted (if necessary) using a piecewise-parablic
        formula. The heights of these central markers are the current estimates of the quantiles
        and returned as an iterator range.

        For further details, see

        K. E. E. Raatikainen, Simultaneous estimation of several quantiles, Simulation, Volume 49,
        Number 4 (October), 1986, p. 159-164.

        The extended \f$ P^2 \f$ algorithm generalizes the \f$ P^2 \f$ algorithm of

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param extended_p_square_probabilities A vector of quantile probabilities.
    */
    template<typename Sample>
    struct extended_p_square_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<
            detail::lvalue_index_iterator<
                permutation_iterator<
                    typename array_type::const_iterator
                  , detail::times2_iterator
                >
            >
        > result_type;

        template<typename Args>
        extended_p_square_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
          , heights(2 * probabilities.size() + 3)
          , actual_positions(heights.size())
          , desired_positions(heights.size())
          , positions_increments(heights.size())
        {
            std::size_t num_quantiles = this->probabilities.size();
            std::size_t num_markers = this->heights.size();

            for(std::size_t i = 0; i < num_markers; ++i)
            {
                this->actual_positions[i] = i + 1;
            }

            this->positions_increments[0] = 0.;
            this->positions_increments[num_markers - 1] = 1.;

            for(std::size_t i = 0; i < num_quantiles; ++i)
            {
                this->positions_increments[2 * i + 2] = probabilities[i];
            }

            for(std::size_t i = 0; i <= num_quantiles; ++i)
            {
                this->positions_increments[2 * i + 1] =
                    0.5 * (this->positions_increments[2 * i] + this->positions_increments[2 * i + 2]);
            }

            for(std::size_t i = 0; i < num_markers; ++i)
            {
                this->desired_positions[i] = 1. + 2. * (num_quantiles + 1.) * this->positions_increments[i];
            }
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            // m+2 principal markers and m+1 middle markers
            std::size_t num_markers = 2 * this->probabilities.size() + 3;

            // first accumulate num_markers samples
            if(cnt <= num_markers)
            {
                this->heights[cnt - 1] = args[sample];

                // complete the initialization of heights by sorting
                if(cnt == num_markers)
                {
                    std::sort(this->heights.begin(), this->heights.end());
                }
            }
            else
            {
                std::size_t sample_cell = 1;

                // find cell k = sample_cell such that heights[k-1] <= sample < heights[k]
                if(args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    sample_cell = 1;
                }
                else if(args[sample] >= this->heights[num_markers - 1])
                {
                    this->heights[num_markers - 1] = args[sample];
                    sample_cell = num_markers - 1;
                }
                else
                {
                    typedef typename array_type::iterator iterator;
                    iterator it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // update actual positions of all markers above sample_cell index
                for(std::size_t i = sample_cell; i < num_markers; ++i)
                {
                    ++this->actual_positions[i];
                }

                // update desired positions of all markers
                for(std::size_t i = 0; i < num_markers; ++i)
                {
                    this->desired_positions[i] += this->positions_increments[i];
                }

                // adjust heights and actual positions of markers 1 to num_markers-2 if necessary
                for(std::size_t i = 1; i <= num_markers - 2; ++i)
                {
                    // offset to desired position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i+1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i-1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i+1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i-1] - this->heights[i]) / dm;

                    if((d >= 1 && dp > 1) || (d <= -1 && dm < -1))
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        float_type h = this->heights[i] + sign_d / (dp - dm) * ((sign_d - dm)*hp
                                     + (dp - sign_d) * hm);

                        // try adjusting heights[i] using p-squared formula
                        if(this->heights[i - 1] < h && h < this->heights[i + 1])
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if(d > 0)
                            {
                                this->heights[i] += hp;
                            }
                            if(d < 0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }

        result_type result(dont_care) const
        {
            // for i in [1,probabilities.size()], return heights[i * 2]
            detail::times2_iterator idx_begin = detail::make_times2_iterator(1);
            detail::times2_iterator idx_end = detail::make_times2_iterator(this->probabilities.size() + 1);

            return result_type(
                make_permutation_iterator(this->heights.begin(), idx_begin)
              , make_permutation_iterator(this->heights.begin(), idx_end)
            );
        }

    public:
        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that the parameters did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & probabilities;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
            ar & positions_increments;
        }

    private:
        array_type probabilities;         // the quantile probabilities
        array_type heights;               // q_i
        array_type actual_positions;      // n_i
        array_type desired_positions;     // d_i
        array_type positions_increments;  // f_i
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::extended_p_square
//
namespace tag
{
    struct extended_p_square
      : depends_on<count>
      , extended_p_square_probabilities
    {
        typedef accumulators::impl::extended_p_square_impl<mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::extended_p_square::probabilities named parameter
        static boost::parameter::keyword<tag::probabilities> const probabilities;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::extended_p_square
//
namespace extract
{
    extractor<tag::extended_p_square> const extended_p_square = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(extended_p_square)
}

using extract::extended_p_square;

// So that extended_p_square can be automatically substituted with
// weighted_extended_p_square when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::extended_p_square>
{
    typedef tag::weighted_extended_p_square type;
};

template<>
struct feature_of<tag::weighted_extended_p_square>
  : feature_of<tag::extended_p_square>
{
};

}} // namespace boost::accumulators

#endif

/* extended_p_square.hpp
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
*/