// Details for templated Spreadsort-based integer_sort.

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

#ifndef BOOST_SORT_SPREADSORT_DETAIL_INTEGER_SORT_HPP
#define BOOST_SORT_SPREADSORT_DETAIL_INTEGER_SORT_HPP
#include <algorithm>
#include <vector>
#include <limits>
#include <functional>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/sort/spreadsort/detail/constants.hpp>
#include <boost/sort/spreadsort/detail/spreadsort_common.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace sort {
namespace spreadsort {
  namespace detail {
    // Return true if the list is sorted.  Otherwise, find the minimum and
    // maximum using <.
    template <class RandomAccessIter>
    inline bool
    is_sorted_or_find_extremes(RandomAccessIter current, RandomAccessIter last,
                               RandomAccessIter & max, RandomAccessIter & min)
    {
      min = max = current;
      //This assumes we have more than 1 element based on prior checks.
      while (!(*(current + 1) < *current)) {
        //If everything is in sorted order, return
        if (++current == last - 1)
          return true;
      }

      //The maximum is the last sorted element
      max = current;
      //Start from the first unsorted element
      while (++current < last) {
        if (*max < *current)
          max = current;
        else if (*current < *min)
          min = current;
      }
      return false;
    }

    // Return true if the list is sorted.  Otherwise, find the minimum and
    // maximum.
    // Use a user-defined comparison operator
    template <class RandomAccessIter, class Compare>
    inline bool
    is_sorted_or_find_extremes(RandomAccessIter current, RandomAccessIter last,
                RandomAccessIter & max, RandomAccessIter & min, Compare comp)
    {
      min = max = current;
      while (!comp(*(current + 1), *current)) {
        //If everything is in sorted order, return
        if (++current == last - 1)
          return true;
      }

      //The maximum is the last sorted element
      max = current;
      while (++current < last) {
        if (comp(*max, *current))
          max = current;
        else if (comp(*current, *min))
          min = current;
      }
      return false;
    }

    //Gets a non-negative right bit shift to operate as a logarithmic divisor
    template<unsigned log_mean_bin_size>
    inline int
    get_log_divisor(size_t count, int log_range)
    {
      int log_divisor;
      //If we can finish in one iteration without exceeding either
      //(2 to the max_finishing_splits) or n bins, do so
      if ((log_divisor = log_range - rough_log_2_size(count)) <= 0 && 
         log_range <= max_finishing_splits)
        log_divisor = 0; 
      else {
        //otherwise divide the data into an optimized number of pieces
        log_divisor += log_mean_bin_size;
        //Cannot exceed max_splits or cache misses slow down bin lookups
        if ((log_range - log_divisor) > max_splits)
          log_divisor = log_range - max_splits;
      }
      return log_divisor;
    }

    //Implementation for recursive integer sorting
    template <class RandomAccessIter, class Div_type, class Size_type>
    inline void
    spreadsort_rec(RandomAccessIter first, RandomAccessIter last,
              std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
              , size_t *bin_sizes)
    {
      //This step is roughly 10% of runtime, but it helps avoid worst-case
      //behavior and improve behavior with real data
      //If you know the maximum and minimum ahead of time, you can pass those
      //values in and skip this step for the first iteration
      RandomAccessIter max, min;
      if (is_sorted_or_find_extremes(first, last, max, min))
        return;
      RandomAccessIter * target_bin;
      unsigned log_divisor = get_log_divisor<int_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type((*max >> 0) - (*min >> 0))));
      Div_type div_min = *min >> log_divisor;
      Div_type div_max = *max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins =
        size_bins(bin_sizes, bin_cache, cache_offset, cache_end, bin_count);

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[size_t((*(current++) >> log_divisor) - div_min)]++;
      //Assign the bin positions
      bins[0] = first;
      for (unsigned u = 0; u < bin_count - 1; u++)
        bins[u + 1] = bins[u] + bin_sizes[u];

      RandomAccessIter nextbinstart = first;
      //Swap into place
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < bin_count - 1; ++u) {
        RandomAccessIter * local_bin = bins + u;
        nextbinstart += bin_sizes[u];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < nextbinstart;
            ++current) {
          //Swapping elements in current into place until the correct
          //element has been swapped in
          for (target_bin = (bins + ((*current >> log_divisor) - div_min));
              target_bin != local_bin;
            target_bin = bins + ((*current >> log_divisor) - div_min)) {
            //3-way swap; this is about 1% faster than a 2-way swap
            //The main advantage is less copies are involved per item
            //put in the correct place
            typename std::iterator_traits<RandomAccessIter>::value_type tmp;
            RandomAccessIter b = (*target_bin)++;
            RandomAccessIter * b_bin = bins + ((*b >> log_divisor) - div_min);
            if (b_bin != local_bin) {
              RandomAccessIter c = (*b_bin)++;
              tmp = *c;
              *c = *b;
            }
            else
              tmp = *b;
            *b = *current;
            *current = tmp;
          }
        }
        *local_bin = nextbinstart;
      }
      bins[bin_count - 1] = last;

      //If we've bucketsorted, the array is sorted and we should skip recursion
      if (!log_divisor)
        return;
      //log_divisor is the remaining range; calculating the comparison threshold
      size_t max_count =
        get_min_count<int_log_mean_bin_size, int_log_min_split_count,
                      int_log_finishing_count>(log_divisor);

      //Recursing
      RandomAccessIter lastPos = first;
      for (unsigned u = cache_offset; u < cache_end; lastPos = bin_cache[u],
          ++u) {
        Size_type count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using boost::sort::pdqsort if its worst-case is better
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u]);
        else
          spreadsort_rec<RandomAccessIter, Div_type, Size_type>(lastPos,
                                                                 bin_cache[u],
                                                                 bin_cache,
                                                                 cache_end,
                                                                 bin_sizes);
      }
    }

    //Generic bitshift-based 3-way swapping code
    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline void inner_swap_loop(RandomAccessIter * bins,
      const RandomAccessIter & next_bin_start, unsigned ii, Right_shift &rshift
      , const unsigned log_divisor, const Div_type div_min)
    {
      RandomAccessIter * local_bin = bins + ii;
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        for (RandomAccessIter * target_bin =
            (bins + (rshift(*current, log_divisor) - div_min));
            target_bin != local_bin;
            target_bin = bins + (rshift(*current, log_divisor) - div_min)) {
          typename std::iterator_traits<RandomAccessIter>::value_type tmp;
          RandomAccessIter b = (*target_bin)++;
          RandomAccessIter * b_bin =
            bins + (rshift(*b, log_divisor) - div_min);
          //Three-way swap; if the item to be swapped doesn't belong
          //in the current bin, swap it to where it belongs
          if (b_bin != local_bin) {
            RandomAccessIter c = (*b_bin)++;
            tmp = *c;
            *c = *b;
          }
          //Note: we could increment current once the swap is done in this case
          //but that seems to impair performance
          else
            tmp = *b;
          *b = *current;
          *current = tmp;
        }
      }
      *local_bin = next_bin_start;
    }

    //Standard swapping wrapper for ascending values
    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline void swap_loop(RandomAccessIter * bins,
             RandomAccessIter & next_bin_start, unsigned ii, Right_shift &rshift
             , const size_t *bin_sizes
             , const unsigned log_divisor, const Div_type div_min)
    {
      next_bin_start += bin_sizes[ii];
      inner_swap_loop<RandomAccessIter, Div_type, Right_shift>(bins,
                              next_bin_start, ii, rshift, log_divisor, div_min);
    }

    //Functor implementation for recursive sorting
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare, class Size_type, unsigned log_mean_bin_size,
                unsigned log_min_split_count, unsigned log_finishing_count>
    inline void
    spreadsort_rec(RandomAccessIter first, RandomAccessIter last,
          std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
          , size_t *bin_sizes, Right_shift rshift, Compare comp)
    {
      RandomAccessIter max, min;
      if (is_sorted_or_find_extremes(first, last, max, min, comp))
        return;
      unsigned log_divisor = get_log_divisor<log_mean_bin_size>(last - first,
            rough_log_2_size(Size_type(rshift(*max, 0) - rshift(*min, 0))));
      Div_type div_min = rshift(*min, log_divisor);
      Div_type div_max = rshift(*max, log_divisor);
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned(rshift(*(current++), log_divisor) - div_min)]++;
      bins[0] = first;
      for (unsigned u = 0; u < bin_count - 1; u++)
        bins[u + 1] = bins[u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      for (unsigned u = 0; u < bin_count - 1; ++u)
        swap_loop<RandomAccessIter, Div_type, Right_shift>(bins, next_bin_start,
                                  u, rshift, bin_sizes, log_divisor, div_min);
      bins[bin_count - 1] = last;

      //If we've bucketsorted, the array is sorted
      if (!log_divisor)
        return;

      //Recursing
      size_t max_count = get_min_count<log_mean_bin_size, log_min_split_count,
                          log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (unsigned u = cache_offset; u < cache_end; lastPos = bin_cache[u],
          ++u) {
        size_t count = bin_cache[u] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u], comp);
        else
          spreadsort_rec<RandomAccessIter, Div_type, Right_shift, Compare,
        Size_type, log_mean_bin_size, log_min_split_count, log_finishing_count>
      (lastPos, bin_cache[u], bin_cache, cache_end, bin_sizes, rshift, comp);
      }
    }

    //Functor implementation for recursive sorting with only Shift overridden
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Size_type, unsigned log_mean_bin_size,
              unsigned log_min_split_count, unsigned log_finishing_count>
    inline void
    spreadsort_rec(RandomAccessIter first, RandomAccessIter last,
              std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
              , size_t *bin_sizes, Right_shift rshift)
    {
      RandomAccessIter max, min;
      if (is_sorted_or_find_extremes(first, last, max, min))
        return;
      unsigned log_divisor = get_log_divisor<log_mean_bin_size>(last - first,
            rough_log_2_size(Size_type(rshift(*max, 0) - rshift(*min, 0))));
      Div_type div_min = rshift(*min, log_divisor);
      Div_type div_max = rshift(*max, log_divisor);
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned(rshift(*(current++), log_divisor) - div_min)]++;
      bins[0] = first;
      for (unsigned u = 0; u < bin_count - 1; u++)
        bins[u + 1] = bins[u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter nextbinstart = first;
      for (unsigned ii = 0; ii < bin_count - 1; ++ii)
        swap_loop<RandomAccessIter, Div_type, Right_shift>(bins, nextbinstart,
                                ii, rshift, bin_sizes, log_divisor, div_min);
      bins[bin_count - 1] = last;

      //If we've bucketsorted, the array is sorted
      if (!log_divisor)
        return;

      //Recursing
      size_t max_count = get_min_count<log_mean_bin_size, log_min_split_count,
                          log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (unsigned u = cache_offset; u < cache_end; lastPos = bin_cache[u],
          ++u) {
        size_t count = bin_cache[u] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u]);
        else
          spreadsort_rec<RandomAccessIter, Div_type, Right_shift, Size_type,
          log_mean_bin_size, log_min_split_count, log_finishing_count>(lastPos,
                      bin_cache[u], bin_cache, cache_end, bin_sizes, rshift);
      }
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Div_type>
    //Only use spreadsort if the integer can fit in a size_t
    inline typename boost::enable_if_c< sizeof(Div_type) <= sizeof(size_t),
                                                            void >::type
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      spreadsort_rec<RandomAccessIter, Div_type, size_t>(first, last,
          bin_cache, 0, bin_sizes);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Div_type>
    //Only use spreadsort if the integer can fit in a uintmax_t
    inline typename boost::enable_if_c< (sizeof(Div_type) > sizeof(size_t))
      && sizeof(Div_type) <= sizeof(boost::uintmax_t), void >::type
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      spreadsort_rec<RandomAccessIter, Div_type, boost::uintmax_t>(first,
          last, bin_cache, 0, bin_sizes);
    }

    template <class RandomAccessIter, class Div_type>
    inline typename boost::disable_if_c< sizeof(Div_type) <= sizeof(size_t)
      || sizeof(Div_type) <= sizeof(boost::uintmax_t), void >::type
    //defaulting to boost::sort::pdqsort when integer_sort won't work
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type)
    {
      //Warning that we're using boost::sort::pdqsort, even though integer_sort was called
      BOOST_STATIC_ASSERT( sizeof(Div_type) <= sizeof(size_t) );
      boost::sort::pdqsort(first, last);
    }


    //Same for the full functor version
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    //Only use spreadsort if the integer can fit in a size_t
    inline typename boost::enable_if_c< sizeof(Div_type) <= sizeof(size_t),
                                 void >::type
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
                Right_shift shift, Compare comp)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      spreadsort_rec<RandomAccessIter, Div_type, Right_shift, Compare,
          size_t, int_log_mean_bin_size, int_log_min_split_count, 
                        int_log_finishing_count>
          (first, last, bin_cache, 0, bin_sizes, shift, comp);
    }

    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    //Only use spreadsort if the integer can fit in a uintmax_t
    inline typename boost::enable_if_c< (sizeof(Div_type) > sizeof(size_t))
      && sizeof(Div_type) <= sizeof(boost::uintmax_t), void >::type
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
                Right_shift shift, Compare comp)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      spreadsort_rec<RandomAccessIter, Div_type, Right_shift, Compare,
                        boost::uintmax_t, int_log_mean_bin_size,
                        int_log_min_split_count, int_log_finishing_count>
          (first, last, bin_cache, 0, bin_sizes, shift, comp);
    }

    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    inline typename boost::disable_if_c< sizeof(Div_type) <= sizeof(size_t)
      || sizeof(Div_type) <= sizeof(boost::uintmax_t), void >::type
    //defaulting to boost::sort::pdqsort when integer_sort won't work
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
                Right_shift shift, Compare comp)
    {
      //Warning that we're using boost::sort::pdqsort, even though integer_sort was called
      BOOST_STATIC_ASSERT( sizeof(Div_type) <= sizeof(size_t) );
      boost::sort::pdqsort(first, last, comp);
    }


    //Same for the right shift version
    template <class RandomAccessIter, class Div_type, class Right_shift>
    //Only use spreadsort if the integer can fit in a size_t
    inline typename boost::enable_if_c< sizeof(Div_type) <= sizeof(size_t),
                                 void >::type
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
                Right_shift shift)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      spreadsort_rec<RandomAccessIter, Div_type, Right_shift, size_t,
          int_log_mean_bin_size, int_log_min_split_count, 
                        int_log_finishing_count>
          (first, last, bin_cache, 0, bin_sizes, shift);
    }

    template <class RandomAccessIter, class Div_type, class Right_shift>
    //Only use spreadsort if the integer can fit in a uintmax_t
    inline typename boost::enable_if_c< (sizeof(Div_type) > sizeof(size_t))
      && sizeof(Div_type) <= sizeof(boost::uintmax_t), void >::type
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
                Right_shift shift)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      spreadsort_rec<RandomAccessIter, Div_type, Right_shift,
                        boost::uintmax_t, int_log_mean_bin_size,
                        int_log_min_split_count, int_log_finishing_count>
          (first, last, bin_cache, 0, bin_sizes, shift);
    }

    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline typename boost::disable_if_c< sizeof(Div_type) <= sizeof(size_t)
      || sizeof(Div_type) <= sizeof(boost::uintmax_t), void >::type
    //defaulting to boost::sort::pdqsort when integer_sort won't work
    integer_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
                Right_shift shift)
    {
      //Warning that we're using boost::sort::pdqsort, even though integer_sort was called
      BOOST_STATIC_ASSERT( sizeof(Div_type) <= sizeof(size_t) );
      boost::sort::pdqsort(first, last);
    }
  }
}
}
}

#endif

/* integer_sort.hpp
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
*/