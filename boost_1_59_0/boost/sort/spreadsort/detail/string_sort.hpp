// Details for a templated general-case hybrid-radix string_sort.

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

#ifndef BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_HPP
#define BOOST_SORT_SPREADSORT_DETAIL_SPREAD_SORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
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
    static const int max_step_size = 64;

    //Offsetting on identical characters.  This function works a chunk of
    //characters at a time for cache efficiency and optimal worst-case
    //performance.
    template<class RandomAccessIter, class Unsigned_char_type>
    inline void
    update_offset(RandomAccessIter first, RandomAccessIter finish,
                  size_t &char_offset)
    {
      const int char_size = sizeof(Unsigned_char_type);
      size_t nextOffset = char_offset;
      int step_size = max_step_size / char_size;
      while (true) {
        RandomAccessIter curr = first;
        do {
          //Ignore empties, but if the nextOffset would exceed the length or
          //not match, exit; we've found the last matching character
          //This will reduce the step_size if the current step doesn't match.
          if ((*curr).size() > char_offset) {
            if((*curr).size() <= (nextOffset + step_size)) {
              step_size = (*curr).size() - nextOffset - 1;
              if (step_size < 1) {
                char_offset = nextOffset;
                return;
              }
            }
            const int step_byte_size = step_size * char_size;
            if (memcmp(curr->data() + nextOffset, first->data() + nextOffset, 
                       step_byte_size) != 0) {
              if (step_size == 1) {
                char_offset = nextOffset;
                return;
              }
              step_size = (step_size > 4) ? 4 : 1;
              continue;
            }
          }
          ++curr;
        } while (curr != finish);
        nextOffset += step_size;
      }
    }

    //Offsetting on identical characters.  This function works a character
    //at a time for optimal worst-case performance.
    template<class RandomAccessIter, class Get_char, class Get_length>
    inline void
    update_offset(RandomAccessIter first, RandomAccessIter finish,
                  size_t &char_offset, Get_char get_character, Get_length length)
    {
      size_t nextOffset = char_offset;
      while (true) {
        RandomAccessIter curr = first;
        do {
          //ignore empties, but if the nextOffset would exceed the length or
          //not match, exit; we've found the last matching character
          if (length(*curr) > char_offset && (length(*curr) <= (nextOffset + 1)
            || get_character((*curr), nextOffset) != get_character((*first), nextOffset))) {
            char_offset = nextOffset;
            return;
          }
        } while (++curr != finish);
        ++nextOffset;
      }
    }

    //This comparison functor assumes strings are identical up to char_offset
    template<class Data_type, class Unsigned_char_type>
    struct offset_less_than {
      offset_less_than(size_t char_offset) : fchar_offset(char_offset){}
      inline bool operator()(const Data_type &x, const Data_type &y) const
      {
        size_t minSize = (std::min)(x.size(), y.size());
        for (size_t u = fchar_offset; u < minSize; ++u) {
          BOOST_STATIC_ASSERT(sizeof(x[u]) == sizeof(Unsigned_char_type));
          if (static_cast<Unsigned_char_type>(x[u]) !=
              static_cast<Unsigned_char_type>(y[u])) {
            return static_cast<Unsigned_char_type>(x[u]) < 
              static_cast<Unsigned_char_type>(y[u]);
          }
        }
        return x.size() < y.size();
      }
      size_t fchar_offset;
    };

    //Compares strings assuming they are identical up to char_offset
    template<class Data_type, class Unsigned_char_type>
    struct offset_greater_than {
      offset_greater_than(size_t char_offset) : fchar_offset(char_offset){}
      inline bool operator()(const Data_type &x, const Data_type &y) const
      {
        size_t minSize = (std::min)(x.size(), y.size());
        for (size_t u = fchar_offset; u < minSize; ++u) {
          BOOST_STATIC_ASSERT(sizeof(x[u]) == sizeof(Unsigned_char_type));
          if (static_cast<Unsigned_char_type>(x[u]) !=
              static_cast<Unsigned_char_type>(y[u])) {
            return static_cast<Unsigned_char_type>(x[u]) > 
              static_cast<Unsigned_char_type>(y[u]);
          }
        }
        return x.size() > y.size();
      }
      size_t fchar_offset;
    };

    //This comparison functor assumes strings are identical up to char_offset
    template<class Data_type, class Get_char, class Get_length>
    struct offset_char_less_than {
      offset_char_less_than(size_t char_offset) : fchar_offset(char_offset){}
      inline bool operator()(const Data_type &x, const Data_type &y) const
      {
        size_t minSize = (std::min)(length(x), length(y));
        for (size_t u = fchar_offset; u < minSize; ++u) {
          if (get_character(x, u) != get_character(y, u)) {
            return get_character(x, u) < get_character(y, u);
          }
        }
        return length(x) < length(y);
      }
      size_t fchar_offset;
      Get_char get_character;
      Get_length length;
    };

    //String sorting recursive implementation
    template <class RandomAccessIter, class Unsigned_char_type>
    inline void
    string_sort_rec(RandomAccessIter first, RandomAccessIter last,
                    size_t char_offset,
                    std::vector<RandomAccessIter> &bin_cache,
                    unsigned cache_offset, size_t *bin_sizes)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      //Iterate to the end of the empties.  If all empty, return
      while ((*first).size() <= char_offset) {
        if (++first == last)
          return;
      }
      RandomAccessIter finish = last - 1;
      //Getting the last non-empty
      for (;(*finish).size() <= char_offset; --finish);
      ++finish;
      //Offsetting on identical characters.  This section works
      //a few characters at a time for optimal worst-case performance.
      update_offset<RandomAccessIter, Unsigned_char_type>(first, finish,
                                                          char_offset);
      
      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count) + 1;

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if ((*current).size() <= char_offset) {
          bin_sizes[0]++;
        }
        else
          bin_sizes[static_cast<Unsigned_char_type>((*current)[char_offset])
                    + 1]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset]);
      next_bin_start +=  bin_sizes[0];
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while ((*current).size() > char_offset) {
          target_bin =
            bins + static_cast<Unsigned_char_type>((*current)[char_offset]);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = bin_count - 1;
      for (; last_bin && !bin_sizes[last_bin + 1]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u + 1];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = bins + static_cast<Unsigned_char_type>
              ((*current)[char_offset]);  target_bin != local_bin;
            target_bin = bins + static_cast<Unsigned_char_type>
              ((*current)[char_offset])) iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = last;
      //Recursing
      RandomAccessIter lastPos = bin_cache[cache_offset];
      //Skip this loop for empties
      for (unsigned u = cache_offset + 1; u < cache_offset + last_bin + 2;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using boost::sort::pdqsort if its worst-case is better
        if (count < max_size)
          boost::sort::pdqsort(lastPos, bin_cache[u],
              offset_less_than<Data_type, Unsigned_char_type>(char_offset + 1));
        else
          string_sort_rec<RandomAccessIter, Unsigned_char_type>(lastPos,
              bin_cache[u], char_offset + 1, bin_cache, cache_end, bin_sizes);
      }
    }

    //Sorts strings in reverse order, with empties at the end
    template <class RandomAccessIter, class Unsigned_char_type>
    inline void
    reverse_string_sort_rec(RandomAccessIter first, RandomAccessIter last,
                            size_t char_offset,
                            std::vector<RandomAccessIter> &bin_cache,
                            unsigned cache_offset,
                            size_t *bin_sizes)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      RandomAccessIter curr = first;
      //Iterate to the end of the empties.  If all empty, return
      while ((*curr).size() <= char_offset) {
        if (++curr == last)
          return;
      }
      //Getting the last non-empty
      while ((*(--last)).size() <= char_offset);
      ++last;
      //Offsetting on identical characters.  This section works
      //a few characters at a time for optimal worst-case performance.
      update_offset<RandomAccessIter, Unsigned_char_type>(curr, last,
                                                          char_offset);
      RandomAccessIter * target_bin;

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      const unsigned max_bin = bin_count - 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count);
      RandomAccessIter * end_bin = &(bin_cache[cache_offset + max_bin]);

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if ((*current).size() <= char_offset) {
          bin_sizes[bin_count]++;
        }
        else
          bin_sizes[max_bin - static_cast<Unsigned_char_type>
            ((*current)[char_offset])]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = last;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset + bin_count]);
      RandomAccessIter lastFull = *local_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while ((*current).size() > char_offset) {
          target_bin =
            end_bin - static_cast<Unsigned_char_type>((*current)[char_offset]);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      next_bin_start = first;
      //iterate backwards to find the last non-empty bin
      //this saves iterations in multiple loops
      unsigned last_bin = max_bin;
      for (; last_bin && !bin_sizes[last_bin]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin =
            end_bin - static_cast<Unsigned_char_type>((*current)[char_offset]);
            target_bin != local_bin;
            target_bin =
            end_bin - static_cast<Unsigned_char_type>((*current)[char_offset]))
              iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = lastFull;
      //Recursing
      RandomAccessIter lastPos = first;
      //Skip this loop for empties
      for (unsigned u = cache_offset; u <= cache_offset + last_bin;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using boost::sort::pdqsort if its worst-case is better
        if (count < max_size)
          boost::sort::pdqsort(lastPos, bin_cache[u], offset_greater_than<Data_type,
                    Unsigned_char_type>(char_offset + 1));
        else
          reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type>
    (lastPos, bin_cache[u], char_offset + 1, bin_cache, cache_end, bin_sizes);
      }
    }

    //String sorting recursive implementation
    template <class RandomAccessIter, class Unsigned_char_type, class Get_char,
              class Get_length>
    inline void
    string_sort_rec(RandomAccessIter first, RandomAccessIter last,
              size_t char_offset, std::vector<RandomAccessIter> &bin_cache,
              unsigned cache_offset, size_t *bin_sizes,
              Get_char get_character, Get_length length)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      //Iterate to the end of the empties.  If all empty, return
      while (length(*first) <= char_offset) {
        if (++first == last)
          return;
      }
      RandomAccessIter finish = last - 1;
      //Getting the last non-empty
      for (;length(*finish) <= char_offset; --finish);
      ++finish;
      update_offset(first, finish, char_offset, get_character, length);

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count) + 1;

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if (length(*current) <= char_offset) {
          bin_sizes[0]++;
        }
        else
          bin_sizes[get_character((*current), char_offset) + 1]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset]);
      next_bin_start +=  bin_sizes[0];
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while (length(*current) > char_offset) {
          target_bin = bins + get_character((*current), char_offset);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = bin_count - 1;
      for (; last_bin && !bin_sizes[last_bin + 1]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned ii = 0; ii < last_bin; ++ii) {
        local_bin = bins + ii;
        next_bin_start += bin_sizes[ii + 1];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = bins + get_character((*current), char_offset);
              target_bin != local_bin;
              target_bin = bins + get_character((*current), char_offset))
            iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = last;

      //Recursing
      RandomAccessIter lastPos = bin_cache[cache_offset];
      //Skip this loop for empties
      for (unsigned u = cache_offset + 1; u < cache_offset + last_bin + 2;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using boost::sort::pdqsort if its worst-case is better
        if (count < max_size)
          boost::sort::pdqsort(lastPos, bin_cache[u], offset_char_less_than<Data_type,
                    Get_char, Get_length>(char_offset + 1));
        else
          string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
            Get_length>(lastPos, bin_cache[u], char_offset + 1, bin_cache,
                        cache_end, bin_sizes, get_character, length);
      }
    }

    //String sorting recursive implementation
    template <class RandomAccessIter, class Unsigned_char_type, class Get_char,
              class Get_length, class Compare>
    inline void
    string_sort_rec(RandomAccessIter first, RandomAccessIter last,
              size_t char_offset, std::vector<RandomAccessIter> &bin_cache,
              unsigned cache_offset, size_t *bin_sizes,
              Get_char get_character, Get_length length, Compare comp)
    {
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      //Iterate to the end of the empties.  If all empty, return
      while (length(*first) <= char_offset) {
        if (++first == last)
          return;
      }
      RandomAccessIter finish = last - 1;
      //Getting the last non-empty
      for (;length(*finish) <= char_offset; --finish);
      ++finish;
      update_offset(first, finish, char_offset, get_character, length);

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count) + 1;

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if (length(*current) <= char_offset) {
          bin_sizes[0]++;
        }
        else
          bin_sizes[get_character((*current), char_offset) + 1]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = first;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset]);
      next_bin_start +=  bin_sizes[0];
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while (length(*current) > char_offset) {
          target_bin = bins + get_character((*current), char_offset);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = bin_count - 1;
      for (; last_bin && !bin_sizes[last_bin + 1]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u + 1];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = bins + get_character((*current), char_offset);
              target_bin != local_bin;
              target_bin = bins + get_character((*current), char_offset))
            iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = last;

      //Recursing
      RandomAccessIter lastPos = bin_cache[cache_offset];
      //Skip this loop for empties
      for (unsigned u = cache_offset + 1; u < cache_offset + last_bin + 2;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using boost::sort::pdqsort if its worst-case is better
        if (count < max_size)
          boost::sort::pdqsort(lastPos, bin_cache[u], comp);
        else
          string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
                          Get_length, Compare>
            (lastPos, bin_cache[u], char_offset + 1, bin_cache, cache_end,
             bin_sizes, get_character, length, comp);
      }
    }

    //Sorts strings in reverse order, with empties at the end
    template <class RandomAccessIter, class Unsigned_char_type, class Get_char,
              class Get_length, class Compare>
    inline void
    reverse_string_sort_rec(RandomAccessIter first, RandomAccessIter last,
              size_t char_offset, std::vector<RandomAccessIter> &bin_cache,
              unsigned cache_offset, size_t *bin_sizes,
              Get_char get_character, Get_length length, Compare comp)
    {
      //This section makes handling of long identical substrings much faster
      //with a mild average performance impact.
      RandomAccessIter curr = first;
      //Iterate to the end of the empties.  If all empty, return
      while (length(*curr) <= char_offset) {
        if (++curr == last)
          return;
      }
      //Getting the last non-empty
      while (length(*(--last)) <= char_offset);
      ++last;
      //Offsetting on identical characters.  This section works
      //a character at a time for optimal worst-case performance.
      update_offset(curr, last, char_offset, get_character, length);

      const unsigned bin_count = (1 << (sizeof(Unsigned_char_type)*8));
      //Equal worst-case of radix and comparison is when bin_count = n*log(n).
      const unsigned max_size = bin_count;
      const unsigned membin_count = bin_count + 1;
      const unsigned max_bin = bin_count - 1;
      unsigned cache_end;
      RandomAccessIter * bins = size_bins(bin_sizes, bin_cache, cache_offset,
                                          cache_end, membin_count);
      RandomAccessIter *end_bin = &(bin_cache[cache_offset + max_bin]);

      //Calculating the size of each bin; this takes roughly 10% of runtime
      for (RandomAccessIter current = first; current != last; ++current) {
        if (length(*current) <= char_offset) {
          bin_sizes[bin_count]++;
        }
        else
          bin_sizes[max_bin - get_character((*current), char_offset)]++;
      }
      //Assign the bin positions
      bin_cache[cache_offset] = first;
      for (unsigned u = 0; u < membin_count - 1; u++)
        bin_cache[cache_offset + u + 1] =
          bin_cache[cache_offset + u] + bin_sizes[u];

      //Swap into place
      RandomAccessIter next_bin_start = last;
      //handling empty bins
      RandomAccessIter * local_bin = &(bin_cache[cache_offset + bin_count]);
      RandomAccessIter lastFull = *local_bin;
      RandomAccessIter * target_bin;
      //Iterating over each element in the bin of empties
      for (RandomAccessIter current = *local_bin; current < next_bin_start;
          ++current) {
        //empties belong in this bin
        while (length(*current) > char_offset) {
          target_bin = end_bin - get_character((*current), char_offset);
          iter_swap(current, (*target_bin)++);
        }
      }
      *local_bin = next_bin_start;
      next_bin_start = first;
      //iterate backwards to find the last bin with elements in it
      //this saves iterations in multiple loops
      unsigned last_bin = max_bin;
      for (; last_bin && !bin_sizes[last_bin]; --last_bin);
      //This dominates runtime, mostly in the swap and bin lookups
      for (unsigned u = 0; u < last_bin; ++u) {
        local_bin = bins + u;
        next_bin_start += bin_sizes[u];
        //Iterating over each element in this bin
        for (RandomAccessIter current = *local_bin; current < next_bin_start;
            ++current) {
          //Swapping into place until the correct element has been swapped in
          for (target_bin = end_bin - get_character((*current), char_offset);
              target_bin != local_bin;
              target_bin = end_bin - get_character((*current), char_offset))
            iter_swap(current, (*target_bin)++);
        }
        *local_bin = next_bin_start;
      }
      bins[last_bin] = lastFull;
      //Recursing
      RandomAccessIter lastPos = first;
      //Skip this loop for empties
      for (unsigned u = cache_offset; u <= cache_offset + last_bin;
          lastPos = bin_cache[u], ++u) {
        size_t count = bin_cache[u] - lastPos;
        //don't sort unless there are at least two items to Compare
        if (count < 2)
          continue;
        //using boost::sort::pdqsort if its worst-case is better
        if (count < max_size)
          boost::sort::pdqsort(lastPos, bin_cache[u], comp);
        else
          reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type,
                                  Get_char, Get_length, Compare>
            (lastPos, bin_cache[u], char_offset + 1, bin_cache, cache_end,
             bin_sizes, get_character, length, comp);
      }
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename boost::enable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      string_sort_rec<RandomAccessIter, Unsigned_char_type>
        (first, last, 0, bin_cache, 0, bin_sizes);
    }

    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Unsigned_char_type)
    {
      //Warning that we're using boost::sort::pdqsort, even though string_sort was called
      BOOST_STATIC_ASSERT( sizeof(Unsigned_char_type) <= 2 );
      boost::sort::pdqsort(first, last);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename boost::enable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
                        Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type>
        (first, last, 0, bin_cache, 0, bin_sizes);
    }

    template <class RandomAccessIter, class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
                Unsigned_char_type)
    {
      typedef typename std::iterator_traits<RandomAccessIter>::value_type
        Data_type;
      //Warning that we're using boost::sort::pdqsort, even though string_sort was called
      BOOST_STATIC_ASSERT( sizeof(Unsigned_char_type) <= 2 );
      boost::sort::pdqsort(first, last, std::greater<Data_type>());
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Unsigned_char_type>
    inline typename boost::enable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Get_char get_character, Get_length length, Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
        Get_length>(first, last, 0, bin_cache, 0, bin_sizes, get_character, length);
    }

    template <class RandomAccessIter, class Get_char, class Get_length,
              class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
                Get_char get_character, Get_length length, Unsigned_char_type)
    {
      //Warning that we're using boost::sort::pdqsort, even though string_sort was called
      BOOST_STATIC_ASSERT( sizeof(Unsigned_char_type) <= 2 );
      boost::sort::pdqsort(first, last);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename boost::enable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char get_character, Get_length length, Compare comp, Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char
        , Get_length, Compare>
        (first, last, 0, bin_cache, 0, bin_sizes, get_character, length, comp);
    }

    //disable_if_c was refusing to compile, so rewrote to use enable_if_c
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename boost::enable_if_c< (sizeof(Unsigned_char_type) > 2), void
                                        >::type
    string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char get_character, Get_length length, Compare comp, Unsigned_char_type)
    {
      //Warning that we're using boost::sort::pdqsort, even though string_sort was called
      BOOST_STATIC_ASSERT( sizeof(Unsigned_char_type) <= 2 );
      boost::sort::pdqsort(first, last, comp);
    }

    //Holds the bin vector and makes the initial recursive call
    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename boost::enable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                      >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char get_character, Get_length length, Compare comp, Unsigned_char_type)
    {
      size_t bin_sizes[(1 << (8 * sizeof(Unsigned_char_type))) + 1];
      std::vector<RandomAccessIter> bin_cache;
      reverse_string_sort_rec<RandomAccessIter, Unsigned_char_type, Get_char,
                              Get_length, Compare>
        (first, last, 0, bin_cache, 0, bin_sizes, get_character, length, comp);
    }

    template <class RandomAccessIter, class Get_char, class Get_length,
              class Compare, class Unsigned_char_type>
    inline typename boost::disable_if_c< sizeof(Unsigned_char_type) <= 2, void
                                                                       >::type
    reverse_string_sort(RandomAccessIter first, RandomAccessIter last,
        Get_char get_character, Get_length length, Compare comp, Unsigned_char_type)
    {
      //Warning that we're using boost::sort::pdqsort, even though string_sort was called
      BOOST_STATIC_ASSERT( sizeof(Unsigned_char_type) <= 2 );
      boost::sort::pdqsort(first, last, comp);
    }
  }
}
}
}

#endif

/* string_sort.hpp
+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
*/