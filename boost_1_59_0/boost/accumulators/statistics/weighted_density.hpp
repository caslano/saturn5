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
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
*/