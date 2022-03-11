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