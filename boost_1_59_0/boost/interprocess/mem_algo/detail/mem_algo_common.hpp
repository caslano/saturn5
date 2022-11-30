//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MEM_ALGO_COMMON_HPP
#define BOOST_INTERPROCESS_DETAIL_MEM_ALGO_COMMON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/containers/allocation_type.hpp>
// interprocess/detail
#include <boost/interprocess/detail/math_functions.hpp>
#include <boost/interprocess/detail/min_max.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/utilities.hpp>
// container/detail
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/container/detail/placement_new.hpp>
// move
#include <boost/move/utility_core.hpp>
// move/detail
#include <boost/move/detail/force_ptr.hpp>
// other boost
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

//!\file
//!Implements common operations for memory algorithms.

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class VoidPointer>
class basic_multiallocation_chain
   : public boost::container::dtl::
      basic_multiallocation_chain<VoidPointer>
{
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_multiallocation_chain)
   typedef boost::container::dtl::
      basic_multiallocation_chain<VoidPointer> base_t;
   public:

   basic_multiallocation_chain()
      :  base_t()
   {}

   basic_multiallocation_chain(BOOST_RV_REF(basic_multiallocation_chain) other)
      :  base_t(::boost::move(static_cast<base_t&>(other)))
   {}

   basic_multiallocation_chain& operator=(BOOST_RV_REF(basic_multiallocation_chain) other)
   {
      this->base_t::operator=(::boost::move(static_cast<base_t&>(other)));
      return *this;
   }

   void *pop_front()
   {
      return boost::interprocess::ipcdetail::to_raw_pointer(this->base_t::pop_front());
   }
};


//!This class implements several allocation functions shared by different algorithms
//!(aligned allocation, multiple allocation...).
template<class MemoryAlgorithm>
class memory_algorithm_common
{
   public:
   typedef typename MemoryAlgorithm::void_pointer              void_pointer;
   typedef typename MemoryAlgorithm::block_ctrl                block_ctrl;
   typedef typename MemoryAlgorithm::multiallocation_chain     multiallocation_chain;
   typedef memory_algorithm_common<MemoryAlgorithm>            this_type;
   typedef typename MemoryAlgorithm::size_type                 size_type;

   static const size_type Alignment              = MemoryAlgorithm::Alignment;
   static const size_type MinBlockUnits          = MemoryAlgorithm::MinBlockUnits;
   static const size_type AllocatedCtrlBytes     = MemoryAlgorithm::AllocatedCtrlBytes;
   static const size_type AllocatedCtrlUnits     = MemoryAlgorithm::AllocatedCtrlUnits;
   static const size_type BlockCtrlBytes         = MemoryAlgorithm::BlockCtrlBytes;
   static const size_type BlockCtrlUnits         = MemoryAlgorithm::BlockCtrlUnits;
   static const size_type UsableByPreviousChunk  = MemoryAlgorithm::UsableByPreviousChunk;

   static void assert_alignment(const void *ptr)
   {  assert_alignment((std::size_t)ptr); }

   static void assert_alignment(size_type uint_ptr)
   {
      (void)uint_ptr;
      BOOST_ASSERT(uint_ptr % Alignment == 0);
   }

   static bool check_alignment(const void *ptr)
   {  return (((std::size_t)ptr) % Alignment == 0);   }

   static size_type ceil_units(size_type size)
   {  return get_rounded_size(size, Alignment)/Alignment; }

   static size_type floor_units(size_type size)
   {  return size/Alignment;  }

   static size_type multiple_of_units(size_type size)
   {  return get_rounded_size(size, Alignment);  }

   static void allocate_many
      (MemoryAlgorithm *memory_algo, size_type elem_bytes, size_type n_elements, multiallocation_chain &chain)
   {
      return this_type::priv_allocate_many(memory_algo, &elem_bytes, n_elements, 0, chain);
   }

   static void deallocate_many(MemoryAlgorithm *memory_algo, multiallocation_chain &chain)
   {
      return this_type::priv_deallocate_many(memory_algo, chain);
   }

   static bool calculate_lcm_and_needs_backwards_lcmed
      (size_type backwards_multiple, size_type received_size, size_type size_to_achieve,
      size_type &lcm_out, size_type &needs_backwards_lcmed_out)
   {
      // Now calculate lcm_val
      size_type max = backwards_multiple;
      size_type min = Alignment;
      size_type needs_backwards;
      size_type needs_backwards_lcmed;
      size_type lcm_val;
      size_type current_forward;
      //Swap if necessary
      if(max < min){
         size_type tmp = min;
         min = max;
         max = tmp;
      }
      //Check if it's power of two
      if((backwards_multiple & (backwards_multiple-1)) == 0){
         if(0 != (size_to_achieve & ((backwards_multiple-1)))){
            return false;
         }

         lcm_val = max;
         //If we want to use minbytes data to get a buffer between maxbytes
         //and minbytes if maxbytes can't be achieved, calculate the
         //biggest of all possibilities
         current_forward = get_truncated_size_po2(received_size, backwards_multiple);
         needs_backwards = size_to_achieve - current_forward;
         BOOST_ASSERT((needs_backwards % backwards_multiple) == 0);
         needs_backwards_lcmed = get_rounded_size_po2(needs_backwards, lcm_val);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      //Check if it's multiple of alignment
      else if((backwards_multiple & (Alignment - 1u)) == 0){
         lcm_val = backwards_multiple;
         current_forward = get_truncated_size(received_size, backwards_multiple);
         //No need to round needs_backwards because backwards_multiple == lcm_val
         needs_backwards_lcmed = needs_backwards = size_to_achieve - current_forward;
         BOOST_ASSERT((needs_backwards_lcmed & (Alignment - 1u)) == 0);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      //Check if it's multiple of the half of the alignmment
      else if((backwards_multiple & ((Alignment/2u) - 1u)) == 0){
         lcm_val = backwards_multiple*2u;
         current_forward = get_truncated_size(received_size, backwards_multiple);
         needs_backwards_lcmed = needs_backwards = size_to_achieve - current_forward;
         if(0 != (needs_backwards_lcmed & (Alignment-1)))
         //while(0 != (needs_backwards_lcmed & (Alignment-1)))
            needs_backwards_lcmed += backwards_multiple;
         BOOST_ASSERT((needs_backwards_lcmed % lcm_val) == 0);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      //Check if it's multiple of the quarter of the alignmment
      else if((backwards_multiple & ((Alignment/4u) - 1u)) == 0){
         size_type remainder;
         lcm_val = backwards_multiple*4u;
         current_forward = get_truncated_size(received_size, backwards_multiple);
         needs_backwards_lcmed = needs_backwards = size_to_achieve - current_forward;
         //while(0 != (needs_backwards_lcmed & (Alignment-1)))
            //needs_backwards_lcmed += backwards_multiple;
         if(0 != (remainder = ((needs_backwards_lcmed & (Alignment-1))>>(Alignment/8u)))){
            if(backwards_multiple & Alignment/2u){
               needs_backwards_lcmed += (remainder)*backwards_multiple;
            }
            else{
               needs_backwards_lcmed += (4-remainder)*backwards_multiple;
            }
         }
         BOOST_ASSERT((needs_backwards_lcmed % lcm_val) == 0);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      else{
         lcm_val = lcm(max, min);
      }
      //If we want to use minbytes data to get a buffer between maxbytes
      //and minbytes if maxbytes can't be achieved, calculate the
      //biggest of all possibilities
      current_forward = get_truncated_size(received_size, backwards_multiple);
      needs_backwards = size_to_achieve - current_forward;
      BOOST_ASSERT((needs_backwards % backwards_multiple) == 0);
      needs_backwards_lcmed = get_rounded_size(needs_backwards, lcm_val);
      lcm_out = lcm_val;
      needs_backwards_lcmed_out = needs_backwards_lcmed;
      return true;
   }

   static void allocate_many
      ( MemoryAlgorithm *memory_algo
      , const size_type *elem_sizes
      , size_type n_elements
      , size_type sizeof_element
      , multiallocation_chain &chain)
   {
      this_type::priv_allocate_many(memory_algo, elem_sizes, n_elements, sizeof_element, chain);
   }

   static void* allocate_aligned
      (MemoryAlgorithm *memory_algo, size_type nbytes, size_type alignment)
   {

      //Ensure power of 2
      if ((alignment & (alignment - size_type(1u))) != 0){
         //Alignment is not power of two
         BOOST_ASSERT((alignment & (alignment - size_type(1u))) == 0);
         return 0;
      }

      size_type real_size = nbytes;
      if(alignment <= Alignment){
         void *ignore_reuse = 0;
         return memory_algo->priv_allocate
            (boost::interprocess::allocate_new, nbytes, real_size, ignore_reuse);
      }

      if(nbytes > UsableByPreviousChunk)
         nbytes -= UsableByPreviousChunk;

      //We can find a aligned portion if we allocate a block that has alignment
      //nbytes + alignment bytes or more.
      size_type minimum_allocation = max_value
         (nbytes + alignment, size_type(MinBlockUnits*Alignment));
      //Since we will split that block, we must request a bit more memory
      //if the alignment is near the beginning of the buffer, because otherwise,
      //there is no space for a new block before the alignment.
      //
      //            ____ Aligned here
      //           |
      //  -----------------------------------------------------
      // | MBU |
      //  -----------------------------------------------------
      size_type request =
         minimum_allocation + (2*MinBlockUnits*Alignment - AllocatedCtrlBytes
         //prevsize - UsableByPreviousChunk
         );

      //Now allocate the buffer
      real_size = request;
      void *ignore_reuse = 0;
      void *buffer = memory_algo->priv_allocate(boost::interprocess::allocate_new, request, real_size, ignore_reuse);
      if(!buffer){
         return 0;
      }
      else if ((((std::size_t)(buffer)) % alignment) == 0){
         //If we are lucky and the buffer is aligned, just split it and
         //return the high part
         block_ctrl *first  = memory_algo->priv_get_block(buffer);
         size_type old_size = first->m_size;
         const size_type first_min_units =
            max_value(ceil_units(nbytes) + AllocatedCtrlUnits, size_type(MinBlockUnits));
         //We can create a new block in the end of the segment
         if(old_size >= (first_min_units + MinBlockUnits)){
            block_ctrl *second =  move_detail::force_ptr<block_ctrl*>
               (reinterpret_cast<char*>(first) + Alignment*first_min_units);
            first->m_size  = first_min_units & block_ctrl::size_mask;
            second->m_size = (old_size - first->m_size) & block_ctrl::size_mask;
            BOOST_ASSERT(second->m_size >= MinBlockUnits);
            memory_algo->priv_mark_new_allocated_block(first);
            memory_algo->priv_mark_new_allocated_block(second);
            memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(second));
         }
         return buffer;
      }

      //Buffer not aligned, find the aligned part.
      //
      //                    ____ Aligned here
      //                   |
      //  -----------------------------------------------------
      // | MBU +more | ACB |
      //  -----------------------------------------------------
      char *pos = reinterpret_cast<char*>
         (reinterpret_cast<std::size_t>(static_cast<char*>(buffer) +
            //This is the minimum size of (2)
            (MinBlockUnits*Alignment - AllocatedCtrlBytes) +
            //This is the next MBU for the aligned memory
            AllocatedCtrlBytes +
            //This is the alignment trick
            alignment - 1) & -alignment);

      //Now obtain the address of the blocks
      block_ctrl *first  = memory_algo->priv_get_block(buffer);
      block_ctrl *second = memory_algo->priv_get_block(pos);
      BOOST_ASSERT(pos <= (reinterpret_cast<char*>(first) + first->m_size*Alignment));
      BOOST_ASSERT(first->m_size >= 2*MinBlockUnits);
      BOOST_ASSERT((pos + MinBlockUnits*Alignment - AllocatedCtrlBytes + nbytes*Alignment/Alignment) <=
             (reinterpret_cast<char*>(first) + first->m_size*Alignment));
      //Set the new size of the first block
      size_type old_size = first->m_size;
      first->m_size = size_type(size_type(reinterpret_cast<char*>(second) - reinterpret_cast<char*>(first))/Alignment
                        & block_ctrl::size_mask);
      memory_algo->priv_mark_new_allocated_block(first);

      //Now check if we can create a new buffer in the end
      //
      //              __"second" block
      //             |      __Aligned here
      //             |     |      __"third" block
      //  -----------|-----|-----|------------------------------
      // | MBU +more | ACB | (3) | BCU |
      //  -----------------------------------------------------
      //This size will be the minimum size to be able to create a
      //new block in the end.
      const size_type second_min_units = max_value(size_type(MinBlockUnits),
                        ceil_units(nbytes) + AllocatedCtrlUnits );

      //Check if we can create a new block (of size MinBlockUnits) in the end of the segment
      if((old_size - first->m_size) >= (second_min_units + MinBlockUnits)){
         //Now obtain the address of the end block
         block_ctrl *third = new (reinterpret_cast<char*>(second) + Alignment*second_min_units)block_ctrl;
         second->m_size = second_min_units & block_ctrl::size_mask;
         third->m_size  = (old_size - first->m_size - second->m_size) & block_ctrl::size_mask;
         BOOST_ASSERT(third->m_size >= MinBlockUnits);
         memory_algo->priv_mark_new_allocated_block(second);
         memory_algo->priv_mark_new_allocated_block(third);
         memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(third));
      }
      else{
         second->m_size = (old_size - first->m_size) & block_ctrl::size_mask;
         BOOST_ASSERT(second->m_size >= MinBlockUnits);
         memory_algo->priv_mark_new_allocated_block(second);
      }

      memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(first));
      return memory_algo->priv_get_user_buffer(second);
   }

   static bool try_shrink
      (MemoryAlgorithm *memory_algo, void *ptr
      ,const size_type max_size, size_type &received_size)
   {
      size_type const preferred_size = received_size;
      (void)memory_algo;
      //Obtain the real block
      block_ctrl *block = memory_algo->priv_get_block(ptr);
      size_type old_block_units = (size_type)block->m_size;

      //The block must be marked as allocated
      BOOST_ASSERT(memory_algo->priv_is_allocated_block(block));

      //Check if alignment and block size are right
      assert_alignment(ptr);

      //Put this to a safe value
      received_size = (old_block_units - AllocatedCtrlUnits)*Alignment + UsableByPreviousChunk;

      //Now translate it to Alignment units
      const size_type max_user_units       = floor_units(max_size - UsableByPreviousChunk);
      const size_type preferred_user_units = ceil_units(preferred_size - UsableByPreviousChunk);

      //Check if rounded max and preferred are possible correct
      if(max_user_units < preferred_user_units)
         return false;

      //Check if the block is smaller than the requested minimum
      size_type old_user_units = old_block_units - AllocatedCtrlUnits;

      if(old_user_units < preferred_user_units)
         return false;

      //If the block is smaller than the requested minimum
      if(old_user_units == preferred_user_units)
         return true;

      size_type shrunk_user_units =
         ((BlockCtrlUnits - AllocatedCtrlUnits) >= preferred_user_units)
         ? (BlockCtrlUnits - AllocatedCtrlUnits)
         : preferred_user_units;

      //Some parameter checks
      if(max_user_units < shrunk_user_units)
         return false;

      //We must be able to create at least a new empty block
      if((old_user_units - shrunk_user_units) < BlockCtrlUnits ){
         return false;
      }

      //Update new size
      received_size = shrunk_user_units*Alignment + UsableByPreviousChunk;
      return true;
   }

   static bool shrink
      (MemoryAlgorithm *memory_algo, void *ptr
      ,const size_type max_size, size_type &received_size)
   {
      size_type const preferred_size = received_size;
      //Obtain the real block
      block_ctrl *block = memory_algo->priv_get_block(ptr);
      size_type old_block_units = (size_type)block->m_size;

      if(!try_shrink(memory_algo, ptr, max_size, received_size)){
         return false;
      }

      //Check if the old size was just the shrunk size (no splitting)
      if((old_block_units - AllocatedCtrlUnits) == ceil_units(preferred_size - UsableByPreviousChunk))
         return true;

      //Now we can just rewrite the size of the old buffer
      block->m_size = ((received_size-UsableByPreviousChunk)/Alignment + AllocatedCtrlUnits) & block_ctrl::size_mask;
      BOOST_ASSERT(block->m_size >= BlockCtrlUnits);

      //We create the new block
      block_ctrl *new_block = move_detail::force_ptr<block_ctrl*>
                  (reinterpret_cast<char*>(block) + block->m_size*Alignment);
      //Write control data to simulate this new block was previously allocated
      //and deallocate it
      new_block->m_size = (old_block_units - block->m_size) & block_ctrl::size_mask;
      BOOST_ASSERT(new_block->m_size >= BlockCtrlUnits);
      memory_algo->priv_mark_new_allocated_block(block);
      memory_algo->priv_mark_new_allocated_block(new_block);
      memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(new_block));
      return true;
   }

   private:
   static void priv_allocate_many
      ( MemoryAlgorithm *memory_algo
      , const size_type *elem_sizes
      , size_type n_elements
      , size_type sizeof_element
      , multiallocation_chain &chain)
   {
      //Note: sizeof_element == 0 indicates that we want to
      //allocate n_elements of the same size "*elem_sizes"

      //Calculate the total size of all requests
      size_type total_request_units = 0;
      size_type elem_units = 0;
      const size_type ptr_size_units = memory_algo->priv_get_total_units(sizeof(void_pointer));
      if(!sizeof_element){
         elem_units = memory_algo->priv_get_total_units(*elem_sizes);
         elem_units = ptr_size_units > elem_units ? ptr_size_units : elem_units;
         total_request_units = n_elements*elem_units;
      }
      else{
         for(size_type i = 0; i < n_elements; ++i){
            if(multiplication_overflows(elem_sizes[i], sizeof_element)){
               total_request_units = 0;
               break;
            }
            elem_units = memory_algo->priv_get_total_units(elem_sizes[i]*sizeof_element);
            elem_units = ptr_size_units > elem_units ? ptr_size_units : elem_units;
            if(sum_overflows(total_request_units, elem_units)){
               total_request_units = 0;
               break;
            }
            total_request_units += elem_units;
         }
      }

      if(total_request_units && !multiplication_overflows(total_request_units, Alignment)){
         size_type low_idx = 0;
         while(low_idx < n_elements){
            size_type total_bytes = total_request_units*Alignment - AllocatedCtrlBytes + UsableByPreviousChunk;
            size_type min_allocation = (!sizeof_element)
               ?  elem_units
               :  memory_algo->priv_get_total_units(elem_sizes[low_idx]*sizeof_element);
            min_allocation = min_allocation*Alignment - AllocatedCtrlBytes + UsableByPreviousChunk;

            size_type received_size = total_bytes;
            void *ignore_reuse = 0;
            void *ret = memory_algo->priv_allocate
               (boost::interprocess::allocate_new, min_allocation, received_size, ignore_reuse);
            if(!ret){
               break;
            }

            block_ctrl *block = memory_algo->priv_get_block(ret);
            size_type received_units = (size_type)block->m_size;
            char *block_address = reinterpret_cast<char*>(block);

            size_type total_used_units = 0;
            while(total_used_units < received_units){
               if(sizeof_element){
                  elem_units = memory_algo->priv_get_total_units(elem_sizes[low_idx]*sizeof_element);
                  elem_units = ptr_size_units > elem_units ? ptr_size_units : elem_units;
               }
               if(total_used_units + elem_units > received_units)
                  break;
               total_request_units -= elem_units;
               //This is the position where the new block must be created
               block_ctrl *new_block = move_detail::force_ptr<block_ctrl*>(block_address);
               assert_alignment(new_block);

               //The last block should take all the remaining space
               if((low_idx + 1) == n_elements ||
                  (total_used_units + elem_units +
                  ((!sizeof_element)
                     ? elem_units
               : max_value(memory_algo->priv_get_total_units(elem_sizes[low_idx+1]*sizeof_element), ptr_size_units))
                   > received_units)){
                  //By default, the new block will use the rest of the buffer
                  new_block->m_size = (received_units - total_used_units) & block_ctrl::size_mask;
                  memory_algo->priv_mark_new_allocated_block(new_block);

                  //If the remaining units are bigger than needed and we can
                  //split it obtaining a new free memory block do it.
                  if((received_units - total_used_units) >= (elem_units + MemoryAlgorithm::BlockCtrlUnits)){
                     size_type shrunk_request = elem_units*Alignment - AllocatedCtrlBytes + UsableByPreviousChunk;
                     size_type shrunk_received = shrunk_request;
                     bool shrink_ok = shrink
                           (memory_algo
                           ,memory_algo->priv_get_user_buffer(new_block)
                           ,shrunk_request
                           ,shrunk_received);
                     (void)shrink_ok;
                     //Shrink must always succeed with passed parameters
                     BOOST_ASSERT(shrink_ok);
                     //Some sanity checks
                     BOOST_ASSERT(shrunk_request == shrunk_received);
                     BOOST_ASSERT(elem_units == ((shrunk_request-UsableByPreviousChunk)/Alignment + AllocatedCtrlUnits));
                     //"new_block->m_size" must have been reduced to elem_units by "shrink"
                     BOOST_ASSERT(new_block->m_size == elem_units);
                     //Now update the total received units with the reduction
                     received_units = elem_units + total_used_units;
                  }
               }
               else{
                  new_block->m_size = elem_units & block_ctrl::size_mask;
                  memory_algo->priv_mark_new_allocated_block(new_block);
               }

               block_address += new_block->m_size*Alignment;
               total_used_units += (size_type)new_block->m_size;
               //Check we have enough room to overwrite the intrusive pointer
               BOOST_ASSERT((new_block->m_size*Alignment - AllocatedCtrlUnits) >= sizeof(void_pointer));
               void_pointer p = ::new(memory_algo->priv_get_user_buffer(new_block), boost_container_new_t())void_pointer(0);
               chain.push_back(p);
               ++low_idx;
            }
            //Sanity check
            BOOST_ASSERT(total_used_units == received_units);
         }

         if(low_idx != n_elements){
            priv_deallocate_many(memory_algo, chain);
         }
      }
   }

   static void priv_deallocate_many(MemoryAlgorithm *memory_algo, multiallocation_chain &chain)
   {
      while(!chain.empty()){
         memory_algo->priv_deallocate(to_raw_pointer(chain.pop_front()));
      }
   }
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MEM_ALGO_COMMON_HPP

/* mem_algo_common.hpp
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
*/