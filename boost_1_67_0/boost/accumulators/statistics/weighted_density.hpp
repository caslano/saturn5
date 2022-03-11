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