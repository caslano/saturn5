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
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment) BOOST_OVERRIDE
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
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) BOOST_OVERRIDE
   {
      if (alignment <= priv_guaranteed_allocator_alignment())
         this->ebo_alloc_t::get().deallocate((char*)p, bytes);
      else
         this->priv_aligned_dealloc(p, bytes, alignment);
   }

   //! Let p be dynamic_cast<const resource_adaptor_imp*>(&other).
   //!
   //! <b>Returns</b>: false if p is null, otherwise the value of m_alloc == p->m_alloc.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT BOOST_OVERRIDE
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