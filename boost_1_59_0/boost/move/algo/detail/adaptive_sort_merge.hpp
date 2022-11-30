//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// Stable sorting that works in O(N*log(N)) worst time
// and uses O(1) extra memory
//
//////////////////////////////////////////////////////////////////////////////
//
// The main idea of the adaptive_sort algorithm was developed by Andrey Astrelin
// and explained in the article from the russian collaborative blog
// Habrahabr (http://habrahabr.ru/post/205290/). The algorithm is based on
// ideas from B-C. Huang and M. A. Langston explained in their article
// "Fast Stable Merging and Sorting in Constant Extra Space (1989-1992)"
// (http://comjnl.oxfordjournals.org/content/35/6/643.full.pdf).
//
// This implementation by Ion Gaztanaga uses previous ideas with additional changes:
// 
// - Use of GCD-based rotation.
// - Non power of two buffer-sizes.
// - Tries to find sqrt(len)*2 unique keys, so that the merge sort
//   phase can form up to sqrt(len)*4 segments if enough keys are found.
// - The merge-sort phase can take advantage of external memory to
//   save some additional combination steps.
// - Combination phase: Blocks are selection sorted and merged in parallel.
// - The combination phase is performed alternating merge to left and merge
//   to right phases minimizing swaps due to internal buffer repositioning.
// - When merging blocks special optimizations are made to avoid moving some
//   elements twice.
//
// The adaptive_merge algorithm was developed by Ion Gaztanaga reusing some parts
// from the sorting algorithm and implementing an additional block merge algorithm
// without moving elements to left or right.
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_ADAPTIVE_SORT_MERGE_HPP
#define BOOST_MOVE_ADAPTIVE_SORT_MERGE_HPP

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/detail/reverse_iterator.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/move/algo/detail/merge.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/algo/detail/insertion_sort.hpp>
#include <boost/move/algo/detail/merge_sort.hpp>
#include <boost/move/algo/detail/heap_sort.hpp>
#include <boost/move/algo/detail/merge.hpp>
#include <boost/move/algo/detail/is_sorted.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <limits.h>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#ifndef BOOST_MOVE_ADAPTIVE_SORT_STATS_LEVEL
   #define BOOST_MOVE_ADAPTIVE_SORT_STATS_LEVEL 1
#endif

#ifdef BOOST_MOVE_ADAPTIVE_SORT_STATS
   #if BOOST_MOVE_ADAPTIVE_SORT_STATS_LEVEL == 2
      #define BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1(STR, L) \
         print_stats(STR, L)\
      //

      #define BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2(STR, L) \
         print_stats(STR, L)\
      //
   #else
      #define BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1(STR, L) \
         print_stats(STR, L)\
      //

      #define BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2(STR, L)
   #endif
#else
   #define BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1(STR, L)
   #define BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2(STR, L)
#endif

#ifdef BOOST_MOVE_ADAPTIVE_SORT_INVARIANTS
   #define BOOST_MOVE_ADAPTIVE_SORT_INVARIANT  BOOST_ASSERT
#else
   #define BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(L)
#endif

namespace boost {
namespace movelib {

#if defined(BOOST_MOVE_ADAPTIVE_SORT_INVARIANTS)

bool is_sorted(::order_perf_type *first, ::order_perf_type *last, ::order_type_less)
{
   if (first != last) {
      const order_perf_type *next = first, *cur(first);
      while (++next != last) {
         if (!(cur->key < next->key || (cur->key == next->key && cur->val < next->val)))
            return false;
         cur = next;
      }
   }
   return true;
}

#endif   //BOOST_MOVE_ADAPTIVE_SORT_INVARIANTS

namespace detail_adaptive {

static const std::size_t AdaptiveSortInsertionSortThreshold = 16;
//static const std::size_t AdaptiveSortInsertionSortThreshold = 4;
BOOST_STATIC_ASSERT((AdaptiveSortInsertionSortThreshold&(AdaptiveSortInsertionSortThreshold-1)) == 0);

#if defined BOOST_HAS_INTPTR_T
   typedef ::boost::uintptr_t uintptr_t;
#else
   typedef std::size_t uintptr_t;
#endif

template<class T>
const T &min_value(const T &a, const T &b)
{
   return a < b ? a : b;
}

template<class T>
const T &max_value(const T &a, const T &b)
{
   return a > b ? a : b;
}

template<class ForwardIt, class Pred, class V>
typename iter_size<ForwardIt>::type
   count_if_with(ForwardIt first, ForwardIt last, Pred pred, const V &v)
{
   typedef typename iter_size<ForwardIt>::type size_type;
   size_type count = 0;
   while(first != last) {
      count = size_type(count + static_cast<size_type>(0 != pred(*first, v)));
      ++first;
   }
   return count;
}


template<class RandIt, class Compare>
RandIt skip_until_merge
   ( RandIt first1, RandIt const last1
   , const typename iterator_traits<RandIt>::value_type &next_key, Compare comp)
{
   while(first1 != last1 && !comp(next_key, *first1)){
      ++first1;
   }
   return first1;
}


template<class RandItKeys, class RandIt>
void swap_and_update_key
   ( RandItKeys const key_next
   , RandItKeys const key_range2
   , RandItKeys &key_mid
   , RandIt const begin
   , RandIt const end
   , RandIt const with)
{
   if(begin != with){
      ::boost::adl_move_swap_ranges(begin, end, with);
      ::boost::adl_move_swap(*key_next, *key_range2);
      if(key_next == key_mid){
         key_mid = key_range2;
      }
      else if(key_mid == key_range2){
         key_mid = key_next;
      }
   }
}

template<class RandItKeys>
void update_key
(RandItKeys const key_next
   , RandItKeys const key_range2
   , RandItKeys &key_mid)
{
   if (key_next != key_range2) {
      ::boost::adl_move_swap(*key_next, *key_range2);
      if (key_next == key_mid) {
         key_mid = key_range2;
      }
      else if (key_mid == key_range2) {
         key_mid = key_next;
      }
   }
}

template<class RandItKeys, class RandIt, class RandIt2, class Op>
RandIt2 buffer_and_update_key
(RandItKeys const key_next
   , RandItKeys const key_range2
   , RandItKeys &key_mid
   , RandIt begin
   , RandIt end
   , RandIt with
   , RandIt2 buffer
   , Op op)
{
   if (begin != with) {
      while(begin != end) {
         op(three_way_t(), begin++, with++, buffer++);
      }
      ::boost::adl_move_swap(*key_next, *key_range2);
      if (key_next == key_mid) {
         key_mid = key_range2;
      }
      else if (key_mid == key_range2) {
         key_mid = key_next;
      }
   }
   return buffer;
}

///////////////////////////////////////////////////////////////////////////////
//
//                         MERGE BUFFERLESS
//
///////////////////////////////////////////////////////////////////////////////

// [first1, last1) merge [last1,last2) -> [first1,last2)
template<class RandIt, class Compare>
RandIt partial_merge_bufferless_impl
   (RandIt first1, RandIt last1, RandIt const last2, bool *const pis_range1_A, Compare comp)
{
   if(last1 == last2){
      return first1;
   }
   bool const is_range1_A = *pis_range1_A;
   if(first1 != last1 && comp(*last1, last1[-1])){
      do{
         RandIt const old_last1 = last1;
         last1  = boost::movelib::lower_bound(last1, last2, *first1, comp);
         first1 = rotate_gcd(first1, old_last1, last1);//old_last1 == last1 supported
         if(last1 == last2){
            return first1;
         }
         do{
            ++first1;
         } while(last1 != first1 && !comp(*last1, *first1) );
      } while(first1 != last1);
   }
   *pis_range1_A = !is_range1_A;
   return last1;
}

// [first1, last1) merge [last1,last2) -> [first1,last2)
template<class RandIt, class Compare>
RandIt partial_merge_bufferless
   (RandIt first1, RandIt last1, RandIt const last2, bool *const pis_range1_A, Compare comp)
{
   return *pis_range1_A ? partial_merge_bufferless_impl(first1, last1, last2, pis_range1_A, comp)
                        : partial_merge_bufferless_impl(first1, last1, last2, pis_range1_A, antistable<Compare>(comp));
}

template<class SizeType>
static SizeType needed_keys_count(SizeType n_block_a, SizeType n_block_b)
{
   return SizeType(n_block_a + n_block_b);
}

template<class RandItKeys, class KeyCompare, class RandIt, class Compare>
typename iter_size<RandIt>::type
   find_next_block
      ( RandItKeys const key_first
      , KeyCompare key_comp
      , RandIt const first
      , typename iter_size<RandIt>::type const l_block
      , typename iter_size<RandIt>::type const ix_first_block
      , typename iter_size<RandIt>::type const ix_last_block
      , Compare comp)
{
   typedef typename iter_size<RandIt>::type      size_type;
   typedef typename iterator_traits<RandIt>::value_type     value_type;
   typedef typename iterator_traits<RandItKeys>::value_type key_type;
   BOOST_ASSERT(ix_first_block <= ix_last_block);
   size_type ix_min_block = 0u;
   for (size_type szt_i = ix_first_block; szt_i < ix_last_block; ++szt_i) {
      const value_type &min_val = first[size_type(ix_min_block*l_block)];
      const value_type &cur_val = first[size_type(szt_i*l_block)];
      const key_type   &min_key = key_first[ix_min_block];
      const key_type   &cur_key = key_first[szt_i];

      bool const less_than_minimum = comp(cur_val, min_val) ||
         (!comp(min_val, cur_val) && key_comp(cur_key, min_key));

      if (less_than_minimum) {
         ix_min_block = szt_i;
      }
   }
   return ix_min_block;
}

template<class RandItKeys, class KeyCompare, class RandIt, class Compare>
void merge_blocks_bufferless
   ( RandItKeys const key_first
   , KeyCompare key_comp
   , RandIt const first
   , typename iter_size<RandIt>::type const l_block
   , typename iter_size<RandIt>::type const l_irreg1
   , typename iter_size<RandIt>::type const n_block_a
   , typename iter_size<RandIt>::type const n_block_b
   , typename iter_size<RandIt>::type const l_irreg2
   , Compare comp)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type const key_count = needed_keys_count(n_block_a, n_block_b);
   ::boost::ignore_unused(key_count);
   //BOOST_ASSERT(n_block_a || n_block_b);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted_and_unique(key_first, key_first + key_count, key_comp));
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_b || n_block_a == count_if_with(key_first, key_first + key_count, key_comp, key_first[n_block_a]));

   size_type n_bef_irreg2 = 0;
   bool l_irreg_pos_count = true;
   RandItKeys key_mid(key_first + n_block_a);
   RandIt const first_irr2 = first + size_type(l_irreg1 + (n_block_a+n_block_b)*l_block);
   RandIt const last_irr2  = first_irr2 + l_irreg2;

   {  //Selection sort blocks
      size_type n_block_left = size_type(n_block_b + n_block_a);
      RandItKeys key_range2(key_first);

      size_type min_check = n_block_a == n_block_left ? 0u : n_block_a;
      size_type max_check = min_value<size_type>(size_type(min_check+1), n_block_left);
      for ( RandIt f = first+l_irreg1; n_block_left; --n_block_left) {
         size_type const next_key_idx = find_next_block(key_range2, key_comp, f, l_block, min_check, max_check, comp);
         RandItKeys const key_next(key_range2 + next_key_idx);
         max_check = min_value<size_type>(max_value<size_type>(max_check, size_type(next_key_idx+2)), n_block_left);

         RandIt const first_min = f + size_type(next_key_idx*l_block);

         //Check if irregular b block should go here.
         //If so, break to the special code handling the irregular block
         if (l_irreg_pos_count && l_irreg2 && comp(*first_irr2, *first_min)){
            l_irreg_pos_count = false;
         }
         n_bef_irreg2 = size_type(n_bef_irreg2+l_irreg_pos_count);

         swap_and_update_key(key_next, key_range2, key_mid, f, f + l_block, first_min);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(f, f+l_block, comp));
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first_min, first_min + l_block, comp));
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT((f == (first+l_irreg1)) || !comp(*f, *(f-l_block)));
         //Update context
         ++key_range2;
         f += l_block;
         min_check = size_type(min_check - (min_check != 0));
         max_check = size_type(max_check - (max_check != 0));
      }
   }
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first+l_irreg1+n_bef_irreg2*l_block, first_irr2, comp));

   RandIt first1 = first;
   RandIt last1  = first+l_irreg1;
   RandItKeys const key_end (key_first+n_bef_irreg2);
   bool is_range1_A = true;

   for(RandItKeys key_next = key_first; key_next != key_end; ++key_next){
      bool is_range2_A = key_mid == (key_first+key_count) || key_comp(*key_next, *key_mid);
      first1 = is_range1_A == is_range2_A
         ? last1 : partial_merge_bufferless(first1, last1, last1 + l_block, &is_range1_A, comp);
      last1 += l_block;
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, first1, comp));
   }

   merge_bufferless(is_range1_A ? first1 : last1, first_irr2, last_irr2, comp);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, last_irr2, comp));
}

// Complexity: 2*distance(first, last)+max_collected^2/2
//
// Tries to collect at most n_keys unique elements from [first, last),
// in the begining of the range, and ordered according to comp
// 
// Returns the number of collected keys
template<class RandIt, class Compare, class XBuf>
typename iter_size<RandIt>::type
   collect_unique
      ( RandIt const first, RandIt const last
      , typename iter_size<RandIt>::type const max_collected, Compare comp
      , XBuf & xbuf)
{
   typedef typename iter_size<RandIt>::type       size_type;
   size_type h = 0;

   if(max_collected){
      ++h;  // first key is always here
      RandIt h0 = first;
      RandIt u = first; ++u;
      RandIt search_end = u;

      if(xbuf.capacity() >= max_collected){
         typename XBuf::iterator const ph0 = xbuf.add(first);
         while(u != last && h < max_collected){
            typename XBuf::iterator const r = boost::movelib::lower_bound(ph0, xbuf.end(), *u, comp);
            //If key not found add it to [h, h+h0)
            if(r == xbuf.end() || comp(*u, *r) ){
               RandIt const new_h0 = boost::move(search_end, u, h0);
               search_end = u;
               ++search_end;
               ++h;
               xbuf.insert(r, u);
               h0 = new_h0;
            }
            ++u;
         }
         boost::move_backward(first, h0, h0+h);
         boost::move(xbuf.data(), xbuf.end(), first);
      }
      else{
         while(u != last && h < max_collected){
            RandIt const r = boost::movelib::lower_bound(h0, search_end, *u, comp);
            //If key not found add it to [h, h+h0)
            if(r == search_end || comp(*u, *r) ){
               RandIt const new_h0 = rotate_gcd(h0, search_end, u);
               search_end = u;
               ++search_end;
               ++h;
               rotate_gcd(r+(new_h0-h0), u, search_end);
               h0 = new_h0;
            }
            ++u;
         }
         rotate_gcd(first, h0, h0+h);
      }
   }
   return h;
}

template<class Unsigned>
Unsigned floor_sqrt(Unsigned n)
{
   Unsigned rem = 0, root = 0;
   const unsigned bits = sizeof(Unsigned)*CHAR_BIT;

   for (unsigned i = bits / 2; i > 0; i--) {
      root = Unsigned(root << 1u);
      rem = Unsigned(Unsigned(rem << 2u) | Unsigned(n >> (bits - 2u)));
      n = Unsigned(n << 2u);
      if (root < rem) {
         rem  = Unsigned(rem - Unsigned(root | 1u));
         root = Unsigned(root + 2u);
      }
   }
   return Unsigned(root >> 1u);
}

template<class Unsigned>
Unsigned ceil_sqrt(Unsigned const n)
{
   Unsigned r = floor_sqrt(n);
   return Unsigned(r + Unsigned((n%r) != 0));
}

template<class Unsigned>
Unsigned floor_merge_multiple(Unsigned const n, Unsigned &base, Unsigned &pow)
{
   Unsigned s = n;
   Unsigned p = 0;
   while(s > AdaptiveSortInsertionSortThreshold){
      s /= 2;
      ++p;
   }
   base = s;
   pow = p;
   return Unsigned(s << p);
}

template<class Unsigned>
Unsigned ceil_merge_multiple(Unsigned const n, Unsigned &base, Unsigned &pow)
{
   Unsigned fm = floor_merge_multiple(n, base, pow);

   if(fm != n){
      if(base < AdaptiveSortInsertionSortThreshold){
         ++base;
      }
      else{
         base = AdaptiveSortInsertionSortThreshold/2 + 1;
         ++pow;
      }
   }
   return Unsigned(base << pow);
}

template<class Unsigned>
Unsigned ceil_sqrt_multiple(Unsigned const n, Unsigned *pbase = 0)
{
   Unsigned const r = ceil_sqrt(n);
   Unsigned pow = 0;
   Unsigned base = 0;
   Unsigned const res = ceil_merge_multiple(r, base, pow);
   if(pbase) *pbase = base;
   return res;
}

struct less
{
   template<class T>
   bool operator()(const T &l, const T &r)
   {  return l < r;  }
};

///////////////////////////////////////////////////////////////////////////////
//
//                            MERGE BLOCKS
//
///////////////////////////////////////////////////////////////////////////////

//#define ADAPTIVE_SORT_MERGE_SLOW_STABLE_SORT_IS_NLOGN

#if defined ADAPTIVE_SORT_MERGE_SLOW_STABLE_SORT_IS_NLOGN
template<class RandIt, class Compare>
void slow_stable_sort
   ( RandIt const first, RandIt const last, Compare comp)
{
   boost::movelib::inplace_stable_sort(first, last, comp);
}

#else //ADAPTIVE_SORT_MERGE_SLOW_STABLE_SORT_IS_NLOGN

template<class RandIt, class Compare>
void slow_stable_sort
   ( RandIt const first, RandIt const last, Compare comp)
{
   typedef typename iter_size<RandIt>::type       size_type;

   size_type L = size_type(last - first);
   {  //Use insertion sort to merge first elements
      size_type m = 0;
      while((L - m) > size_type(AdaptiveSortInsertionSortThreshold)){
         insertion_sort(first+m, first+m+size_type(AdaptiveSortInsertionSortThreshold), comp);
         m = size_type(m + AdaptiveSortInsertionSortThreshold);
      }
      insertion_sort(first+m, last, comp);
   }

   size_type h = AdaptiveSortInsertionSortThreshold;
   for(bool do_merge = L > h; do_merge; h = size_type(h*2)){
      do_merge = (L - h) > h;
      size_type p0 = 0;
      if(do_merge){
         size_type const h_2 = size_type(2*h);
         while((L-p0) > h_2){
            merge_bufferless(first+p0, first+p0+h, first+p0+h_2, comp);
            p0 = size_type(p0 + h_2);
         }
      }
      if((L-p0) > h){
         merge_bufferless(first+p0, first+p0+h, last, comp);
      }
   }
}

#endif   //ADAPTIVE_SORT_MERGE_SLOW_STABLE_SORT_IS_NLOGN

//Returns new l_block and updates use_buf
template<class Unsigned>
Unsigned lblock_for_combine
   (Unsigned const l_block, Unsigned const n_keys, Unsigned const l_data, bool &use_buf)
{
   BOOST_ASSERT(l_data > 1);

   //We need to guarantee lblock >= l_merged/(n_keys/2) keys for the combination.
   //We have at least 4 keys guaranteed (which are the minimum to merge 2 ranges)
   //If l_block != 0, then n_keys is already enough to merge all blocks in all
   //phases as we've found all needed keys for that buffer and length before.
   //If l_block == 0 then see if half keys can be used as buffer and the rest
   //as keys guaranteeing that n_keys >= (2*l_merged)/lblock = 
   if(!l_block){
      //If l_block == 0 then n_keys is power of two
      //(guaranteed by build_params(...))
      BOOST_ASSERT(n_keys >= 4);
      //BOOST_ASSERT(0 == (n_keys &(n_keys-1)));

      //See if half keys are at least 4 and if half keys fulfill
      Unsigned const new_buf  = n_keys/2;
      Unsigned const new_keys = Unsigned(n_keys-new_buf);
      use_buf = new_keys >= 4 && new_keys >= l_data/new_buf;
      if(use_buf){
         return new_buf;
      }
      else{
         return l_data/n_keys;
      }
   }
   else{
      use_buf = true;
      return l_block;
   }
}

template<class RandIt, class Compare, class XBuf>
void stable_sort( RandIt first, RandIt last, Compare comp, XBuf & xbuf)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type const len = size_type(last - first);
   size_type const half_len = size_type(len/2u + (len&1u));
   if(std::size_t(xbuf.capacity() - xbuf.size()) >= half_len) {
      merge_sort(first, last, comp, xbuf.data()+xbuf.size());
   }
   else{
      slow_stable_sort(first, last, comp);
   }
}

template<class RandIt, class Comp, class XBuf>
void unstable_sort( RandIt first, RandIt last
                    , Comp comp
                    , XBuf & xbuf)
{
   heap_sort(first, last, comp);
   ::boost::ignore_unused(xbuf);
}

template<class RandIt, class Compare, class XBuf>
void stable_merge
      ( RandIt first, RandIt const middle, RandIt last
      , Compare comp
      , XBuf &xbuf)
{
   BOOST_ASSERT(xbuf.empty());
   typedef typename iter_size<RandIt>::type   size_type;
   size_type const len1  = size_type(middle-first);
   size_type const len2  = size_type(last-middle);
   size_type const l_min = min_value<size_type>(len1, len2);
   if(xbuf.capacity() >= l_min){
      buffered_merge(first, middle, last, comp, xbuf);
      xbuf.clear();
   }
   else{
      //merge_bufferless(first, middle, last, comp);
      merge_adaptive_ONlogN(first, middle, last, comp, xbuf.begin(), xbuf.capacity());
   }
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, last, boost::movelib::unantistable(comp)));
}

template<class RandIt, class Comp, class XBuf>
void initialize_keys( RandIt first, RandIt last
                    , Comp comp
                    , XBuf & xbuf)
{
   unstable_sort(first, last, comp, xbuf);
   BOOST_ASSERT(boost::movelib::is_sorted_and_unique(first, last, comp));
}

template<class RandIt, class U>
void initialize_keys( RandIt first, RandIt last
                    , less
                    , U &)
{
   typedef typename iterator_traits<RandIt>::value_type value_type;
   std::size_t count = std::size_t(last - first);
   for(std::size_t i = 0; i != count; ++i){
      *first = static_cast<value_type>(i);
      ++first;
   }
}

template <class Unsigned>
Unsigned calculate_total_combined(Unsigned const len, Unsigned const l_prev_merged, Unsigned *pl_irreg_combined = 0)
{
   typedef Unsigned size_type;

   size_type const l_combined = size_type(2*l_prev_merged);
   size_type l_irreg_combined = size_type(len%l_combined);
   size_type l_total_combined = len;
   if(l_irreg_combined <= l_prev_merged){
      l_total_combined = size_type(l_total_combined - l_irreg_combined);
      l_irreg_combined = 0;
   }
   if(pl_irreg_combined)
      *pl_irreg_combined = l_irreg_combined;
   return l_total_combined;
}

template<class RandItKeys, class KeyCompare, class SizeType, class XBuf>
void combine_params
   ( RandItKeys const keys
   , KeyCompare key_comp
   , SizeType l_combined
   , SizeType const l_prev_merged
   , SizeType const l_block
   , XBuf & xbuf
   //Output
   , SizeType &n_block_a
   , SizeType &n_block_b
   , SizeType &l_irreg1
   , SizeType &l_irreg2
   //Options
   , bool do_initialize_keys = true)
{
   typedef SizeType   size_type;

   //Initial parameters for selection sort blocks
   l_irreg1 = size_type(l_prev_merged%l_block);
   l_irreg2 = size_type((l_combined-l_irreg1)%l_block);
   BOOST_ASSERT(((l_combined-l_irreg1-l_irreg2)%l_block) == 0);
   size_type const n_reg_block = size_type((l_combined-l_irreg1-l_irreg2)/l_block);
   n_block_a = l_prev_merged/l_block;
   n_block_b = size_type(n_reg_block - n_block_a);
   BOOST_ASSERT(n_reg_block>=n_block_a);

   //Key initialization
   if (do_initialize_keys) {
      initialize_keys(keys, keys + needed_keys_count(n_block_a, n_block_b), key_comp, xbuf);
   }
}



//////////////////////////////////
//
//          partial_merge
//
//////////////////////////////////
template<class InputIt1, class InputIt2, class OutputIt, class Compare, class Op>
OutputIt op_partial_merge_impl
   (InputIt1 &r_first1, InputIt1 const last1, InputIt2 &r_first2, InputIt2 const last2, OutputIt d_first, Compare comp, Op op)
{
   InputIt1 first1(r_first1);
   InputIt2 first2(r_first2);
   if(first2 != last2 && last1 != first1)
   while(1){
      if(comp(*first2, *first1)) {
         op(first2++, d_first++);
         if(first2 == last2){
            break;
         }
      }
      else{
         op(first1++, d_first++);
         if(first1 == last1){
            break;
         }
      }
   }
   r_first1 = first1;
   r_first2 = first2;
   return d_first;
}

template<class InputIt1, class InputIt2, class OutputIt, class Compare, class Op>
OutputIt op_partial_merge
   (InputIt1 &r_first1, InputIt1 const last1, InputIt2 &r_first2, InputIt2 const last2, OutputIt d_first, Compare comp, Op op, bool is_stable)
{
   return is_stable ? op_partial_merge_impl(r_first1, last1, r_first2, last2, d_first, comp, op)
                    : op_partial_merge_impl(r_first1, last1, r_first2, last2, d_first, antistable<Compare>(comp), op);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//    op_partial_merge_and_save
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
template<class InputIt1, class InputIt2, class OutputIt, class Compare, class Op>
OutputIt op_partial_merge_and_swap_impl
   (InputIt1 &r_first1, InputIt1 const last1, InputIt2 &r_first2, InputIt2 const last2, InputIt2 &r_first_min, OutputIt d_first, Compare comp, Op op)
{
   InputIt1 first1(r_first1);
   InputIt2 first2(r_first2);
   
   if(first2 != last2 && last1 != first1) {
      InputIt2 first_min(r_first_min);
      bool non_empty_ranges = true;
      do{
         if(comp(*first_min, *first1)) {
            op(three_way_t(), first2++, first_min++, d_first++);
            non_empty_ranges = first2 != last2;
         }
         else{
            op(first1++, d_first++);
            non_empty_ranges = first1 != last1;
         }
      } while(non_empty_ranges);
      r_first_min = first_min;
      r_first1 = first1;
      r_first2 = first2;
   }
   return d_first;
}

template<class RandIt, class InputIt2, class OutputIt, class Compare, class Op>
OutputIt op_partial_merge_and_swap
   (RandIt &r_first1, RandIt const last1, InputIt2 &r_first2, InputIt2 const last2, InputIt2 &r_first_min, OutputIt d_first, Compare comp, Op op, bool is_stable)
{
   return is_stable ? op_partial_merge_and_swap_impl(r_first1, last1, r_first2, last2, r_first_min, d_first, comp, op)
                    : op_partial_merge_and_swap_impl(r_first1, last1, r_first2, last2, r_first_min, d_first, antistable<Compare>(comp), op);
}

template<class RandIt1, class RandIt2, class RandItB, class Compare, class Op>
RandItB op_buffered_partial_merge_and_swap_to_range1_and_buffer
   ( RandIt1 first1, RandIt1 const last1
   , RandIt2 &rfirst2, RandIt2 const last2, RandIt2 &rfirst_min
   , RandItB &rfirstb, Compare comp, Op op )
{
   RandItB firstb = rfirstb;
   RandItB lastb  = firstb;
   RandIt2 first2 = rfirst2;

   //Move to buffer while merging
   //Three way moves need less moves when op is swap_op so use it
   //when merging elements from range2 to the destination occupied by range1
   if(first1 != last1 && first2 != last2){
      RandIt2 first_min = rfirst_min;
      op(four_way_t(), first2++, first_min++, first1++, lastb++);

      while(first1 != last1){
         if(first2 == last2){
            lastb = op(forward_t(), first1, last1, firstb);
            break;
         }

         if(comp(*first_min, *firstb)){
            op( four_way_t(), first2++, first_min++, first1++, lastb++);
         }
         else{
            op(three_way_t(), firstb++, first1++, lastb++);
         }
      }
      rfirst2 = first2;
      rfirstb = firstb;
      rfirst_min = first_min;
   }

   return lastb;
}

template<class RandIt1, class RandIt2, class RandItB, class Compare, class Op>
RandItB op_buffered_partial_merge_to_range1_and_buffer
   ( RandIt1 first1, RandIt1 const last1
   , RandIt2 &rfirst2, RandIt2 const last2
   , RandItB &rfirstb, Compare comp, Op op )
{
   RandItB firstb = rfirstb;
   RandItB lastb  = firstb;
   RandIt2 first2 = rfirst2;

   //Move to buffer while merging
   //Three way moves need less moves when op is swap_op so use it
   //when merging elements from range2 to the destination occupied by range1
   if(first1 != last1 && first2 != last2){
      op(three_way_t(), first2++, first1++, lastb++);

      while(true){
         if(first1 == last1){
            break;
         }
         if(first2 == last2){
            lastb = op(forward_t(), first1, last1, firstb);
            break;
         }
         if (comp(*first2, *firstb)) {
            op(three_way_t(), first2++, first1++, lastb++);
         }
         else {
            op(three_way_t(), firstb++, first1++, lastb++);
         }
      }
      rfirst2 = first2;
      rfirstb = firstb;
   }

   return lastb;
}

template<class RandIt, class RandItBuf, class Compare, class Op>
RandIt op_partial_merge_and_save_impl
   ( RandIt first1, RandIt const last1, RandIt &rfirst2, RandIt last2, RandIt first_min
   , RandItBuf &buf_first1_in_out, RandItBuf &buf_last1_in_out
   , Compare comp, Op op
   )
{
   RandItBuf buf_first1 = buf_first1_in_out;
   RandItBuf buf_last1  = buf_last1_in_out;
   RandIt first2(rfirst2);

   bool const do_swap = first2 != first_min;
   if(buf_first1 == buf_last1){
      //Skip any element that does not need to be moved
      RandIt new_first1 = skip_until_merge(first1, last1, *first_min, comp);
      buf_first1 += (new_first1-first1);
      first1 = new_first1;
      buf_last1  = do_swap ? op_buffered_partial_merge_and_swap_to_range1_and_buffer(first1, last1, first2, last2, first_min, buf_first1, comp, op)
                           : op_buffered_partial_merge_to_range1_and_buffer    (first1, last1, first2, last2, buf_first1, comp, op);
      first1 = last1;
   }
   else{
      BOOST_ASSERT((last1-first1) == (buf_last1 - buf_first1));
   }

   //Now merge from buffer
   first1 = do_swap ? op_partial_merge_and_swap_impl(buf_first1, buf_last1, first2, last2, first_min, first1, comp, op)
                    : op_partial_merge_impl    (buf_first1, buf_last1, first2, last2, first1, comp, op);
   buf_first1_in_out = buf_first1;
   buf_last1_in_out  = buf_last1;
   rfirst2 = first2;
   return first1;
}

template<class RandIt, class RandItBuf, class Compare, class Op>
RandIt op_partial_merge_and_save
   ( RandIt first1, RandIt const last1, RandIt &rfirst2, RandIt last2, RandIt first_min
   , RandItBuf &buf_first1_in_out
   , RandItBuf &buf_last1_in_out
   , Compare comp
   , Op op
   , bool is_stable)
{
   return is_stable
      ? op_partial_merge_and_save_impl
         (first1, last1, rfirst2, last2, first_min, buf_first1_in_out, buf_last1_in_out, comp, op)
      : op_partial_merge_and_save_impl
         (first1, last1, rfirst2, last2, first_min, buf_first1_in_out, buf_last1_in_out, antistable<Compare>(comp), op)
      ;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//    op_merge_blocks_with_irreg
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

template<class RandItKeys, class KeyCompare, class RandIt, class RandIt2, class OutputIt, class Compare, class Op>
OutputIt op_merge_blocks_with_irreg
   ( RandItKeys key_first
   , RandItKeys key_mid
   , KeyCompare key_comp
   , RandIt first_reg
   , RandIt2 &first_irr
   , RandIt2 const last_irr
   , OutputIt dest
   , typename iter_size<RandIt>::type const l_block
   , typename iter_size<RandIt>::type n_block_left
   , typename iter_size<RandIt>::type min_check
   , typename iter_size<RandIt>::type max_check
   , Compare comp, bool const is_stable, Op op)
{
   typedef typename iter_size<RandIt>::type size_type;

   for(; n_block_left; --n_block_left){
      size_type next_key_idx = find_next_block(key_first, key_comp, first_reg, l_block, min_check, max_check, comp);  
      max_check = min_value(max_value(max_check, size_type(next_key_idx+2u)), n_block_left);
      RandIt const last_reg  = first_reg + l_block;
      RandIt first_min = first_reg + size_type(next_key_idx*l_block);
      RandIt const last_min  = first_min + l_block;
      boost::ignore_unused(last_min);

      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first_reg, last_reg, comp));
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!next_key_idx || boost::movelib::is_sorted(first_min, last_min, comp));
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT((!next_key_idx || !comp(*first_reg, *first_min )));

      OutputIt orig_dest = dest;
      boost::ignore_unused(orig_dest);
      dest = next_key_idx ? op_partial_merge_and_swap(first_irr, last_irr, first_reg, last_reg, first_min, dest, comp, op, is_stable)
                          : op_partial_merge         (first_irr, last_irr, first_reg, last_reg, dest, comp, op, is_stable);
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(orig_dest, dest, comp));

      if(first_reg == dest){
         dest = next_key_idx ? ::boost::adl_move_swap_ranges(first_min, last_min, first_reg)
                             : last_reg;
      }
      else{
         dest = next_key_idx ? op(three_way_forward_t(), first_reg, last_reg, first_min, dest)
                             : op(forward_t(), first_reg, last_reg, dest);
      }

      RandItKeys const key_next(key_first + next_key_idx);
      swap_and_update_key(key_next, key_first, key_mid, last_reg, last_reg, first_min);

      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(orig_dest, dest, comp));
      first_reg = last_reg;
      ++key_first;
      min_check = size_type(min_check - (min_check != 0));
      max_check = size_type(max_check - (max_check != 0));
   }
   return dest;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//    op_merge_blocks_left/right
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

template<class RandItKeys, class KeyCompare, class RandIt, class Compare, class Op>
void op_merge_blocks_left
   ( RandItKeys const key_first
   , KeyCompare key_comp
   , RandIt const first
   , typename iter_size<RandIt>::type const l_block
   , typename iter_size<RandIt>::type const l_irreg1
   , typename iter_size<RandIt>::type const n_block_a
   , typename iter_size<RandIt>::type const n_block_b
   , typename iter_size<RandIt>::type const l_irreg2
   , Compare comp, Op op)
{
   typedef typename iter_size<RandIt>::type       size_type;

   size_type const key_count = needed_keys_count(n_block_a, n_block_b);
   boost::ignore_unused(key_count);

//   BOOST_ASSERT(n_block_a || n_block_b);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted_and_unique(key_first, key_first + key_count, key_comp));
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_b || n_block_a == count_if_with(key_first, key_first + key_count, key_comp, key_first[n_block_a]));

   size_type n_block_b_left = n_block_b;
   size_type n_block_a_left = n_block_a;
   size_type n_block_left = size_type(n_block_b + n_block_a);
   RandItKeys key_mid(key_first + n_block_a);

   RandIt buffer = first - l_block;
   RandIt first1 = first;
   RandIt last1  = first1 + l_irreg1;
   RandIt first2 = last1;
   RandIt const irreg2 = first2 + size_type(n_block_left*l_block);
   bool is_range1_A = true;

   RandItKeys key_range2(key_first);

   ////////////////////////////////////////////////////////////////////////////
   //Process all regular blocks before the irregular B block
   ////////////////////////////////////////////////////////////////////////////
   size_type min_check = n_block_a == n_block_left ? 0u : n_block_a;
   size_type max_check = min_value<size_type>(size_type(min_check+1u), n_block_left);
   for (; n_block_left; --n_block_left) {
      size_type const next_key_idx = find_next_block(key_range2, key_comp, first2, l_block, min_check, max_check, comp);
      max_check = min_value<size_type>(max_value<size_type>(max_check, size_type(next_key_idx+2u)), n_block_left);
      RandIt const first_min = first2 + size_type(next_key_idx*l_block);
      RandIt const last_min  = first_min + l_block;

      boost::ignore_unused(last_min);
      RandIt const last2  = first2 + l_block;

      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first1, last1, comp));
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first2, last2, comp));
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_left || boost::movelib::is_sorted(first_min, last_min, comp));

      //Check if irregular b block should go here.
      //If so, break to the special code handling the irregular block
      if (!n_block_b_left &&
            ( (l_irreg2 && comp(*irreg2, *first_min)) || (!l_irreg2 && is_range1_A)) ){
         break;
      }

      RandItKeys const key_next(key_range2 + next_key_idx);
      bool const is_range2_A = key_mid == (key_first+key_count) || key_comp(*key_next, *key_mid);

      bool const is_buffer_middle = last1 == buffer;
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT( ( is_buffer_middle && size_type(first2-buffer) == l_block && buffer == last1) ||
                                          (!is_buffer_middle && size_type(first1-buffer) == l_block && first2 == last1));

      if(is_range1_A == is_range2_A){
         BOOST_ASSERT((first1 == last1) || !comp(*first_min, last1[typename iterator_traits<RandIt>::difference_type(-1)]));
         if(!is_buffer_middle){
            buffer = op(forward_t(), first1, last1, buffer);
         }
         swap_and_update_key(key_next, key_range2, key_mid, first2, last2, first_min);
         first1 = first2;
         last1  = last2;
      }
      else {
         RandIt unmerged;
         RandIt buf_beg;
         RandIt buf_end;
         if(is_buffer_middle){
            buf_end = buf_beg = first2 - (last1-first1);
            unmerged = op_partial_merge_and_save( first1, last1, first2, last2, first_min
                                                , buf_beg, buf_end, comp, op, is_range1_A);
         }  
         else{
            buf_beg = first1;
            buf_end = last1;
            unmerged = op_partial_merge_and_save
               (buffer, buffer+(last1-first1), first2, last2, first_min, buf_beg, buf_end, comp, op, is_range1_A);
         }

         boost::ignore_unused(unmerged);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first-l_block, unmerged, comp));

         swap_and_update_key( key_next, key_range2, key_mid, first2, last2
                            , last_min - size_type(last2 - first2));

         if(buf_beg != buf_end){  //range2 exhausted: is_buffer_middle for the next iteration
            first1 = buf_beg;
            last1  = buf_end;
            BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(buf_end == (last2-l_block));
            buffer = last1;
         }
         else{ //range1 exhausted: !is_buffer_middle for the next iteration
            first1 = first2;
            last1  = last2;
            buffer = first2 - l_block;
            is_range1_A = is_range2_A;
         }
      }
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT( (is_range2_A && n_block_a_left) || (!is_range2_A && n_block_b_left));
      is_range2_A ? --n_block_a_left : --n_block_b_left;
      first2 = last2;
      //Update context
      ++key_range2;
      min_check = size_type(min_check - (min_check != 0));
      max_check = size_type(max_check - (max_check != 0));
   }

   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_b || n_block_a == count_if_with(key_first, key_range2 + n_block_left, key_comp, *key_mid));
   BOOST_ASSERT(!n_block_b_left);

   ////////////////////////////////////////////////////////////////////////////
   //Process remaining range 1 left before the irregular B block
   ////////////////////////////////////////////////////////////////////////////
   bool const is_buffer_middle = last1 == buffer;
   RandIt first_irr2 = irreg2;
   RandIt const last_irr2  = first_irr2 + l_irreg2;
   if(l_irreg2 && is_range1_A){
      if(is_buffer_middle){
         first1 = skip_until_merge(first1, last1, *first_irr2, comp);
         //Even if we copy backward, no overlapping occurs so use forward copy
         //that can be faster specially with trivial types
         RandIt const new_first1 = first2 - (last1 - first1);
         op(forward_t(), first1, last1, new_first1);
         first1 = new_first1;
         last1 = first2;
         buffer = first1 - l_block;
      }
      buffer = op_partial_merge_impl(first1, last1, first_irr2, last_irr2, buffer, comp, op);
      buffer = op(forward_t(), first1, last1, buffer);
   }
   else if(!is_buffer_middle){
      buffer = op(forward_t(), first1, last1, buffer);
   }
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first-l_block, buffer, comp));

   ////////////////////////////////////////////////////////////////////////////
   //Process irregular B block and remaining A blocks
   ////////////////////////////////////////////////////////////////////////////
   buffer = op_merge_blocks_with_irreg
      ( key_range2, key_mid, key_comp, first2, first_irr2, last_irr2
      , buffer, l_block, n_block_left, min_check, max_check, comp, false, op);
   buffer = op(forward_t(), first_irr2, last_irr2, buffer);
   boost::ignore_unused(buffer);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first-l_block, buffer, comp));
}

// first - first element to merge.
// first[-l_block, 0) - buffer (if use_buf == true)
// l_block - length of regular blocks. First nblocks are stable sorted by 1st elements and key-coded
// keys - sequence of keys, in same order as blocks. key<midkey means stream A
// n_bef_irreg2/n_aft_irreg2 are regular blocks
// l_irreg2 is a irregular block, that is to be combined after n_bef_irreg2 blocks and before n_aft_irreg2 blocks
// If l_irreg2==0 then n_aft_irreg2==0 (no irregular blocks).
template<class RandItKeys, class KeyCompare, class RandIt, class Compare>
void merge_blocks_left
   ( RandItKeys const key_first
   , KeyCompare key_comp
   , RandIt const first
   , typename iter_size<RandIt>::type const l_block
   , typename iter_size<RandIt>::type const l_irreg1
   , typename iter_size<RandIt>::type const n_block_a
   , typename iter_size<RandIt>::type const n_block_b
   , typename iter_size<RandIt>::type const l_irreg2
   , Compare comp
   , bool const xbuf_used)
{
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_b || n_block_a == count_if_with(key_first, key_first + needed_keys_count(n_block_a, n_block_b), key_comp, key_first[n_block_a]));
   if(xbuf_used){
      op_merge_blocks_left
         (key_first, key_comp, first, l_block, l_irreg1, n_block_a, n_block_b, l_irreg2, comp, move_op());
   }
   else{
      op_merge_blocks_left
         (key_first, key_comp, first, l_block, l_irreg1, n_block_a, n_block_b, l_irreg2, comp, swap_op());
   }
}

// first - first element to merge.
// [first+l_block*(n_bef_irreg2+n_aft_irreg2)+l_irreg2, first+l_block*(n_bef_irreg2+n_aft_irreg2+1)+l_irreg2) - buffer
// l_block - length of regular blocks. First nblocks are stable sorted by 1st elements and key-coded
// keys - sequence of keys, in same order as blocks. key<midkey means stream A
// n_bef_irreg2/n_aft_irreg2 are regular blocks
// l_irreg2 is a irregular block, that is to be combined after n_bef_irreg2 blocks and before n_aft_irreg2 blocks
// If l_irreg2==0 then n_aft_irreg2==0 (no irregular blocks).
template<class RandItKeys, class KeyCompare, class RandIt, class Compare>
void merge_blocks_right
   ( RandItKeys const key_first
   , KeyCompare key_comp
   , RandIt const first
   , typename iter_size<RandIt>::type const l_block
   , typename iter_size<RandIt>::type const n_block_a
   , typename iter_size<RandIt>::type const n_block_b
   , typename iter_size<RandIt>::type const l_irreg2
   , Compare comp
   , bool const xbuf_used)
{
   typedef typename iter_size<RandIt>::type size_type;
   merge_blocks_left
      ( (make_reverse_iterator)(key_first + needed_keys_count(n_block_a, n_block_b))
      , inverse<KeyCompare>(key_comp)
      , (make_reverse_iterator)(first + size_type((n_block_a+n_block_b)*l_block+l_irreg2))
      , l_block
      , l_irreg2
      , n_block_b
      , n_block_a
      , 0
      , inverse<Compare>(comp), xbuf_used);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//    op_merge_blocks_with_buf
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
template<class RandItKeys, class KeyCompare, class RandIt, class Compare, class Op, class RandItBuf>
void op_merge_blocks_with_buf
   ( RandItKeys key_first
   , KeyCompare key_comp
   , RandIt const first
   , typename iter_size<RandIt>::type const l_block
   , typename iter_size<RandIt>::type const l_irreg1
   , typename iter_size<RandIt>::type const n_block_a
   , typename iter_size<RandIt>::type const n_block_b
   , typename iter_size<RandIt>::type const l_irreg2
   , Compare comp
   , Op op
   , RandItBuf const buf_first)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type const key_count = needed_keys_count(n_block_a, n_block_b);
   boost::ignore_unused(key_count);
   //BOOST_ASSERT(n_block_a || n_block_b);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted_and_unique(key_first, key_first + key_count, key_comp));
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_b || n_block_a == count_if_with(key_first, key_first + key_count, key_comp, key_first[n_block_a]));

   size_type n_block_b_left = n_block_b;
   size_type n_block_a_left = n_block_a;
   size_type n_block_left = size_type(n_block_b + n_block_a);
   RandItKeys key_mid(key_first + n_block_a);

   RandItBuf buffer = buf_first;
   RandItBuf buffer_end = buffer;
   RandIt first1 = first;
   RandIt last1  = first1 + l_irreg1;
   RandIt first2 = last1;
   RandIt const first_irr2 = first2 + size_type(n_block_left*l_block);
   bool is_range1_A = true;
   const size_type len = size_type(l_block * n_block_a + l_block * n_block_b + l_irreg1 + l_irreg2);
   boost::ignore_unused(len);

   RandItKeys key_range2(key_first);

   ////////////////////////////////////////////////////////////////////////////
   //Process all regular blocks before the irregular B block
   ////////////////////////////////////////////////////////////////////////////
   size_type min_check = n_block_a == n_block_left ? 0u : n_block_a;
   size_type max_check = min_value(size_type(min_check+1), n_block_left);
   for (; n_block_left; --n_block_left) {
      size_type const next_key_idx = find_next_block(key_range2, key_comp, first2, l_block, min_check, max_check, comp);
      max_check = min_value(max_value(max_check, size_type(next_key_idx+2)), n_block_left);
      RandIt       first_min = first2 + size_type(next_key_idx*l_block);
      RandIt const last_min  = first_min + l_block;
      boost::ignore_unused(last_min);
      RandIt const last2  = first2 + l_block;

      bool const buffer_empty = buffer == buffer_end;
      boost::ignore_unused(buffer_empty);
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(buffer_empty ? boost::movelib::is_sorted(first1, last1, comp) : boost::movelib::is_sorted(buffer, buffer_end, comp));
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first2, last2, comp));
      BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!n_block_left || boost::movelib::is_sorted(first_min, last_min, comp));

      //Check if irregular b block should go here.
      //If so, break to the special code handling the irregular block
      if (!n_block_b_left &&
            ( (l_irreg2 && comp(*first_irr2, *first_min)) || (!l_irreg2 && is_range1_A)) ){
         break;
      }

      RandItKeys const key_next(key_range2 + next_key_idx);
      bool const is_range2_A = key_mid == (key_first+key_count) || key_comp(*key_next, *key_mid);

      if(is_range1_A == is_range2_A){
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT((first1 == last1) || (buffer_empty ? !comp(*first_min, last1[-1]) : !comp(*first_min, buffer_end[-1])));
         //If buffered, put those elements in place
         RandIt res = op(forward_t(), buffer, buffer_end, first1);
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_fwd: ", len);
         buffer    = buffer_end = buf_first;
         BOOST_ASSERT(buffer_empty || res == last1);
         boost::ignore_unused(res);
         //swap_and_update_key(key_next, key_range2, key_mid, first2, last2, first_min);
         buffer_end = buffer_and_update_key(key_next, key_range2, key_mid, first2, last2, first_min, buffer = buf_first, op);
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_swp: ", len);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first2, last2, comp));
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first_min, last_min, comp));
         first1 = first2;
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, first1, comp));
      }
      else {
         RandIt const unmerged = op_partial_merge_and_save(first1, last1, first2, last2, first_min, buffer, buffer_end, comp, op, is_range1_A);
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_mrs: ", len);
         bool const is_range_1_empty = buffer == buffer_end;
         BOOST_ASSERT(is_range_1_empty || (buffer_end-buffer) == (last1+l_block-unmerged));
         if(is_range_1_empty){
            buffer    = buffer_end = buf_first;
            first_min = last_min - (last2 - first2);
            //swap_and_update_key(key_next, key_range2, key_mid, first2, last2, first_min);
            buffer_end = buffer_and_update_key(key_next, key_range2, key_mid, first2, last2, first_min, buf_first, op);
         }
         else{
            first_min = last_min;
            //swap_and_update_key(key_next, key_range2, key_mid, first2, last2, first_min);
            update_key(key_next, key_range2, key_mid);
         }
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(!is_range_1_empty || (last_min-first_min) == (last2-unmerged));
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_swp: ", len);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first_min, last_min, comp));
         is_range1_A ^= is_range_1_empty;
         first1 = unmerged;
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, unmerged, comp));
      }
      BOOST_ASSERT( (is_range2_A && n_block_a_left) || (!is_range2_A && n_block_b_left));
      is_range2_A ? --n_block_a_left : --n_block_b_left;
      last1 += l_block;
      first2 = last2;
      //Update context
      ++key_range2;
      min_check = size_type(min_check - (min_check != 0));
      max_check = size_type(max_check - (max_check != 0));
   }
   RandIt res = op(forward_t(), buffer, buffer_end, first1);
   boost::ignore_unused(res);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, res, comp));
   BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_fwd: ", len);

   ////////////////////////////////////////////////////////////////////////////
   //Process irregular B block and remaining A blocks
   ////////////////////////////////////////////////////////////////////////////
   RandIt const last_irr2 = first_irr2 + l_irreg2;
   op(forward_t(), first_irr2, first_irr2+l_irreg2, buf_first);
   BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_fwir:", len);
   buffer = buf_first;
   buffer_end = buffer+l_irreg2;

   reverse_iterator<RandItBuf> rbuf_beg(buffer_end);
   RandIt dest = op_merge_blocks_with_irreg
      ((make_reverse_iterator)(key_first + n_block_b + n_block_a), (make_reverse_iterator)(key_mid), inverse<KeyCompare>(key_comp)
      , (make_reverse_iterator)(first_irr2), rbuf_beg, (make_reverse_iterator)(buffer), (make_reverse_iterator)(last_irr2)
      , l_block, n_block_left, 0, n_block_left
      , inverse<Compare>(comp), true, op).base();
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(dest, last_irr2, comp));
   BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_blocks_w_irg: ", len);

   buffer_end = rbuf_beg.base();
   BOOST_ASSERT((dest-last1) == (buffer_end-buffer));
   op_merge_with_left_placed(is_range1_A ? first1 : last1, last1, dest, buffer, buffer_end, comp, op);
   BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   merge_with_left_plc:", len);
   BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(first, last_irr2, comp));
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//  op_insertion_sort_step_left/right
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

template<class RandIt, class Compare, class Op>
typename iter_size<RandIt>::type
   op_insertion_sort_step_left
      ( RandIt const first
      , typename iter_size<RandIt>::type const length
      , typename iter_size<RandIt>::type const step
      , Compare comp, Op op)
{
   typedef typename iter_size<RandIt>::type       size_type;

   size_type const s = min_value<size_type>(step, AdaptiveSortInsertionSortThreshold);
   size_type m = 0;

   while(size_type(length - m) > s){
      insertion_sort_op(first+m, first+m+s, first+m-s, comp, op);
      m = size_type(m + s);
   }
   insertion_sort_op(first+m, first+length, first+m-s, comp, op);
   return s;
}

template<class RandIt, class Compare, class Op>
void op_merge_right_step_once
      ( RandIt first_block
      , typename iter_size<RandIt>::type const elements_in_blocks
      , typename iter_size<RandIt>::type const l_build_buf
      , Compare comp
      , Op op)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type restk = size_type(elements_in_blocks%(2*l_build_buf));
   size_type p = size_type(elements_in_blocks - restk);
   BOOST_ASSERT(0 == (p%(2*l_build_buf)));

   if(restk <= l_build_buf){
      op(backward_t(),first_block+p, first_block+p+restk, first_block+p+restk+l_build_buf);
   }
   else{
      op_merge_right(first_block+p, first_block+p+l_build_buf, first_block+p+restk, first_block+p+restk+l_build_buf, comp, op);
   }
   while(p>0){
      p = size_type(p - 2u*l_build_buf);
      op_merge_right( first_block+p, first_block+size_type(p+l_build_buf)
                    , first_block+size_type(p+2*l_build_buf)
                    , first_block+size_type(p+3*l_build_buf), comp, op);
   }
}


//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//    insertion_sort_step
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
template<class RandIt, class Compare>
typename iter_size<RandIt>::type
   insertion_sort_step
      ( RandIt const first
      , typename iter_size<RandIt>::type const length
      , typename iter_size<RandIt>::type const step
      , Compare comp)
{
   typedef typename iter_size<RandIt>::type size_type;
   size_type const s = min_value<size_type>(step, AdaptiveSortInsertionSortThreshold);
   size_type m = 0;

   while((length - m) > s){
      insertion_sort(first+m, first+m+s, comp);
      m = size_type(m + s);
   }
   insertion_sort(first+m, first+length, comp);
   return s;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
//
//    op_merge_left_step_multiple
//
//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
template<class RandIt, class Compare, class Op>
typename iter_size<RandIt>::type  
   op_merge_left_step_multiple
      ( RandIt first_block
      , typename iter_size<RandIt>::type const elements_in_blocks
      , typename iter_size<RandIt>::type l_merged
      , typename iter_size<RandIt>::type const l_build_buf
      , typename iter_size<RandIt>::type l_left_space
      , Compare comp
      , Op op)
{
   typedef typename iter_size<RandIt>::type size_type;
   for(; l_merged < l_build_buf && l_left_space >= l_merged; l_merged = size_type(l_merged*2u)){
      size_type p0=0;
      RandIt pos = first_block;
      while((elements_in_blocks - p0) > 2*l_merged) {
         op_merge_left(pos-l_merged, pos, pos+l_merged, pos+size_type(2*l_merged), comp, op);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(pos-l_merged, pos+l_merged, comp));
         p0 = size_type(p0 + 2u*l_merged);
         pos = first_block+p0;
      }
      if((elements_in_blocks-p0) > l_merged) {
         op_merge_left(pos-l_merged, pos, pos+l_merged, first_block+elements_in_blocks, comp, op);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT
            (boost::movelib::is_sorted
               (pos-l_merged, pos+size_type((first_block+elements_in_blocks-pos))-l_merged, comp));
      }
      else {
         op(forward_t(), pos, first_block+elements_in_blocks, pos-l_merged);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT
            (boost::movelib::is_sorted
               (pos-l_merged, first_block+size_type(elements_in_blocks-l_merged), comp));
      }
      first_block  -= l_merged;
      l_left_space = size_type(l_left_space - l_merged);
   }
   return l_merged;
}


}  //namespace detail_adaptive {
}  //namespace movelib {
}  //namespace boost {

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#include <boost/move/detail/config_end.hpp>

#endif   //#define BOOST_MOVE_ADAPTIVE_SORT_MERGE_HPP

/* adaptive_sort_merge.hpp
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
*/