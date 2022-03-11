//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_RESOURCE_ADAPTOR_HPP
#define BOOST_CONTAINER_PMR_RESOURCE_ADAPTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>

#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <boost/container/detail/std_fwd.hpp>

#include <cstring>

namespace boost {
namespace container {

namespace pmr_dtl {

template<class T>
struct max_allocator_alignment
{
   static const std::size_t value = 1;
};

template<class T>
struct max_allocator_alignment< ::boost::container::new_allocator<T> >
{
   static const std::size_t value = boost::move_detail::alignment_of<boost::move_detail::max_align_t>::value;
};

template<class T>
struct max_allocator_alignment< std::allocator<T> >
{
   static const std::size_t value = boost::move_detail::alignment_of<boost::move_detail::max_align_t>::value;
};

}  //namespace pmr_dtl

namespace pmr {

//! An instance of resource_adaptor<Allocator> is an adaptor that wraps a memory_resource interface
//! around Allocator. In order that resource_adaptor<X<T>> and resource_adaptor<X<U>> are the same
//! type for any allocator template X and types T and U, resource_adaptor<Allocator> is rendered as
//! an alias to this class template such that Allocator is rebound to a char value type in every
//! specialization of the class template. The requirements on this class template are defined below.
//! In addition to the Allocator requirements, the parameter to resource_adaptor shall meet
//! the following additional requirements:
//!
//! - `typename allocator_traits<Allocator>:: pointer` shall be identical to
//!   `typename allocator_traits<Allocator>:: value_type*`.
//!
//! - `typename allocator_traits<Allocator>:: const_pointer` shall be identical to
//!   `typename allocator_traits<Allocator>:: value_type const*`.
//!
//! - `typename allocator_traits<Allocator>:: void_pointer` shall be identical to `void*`.
//!
//! - `typename allocator_traits<Allocator>:: const_void_pointer` shall be identical to `void const*`.
template <class Allocator>
class resource_adaptor_imp
   : public  memory_resource
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   , private ::boost::intrusive::detail::ebo_functor_holder<Allocator>
   #endif
{
   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
   Allocator m_alloc;
   #else
   BOOST_COPYABLE_AND_MOVABLE(resource_adaptor_imp)
   typedef ::boost::intrusive::detail::ebo_functor_holder<Allocator> ebo_alloc_t;
   void static_assert_if_not_char_allocator() const
   {
      //This class can only be used with allocators type char
      BOOST_STATIC_ASSERT((boost::container::dtl::is_same<typename Allocator::value_type, char>::value));
   }
   #endif

   public:
   typedef Allocator allocator_type;

   //! <b>Effects</b>: Default constructs
   //!   m_alloc.
   resource_adaptor_imp()
   {  this->static_assert_if_not_char_allocator(); }

   //! <b>Effects</b>: Copy constructs
   //!   m_alloc.
   resource_adaptor_imp(const resource_adaptor_imp &other)
      : ebo_alloc_t(other.ebo_alloc_t::get())
   {}

   //! <b>Effects</b>: Move constructs
   //!   m_alloc.
   resource_adaptor_imp(BOOST_RV_REF(resource_adaptor_imp) other)
      : ebo_alloc_t(::boost::move(other.get()))
   {}

   //! <b>Effects</b>: Initializes m_alloc with
   //!   a2.
   explicit resource_adaptor_imp(const Allocator& a2)
      : ebo_alloc_t(a2)
   {  this->static_assert_if_not_char_allocator(); }

   //! <b>Effects</b>: Initializes m_alloc with
   //!   a2.
   explicit resource_adaptor_imp(BOOST_RV_REF(Allocator) a2)
      : ebo_alloc_t(::boost::move(a2))
   {  this->static_assert_if_not_char_allocator(); }

   //! <b>Effects</b>: Copy assigns
   //!   m_alloc.
   resource_adaptor_imp& operator=(BOOST_COPY_ASSIGN_REF(resource_adaptor_imp) other)
   {  this->ebo_alloc_t::get() = other.ebo_alloc_t::get(); return *this;  }

   //! <b>Effects</b>: Move assigns
   //!   m_alloc.
   resource_adaptor_imp& operator=(BOOST_RV_REF(resource_adaptor_imp) other)
   {  this->ebo_alloc_t::get() = ::boost::move(other.ebo_alloc_t::get()); return *this;  }

   //! <b>Effects</b>: Returns m_alloc.
   allocator_type &get_allocator()
   {  return this->ebo_alloc_t::get(); }

   //! <b>Effects</b>: Returns m_alloc.
   const allocator_type &get_allocator() const
   {  return this->ebo_alloc_t::get(); }

   protected:
   //! <b>Returns</b>: Allocated memory obtained by calling m_alloc.allocate. The size and alignment
   //!   of the allocated memory shall meet the requirements for a class derived from memory_resource.
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment)
   {
      if (alignment <= priv_guaranteed_allocator_alignment())
         return this->ebo_alloc_t::get().allocate(bytes);
      else
         return this->priv_aligned_alloc(bytes, alignment);
   }

   //! <b>Requires</b>: p was previously allocated using A.allocate, where A == m_alloc, and not
   //!   subsequently deallocated. 
   //!
   //! <b>Effects</b>: Returns memory to the allocator using m_alloc.deallocate().
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment)
   {
      if (alignment <= priv_guaranteed_allocator_alignment())
         this->ebo_alloc_t::get().deallocate((char*)p, bytes);
      else
         this->priv_aligned_dealloc(p, bytes, alignment);
   }

   //! Let p be dynamic_cast<const resource_adaptor_imp*>(&other).
   //!
   //! <b>Returns</b>: false if p is null, otherwise the value of m_alloc == p->m_alloc.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT
   {
      const resource_adaptor_imp* p = dynamic_cast<const resource_adaptor_imp*>(&other);
      return p && p->ebo_alloc_t::get() == this->ebo_alloc_t::get();
   }

   private:
   void * priv_aligned_alloc(std::size_t bytes, std::size_t alignment)
   {
      //Allocate space for requested bytes, plus alignment, plus bookeeping data
      void *const p = this->ebo_alloc_t::get().allocate(bytes + priv_extra_bytes_for_overalignment(alignment));

      if (0 != p) {
         //Obtain the aligned address after the bookeeping data
         void *const aligned_ptr = (void*)(((std::size_t)p + priv_extra_bytes_for_overalignment(alignment)) & ~(alignment - 1));

         //Store bookeeping data. Use memcpy as the underlying memory might be unaligned for
         //a pointer (e.g. 2 byte alignment in 32 bit, 4 byte alignment in 64 bit)
         std::memcpy(priv_bookeeping_addr_from_aligned_ptr(aligned_ptr), &p, sizeof(p));
         return aligned_ptr;
      }
      return 0;
   }

   void priv_aligned_dealloc(void *aligned_ptr, std::size_t bytes, std::size_t alignment)
   {
      //Obtain bookeeping data
      void *p;
      std::memcpy(&p, priv_bookeeping_addr_from_aligned_ptr(aligned_ptr), sizeof(p));
      std::size_t s  = bytes + priv_extra_bytes_for_overalignment(alignment);
      this->ebo_alloc_t::get().deallocate((char*)p, s);
   }

   static BOOST_CONTAINER_FORCEINLINE void *priv_bookeeping_addr_from_aligned_ptr(void *aligned_ptr)
   {
      return reinterpret_cast<void*>(reinterpret_cast<std::size_t>(aligned_ptr) - sizeof(void*));
   }

   BOOST_CONTAINER_FORCEINLINE static std::size_t priv_extra_bytes_for_overalignment(std::size_t alignment)
   {
      return alignment - 1 + sizeof(void*);
   }

   BOOST_CONTAINER_FORCEINLINE static std::size_t priv_guaranteed_allocator_alignment()
   {
      return pmr_dtl::max_allocator_alignment<Allocator>::value;
   }
};

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

//! `resource_adaptor<Allocator>` is rendered as an alias to resource_adaptor_imp class template
//! such that Allocator is rebound to a char value type.
template <class Allocator>
using resource_adaptor = resource_adaptor_imp
   <typename allocator_traits<Allocator>::template rebind_alloc<char> >;

#else

template <class Allocator>
class resource_adaptor
   : public resource_adaptor_imp
      <typename allocator_traits<Allocator>::template portable_rebind_alloc<char>::type>
{
   typedef resource_adaptor_imp
      <typename allocator_traits<Allocator>::template portable_rebind_alloc<char>::type> base_t;

   BOOST_COPYABLE_AND_MOVABLE(resource_adaptor)

   public:
   resource_adaptor()
      : base_t()
   {}

   resource_adaptor(const resource_adaptor &other)
      : base_t(other)
   {}

   resource_adaptor(BOOST_RV_REF(resource_adaptor) other)
      : base_t(BOOST_MOVE_BASE(base_t, other))
   {}

   explicit resource_adaptor(const Allocator& a2)
      : base_t(a2)
   {}

   explicit resource_adaptor(BOOST_RV_REF(Allocator) a2)
      : base_t(::boost::move(a2))
   {}

   resource_adaptor& operator=(BOOST_COPY_ASSIGN_REF(resource_adaptor) other)
   {  return static_cast<resource_adaptor&>(this->base_t::operator=(other));  }

   resource_adaptor& operator=(BOOST_RV_REF(resource_adaptor) other)
   {  return static_cast<resource_adaptor&>(this->base_t::operator=(BOOST_MOVE_BASE(base_t, other)));  }

   //get_allocator and protected functions are properly inherited
};

#endif

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_RESOURCE_ADAPTOR_HPP

/* resource_adaptor.hpp
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
*/