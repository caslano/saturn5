// Contains get_min_count, the core optimization of the spreadsort algorithm.
// Also has other helper functions commonly useful across variants.

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

#ifndef BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_COMMON_HPP
#define BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_COMMON_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
#include <functional>
#include <boost/static_assert.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/spreadsort/detail/constants.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace sort {
namespace spreadsort {
 namespace detail {
    //This only works on unsigned data types
    template <typename T>
    inline unsigned
    rough_log_2_size(const T& input)
    {
      unsigned result = 0;
      //The && is necessary on some compilers to avoid infinite loops
      //it doesn't significantly impair performance
      while ((result < (8*sizeof(T))) && (input >> result)) ++result;
      return result;
    }

    //Gets the minimum size to call spreadsort on to control worst-case runtime.
    //This is called for a set of bins, instead of bin-by-bin, to minimize
    //runtime overhead.
    //This could be replaced by a lookup table of sizeof(Div_type)*8 but this
    //function is more general.
    template<unsigned log_mean_bin_size,
      unsigned log_min_split_count, unsigned log_finishing_count>
    inline size_t
    get_min_count(unsigned log_range)
    {
      const size_t typed_one = 1;
      const unsigned min_size = log_mean_bin_size + log_min_split_count;
      //Assuring that constants have valid settings
      BOOST_STATIC_ASSERT(log_min_split_count <= max_splits &&
                          log_min_split_count > 0);
      BOOST_STATIC_ASSERT(max_splits > 1 &&
                          max_splits < (8 * sizeof(unsigned)));
      BOOST_STATIC_ASSERT(max_finishing_splits >= max_splits &&
                          max_finishing_splits < (8 * sizeof(unsigned)));
      BOOST_STATIC_ASSERT(log_mean_bin_size >= 0);
      BOOST_STATIC_ASSERT(log_finishing_count >= 0);
      //if we can complete in one iteration, do so
      //This first check allows the compiler to optimize never-executed code out
      if (log_finishing_count < min_size) {
        if (log_range <= min_size && log_range <= max_splits) {
          //Return no smaller than a certain minimum limit
          if (log_range <= log_finishing_count)
            return typed_one << log_finishing_count;
          return typed_one << log_range;
        }
      }
      const unsigned base_iterations = max_splits - log_min_split_count;
      //sum of n to n + x = ((x + 1) * (n + (n + x)))/2 + log_mean_bin_size
      const unsigned base_range =
          ((base_iterations + 1) * (max_splits + log_min_split_count))/2
          + log_mean_bin_size;
      //Calculating the required number of iterations, and returning
      //1 << (iteration_count + min_size)
      if (log_range < base_range) {
        unsigned result = log_min_split_count;
        for (unsigned offset = min_size; offset < log_range;
          offset += ++result);
        //Preventing overflow; this situation shouldn't occur
        if ((result + log_mean_bin_size) >= (8 * sizeof(size_t)))
          return typed_one << ((8 * sizeof(size_t)) - 1);
        return typed_one << (result + log_mean_bin_size);
      }
      //A quick division can calculate the worst-case runtime for larger ranges
      unsigned remainder = log_range - base_range;
      //the max_splits - 1 is used to calculate the ceiling of the division
      unsigned bit_length = ((((max_splits - 1) + remainder)/max_splits)
        + base_iterations + min_size);
      //Preventing overflow; this situation shouldn't occur
      if (bit_length >= (8 * sizeof(size_t)))
        return typed_one << ((8 * sizeof(size_t)) - 1);
      //n(log_range)/max_splits + C, optimizing worst-case performance
      return typed_one << bit_length;
    }

    // Resizes the bin cache and bin sizes, and initializes each bin size to 0.
    // This generates the memory overhead to use in radix sorting.
    template <class RandomAccessIter>
    inline RandomAccessIter *
    size_bins(size_t *bin_sizes, std::vector<RandomAccessIter>
  &bin_cache, unsigned cache_offset, unsigned &cache_end, unsigned bin_count)
    {
      // Clear the bin sizes
      for (size_t u = 0; u < bin_count; u++)
        bin_sizes[u] = 0;
      //Make sure there is space for the bins
      cache_end = cache_offset + bin_count;
      if (cache_end > bin_cache.size())
        bin_cache.resize(cache_end);
      return &(bin_cache[cache_offset]);
    }
  }
}
}
}

#endif

/* spreadsort_common.hpp
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
*/