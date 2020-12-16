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
X+G0xjcsUxo5eBECg83VL4jtWfB6M+uyW1phvcPMKwHXR7aCjtse1hFoS1dE7fBUHFAqSm5JICuzwa2stmLpNh/NU6XCavN1orC3GBMVKyeReql4hHS0tY0Z+XvxinDakDWdX+1JiHVILK0Z33CJpjXjzPXah6vnA25eIXzHB034h77mCZ//PzDdmR7a2d54XirbogUTW9Nl7U7qaqJWOeGjEJvT4+MfF+48QXn89N0B1qfdYp3N8207ijx+8j+bI4/vq5f79iK93H5SriuPuEcqHeWJ8Pjcf/7m3GME/zhhx7H5xybkxf/6OIR/tO8KNHbDQp1/dGyNkBej4RHy4v2bQ9jHq177L5IXN8Y/XrE9kn/88u/Ntrfr8FmAf+yFPgy1t+v9Zu2pt7cbt+1EzmNe+Ch4RrLzVf2M5LotxzyPiVkWPCa59ZXmnMcMMNQ1OliXimhZTI1X9OTrwYrqXz4V5zHEH9SE8QffhIZXh4VvlHCkPvqujw2sg2j2ywltx+fkaLd6MzV/cBzeXV42W1U/5lxX20Se5y2hNdVMVfim9a8EV+R+3LT+1ZLG9K+M2k4lBv2rDjsDSk69NmuqTAsZh3QOBEWdZvrLOtb0b2Ilp3QMNusla7OL8Kc4upDxdnzYqN7VDHHxI5AIRM8hLHpXt7Cf1h0BkOZtCgFpOoIGkGpf0kG6Jwwk6FBq8Hykw1O6MahvpetHn2p9q5bG+Si7JsYUa9zlG/gK0uAeB15nisoKO1qXlV0+ZUD67oLEbFzJFefwr7D7q2r2OPMglGiwTDoX+yVUC+P9RWXjoxf6a+KQn7xUpSe0HVBbkIC8Dv9qyjl5Oxw19bDAL+jEWD/ul/zZX0ZXIIDGIrzNS64iaJhqhxo1mRCgTuusZeIDBzXE2BdLFVdYl7VLty673JxtXbaGql6kV51A8TDm/z4MIkRvQ4qFi1miF9MF8QBwRTT0IFe0qipaXXgH3tYq5a0q0Pzf28s/b2H3rLJktVrvWRlNoaxWa+Wx2k6uBWwlsXgy8WfOKrk6yuGptNgzVOvMK8GUsJYPmsNuswh79Qo2lg4J9qw7FT8j/nhmk4bW6+1YC3xWa3YoK0i1hH3I+obGkf7IWdi54NA7zNil0kJfeGOP00CF+BKzA3RrhUEf12hfafD/KOC58to4fKPi0nbCKoMWTQ72GqVc2awczlIOZxdvmpRih6DLlVdmnzKg18CCru+ZqSUZWye1RfwvjrwqXKSImTag90BrVn0WFvYcBLPJoU8nsxAuhUqtddZqxlArMN4dcOL0uppoyvGNMxdt4nkTi24hd2vWZVVTG/x80X80cVuHBhZE+ytr2uFYyaaUe6raDqylxOKv8D/uG7PO/gwvUxt+wP/u2zyr205toHR3O7vnUKbVV453O9ZQSbteTn8ZxRX0zab+3+KkS2+epfOuzeDTMe9L5iEvbuWZ7cOTruWrd8x3WXD0bs/40TpzMKaXsrmm5XJqOqm8Ubck2w+usBTcFCzwRikQl+INyaifPJhL6Y8OLWiN7AXRxXA19JZGPpDtQpH4QPOmkwpWfpbXplTolKZmi4mzo/c9a/01H6z7j/2sNnEAz+zTlTbhnS5PIsYJ4VSEUxHORDgT4VyEcyuaIf/cwFMPt75chlPI4V8lsnCz+h6IZRvNf72e/xLk74X8Pkc6f/LIX0M/Ucyh1WenbWK8RjMGzgHNLl/X6n2J5KDOMuFmcuOCv6F+B1yKOFptZAcv2jst1HL1NMJmnUrMEkrw7L5MIuxaTItgDLBRucWzh4Onl5hrbuSSy/fYUFdUQUt2GbM77tgFI7u5oIXdlzkA15SWf91CL1JqWGUeaAcGdeLV7lE=
*/