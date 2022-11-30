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
   ~monotonic_buffer_resource() BOOST_OVERRIDE;

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
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment) BOOST_OVERRIDE;

   //! <b>Effects</b>: None
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Remarks</b>: Memory used by this resource increases monotonically until its destruction.
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) BOOST_NOEXCEPT BOOST_OVERRIDE;

   //! <b>Returns</b>:
   //!   `this == dynamic_cast<const monotonic_buffer_resource*>(&other)`.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT BOOST_OVERRIDE;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_MONOTONIC_BUFFER_RESOURCE_HPP

/* monotonic_buffer_resource.hpp
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
*/