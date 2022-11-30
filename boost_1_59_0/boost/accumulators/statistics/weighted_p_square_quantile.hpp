///////////////////////////////////////////////////////////////////////////////
// weighted_p_square_quantile.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_P_SQUARE_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_P_SQUARE_QUANTILE_HPP_DE_01_01_2006

#include <cmath>
#include <functional>
#include <boost/array.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>

namespace boost { namespace accumulators
{

namespace impl {
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_p_square_quantile_impl
    //  single quantile estimation with weighted samples
    /**
        @brief Single quantile estimation with the \f$P^2\f$ algorithm for weighted samples

        This version of the \f$P^2\f$ algorithm extends the \f$P^2\f$ algorithm to support weighted samples.
        The \f$P^2\f$ algorithm estimates a quantile dynamically without storing samples. Instead of
        storing the whole sample cumulative distribution, only five points (markers) are stored. The heights
        of these markers are the minimum and the maximum of the samples and the current estimates of the
        \f$(p/2)\f$-, \f$p\f$ - and \f$(1+p)/2\f$ -quantiles. Their positions are equal to the number
        of samples that are smaller or equal to the markers. Each time a new sample is added, the
        positions of the markers are updated and if necessary their heights are adjusted using a piecewise-
        parabolic formula.

        For further details, see

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param quantile_probability
    */
    template<typename Sample, typename Weight, typename Impl>
    struct weighted_p_square_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        typedef array<float_type, 5> array_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        weighted_p_square_quantile_impl(Args const &args)
          : p(is_same<Impl, for_median>::value ? 0.5 : args[quantile_probability | 0.5])
          , heights()
          , actual_positions()
          , desired_positions()
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            // accumulate 5 first samples
            if (cnt <= 5)
            {
                this->heights[cnt - 1] = args[sample];

                // In this initialization phase, actual_positions stores the weights of the
                // initial samples that are needed at the end of the initialization phase to
                // compute the correct initial positions of the markers.
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights and actual_positions by sorting
                if (cnt == 5)
                {
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
                    for (std::size_t i = 1; i < 5; ++i)
                    {
                        this->actual_positions[i] += this->actual_positions[i - 1];
                    }
                }
            }
            else
            {
                std::size_t sample_cell = 1; // k

                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if (this->heights[4] <= args[sample])
                {
                    this->heights[4] = args[sample];
                    sample_cell = 4;
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

                // increment positions of markers above sample_cell
                for (std::size_t i = sample_cell; i < 5; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // update desired positions for all markers
                this->desired_positions[0] = this->actual_positions[0];
                this->desired_positions[1] = (sum_of_weights(args) - this->actual_positions[0])
                                           * this->p/2. + this->actual_positions[0];
                this->desired_positions[2] = (sum_of_weights(args) - this->actual_positions[0])
                                           * this->p + this->actual_positions[0];
                this->desired_positions[3] = (sum_of_weights(args) - this->actual_positions[0])
                                           * (1. + this->p)/2. + this->actual_positions[0];
                this->desired_positions[4] = sum_of_weights(args);

                // adjust height and actual positions of markers 1 to 3 if necessary
                for (std::size_t i = 1; i <= 3; ++i)
                {
                    // offset to desired positions
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

        result_type result(dont_care) const
        {
            return this->heights[2];
        }

        // make this accumulator serializeable
        // TODO split to save/load and check on parameters provided in ctor
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & p;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
        }

    private:
        float_type p;                    // the quantile probability p
        array_type heights;              // q_i
        array_type actual_positions;     // n_i
        array_type desired_positions;    // n'_i
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_p_square_quantile
//
namespace tag
{
    struct weighted_p_square_quantile
      : depends_on<count, sum_of_weights>
    {
        typedef accumulators::impl::weighted_p_square_quantile_impl<mpl::_1, mpl::_2, regular> impl;
    };
    struct weighted_p_square_quantile_for_median
      : depends_on<count, sum_of_weights>
    {
        typedef accumulators::impl::weighted_p_square_quantile_impl<mpl::_1, mpl::_2, for_median> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_p_square_quantile
// extract::weighted_p_square_quantile_for_median
//
namespace extract
{
    extractor<tag::weighted_p_square_quantile> const weighted_p_square_quantile = {};
    extractor<tag::weighted_p_square_quantile_for_median> const weighted_p_square_quantile_for_median = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_p_square_quantile)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_p_square_quantile_for_median)
}

using extract::weighted_p_square_quantile;
using extract::weighted_p_square_quantile_for_median;

}} // namespace boost::accumulators

#endif

/* weighted_p_square_quantile.hpp
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
*/