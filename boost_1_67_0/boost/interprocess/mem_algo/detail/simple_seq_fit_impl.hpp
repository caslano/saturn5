//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MEM_ALGO_DETAIL_SIMPLE_SEQ_FIT_IMPL_HPP
#define BOOST_INTERPROCESS_MEM_ALGO_DETAIL_SIMPLE_SEQ_FIT_IMPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/pointer_traits.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/containers/allocation_type.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/min_max.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/interprocess/mem_algo/detail/mem_algo_common.hpp>
#include <boost/move/detail/type_traits.hpp> //make_unsigned, alignment_of
#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <cstring>
#include <boost/assert.hpp>

//!\file
//!Describes sequential fit algorithm used to allocate objects in shared memory.
//!This class is intended as a base class for single segment and multi-segment
//!implementations.

namespace boost {
namespace interprocess {
namespace ipcdetail {

//!This class implements the simple sequential fit algorithm with a simply
//!linked list of free buffers.
//!This class is intended as a base class for single segment and multi-segment
//!implementations.
template<class MutexFamily, class VoidPointer>
class simple_seq_fit_impl
{
   //Non-copyable
   simple_seq_fit_impl();
   simple_seq_fit_impl(const simple_seq_fit_impl &);
   simple_seq_fit_impl &operator=(const simple_seq_fit_impl &);

   typedef typename boost::intrusive::
      pointer_traits<VoidPointer>::template
         rebind_pointer<char>::type                         char_ptr;

   public:

   //!Shared interprocess_mutex family used for the rest of the Interprocess framework
   typedef MutexFamily        mutex_family;
   //!Pointer type to be used with the rest of the Interprocess framework
   typedef VoidPointer        void_pointer;
   typedef boost::container::dtl::
      basic_multiallocation_chain<VoidPointer>     multiallocation_chain;

   typedef typename boost::intrusive::pointer_traits<char_ptr>::difference_type difference_type;
   typedef typename boost::container::dtl::make_unsigned<difference_type>::type size_type;


   private:
   class block_ctrl;
   friend class block_ctrl;

   typedef typename boost::intrusive::
      pointer_traits<VoidPointer>::template
         rebind_pointer<block_ctrl>::type                   block_ctrl_ptr;

   //!Block control structure
   class block_ctrl
   {
      public:
      //!Offset pointer to the next block.
      block_ctrl_ptr m_next;
      //!This block's memory size (including block_ctrl
      //!header) in BasicSize units
      size_type    m_size;

      size_type get_user_bytes() const
      {  return this->m_size*Alignment - BlockCtrlBytes; }

      size_type get_total_bytes() const
      {  return this->m_size*Alignment; }
   };

   //!Shared interprocess_mutex to protect memory allocate/deallocate
   typedef typename MutexFamily::mutex_type        interprocess_mutex;

   //!This struct includes needed data and derives from
   //!interprocess_mutex to allow EBO when using null interprocess_mutex
   struct header_t : public interprocess_mutex
   {
      //!Pointer to the first free block
      block_ctrl        m_root;
      //!Allocated bytes for internal checking
      size_type         m_allocated;
      //!The size of the memory segment
      size_type         m_size;
      //!The extra size required by the segment
      size_type         m_extra_hdr_bytes;
   }  m_header;

   friend class ipcdetail::memory_algorithm_common<simple_seq_fit_impl>;

   typedef ipcdetail::memory_algorithm_common<simple_seq_fit_impl> algo_impl_t;

   public:
   //!Constructor. "size" is the total size of the managed memory segment,
   //!"extra_hdr_bytes" indicates the extra bytes beginning in the sizeof(simple_seq_fit_impl)
   //!offset that the allocator should not use at all.
   simple_seq_fit_impl           (size_type size, size_type extra_hdr_bytes);

   //!Destructor
   ~simple_seq_fit_impl();

   //!Obtains the minimum size needed by the algorithm
   static size_type get_min_size (size_type extra_hdr_bytes);

   //Functions for single segment management

   //!Allocates bytes, returns 0 if there is not more memory
   void* allocate             (size_type nbytes);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Multiple element allocation, same size
   void allocate_many(size_type elem_bytes, size_type num_elements, multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
      //-----------------------
      algo_impl_t::allocate_many(this, elem_bytes, num_elements, chain);
   }

   //!Multiple element allocation, different size
   void allocate_many(const size_type *elem_sizes, size_type n_elements, size_type sizeof_element, multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
      //-----------------------
      algo_impl_t::allocate_many(this, elem_sizes, n_elements, sizeof_element, chain);
   }

   //!Multiple element deallocation
   void deallocate_many(multiallocation_chain &chain);

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //!Deallocates previously allocated bytes
   void   deallocate          (void *addr);

   //!Returns the size of the memory segment
   size_type get_size()  const;

   //!Returns the number of free bytes of the memory segment
   size_type get_free_memory()  const;

   //!Increases managed memory in extra_size bytes more
   void grow(size_type extra_size);

   //!Decreases managed memory as much as possible
   void shrink_to_fit();

   //!Returns true if all allocated memory has been deallocated
   bool all_memory_deallocated();

   //!Makes an internal sanity check and returns true if success
   bool check_sanity();

   //!Initializes to zero all the memory that's not in use.
   //!This function is normally used for security reasons.
   void zero_free_memory();

   template<class T>
   T *allocation_command  (boost::interprocess::allocation_type command,   size_type limit_size,
                           size_type &prefer_in_recvd_out_size, T *&reuse);

   void * raw_allocation_command  (boost::interprocess::allocation_type command,   size_type limit_size,
                               size_type &prefer_in_recvd_out_size, void *&reuse_ptr, size_type sizeof_object = 1);

   //!Returns the size of the buffer previously allocated pointed by ptr
   size_type size(const void *ptr) const;

   //!Allocates aligned bytes, returns 0 if there is not more memory.
   //!Alignment must be power of 2
   void* allocate_aligned     (size_type nbytes, size_type alignment);

   private:

   //!Obtains the pointer returned to the user from the block control
   static void *priv_get_user_buffer(const block_ctrl *block);

   //!Obtains the block control structure of the user buffer
   static block_ctrl *priv_get_block(const void *ptr);

   //!Real allocation algorithm with min allocation option
   void * priv_allocate(boost::interprocess::allocation_type command
                        ,size_type min_size
                        ,size_type &prefer_in_recvd_out_size, void *&reuse_ptr);

   void * priv_allocation_command(boost::interprocess::allocation_type command
                                 ,size_type min_size
                                 ,size_type &prefer_in_recvd_out_size
                                 ,void *&reuse_ptr
                                 ,size_type sizeof_object);

   //!Returns the number of total units that a user buffer
   //!of "userbytes" bytes really occupies (including header)
   static size_type priv_get_total_units(size_type userbytes);

   static size_type priv_first_block_offset(const void *this_ptr, size_type extra_hdr_bytes);
   size_type priv_block_end_offset() const;

   //!Returns next block if it's free.
   //!Returns 0 if next block is not free.
   block_ctrl *priv_next_block_if_free(block_ctrl *ptr);

   //!Check if this block is free (not allocated)
   bool priv_is_allocated_block(block_ctrl *ptr);

   //!Returns previous block's if it's free.
   //!Returns 0 if previous block is not free.
   std::pair<block_ctrl*, block_ctrl*> priv_prev_block_if_free(block_ctrl *ptr);

   //!Real expand function implementation
   bool priv_expand(void *ptr, size_type min_size, size_type &prefer_in_recvd_out_size);

   //!Real expand to both sides implementation
   void* priv_expand_both_sides(boost::interprocess::allocation_type command
                               ,size_type min_size, size_type &prefer_in_recvd_out_size
                               ,void *reuse_ptr
                               ,bool only_preferred_backwards);

   //!Real private aligned allocation function
   //void* priv_allocate_aligned     (size_type nbytes, size_type alignment);

   //!Checks if block has enough memory and splits/unlinks the block
   //!returning the address to the users
   void* priv_check_and_allocate(size_type units
                                ,block_ctrl* prev
                                ,block_ctrl* block
                                ,size_type &received_size);
   //!Real deallocation algorithm
   void priv_deallocate(void *addr);

   //!Makes a new memory portion available for allocation
   void priv_add_segment(void *addr, size_type size);

   void priv_mark_new_allocated_block(block_ctrl *block);

   public:
   static const size_type Alignment      = ::boost::container::dtl::alignment_of
      < ::boost::container::dtl::max_align_t>::value;
   private:
   static const size_type BlockCtrlBytes = ipcdetail::ct_rounded_size<sizeof(block_ctrl), Alignment>::value;
   static const size_type BlockCtrlUnits = BlockCtrlBytes/Alignment;
   static const size_type MinBlockUnits  = BlockCtrlUnits;
   static const size_type MinBlockSize   = MinBlockUnits*Alignment;
   static const size_type AllocatedCtrlBytes = BlockCtrlBytes;
   static const size_type AllocatedCtrlUnits = BlockCtrlUnits;
   static const size_type UsableByPreviousChunk = 0;

   public:
   static const size_type PayloadPerAllocation = BlockCtrlBytes;
};

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>
   ::priv_first_block_offset(const void *this_ptr, size_type extra_hdr_bytes)
{
   //First align "this" pointer
   size_type uint_this         = (std::size_t)this_ptr;
   size_type uint_aligned_this = uint_this/Alignment*Alignment;
   size_type this_disalignment = (uint_this - uint_aligned_this);
   size_type block1_off =
      ipcdetail::get_rounded_size(sizeof(simple_seq_fit_impl) + extra_hdr_bytes + this_disalignment, Alignment)
      - this_disalignment;
   algo_impl_t::assert_alignment(this_disalignment + block1_off);
   return block1_off;
}

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>
   ::priv_block_end_offset() const
{
   //First align "this" pointer
   size_type uint_this         = (std::size_t)this;
   size_type uint_aligned_this = uint_this/Alignment*Alignment;
   size_type this_disalignment = (uint_this - uint_aligned_this);
   size_type old_end =
      ipcdetail::get_truncated_size(m_header.m_size + this_disalignment, Alignment)
      - this_disalignment;
   algo_impl_t::assert_alignment(old_end + this_disalignment);
   return old_end;
}

template<class MutexFamily, class VoidPointer>
inline simple_seq_fit_impl<MutexFamily, VoidPointer>::
   simple_seq_fit_impl(size_type segment_size, size_type extra_hdr_bytes)
{
   //Initialize sizes and counters
   m_header.m_allocated = 0;
   m_header.m_size      = segment_size;
   m_header.m_extra_hdr_bytes = extra_hdr_bytes;

   //Initialize pointers
   size_type block1_off = priv_first_block_offset(this, extra_hdr_bytes);

   m_header.m_root.m_next  = reinterpret_cast<block_ctrl*>
      ((reinterpret_cast<char*>(this) + block1_off));
   algo_impl_t::assert_alignment(ipcdetail::to_raw_pointer(m_header.m_root.m_next));
   m_header.m_root.m_next->m_size  = (segment_size - block1_off)/Alignment;
   m_header.m_root.m_next->m_next  = &m_header.m_root;
}

template<class MutexFamily, class VoidPointer>
inline simple_seq_fit_impl<MutexFamily, VoidPointer>::~simple_seq_fit_impl()
{
   //There is a memory leak!
//   BOOST_ASSERT(m_header.m_allocated == 0);
//   BOOST_ASSERT(m_header.m_root.m_next->m_next == block_ctrl_ptr(&m_header.m_root));
}

template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::grow(size_type extra_size)
{
   //Old highest address block's end offset
   size_type old_end = this->priv_block_end_offset();

   //Update managed buffer's size
   m_header.m_size += extra_size;

   //We need at least MinBlockSize blocks to create a new block
   if((m_header.m_size - old_end) < MinBlockSize){
      return;
   }

   //We'll create a new free block with extra_size bytes

   block_ctrl *new_block = reinterpret_cast<block_ctrl*>
      (reinterpret_cast<char*>(this) + old_end);

   algo_impl_t::assert_alignment(new_block);
   new_block->m_next = 0;
   new_block->m_size = (m_header.m_size - old_end)/Alignment;
   m_header.m_allocated += new_block->m_size*Alignment;
   this->priv_deallocate(priv_get_user_buffer(new_block));
}

template<class MutexFamily, class VoidPointer>
void simple_seq_fit_impl<MutexFamily, VoidPointer>::shrink_to_fit()
{
   //Get the root and the first memory block
   block_ctrl *prev                 = &m_header.m_root;
   block_ctrl *last                 = &m_header.m_root;
   block_ctrl *block                = ipcdetail::to_raw_pointer(last->m_next);
   block_ctrl *root                 = &m_header.m_root;

   //No free block?
   if(block == root) return;

   //Iterate through the free block list
   while(block != root){
      prev  = last;
      last  = block;
      block = ipcdetail::to_raw_pointer(block->m_next);
   }

   char *last_free_end_address   = reinterpret_cast<char*>(last) + last->m_size*Alignment;
   if(last_free_end_address != (reinterpret_cast<char*>(this) + priv_block_end_offset())){
      //there is an allocated block in the end of this block
      //so no shrinking is possible
      return;
   }

   //Check if have only 1 big free block
   void *unique_block = 0;
   if(!m_header.m_allocated){
      BOOST_ASSERT(prev == root);
      size_type ignore_recvd = 0;
      void *ignore_reuse = 0;
      unique_block = priv_allocate(boost::interprocess::allocate_new, 0, ignore_recvd, ignore_reuse);
      if(!unique_block)
         return;
      last = ipcdetail::to_raw_pointer(m_header.m_root.m_next);
      BOOST_ASSERT(last_free_end_address == (reinterpret_cast<char*>(last) + last->m_size*Alignment));
   }
   size_type last_units = last->m_size;

   size_type received_size;
   void *addr = priv_check_and_allocate(last_units, prev, last, received_size);
   (void)addr;
   BOOST_ASSERT(addr);
   BOOST_ASSERT(received_size == last_units*Alignment - AllocatedCtrlBytes);

   //Shrink it
   m_header.m_size /= Alignment;
   m_header.m_size -= last->m_size;
   m_header.m_size *= Alignment;
   m_header.m_allocated -= last->m_size*Alignment;

   if(unique_block)
      priv_deallocate(unique_block);
}

template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_mark_new_allocated_block(block_ctrl *new_block)
{
   new_block->m_next = 0;
}

template<class MutexFamily, class VoidPointer>
inline
typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *
   simple_seq_fit_impl<MutexFamily, VoidPointer>::priv_get_block(const void *ptr)
{
   return const_cast<block_ctrl*>(reinterpret_cast<const block_ctrl*>
      (reinterpret_cast<const char*>(ptr) - AllocatedCtrlBytes));
}

template<class MutexFamily, class VoidPointer>
inline
void *simple_seq_fit_impl<MutexFamily, VoidPointer>::
      priv_get_user_buffer(const typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *block)
{
   return const_cast<char*>(reinterpret_cast<const char*>(block) + AllocatedCtrlBytes);
}

template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::priv_add_segment(void *addr, size_type segment_size)
{
   algo_impl_t::assert_alignment(addr);
   //Check size
   BOOST_ASSERT(!(segment_size < MinBlockSize));
   if(segment_size < MinBlockSize)
      return;
   //Construct big block using the new segment
   block_ctrl *new_block   = static_cast<block_ctrl *>(addr);
   new_block->m_size       = segment_size/Alignment;
   new_block->m_next       = 0;
   //Simulate this block was previously allocated
   m_header.m_allocated   += new_block->m_size*Alignment;
   //Return block and insert it in the free block list
   this->priv_deallocate(priv_get_user_buffer(new_block));
}

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>::get_size()  const
   {  return m_header.m_size;  }

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>::get_free_memory()  const
{
   return m_header.m_size - m_header.m_allocated -
      algo_impl_t::multiple_of_units(sizeof(*this) + m_header.m_extra_hdr_bytes);
}

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>::
   get_min_size (size_type extra_hdr_bytes)
{
   return ipcdetail::get_rounded_size((size_type)sizeof(simple_seq_fit_impl),Alignment) +
          ipcdetail::get_rounded_size(extra_hdr_bytes,Alignment)
          + MinBlockSize;
}

template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
    all_memory_deallocated()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   return m_header.m_allocated == 0 &&
          ipcdetail::to_raw_pointer(m_header.m_root.m_next->m_next) == &m_header.m_root;
}

template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::zero_free_memory()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   block_ctrl *block = ipcdetail::to_raw_pointer(m_header.m_root.m_next);

   //Iterate through all free portions
   do{
      //Just clear user the memory part reserved for the user
      std::memset( priv_get_user_buffer(block)
                 , 0
             , block->get_user_bytes());
      block = ipcdetail::to_raw_pointer(block->m_next);
   }
   while(block != &m_header.m_root);
}

template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
    check_sanity()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   block_ctrl *block = ipcdetail::to_raw_pointer(m_header.m_root.m_next);

   size_type free_memory = 0;

   //Iterate through all blocks obtaining their size
   while(block != &m_header.m_root){
      algo_impl_t::assert_alignment(block);
      if(!algo_impl_t::check_alignment(block))
         return false;
      //Free blocks's next must be always valid
      block_ctrl *next = ipcdetail::to_raw_pointer(block->m_next);
      if(!next){
         return false;
      }
      free_memory += block->m_size*Alignment;
      block = next;
   }

   //Check allocated bytes are less than size
   if(m_header.m_allocated > m_header.m_size){
      return false;
   }

   //Check free bytes are less than size
   if(free_memory > m_header.m_size){
      return false;
   }
   return true;
}

template<class MutexFamily, class VoidPointer>
inline void* simple_seq_fit_impl<MutexFamily, VoidPointer>::
   allocate(size_type nbytes)
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   size_type ignore_recvd = nbytes;
   void *ignore_reuse = 0;
   return priv_allocate(boost::interprocess::allocate_new, nbytes, ignore_recvd, ignore_reuse);
}

template<class MutexFamily, class VoidPointer>
inline void* simple_seq_fit_impl<MutexFamily, VoidPointer>::
   allocate_aligned(size_type nbytes, size_type alignment)
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   return algo_impl_t::
      allocate_aligned(this, nbytes, alignment);
}

template<class MutexFamily, class VoidPointer>
template<class T>
inline T* simple_seq_fit_impl<MutexFamily, VoidPointer>::
   allocation_command  (boost::interprocess::allocation_type command,   size_type limit_size,
                        size_type &prefer_in_recvd_out_size, T *&reuse_ptr)
{
   void *raw_reuse = reuse_ptr;
   void * const ret = priv_allocation_command
      (command, limit_size, prefer_in_recvd_out_size, raw_reuse, sizeof(T));
   BOOST_ASSERT(0 == ((std::size_t)ret % ::boost::container::dtl::alignment_of<T>::value));
   reuse_ptr = static_cast<T*>(raw_reuse);
   return static_cast<T*>(ret);
}

template<class MutexFamily, class VoidPointer>
inline void* simple_seq_fit_impl<MutexFamily, VoidPointer>::
   raw_allocation_command  (boost::interprocess::allocation_type command, size_type limit_objects,
                        size_type &prefer_in_recvd_out_size, void *&reuse_ptr, size_type sizeof_object)
{
   size_type const preferred_objects = prefer_in_recvd_out_size;
   if(!sizeof_object){
      return reuse_ptr = 0, static_cast<void*>(0);
  }
   if(command & boost::interprocess::try_shrink_in_place){
      if(!reuse_ptr) return static_cast<void*>(0);
      prefer_in_recvd_out_size = preferred_objects*sizeof_object;
      bool success = algo_impl_t::try_shrink
         ( this, reuse_ptr, limit_objects*sizeof_object, prefer_in_recvd_out_size);
      prefer_in_recvd_out_size /= sizeof_object;
      return success ? reuse_ptr : 0;
   }
   else{
      return priv_allocation_command
         (command, limit_objects, prefer_in_recvd_out_size, reuse_ptr, sizeof_object);
   }
}

template<class MutexFamily, class VoidPointer>
inline void* simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_allocation_command (boost::interprocess::allocation_type command,   size_type limit_size,
                       size_type &prefer_in_recvd_out_size, void *&reuse_ptr, size_type sizeof_object)
{
   size_type const preferred_size = prefer_in_recvd_out_size;
   command &= ~boost::interprocess::expand_bwd;
   if(!command){
      return reuse_ptr = 0, static_cast<void*>(0);
   }

   size_type max_count = m_header.m_size/sizeof_object;
   if(limit_size > max_count || preferred_size > max_count){
      return reuse_ptr = 0, static_cast<void*>(0);
   }
   size_type l_size = limit_size*sizeof_object;
   size_type r_size = preferred_size*sizeof_object;
   void *ret = 0;
   {
      //-----------------------
      boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
      //-----------------------
      ret = priv_allocate(command, l_size, r_size, reuse_ptr);
   }
   prefer_in_recvd_out_size = r_size/sizeof_object;
   return ret;
}

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>::size(const void *ptr) const
{
   //We need no synchronization since this block is not going
   //to be modified
   //Obtain the real size of the block
   const block_ctrl *block = static_cast<const block_ctrl*>(priv_get_block(ptr));
   return block->get_user_bytes();
}

template<class MutexFamily, class VoidPointer>
void* simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_expand_both_sides(boost::interprocess::allocation_type command
                         ,size_type min_size
                         ,size_type &prefer_in_recvd_out_size
                         ,void *reuse_ptr
                         ,bool only_preferred_backwards)
{
   size_type const preferred_size = prefer_in_recvd_out_size;
   typedef std::pair<block_ctrl *, block_ctrl *> prev_block_t;
   block_ctrl *reuse = priv_get_block(reuse_ptr);
   prefer_in_recvd_out_size = 0;

   if(this->size(reuse_ptr) > min_size){
      prefer_in_recvd_out_size = this->size(reuse_ptr);
      return reuse_ptr;
   }

   if(command & boost::interprocess::expand_fwd){
      if(priv_expand(reuse_ptr, min_size, prefer_in_recvd_out_size = preferred_size))
         return reuse_ptr;
   }
   else{
      prefer_in_recvd_out_size = this->size(reuse_ptr);
   }
   if(command & boost::interprocess::expand_bwd){
      size_type extra_forward = !prefer_in_recvd_out_size ? 0 : prefer_in_recvd_out_size + BlockCtrlBytes;
      prev_block_t prev_pair = priv_prev_block_if_free(reuse);
      block_ctrl *prev = prev_pair.second;
      if(!prev){
         return 0;
      }

      size_type needs_backwards =
         ipcdetail::get_rounded_size(preferred_size - extra_forward, Alignment);

      if(!only_preferred_backwards){
            max_value(ipcdetail::get_rounded_size(min_size - extra_forward, Alignment)
                     ,min_value(prev->get_user_bytes(), needs_backwards));
      }

      //Check if previous block has enough size
      if((prev->get_user_bytes()) >=  needs_backwards){
         //Now take all next space. This will succeed
         if(!priv_expand(reuse_ptr, prefer_in_recvd_out_size, prefer_in_recvd_out_size)){
            BOOST_ASSERT(0);
         }

         //We need a minimum size to split the previous one
         if((prev->get_user_bytes() - needs_backwards) > 2*BlockCtrlBytes){
             block_ctrl *new_block = reinterpret_cast<block_ctrl*>
                  (reinterpret_cast<char*>(reuse) - needs_backwards - BlockCtrlBytes);

            new_block->m_next = 0;
            new_block->m_size =
               BlockCtrlUnits + (needs_backwards + extra_forward)/Alignment;
            prev->m_size =
               (prev->get_total_bytes() - needs_backwards)/Alignment - BlockCtrlUnits;
            prefer_in_recvd_out_size = needs_backwards + extra_forward;
            m_header.m_allocated += needs_backwards + BlockCtrlBytes;
            return priv_get_user_buffer(new_block);
         }
         else{
            //Just merge the whole previous block
            block_ctrl *prev_2_block = prev_pair.first;
            //Update received size and allocation
            prefer_in_recvd_out_size = extra_forward + prev->get_user_bytes();
            m_header.m_allocated += prev->get_total_bytes();
            //Now unlink it from previous block
            prev_2_block->m_next = prev->m_next;
            prev->m_size = reuse->m_size + prev->m_size;
            prev->m_next = 0;
            priv_get_user_buffer(prev);
         }
      }
   }
   return 0;
}

template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::
   deallocate_many(typename simple_seq_fit_impl<MutexFamily, VoidPointer>::multiallocation_chain &chain)
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   while(!chain.empty()){
      this->priv_deallocate(to_raw_pointer(chain.pop_front()));
   }
}

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::size_type
simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_get_total_units(size_type userbytes)
{
   size_type s = ipcdetail::get_rounded_size(userbytes, Alignment)/Alignment;
   if(!s)   ++s;
   return BlockCtrlUnits + s;
}

template<class MutexFamily, class VoidPointer>
void * simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_allocate(boost::interprocess::allocation_type command
                ,size_type limit_size, size_type &prefer_in_recvd_out_size, void *&reuse_ptr)
{
   size_type const preferred_size = prefer_in_recvd_out_size;
   if(command & boost::interprocess::shrink_in_place){
      if(!reuse_ptr)  return static_cast<void*>(0);
      bool success = algo_impl_t::shrink(this, reuse_ptr, limit_size, prefer_in_recvd_out_size);
      return success ? reuse_ptr : 0;
   }
   prefer_in_recvd_out_size = 0;

   if(limit_size > preferred_size){
      return reuse_ptr = 0, static_cast<void*>(0);
   }

   //Number of units to request (including block_ctrl header)
   size_type nunits = ipcdetail::get_rounded_size(preferred_size, Alignment)/Alignment + BlockCtrlUnits;

   //Get the root and the first memory block
   block_ctrl *prev                 = &m_header.m_root;
   block_ctrl *block                = ipcdetail::to_raw_pointer(prev->m_next);
   block_ctrl *root                 = &m_header.m_root;
   block_ctrl *biggest_block        = 0;
   block_ctrl *prev_biggest_block   = 0;
   size_type biggest_size         = 0;

   //Expand in place
   if(reuse_ptr && (command & (boost::interprocess::expand_fwd | boost::interprocess::expand_bwd))){
      void *ret = priv_expand_both_sides(command, limit_size, prefer_in_recvd_out_size = preferred_size, reuse_ptr, true);
      if(ret){
         algo_impl_t::assert_alignment(ret);
         return ret;
      }
   }

   if(command & boost::interprocess::allocate_new){
      prefer_in_recvd_out_size = 0;
      while(block != root){
         //Update biggest block pointers
         if(block->m_size > biggest_size){
            prev_biggest_block = prev;
            biggest_size  = block->m_size;
            biggest_block = block;
         }
         algo_impl_t::assert_alignment(block);
         void *addr = this->priv_check_and_allocate(nunits, prev, block, prefer_in_recvd_out_size);
         if(addr){
            algo_impl_t::assert_alignment(addr);
            return reuse_ptr = 0, addr;
         }
         //Bad luck, let's check next block
         prev  = block;
         block = ipcdetail::to_raw_pointer(block->m_next);
      }

      //Bad luck finding preferred_size, now if we have any biggest_block
      //try with this block
      if(biggest_block){
         size_type limit_units = ipcdetail::get_rounded_size(limit_size, Alignment)/Alignment + BlockCtrlUnits;
         if(biggest_block->m_size < limit_units){
            return reuse_ptr = 0, static_cast<void*>(0);
         }
         void *ret = this->priv_check_and_allocate
            (biggest_block->m_size, prev_biggest_block, biggest_block, prefer_in_recvd_out_size = biggest_block->m_size*Alignment - BlockCtrlUnits);
         BOOST_ASSERT(ret != 0);
         algo_impl_t::assert_alignment(ret);
         return reuse_ptr = 0, ret;
      }
   }
   //Now try to expand both sides with min size
   if(reuse_ptr && (command & (boost::interprocess::expand_fwd | boost::interprocess::expand_bwd))){
      void *ret = priv_expand_both_sides (command, limit_size, prefer_in_recvd_out_size = preferred_size, reuse_ptr, false);
      algo_impl_t::assert_alignment(ret);
      return ret;
   }
   return reuse_ptr = 0, static_cast<void*>(0);
}

template<class MutexFamily, class VoidPointer> inline
bool simple_seq_fit_impl<MutexFamily, VoidPointer>::priv_is_allocated_block
      (typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *block)
{  return block->m_next == 0;  }

template<class MutexFamily, class VoidPointer>
inline typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *
   simple_seq_fit_impl<MutexFamily, VoidPointer>::
      priv_next_block_if_free
         (typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *ptr)
{
   //Take the address where the next block should go
   block_ctrl *next_block = reinterpret_cast<block_ctrl*>
      (reinterpret_cast<char*>(ptr) + ptr->m_size*Alignment);

   //Check if the adjacent block is in the managed segment
   char *this_char_ptr = reinterpret_cast<char*>(this);
   char *next_char_ptr = reinterpret_cast<char*>(next_block);
   size_type distance = (size_type)(next_char_ptr - this_char_ptr)/Alignment;

   if(distance >= (m_header.m_size/Alignment)){
      //"next_block" does not exist so we can't expand "block"
      return 0;
   }

   if(!next_block->m_next)
      return 0;

   return next_block;
}

template<class MutexFamily, class VoidPointer>
inline
   std::pair<typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *
            ,typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *>
   simple_seq_fit_impl<MutexFamily, VoidPointer>::
      priv_prev_block_if_free
         (typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *ptr)
{
   typedef std::pair<block_ctrl *, block_ctrl *> prev_pair_t;
   //Take the address where the previous block should go
   block_ctrl *root           = &m_header.m_root;
   block_ctrl *prev_2_block   = root;
   block_ctrl *prev_block = ipcdetail::to_raw_pointer(root->m_next);

   while((reinterpret_cast<char*>(prev_block) + prev_block->m_size*Alignment)
            != reinterpret_cast<char*>(ptr)
         && prev_block != root){
      prev_2_block = prev_block;
      prev_block = ipcdetail::to_raw_pointer(prev_block->m_next);
   }

   if(prev_block == root || !prev_block->m_next)
      return prev_pair_t(static_cast<block_ctrl*>(0), static_cast<block_ctrl*>(0));

   //Check if the previous block is in the managed segment
   char *this_char_ptr = reinterpret_cast<char*>(this);
   char *prev_char_ptr = reinterpret_cast<char*>(prev_block);
   size_type distance = (size_type)(prev_char_ptr - this_char_ptr)/Alignment;

   if(distance >= (m_header.m_size/Alignment)){
      //"previous_block" does not exist so we can't expand "block"
      return prev_pair_t(static_cast<block_ctrl*>(0), static_cast<block_ctrl*>(0));
   }
   return prev_pair_t(prev_2_block, prev_block);
}


template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_expand (void *ptr, size_type min_size, size_type &received_size)
{
   size_type preferred_size = received_size;
   //Obtain the real size of the block
   block_ctrl *block = reinterpret_cast<block_ctrl*>(priv_get_block(ptr));
   size_type old_block_size = block->m_size;

   //All used blocks' next is marked with 0 so check it
   BOOST_ASSERT(block->m_next == 0);

   //Put this to a safe value
   received_size = old_block_size*Alignment - BlockCtrlBytes;

   //Now translate it to Alignment units
   min_size       = ipcdetail::get_rounded_size(min_size, Alignment)/Alignment;
   preferred_size = ipcdetail::get_rounded_size(preferred_size, Alignment)/Alignment;

   //Some parameter checks
   if(min_size > preferred_size)
      return false;

   size_type data_size = old_block_size - BlockCtrlUnits;

   if(data_size >= min_size)
      return true;

   block_ctrl *next_block = priv_next_block_if_free(block);
   if(!next_block){
      return false;
   }

   //Is "block" + "next_block" big enough?
   size_type merged_size = old_block_size + next_block->m_size;

   //Now we can expand this block further than before
   received_size = merged_size*Alignment - BlockCtrlBytes;

   if(merged_size < (min_size + BlockCtrlUnits)){
      return false;
   }

   //We can fill expand. Merge both blocks,
   block->m_next = next_block->m_next;
   block->m_size = merged_size;

   //Find the previous free block of next_block
   block_ctrl *prev = &m_header.m_root;
   while(ipcdetail::to_raw_pointer(prev->m_next) != next_block){
      prev = ipcdetail::to_raw_pointer(prev->m_next);
   }

   //Now insert merged block in the free list
   //This allows reusing allocation logic in this function
   m_header.m_allocated -= old_block_size*Alignment;
   prev->m_next = block;

   //Now use check and allocate to do the allocation logic
   preferred_size += BlockCtrlUnits;
   size_type nunits = preferred_size < merged_size ? preferred_size : merged_size;

   //This must success since nunits is less than merged_size!
   if(!this->priv_check_and_allocate (nunits, prev, block, received_size)){
      //Something very ugly is happening here. This is a bug
      //or there is memory corruption
      BOOST_ASSERT(0);
      return false;
   }
   return true;
}

template<class MutexFamily, class VoidPointer> inline
void* simple_seq_fit_impl<MutexFamily, VoidPointer>::priv_check_and_allocate
   (size_type nunits
   ,typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl* prev
   ,typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl* block
   ,size_type &received_size)
{
   size_type upper_nunits = nunits + BlockCtrlUnits;
   bool found = false;

   if (block->m_size > upper_nunits){
      //This block is bigger than needed, split it in
      //two blocks, the first's size will be "units"
      //the second's size will be "block->m_size-units"
      size_type total_size = block->m_size;
      block->m_size  = nunits;

      block_ctrl *new_block = reinterpret_cast<block_ctrl*>
         (reinterpret_cast<char*>(block) + Alignment*nunits);
      new_block->m_size  = total_size - nunits;
      new_block->m_next  = block->m_next;
      prev->m_next = new_block;
      found = true;
   }
   else if (block->m_size >= nunits){
      //This block has exactly the right size with an extra
      //unusable extra bytes.
      prev->m_next = block->m_next;
      found = true;
   }

   if(found){
      //We need block_ctrl for deallocation stuff, so
      //return memory user can overwrite
      m_header.m_allocated += block->m_size*Alignment;
      received_size =  block->get_user_bytes();
      //Mark the block as allocated
      block->m_next = 0;
      //Check alignment
      algo_impl_t::assert_alignment(block);
      return priv_get_user_buffer(block);
   }
   return 0;
}

template<class MutexFamily, class VoidPointer>
void simple_seq_fit_impl<MutexFamily, VoidPointer>::deallocate(void* addr)
{
   if(!addr)   return;
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   return this->priv_deallocate(addr);
}

template<class MutexFamily, class VoidPointer>
void simple_seq_fit_impl<MutexFamily, VoidPointer>::priv_deallocate(void* addr)
{
   if(!addr)   return;

   //Let's get free block list. List is always sorted
   //by memory address to allow block merging.
   //Pointer next always points to the first
   //(lower address) block
   block_ctrl * prev  = &m_header.m_root;
   block_ctrl * pos   = ipcdetail::to_raw_pointer(m_header.m_root.m_next);
   block_ctrl * block = reinterpret_cast<block_ctrl*>(priv_get_block(addr));

   //All used blocks' next is marked with 0 so check it
   BOOST_ASSERT(block->m_next == 0);

   //Check if alignment and block size are right
   algo_impl_t::assert_alignment(addr);

   size_type total_size = Alignment*block->m_size;
   BOOST_ASSERT(m_header.m_allocated >= total_size);

   //Update used memory count
   m_header.m_allocated -= total_size;

   //Let's find the previous and the next block of the block to deallocate
   //This ordering comparison must be done with original pointers
   //types since their mapping to raw pointers can be different
   //in each process
   while((ipcdetail::to_raw_pointer(pos) != &m_header.m_root) && (block > pos)){
      prev = pos;
      pos = ipcdetail::to_raw_pointer(pos->m_next);
   }

   //Try to combine with upper block
   char *block_char_ptr = reinterpret_cast<char*>(ipcdetail::to_raw_pointer(block));

   if ((block_char_ptr + Alignment*block->m_size) ==
         reinterpret_cast<char*>(ipcdetail::to_raw_pointer(pos))){
      block->m_size += pos->m_size;
      block->m_next  = pos->m_next;
   }
   else{
      block->m_next = pos;
   }

   //Try to combine with lower block
   if ((reinterpret_cast<char*>(ipcdetail::to_raw_pointer(prev))
            + Alignment*prev->m_size) ==
        block_char_ptr){


      prev->m_size += block->m_size;
      prev->m_next  = block->m_next;
   }
   else{
      prev->m_next = block;
   }
}

}  //namespace ipcdetail {

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_MEM_ALGO_DETAIL_SIMPLE_SEQ_FIT_IMPL_HPP


/* simple_seq_fit_impl.hpp
aoF5UDG3jd4kF4hQK0RlZj0/MD8Lh0L3jJYgxV64dFcXf0rA19jCgdPA6vjtddme3BOIvTLgqXS65Az1+iHpIyBUwcGoBDOHVXxnW1+YSd6OjC9Xe4+5xnn1vj6J59n0roLeueOR2udkuwv/H2d1376pk1F4lJIWh3bpaGL4r9sM5KXb4KBDVN3vONI8SSPKhRVonsdVufBaCen6t8b5Qt9Ynpxh9CkRhNl1k/OySfT9G69Cx7Owm49WJsJN1RbMjedEN4ZEZemp7ywr3SZ5xIv3ddkTTY+S4DPWA34vrHtAWdsiWHkGYFdYAOpRzeL8rahy3eh9ylcpp4BQ0yLwHTDtup8jnUy66ZBy6CjY1L1YyEmqK1b7FGFQH9vGV5hGlSf+LHU4ZbhHkLfm3vZbLcqWJknr4AXgMDZM3ifAvB81/ThkoOZ+A6g2D0CK3wfKVlkGeKrw0r2lmgCifzUlHwCy4u46m9NpTzxUqs2qqR/KqrOV4T07GVaWedb9M/x6bv4Rd/gs+NXOGldtAqbsvZIqhDegVaHGeh045C8VJkxneH96ZM1EWnf/pz6o9ouUR1qX1vt3nF/CPg5Hv8s9UEGGfoVmfSsXGFjcdVC88Unm+jpWGbT9a1GTZK6vnUM7K/ddIAe/DJtkTSuEN+MMbHXMcC/Bzs3HwSEWaGNlpDP0ujPR0ZpGExJ1FOSDs5crva7oQ6dxRjG9Wrg1PDfNt7QaLczzvXPYaqhjDyZFRZ4gn8GVxxeEj3T8z6c4fU6yyIGvh1ENhI4EY8OeU0XZ9mG1Uh07q3uz3DT76fl0ly2OmXNJLZevK1kSLr+TQA1/Og6ne3TcGDoMBF15HbT8UhpRof7g8eJy06I9ybs30P7iR+cRiBzozjI01fEdHELW8jkQoT+v/aQE/dYd9HznIz7WhBZI8K7d1ExSAuLmQfgwtXsyVoIq/7ap1pXikTa5xD72R9rY2E3EiRGqzGi6I91C9TD+zF20za7t9IsDGLHS7VgD5Vjzr7K2fnUbvjHufvNK5DTAk0HKTBLVjbhjn/ceXz9e3oPr6kuingEnuhfib84Y7pQGbyePOufOGH9ZF+7Cw6iOD4ZuZfN49+DAbtmji9Mz/lyeXAYJI1j0EWwAZlhTfkkyDTZQS7tGWj/n31I2eXS/HAZ7nV4GuVJNtZ1w53g7FYz7BPVdtMce5cnRvb1GfmLl2YUXOjBbhFlLAqmr50nrt19OQWbUj07wqs4yhVvLjySHVbfEq7olmH9jT77luvZme0fHde4VQsT6MPhpiofI8cukPBEkORayNDsK1yH09JwDiuRHqT6iobyyVB8hjRIec3TLMJOcic9iKwUdrqZTCrLosKbBMDrScoUryOt5ReAuZydHVt7kGIy5sKXcjUQrlEWoN/EWf0t8oT7mj52B+bCxKDOpt1BCk7Tp+FluUQEgs3ne1wPc82huMddUA4iHLdScJSidJvyEtqc9p6+qwebohF6dkVUB/gGCjIFGZc8+gmugZ1bfu927YWspj+c82lN9VdnTAO3KqWWvJfgJVKn5IjLgzUXwMzyd1iVwaSvBuDWgjfLaeHnssZIONte1ZP21D2GElauX54kRBHkphcHuHLgkQ0121hANGhTvrLAjd333Y2ugi1W5St6oVKRqeTlMbRUP7HlVYzqoN2JJwHARwkcw5zVIlnOMUIsuuIhEcnt0ObmfMG7tFVU35mjVdKjuSuEPnOz7TSm+aeziews+dPghNSXnw22X+2C86cHfTS72N6Cj2NBLx05ODtuBiOiNRgRE7m+Wiilwg50rVp7cp5Zu/qo6yHlVUFZU59R6s6d8d2XydOWSepODLGPFSCAb+eKcfGxaF/u5ZnF62aHe5APAdCv2DL5S/UW62eiuquXj801dTmYBUmF8ZvkAmRDAkpdUeUsiFnJxI96mbZ2GIj2y/QXWbTCmtcmVM2jnHl3mNs2uQFkd2hqd3PN4S1fo+uVGMHw+wnPz5NG/EFMzp+1GjU3Np2O01b05OjG/C27tJtSqUHUysvXv8GwOWnUJjP8ubvrqJvLMH870VL/zOLXbFugaGCh3LIlpsfuoqjrD83pZN9o+OfIsK+2fqWD19MSeKJNsWmu3w7mUa2COa8L3/NF8/XzKmcj1JE8Y+YFRdyaowzmZ9u1ysh/evbea/5CwAej81ns9fr743D12cfPWO3xaZLp8yPM+cAjzR6cAgfhYHng5L28FLPp5gqR5ETvpWYfv5T+icoUHQ0S8TtCKnTRysYgLdf6gIBsKvLWIQXn8pe91Pu8FHGsyPrSpIehQrys9aE9l4yB+Vqf7AaVJMzT3gQ+7SI9kWBpdJqVz7ujf4VJPubm9VYiWDfCBN7n0qvKrZhW0Nqdx1WMG4wEe35t29kwRUHcJLli4GY7SoCinYIjVK8GSVqrDs/iG5FCVxg307XlBpUZhs2dqZnoVXZ+C4JSnQyr/jrW/AfyED2rQ5kR5wa73zH/ZZCEoTy/6yXyXpP3jLkvbBDzq81SzPrXsnVLcIUTFw4LovA/m96CJ8Ea6naYAP0mUewHKCxDaTBWFWA5UO1pElafZ06nouVwgEN5d12dQGArw4v8+AmBGNLgMZrZNYs66yieB4ygcqKv/Zi+TRfOXSUytOHj31oAyXzNzrYQa3e1fWb4Pw3v6NGp0bSfMl7KskWXUbq9Dg4NHmELfhwaAMhTrszzmUzXV4bidl5dZqxkit1udvgK3Vs1brjRC6HfZRAMFbJcdGPVUaQUJjyc2ywKvHqVHP5rGicz2njCvwd3fDjualBdFVmTYbsoQ5WSY7bYa6SIPIkPLIASf7kY+0EjdFMUXwjATPYFvudZJvlhuCcz+VbRSknj7xXlRaG4JEna8YkADMhXRkhfyP2F9/iwgtEL4heHjsFhPTDA80Y/9tiBKGG2r71b8b/9xl2dIFLca/ywxaWlB+L+Q1N78+602qzWp8S+WR+k2H/rseIRnXwz4Hxn/1J3V4JppR7oT3es5Fpa1MauJHXWxXLKILGusyXBEBvzNAM0qabk4SmslX49jM4tLTn4B0ndFaX0lxhen7e9Ydwn83hF/s3TCyqYrX0IrrvQydlpeCjKvUSwlzj+9PJvVQ4N1LlpcNCXlaQEoYID/3f7suTC8u5lP2KoxfWyD8f4CX4DAvBEmVla0Kib+T1Jj2DaI3VjeEpJ2sjj6C9Udn9u+qRLXPyHokR+ftjfhI7DYVlj0y9Sz8e39enVlxr8N8xJ+c4+7L8404d1/i6q0JwTJJQOhOgJSovMqPPnP0thC7t21AZA+iYOzzJPiE6touS1H+wy2V3c5YbgrLMdlB4ICnpucx9PlTiU16iBrNDLQ0qz63/njDwJP0bCif5lsDf9WGZzVwpYPmLNs324535Vn/GGJ0FySsPrXNqHiuCU4e3Kkko0FkHQuHPS1erT/G5UW1YVY1hR4QmZGLaPtRUl81SHDHd7lk+TAwIgwdzlUY0joz997+0GeM/vA/TW8fZ6KwGhQS47yuj1KB59/drPVGc+H8DdQ6S/hVXP4GIHw7LePC4bMfm75+dZoW3Fp55rA8kRB9X8fwpVhyjR/1yi9w5igFR88j3qCdlqV+4WY6xRVsu4WvslbqUTPb80nSn2MU1ZVlM3uHPvQSLzMoftQoWnQ9faPESjqdQUNY18JtYDWUEF9bq1t2VGVafpJJBtpNG5i2aUhaabkpIzrPNcCOYwmPt12ygIHb+j25UeY1idBZ7yHCHvnYIz89XdfYEFOJdQbzujZmBP/Ckuxgs23q3W9HF0Mfra5vnkNjr3Tl8IqwO8f1i/jfG8W51Nzw4jDNSzQYe05epq5mffi0vHv/bwa/ZZXpz/OltjPM+fgSGvD4xdzgW5pq/Mlm4KtEPffQ0+/qAiOsY9xbATGZSRCrH2lUnkszHCvIGjS6AFoPnuBC4PUOJbnwlrUN5KR1nJpNI1QGV/Sr/U++79PYujAJHcoX7medZ/IHQpRENkdn96vRyu3gX3PVg68V9pgwhOBoBxMUAnnp1UqDuTYeuXVWaIUKQEo1/Q0zxRUdLmANKgfkvlwxnkn3x0+FWRX0BYi57ct0ltTnKcniVQycvywbo0J197hwNH+hKzM2UL+cCy/TLMiAJEG8fSNOdbOmJCBcgefCuMU9uyT6VzXkTYFXgoxswWHuilfQ01tW6s3vv02bVGpJR6rmR3narSsGOyvoc33FeuZrDEH2d3ak5zyeVGs9aWFOg8epBkSVH1sA2Fko1ODfxTULKVLtbMSCzah/6SHRAc/eH8+Ufd5IdWxpJK1/1FXokviBm8b9PHZHJohBj7aYacRnO+btBLHOUY2Zfx7NitpcZV6ode5pcJF8MYPAP5RQiZS6y8gBEbb5LBUULXJ5f2bzXifNHe9YHw66B79Kf3zWMiQ5lm68Mmm/2BxsYR59iqFnWS/oubFvw+C3B+P0wqAGbZGGLKwn/QOyUo8NOLVx7TQ9QS3uGfOYPG8twd2s/qFP9UYuUVOxSeO6RNXXwftnL7kfIVslCksdQ2sqC4c3hQHbNsPrHLO0hu/CESEfQEnE+SH/wK/tQVhIOWM9Dfwml/4Naq8CERVfcERVrhbU41KxWCvSjom/MgRTHNFbyZtRrVN0HMBfzf4wg9tCJ0UTfgFFA33jOkfpg0BOTo5gd5lKB0a4dILu0CNQvNgivywFMQKc1QQ1sSQ+2UVGnGnUaFbxIvTUGudXMv82TeU8oHs191A3GoV6MbNcO7moyPZmKtX2H45SF7nlbpzz/VeLSZz+BzTHZovMCOmGDBmKkhmCNxHoq/v/JwZVgHy+jXeDQ8CzNyzBciUgQ+niBA00n+YmenP6ez6nXfD6NveOd/uIg29oisA7cElWqyfvz+a91k2lDyPiDtDKwDMSPq1HdLjt0Gy0t9BWTjHCVhTWf+toqmR93w3HLBPEu/n83qG/Lfnmgr4memRb2mrOQRV9zvMSTfayTkChXXhSLZf3ri+jt65vsNdgBH3B1ZDuc23AFLEAHLOyFgGXH0IPuJOt80neFbtIf8roH0U14JmlR+YYhxC1RXq/IL85x0TAIQHGrf4RyHDlao815VGEsDwEfYeBWEL/DSfHIsrIfAVZzfT09sCPS/4DqvtMQphEaMLIAzh1efp6xv3iawzvYDJlCfOgjYbHnTunlpMujbdRVf6HBf+rEjNx235jXMRqKR9E2QwDjZ0ZvqmdZ7baaaM1nH0dq7doIPlzQkoHqY0f6kfd7fhN07IeU7bsiXOYlg9ennCjVg2/NwL5kwulR2ca7LPK49/bCJutCdb5cR8WD8GFnLSfO5EMNHs1z3SKIEsOMzZZngsV76s9Knj4P3T/A1aHM0CQRieYcLj2qtNqM9rRc51M0QFW0gu3S2ZNM41ZFWEOM9YtedtWooUheNIGijLuc7IHdRYHhpOve349lhfA4Pfq3RQIMj6LdZj/19ep6ShPvTJFM3vUWttUpn4Z40tyjWMpft3U7Ypf2yd/+TMDW9JC0wW0zV/Ciq8rJ9xb1IXAZ/hXCxTLnH7gpaQlk+gQtOsWlXT06c1eJ1fO7+xWs3EzHwpTezdOpVfNEJHLcPwzuPEXurCV376Nh2HNhmhp0ZCeswGjM2V6/pXiuoqL/V/gWc6pyWZL+6ScIQGPS3H3QXE1wpU3HsgiaT0pWUC9hcpeV/xHgtIpQFg6fBcfb+1q+JcfIePtFSyuRB6iNmMyw6HVJyPrBqgu7h03b5P52XlpzXfmhCnmRv0XEhWWem3kbHNkRa2bZYrD7CglOV71cbk3T/CinboYhNDD6yYwIzspgHRcjILfirNTFwH/N2D7W6SSwH4L8U/fzRydTw/H+vnBf253wu8jAjqv/9bAbQMNGasVtvQ8kFlLnAwTc7WxEkJTOY6TpO2ksuXCKwn7nwK+iXp3/a4xEFIWiOW6/qvdgyPq/Ff9VzLUi610qwNQRotoZ+3B0ZnzBHDi/UnUnHM1qrc8N3rDWLXR4YgR0kWYeJrONImEOdJ2zRq+mEnHgjYveEX1cpuE5tle296Sk0rY+8xlu5y3nKgYGzyXaJWLrfAL74JpjA66eLm4VE9P/oV25Z6bswlpUre3LnjO3GfX9vNKqLEO2e/iHoq4vkiii1HCUh78JGhGKS/trKea+a+dOo6Q/a18+IN+Lnk8P1grqjkTAfIdokCqt5f0cJSbUV7sDhSkScPr/7e+1wiCv3ZQRuAyLLFe4KJhI7vJKZsERTj/Gqpjdm+je8OLSnm4hSsLQ6HthD7ergbHOOOEVNjPuptijTNtJi/V7umfy6a1rORmFvZmJAZjzAs+8GBU4zR/XK/qXmmW0+jJFLcoOzd3Ot4NLUXUgVces6pmHYRSzgFBEyyl4s3ZSO+HkrxUtz9W8O5J3d9LKsNmvVa2fEO/2131L1YwBv7oSzz7CL8Zkkm8DFrOucppPjLbdveY1rbh9u28RJDydu2mFID7IkjfnEl8TzDZKOWlxegr40POdP3LMtRzvqSgfOLI0J7y++vKiY8t5e5nPWxD9IQbYJwIZvMvhoO1mnaTsS2RGpWhOmPoeRVtD+NJ4F8auvuuduGTEafjwzKpPL7iCG8XeyxTUepbVO4kUUi4p+XMtgCKZxBPjDMgRoR8K4+7BFt2mHzzHU7G4e4w/fNVXHXpfYZBVPXn0r/nBzr60r/N+uDszzsn09qkxhkjsuUvVP0cbewUmH1gamFSGtSg2ONn1Jeo8f6sIqgNYUW7lD8F3d6nA8UjxV1KwfWD3ZHcbk3qJ1CIMbc70SoAJksHCS3JuBaw42CC8j9u86qG7mpwXt7FqR7Jc0BGDcfFmN4inZLZ8du022RFfn28dl9+tej2z0abQb5G3/mSUuwJGjIcJkDNKLgewqyNx7RTShbDg/t5hINMgm4elwTWK7n9miCqigOTW8cqo26lQhgoMnd7cvL2BR+Ggnn/sjMQ0W5l8gZqz333ddCxlr2ljD2IfyTql/ul8CdHGd8LBJx1S3OcRGPZ+/JkPenTRK/5NCDUGK/2qkJCskSMDVocysC6b60oELPbDGkEuyNjShGfs1nGhO8una9URjoyHS9kSAbQELs5UOVHLOz/Y3kx0sobO1yo3SeONdI+gEuCrNqpu0BjpmqwrNGhwRhR76IsLLOMazhTW4ODG8vlsdTIvF/cf5Ly85y7Tv5bbnjzsNfY9acWUQGQeApE6OOgnPF3xgt4CkdI2dDi5uHCwcju0LavHTshwtefV3EBe/qdxhnHGGpmQgE7z+tCoBsf9k5smtv2jlylTUcftH5s77syUs1yII9FTzlVXFum/CM9DL5cYFxIOpF0Q7xxsETGCWmD7EuS7iSD3/Gu5rt0enJNm06goABYV7nYdYQgTX0wCsUhuhbFGmchx5c7mEbgnWH1mVwizfk/ls37z4E68Utqva3Kgb4oDCcEQ/ZUhb2Ea/zRO1vUSLEvizShU7SMC09TrxLDQNE6lPlGdt19Gma3bnz9uTGAv7Zn5ZpjJ5MPGHX0fsN8v1xv+OMu+HY2N0sXbvM/c6IhJIanVN3IcLwfsdRX/xrYOuVF7z9tN/lmLdJOvsm53w28jywhGC5KI60mACup1VMQCf+YXex4xVgiMj0WGl/eOVSNscUMJQ3Nnpn7gvPfCJPCDO1C9RLtUiQltTX4N4e1jMKLDsYFhVR6WYGDMHzhy+GR04/jSe4LgUQHkLNjdByecoZ/ZHkeXCDo2tzSU+dmREkeWlwhGKSh0lQ7IGAx8IL3/In8ulntcOgWFjcooZK2fliatu0WXN8cyqhz+Gwz41wBoLPKqhsL/BLkbb45fCITfaf8tsHPnz5LtBrqbdOSeWdn9QSXQsBrZRPWy8cVSpQxz8Fhe4ljhdOCXBZdX+pycTG21ypKYMAmN02VfLWRSoGZ+NaJsu2UA5/DdN+oauw8rdPWdl/Mu3Ublm3nmY6uP6NfetqV8Er2pe5d7rtcAqS8Biw2sOr+6y/IWFF0bb15BU9qwx5XCsATfDN3awOoXsdbx3Wp9EYMBgc+sFOuH6cawb9qwumeVwQLJKHSFPzzM/yxNFKJO94zkbTtJO5EpVQlU+/YljuWF/Pl/xN2LTVBQlOHMufCrhQNyFwqGwaObaM5I5OqVnFvwjzO4v02PTzHlcpKqGhjPSzx2+rznuv1XDAnLBleYBrbLbvB7uTNEeT8Hh5avZibPLuckcho/KXuxn32K9HB5OvJffBIlfPd6uFuRwYAH8hm4chhRtaBsx8VedREc0YugJ3Qh1gaeLlsCf+qUT09csZzCv+Y3/7uhFT7xUFmmUqtsP3a3MfGAafLBgR2Aw0+rZ/43wAFI6NRPl02/f/fnA/G+Fk3Lg6Y0oBhBJt5bQy/oVu9QZbJH+n81kkVse7PmTYsgsWU4VODKb/sTxFpQMlHiMp60uM9Z+r+y46yoxKGaSlJgWKmrF9eSWSVyM1hCxr7vPq5mXKhebsCSTtI+8hVs88/ELS1oWGroGY3/uD/WmWF4MlQjgMyQK//HCKEJBampVa3WLhYBgcbdSfPBwLkEQw5Wkf2kBViNxDJvtlpR2qeJcPTH2vfia+2jGu6u6XAlTeV4hJJcstEu3ot0J+ekniTPOEAcNPZnfun+eLUIxSp86SpkZSY+e6plL/mk0D7238Z7KwWw2kxqqLxXJBlFLtLhmJpwE2nexSj4sEcgm0XBhSpUtFMaW/2rmiaLuOiMyj7o9F5sNpybf0oJVkE31SpkRmykHsCBv18bdjcxyPFkmfMhgIsgiVsGhTbPV/zHoRzTegmmBAVX/UtBO7iT/P146oKrKKdQnTeSTVRcnDEv9XJ7d7L6IGEivmcJt4Fo73XFXXKxrHb4B7mlWu25v5vd7dXEAzXyUF9pLNlD9csoyRM8Jp05PX0K2zd+e6dI/jr7qSt4qP7yOZjJ2CnhbvbWbwjIHq0y1POWcEhhLjmOcpc3pAs8ezH/VGnP6DUmCv1hyjwvvIhA/gZfOnkCqBWHsIMCB5/dNSdum0v5EhwUuvpVwWuxedS489kWUEVfAHHnGSQqz0g77sd1pzAherUWwZbFIZFYXEqx9emtMu+wHVIHzkiLhwab0Qr6233xPwQqsDZEqYnixPQ4/85yzZ57VLYlqD7htV1O5SbVVFMkJp+FOoWLV+sA85BAcF91PwWzI=
*/