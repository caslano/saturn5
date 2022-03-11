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
   typedef typename AllocTraits::size_type  size_type;

   null_scoped_deallocator(pointer, Allocator&, size_type)
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

   scoped_array_deallocator(pointer p, Allocator& a, size_type length)
      : m_ptr(p), m_alloc(a), m_length(length) {}

   ~scoped_array_deallocator()
   {  if (m_ptr) m_alloc.deallocate(m_ptr, m_length);  }

   void release()
   {  m_ptr = 0; }

   private:
   pointer     m_ptr;
   Allocator&  m_alloc;
   size_type   m_length;
};

template <class Allocator>
struct null_scoped_array_deallocator
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;
   typedef typename AllocTraits::size_type  size_type;

   null_scoped_array_deallocator(pointer, Allocator&, size_type)
   {}

   void release()
   {}
};

template <class Allocator>
struct scoped_destroy_deallocator
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer    pointer;
   typedef typename AllocTraits::size_type  size_type;
   typedef dtl::integral_constant<unsigned,
      boost::container::dtl::
         version<Allocator>::value>                          alloc_version;

   scoped_destroy_deallocator(pointer p, Allocator& a)
      : m_ptr(p), m_alloc(a) {}

   ~scoped_destroy_deallocator()
   {
      if(m_ptr){
         AllocTraits::destroy(m_alloc, boost::movelib::to_raw_pointer(m_ptr));
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
   typedef typename AllocTraits::size_type  size_type;

   scoped_destructor_n(pointer p, Allocator& a, size_type n)
      : m_p(p), m_a(a), m_n(n)
   {}

   void release()
   {  m_p = 0; }

   void increment_size(size_type inc)
   {  m_n += inc;   }

   void increment_size_backwards(size_type inc)
   {  m_n += inc;   m_p -= inc;  }

   void shrink_forward(size_type inc)
   {  m_n -= inc;   m_p += inc;  }

   ~scoped_destructor_n()
   {
      if(!m_p) return;
      value_type *raw_ptr = boost::movelib::to_raw_pointer(m_p);
      while(m_n--){
         AllocTraits::destroy(m_a, raw_ptr++);
      }
   }

   private:
   pointer     m_p;
   Allocator & m_a;
   size_type   m_n;
};

//!A deleter for scoped_ptr that destroys
//!an object using a STL allocator.
template <class Allocator>
struct null_scoped_destructor_n
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   typedef typename AllocTraits::pointer pointer;
   typedef typename AllocTraits::size_type size_type;

   null_scoped_destructor_n(pointer, Allocator&, size_type)
   {}

   void increment_size(size_type)
   {}

   void increment_size_backwards(size_type)
   {}

   void shrink_forward(size_type)
   {}

   void release()
   {}
};

template<class Allocator>
class scoped_destructor
{
   typedef boost::container::allocator_traits<Allocator> AllocTraits;
   public:
   typedef typename Allocator::value_type value_type;
   scoped_destructor(Allocator &a, value_type *pv)
      : pv_(pv), a_(a)
   {}

   ~scoped_destructor()
   {
      if(pv_){
         AllocTraits::destroy(a_, pv_);
      }
   }

   void release()
   {  pv_ = 0; }


   void set(value_type *ptr) { pv_ = ptr; }

   value_type *get() const { return pv_; }

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
   value_destructor(Allocator &a, value_type &rv)
      : rv_(rv), a_(a)
   {}

   ~value_destructor()
   {
      AllocTraits::destroy(a_, &rv_);
   }

   private:
   value_type &rv_;
   Allocator &a_;
};

template <class Allocator>
class allocator_destroyer
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
   void priv_deallocate(const pointer &p, version_1)
   {  AllocTraits::deallocate(a_,p, 1); }

   void priv_deallocate(const pointer &p, version_2)
   {  a_.deallocate_one(p); }

   public:
   explicit allocator_destroyer(Allocator &a)
      : a_(a)
   {}

   void operator()(const pointer &p)
   {
      AllocTraits::destroy(a_, boost::movelib::to_raw_pointer(p));
      this->priv_deallocate(p, alloc_version());
   }
};

template <class Allocator>
class allocator_destroyer_and_chain_builder
{
   typedef allocator_traits<Allocator> allocator_traits_type;
   typedef typename allocator_traits_type::value_type value_type;
   typedef typename Allocator::multiallocation_chain    multiallocation_chain;

   Allocator & a_;
   multiallocation_chain &c_;

   public:
   allocator_destroyer_and_chain_builder(Allocator &a, multiallocation_chain &c)
      :  a_(a), c_(c)
   {}

   void operator()(const typename Allocator::pointer &p)
   {
      allocator_traits<Allocator>::destroy(a_, boost::movelib::to_raw_pointer(p));
      c_.push_back(p);
   }
};

template <class Allocator>
class allocator_multialloc_chain_node_deallocator
{
   typedef allocator_traits<Allocator> allocator_traits_type;
   typedef typename allocator_traits_type::value_type value_type;
   typedef typename Allocator::multiallocation_chain    multiallocation_chain;
   typedef allocator_destroyer_and_chain_builder<Allocator> chain_builder;

   Allocator & a_;
   multiallocation_chain c_;

   public:
   allocator_multialloc_chain_node_deallocator(Allocator &a)
      :  a_(a), c_()
   {}

   chain_builder get_chain_builder()
   {  return chain_builder(a_, c_);  }

   ~allocator_multialloc_chain_node_deallocator()
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