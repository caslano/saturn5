//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_MONOTONIC_BUFFER_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_MONOTONIC_BUFFER_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/detail/block_slist.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! A monotonic_buffer_resource is a special-purpose memory resource intended for
//! very fast memory allocations in situations where memory is used to build up a
//! few objects and then is released all at once when the memory resource object
//! is destroyed. It has the following qualities:
//! 
//! - A call to deallocate has no effect, thus the amount of memory consumed
//!   increases monotonically until the resource is destroyed.
//! 
//! - The program can supply an initial buffer, which the allocator uses to satisfy
//!   memory requests.
//! 
//! - When the initial buffer (if any) is exhausted, it obtains additional buffers
//!   from an upstream memory resource supplied at construction. Each additional
//!   buffer is larger than the previous one, following a geometric progression.
//! 
//! - It is intended for access from one thread of control at a time. Specifically,
//!   calls to allocate and deallocate do not synchronize with one another.
//! 
//! - It owns the allocated memory and frees it on destruction, even if deallocate has
//!   not been called for some of the allocated blocks.
class BOOST_CONTAINER_DECL monotonic_buffer_resource
   : public memory_resource
{
   block_slist       m_memory_blocks;
   void *            m_current_buffer;
   std::size_t       m_current_buffer_size;
   std::size_t       m_next_buffer_size;
   void * const      m_initial_buffer;
   std::size_t const m_initial_buffer_size;

   /// @cond
   void increase_next_buffer();
   void increase_next_buffer_at_least_to(std::size_t minimum_size);
   void *allocate_from_current(std::size_t aligner, std::size_t bytes);
   /// @endcond

   public:

   //! The number of bytes that will be requested by the default in the first call
   //! to the upstream allocator
   //!
   //! <b>Note</b>: Non-standard extension.
   static const std::size_t initial_next_buffer_size = 32u*sizeof(void*);

   //! <b>Requires</b>: `upstream` shall be the address of a valid memory resource or `nullptr`
   //!
   //! <b>Effects</b>: If `upstream` is not nullptr, sets the internal resource to `upstream`,
   //!   to get_default_resource() otherwise.
   //!   Sets the internal `current_buffer` to `nullptr` and the internal `next_buffer_size` to an
   //!   implementation-defined size.
   explicit monotonic_buffer_resource(memory_resource* upstream = 0) BOOST_NOEXCEPT;

   //! <b>Requires</b>: `upstream` shall be the address of a valid memory resource or `nullptr`
   //!   and `initial_size` shall be greater than zero.
   //!
   //! <b>Effects</b>: If `upstream` is not nullptr, sets the internal resource to `upstream`,
   //!   to get_default_resource() otherwise. Sets the internal `current_buffer` to `nullptr` and
   //!   `next_buffer_size` to at least `initial_size`.
   explicit monotonic_buffer_resource(std::size_t initial_size, memory_resource* upstream = 0) BOOST_NOEXCEPT;

   //! <b>Requires</b>: `upstream` shall be the address of a valid memory resource or `nullptr`,
   //!   `buffer_size` shall be no larger than the number of bytes in buffer.
   //!
   //! <b>Effects</b>: If `upstream` is not nullptr, sets the internal resource to `upstream`,
   //!   to get_default_resource() otherwise. Sets the internal `current_buffer` to `buffer`,
   //!   and `next_buffer_size` to `buffer_size` (but not less than an implementation-defined size),
   //!   then increases `next_buffer_size` by an implementation-defined growth factor (which need not be integral).
   monotonic_buffer_resource(void* buffer, std::size_t buffer_size, memory_resource* upstream = 0) BOOST_NOEXCEPT;

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   monotonic_buffer_resource(const monotonic_buffer_resource&) = delete;
   monotonic_buffer_resource operator=(const monotonic_buffer_resource&) = delete;
   #else
   private:
   monotonic_buffer_resource          (const monotonic_buffer_resource&);
   monotonic_buffer_resource operator=(const monotonic_buffer_resource&);
   public:
   #endif

   //! <b>Effects</b>: Calls
   //!   `this->release()`.
   virtual ~monotonic_buffer_resource();

   //! <b>Effects</b>: `upstream_resource()->deallocate()` as necessary to release all allocated memory.
   //!   [Note: memory is released back to `upstream_resource()` even if some blocks that were allocated
   //!   from this have not been deallocated from this. - end note]
   void release() BOOST_NOEXCEPT;

   //! <b>Returns</b>: The value of
   //!   the internal resource.
   memory_resource* upstream_resource() const BOOST_NOEXCEPT;

   //! <b>Returns</b>:
   //!   The number of bytes of storage available for the specified alignment and
   //!   the number of bytes wasted due to the requested alignment.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t remaining_storage(std::size_t alignment, std::size_t &wasted_due_to_alignment) const BOOST_NOEXCEPT;
   
   //! <b>Returns</b>:
   //!   The number of bytes of storage available for the specified alignment.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t remaining_storage(std::size_t alignment = 1u) const BOOST_NOEXCEPT;

   //! <b>Returns</b>:
   //!   The address pointing to the start of the current free storage.
   //!
   //! <b>Note</b>: Non-standard extension.
   const void *current_buffer() const BOOST_NOEXCEPT;

   //! <b>Returns</b>:
   //!   The number of bytes that will be requested for the next buffer once the
   //!   current one is exhausted.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t next_buffer_size() const BOOST_NOEXCEPT;

   protected:

   //! <b>Returns</b>: A pointer to allocated storage with a size of at least `bytes`. The size
   //!   and alignment of the allocated memory shall meet the requirements for a class derived
   //!   from `memory_resource`.
   //!
   //! <b>Effects</b>: If the unused space in the internal `current_buffer` can fit a block with the specified
   //!   bytes and alignment, then allocate the return block from the internal `current_buffer`; otherwise sets
   //!   the internal `current_buffer` to `upstream_resource()->allocate(n, m)`, where `n` is not less than
   //!   `max(bytes, next_buffer_size)` and `m` is not less than alignment, and increase
   //!   `next_buffer_size` by an implementation-defined growth factor (which need not be integral),
   //!   then allocate the return block from the newly-allocated internal `current_buffer`.
   //!
   //! <b>Throws</b>: Nothing unless `upstream_resource()->allocate()` throws.
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment);

   //! <b>Effects</b>: None
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Remarks</b>: Memory used by this resource increases monotonically until its destruction.
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) BOOST_NOEXCEPT;

   //! <b>Returns</b>:
   //!   `this == dynamic_cast<const monotonic_buffer_resource*>(&other)`.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_MONOTONIC_BUFFER_RESOURCE_HPP

/* monotonic_buffer_resource.hpp
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
*/