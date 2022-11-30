//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Orson Peters  2017.
// (C) Copyright Ion Gaztanaga 2017-2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// This implementation of Pattern-defeating quicksort (pdqsort) was written
// by Orson Peters, and discussed in the Boost mailing list:
// http://boost.2283326.n4.nabble.com/sort-pdqsort-td4691031.html
//
// This implementation is the adaptation by Ion Gaztanaga of code originally in GitHub
// with permission from the author to relicense it under the Boost Software License
// (see the Boost mailing list for details).
//
// The original copyright statement is pasted here for completeness:
//
//  pdqsort.h - Pattern-defeating quicksort.
//  Copyright (c) 2015 Orson Peters
//  This software is provided 'as-is', without any express or implied warranty. In no event will the
//  authors be held liable for any damages arising from the use of this software.
//  Permission is granted to anyone to use this software for any purpose, including commercial
//  applications, and to alter it and redistribute it freely, subject to the following restrictions:
//  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
//     original software. If you use this software in a product, an acknowledgment in the product
//     documentation would be appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
//     being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_ALGO_PDQSORT_HPP
#define BOOST_MOVE_ALGO_PDQSORT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/detail/workaround.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/algo/detail/insertion_sort.hpp>
#include <boost/move/algo/detail/heap_sort.hpp>
#include <boost/move/detail/iterator_traits.hpp>

#include <boost/move/adl_move_swap.hpp>
#include <cstddef>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {
namespace movelib {

namespace pdqsort_detail {

   //A simple pair implementation to avoid including <utility>
   template<class T1, class T2>
   struct pair
   {
      pair()
      {}

      pair(const T1 &t1, const T2 &t2)
         : first(t1), second(t2)
      {}

      T1 first;
      T2 second;
   };

    enum {
        // Partitions below this size are sorted using insertion sort.
        insertion_sort_threshold = 24,

        // Partitions above this size use Tukey's ninther to select the pivot.
        ninther_threshold = 128,

        // When we detect an already sorted partition, attempt an insertion sort that allows this
        // amount of element moves before giving up.
        partial_insertion_sort_limit = 8,

        // Must be multiple of 8 due to loop unrolling, and < 256 to fit in unsigned char.
        block_size = 64,

        // Cacheline size, assumes power of two.
        cacheline_size = 64

    };

    // Returns floor(log2(n)), assumes n > 0.
    template<class Unsigned>
    Unsigned log2(Unsigned n) {
        Unsigned log = 0;
        while (n >>= 1) ++log;
        return log;
    }

    // Attempts to use insertion sort on [begin, end). Will return false if more than
    // partial_insertion_sort_limit elements were moved, and abort sorting. Otherwise it will
    // successfully sort and return true.
    template<class Iter, class Compare>
    inline bool partial_insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename boost::movelib::iterator_traits<Iter>::value_type T;
        typedef typename boost::movelib:: iter_size<Iter>::type  size_type;
        if (begin == end) return true;
        
        size_type limit = 0;
        for (Iter cur = begin + 1; cur != end; ++cur) {
            if (limit > partial_insertion_sort_limit) return false;

            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = boost::move(*sift);

                do { *sift-- = boost::move(*sift_1); }
                while (sift != begin && comp(tmp, *--sift_1));

                *sift = boost::move(tmp);
                limit += size_type(cur - sift);
            }
        }

        return true;
    }

    template<class Iter, class Compare>
    inline void sort2(Iter a, Iter b, Compare comp) {
        if (comp(*b, *a)) boost::adl_move_iter_swap(a, b);
    }

    // Sorts the elements *a, *b and *c using comparison function comp.
    template<class Iter, class Compare>
    inline void sort3(Iter a, Iter b, Iter c, Compare comp) {
        sort2(a, b, comp);
        sort2(b, c, comp);
        sort2(a, b, comp);
    }

    // Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
    // to the pivot are put in the right-hand partition. Returns the position of the pivot after
    // partitioning and whether the passed sequence already was correctly partitioned. Assumes the
    // pivot is a median of at least 3 elements and that [begin, end) is at least
    // insertion_sort_threshold long.
    template<class Iter, class Compare>
    pdqsort_detail::pair<Iter, bool> partition_right(Iter begin, Iter end, Compare comp) {
        typedef typename boost::movelib::iterator_traits<Iter>::value_type T;
        
        // Move pivot into local for speed.
        T pivot(boost::move(*begin));

        Iter first = begin;
        Iter last = end;

        // Find the first element greater than or equal than the pivot (the median of 3 guarantees
        // this exists).
        while (comp(*++first, pivot));

        // Find the first element strictly smaller than the pivot. We have to guard this search if
        // there was no element before *first.
        if (first - 1 == begin) while (first < last && !comp(*--last, pivot));
        else                    while (                !comp(*--last, pivot));

        // If the first pair of elements that should be swapped to partition are the same element,
        // the passed in sequence already was correctly partitioned.
        bool already_partitioned = first >= last;
        
        // Keep swapping pairs of elements that are on the wrong side of the pivot. Previously
        // swapped pairs guard the searches, which is why the first iteration is special-cased
        // above.
        while (first < last) {
            boost::adl_move_iter_swap(first, last);
            while (comp(*++first, pivot));
            while (!comp(*--last, pivot));
        }

        // Put the pivot in the right place.
        Iter pivot_pos = first - 1;
        *begin = boost::move(*pivot_pos);
        *pivot_pos = boost::move(pivot);

        return pdqsort_detail::pair<Iter, bool>(pivot_pos, already_partitioned);
    }

    // Similar function to the one above, except elements equal to the pivot are put to the left of
    // the pivot and it doesn't check or return if the passed sequence already was partitioned.
    // Since this is rarely used (the many equal case), and in that case pdqsort already has O(n)
    // performance, no block quicksort is applied here for simplicity.
    template<class Iter, class Compare>
    inline Iter partition_left(Iter begin, Iter end, Compare comp) {
        typedef typename boost::movelib::iterator_traits<Iter>::value_type T;

        T pivot(boost::move(*begin));
        Iter first = begin;
        Iter last = end;
        
        while (comp(pivot, *--last));

        if (last + 1 == end) while (first < last && !comp(pivot, *++first));
        else                 while (                !comp(pivot, *++first));

        while (first < last) {
            boost::adl_move_iter_swap(first, last);
            while (comp(pivot, *--last));
            while (!comp(pivot, *++first));
        }

        Iter pivot_pos = last;
        *begin = boost::move(*pivot_pos);
        *pivot_pos = boost::move(pivot);

        return pivot_pos;
    }


   template<class Iter, class Compare>
   void pdqsort_loop( Iter begin, Iter end, Compare comp
                    , typename boost::movelib:: iter_size<Iter>::type bad_allowed
                    , bool leftmost = true)
   {
        typedef typename boost::movelib:: iter_size<Iter>::type size_type;

        // Use a while loop for tail recursion elimination.
        while (true) {
            size_type size = size_type(end - begin);

            // Insertion sort is faster for small arrays.
            if (size < insertion_sort_threshold) {
                insertion_sort(begin, end, comp);
                return;
            }

            // Choose pivot as median of 3 or pseudomedian of 9.
            size_type s2 = size / 2;
            if (size > ninther_threshold) {
                sort3(begin, begin + s2, end - 1, comp);
                sort3(begin + 1, begin + (s2 - 1), end - 2, comp);
                sort3(begin + 2, begin + (s2 + 1), end - 3, comp);
                sort3(begin + (s2 - 1), begin + s2, begin + (s2 + 1), comp);
                boost::adl_move_iter_swap(begin, begin + s2);
            } else sort3(begin + s2, begin, end - 1, comp);

            // If *(begin - 1) is the end of the right partition of a previous partition operation
            // there is no element in [begin, end) that is smaller than *(begin - 1). Then if our
            // pivot compares equal to *(begin - 1) we change strategy, putting equal elements in
            // the left partition, greater elements in the right partition. We do not have to
            // recurse on the left partition, since it's sorted (all equal).
            if (!leftmost && !comp(*(begin - 1), *begin)) {
                begin = partition_left(begin, end, comp) + 1;
                continue;
            }

            // Partition and get results.
            pdqsort_detail::pair<Iter, bool> part_result = partition_right(begin, end, comp);
            Iter pivot_pos = part_result.first;
            bool already_partitioned = part_result.second;

            // Check for a highly unbalanced partition.
            size_type l_size = size_type(pivot_pos - begin);
            size_type r_size = size_type(end - (pivot_pos + 1));
            bool highly_unbalanced = l_size < size / 8 || r_size < size / 8;

            // If we got a highly unbalanced partition we shuffle elements to break many patterns.
            if (highly_unbalanced) {
                // If we had too many bad partitions, switch to heapsort to guarantee O(n log n).
                if (--bad_allowed == 0) {
                    boost::movelib::heap_sort(begin, end, comp);
                    return;
                }

                if (l_size >= insertion_sort_threshold) {
                    boost::adl_move_iter_swap(begin,             begin + l_size / 4);
                    boost::adl_move_iter_swap(pivot_pos - 1, pivot_pos - l_size / 4);

                    if (l_size > ninther_threshold) {
                        boost::adl_move_iter_swap(begin + 1,         begin + (l_size / 4 + 1));
                        boost::adl_move_iter_swap(begin + 2,         begin + (l_size / 4 + 2));
                        boost::adl_move_iter_swap(pivot_pos - 2, pivot_pos - (l_size / 4 + 1));
                        boost::adl_move_iter_swap(pivot_pos - 3, pivot_pos - (l_size / 4 + 2));
                    }
                }
                
                if (r_size >= insertion_sort_threshold) {
                    boost::adl_move_iter_swap(pivot_pos + 1, pivot_pos + (1 + r_size / 4));
                    boost::adl_move_iter_swap(end - 1,                   end - r_size / 4);
                    
                    if (r_size > ninther_threshold) {
                        boost::adl_move_iter_swap(pivot_pos + 2, pivot_pos + (2 + r_size / 4));
                        boost::adl_move_iter_swap(pivot_pos + 3, pivot_pos + (3 + r_size / 4));
                        boost::adl_move_iter_swap(end - 2,             end - (1 + r_size / 4));
                        boost::adl_move_iter_swap(end - 3,             end - (2 + r_size / 4));
                    }
                }
            } else {
                // If we were decently balanced and we tried to sort an already partitioned
                // sequence try to use insertion sort.
                if (already_partitioned && partial_insertion_sort(begin, pivot_pos, comp)
                                        && partial_insertion_sort(pivot_pos + 1, end, comp)) return;
            }
                
            // Sort the left partition first using recursion and do tail recursion elimination for
            // the right-hand partition.
            pdqsort_loop<Iter, Compare>(begin, pivot_pos, comp, bad_allowed, leftmost);
            begin = pivot_pos + 1;
            leftmost = false;
        }
    }
}


template<class Iter, class Compare>
void pdqsort(Iter begin, Iter end, Compare comp)
{
   if (begin == end) return;
   typedef typename boost::movelib:: iter_size<Iter>::type size_type;
   pdqsort_detail::pdqsort_loop<Iter, Compare>(begin, end, comp, pdqsort_detail::log2(size_type(end - begin)));
}

}  //namespace movelib {
}  //namespace boost {

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#include <boost/move/detail/config_end.hpp>

#endif   //BOOST_MOVE_ALGO_PDQSORT_HPP

/* pdqsort.hpp
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
*/