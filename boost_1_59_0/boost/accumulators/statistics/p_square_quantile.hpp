///////////////////////////////////////////////////////////////////////////////
// p_square_quantile.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_QUANTILE_HPP_DE_01_01_2006

#include <cmath>
#include <functional>
#include <boost/array.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/serialization/boost_array.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // p_square_quantile_impl
    //  single quantile estimation
    /**
        @brief Single quantile estimation with the \f$P^2\f$ algorithm

        The \f$P^2\f$ algorithm estimates a quantile dynamically without storing samples. Instead of
        storing the whole sample cumulative distribution, only five points (markers) are stored. The heights
        of these markers are the minimum and the maximum of the samples and the current estimates of the
        \f$(p/2)\f$-, \f$p\f$- and \f$(1+p)/2\f$-quantiles. Their positions are equal to the number
        of samples that are smaller or equal to the markers. Each time a new samples is recorded, the
        positions of the markers are updated and if necessary their heights are adjusted using a piecewise-
        parabolic formula.

        For further details, see

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param quantile_probability
    */
    template<typename Sample, typename Impl>
    struct p_square_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef array<float_type, 5> array_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        p_square_quantile_impl(Args const &args)
          : p(is_same<Impl, for_median>::value ? float_type(0.5) : args[quantile_probability | float_type(0.5)])
          , heights()
          , actual_positions()
          , desired_positions()
          , positions_increments()
        {
            for(std::size_t i = 0; i < 5; ++i)
            {
                this->actual_positions[i] = i + float_type(1.);
            }

            this->desired_positions[0] = float_type(1.);
            this->desired_positions[1] = float_type(1.) + float_type(2.) * this->p;
            this->desired_positions[2] = float_type(1.) + float_type(4.) * this->p;
            this->desired_positions[3] = float_type(3.) + float_type(2.) * this->p;
            this->desired_positions[4] = float_type(5.);


            this->positions_increments[0] = float_type(0.);
            this->positions_increments[1] = this->p / float_type(2.);
            this->positions_increments[2] = this->p;
            this->positions_increments[3] = (float_type(1.) + this->p) / float_type(2.);
            this->positions_increments[4] = float_type(1.);
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            // accumulate 5 first samples
            if(cnt <= 5)
            {
                this->heights[cnt - 1] = args[sample];

                // complete the initialization of heights by sorting
                if(cnt == 5)
                {
                    std::sort(this->heights.begin(), this->heights.end());
                }
            }
            else
            {
                std::size_t sample_cell = 1; // k

                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
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

                // update positions of markers above sample_cell
                for(std::size_t i = sample_cell; i < 5; ++i)
                {
                    ++this->actual_positions[i];
                }

                // update desired positions of all markers
                for(std::size_t i = 0; i < 5; ++i)
                {
                    this->desired_positions[i] += this->positions_increments[i];
                }

                // adjust heights and actual positions of markers 1 to 3 if necessary
                for(std::size_t i = 1; i <= 3; ++i)
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

                    if((d >= float_type(1.) && dp > float_type(1.)) || (d <= float_type(-1.) && dm < float_type(-1.)))
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        // try adjusting heights[i] using p-squared formula
                        float_type h = this->heights[i] + sign_d / (dp - dm) * ((sign_d - dm) * hp
                                     + (dp - sign_d) * hm);

                        if(this->heights[i - 1] < h && h < this->heights[i + 1])
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if(d > float_type(0))
                            {
                                this->heights[i] += hp;
                            }
                            if(d < float_type(0))
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
        // TODO: do we need to split to load/save and verify that P did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & p;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
            ar & positions_increments;
        }

    private:
        float_type p;                    // the quantile probability p
        array_type heights;              // q_i
        array_type actual_positions;     // n_i
        array_type desired_positions;    // n'_i
        array_type positions_increments; // dn'_i
    };

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// tag::p_square_quantile
//
namespace tag
{
    struct p_square_quantile
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::p_square_quantile_impl<mpl::_1, regular> impl;
    };
    struct p_square_quantile_for_median
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::p_square_quantile_impl<mpl::_1, for_median> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::p_square_quantile
// extract::p_square_quantile_for_median
//
namespace extract
{
    extractor<tag::p_square_quantile> const p_square_quantile = {};
    extractor<tag::p_square_quantile_for_median> const p_square_quantile_for_median = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(p_square_quantile)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(p_square_quantile_for_median)
}

using extract::p_square_quantile;
using extract::p_square_quantile_for_median;

// So that p_square_quantile can be automatically substituted with
// weighted_p_square_quantile when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::p_square_quantile>
{
    typedef tag::weighted_p_square_quantile type;
};

template<>
struct feature_of<tag::weighted_p_square_quantile>
  : feature_of<tag::p_square_quantile>
{
};

}} // namespace boost::accumulators

#endif

/* p_square_quantile.hpp
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
*/