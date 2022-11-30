// Details for templated Spreadsort-based float_sort.

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
float_mem_cast fix provided by:
Scott McMurray
*/

#ifndef BOOST_SORT_SPREADSORT_DETAIL_FLOAT_SORT_HPP
#define BOOST_SORT_SPREADSORT_DETAIL_FLOAT_SORT_HPP
#include <algorithm>
#include <vector>
#include <limits>
#include <functional>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/sort/spreadsort/detail/constants.hpp>
#include <boost/sort/spreadsort/detail/integer_sort.hpp>
#include <boost/sort/spreadsort/detail/spreadsort_common.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace sort {
namespace spreadsort {
  namespace detail {
    //Casts a RandomAccessIter to the specified integer type
    template<class Cast_type, class RandomAccessIter>
    inline Cast_type
    cast_float_iter(const RandomAccessIter & floatiter)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //Only cast IEEE floating-point numbers, and only to same-sized integers
      BOOST_STATIC_ASSERT(sizeof(Cast_type) == sizeof(Data_type));
      BOOST_STATIC_ASSERT(std::numeric_limits<Data_type>::is_iec559);
      BOOST_STATIC_ASSERT(std::numeric_limits<Cast_type>::is_integer);
      Cast_type result;
      std::memcpy(&result, &(*floatiter), sizeof(Data_type));
      return result;
    }

    // Return true if the list is sorted.  Otherwise, find the minimum and
    // maximum.  Values are Right_shifted 0 bits before comparison.
    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline bool
    is_sorted_or_find_extremes(RandomAccessIter current, RandomAccessIter last,
                  Div_type & max, Div_type & min, Right_shift rshift)
    {
      min = max = rshift(*current, 0);
      RandomAccessIter prev = current;
      bool sorted = true;
      while (++current < last) {
        Div_type value = rshift(*current, 0);
        sorted &= *current >= *prev;
        prev = current;
        if (max < value)
          max = value;
        else if (value < min)
          min = value;
      }
      return sorted;
    }

    // Return true if the list is sorted.  Otherwise, find the minimum and
    // maximum.  Uses comp to check if the data is already sorted.
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    inline bool
    is_sorted_or_find_extremes(RandomAccessIter current, RandomAccessIter last,
                               Div_type & max, Div_type & min, 
                               Right_shift rshift, Compare comp)
    {
      min = max = rshift(*current, 0);
      RandomAccessIter prev = current;
      bool sorted = true;
      while (++current < last) {
        Div_type value = rshift(*current, 0);
        sorted &= !comp(*current, *prev);
        prev = current;
        if (max < value)
          max = value;
        else if (value < min)
          min = value;
      }
      return sorted;
    }

    //Specialized swap loops for floating-point casting
    template <class RandomAccessIter, class Div_type>
    inline void inner_float_swap_loop(RandomAccessIter * bins,
                        const RandomAccessIter & nextbinstart, unsigned ii
                        , const unsigned log_divisor, const Div_type div_min)
    {
      RandomAccessIter * local_bin = bins + ii;
      for (RandomAccessIter current = *local_bin; current < nextbinstart;
          ++current) {
        for (RandomAccessIter * target_bin =
            (bins + ((cast_float_iter<Div_type, RandomAccessIter>(current) >>
                      log_divisor) - div_min));  target_bin != local_bin;
          target_bin = bins + ((cast_float_iter<Div_type, RandomAccessIter>
                               (current) >> log_divisor) - div_min)) {
          typename std::iterator_traits<RandomAccessIter>::value_type tmp;
          RandomAccessIter b = (*target_bin)++;
          RandomAccessIter * b_bin = bins + ((cast_float_iter<Div_type,
                              RandomAccessIter>(b) >> log_divisor) - div_min);
          //Three-way swap; if the item to be swapped doesn't belong in the
          //current bin, swap it to where it belongs
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

    template <class RandomAccessIter, class Div_type>
    inline void float_swap_loop(RandomAccessIter * bins,
                          RandomAccessIter & nextbinstart, unsigned ii,
                          const size_t *bin_sizes,
                          const unsigned log_divisor, const Div_type div_min)
    {
      nextbinstart += bin_sizes[ii];
      inner_float_swap_loop<RandomAccessIter, Div_type>
        (bins, nextbinstart, ii, log_divisor, div_min);
    }

    // Return true if the list is sorted.  Otherwise, find the minimum and
    // maximum.  Values are cast to Cast_type before comparison.
    template <class RandomAccessIter, class Cast_type>
    inline bool
    is_sorted_or_find_extremes(RandomAccessIter current, RandomAccessIter last,
                  Cast_type & max, Cast_type & min)
    {
      min = max = cast_float_iter<Cast_type, RandomAccessIter>(current);
      RandomAccessIter prev = current;
      bool sorted = true;
      while (++current < last) {
        Cast_type value = cast_float_iter<Cast_type, RandomAccessIter>(current);
        sorted &= *current >= *prev;
        prev = current;
        if (max < value)
          max = value;
        else if (value < min)
          min = value;
      }
      return sorted;
    }

    //Special-case sorting of positive floats with casting
    template <class RandomAccessIter, class Div_type, class Size_type>
    inline void
    positive_float_sort_rec(RandomAccessIter first, RandomAccessIter last,
              std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
              , size_t *bin_sizes)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes<RandomAccessIter, Div_type>(first, last, 
                                                                max, min))
        return;
      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned((cast_float_iter<Div_type, RandomAccessIter>(
            current++) >> log_divisor) - div_min)]++;
      bins[0] = first;
      for (unsigned u = 0; u < bin_count - 1; u++)
        bins[u + 1] = bins[u] + bin_sizes[u];


      //Swap into place
      RandomAccessIter nextbinstart = first;
      for (unsigned u = 0; u < bin_count - 1; ++u)
        float_swap_loop<RandomAccessIter, Div_type>
          (bins, nextbinstart, u, bin_sizes, log_divisor, div_min);
      bins[bin_count - 1] = last;

      //Return if we've completed bucketsorting
      if (!log_divisor)
        return;

      //Recursing
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (unsigned u = cache_offset; u < cache_end; lastPos = bin_cache[u],
          ++u) {
        size_t count = bin_cache[u] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u]);
        else
          positive_float_sort_rec<RandomAccessIter, Div_type, Size_type>
            (lastPos, bin_cache[u], bin_cache, cache_end, bin_sizes);
      }
    }

    //Sorting negative floats
    //Bins are iterated in reverse because max_neg_float = min_neg_int
    template <class RandomAccessIter, class Div_type, class Size_type>
    inline void
    negative_float_sort_rec(RandomAccessIter first, RandomAccessIter last,
                        std::vector<RandomAccessIter> &bin_cache,
                        unsigned cache_offset, size_t *bin_sizes)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes<RandomAccessIter, Div_type>(first, last, 
                                                                 max, min))
        return;

      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned((cast_float_iter<Div_type, RandomAccessIter>(
            current++) >> log_divisor) - div_min)]++;
      bins[bin_count - 1] = first;
      for (int ii = bin_count - 2; ii >= 0; --ii)
        bins[ii] = bins[ii + 1] + bin_sizes[ii + 1];

      //Swap into place
      RandomAccessIter nextbinstart = first;
      //The last bin will always have the correct elements in it
      for (int ii = bin_count - 1; ii > 0; --ii)
        float_swap_loop<RandomAccessIter, Div_type>
          (bins, nextbinstart, ii, bin_sizes, log_divisor, div_min);
      //Update the end position because we don't process the last bin
      bin_cache[cache_offset] = last;

      //Return if we've completed bucketsorting
      if (!log_divisor)
        return;

      //Recursing
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (int ii = cache_end - 1; ii >= static_cast<int>(cache_offset);
          lastPos = bin_cache[ii], --ii) {
        size_t count = bin_cache[ii] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[ii]);
        else
          negative_float_sort_rec<RandomAccessIter, Div_type, Size_type>
            (lastPos, bin_cache[ii], bin_cache, cache_end, bin_sizes);
      }
    }

    //Sorting negative floats
    //Bins are iterated in reverse order because max_neg_float = min_neg_int
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Size_type>
    inline void
    negative_float_sort_rec(RandomAccessIter first, RandomAccessIter last,
              std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
              , size_t *bin_sizes, Right_shift rshift)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes(first, last, max, min, rshift))
        return;
      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned(rshift(*(current++), log_divisor) - div_min)]++;
      bins[bin_count - 1] = first;
      for (int ii = bin_count - 2; ii >= 0; --ii)
        bins[ii] = bins[ii + 1] + bin_sizes[ii + 1];

      //Swap into place
      RandomAccessIter nextbinstart = first;
      //The last bin will always have the correct elements in it
      for (int ii = bin_count - 1; ii > 0; --ii)
        swap_loop<RandomAccessIter, Div_type, Right_shift>
          (bins, nextbinstart, ii, rshift, bin_sizes, log_divisor, div_min);
      //Update the end position of the unprocessed last bin
      bin_cache[cache_offset] = last;

      //Return if we've completed bucketsorting
      if (!log_divisor)
        return;

      //Recursing
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (int ii = cache_end - 1; ii >= static_cast<int>(cache_offset);
          lastPos = bin_cache[ii], --ii) {
        size_t count = bin_cache[ii] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[ii]);
        else
          negative_float_sort_rec<RandomAccessIter, Div_type, Right_shift,
                                  Size_type>
            (lastPos, bin_cache[ii], bin_cache, cache_end, bin_sizes, rshift);
      }
    }

    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare, class Size_type>
    inline void
    negative_float_sort_rec(RandomAccessIter first, RandomAccessIter last,
            std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset,
            size_t *bin_sizes, Right_shift rshift, Compare comp)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes(first, last, max, min, rshift, comp))
        return;
      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned(rshift(*(current++), log_divisor) - div_min)]++;
      bins[bin_count - 1] = first;
      for (int ii = bin_count - 2; ii >= 0; --ii)
        bins[ii] = bins[ii + 1] + bin_sizes[ii + 1];

      //Swap into place
      RandomAccessIter nextbinstart = first;
      //The last bin will always have the correct elements in it
      for (int ii = bin_count - 1; ii > 0; --ii)
        swap_loop<RandomAccessIter, Div_type, Right_shift>
          (bins, nextbinstart, ii, rshift, bin_sizes, log_divisor, div_min);
      //Update the end position of the unprocessed last bin
      bin_cache[cache_offset] = last;

      //Return if we've completed bucketsorting
      if (!log_divisor)
        return;

      //Recursing
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (int ii = cache_end - 1; ii >= static_cast<int>(cache_offset);
          lastPos = bin_cache[ii], --ii) {
        size_t count = bin_cache[ii] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[ii], comp);
        else
          negative_float_sort_rec<RandomAccessIter, Div_type, Right_shift,
                                  Compare, Size_type>(lastPos, bin_cache[ii],
                                                      bin_cache, cache_end,
                                                      bin_sizes, rshift, comp);
      }
    }

    //Casting special-case for floating-point sorting
    template <class RandomAccessIter, class Div_type, class Size_type>
    inline void
    float_sort_rec(RandomAccessIter first, RandomAccessIter last,
                std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
                , size_t *bin_sizes)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes<RandomAccessIter, Div_type>(first, last, 
                                                                max, min))
        return;
      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned((cast_float_iter<Div_type, RandomAccessIter>(
            current++) >> log_divisor) - div_min)]++;
      //The index of the first positive bin
      //Must be divided small enough to fit into an integer
      unsigned first_positive = (div_min < 0) ? unsigned(-div_min) : 0;
      //Resetting if all bins are negative
      if (cache_offset + first_positive > cache_end)
        first_positive = cache_end - cache_offset;
      //Reversing the order of the negative bins
      //Note that because of the negative/positive ordering direction flip
      //We can not depend upon bin order and positions matching up
      //so bin_sizes must be reused to contain the end of the bin
      if (first_positive > 0) {
        bins[first_positive - 1] = first;
        for (int ii = first_positive - 2; ii >= 0; --ii) {
          bins[ii] = first + bin_sizes[ii + 1];
          bin_sizes[ii] += bin_sizes[ii + 1];
        }
        //Handling positives following negatives
        if (first_positive < bin_count) {
          bins[first_positive] = first + bin_sizes[0];
          bin_sizes[first_positive] += bin_sizes[0];
        }
      }
      else
        bins[0] = first;
      for (unsigned u = first_positive; u < bin_count - 1; u++) {
        bins[u + 1] = first + bin_sizes[u];
        bin_sizes[u + 1] += bin_sizes[u];
      }

      //Swap into place
      RandomAccessIter nextbinstart = first;
      for (unsigned u = 0; u < bin_count; ++u) {
        nextbinstart = first + bin_sizes[u];
        inner_float_swap_loop<RandomAccessIter, Div_type>
          (bins, nextbinstart, u, log_divisor, div_min);
      }

      if (!log_divisor)
        return;

      //Handling negative values first
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (int ii = cache_offset + first_positive - 1; 
           ii >= static_cast<int>(cache_offset);
           lastPos = bin_cache[ii--]) {
        size_t count = bin_cache[ii] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[ii]);
        //sort negative values using reversed-bin spreadsort
        else
          negative_float_sort_rec<RandomAccessIter, Div_type, Size_type>
            (lastPos, bin_cache[ii], bin_cache, cache_end, bin_sizes);
      }

      for (unsigned u = cache_offset + first_positive; u < cache_end;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u]);
        //sort positive values using normal spreadsort
        else
          positive_float_sort_rec<RandomAccessIter, Div_type, Size_type>
            (lastPos, bin_cache[u], bin_cache, cache_end, bin_sizes);
      }
    }

    //Functor implementation for recursive sorting
    template <class RandomAccessIter, class Div_type, class Right_shift
      , class Size_type>
    inline void
    float_sort_rec(RandomAccessIter first, RandomAccessIter last,
              std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset
              , size_t *bin_sizes, Right_shift rshift)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes(first, last, max, min, rshift))
        return;
      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned(rshift(*(current++), log_divisor) - div_min)]++;
      //The index of the first positive bin
      unsigned first_positive = (div_min < 0) ? unsigned(-div_min) : 0;
      //Resetting if all bins are negative
      if (cache_offset + first_positive > cache_end)
        first_positive = cache_end - cache_offset;
      //Reversing the order of the negative bins
      //Note that because of the negative/positive ordering direction flip
      //We can not depend upon bin order and positions matching up
      //so bin_sizes must be reused to contain the end of the bin
      if (first_positive > 0) {
        bins[first_positive - 1] = first;
        for (int ii = first_positive - 2; ii >= 0; --ii) {
          bins[ii] = first + bin_sizes[ii + 1];
          bin_sizes[ii] += bin_sizes[ii + 1];
        }
        //Handling positives following negatives
        if (static_cast<unsigned>(first_positive) < bin_count) {
          bins[first_positive] = first + bin_sizes[0];
          bin_sizes[first_positive] += bin_sizes[0];
        }
      }
      else
        bins[0] = first;
      for (unsigned u = first_positive; u < bin_count - 1; u++) {
        bins[u + 1] = first + bin_sizes[u];
        bin_sizes[u + 1] += bin_sizes[u];
      }

      //Swap into place
      RandomAccessIter next_bin_start = first;
      for (unsigned u = 0; u < bin_count; ++u) {
        next_bin_start = first + bin_sizes[u];
        inner_swap_loop<RandomAccessIter, Div_type, Right_shift>
          (bins, next_bin_start, u, rshift, log_divisor, div_min);
      }

      //Return if we've completed bucketsorting
      if (!log_divisor)
        return;

      //Handling negative values first
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (int ii = cache_offset + first_positive - 1; 
           ii >= static_cast<int>(cache_offset);
           lastPos = bin_cache[ii--]) {
        size_t count = bin_cache[ii] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[ii]);
        //sort negative values using reversed-bin spreadsort
        else
          negative_float_sort_rec<RandomAccessIter, Div_type,
            Right_shift, Size_type>(lastPos, bin_cache[ii], bin_cache,
                                    cache_end, bin_sizes, rshift);
      }

      for (unsigned u = cache_offset + first_positive; u < cache_end;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u]);
        //sort positive values using normal spreadsort
        else
          spreadsort_rec<RandomAccessIter, Div_type, Right_shift, Size_type,
                          float_log_mean_bin_size, float_log_min_split_count,
                          float_log_finishing_count>
            (lastPos, bin_cache[u], bin_cache, cache_end, bin_sizes, rshift);
      }
    }

    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare, class Size_type>
    inline void
    float_sort_rec(RandomAccessIter first, RandomAccessIter last,
            std::vector<RandomAccessIter> &bin_cache, unsigned cache_offset,
            size_t *bin_sizes, Right_shift rshift, Compare comp)
    {
      Div_type max, min;
      if (is_sorted_or_find_extremes(first, last, max, min, rshift, comp))
        return;
      unsigned log_divisor = get_log_divisor<float_log_mean_bin_size>(
          last - first, rough_log_2_size(Size_type(max - min)));
      Div_type div_min = min >> log_divisor;
      Div_type div_max = max >> log_divisor;
      unsigned bin_count = unsigned(div_max - div_min) + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, bin_count);

      //Calculating the size of each bin
      for (RandomAccessIter current = first; current != last;)
        bin_sizes[unsigned(rshift(*(current++), log_divisor) - div_min)]++;
      //The index of the first positive bin
      unsigned first_positive = 
        (div_min < 0) ? static_cast<unsigned>(-div_min) : 0;
      //Resetting if all bins are negative
      if (cache_offset + first_positive > cache_end)
        first_positive = cache_end - cache_offset;
      //Reversing the order of the negative bins
      //Note that because of the negative/positive ordering direction flip
      //We can not depend upon bin order and positions matching up
      //so bin_sizes must be reused to contain the end of the bin
      if (first_positive > 0) {
        bins[first_positive - 1] = first;
        for (int ii = first_positive - 2; ii >= 0; --ii) {
          bins[ii] = first + bin_sizes[ii + 1];
          bin_sizes[ii] += bin_sizes[ii + 1];
        }
        //Handling positives following negatives
        if (static_cast<unsigned>(first_positive) < bin_count) {
          bins[first_positive] = first + bin_sizes[0];
          bin_sizes[first_positive] += bin_sizes[0];
        }
      }
      else
        bins[0] = first;
      for (unsigned u = first_positive; u < bin_count - 1; u++) {
        bins[u + 1] = first + bin_sizes[u];
        bin_sizes[u + 1] += bin_sizes[u];
      }

      //Swap into place
      RandomAccessIter next_bin_start = first;
      for (unsigned u = 0; u < bin_count; ++u) {
        next_bin_start = first + bin_sizes[u];
        inner_swap_loop<RandomAccessIter, Div_type, Right_shift>
          (bins, next_bin_start, u, rshift, log_divisor, div_min);
      }

      //Return if we've completed bucketsorting
      if (!log_divisor)
        return;

      //Handling negative values first
      size_t max_count = get_min_count<float_log_mean_bin_size,
                                       float_log_min_split_count,
                                       float_log_finishing_count>(log_divisor);
      RandomAccessIter lastPos = first;
      for (int ii = cache_offset + first_positive - 1; 
           ii >= static_cast<int>(cache_offset);
           lastPos = bin_cache[ii--]) {
        size_t count = bin_cache[ii] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[ii], comp);
        //sort negative values using reversed-bin spreadsort
        else
          negative_float_sort_rec<RandomAccessIter, Div_type, Right_shift,
                                  Compare, Size_type>(lastPos, bin_cache[ii],
                                                      bin_cache, cache_end,
                                                      bin_sizes, rshift, comp);
      }

      for (unsigned u = cache_offset + first_positive; u < cache_end;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        if (count < 2)
          continue;
        if (count < max_count)
          boost::sort::pdqsort(lastPos, bin_cache[u], comp);
        //sort positive values using normal spreadsort
        else
          spreadsort_rec<RandomAccessIter, Div_type, Right_shift, Compare,
                          Size_type, float_log_mean_bin_size,
                          float_log_min_split_count, float_log_finishing_count>
      (lastPos, bin_cache[u], bin_cache, cache_end, bin_sizes, rshift, comp);
      }
    }

    //Checking whether the value type is a float, and trying a 32-bit integer
    template <class RandomAccessIter>
    inline typename boost::enable_if_c< sizeof(boost::uint32_t) ==
      sizeof(typename std::iterator_traits<RandomAccessIter>::value_type)
      && std::numeric_limits<typename
      std::iterator_traits<RandomAccessIter>::value_type>::is_iec559,
      void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      float_sort_rec<RandomAccessIter, boost::int32_t, boost::uint32_t>
        (first, last, bin_cache, 0, bin_sizes);
    }

    //Checking whether the value type is a double, and using a 64-bit integer
    template <class RandomAccessIter>
    inline typename boost::enable_if_c< sizeof(boost::uint64_t) ==
      sizeof(typename std::iterator_traits<RandomAccessIter>::value_type)
      && std::numeric_limits<typename
      std::iterator_traits<RandomAccessIter>::value_type>::is_iec559,
      void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      float_sort_rec<RandomAccessIter, boost::int64_t, boost::uint64_t>
        (first, last, bin_cache, 0, bin_sizes);
    }

    template <class RandomAccessIter>
    inline typename boost::disable_if_c< (sizeof(boost::uint64_t) ==
      sizeof(typename std::iterator_traits<RandomAccessIter>::value_type)
      || sizeof(boost::uint32_t) ==
      sizeof(typename std::iterator_traits<RandomAccessIter>::value_type))
      && std::numeric_limits<typename
      std::iterator_traits<RandomAccessIter>::value_type>::is_iec559,
      void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last)
    {
      BOOST_STATIC_ASSERT(!(sizeof(boost::uint64_t) ==
      sizeof(typename std::iterator_traits<RandomAccessIter>::value_type)
      || sizeof(boost::uint32_t) ==
      sizeof(typename std::iterator_traits<RandomAccessIter>::value_type))
      || !std::numeric_limits<typename
      std::iterator_traits<RandomAccessIter>::value_type>::is_iec559);
      boost::sort::pdqsort(first, last);
    }

    //These approaches require the user to do the typecast
    //with rshift but default comparision
    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline typename boost::enable_if_c< sizeof(size_t) >= sizeof(Div_type),
      void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
               Right_shift rshift)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      float_sort_rec<RandomAccessIter, Div_type, Right_shift, size_t>
        (first, last, bin_cache, 0, bin_sizes, rshift);
    }

    //maximum integer size with rshift but default comparision
    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline typename boost::enable_if_c< sizeof(size_t) < sizeof(Div_type)
      && sizeof(boost::uintmax_t) >= sizeof(Div_type), void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
               Right_shift rshift)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      float_sort_rec<RandomAccessIter, Div_type, Right_shift, boost::uintmax_t>
        (first, last, bin_cache, 0, bin_sizes, rshift);
    }

    //sizeof(Div_type) doesn't match, so use boost::sort::pdqsort
    template <class RandomAccessIter, class Div_type, class Right_shift>
    inline typename boost::disable_if_c< sizeof(boost::uintmax_t) >=
      sizeof(Div_type), void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
               Right_shift rshift)
    {
      BOOST_STATIC_ASSERT(sizeof(boost::uintmax_t) >= sizeof(Div_type));
      boost::sort::pdqsort(first, last);
    }

    //specialized comparison
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    inline typename boost::enable_if_c< sizeof(size_t) >= sizeof(Div_type),
      void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
               Right_shift rshift, Compare comp)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      float_sort_rec<RandomAccessIter, Div_type, Right_shift, Compare,
        size_t>
        (first, last, bin_cache, 0, bin_sizes, rshift, comp);
    }

    //max-sized integer with specialized comparison
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    inline typename boost::enable_if_c< sizeof(size_t) < sizeof(Div_type)
      && sizeof(boost::uintmax_t) >= sizeof(Div_type), void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
               Right_shift rshift, Compare comp)
    {
      size_t bin_sizes[1 << max_finishing_splits];
      std::vector<RandomAccessIter> bin_cache;
      float_sort_rec<RandomAccessIter, Div_type, Right_shift, Compare,
        boost::uintmax_t>
        (first, last, bin_cache, 0, bin_sizes, rshift, comp);
    }

    //sizeof(Div_type) doesn't match, so use boost::sort::pdqsort
    template <class RandomAccessIter, class Div_type, class Right_shift,
              class Compare>
    inline typename boost::disable_if_c< sizeof(boost::uintmax_t) >=
      sizeof(Div_type), void >::type
    float_sort(RandomAccessIter first, RandomAccessIter last, Div_type,
               Right_shift rshift, Compare comp)
    {
      BOOST_STATIC_ASSERT(sizeof(boost::uintmax_t) >= sizeof(Div_type));
      boost::sort::pdqsort(first, last, comp);
    }
  }
}
}
}

#endif

/* float_sort.hpp
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
*/