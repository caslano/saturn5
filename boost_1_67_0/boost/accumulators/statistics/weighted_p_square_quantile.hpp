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