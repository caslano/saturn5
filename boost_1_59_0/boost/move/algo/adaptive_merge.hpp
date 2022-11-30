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

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {
namespace movelib {

///@cond
namespace detail_adaptive {

template<class RandIt, class Compare, class XBuf>
inline void adaptive_merge_combine_blocks( RandIt first
                                      , typename iter_size<RandIt>::type len1
                                      , typename iter_size<RandIt>::type len2
                                      , typename iter_size<RandIt>::type collected
                                      , typename iter_size<RandIt>::type n_keys
                                      , typename iter_size<RandIt>::type l_block
                                      , bool use_internal_buf
                                      , bool xbuf_used
                                      , Compare comp
                                      , XBuf & xbuf
                                      )
{
   typedef typename iter_size<RandIt>::type       size_type;

   size_type const len = size_type(len1+len2);
   size_type const l_combine  = size_type(len-collected);
   size_type const l_combine1 = size_type(len1-collected);

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
               ( keys, comp, first_data, l_block, l_irreg1, n_block_a, n_block_b
               , l_irreg2, comp, swap_op(), first_data-l_block);
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
                                      , typename iter_size<RandIt>::type len1
                                      , typename iter_size<RandIt>::type len2
                                      , typename iter_size<RandIt>::type collected
                                      , typename iter_size<RandIt>::type l_intbuf
                                      , typename iter_size<RandIt>::type //l_block
                                      , bool //use_internal_buf
                                      , bool xbuf_used
                                      , Compare comp
                                      , XBuf & xbuf
                                      )
{
   typedef typename iter_size<RandIt>::type       size_type;

   size_type n_keys = size_type(collected-l_intbuf);
   size_type len = size_type(len1+len2);
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
   size_type n_keys = size_type(len1/l_block + len2/l_block);
   const size_type second_half_blocks = size_type(len2/l_block);
   const size_type first_half_aux = size_type(len1 - l_intbuf);
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
   size_type n_keys = size_type((len1-l_intbuf)/l_block + len2/l_block);
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
   , typename iter_size<RandIt>::type len1
   , typename iter_size<RandIt>::type len2
   , Compare comp
   , XBuf & xbuf
   )
{
   typedef typename iter_size<RandIt>::type size_type;

   if(xbuf.capacity() >= min_value<size_type>(len1, len2)){
      buffered_merge( first, first+len1
                    , first + len1+len2, comp, xbuf);
   }
   else{
      const size_type len = size_type(len1+len2);
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
      size_type const to_collect = size_type(l_intbuf+n_keys);
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
                , typename iter_size<RandIt>::type uninitialized_len = 0)
{
   typedef typename iter_size<RandIt>::type  size_type;
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

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#include <boost/move/detail/config_end.hpp>

#endif   //#define BOOST_MOVE_ADAPTIVE_MERGE_HPP

/* adaptive_merge.hpp
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
*/