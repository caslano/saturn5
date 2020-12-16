///////////////////////////////////////////////////////////////////////////////
// weighted_extended_p_square.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_EXTENDED_P_SQUARE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_EXTENDED_P_SQUARE_HPP_DE_01_01_2006

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
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/times2_iterator.hpp>
#include <boost/accumulators/statistics/extended_p_square.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_extended_p_square_impl
    //  multiple quantile estimation with weighted samples
    /**
        @brief Multiple quantile estimation with the extended \f$P^2\f$ algorithm for weighted samples

        This version of the extended \f$P^2\f$ algorithm extends the extended \f$P^2\f$ algorithm to
        support weighted samples. The extended \f$P^2\f$ algorithm dynamically estimates several
        quantiles without storing samples. Assume that \f$m\f$ quantiles
        \f$\xi_{p_1}, \ldots, \xi_{p_m}\f$ are to be estimated. Instead of storing the whole sample
        cumulative distribution, the algorithm maintains only \f$m+2\f$ principal markers and
        \f$m+1\f$ middle markers, whose positions are updated with each sample and whose heights
        are adjusted (if necessary) using a piecewise-parablic formula. The heights of the principal
        markers are the current estimates of the quantiles and are returned as an iterator range.

        For further details, see

        K. E. E. Raatikainen, Simultaneous estimation of several quantiles, Simulation, Volume 49,
        Number 4 (October), 1986, p. 159-164.

        The extended \f$ P^2 \f$ algorithm generalizes the \f$ P^2 \f$ algorithm of

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param extended_p_square_probabilities A vector of quantile probabilities.
    */
    template<typename Sample, typename Weight>
    struct weighted_extended_p_square_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
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
        weighted_extended_p_square_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
          , heights(2 * probabilities.size() + 3)
          , actual_positions(heights.size())
          , desired_positions(heights.size())
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);
            std::size_t sample_cell = 1; // k
            std::size_t num_quantiles = this->probabilities.size();

            // m+2 principal markers and m+1 middle markers
            std::size_t num_markers = 2 * num_quantiles + 3;

            // first accumulate num_markers samples
            if(cnt <= num_markers)
            {
                this->heights[cnt - 1] = args[sample];
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights (and actual_positions) by sorting
                if(cnt == num_markers)
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
                    for (std::size_t i = 1; i < num_markers; ++i)
                    {
                        actual_positions[i] += actual_positions[i - 1];
                    }
                }
            }
            else
            {
                if(args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if(args[sample] >= this->heights[num_markers - 1])
                {
                    this->heights[num_markers - 1] = args[sample];
                    sample_cell = num_markers - 1;
                }
                else
                {
                    // find cell k = sample_cell such that heights[k-1] <= sample < heights[k]

                    typedef typename array_type::iterator iterator;
                    iterator it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // update actual position of all markers above sample_cell
                for(std::size_t i = sample_cell; i < num_markers; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // compute desired positions
                {
                    this->desired_positions[0] = this->actual_positions[0];
                    this->desired_positions[num_markers - 1] = sum_of_weights(args);
                    this->desired_positions[1] = (sum_of_weights(args) - this->actual_positions[0]) * probabilities[0]
                                              / 2. + this->actual_positions[0];
                    this->desired_positions[num_markers - 2] = (sum_of_weights(args) - this->actual_positions[0])
                                                            * (probabilities[num_quantiles - 1] + 1.)
                                                            / 2. + this->actual_positions[0];

                    for (std::size_t i = 0; i < num_quantiles; ++i)
                    {
                        this->desired_positions[2 * i + 2] = (sum_of_weights(args) - this->actual_positions[0])
                                                          * probabilities[i] + this->actual_positions[0];
                    }

                    for (std::size_t i = 1; i < num_quantiles; ++i)
                    {
                        this->desired_positions[2 * i + 1] = (sum_of_weights(args) - this->actual_positions[0])
                                                      * (probabilities[i - 1] + probabilities[i])
                                                      / 2. + this->actual_positions[0];
                    }
                }

                // adjust heights and actual_positions of markers 1 to num_markers - 2 if necessary
                for (std::size_t i = 1; i <= num_markers - 2; ++i)
                {
                    // offset to desired position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if((d >= 1 && dp > 1) || (d <= -1 && dm < -1))
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        float_type h = this->heights[i] + sign_d / (dp - dm) * ((sign_d - dm)*hp + (dp - sign_d) * hm);

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

        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that the parameters did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & probabilities;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
        }

    private:
        array_type probabilities;         // the quantile probabilities
        array_type heights;               // q_i
        array_type actual_positions;      // n_i
        array_type desired_positions;     // d_i
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_extended_p_square
//
namespace tag
{
    struct weighted_extended_p_square
      : depends_on<count, sum_of_weights>
      , extended_p_square_probabilities
    {
        typedef accumulators::impl::weighted_extended_p_square_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_extended_p_square
//
namespace extract
{
    extractor<tag::weighted_extended_p_square> const weighted_extended_p_square = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_extended_p_square)
}

using extract::weighted_extended_p_square;

}} // namespace boost::accumulators

#endif

/* weighted_extended_p_square.hpp
oG41aWLPn0u1ZbdBlHB2h4MhRLsMEcKe9S4wJbmmctk9K5Ydz2XnpkXLpTY9widtaI4xJlPX40CjFIn78IjtCG3MhnxQWk2tlIORjLzHuQkx0SYQp/RvCZlS7ajLqR7Eeh9nxfhAFw5zgXGk+bInCwlip4bq5u8svOcKb/ZTeME1O3S3Fmih8SSJd0aCTHzGCf+JEGkWt9N0OJVlncncS+y50hNYaBNpjSZEqEzpiNeQ3nxHz4CI17//CofpVa9Ht3vDBk16c31vOlM4CYY1iB/UKB1HzCCDfd5ksgIaqG2oOnXUjGGtMAYr0pXWVy0qBC93snMmkGHgDRozpa0po/pJnBFR1rFLogN/u9rxYq0Y3j9AKMl3v+Ey8tTyW9FNgpOw0Exu1Hd6tBv1MtWnGVOgv8zmdsxeS0LpXcCQMIF6Io2poE/f0e8/lnD/d4dX1cj9kjyEVqOnHR4aQjuIu34UJwu8Ja/obfANdt4Gz7q+Tszi6gjDRniZSoXmFkN0kfYl3sYnKG1GK0fkmoP93lU1vP6vy+A82F5CDv3xUFYyBQ96R4y9Ca8BYil6W6SjC//2Y0CxICkeMG++AR3YGeEDy4dnXIrw3+k075V/9/s+eNcA4b8rH/51S+5UYIT2mNOLfjup8sw/Pyd/bkk3yZ/svETtuoEFdrKrWkW8aC8u/5jFD5acP/v31sDh7ZBFmNfnWhmQANX7yKGBt45DCOc1lYsfc2+nrh4tDLMbi0nGClFXq13P1YopeSwatTVFzeKoOUkcdZZEfV8tRdTS+1lxXmekPTC/jBZbd8E5RTa9TUF1EbmM5+AVvmABDx38IUA9Vgfd1CE5xHsNvABRsxrLXoOfslEjLmQ9ZSGeocnRC3xv4N194eVEVRLYL70Q/rT9VaUqJ8nDXRVdWXVyRwQYvZx1WPRydl14oQj5QQVTTJIMsHxzqnjpydXhQRZR5F3NFryCvaMO/sQzoVinAObJiCKLbgxyD6N4KItRKAd9TPPpTBF1oIZbdJCm97ZeYxHQy+JPS1/2DEKypCVdehlBJDX3ZTfPucsCU5AKIhD6StRxnfzUbxwL6jiKn1Pfl10g2Ugvr+yrtXJUjgo+AxEKuZj0//9eJU1UP8GXHrHwFWG5XW8IO+POoOuODgrj5f2/6+XO73ZPoy1YJh/HL4B9DOzFL7tTf4vwiLwHEQVc7wu+9EUsi2cHafBkxyeBC00nl+vLibDBfJ1HM6ybva6TIwbQCfE7n64V47a0TUK/7RexjggfF8FQUmS2FRCUE0inmlbnsfnqkpc1x65di0njqXZRjn1UTb+SOTZZJILelAX5e+lqMObbjTD+y1gs2e4JpieotGbMGa4rzeVD5Ko7DpTrKO7FCWHBbTtKjVMLe8m8UpqhFvjkfkt3sS2J7xdZlqA1CDavfw0uxz7p3+WgG3hGU6EpwneY3pzF1JJNsvTPAgfzibUKDCDE9kGzZ5JsVkmd3kvn/eZIDjSdIBOUX4MPUpYuUM2lPm/RdtERZ7HHus9nPUla5/OAAi0Jlz0FRAc6JJGT7KnUi7RJeQtN+HdQAdkGBYCNMcKlLBRELh3U0p5c3UbEcLtjkagWdOEA5sCp7KJ4Pvda4DnOJNtPfU+XRYIfIssvollCkpZdPcSlSFT+3z2cWwrSHed0ox6RdCtM6ZZkicA9CsVRWoShJSW0fSgxRVMaif9pCx7OOduojrgv+lc+4fDv/Yj92cOd5HxLIVTVYUZUDDHxtNfb/6y+/nrJ1W3s18r6W10RT2E7auhj3XbyfZq3q0aMA4PuppAbmB7ZHCy3CW9J/y66b0Jc/romVL/aU5GolL1IjKsQIa09R/i7nVi8IbM=
*/