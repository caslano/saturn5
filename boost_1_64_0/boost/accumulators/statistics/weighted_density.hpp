///////////////////////////////////////////////////////////////////////////////
// weighted_density.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_DENSITY_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_DENSITY_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/density.hpp> // for named parameters density_cache_size and density_num_bins
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_density_impl
    //  density histogram for weighted samples
    /**
        @brief Histogram density estimator for weighted samples

        The histogram density estimator returns a histogram of the sample distribution. The positions and sizes of the bins
        are determined using a specifiable number of cached samples (cache_size). The range between the minimum and the
        maximum of the cached samples is subdivided into a specifiable number of bins (num_bins) of same size. Additionally,
        an under- and an overflow bin is added to capture future under- and overflow samples. Once the bins are determined,
        the cached samples and all subsequent samples are added to the correct bins. At the end, a range of std::pair is
        returned, where each pair contains the position of the bin (lower bound) and the sum of the weights (normalized with the
        sum of all weights).

        @param density_cache_size Number of first samples used to determine min and max.
        @param density_num_bins Number of bins (two additional bins collect under- and overflow samples).
    */
    template<typename Sample, typename Weight>
    struct weighted_density_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Weight, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<typename histogram_type::iterator> result_type;

        template<typename Args>
        weighted_density_impl(Args const &args)
            : cache_size(args[density_cache_size])
            , cache(cache_size)
            , num_bins(args[density_num_bins])
            , samples_in_bin(num_bins + 2, 0.)
            , bin_positions(num_bins + 2)
            , histogram(
                num_bins + 2
              , std::make_pair(
                    numeric::fdiv(args[sample | Sample()],(std::size_t)1)
                  , numeric::fdiv(args[sample | Sample()],(std::size_t)1)
                )
              )
            , is_dirty(true)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty = true;

            std::size_t cnt = count(args);

            // Fill up cache with cache_size first samples
            if (cnt <= this->cache_size)
            {
                this->cache[cnt - 1] = std::make_pair(args[sample], args[weight]);
            }

            // Once cache_size samples have been accumulated, create num_bins bins of same size between
            // the minimum and maximum of the cached samples as well as an under- and an overflow bin.
            // Store their lower bounds (bin_positions) and fill the bins with the cached samples (samples_in_bin).
            if (cnt == this->cache_size)
            {
                float_type minimum = numeric::fdiv((min)(args),(std::size_t)1);
                float_type maximum = numeric::fdiv((max)(args),(std::size_t)1);
                float_type bin_size = numeric::fdiv(maximum - minimum, this->num_bins);

                // determine bin positions (their lower bounds)
                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->bin_positions[i] = minimum + (i - 1.) * bin_size;
                }

                for (typename histogram_type::const_iterator iter = this->cache.begin(); iter != this->cache.end(); ++iter)
                {
                    if (iter->first < this->bin_positions[1])
                    {
                        this->samples_in_bin[0] += iter->second;
                    }
                    else if (iter->first >= this->bin_positions[this->num_bins + 1])
                    {
                        this->samples_in_bin[this->num_bins + 1] += iter->second;
                    }
                    else
                    {
                        typename array_type::iterator it = std::upper_bound(
                            this->bin_positions.begin()
                          , this->bin_positions.end()
                          , iter->first
                        );

                        std::size_t d = std::distance(this->bin_positions.begin(), it);
                        this->samples_in_bin[d - 1] += iter->second;
                    }
                }
            }
            // Add each subsequent sample to the correct bin
            else if (cnt > this->cache_size)
            {
                if (args[sample] < this->bin_positions[1])
                {
                    this->samples_in_bin[0] += args[weight];
                }
                else if (args[sample] >= this->bin_positions[this->num_bins + 1])
                {
                    this->samples_in_bin[this->num_bins + 1] += args[weight];
                }
                else
                {
                    typename array_type::iterator it = std::upper_bound(
                        this->bin_positions.begin()
                      , this->bin_positions.end()
                      , args[sample]
                    );

                    std::size_t d = std::distance(this->bin_positions.begin(), it);
                    this->samples_in_bin[d - 1] += args[weight];
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
                // the values bin_positions[i] (x-axis of histogram) and
                // samples_in_bin[i] / cnt (y-axis of histogram).

                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->histogram[i] = std::make_pair(this->bin_positions[i], numeric::fdiv(this->samples_in_bin[i], sum_of_weights(args)));
                }
            }

            // returns a range of pairs
            return make_iterator_range(this->histogram);
        }

        // make this accumulator serializeable
        // TODO split to save/load and check on parameters provided in ctor
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & cache_size;
            ar & cache;
            ar & num_bins;
            ar & samples_in_bin;
            ar & bin_positions;
            ar & histogram;
            ar & is_dirty; 
        }

    private:
        std::size_t            cache_size;      // number of cached samples
        histogram_type         cache;           // cache to store the first cache_size samples with their weights as std::pair
        std::size_t            num_bins;        // number of bins
        array_type             samples_in_bin;  // number of samples in each bin
        array_type             bin_positions;   // lower bounds of bins
        mutable histogram_type histogram;       // histogram
        mutable bool is_dirty;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_density
//
namespace tag
{
    struct weighted_density
      : depends_on<count, sum_of_weights, min, max>
      , density_cache_size
      , density_num_bins
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_density_impl<mpl::_1, mpl::_2> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        static boost::parameter::keyword<density_cache_size> const cache_size;
        static boost::parameter::keyword<density_num_bins> const num_bins;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_density
//
namespace extract
{
    extractor<tag::density> const weighted_density = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_density)
}

using extract::weighted_density;

}} // namespace boost::accumulators

#endif

/* weighted_density.hpp
LewV5NbjEXLA+Aij7atFtXQuVpxFjOqPK13VOvOFvXExC3489bcJvnt+Js6T+3AWHt/v8P3j/mi4cUD+G+J/0/8/v8qn6v2He3rzTBHWgJao8bfo+S2Ui0F7OLdWyWrEI4FpHFHeDuxiFn1hJfvpraROe6KHWGc1FRVI0GDJ4ERngMX+p0FN9KHMzm/3Lo1B3CZgvCv0h0PRvmw/054koyXMdCwLiv3h0VrsL9NPpW4/qaQ4ki97AqXKqaMnXXUrEpVisBYw+TZbAF5rymIu18J8FeE57Iac/afq+Vnrf3pGLl0DfxXEV+8h87M0M8fnL3yCKj6mARZ7MgsQ/m+8FNyiEfGwwuMcLwldIzaN5JTkEo0S9A+d4igezNPFKAzjkm+0NfZEtv+OcMop1EkoAqIbUqB7EL+ByF79L+LU7Sn1i1TtWBcHXE4BD2staT2Ju6U5v6qDV6Vj1UkfM8ECY1XpMCqzzm0MX+PNZrGBvN/dFwqFz1qV/JHnU1RJV13tEXPqVpTb1ZTB2nJR3Mw01VpYx4scQiAO4DOXP8VBm9Znu979pZ9K+w0/9QivsnAoIVGOdWD2yO1L48gOmFmwf59FEHsJbnPPwXnzihtX3kCAo0AnIJcG5qR5gzxOvK6tuTDczxOhOo9el7bAMKsHNFbMBfkGuCj8IWJ4cPyC+7/Dn8r+GUz7VYdv1nt2H2cSx9lNio/aotfPFI6zJ7dOCbn9x5Nj0mPi6Yw1GnyBiS/YfMPFxFsmJOhRrdJvIo4UK6oQYyuuUKmjqncDVwq8GIM4pfXURlr8BatdQgkDkxHIU21tpDN24qno61gVA+BRX3Ayoc650tj2QRlcqnqtm9XSrlQ51ADZ2ZFSbhgJLCTUocbQhUoi5IO8CZNqcUtozVi1yljNirCcPr94D2zT6emtnP5CuE1ed014R8FtNNLncrtw8UIhtSTDf30MfHBSPcF/EABognRCzmji/SO8kGfuH4a3wDu3NudqtbUFOdhx4EAjX6fAG4RCTFqpEZqVEBFIrlU1e7FWCwN+TgsezagwNFibmTMyh9uifmrKjEJs3MM+KLMYeezzjQbyuak/Np0hf5bzz1mV108DM/X6qYFjCjcS/kissn5SJyPrpxXFU+x4aWfCnVImf8SztBwaj794fkqw6PXSG2GJ9Ljm0B8PPo1ESknV/MERiXQgRFI+auVYOCx+YNyPA/0nIZS+TnJ2WYjzHGjdpwK3MG4bOBatdXE9HNPIC/ZA5yIGFn1G8UhKvXVwRErtOpik1GHxBicosXJVbbk9qZofgOW7jToBe/DGEyUlVJgjhpYwxj74JPaXVR95dWCRPdzyErpJM/XwWktuo+CNx/1l8SPrUh6H5IRMPN8zhJXLs/o2/8Z4Wcx4o8Sq+D7zAu6G12th7RYfzlqmmFclp3f9yzlJztuIjOkiEQClCRG94/3jICmZJ3DHUSSHq4gh5LOB1gwvc9X1JHhvceQPCpHgPQGBZyYSD5z57fG4mHUnT/19Et+vTpz6/e34WulZxynV/xef+O+WhSvyJ+FN3/p4pDFj4mEWyuBhxqInTl9D/gwiHp5ymOh6u7X8WUzy50Z1UQYNQYw5HpBvNARPn0OUobveF9bOWSnb4ilZ1Ic8/ESwFMn2KqZcZO+UjLJ3qoNNheJEjtr6Sq3IGlJLGEwNUTHjl+8IpfbsFfVJN4AvKeoSPldVOC9yripV1NDiIFJ94OW5UwuNvuDT1OhcOwlo/2AhMcGiZcjNYtKRQZqX8zAel5lkyK0UOjiL2YO9HV/XlbOU+qsPTcq/J8EylVGEeM7JYRR90ESrQTYDS3SyuKCzLNbfJQRPtunBC0/omVTWMgQ=
*/