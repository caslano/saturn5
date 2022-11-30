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

#ifndef BOOST_MOVE_ADAPTIVE_SORT_HPP
#define BOOST_MOVE_ADAPTIVE_SORT_HPP

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/algo/detail/adaptive_sort_merge.hpp>
#include <boost/core/ignore_unused.hpp>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {
namespace movelib {

///@cond
namespace detail_adaptive {

template<class RandIt>
void move_data_backward( RandIt cur_pos
              , typename iter_size<RandIt>::type const l_data
              , RandIt new_pos
              , bool const xbuf_used)
{
   //Move buffer to the total combination right
   if(xbuf_used){
      boost::move_backward(cur_pos, cur_pos+l_data, new_pos+l_data);      
   }
   else{
      boost::adl_move_swap_ranges_backward(cur_pos, cur_pos+l_data, new_pos+l_data);      
      //Rotate does less moves but it seems slower due to cache issues
      //rotate_gcd(first-l_block, first+len-l_block, first+len);
   }
}

template<class RandIt>
void move_data_forward( RandIt cur_pos
              , typename iter_size<RandIt>::type const l_data
              , RandIt new_pos
              , bool const xbuf_used)
{
   //Move buffer to the total combination right
   if(xbuf_used){
      boost::move(cur_pos, cur_pos+l_data, new_pos);
   }
   else{
      boost::adl_move_swap_ranges(cur_pos, cur_pos+l_data, new_pos);
      //Rotate does less moves but it seems slower due to cache issues
      //rotate_gcd(first-l_block, first+len-l_block, first+len);
   }
}

// build blocks of length 2*l_build_buf. l_build_buf is power of two
// input: [0, l_build_buf) elements are buffer, rest unsorted elements
// output: [0, l_build_buf) elements are buffer, blocks 2*l_build_buf and last subblock sorted
//
// First elements are merged from right to left until elements start
// at first. All old elements [first, first + l_build_buf) are placed at the end
// [first+len-l_build_buf, first+len). To achieve this:
// - If we have external memory to merge, we save elements from the buffer
//   so that a non-swapping merge is used. Buffer elements are restored
//   at the end of the buffer from the external memory.
//
// - When the external memory is not available or it is insufficient
//   for a merge operation, left swap merging is used.
//
// Once elements are merged left to right in blocks of l_build_buf, then a single left
// to right merge step is performed to achieve merged blocks of size 2K.
// If external memory is available, usual merge is used, swap merging otherwise.
//
// As a last step, if auxiliary memory is available in-place merge is performed.
// until all is merged or auxiliary memory is not large enough.
template<class RandIt, class Compare, class XBuf>
typename iter_size<RandIt>::type  
   adaptive_sort_build_blocks
      ( RandIt const first
      , typename iter_size<RandIt>::type const len
      , typename iter_size<RandIt>::type const l_base
      , typename iter_size<RandIt>::type const l_build_buf
      , XBuf & xbuf
      , Compare comp)
{
   typedef typename iter_size<RandIt>::type       size_type;
   BOOST_ASSERT(l_build_buf <= len);
   BOOST_ASSERT(0 == ((l_build_buf / l_base)&(l_build_buf/l_base-1)));

   //Place the start pointer after the buffer
   RandIt first_block = first + l_build_buf;
   size_type const elements_in_blocks = size_type(len - l_build_buf);

   //////////////////////////////////
   // Start of merge to left step
   //////////////////////////////////
   size_type l_merged = 0u;

   BOOST_ASSERT(l_build_buf);
   //If there is no enough buffer for the insertion sort step, just avoid the external buffer
   size_type kbuf = min_value<size_type>(l_build_buf, size_type(xbuf.capacity()));
   kbuf = kbuf < l_base ? 0 : kbuf;

   if(kbuf){
      //Backup internal buffer values in external buffer so they can be overwritten
      xbuf.move_assign(first+l_build_buf-kbuf, kbuf);
      l_merged = op_insertion_sort_step_left(first_block, elements_in_blocks, l_base, comp, move_op());

      //Now combine them using the buffer. Elements from buffer can be
      //overwritten since they've been saved to xbuf
      l_merged = op_merge_left_step_multiple
         ( first_block - l_merged, elements_in_blocks, l_merged, l_build_buf, size_type(kbuf - l_merged), comp, move_op());

      //Restore internal buffer from external buffer unless kbuf was l_build_buf,
      //in that case restoration will happen later
      if(kbuf != l_build_buf){
         boost::move(xbuf.data()+kbuf-l_merged, xbuf.data() + kbuf, first_block-l_merged+elements_in_blocks);
      }
   }
   else{
      l_merged = insertion_sort_step(first_block, elements_in_blocks, l_base, comp);
      rotate_gcd(first_block-l_merged, first_block, first_block+elements_in_blocks);
   }

   //Now combine elements using the buffer. Elements from buffer can't be
   //overwritten since xbuf was not big enough, so merge swapping elements.
   l_merged = op_merge_left_step_multiple
      (first_block-l_merged, elements_in_blocks, l_merged, l_build_buf, size_type(l_build_buf - l_merged), comp, swap_op());

   BOOST_ASSERT(l_merged == l_build_buf);

   //////////////////////////////////
   // Start of merge to right step
   //////////////////////////////////

   //If kbuf is l_build_buf then we can merge right without swapping
   //Saved data is still in xbuf
   if(kbuf && kbuf == l_build_buf){
      op_merge_right_step_once(first, elements_in_blocks, l_build_buf, comp, move_op());
      //Restore internal buffer from external buffer if kbuf was l_build_buf.
      //as this operation was previously delayed.
      boost::move(xbuf.data(), xbuf.data() + kbuf, first);
   }
   else{
      op_merge_right_step_once(first, elements_in_blocks, l_build_buf, comp, swap_op());
   }
   xbuf.clear();
   //2*l_build_buf or total already merged
   return min_value<size_type>(elements_in_blocks, size_type(2u*l_build_buf));
}

template<class RandItKeys, class KeyCompare, class RandIt, class Compare, class XBuf>
void adaptive_sort_combine_blocks
   ( RandItKeys const keys
   , KeyCompare key_comp
   , RandIt const first
   , typename iter_size<RandIt>::type const len
   , typename iter_size<RandIt>::type const l_prev_merged
   , typename iter_size<RandIt>::type const l_block
   , bool const use_buf
   , bool const xbuf_used
   , XBuf & xbuf
   , Compare comp
   , bool merge_left)
{
   boost::ignore_unused(xbuf);
   typedef typename iter_size<RandIt>::type         size_type;

   size_type const l_reg_combined   = size_type(2u*l_prev_merged);
   size_type l_irreg_combined = 0;
   size_type const l_total_combined = calculate_total_combined(len, l_prev_merged, &l_irreg_combined);
   size_type const n_reg_combined = len/l_reg_combined;
   RandIt combined_first = first;

   boost::ignore_unused(l_total_combined);
   BOOST_ASSERT(l_total_combined <= len);

   size_type const max_i = size_type(n_reg_combined + (l_irreg_combined != 0));

   if(merge_left || !use_buf) {
      for( size_type combined_i = 0; combined_i != max_i; ) {
         //Now merge blocks
         bool const is_last = combined_i==n_reg_combined;
         size_type const l_cur_combined = is_last ? l_irreg_combined : l_reg_combined;

         range_xbuf<RandIt, size_type, move_op> rbuf( (use_buf && xbuf_used) ? (combined_first-l_block) : combined_first, combined_first);
         size_type n_block_a, n_block_b, l_irreg1, l_irreg2;
         combine_params( keys, key_comp, l_cur_combined
                        , l_prev_merged, l_block, rbuf
                        , n_block_a, n_block_b, l_irreg1, l_irreg2);   //Outputs
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   A combpar:            ", len + l_block);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(combined_first, combined_first + n_block_a*l_block+l_irreg1, comp));
            BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(combined_first + n_block_a*l_block+l_irreg1, combined_first + n_block_a*l_block+l_irreg1+n_block_b*l_block+l_irreg2, comp));
         if(!use_buf){
            merge_blocks_bufferless
               (keys, key_comp, combined_first, l_block, 0u, n_block_a, n_block_b, l_irreg2, comp);
         }
         else{
            merge_blocks_left
               (keys, key_comp, combined_first, l_block, 0u, n_block_a, n_block_b, l_irreg2, comp, xbuf_used);
         }
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   After merge_blocks_L: ", len + l_block);
         ++combined_i;
         if(combined_i != max_i)
            combined_first += l_reg_combined;
      }
   }
   else{
      combined_first += size_type(l_reg_combined*(max_i-1u));
      for( size_type combined_i = max_i; combined_i; ) {
         --combined_i;
         bool const is_last = combined_i==n_reg_combined;
         size_type const l_cur_combined = is_last ? l_irreg_combined : l_reg_combined;

         RandIt const combined_last(combined_first+l_cur_combined);
         range_xbuf<RandIt, size_type, move_op> rbuf(combined_last, xbuf_used ? (combined_last+l_block) : combined_last);
         size_type n_block_a, n_block_b, l_irreg1, l_irreg2;
         combine_params( keys, key_comp, l_cur_combined
                        , l_prev_merged, l_block, rbuf
                        , n_block_a, n_block_b, l_irreg1, l_irreg2);  //Outputs
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   A combpar:            ", len + l_block);
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(combined_first, combined_first + n_block_a*l_block+l_irreg1, comp));
         BOOST_MOVE_ADAPTIVE_SORT_INVARIANT(boost::movelib::is_sorted(combined_first + n_block_a*l_block+l_irreg1, combined_first + n_block_a*l_block+l_irreg1+n_block_b*l_block+l_irreg2, comp));
         merge_blocks_right
            (keys, key_comp, combined_first, l_block, n_block_a, n_block_b, l_irreg2, comp, xbuf_used);
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   After merge_blocks_R: ", len + l_block);
         if(combined_i)
            combined_first -= l_reg_combined;
      }
   }
}

//Returns true if buffer is placed in 
//[buffer+len-l_intbuf, buffer+len). Otherwise, buffer is
//[buffer,buffer+l_intbuf)
template<class RandIt, class Compare, class XBuf>
bool adaptive_sort_combine_all_blocks
   ( RandIt keys
   , typename iter_size<RandIt>::type &n_keys
   , RandIt const buffer
   , typename iter_size<RandIt>::type const l_buf_plus_data
   , typename iter_size<RandIt>::type l_merged
   , typename iter_size<RandIt>::type &l_intbuf
   , XBuf & xbuf
   , Compare comp)
{
   typedef typename iter_size<RandIt>::type       size_type;

   RandIt const first = buffer + l_intbuf;
   size_type const l_data = size_type(l_buf_plus_data - l_intbuf);
   size_type const l_unique = size_type(l_intbuf + n_keys);
   //Backup data to external buffer once if possible
   bool const common_xbuf = l_data > l_merged && l_intbuf && l_intbuf <= xbuf.capacity();
   if(common_xbuf){
      xbuf.move_assign(buffer, l_intbuf);
   }

   bool prev_merge_left = true;
   size_type l_prev_total_combined = l_merged, l_prev_block = 0;
   bool prev_use_internal_buf = true;

   for( size_type n = 0; l_data > l_merged
      ; l_merged = size_type(2u*l_merged)
      , ++n){
      //If l_intbuf is non-zero, use that internal buffer.
      //    Implies l_block == l_intbuf && use_internal_buf == true
      //If l_intbuf is zero, see if half keys can be reused as a reduced emergency buffer,
      //    Implies l_block == n_keys/2 && use_internal_buf == true
      //Otherwise, just give up and and use all keys to merge using rotations (use_internal_buf = false)
      bool use_internal_buf = false;
      size_type const l_block = lblock_for_combine(l_intbuf, n_keys, size_type(2*l_merged), use_internal_buf);
      BOOST_ASSERT(!l_intbuf || (l_block == l_intbuf));
      BOOST_ASSERT(n == 0 || (!use_internal_buf || prev_use_internal_buf) );
      BOOST_ASSERT(n == 0 || (!use_internal_buf || l_prev_block == l_block) );
      
      bool const is_merge_left = (n&1) == 0;
      size_type const l_total_combined = calculate_total_combined(l_data, l_merged);
      if(n && prev_use_internal_buf && prev_merge_left){
         if(is_merge_left || !use_internal_buf){
            move_data_backward(first-l_prev_block, l_prev_total_combined, first, common_xbuf);
         }
         else{
            //Put the buffer just after l_total_combined
            RandIt const buf_end = first+l_prev_total_combined;
            RandIt const buf_beg = buf_end-l_block;
            if(l_prev_total_combined > l_total_combined){
               size_type const l_diff = size_type(l_prev_total_combined - l_total_combined);
               move_data_backward(buf_beg-l_diff, l_diff, buf_end-l_diff, common_xbuf);
            }
            else if(l_prev_total_combined < l_total_combined){
               size_type const l_diff = size_type(l_total_combined - l_prev_total_combined);
               move_data_forward(buf_end, l_diff, buf_beg, common_xbuf);
            }
         }
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L2("   After move_data     : ", l_data + l_intbuf);
      }

      //Combine to form l_merged*2 segments
      if(n_keys){
         size_type upper_n_keys_this_iter = size_type(2u*l_merged/l_block);
         if(upper_n_keys_this_iter > 256){
            adaptive_sort_combine_blocks
               ( keys, comp, !use_internal_buf || is_merge_left ? first : first-l_block
               , l_data, l_merged, l_block, use_internal_buf, common_xbuf, xbuf, comp, is_merge_left);
         }
         else{
            unsigned char uint_keys[256];
            adaptive_sort_combine_blocks
               ( uint_keys, less(), !use_internal_buf || is_merge_left ? first : first-l_block
               , l_data, l_merged, l_block, use_internal_buf, common_xbuf, xbuf, comp, is_merge_left);
            }
      }
      else{
         size_type *const uint_keys = xbuf.template aligned_trailing<size_type>();
         adaptive_sort_combine_blocks
            ( uint_keys, less(), !use_internal_buf || is_merge_left ? first : first-l_block
            , l_data, l_merged, l_block, use_internal_buf, common_xbuf, xbuf, comp, is_merge_left);
      }

      BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1(is_merge_left ? "   After comb blocks L:  " : "   After comb blocks R:  ", l_data + l_intbuf);
      prev_merge_left = is_merge_left;
      l_prev_total_combined = l_total_combined;
      l_prev_block = l_block;
      prev_use_internal_buf = use_internal_buf;
   }
   BOOST_ASSERT(l_prev_total_combined == l_data);
   bool const buffer_right = prev_use_internal_buf && prev_merge_left;

   l_intbuf = prev_use_internal_buf ? l_prev_block : 0u;
   n_keys = size_type(l_unique - l_intbuf);
   //Restore data from to external common buffer if used
   if(common_xbuf){
      if(buffer_right){
         boost::move(xbuf.data(), xbuf.data() + l_intbuf, buffer+l_data);
      }
      else{
         boost::move(xbuf.data(), xbuf.data() + l_intbuf, buffer);
      }
   }
   return buffer_right;
}


template<class RandIt, class Compare, class XBuf>
void adaptive_sort_final_merge( bool buffer_right
                              , RandIt const first
                              , typename iter_size<RandIt>::type const l_intbuf
                              , typename iter_size<RandIt>::type const n_keys
                              , typename iter_size<RandIt>::type const len
                              , XBuf & xbuf
                              , Compare comp)
{
   //BOOST_ASSERT(n_keys || xbuf.size() == l_intbuf);
   xbuf.clear();

   typedef typename iter_size<RandIt>::type         size_type;

   size_type const n_key_plus_buf = size_type(l_intbuf+n_keys);
   if(buffer_right){
      //Use stable sort as some buffer elements might not be unique (see non_unique_buf)
      stable_sort(first+len-l_intbuf, first+len, comp, xbuf);
      stable_merge( first+n_keys, first+len-l_intbuf, first+len,    antistable<Compare>(comp), xbuf);
      unstable_sort(first, first+n_keys, comp, xbuf);
      stable_merge(first, first+n_keys, first+len, comp, xbuf);
   }
   else{
      //Use stable sort as some buffer elements might not be unique (see non_unique_buf)
      stable_sort(first, first+n_key_plus_buf, comp, xbuf);
      if(xbuf.capacity() >= n_key_plus_buf){
         buffered_merge(first, first+n_key_plus_buf, first+len, comp, xbuf);
      }
      else if(xbuf.capacity() >= min_value<size_type>(l_intbuf, n_keys)){
         stable_merge( first+n_keys, first+n_key_plus_buf
                     , first+len, comp, xbuf);
         stable_merge(first, first+n_keys, first+len, comp, xbuf);
      }
      else{
         stable_merge(first, first+n_key_plus_buf, first+len, comp, xbuf);
      }
   }
   BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("   After final_merge   : ", len);
}

template<class RandIt, class Compare, class Unsigned, class XBuf>
bool adaptive_sort_build_params
   (RandIt first, Unsigned const len, Compare comp
   , Unsigned &n_keys, Unsigned &l_intbuf, Unsigned &l_base, Unsigned &l_build_buf
   , XBuf & xbuf
   )
{
   typedef typename iter_size<RandIt>::type         size_type;

   //Calculate ideal parameters and try to collect needed unique keys
   l_base = 0u;

   //Try to find a value near sqrt(len) that is 2^N*l_base where
   //l_base <= AdaptiveSortInsertionSortThreshold. This property is important
   //as build_blocks merges to the left iteratively duplicating the
   //merged size and all the buffer must be used just before the final
   //merge to right step. This guarantees "build_blocks" produces 
   //segments of size l_build_buf*2, maximizing the classic merge phase.
   l_intbuf = size_type(ceil_sqrt_multiple(len, &l_base));

   //The internal buffer can be expanded if there is enough external memory
   while(xbuf.capacity() >= l_intbuf*2){
      l_intbuf = size_type(2u*l_intbuf);
   }

   //This is the minimum number of keys to implement the ideal algorithm
   //
   //l_intbuf is used as buffer plus the key count
   size_type n_min_ideal_keys = size_type(l_intbuf-1u);
   while(n_min_ideal_keys >= (len-l_intbuf-n_min_ideal_keys)/l_intbuf){
      --n_min_ideal_keys;
   }
   ++n_min_ideal_keys;
   BOOST_ASSERT(n_min_ideal_keys <= l_intbuf);

   if(xbuf.template supports_aligned_trailing<size_type>
         (l_intbuf, size_type((size_type(len-l_intbuf)-1u)/l_intbuf+1u))){
      n_keys = 0u;
      l_build_buf = l_intbuf;
   }
   else{
      //Try to achieve a l_build_buf of length l_intbuf*2, so that we can merge with that
      //l_intbuf*2 buffer in "build_blocks" and use half of them as buffer and the other half
      //as keys in combine_all_blocks. In that case n_keys >= n_min_ideal_keys but by a small margin.
      //
      //If available memory is 2*sqrt(l), then only sqrt(l) unique keys are needed,
      //(to be used for keys in combine_all_blocks) as the whole l_build_buf
      //will be backuped in the buffer during build_blocks.
      bool const non_unique_buf = xbuf.capacity() >= l_intbuf;
      size_type const to_collect = non_unique_buf ? n_min_ideal_keys : size_type(l_intbuf*2u);
      size_type collected = collect_unique(first, first+len, to_collect, comp, xbuf);

      //If available memory is 2*sqrt(l), then for "build_params" 
      //the situation is the same as if 2*l_intbuf were collected.
      if(non_unique_buf && collected == n_min_ideal_keys){
         l_build_buf = l_intbuf;
         n_keys = n_min_ideal_keys;
      }
      else if(collected == 2*l_intbuf){
         //l_intbuf*2 elements found. Use all of them in the build phase 
         l_build_buf = size_type(l_intbuf*2);
         n_keys = l_intbuf;
      }
      else if(collected >= (n_min_ideal_keys+l_intbuf)){ 
         l_build_buf = l_intbuf;
         n_keys = size_type(collected - l_intbuf);
      }
      //If collected keys are not enough, try to fix n_keys and l_intbuf. If no fix
      //is possible (due to very low unique keys), then go to a slow sort based on rotations.
      else{
         BOOST_ASSERT(collected < (n_min_ideal_keys+l_intbuf));
         if(collected < 4){  //No combination possible with less that 4 keys
            return false;
         }
         n_keys = l_intbuf;
         while(n_keys & (n_keys-1u)){
            n_keys &= size_type(n_keys-1u);  // make it power or 2
         }
         while(n_keys > collected){
            n_keys/=2;
         }
         //AdaptiveSortInsertionSortThreshold is always power of two so the minimum is power of two
         l_base = min_value<Unsigned>(n_keys, AdaptiveSortInsertionSortThreshold);
         l_intbuf = 0;
         l_build_buf = n_keys;
      }
      BOOST_ASSERT((n_keys+l_intbuf) >= l_build_buf);
   }

   return true;
}

// Main explanation of the sort algorithm.
//
// csqrtlen = ceil(sqrt(len));
//
// * First, 2*csqrtlen unique elements elements are extracted from elements to be
//   sorted and placed in the beginning of the range.
//
// * Step "build_blocks": In this nearly-classic merge step, 2*csqrtlen unique elements
//   will be used as auxiliary memory, so trailing len-2*csqrtlen elements are
//   are grouped in blocks of sorted 4*csqrtlen elements. At the end of the step
//   2*csqrtlen unique elements are again the leading elements of the whole range.
//
// * Step "combine_blocks": pairs of previously formed blocks are merged with a different
//   ("smart") algorithm to form blocks of 8*csqrtlen elements. This step is slower than the
//   "build_blocks" step and repeated iteratively (forming blocks of 16*csqrtlen, 32*csqrtlen
//   elements, etc) of until all trailing (len-2*csqrtlen) elements are merged.
//
//   In "combine_blocks" len/csqrtlen elements used are as "keys" (markers) to
//   know if elements belong to the first or second block to be merged and another 
//   leading csqrtlen elements are used as buffer. Explanation of the "combine_blocks" step:
//
//   Iteratively until all trailing (len-2*csqrtlen) elements are merged:
//      Iteratively for each pair of previously merged block:
//         * Blocks are divided groups of csqrtlen elements and
//           2*merged_block/csqrtlen keys are sorted to be used as markers
//         * Groups are selection-sorted by first or last element (depending whether they are going
//           to be merged to left or right) and keys are reordered accordingly as an imitation-buffer.
//         * Elements of each block pair are merged using the csqrtlen buffer taking into account
//           if they belong to the first half or second half (marked by the key).
//
// * In the final merge step leading elements (2*csqrtlen) are sorted and merged with
//   rotations with the rest of sorted elements in the "combine_blocks" step.
//
// Corner cases:
//
// * If no 2*csqrtlen elements can be extracted:
//
//    * If csqrtlen+len/csqrtlen are extracted, then only csqrtlen elements are used
//      as buffer in the "build_blocks" step forming blocks of 2*csqrtlen elements. This
//      means that an additional "combine_blocks" step will be needed to merge all elements.
//    
//    * If no csqrtlen+len/csqrtlen elements can be extracted, but still more than a minimum,
//      then reduces the number of elements used as buffer and keys in the "build_blocks"
//      and "combine_blocks" steps. If "combine_blocks" has no enough keys due to this reduction
//      then uses a rotation based smart merge.
//
//    * If the minimum number of keys can't be extracted, a rotation-based sorting is performed.
//
// * If auxiliary memory is more or equal than ceil(len/2), half-copying mergesort is used.
//
// * If auxiliary memory is more than csqrtlen+n_keys*sizeof(std::size_t),
//   then only csqrtlen elements need to be extracted and "combine_blocks" will use integral
//   keys to combine blocks.
//
// * If auxiliary memory is available, the "build_blocks" will be extended to build bigger blocks
//   using classic merge and "combine_blocks" will use bigger blocks when merging.
template<class RandIt, class Compare, class XBuf>
void adaptive_sort_impl
   ( RandIt first
   , typename iter_size<RandIt>::type const len
   , Compare comp
   , XBuf & xbuf
   )
{
   typedef typename iter_size<RandIt>::type         size_type;

   //Small sorts go directly to insertion sort
   if(len <= size_type(AdaptiveSortInsertionSortThreshold)){
      insertion_sort(first, first + len, comp);
   }
   else if((len-len/2) <= xbuf.capacity()){
      merge_sort(first, first+len, comp, xbuf.data());
   }
   else{
      //Make sure it is at least four
      BOOST_STATIC_ASSERT(AdaptiveSortInsertionSortThreshold >= 4);

      size_type l_base = 0;
      size_type l_intbuf = 0;
      size_type n_keys = 0;
      size_type l_build_buf = 0;

      //Calculate and extract needed unique elements. If a minimum is not achieved
      //fallback to a slow stable sort
      if(!adaptive_sort_build_params(first, len, comp, n_keys, l_intbuf, l_base, l_build_buf, xbuf)){
         stable_sort(first, first+len, comp, xbuf);
      }
      else{
         BOOST_ASSERT(l_build_buf);
         //Otherwise, continue the adaptive_sort
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("\n   After collect_unique: ", len);
         size_type const n_key_plus_buf = size_type(l_intbuf+n_keys);
         //l_build_buf is always power of two if l_intbuf is zero
         BOOST_ASSERT(l_intbuf || (0 == (l_build_buf & (l_build_buf-1))));

         //Classic merge sort until internal buffer and xbuf are exhausted
         size_type const l_merged = adaptive_sort_build_blocks
            ( first + n_key_plus_buf-l_build_buf
            , size_type(len-n_key_plus_buf+l_build_buf)
            , l_base, l_build_buf, xbuf, comp);
         BOOST_MOVE_ADAPTIVE_SORT_PRINT_L1("   After build_blocks:   ", len);

         //Non-trivial merge
         bool const buffer_right = adaptive_sort_combine_all_blocks
            (first, n_keys, first+n_keys, size_type(len-n_keys), l_merged, l_intbuf, xbuf, comp);

         //Sort keys and buffer and merge the whole sequence
         adaptive_sort_final_merge(buffer_right, first, l_intbuf, n_keys, len, xbuf, comp);
      }
   }
}

}  //namespace detail_adaptive {

///@endcond

//! <b>Effects</b>: Sorts the elements in the range [first, last) in ascending order according
//!   to comparison functor "comp". The sort is stable (order of equal elements
//!   is guaranteed to be preserved). Performance is improved if additional raw storage is
//!   provided.
//!
//! <b>Requires</b>:
//!   - RandIt must meet the requirements of ValueSwappable and RandomAccessIterator.
//!   - The type of dereferenced RandIt must meet the requirements of MoveAssignable and MoveConstructible.
//!
//! <b>Parameters</b>:
//!   - first, last: the range of elements to sort
//!   - comp: comparison function object which returns true if the first argument is is ordered before the second.
//!   - uninitialized, uninitialized_len: raw storage starting on "uninitialized", able to hold "uninitialized_len"
//!      elements of type iterator_traits<RandIt>::value_type. Maximum performance is achieved when uninitialized_len
//!      is ceil(std::distance(first, last)/2).
//!
//! <b>Throws</b>: If comp throws or the move constructor, move assignment or swap of the type
//!   of dereferenced RandIt throws.
//!
//! <b>Complexity</b>: Always K x O(Nxlog(N)) comparisons and move assignments/constructors/swaps.
//!   Comparisons are close to minimum even with no additional memory. Constant factor for data movement is minimized
//!   when uninitialized_len is ceil(std::distance(first, last)/2). Pretty good enough performance is achieved when
//!   ceil(sqrt(std::distance(first, last)))*2.
//!
//! <b>Caution</b>: Experimental implementation, not production-ready.
template<class RandIt, class RandRawIt, class Compare>
void adaptive_sort( RandIt first, RandIt last, Compare comp
               , RandRawIt uninitialized
               , typename iter_size<RandIt>::type uninitialized_len)
{
   typedef typename iter_size<RandIt>::type  size_type;
   typedef typename iterator_traits<RandIt>::value_type value_type;

   ::boost::movelib::adaptive_xbuf<value_type, RandRawIt, size_type> xbuf(uninitialized, uninitialized_len);
   ::boost::movelib::detail_adaptive::adaptive_sort_impl(first, size_type(last - first), comp, xbuf);
}

template<class RandIt, class Compare>
void adaptive_sort( RandIt first, RandIt last, Compare comp)
{
   typedef typename iterator_traits<RandIt>::value_type value_type;
   adaptive_sort(first, last, comp, (value_type*)0, 0u);
}

}  //namespace movelib {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#endif   //#define BOOST_MOVE_ADAPTIVE_SORT_HPP

/* adaptive_sort.hpp
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
*/