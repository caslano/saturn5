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

#ifndef BOOST_MOVE_ADAPTIVE_MERGE_HPP
#define BOOST_MOVE_ADAPTIVE_MERGE_HPP

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/algo/detail/adaptive_sort_merge.hpp>

namespace boost {
namespace movelib {

///@cond
namespace detail_adaptive {

template<class RandIt, class Compare, class XBuf>
inline void adaptive_merge_combine_blocks( RandIt first
                                      , typename iterator_traits<RandIt>::size_type len1
                                      , typename iterator_traits<RandIt>::size_type len2
                                      , typename iterator_traits<RandIt>::size_type collected
                                      , typename iterator_traits<RandIt>::size_type n_keys
                                      , typename iterator_traits<RandIt>::size_type l_block
                                      , bool use_internal_buf
                                      , bool xbuf_used
                                      , Compare comp
                                      , XBuf & xbuf
                                      )
{
   typedef typename iterator_traits<RandIt>::size_type size_type;
   size_type const len = len1+len2;
   size_type const l_combine  = len-collected;
   size_type const l_combine1 = len1-collected;

    if(n_keys){
      RandIt const first_data = first+collected;
      RandIt const keys = first;
      BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   A combine: ", len);
      if(xbuf_used){
         if(xbuf.size() < l_block){
            xbuf.initialize_until(l_block, *first);
         }
         BOOST_ASSERT(xbuf.size() >= l_block);
         size_type n_block_a, n_block_b, l_irreg1, l_irreg2;
         combine_params( keys, comp, l_combine
                           , l_combine1, l_block, xbuf
                           , n_block_a, n_block_b, l_irreg1, l_irreg2);   //Outputs
         op_merge_blocks_with_buf
            (keys, comp, first_data, l_block, l_irreg1, n_block_a, n_block_b, l_irreg2, comp, move_op(), xbuf.data());
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("   A mrg xbf: ", len);
      }
      else{
         size_type n_block_a, n_block_b, l_irreg1, l_irreg2;
         combine_params( keys, comp, l_combine
                           , l_combine1, l_block, xbuf
                           , n_block_a, n_block_b, l_irreg1, l_irreg2);   //Outputs
         if(use_internal_buf){
            op_merge_blocks_with_buf
               (keys, comp, first_data, l_block, l_irreg1, n_block_a, n_block_b, l_irreg2, comp, swap_op(), first_data-l_block);
            BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   A mrg buf: ", len);
         }
         else{
            merge_blocks_bufferless
               (keys, comp, first_data, l_block, l_irreg1, n_block_a, n_block_b, l_irreg2, comp);
            BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("   A mrg nbf: ", len);
         }
      }
   }
   else{
      xbuf.shrink_to_fit(l_block);
      if(xbuf.size() < l_block){
         xbuf.initialize_until(l_block, *first);
      }
      size_type *const uint_keys = xbuf.template aligned_trailing<size_type>(l_block);
      size_type n_block_a, n_block_b, l_irreg1, l_irreg2;
      combine_params( uint_keys, less(), l_combine
                     , l_combine1, l_block, xbuf
                     , n_block_a, n_block_b, l_irreg1, l_irreg2, true);   //Outputs
      BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   A combine: ", len);
      BOOST_ASSERT(xbuf.size() >= l_block);
      op_merge_blocks_with_buf
         (uint_keys, less(), first, l_block, l_irreg1, n_block_a, n_block_b, l_irreg2, comp, move_op(), xbuf.data());
      xbuf.clear();
      BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("   A mrg buf: ", len);
   }
}

template<class RandIt, class Compare, class XBuf>
inline void adaptive_merge_final_merge( RandIt first
                                      , typename iterator_traits<RandIt>::size_type len1
                                      , typename iterator_traits<RandIt>::size_type len2
                                      , typename iterator_traits<RandIt>::size_type collected
                                      , typename iterator_traits<RandIt>::size_type l_intbuf
                                      , typename iterator_traits<RandIt>::size_type l_block
                                      , bool use_internal_buf
                                      , bool xbuf_used
                                      , Compare comp
                                      , XBuf & xbuf
                                      )
{
   typedef typename iterator_traits<RandIt>::size_type size_type;
   (void)l_block;
   (void)use_internal_buf;
   size_type n_keys = collected-l_intbuf;
   size_type len = len1+len2;
   if (!xbuf_used || n_keys) {
      xbuf.clear();
      const size_type middle = xbuf_used && n_keys ? n_keys: collected;
      unstable_sort(first, first + middle, comp, xbuf);
      BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   A k/b srt: ", len);
      stable_merge(first, first + middle, first + len, comp, xbuf);
   }
   BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("   A fin mrg: ", len);
}

template<class SizeType>
inline static SizeType adaptive_merge_n_keys_without_external_keys(SizeType l_block, SizeType len1, SizeType len2, SizeType l_intbuf)
{
   typedef SizeType size_type;
   //This is the minimum number of keys to implement the ideal algorithm
   size_type n_keys = len1/l_block+len2/l_block;
   const size_type second_half_blocks = len2/l_block;
   const size_type first_half_aux = len1-l_intbuf;
   while(n_keys >= ((first_half_aux-n_keys)/l_block + second_half_blocks)){
      --n_keys;
   }
   ++n_keys;
   return n_keys;
}

template<class SizeType>
inline static SizeType adaptive_merge_n_keys_with_external_keys(SizeType l_block, SizeType len1, SizeType len2, SizeType l_intbuf)
{
   typedef SizeType size_type;
   //This is the minimum number of keys to implement the ideal algorithm
   size_type n_keys = (len1-l_intbuf)/l_block + len2/l_block;
   return n_keys;
}

template<class SizeType, class Xbuf>
inline SizeType adaptive_merge_n_keys_intbuf(SizeType &rl_block, SizeType len1, SizeType len2, Xbuf & xbuf, SizeType &l_intbuf_inout)
{
   typedef SizeType size_type;
   size_type l_block = rl_block;
   size_type l_intbuf = xbuf.capacity() >= l_block ? 0u : l_block;

   if (xbuf.capacity() > l_block){
      l_block = xbuf.capacity();
   }

   //This is the minimum number of keys to implement the ideal algorithm
   size_type n_keys = adaptive_merge_n_keys_without_external_keys(l_block, len1, len2, l_intbuf);
   BOOST_ASSERT(n_keys >= ((len1-l_intbuf-n_keys)/l_block + len2/l_block));

   if(xbuf.template supports_aligned_trailing<size_type>
      ( l_block
      , adaptive_merge_n_keys_with_external_keys(l_block, len1, len2, l_intbuf)))
   {
      n_keys = 0u;
   }
   l_intbuf_inout = l_intbuf;
   rl_block = l_block;
   return n_keys;
}

// Main explanation of the merge algorithm.
//
// csqrtlen = ceil(sqrt(len));
//
// * First, csqrtlen [to be used as buffer] + (len/csqrtlen - 1) [to be used as keys] => to_collect
//   unique elements are extracted from elements to be sorted and placed in the beginning of the range.
//
// * Step "combine_blocks": the leading (len1-to_collect) elements plus trailing len2 elements
//   are merged with a non-trivial ("smart") algorithm to form an ordered range trailing "len-to_collect" elements.
//
//   Explanation of the "combine_blocks" step:
//
//         * Trailing [first+to_collect, first+len1) elements are divided in groups of cqrtlen elements.
//           Remaining elements that can't form a group are grouped in front of those elements.
//         * Trailing [first+len1, first+len1+len2) elements are divided in groups of cqrtlen elements.
//           Remaining elements that can't form a group are grouped in the back of those elements.
//         * In parallel the following two steps are performed:
//             *  Groups are selection-sorted by first or last element (depending whether they are going
//                to be merged to left or right) and keys are reordered accordingly as an imitation-buffer.
//             * Elements of each block pair are merged using the csqrtlen buffer taking into account
//                if they belong to the first half or second half (marked by the key).
//
// * In the final merge step leading "to_collect" elements are merged with rotations
//   with the rest of merged elements in the "combine_blocks" step.
//
// Corner cases:
//
// * If no "to_collect" elements can be extracted:
//
//    * If more than a minimum number of elements is extracted
//      then reduces the number of elements used as buffer and keys in the
//      and "combine_blocks" steps. If "combine_blocks" has no enough keys due to this reduction
//      then uses a rotation based smart merge.
//
//    * If the minimum number of keys can't be extracted, a rotation-based merge is performed.
//
// * If auxiliary memory is more or equal than min(len1, len2), a buffered merge is performed.
//
// * If the len1 or len2 are less than 2*csqrtlen then a rotation-based merge is performed.
//
// * If auxiliary memory is more than csqrtlen+n_keys*sizeof(std::size_t),
//   then no csqrtlen need to be extracted and "combine_blocks" will use integral
//   keys to combine blocks.
template<class RandIt, class Compare, class XBuf>
void adaptive_merge_impl
   ( RandIt first
   , typename iterator_traits<RandIt>::size_type len1
   , typename iterator_traits<RandIt>::size_type len2
   , Compare comp
   , XBuf & xbuf
   )
{
   typedef typename iterator_traits<RandIt>::size_type size_type;

   if(xbuf.capacity() >= min_value<size_type>(len1, len2)){
      buffered_merge(first, first+len1, first+(len1+len2), comp, xbuf);
   }
   else{
      const size_type len = len1+len2;
      //Calculate ideal parameters and try to collect needed unique keys
      size_type l_block = size_type(ceil_sqrt(len));

      //One range is not big enough to extract keys and the internal buffer so a
      //rotation-based based merge will do just fine
      if(len1 <= l_block*2 || len2 <= l_block*2){
         merge_bufferless(first, first+len1, first+len1+len2, comp);
         return;
      }

      //Detail the number of keys and internal buffer. If xbuf has enough memory, no
      //internal buffer is needed so l_intbuf will remain 0.
      size_type l_intbuf = 0;
      size_type n_keys = adaptive_merge_n_keys_intbuf(l_block, len1, len2, xbuf, l_intbuf);
      size_type const to_collect = l_intbuf+n_keys;
      //Try to extract needed unique values from the first range
      size_type const collected  = collect_unique(first, first+len1, to_collect, comp, xbuf);
      BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("\n   A collect: ", len);

      //Not the minimum number of keys is not available on the first range, so fallback to rotations
      if(collected != to_collect && collected < 4){
         merge_bufferless(first, first+collected, first+len1, comp);
         merge_bufferless(first, first + len1, first + len1 + len2, comp);
         return;
      }

      //If not enough keys but more than minimum, adjust the internal buffer and key count
      bool use_internal_buf = collected == to_collect;
      if (!use_internal_buf){
         l_intbuf = 0u;
         n_keys = collected;
         l_block  = lblock_for_combine(l_intbuf, n_keys, len, use_internal_buf);
         //If use_internal_buf is false, then then internal buffer will be zero and rotation-based combination will be used
         l_intbuf = use_internal_buf ? l_block : 0u;
      }

      bool const xbuf_used = collected == to_collect && xbuf.capacity() >= l_block;
      //Merge trailing elements using smart merges
      adaptive_merge_combine_blocks(first, len1, len2, collected,   n_keys, l_block, use_internal_buf, xbuf_used, comp, xbuf);
      //Merge buffer and keys with the rest of the values
      adaptive_merge_final_merge   (first, len1, len2, collected, l_intbuf, l_block, use_internal_buf, xbuf_used, comp, xbuf);
   }
}

}  //namespace detail_adaptive {

///@endcond

//! <b>Effects</b>: Merges two consecutive sorted ranges [first, middle) and [middle, last)
//!   into one sorted range [first, last) according to the given comparison function comp.
//!   The algorithm is stable (if there are equivalent elements in the original two ranges,
//!   the elements from the first range (preserving their original order) precede the elements
//!   from the second range (preserving their original order).
//!
//! <b>Requires</b>:
//!   - RandIt must meet the requirements of ValueSwappable and RandomAccessIterator.
//!   - The type of dereferenced RandIt must meet the requirements of MoveAssignable and MoveConstructible.
//!
//! <b>Parameters</b>:
//!   - first: the beginning of the first sorted range. 
//!   - middle: the end of the first sorted range and the beginning of the second
//!   - last: the end of the second sorted range
//!   - comp: comparison function object which returns true if the first argument is is ordered before the second.
//!   - uninitialized, uninitialized_len: raw storage starting on "uninitialized", able to hold "uninitialized_len"
//!      elements of type iterator_traits<RandIt>::value_type. Maximum performance is achieved when uninitialized_len
//!      is min(std::distance(first, middle), std::distance(middle, last)).
//!
//! <b>Throws</b>: If comp throws or the move constructor, move assignment or swap of the type
//!   of dereferenced RandIt throws.
//!
//! <b>Complexity</b>: Always K x O(N) comparisons and move assignments/constructors/swaps.
//!   Constant factor for comparisons and data movement is minimized when uninitialized_len
//!   is min(std::distance(first, middle), std::distance(middle, last)).
//!   Pretty good enough performance is achieved when uninitialized_len is
//!   ceil(sqrt(std::distance(first, last)))*2.
//!
//! <b>Caution</b>: Experimental implementation, not production-ready.
template<class RandIt, class Compare>
void adaptive_merge( RandIt first, RandIt middle, RandIt last, Compare comp
                , typename iterator_traits<RandIt>::value_type* uninitialized = 0
                , typename iterator_traits<RandIt>::size_type uninitialized_len = 0)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;
   typedef typename iterator_traits<RandIt>::value_type value_type;

   if (first == middle || middle == last){
      return;
   }

   //Reduce ranges to merge if possible
   do {
      if (comp(*middle, *first)){
         break;
      }
      ++first;
      if (first == middle)
         return;
   } while(1);

   RandIt first_high(middle);
   --first_high;
   do {
      --last;
      if (comp(*last, *first_high)){
         ++last;
         break;
      }
      if (last == middle)
         return;
   } while(1);

   ::boost::movelib::adaptive_xbuf<value_type, value_type*, size_type> xbuf(uninitialized, size_type(uninitialized_len));
   ::boost::movelib::detail_adaptive::adaptive_merge_impl(first, size_type(middle - first), size_type(last - middle), comp, xbuf);
}

}  //namespace movelib {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif   //#define BOOST_MOVE_ADAPTIVE_MERGE_HPP

/* adaptive_merge.hpp
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
*/