//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DESTROYERS_HPP
#define BOOST_CONTAINER_DESTROYERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/allocator_traits.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/detail/version_type.hpp>

namespace boost {
namespace container {
namespace dtl {

//!A deleter for scoped_ptr that deallocates the memory
//!allocated for an object using a STL allocator.
template <class Allocator>
struct scoped_deallocator
{
   typedef allocator_traits<Allocator> allocator_traits_type;
   typedef typename allocator_traits_type::pointer pointer;
   typedef dtl::integral_constant<unsigned,
      boost::container::dtl::
         version<Allocator>::value>                   alloc_version;

   private:
   void priv_deallocate(version_1)
   {  m_alloc.deallocate(m_ptr, 1); }

   void priv_deallocate(version_2)
   {  m_alloc.deallocate_one(m_ptr); }

   BOOST_MOVABLE_BUT_NOT_COPYABLE(scoped_deallocator)

   public:

   pointer     m_ptr;
   Allocator&  m_alloc;

   scoped_deallocator(pointer p, Allocator& a)
      : m_ptr(p), m_alloc(a)
   {}

   ~scoped_deallocator()
   {  if (m_ptr)priv_deallocate(alloc_version());  }

   scoped_deallocator(BOOST_RV_REF(scoped_deallocator) o)
      :  m_ptr(o.m_ptr), m_alloc(o.m_alloc)
   {  o.release();  }

   pointer get() const
   {  return m_ptr;  }

   void set(const pointer &p)
   {  m_ptr = p;  }

   void release()
   {  m_ptr = 0; }
};

template <class Allocator>
struct null_scoped_deallocator
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;

   null_scoped_deallocator(pointer, Allocator&, std::size_t)
   {}

   void release()
   {}

   pointer get() const
   {  return pointer();  }

   void set(const pointer &)
   {}
};

//!A deleter for scoped_ptr that deallocates the memory
//!allocated for an array of objects using a STL allocator.
template <class Allocator>
struct scoped_array_deallocator
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;
   typedef typename AllocTraits::size_type  size_type;

   scoped_array_deallocator(pointer p, Allocator& a, std::size_t length)
      : m_ptr(p), m_alloc(a), m_length(length) {}

   ~scoped_array_deallocator()
   {  if (m_ptr) m_alloc.deallocate(m_ptr, size_type(m_length));  }

   void release()
   {  m_ptr = 0; }

   private:
   pointer     m_ptr;
   Allocator&  m_alloc;
   std::size_t m_length;
};

template <class Allocator>
struct null_scoped_array_deallocator
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;

   null_scoped_array_deallocator(pointer, Allocator&, std::size_t)
   {}

   void release()
   {}
};

template <class Allocator>
struct scoped_node_destroy_deallocator
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;
   typedef dtl::integral_constant<unsigned,
      boost::container::dtl::
         version<Allocator>::value>                          alloc_version;

   scoped_node_destroy_deallocator(pointer p, Allocator& a)
      : m_ptr(p), m_alloc(a) {}

   ~scoped_node_destroy_deallocator()
   {
      if(m_ptr){
         boost::movelib::to_raw_pointer(m_ptr)->destructor(m_alloc);
         priv_deallocate(m_ptr, alloc_version());
      }
   }

   void release()
   {  m_ptr = 0; }

   private:

   void priv_deallocate(const pointer &p, version_1)
   {  AllocTraits::deallocate(m_alloc, p, 1); }

   void priv_deallocate(const pointer &p, version_2)
   {  m_alloc.deallocate_one(p); }

   pointer     m_ptr;
   Allocator&  m_alloc;
};


//!A deleter for scoped_ptr that destroys
//!an object using a STL allocator.
template <class Allocator>
struct scoped_destructor_n
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;
   typedef typename AllocTraits::value_type value_type;

   BOOST_CONTAINER_FORCEINLINE scoped_destructor_n(pointer p, Allocator& a, std::size_t n)
      : m_p(p), m_a(a), m_n(n)
   {}

   BOOST_CONTAINER_FORCEINLINE void release()
   {  m_p = 0; m_n = 0; }

   BOOST_CONTAINER_FORCEINLINE void increment_size(std::size_t inc)
   {  m_n += inc;   }

   BOOST_CONTAINER_FORCEINLINE void increment_size_backwards(std::size_t inc)
   {  m_n += inc;   m_p -= std::ptrdiff_t(inc);  }

   BOOST_CONTAINER_FORCEINLINE void shrink_forward(std::size_t inc)
   {  m_n -= inc;   m_p += std::ptrdiff_t(inc);  }

   ~scoped_destructor_n()
   {
      if(m_n){
         value_type *raw_ptr = boost::movelib::to_raw_pointer(m_p);
         do {
            --m_n;
            AllocTraits::destroy(m_a, raw_ptr);
            ++raw_ptr;
         } while(m_n);
      }
   }

   private:
   pointer     m_p;
   Allocator & m_a;
   std::size_t m_n;
};

//!A deleter for scoped_ptr that destroys
//!an object using a STL allocator.
template <class Allocator>
struct null_scoped_destructor_n
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer pointer;

   BOOST_CONTAINER_FORCEINLINE null_scoped_destructor_n(pointer, Allocator&, std::size_t)
   {}

   BOOST_CONTAINER_FORCEINLINE void increment_size(std::size_t)
   {}

   BOOST_CONTAINER_FORCEINLINE void increment_size_backwards(std::size_t)
   {}

   BOOST_CONTAINER_FORCEINLINE void shrink_forward(std::size_t)
   {}

   BOOST_CONTAINER_FORCEINLINE void release()
   {}
};


//!A deleter for scoped_ptr that destroys
//!an object using a STL allocator.
template <class Allocator>
struct scoped_destructor_range
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;
   typedef typename AllocTraits::value_type value_type;
   
   BOOST_CONTAINER_FORCEINLINE scoped_destructor_range(pointer p, pointer e, Allocator& a)
      : m_p(p), m_e(e), m_a(a)
   {}

   BOOST_CONTAINER_FORCEINLINE void release()
   {  m_p = pointer(); m_e = pointer(); }

   BOOST_CONTAINER_FORCEINLINE void set_end(pointer e)
   {  m_e = e;   }

   BOOST_CONTAINER_FORCEINLINE void set_begin(pointer b)
   {  m_p = b;  }

   BOOST_CONTAINER_FORCEINLINE void set_range(pointer b, pointer e)
   {  m_p = b; m_e = e;   }

   ~scoped_destructor_range()
   {
      while(m_p != m_e){
         value_type *raw_ptr = boost::movelib::to_raw_pointer(m_p);
         AllocTraits::destroy(m_a, raw_ptr);
         ++m_p;
      }
   }

   private:
   pointer     m_p;
   pointer     m_e;
   Allocator & m_a;
};

//!A deleter for scoped_ptr that destroys
//!an object using a STL allocator.
template <class Allocator>
struct null_scoped_destructor_range
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer pointer;

   BOOST_CONTAINER_FORCEINLINE null_scoped_destructor_range(pointer, pointer, Allocator&)
   {}

   BOOST_CONTAINER_FORCEINLINE void release()
   {}

   BOOST_CONTAINER_FORCEINLINE void set_end(pointer)
   {}

   BOOST_CONTAINER_FORCEINLINE void set_begin(pointer)
   {}

   BOOST_CONTAINER_FORCEINLINE void set_range(pointer, pointer)
   {}
};


template<class Allocator>
class scoped_destructor
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   public:
   typedef typename Allocator::value_type value_type;
   BOOST_CONTAINER_FORCEINLINE scoped_destructor(Allocator &a, value_type *pv)
      : pv_(pv), a_(a)
   {}

   BOOST_CONTAINER_FORCEINLINE ~scoped_destructor()
   {
      if(pv_){
         AllocTraits::destroy(a_, pv_);
      }
   }

   BOOST_CONTAINER_FORCEINLINE void release()
   {  pv_ = 0; }


   BOOST_CONTAINER_FORCEINLINE void set(value_type *ptr) { pv_ = ptr; }

   BOOST_CONTAINER_FORCEINLINE value_type *get() const { return pv_; }

   private:
   value_type *pv_;
   Allocator &a_;
};


template<class Allocator, class Value = typename Allocator::value_type>
class value_destructor
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   public:
   typedef Value value_type;
   BOOST_CONTAINER_FORCEINLINE value_destructor(Allocator &a, value_type &rv)
      : rv_(rv), a_(a)
   {}

   BOOST_CONTAINER_FORCEINLINE ~value_destructor()
   {
      AllocTraits::destroy(a_, &rv_);
   }

   private:
   value_type &rv_;
   Allocator &a_;
};

template <class Allocator>
class allocator_node_destroyer
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::value_type value_type;
   typedef typename AllocTraits::pointer    pointer;
   typedef dtl::integral_constant<unsigned,
      boost::container::dtl::
         version<Allocator>::value>                           alloc_version;

   private:
   Allocator & a_;

   private:
   BOOST_CONTAINER_FORCEINLINE void priv_deallocate(const pointer &p, version_1)
   {  AllocTraits::deallocate(a_,p, 1); }

   BOOST_CONTAINER_FORCEINLINE void priv_deallocate(const pointer &p, version_2)
   {  a_.deallocate_one(p); }

   public:
   BOOST_CONTAINER_FORCEINLINE explicit allocator_node_destroyer(Allocator &a)
      : a_(a)
   {}

   BOOST_CONTAINER_FORCEINLINE void operator()(const pointer &p)
   {
      boost::movelib::to_raw_pointer(p)->destructor(a_);
      this->priv_deallocate(p, alloc_version());
   }
};

template<class Allocator>
class scoped_node_destructor
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   public:
   typedef typename Allocator::value_type value_type;
   BOOST_CONTAINER_FORCEINLINE scoped_node_destructor(Allocator &a, value_type *pv)
      : pv_(pv), a_(a)
   {}

   BOOST_CONTAINER_FORCEINLINE ~scoped_node_destructor()
   {
      if(pv_){
         pv_->destructor(a_);
      }
   }

   BOOST_CONTAINER_FORCEINLINE void release()
   {  pv_ = 0; }


   BOOST_CONTAINER_FORCEINLINE void set(value_type *ptr) { pv_ = ptr; }

   BOOST_CONTAINER_FORCEINLINE value_type *get() const { return pv_; }

   private:
   value_type *pv_;
   Allocator &a_;
};



template <class Allocator>
class allocator_node_destroyer_and_chain_builder
{
   typedef allocator_traits<Allocator> allocator_traits_type;
   typedef typename allocator_traits_type::value_type value_type;
   typedef typename Allocator::multiallocation_chain    multiallocation_chain;

   Allocator & a_;
   multiallocation_chain &c_;

   public:
   BOOST_CONTAINER_FORCEINLINE allocator_node_destroyer_and_chain_builder(Allocator &a, multiallocation_chain &c)
      :  a_(a), c_(c)
   {}

   BOOST_CONTAINER_FORCEINLINE void operator()(const typename Allocator::pointer &p)
   {
      boost::movelib::to_raw_pointer(p)->destructor(a_);
      c_.push_back(p);
   }
};

template <class Allocator>
class allocator_multialloc_chain_node_deallocator
{
   typedef allocator_traits<Allocator> allocator_traits_type;
   typedef typename allocator_traits_type::value_type value_type;
   typedef typename Allocator::multiallocation_chain    multiallocation_chain;
   typedef allocator_node_destroyer_and_chain_builder<Allocator> chain_builder;

   Allocator & a_;
   multiallocation_chain c_;

   public:
   BOOST_CONTAINER_FORCEINLINE allocator_multialloc_chain_node_deallocator(Allocator &a)
      :  a_(a), c_()
   {}

   BOOST_CONTAINER_FORCEINLINE chain_builder get_chain_builder()
   {  return chain_builder(a_, c_);  }

   BOOST_CONTAINER_FORCEINLINE ~allocator_multialloc_chain_node_deallocator()
   {
      a_.deallocate_individual(c_);
   }
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DESTROYERS_HPP

/* destroyers.hpp
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
*/