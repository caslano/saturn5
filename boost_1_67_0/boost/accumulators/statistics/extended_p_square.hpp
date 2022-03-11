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