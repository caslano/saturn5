
///////////////////////////////////////////////////////////////////////////////
// density.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_DENSITY_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_DENSITY_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// cache_size and num_bins named parameters
//
BOOST_PARAMETER_NESTED_KEYWORD(tag, density_cache_size, cache_size)
BOOST_PARAMETER_NESTED_KEYWORD(tag, density_num_bins, num_bins)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(density_cache_size)
BOOST_ACCUMULATORS_IGNORE_GLOBAL(density_num_bins)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // density_impl
    //  density histogram
    /**
        @brief Histogram density estimator

        The histogram density estimator returns a histogram of the sample distribution. The positions and sizes of the bins
        are determined using a specifiable number of cached samples (cache_size). The range between the minimum and the
        maximum of the cached samples is subdivided into a specifiable number of bins (num_bins) of same size. Additionally,
        an under- and an overflow bin is added to capture future under- and overflow samples. Once the bins are determined,
        the cached samples and all subsequent samples are added to the correct bins. At the end, a range of std::pair is
        return, where each pair contains the position of the bin (lower bound) and the samples count (normalized with the
        total number of samples).

        @param  density_cache_size Number of first samples used to determine min and max.
        @param  density_num_bins Number of bins (two additional bins collect under- and overflow samples).
    */
    template<typename Sample>
    struct density_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<typename histogram_type::iterator> result_type;

        template<typename Args>
        density_impl(Args const &args)
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
                this->cache[cnt - 1] = args[sample];
            }

            // Once cache_size samples have been accumulated, create num_bins bins of same size between
            // the minimum and maximum of the cached samples as well as under and overflow bins.
            // Store their lower bounds (bin_positions) and fill the bins with the cached samples (samples_in_bin).
            if (cnt == this->cache_size)
            {
                float_type minimum = numeric::fdiv((min)(args), (std::size_t)1);
                float_type maximum = numeric::fdiv((max)(args), (std::size_t)1);
                float_type bin_size = numeric::fdiv(maximum - minimum, this->num_bins );

                // determine bin positions (their lower bounds)
                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->bin_positions[i] = minimum + (i - 1.) * bin_size;
                }

                for (typename array_type::const_iterator iter = this->cache.begin(); iter != this->cache.end(); ++iter)
                {
                    if (*iter < this->bin_positions[1])
                    {
                        ++(this->samples_in_bin[0]);
                    }
                    else if (*iter >= this->bin_positions[this->num_bins + 1])
                    {
                        ++(this->samples_in_bin[this->num_bins + 1]);
                    }
                    else
                    {
                        typename array_type::iterator it = std::upper_bound(
                            this->bin_positions.begin()
                          , this->bin_positions.end()
                          , *iter
                        );

                        std::size_t d = std::distance(this->bin_positions.begin(), it);
                        ++(this->samples_in_bin[d - 1]);
                    }
                }
            }
            // Add each subsequent sample to the correct bin
            else if (cnt > this->cache_size)
            {
                if (args[sample] < this->bin_positions[1])
                {
                    ++(this->samples_in_bin[0]);
                }
                else if (args[sample] >= this->bin_positions[this->num_bins + 1])
                {
                    ++(this->samples_in_bin[this->num_bins + 1]);
                }
                else
                {
                    typename array_type::iterator it = std::upper_bound(
                        this->bin_positions.begin()
                      , this->bin_positions.end()
                      , args[sample]
                    );

                    std::size_t d = std::distance(this->bin_positions.begin(), it);
                    ++(this->samples_in_bin[d - 1]);
                }
            }
        }

        /**
            @pre The number of samples must meet or exceed the cache size
        */
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
                    this->histogram[i] = std::make_pair(this->bin_positions[i], numeric::fdiv(this->samples_in_bin[i], count(args)));
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
        array_type             cache;           // cache to store the first cache_size samples
        std::size_t            num_bins;        // number of bins
        array_type             samples_in_bin;  // number of samples in each bin
        array_type             bin_positions;   // lower bounds of bins
        mutable histogram_type histogram;       // histogram
        mutable bool is_dirty;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::density
//
namespace tag
{
    struct density
      : depends_on<count, min, max>
      , density_cache_size
      , density_num_bins
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::density_impl<mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::density::cache_size named parameter
        /// tag::density::num_bins named parameter
        static boost::parameter::keyword<density_cache_size> const cache_size;
        static boost::parameter::keyword<density_num_bins> const num_bins;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::density
//
namespace extract
{
    extractor<tag::density> const density = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(density)
}

using extract::density;

// So that density can be automatically substituted
// with weighted_density when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::density>
{
    typedef tag::weighted_density type;
};

template<>
struct feature_of<tag::weighted_density>
  : feature_of<tag::density>
{
};

}} // namespace boost::accumulators

#endif

/* density.hpp
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
*/