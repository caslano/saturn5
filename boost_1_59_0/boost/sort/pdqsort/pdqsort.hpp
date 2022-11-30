// Pattern-defeating quicksort

//              Copyright Orson Peters 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.


#ifndef BOOST_SORT_PDQSORT_HPP
#define BOOST_SORT_PDQSORT_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include <boost/type_traits.hpp>

#if __cplusplus >= 201103L
    #include <cstdint>
    #define BOOST_PDQSORT_PREFER_MOVE(x) std::move(x)
#else
    #define BOOST_PDQSORT_PREFER_MOVE(x) (x)
#endif

namespace boost {
namespace sort {

namespace pdqsort_detail {
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

    template<class T> struct is_default_compare : boost::false_type { };
    template<class T> struct is_default_compare<std::less<T> > : boost::true_type { };
    template<class T> struct is_default_compare<std::greater<T> > : boost::true_type { };

    // Returns floor(log2(n)), assumes n > 0.
    template<class T>
    inline int log2(T n) {
        int log = 0;
        while (n >>= 1) ++log;
        return log;
    }

    // Sorts [begin, end) using insertion sort with the given comparison function.
    template<class Iter, class Compare>
    inline void insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (begin == end) return;

        for (Iter cur = begin + 1; cur != end; ++cur) {
            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = BOOST_PDQSORT_PREFER_MOVE(*sift);

                do { *sift-- = BOOST_PDQSORT_PREFER_MOVE(*sift_1); }
                while (sift != begin && comp(tmp, *--sift_1));

                *sift = BOOST_PDQSORT_PREFER_MOVE(tmp);
            }
        }
    }

    // Sorts [begin, end) using insertion sort with the given comparison function. Assumes
    // *(begin - 1) is an element smaller than or equal to any element in [begin, end).
    template<class Iter, class Compare>
    inline void unguarded_insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (begin == end) return;

        for (Iter cur = begin + 1; cur != end; ++cur) {
            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = BOOST_PDQSORT_PREFER_MOVE(*sift);

                do { *sift-- = BOOST_PDQSORT_PREFER_MOVE(*sift_1); }
                while (comp(tmp, *--sift_1));

                *sift = BOOST_PDQSORT_PREFER_MOVE(tmp);
            }
        }
    }

    // Attempts to use insertion sort on [begin, end). Will return false if more than
    // partial_insertion_sort_limit elements were moved, and abort sorting. Otherwise it will
    // successfully sort and return true.
    template<class Iter, class Compare>
    inline bool partial_insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (begin == end) return true;
        
        std::size_t limit = 0;
        for (Iter cur = begin + 1; cur != end; ++cur) {
            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = BOOST_PDQSORT_PREFER_MOVE(*sift);

                do { *sift-- = BOOST_PDQSORT_PREFER_MOVE(*sift_1); }
                while (sift != begin && comp(tmp, *--sift_1));

                *sift = BOOST_PDQSORT_PREFER_MOVE(tmp);
                limit += cur - sift;
            }
            
            if (limit > partial_insertion_sort_limit) return false;
        }

        return true;
    }

    template<class Iter, class Compare>
    inline void sort2(Iter a, Iter b, Compare comp) {
        if (comp(*b, *a)) std::iter_swap(a, b);
    }

    // Sorts the elements *a, *b and *c using comparison function comp.
    template<class Iter, class Compare>
    inline void sort3(Iter a, Iter b, Iter c, Compare comp) {
        sort2(a, b, comp);
        sort2(b, c, comp);
        sort2(a, b, comp);
    }

    template<class T>
    inline T* align_cacheline(T* p) {
#if defined(UINTPTR_MAX) && __cplusplus >= 201103L
        std::uintptr_t ip = reinterpret_cast<std::uintptr_t>(p);
#else
        std::size_t ip = reinterpret_cast<std::size_t>(p);
#endif
        ip = (ip + cacheline_size - 1) & -cacheline_size;
        return reinterpret_cast<T*>(ip);
    }

    template<class Iter>
    inline void swap_offsets(Iter first, Iter last,
                             unsigned char* offsets_l, unsigned char* offsets_r,
                             size_t num, bool use_swaps) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (use_swaps) {
            // This case is needed for the descending distribution, where we need
            // to have proper swapping for pdqsort to remain O(n).
            for (size_t i = 0; i < num; ++i) {
                std::iter_swap(first + offsets_l[i], last - offsets_r[i]);
            }
        } else if (num > 0) {
            Iter l = first + offsets_l[0]; Iter r = last - offsets_r[0];
            T tmp(BOOST_PDQSORT_PREFER_MOVE(*l)); *l = BOOST_PDQSORT_PREFER_MOVE(*r);
            for (size_t i = 1; i < num; ++i) {
                l = first + offsets_l[i]; *r = BOOST_PDQSORT_PREFER_MOVE(*l);
                r = last - offsets_r[i]; *l = BOOST_PDQSORT_PREFER_MOVE(*r);
            }
            *r = BOOST_PDQSORT_PREFER_MOVE(tmp);
        }
    }

    // Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
    // to the pivot are put in the right-hand partition. Returns the position of the pivot after
    // partitioning and whether the passed sequence already was correctly partitioned. Assumes the
    // pivot is a median of at least 3 elements and that [begin, end) is at least
    // insertion_sort_threshold long. Uses branchless partitioning.
    template<class Iter, class Compare>
    inline std::pair<Iter, bool> partition_right_branchless(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;

        // Move pivot into local for speed.
        T pivot(BOOST_PDQSORT_PREFER_MOVE(*begin));
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
        if (!already_partitioned) {
            std::iter_swap(first, last);
            ++first;

            // The following branchless partitioning is derived from "BlockQuicksort: How Branch
            // Mispredictions don’t affect Quicksort" by Stefan Edelkamp and Armin Weiss, but
            // heavily micro-optimized.
            unsigned char offsets_l_storage[block_size + cacheline_size];
            unsigned char offsets_r_storage[block_size + cacheline_size];
            unsigned char* offsets_l = align_cacheline(offsets_l_storage);
            unsigned char* offsets_r = align_cacheline(offsets_r_storage);

            Iter offsets_l_base = first;
            Iter offsets_r_base = last;
            size_t num_l, num_r, start_l, start_r;
            num_l = num_r = start_l = start_r = 0;
            
            while (first < last) {
                // Fill up offset blocks with elements that are on the wrong side.
                // First we determine how much elements are considered for each offset block.
                size_t num_unknown = last - first;
                size_t left_split = num_l == 0 ? (num_r == 0 ? num_unknown / 2 : num_unknown) : 0;
                size_t right_split = num_r == 0 ? (num_unknown - left_split) : 0;

                // Fill the offset blocks.
                if (left_split >= block_size) {
                    for (size_t i = 0; i < block_size;) {
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                    }
                } else {
                    for (size_t i = 0; i < left_split;) {
                        offsets_l[num_l] = i++; num_l += !comp(*first, pivot); ++first;
                    }
                }

                if (right_split >= block_size) {
                    for (size_t i = 0; i < block_size;) {
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                    }
                } else {
                    for (size_t i = 0; i < right_split;) {
                        offsets_r[num_r] = ++i; num_r += comp(*--last, pivot);
                    }
                }

                // Swap elements and update block sizes and first/last boundaries.
                size_t num = (std::min)(num_l, num_r);
                swap_offsets(offsets_l_base, offsets_r_base,
                             offsets_l + start_l, offsets_r + start_r,
                             num, num_l == num_r);
                num_l -= num; num_r -= num;
                start_l += num; start_r += num;

                if (num_l == 0) {
                    start_l = 0;
                    offsets_l_base = first;
                }
                
                if (num_r == 0) {
                    start_r = 0;
                    offsets_r_base = last;
                }
            }

            // We have now fully identified [first, last)'s proper position. Swap the last elements.
            if (num_l) {
                offsets_l += start_l;
                while (num_l--) std::iter_swap(offsets_l_base + offsets_l[num_l], --last);
                first = last;
            }
            if (num_r) {
                offsets_r += start_r;
                while (num_r--) std::iter_swap(offsets_r_base - offsets_r[num_r], first), ++first;
                last = first;
            }
        }

        // Put the pivot in the right place.
        Iter pivot_pos = first - 1;
        *begin = BOOST_PDQSORT_PREFER_MOVE(*pivot_pos);
        *pivot_pos = BOOST_PDQSORT_PREFER_MOVE(pivot);

        return std::make_pair(pivot_pos, already_partitioned);
    }

    // Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
    // to the pivot are put in the right-hand partition. Returns the position of the pivot after
    // partitioning and whether the passed sequence already was correctly partitioned. Assumes the
    // pivot is a median of at least 3 elements and that [begin, end) is at least
    // insertion_sort_threshold long.
    template<class Iter, class Compare>
    inline std::pair<Iter, bool> partition_right(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        
        // Move pivot into local for speed.
        T pivot(BOOST_PDQSORT_PREFER_MOVE(*begin));

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
            std::iter_swap(first, last);
            while (comp(*++first, pivot));
            while (!comp(*--last, pivot));
        }

        // Put the pivot in the right place.
        Iter pivot_pos = first - 1;
        *begin = BOOST_PDQSORT_PREFER_MOVE(*pivot_pos);
        *pivot_pos = BOOST_PDQSORT_PREFER_MOVE(pivot);

        return std::make_pair(pivot_pos, already_partitioned);
    }

    // Similar function to the one above, except elements equal to the pivot are put to the left of
    // the pivot and it doesn't check or return if the passed sequence already was partitioned.
    // Since this is rarely used (the many equal case), and in that case pdqsort already has O(n)
    // performance, no block quicksort is applied here for simplicity.
    template<class Iter, class Compare>
    inline Iter partition_left(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;

        T pivot(BOOST_PDQSORT_PREFER_MOVE(*begin));
        Iter first = begin;
        Iter last = end;
        
        while (comp(pivot, *--last));

        if (last + 1 == end) while (first < last && !comp(pivot, *++first));
        else                 while (                !comp(pivot, *++first));

        while (first < last) {
            std::iter_swap(first, last);
            while (comp(pivot, *--last));
            while (!comp(pivot, *++first));
        }

        Iter pivot_pos = last;
        *begin = BOOST_PDQSORT_PREFER_MOVE(*pivot_pos);
        *pivot_pos = BOOST_PDQSORT_PREFER_MOVE(pivot);

        return pivot_pos;
    }


    template<class Iter, class Compare, bool Branchless>
    inline void pdqsort_loop(Iter begin, Iter end, Compare comp, int bad_allowed, bool leftmost = true) {
        typedef typename std::iterator_traits<Iter>::difference_type diff_t;

        // Use a while loop for tail recursion elimination.
        while (true) {
            diff_t size = end - begin;

            // Insertion sort is faster for small arrays.
            if (size < insertion_sort_threshold) {
                if (leftmost) insertion_sort(begin, end, comp);
                else unguarded_insertion_sort(begin, end, comp);
                return;
            }

            // Choose pivot as median of 3 or pseudomedian of 9.
            diff_t s2 = size / 2;
            if (size > ninther_threshold) {
                sort3(begin, begin + s2, end - 1, comp);
                sort3(begin + 1, begin + (s2 - 1), end - 2, comp);
                sort3(begin + 2, begin + (s2 + 1), end - 3, comp);
                sort3(begin + (s2 - 1), begin + s2, begin + (s2 + 1), comp);
                std::iter_swap(begin, begin + s2);
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
            std::pair<Iter, bool> part_result =
                Branchless ? partition_right_branchless(begin, end, comp)
                           : partition_right(begin, end, comp);
            Iter pivot_pos = part_result.first;
            bool already_partitioned = part_result.second;

            // Check for a highly unbalanced partition.
            diff_t l_size = pivot_pos - begin;
            diff_t r_size = end - (pivot_pos + 1);
            bool highly_unbalanced = l_size < size / 8 || r_size < size / 8;

            // If we got a highly unbalanced partition we shuffle elements to break many patterns.
            if (highly_unbalanced) {
                // If we had too many bad partitions, switch to heapsort to guarantee O(n log n).
                if (--bad_allowed == 0) {
                    std::make_heap(begin, end, comp);
                    std::sort_heap(begin, end, comp);
                    return;
                }

                if (l_size >= insertion_sort_threshold) {
                    std::iter_swap(begin,             begin + l_size / 4);
                    std::iter_swap(pivot_pos - 1, pivot_pos - l_size / 4);

                    if (l_size > ninther_threshold) {
                        std::iter_swap(begin + 1,         begin + (l_size / 4 + 1));
                        std::iter_swap(begin + 2,         begin + (l_size / 4 + 2));
                        std::iter_swap(pivot_pos - 2, pivot_pos - (l_size / 4 + 1));
                        std::iter_swap(pivot_pos - 3, pivot_pos - (l_size / 4 + 2));
                    }
                }
                
                if (r_size >= insertion_sort_threshold) {
                    std::iter_swap(pivot_pos + 1, pivot_pos + (1 + r_size / 4));
                    std::iter_swap(end - 1,                   end - r_size / 4);
                    
                    if (r_size > ninther_threshold) {
                        std::iter_swap(pivot_pos + 2, pivot_pos + (2 + r_size / 4));
                        std::iter_swap(pivot_pos + 3, pivot_pos + (3 + r_size / 4));
                        std::iter_swap(end - 2,             end - (1 + r_size / 4));
                        std::iter_swap(end - 3,             end - (2 + r_size / 4));
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
            pdqsort_loop<Iter, Compare, Branchless>(begin, pivot_pos, comp, bad_allowed, leftmost);
            begin = pivot_pos + 1;
            leftmost = false;
        }
    }
}


/*! \brief Generic sort algorithm using random access iterators and a user-defined comparison operator.

    \details @c pdqsort is a fast generic sorting algorithm that is similar in concept to introsort
but runs faster on certain patterns. @c pdqsort is in-place, unstable, deterministic, has a worst
case runtime of <em>O(N * lg(N))</em> and a best case of <em>O(N)</em>. Even without patterns, the
quicksort has been very efficiently implemented, and @c pdqsort runs 1-5% faster than GCC 6.2's
@c std::sort. If the type being sorted is @c std::is_arithmetic and Compare is @c std::less or
@c std::greater this function will automatically use @c pdqsort_branchless for far greater speedups.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveAssignable">MoveAssignable</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveConstructible">MoveConstructible</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps
   (or moves), functors, or any operations on iterators throw.
   \warning Invalid arguments cause undefined behaviour.
   \warning Throwing an exception may cause data loss.
*/
template<class Iter, class Compare>
inline void pdqsort(Iter first, Iter last, Compare comp) {
    if (first == last) return;
    pdqsort_detail::pdqsort_loop<Iter, Compare,
        pdqsort_detail::is_default_compare<typename boost::decay<Compare>::type>::value &&
        boost::is_arithmetic<typename std::iterator_traits<Iter>::value_type>::value>(
        first, last, comp, pdqsort_detail::log2(last - first));
}


/*! \brief Generic sort algorithm using random access iterators and a user-defined comparison operator.

    \details @c pdqsort_branchless is a fast generic sorting algorithm that is similar in concept to
introsort but runs faster on certain patterns. @c pdqsort_branchless is in-place, unstable,
deterministic, has a worst case runtime of <em>O(N * lg(N))</em> and a best case of <em>O(N)</em>.
Even without patterns, the quicksort has been very efficiently implemented with block based
partitioning, and @c pdqsort_branchless runs 80-90% faster than GCC 6.2's @c std::sort when sorting
small data such as integers. However, this speedup is gained by totally bypassing the branch
predictor, if your comparison operator or iterator contains branches you will most likely see little
gain or a small loss in performance.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveAssignable">MoveAssignable</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveConstructible">MoveConstructible</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps
   (or moves), functors, or any operations on iterators throw.
   \warning Invalid arguments cause undefined behaviour.
   \warning Throwing an exception may cause data loss.
*/
template<class Iter, class Compare>
inline void pdqsort_branchless(Iter first, Iter last, Compare comp) {
    if (first == last) return;
    pdqsort_detail::pdqsort_loop<Iter, Compare, true>(
        first, last, comp, pdqsort_detail::log2(last - first));
}


/*! \brief Generic sort algorithm using random access iterators.

    \details @c pdqsort is a fast generic sorting algorithm that is similar in concept to introsort
but runs faster on certain patterns. @c pdqsort is in-place, unstable, deterministic, has a worst
case runtime of <em>O(N * lg(N))</em> and a best case of <em>O(N)</em>. Even without patterns, the
quicksort partitioning has been very efficiently implemented, and @c pdqsort runs 80-90% faster than
GCC 6.2's @c std::sort. If the type being sorted is @c std::is_arithmetic this function will
automatically use @c pdqsort_branchless.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveAssignable">MoveAssignable</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveConstructible">MoveConstructible</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps
   (or moves), functors, or any operations on iterators throw.
   \warning Invalid arguments cause undefined behaviour.
   \warning Throwing an exception may cause data loss.
*/
template<class Iter>
inline void pdqsort(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type T;
    pdqsort(first, last, std::less<T>());
}


/*! \brief Generic sort algorithm using random access iterators.

    \details @c pdqsort_branchless is a fast generic sorting algorithm that is similar in concept to
introsort but runs faster on certain patterns. @c pdqsort_branchless is in-place, unstable,
deterministic, has a worst case runtime of <em>O(N * lg(N))</em> and a best case of <em>O(N)</em>.
Even without patterns, the quicksort has been very efficiently implemented with block based
partitioning, and @c pdqsort_branchless runs 80-90% faster than GCC 6.2's @c std::sort when sorting
small data such as integers. However, this speedup is gained by totally bypassing the branch
predictor, if your comparison operator or iterator contains branches you will most likely see little
gain or a small loss in performance.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveAssignable">MoveAssignable</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/MoveConstructible">MoveConstructible</a>
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps
   (or moves), functors, or any operations on iterators throw.
   \warning Invalid arguments cause undefined behaviour.
   \warning Throwing an exception may cause data loss.
*/
template<class Iter>
inline void pdqsort_branchless(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type T;
    pdqsort_branchless(first, last, std::less<T>());
}

}
}

#undef BOOST_PDQSORT_PREFER_MOVE

#endif

/* pdqsort.hpp
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
*/