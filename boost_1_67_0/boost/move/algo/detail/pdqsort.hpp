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
        typedef typename boost::movelib::iterator_traits<Iter>::size_type  size_type;
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
                    , typename boost::movelib::iterator_traits<Iter>::size_type bad_allowed
                    , bool leftmost = true)
   {
        typedef typename boost::movelib::iterator_traits<Iter>::size_type size_type;

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
   typedef typename boost::movelib::iterator_traits<Iter>::size_type size_type;
   pdqsort_detail::pdqsort_loop<Iter, Compare>(begin, end, comp, pdqsort_detail::log2(size_type(end - begin)));
}

}  //namespace movelib {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif   //BOOST_MOVE_ALGO_PDQSORT_HPP

/* pdqsort.hpp
sjFeBgRhNFJH4nM5GSNPfGtg5wRSNALQqwf2mL06szaPpdnCcvuzuV4pXThRjxERYTg/JZet2TyGJYzwIYZZYh1LnwOWUgvLqA3L3y0sX/SYtHs8Ro2Xwo/ktVA8Tzsg2qiNaLOCaPtPIdHqgGj9zxYjWsBCdMfTAtFUGMR+Nj8K/PCCIWK5UCl3nRLyoOvYKf7dt7TRHD/gQFdEpesFTPNHQqN07MYNsjgXfm+WvhPClWP4Q2t/HcNf+2oBw2O1Qob/5wpg9i7B7Nvhw0wCkxXMjZFMLztrJq9Y+dqQwQ/2kjQszUvD444CaVj2+6ShoaeYNGyyCL109x8hDWdPC2nI8MO7TXz2gd1i4dv273OlgVyzdewBX/2N0PmiC/yqbzAZHS0XSCrOmeU5TbVbUOowtfxiS02WpGBeWGS13fmGWG0XGbJ//GQOWfSVIWNXW6pTCsBr0/viJTnzfw7rqcRWan8+/5+k/0267/0/Gcdv3k988q97i+8nTl6K+4n/B3iIiSvqNQCAQ0usXX90U1WeT5O0DRBIlADVQeyeRRe3nDlo1ANGfvOK45CSpNOEORJ/7Gonm3EdfyQCrqkwbUbfXuIwSjmgMOrsnFl2Ra1H1DLCboQurVKklA4W27Gd3bJz2XbPVMVSbCH7/X7vey8vadLinPUPbN5998e793vv98f9fr+fce2Juz/Oa0/MNidG9ObEH30Lc+LuZS9lmBOh+srQo2MffjeHjTFDGBfksPEdQQ453iY9s/+4Tp9Ho3mjaZlhM7kUXgUS9iQNT82cOulMakq8mA+unw+rMcO+mmWhXIyfDdMQH7xERvpPYUIuIUh7YuBS1hQcKNm0Tw0PUIsVgPj4FrRKFvpB2xHNiXnELKpx/Ave51pzuJkOzNa3xXVtRW9CvA7lUQZa2cClzBm6gUxe47+ZpQaJuR99WzN84fy6rWy5Ba3sZeWWsgJT0S7n4bLDrMouG1m5uazcem/ZcrNpuZW5HVQiF2Tay/G+uQitWSDpz4mnYFlAKzSDVqgoDCpDWEKm9qwrm9dKNyngzeqZUohP8D8dXs6CY+PdB2dCDKFHmGKpWj4bvYY33iUUjOUITGnxhdbv2C34svMjWLldaXyZLNyfsbfFuZF+crldZdmTNh7LaS8fix8ctdKF2aKYJXq91psFU0D8F36axQNdptrPnRb3P21Aa+8YnwuONgqlVToox5oQ5MVtYVeRLspiB+WFLJaUN5pZrIn01BZQSsn3EJRJCnWWuj1edvc6xEOK3syqugsQg7i3QOLCi1uPVFyEQMUVZgQq9lsQqLhcOPwdVNT89JD1E9lQ0P/XwgV0H7/TeUiNl2ss6HrWcCTtxMm3/U8qdUtOkNHvv6USrJjPlmMTxVuR9406Ld1ysE9YIFq9msXMCMookv5V6A2sWWN6QXFn0T75UdD2ufwougTi7KxPnUTbE0ZmVtfGWifZ4uReLHWgbiILz1wvJv8CdUpYlFDZtSOFAbUgkQ3L7gHQqWdrJg/SqPVMU15CXPY2nEgcU+o0zW23N3Vam1er3mKCpoMxKrGuDfxaaqOq2zemjVzEmyPkSMH7O66b71X5PPDalB2Ic98nbBvWgIfftJIsaS7JHr0NJjzg5f+8gp78i2Ez+pSiLr6E4tCqrPJMOYb+0aZmqQ2bOne9iYwv0Mx/rlAMcjdGA6KZ+3XNRFaqzRTLS+RYn64Nwumx4h7qA06Qc3er9iG31cs/W6FFQXS6Ltier6P08w0+jXAm460WYcVBo8KMiC6ix9NmxKkM71AwxctSnGcHzvNH7Gi2sXWQCWNrCxpb7cxnTURb/F6E/XZ3eomAOpulXjKNXy6wbf0Y5exohxzt7rem75uj3cKQZGPuXpXeG9DCSvYYe3qdZbTvNC6K8UgFfE6WXbXZttVJCABYDyi8YVJ0HvsCpOF1rhN6m2qGjYcdhTb7b2fBBjxZb8FIU7GPSlhwv7xOWDUP+ph/Lhk2WbAP+/kVbZxBOYaG2KvUGcwyxF4N+x56rgYu5PNCi1JSRnOk/FCTOgCzkEoduFOwAveRH6yV8lTNcM2JTHf1wJtTYKiV0PccdHxbQi1LrfqPcPVEK0Si8QxLlVjFzM+VemulbvsycnjutD2/BQ1YCzUTbYMsNfJDv1HTlovW0sbQsa0hfUzy8M9lNSPMZDShZo7BhCjk4mxV6ft6eU5u+tYvTN5NLfbzzuOZ+QxzmFMt4RuFYArnlqzda5mF1C+g/CweVUQ9PUJz/4GRAq1H6fy31V2Dd0MObAUDAeWHBmQ31zekpjHD3L/bR9KrVwj8yzUtMotEPCA9C5LeNNltERenmGMoi1O7LfGPbHVoMw3biFwGkFygy+z+LGp/c3X9Tfr2/aFHxGLsIXtm9OxPWY0xIUL3ZMgSlvyyxD358NTO6Ndvbq7zmI4CZ1c1XkOgv+co5sXSjrACYHQkJGDSVo339RHv48T7BkKT7Kia3L0emKBgfp2C+bUB8zsubmqR+R2mQ8jK7H5lAxvTgtVF10jkb4nJPVLp4X+xWLmvHWTplMVGVhQ2iDuMx5bQHUbtiC16dah1mRK9ogjFcLxZ/F6+WAQziHjDdKDB7fGhyBT/AZQceVhkWTUoTLCqLc37UNxJnc6R8/OIrgLOk1ahqhdqj8cjFfvzJ/r7iXzGZ3cJ+qdLVnK3dzjbMU1MlXplyKbi6F0fR6bKmC1JHLj91XJVB24TTWnDrF7CSDzq4Ws7zqSciOu063C83fbcJCOJJLj1LtOdRrfXw4+JGYOHz3WgOTLWbbDVfazBQHXwa/8AL8BTncDZjU1gGIhK8Oc+pSDETsXUNQWkxATwKB8Pntdaf4Ba74TWAwXC0D1NGIvqigigqDuMnoUPExEgikrddGI4nWEDsPKq9GOUDfl/DKZS1bXD02w//TV5MlpZucXnSay1cFf5AXIH3Crymfd6FenUzV0Vlpqrw0a+6SZMl8MvdCasK+DEwaO43AolJn4flrgHoMS8HCowv6VsplzVArKD31rmN8tVbZGFZVJfmbtXljq6pI7Pom2yu61Lavss2vL5h91Tt+17xXCGf36mp3eoqfCpqYgFn4wUNRvSKD+d/FhPKg3w3s0Pwk86AM7tQPN/V6QU5i5s8PHpdyjijC06tRLfvPoLNE9tel9t6KeZDT0BP/srlZAo/ZHRP0887Mh4OD3HQ/36jiMBkop45p+ExE36t0N8pkGJkqkCNUSyezCCj49SaIcji7+UnNDL53n9g6ygNCpqDMqMHerteWVlQuoIwDndw3dD+yzWAV24RqLTlC9wJs89WYCcplOoFZ1ePPQXslnyQ62y1AZ7J0A8tyiMWDpm3kzmUZB7owvSMWVjpkW5y4TGkXGp+QsxhZjObZ4FO7GvhyhtEJpRLcwE2m4l3YFOpt4mfZlK2d5Lim1Rh5bOzbEewpaq4hj2FOuN2kBGLTeDDiVXgLTbU+AqN8dM8MRVYa0xwTPXkphRXuLyW+CX35IqNG/Ck6zTl7/raeFC6rz7S/pUTA8M0+bsOudKiQw29P502M2VqTb1i20wAQGkANLPsglLI5eOfJxMo5bXX8vUz2pPTJQvGdebk/IPSzFNU4GuwycwzWpMlmQFYqAwOf7CNzCW6ABQAgzyAddXkWBGNCRdhPv5/IVmykXSZCUknRNqzhFeoEKcqkwD5ZRp0C26heTgCNBICMPpsQlhA+IijcwodG1hRUAs/tTJXDVz8OvUCZ09CoN2ctuj1HCqmAUNAcnQf5vQjS0xeRQvM0ZHxFWDVz5kgAfVctwC/+P9vxInJ5y3eMLw16+5kPKHCxB7+YGQwY4xEaMYEzEILHJj6Nbt5LRITqKhB7fuNgREuq3m+DA0fx4P7GRkeqIef/kSCezBi4GzbfDe+iZy6gxhZRpC/7yQ3ax2EMLKiXqs4WODeIW57fiZlPJ+gsYKn2IeVY1gFBiKcDf0zKuulPzuqEBNNKgv5wqkI6K7/ZXc/olwRDmTKMttuQj1n3mysDFgKN4cT26UMHgjZkk8BkzAjsmNvP6Asys1w/IRJcKCN6a7jm6wRUuc7dWyYwP0c+Se4BFnslo2b/jgKWhDeTJ2fX/cplvfVca8988iyhTExnjDJVLFga/Le/aTtY64eyKJtkd4lqRnpehsXI9/+xLxg2ig5K8Lfq4cldsW0ZvA0fHcDA1vRZfPg1RXCcG11SfvOCKQ7NkhfLcSWGT7XtRxgZA9oXmo3iZasMDLf/mqcCOpb8Iu/c1x/P98eIP/Zi+GwEauWXQIEUkj/gQVefz8RSqI/lFZaWcSVrkRP0KOY298hBiERSSWVIamhb7Rm0piLfIojHfDg/6D7F2cn0Q9vu7DFJq0ieM4UWrSJ6WpnHG/RB6z9uQgD2W9BtPr1bjqWvi8evjwfGwqaJH3NJ7FLXjwrNiCadptOYuD0PKbK7/7MA1WvAH+9tAWTCRa4W8vrz2DMb7RaxP1+J4PA+EEzWPD595SkSAcnbjDsPqHfzI6h1CEegpFu+toI9e9i41h/DptvlNyfP9Zunp7PGSmK+ZuIiFeRJ1F1ibqu4l+Ek1ndQZok/obOwvr8+wqz5F84slnysR3iWc02dSdR6x2ueuC7adhKDp3inZ/K8jePudHIVylajmBP1MzzjcJD9/78F6iASi0mk3dj4R6CMtliYPyPAA741ASGq5ms8RnxFsv4onh5l6QgTkIeUorIwa1MOExMnjfUps0YgTi12WHTw6zwS2Xsbqt9hSBG9Tji7B3cApgzA/SvZ6VdV7o+k7XSgF8V117MIrF6xN19H9bfKeAc+HeUCMOs74DTiQalI/vgT8T8Q5SHh0wgG05+r+Mh84UPDYENa8R3ScOYTXWdqAQWir7RpEv4FSeYXvfUVwdb49Yq2U7NFbxvei5fjO0aKrlRkazggEDFoo3gfmpbYb+2qNfiwmLd0UnVS+63hY/jJeY4kPhGNGvtdmjEqYWDaq8QAuawAX1igUds9pE+Vn0KjaCJvQqbY8JLh0T00nbcvOujG0p9qPr5ER4zXRyqlCLvR41hnGuFkQ76EW1/rr0aaPHq16QI02cLs1XjlBXwpRUPeb4h4fQG8f11ZNeP79jo7DaDYNiEfDrMlPx1+EtxKwhFEGQGyn9VgDD/18TJZOZ1Gt7/66rQSsJ8OEN1M54I6tGw+CVyBePn5wIr0F+aPADRX5xpnTIfkKXV7A7MVE+avq/1ecFXEz76ecUi5IGEbTF69UHupe2UPx46xq60tkQuv/kL+Fn0xoRbCGi0tInDXCM3jX7dMi28CAJDyoxQEP5f98aYauHP/kajP4YgA+Atu9fPA1OxMgPF/8RRKRIMRR3rsH7tG7x/rfKrX6kWRrAZhSW2uj+6lnDETZy5W2OJwSK9fmm4Rfj3l+J+AjE3lLushBfzM/X3ioSQSk3sHU7XjaEuh/GFHlKNHtqxtO/r1cKtsI/yCrTT4bf1D0xX9xjoKzI6hMU0WrOD5E5JX8GwCvJR5idjRAlb1ANH/jtELqrenmoeQgkd5LJEdRcASkJWZa/BEMY6cNCKxqGCPpSKXTcsBsKP+8bUoSdzKRp4963ZeWniVoCQPFSq0eOtcqxNtC8aswUAGtVU+e0gSKPdpWw0edpljrmoRj9axCjPfzeawlp5TpkBn5haMDwWJHk5r3t4iQL+APhBakZe0UaGSh3Hr+X79qu6c+1A6H0eECZrmRBuyztYwYcmyztZUWy1G0yBdAz0SZLfc6k7O41ufcisVMcgCwNJ6T9Hjg1wkZKHx3diTARwd3N0n4abIAG+/Y1NFg7Jl5PUFJDHG+/PUywYmGDNsiZzMmk88w9zIL7yqSBMvcgW8q+g5gTwYb40DOFLFrSX+QarDHCru16xsKCs6Ggv9h1BrRRN6IouE7FjOwUCw66RmKFbEQO7oWHpk7XqZpiVjVQdtrUBmWmM66RmiksNlgWazBdhNZZbCAxe6Zp2NWje62BSYOm4N7EnRZXD4s11BSVNZta+k3MDU3uJH1z0fToDBZ8ddGU6DQW3L3IGS2GYS9yRTBmKbhTns6qXpUnM/duVrVPvhkWQL5DhC3OejG//Nd78orwOisFnE9oNijxfn5zKcH3+JW9x3/RhMRpD7W9/7JI7y+SMSrHSGhn8R6R9k917Sd2IBCx3/OKhOQBEjP4ha3006y8AbyHb/equRYLaVM4euvHSaMj+F1fjszl4gpRhd6rFAmp/VomziIhTfOv/3eIzOFHJ0pAKOZvdftE/EbNp4NjR45RiSzj1gIBiIFIJOyT6trh9YInqHAwpqcdlC9PhSq5w1b3qYAAG9Sz+jSS7TQEsFDPjP75mIUoVAiL5eV1cy5o+ezVF0TtARUbBh8jx2PDtaDRTFXhlu5yDUcmi1KCnlGOLA1bfrB/mTreghpXxnjXR8oqYefREDy8QBtCFjLTlYzgmfQI+p9If9Yb113QQD9ztQnn6YeUVDADCTA0P6BLD0u4SmO+Sq3/gah/ZZgEqn/+K+0TyW/hhfy2x0jgkaVeSmLqOhqxw+y18BtkjHORY4P9hZhn97JqdzrBC2WRE8mB3oZRi+15lDJYkJwxbySjstX1qMWWuBb/XmZO3PkudmVqFhBxOhRzJtnpxS8M9CK90ZfOkwSHMhW364q5VmxyPQFl72HZSlGWFjzNYYM+81U6OVafHjpcJKEd9PDvPmdWNu6AfuNy/cbNTm6lbORyF0zAViNOTGwQ5ub3z5oRK8oOf7bCnwG+4+/NWW5iyhrx935izsInuqL1iv9EWy/0ScGbWlqvKHTHOuFohPWCofSo63WMVz0r1qusQPhWlaPnyvMz0d+yS9V3UrbnboEHrmFbAkOnWbnZdGTMerlqYManqMW1SXPmelExeuMqxZas9cLi4+lia+aSUfGbopitKrF7vs0KPvyzP3sFYTpW1x5xwJdvHUK3UuAtx/hMaC/eBct4jBfCn5X8xI/zLeOfYIGV9Ss+9W3sTSBXRNGGgUqoMNuwEzJZWOQ9TfRvC/3bSv+20b8d9G8n2ViEdvM350BQI0MRI/OQ1+fnc74mRRg6aY43KsaZhUG7re5l8pcVJhpdusfQ3OUvKUauNAAWLOnTX0yQoUgxDnm1bPH85CcgP6rGLzT9kEDr4QfeVLE7THrWCHrr/ks6RbRA7UdlgxNajM7+41iJAeW3DyPB1A140mr+iPLypzPyIYTfeGHcfAgXNZdOVbpXIQJVk+/qNR6dVI/HdO5sB6K/fy194cryYemwCGOjIHcqPcS7oqbEPxSgARLR3zyBkIEMuXMpGLvmRg9NLO8RCMSVXn15OEWYNj3j5dv7fxhf4b/jxcmYEZZOMMLSCUc4Rp4ho3AAMxIRCtZqaxoTjq21Y7KagEP2O9jq2XL5bLa2VK4oZYF5sn8eWz3/Prl8foZPo/j+YPnE+TGw04yM6InVcMxh4jdN0llr8RLMnXruJQJWH41NPenYaky0w9Y65AoHC5TI/pLMUc6V/XPZ6nly+Ty2dr5cMT83hJ0+kQbm22I/NPsDuAT86b8zkz/lgvgQ/HoEftVeTkXnsE0WZxKYzwxQAm6BoqnLag+bXc2Pf8m/jxVqrPFUdC77HjAAu7P9whcrXCefmJEwv0j5kBZCmWUF5t46+fiX6IMgWeVFoJLE7LVHzX44mBTQPfyVWKvADMLSKblIFX/nUxPjUwLPx7RDjaE3KFPxQFbGOgcVvvrmbkNmYkUmlYASVcwMsmTvL26W0MhqgCM05FiFHgklAS8fliiNp0hsnGYeaB4jPhEEflTlqPTxpbtGFHAUk14INeoRDgo0hIPQ+ZUEKxzw8B2iB1lyaPimggM5PBpXKqn08s93qh0UZgAZmrNgE1Rk5jbsocoR8PFbJQ1kB7NHYoI2areSh2nQVqArUVcZam2NfVJNcXM5zUdo70oVrb1/lYbWHjbomvlLtRlHRpK70OaVKoD921pNC8oVWs1zO5WaszNr/gBruu2wABu0mpMy+nxLrVmaWXOBNtrFWs3JGX1G1ZrzMmtatdGatJpTMvp0qTXn50jml23XG8iZKk0PIKnkG+jQ6DsPcasESeTyo5UKQarU/UkOkqzkpTtoqNmivaA7twUmds5Khe6sqpNXhTWNRK9986f1mQ1ZMsjLCvP8uxWNyht0jVuRQWEt9bnHsVervkOrTgkOKxz66nKe6pu16gGtOm3eitn66nfnqf4DrXqJVp3yGFaU6qtPyVN9gVb9zHK1ehFVn6ev3ro9d3WrVv0lrXoxVZ+vr57IXT0/iPGfRU+zll8BPYHE+sr2Y6lxqKlt2RVQEzSzTt/MWFqSl+WlJag8si3HGNKUtGZZXkqCyv+WqzLSUYCg423L8tIRVN6Sq3KaitqX5qUiqLwqV+U0DdUvzUtDULk4V+U0Ba1bmpeCoPLHPx9beSL6eaRDry+OtQCjd/GomjlXJ+/rrRBGnbAXuoHwagYUpwoh8IZu1IPYCJTsAbpI4ac3CXsZmpM9COvBmzalAfx0rNWkt4IZ9XDqBfrUBjoA8PHAb7Tvn/o73fffmnsL6fMJG7K+vUD94FxfSgjw2hUyotAnNRzK3rQRRw/cWqRhtb5TjO6p5Q8iYg7mKar7Axngkx7CQa3qBnlxHf+rIfR9TCrz2fF/3D0NdJRVdpPkSzLgwIwwSJSoqRtrFrM1mrQnMcQdITPJFiaZmZAZtpKQttlsNsY9VGdY2iZZPZPZ8p3HZ+1KVo5i1dZ22S61nFWX6GIN0cMAporWlQSCsltW35AcDWgxCGX67n3v+743k1/c9pyeqqjzvXffz3333vfufffdG6A/2Ir4tAp8DgdoeKuOzwVmRlheZViyJL6rR28+yvViPn4IRzAegJyutJi3vFC0PBSg1xktT8kZOyS1fCgtBaikges3Fui7GLuROzTlyEp3trzsirzsNkSoSQMDX2Z7fu3/GT0s/yyNHrZsSaeH1i3/M/SQvyWdHhZuuTJ6OD3FNvN/jx4qfjlbPO+zmLjea/XT577QnXd4MnjM3C7NCpwupARd1hlklBQwdT79672XpPRuXPDOp0PF8qXm+68X5B6lhF+zzLZ0gOmY9r6B6Ycwn/tU2DqiBzYIYwv9ZvUgXD/6DD8iwxaDpuFZkGvG65P53Rq8Em43PRm5EopmBaZxGTkVCCaz30A=
*/