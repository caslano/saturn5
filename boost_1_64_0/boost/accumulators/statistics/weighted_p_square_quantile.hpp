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
LQ5/ObVvdgqm6CozlM9XVGSVtKHHupPyi7z/5QMNqW2DCJkRWgNhswsFm61X+22gVVCG9bYqOjUefyZxA+i1hB9x8ivQ3HHit0o7ykR5ZkFyjdPXRqZBu724jQDuyIOGfZrf7k3XLMpZEF58cDLdR9uekM746FzSAs6chHPy6XJOvuwLPif/Cg/1mi2kGGfJUv4SnZVSn5Xxy6TOZGNIAhtLFVCB2j8l3mROq34Pn6JjBjvz/JSORMiaKb0z0rOUQdEO37VxRMtYvrOn1KlHAB6QqcvyvXSJfVWLePhW9Jc58urxbsoYGz3BDnu4qX78Jj9wGZcAxIMuX8GfXhuNzx2Wr1FCyg+GrxHXoBUwsVz7fFxC4D5UCPq64YzI6spbxVACvvHnwqNQGl1AWmoWk3FNj485oCDzc/NxMz8n8CtaPd6y0F9hXVaO/p+8J9GEpRAXqf+zlscWRykYrM6IQeY1ezWs8jjo5tD5od2f6V8TkIHIgYzIQAreoNcD5EzqvOWLtGOfrnLs0xdlijOpH9WNy+jYRzoGeBsUFcaS5k3aTrXbfBZ3zyIn8MpmWhbTQHMDth4ogIXljjj17t7xJlSSy3YmrCW7VYTk/6LdDYd3pkl/0QFIFQBeQQ8ErKIPqjnLCFSq0giH/k0/+Wa84Zt6tTN/M9iGhKQj8SZiXwBXb7yyv1KxU1DEm4S/Qr3usVp/xjbrzIuCYl/U11htPaS2Voba6tSXXo+E8KSdFTbnJ/Oj/eqgvtK0RyP1mX6qCqZv2x6hz6QRTBuqAvMFSI8Va85h4+tLQK50pTflyjgHnKWerp7HI1nQhvplZBT1RWbP6jjOgsulPiMZv4VPJ4bY5GRiUBKdSiCcinAqwpkIZyKci3AuwiMQHoFnPp75VhtsfNn6mx82zxwOPSgWJX/JN7mvdCgWR54jFdBcZi+9P4qxWNVuoK+rfZqzNLBNBKLDGwvo7ASpG9lqbqcvlWvzXXmZqep9PeNNCNdl2kyYHO6U7DS5322t3Zcb58+lAjo6BL8LrqRiJlIx3YIXu4rtPaXcFkX5RstEuQTQLIduhMwWdeoSEQ9gppywsf4J/OQ8+KdV2siaqUk2gjWLYfUgtaavQ8l06AlOTiiihPb+jZ56f0EyRedydDGil0+QBt64izSVZqjPLz6O8+GAfDYvANF2tdUnJLU/X3aiaBSK/mf5bPUApDQ633vI1xhYM77Z+BlhrUKe3XkP4ZPI9q8MtN+lrKDRppvT722sLzJcSi48Am+K6Iuzc5QqTA9MjBZ2/yalijpmYOMdk/mZdMysRXTFkFLOXaMMhfioSs18jeKABZ8pV8qb2WeN+v9aGeg/WpG3y8i6MZK5vUjlL8G/CY1rIWJu9rqIXDZeNLmpSI9RF8wPuGNsP+fTRLTgTKZ+dnBsnNrhVcC5yV76rOZO7Mru8aZje2tsav4VvB/o/ywl05YNtvn31PltA53vy52g9f/oQP+30/vfd80EbQyuYaW6FdCoM2MMaASu5RHgEibKINSc13/oSHciGJi29oNlce5E71BxSCJ6Dn/WFnFaFGPwOAzXQ59oGF399LXjmMmN/7gqdHDc1Fvv8cNFTcVU5z0mxFWE6r9WiH7GePgcbcnz9i30EL+8PhsTOGL/j8ivBPIXS/6j+yv5aYVG1G4nJQW5THvuNtYBHQGERzJNzG0oK7BYiWTIZ79be0I+RvSqI89P8gUIctgg7iMYkAYaxhZZyv22Gltxmf1d5r6tWQeyvPfbYC/LV2C5+t8a5z5Dm+Nt2Qt3T+RTTP2jrEVd8MZRh2n19T/LbVVuvEddhh0qy/uAzXvLPSTk7UdtemAj71ppNP63CEpn9Cw=
*/