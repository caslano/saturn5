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
            block_ctrl *second =  reinterpret_cast<block_ctrl *>
               (reinterpret_cast<char*>(first) + Alignment*first_min_units);
            first->m_size  = first_min_units;
            second->m_size = old_size - first->m_size;
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
      first->m_size  = (size_type)(reinterpret_cast<char*>(second) - reinterpret_cast<char*>(first))/Alignment;
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
         second->m_size = second_min_units;
         third->m_size  = old_size - first->m_size - second->m_size;
         BOOST_ASSERT(third->m_size >= MinBlockUnits);
         memory_algo->priv_mark_new_allocated_block(second);
         memory_algo->priv_mark_new_allocated_block(third);
         memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(third));
      }
      else{
         second->m_size = old_size - first->m_size;
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
      block->m_size = (received_size-UsableByPreviousChunk)/Alignment + AllocatedCtrlUnits;
      BOOST_ASSERT(block->m_size >= BlockCtrlUnits);

      //We create the new block
      block_ctrl *new_block = reinterpret_cast<block_ctrl*>
                  (reinterpret_cast<char*>(block) + block->m_size*Alignment);
      //Write control data to simulate this new block was previously allocated
      //and deallocate it
      new_block->m_size = old_block_units - block->m_size;
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
               block_ctrl *new_block = reinterpret_cast<block_ctrl *>(block_address);
               assert_alignment(new_block);

               //The last block should take all the remaining space
               if((low_idx + 1) == n_elements ||
                  (total_used_units + elem_units +
                  ((!sizeof_element)
                     ? elem_units
               : max_value(memory_algo->priv_get_total_units(elem_sizes[low_idx+1]*sizeof_element), ptr_size_units))
                   > received_units)){
                  //By default, the new block will use the rest of the buffer
                  new_block->m_size = received_units - total_used_units;
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
                  new_block->m_size = elem_units;
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