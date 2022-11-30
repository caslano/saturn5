//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_BLOCK_SLIST_HEADER
#define BOOST_CONTAINER_DETAIL_BLOCK_SLIST_HEADER

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif


#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/throw_exception.hpp>
#include <boost/container/detail/placement_new.hpp>

#include <boost/move/detail/type_traits.hpp>
#include <boost/intrusive/linear_slist_algorithms.hpp>
#include <boost/assert.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

struct slist_node
{
   slist_node *next;
};

struct slist_node_traits
{
   typedef slist_node         node;
   typedef slist_node*        node_ptr;
   typedef const slist_node*  const_node_ptr;

   static node_ptr get_next(const_node_ptr n)
   {  return n->next;  }

   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->next = next;  }
};

struct block_slist_header
   : public slist_node
{
   std::size_t size;
};

typedef bi::linear_slist_algorithms<slist_node_traits> slist_algo;

template<class DerivedFromBlockSlistHeader = block_slist_header>
class block_slist_base
{
   slist_node m_slist;

   static const std::size_t MaxAlignMinus1 = memory_resource::max_align-1u;

   public:

   static const std::size_t header_size = std::size_t(sizeof(DerivedFromBlockSlistHeader) + MaxAlignMinus1) & std::size_t(~MaxAlignMinus1);

   explicit block_slist_base()
   {  slist_algo::init_header(&m_slist);  }

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   block_slist_base(const block_slist_base&) = delete;
   block_slist_base operator=(const block_slist_base&) = delete;
   #else
   private:
   block_slist_base          (const block_slist_base&);
   block_slist_base operator=(const block_slist_base&);
   public:
   #endif

   ~block_slist_base()
   {}

   void *allocate(std::size_t size, memory_resource &mr)
   {
      if((size_t(-1) - header_size) < size)
         throw_bad_alloc();
      void *p = mr.allocate(size+header_size);
      block_slist_header &mb  = *::new((void*)p, boost_container_new_t()) DerivedFromBlockSlistHeader;
      mb.size = size+header_size;
      slist_algo::link_after(&m_slist, &mb);
      return (char *)p + header_size;
   }

   void release(memory_resource &mr) BOOST_NOEXCEPT
   {
      slist_node *n = slist_algo::node_traits::get_next(&m_slist);
      while(n){
         DerivedFromBlockSlistHeader &d = static_cast<DerivedFromBlockSlistHeader&>(*n);
         n = slist_algo::node_traits::get_next(n);
         std::size_t size = d.block_slist_header::size;
         d.~DerivedFromBlockSlistHeader();
         mr.deallocate(reinterpret_cast<char*>(&d), size, memory_resource::max_align);         
      }
      slist_algo::init_header(&m_slist);
   }
};

class block_slist
   : public block_slist_base<>
{
   memory_resource &m_upstream_rsrc;

   public:

   explicit block_slist(memory_resource &upstream_rsrc)
      : block_slist_base<>(), m_upstream_rsrc(upstream_rsrc)
   {}

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   block_slist(const block_slist&) = delete;
   block_slist operator=(const block_slist&) = delete;
   #else
   private:
   block_slist          (const block_slist&);
   block_slist operator=(const block_slist&);
   public:
   #endif

   ~block_slist()
   {  this->release();  }

   void *allocate(std::size_t size)
   {  return this->block_slist_base<>::allocate(size, m_upstream_rsrc);  }

   void release() BOOST_NOEXCEPT
   {  return this->block_slist_base<>::release(m_upstream_rsrc);  }

   memory_resource& upstream_resource() const BOOST_NOEXCEPT
   {  return m_upstream_rsrc;   }
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_BLOCK_SLIST_HEADER

/* block_slist.hpp
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
*/