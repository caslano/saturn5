//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_BLOCK_LIST_HEADER
#define BOOST_CONTAINER_DETAIL_BLOCK_LIST_HEADER

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
#include <boost/intrusive/circular_list_algorithms.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <boost/assert.hpp>
#include <boost/container/detail/placement_new.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

struct list_node
{
   list_node *next;
   list_node *previous;
};

struct list_node_traits
{
   typedef list_node         node;
   typedef list_node*        node_ptr;
   typedef const list_node*  const_node_ptr;

   static node_ptr get_next(const_node_ptr n)
   {  return n->next;  }

   static node_ptr get_previous(const_node_ptr n)
   {  return n->previous;  }

   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->next = next;  }

   static void set_previous(const node_ptr & n, const node_ptr & previous)
   {  n->previous = previous;  }
};

struct block_list_header
   : public list_node
{
   std::size_t size;
};

typedef bi::circular_list_algorithms<list_node_traits> list_algo;


template<class DerivedFromBlockListHeader = block_list_header>
class block_list_base
{
   list_node m_list;

   static const std::size_t MaxAlignMinus1 = memory_resource::max_align-1u;

   public:

   static const std::size_t header_size = std::size_t(sizeof(DerivedFromBlockListHeader) + MaxAlignMinus1) & std::size_t(~MaxAlignMinus1);

   explicit block_list_base()
   {  list_algo::init_header(&m_list);  }

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   block_list_base(const block_list_base&) = delete;
   block_list_base operator=(const block_list_base&) = delete;
   #else
   private:
   block_list_base          (const block_list_base&);
   block_list_base operator=(const block_list_base&);
   public:
   #endif

   ~block_list_base()
   {}

   void *allocate(std::size_t size, memory_resource &mr)
   {
      if((size_t(-1) - header_size) < size)
         throw_bad_alloc();
      void *p = mr.allocate(size+header_size);
      block_list_header &mb  = *::new((void*)p, boost_container_new_t()) DerivedFromBlockListHeader;
      mb.size = size+header_size;
      list_algo::link_after(&m_list, &mb);
      return (char *)p + header_size;
   }

   void deallocate(void *p, memory_resource &mr) BOOST_NOEXCEPT
   {
      DerivedFromBlockListHeader *pheader = static_cast<DerivedFromBlockListHeader*>
         (static_cast<void*>((char*)p - header_size));
      list_algo::unlink(pheader);
      const std::size_t size = pheader->size;
      static_cast<DerivedFromBlockListHeader*>(pheader)->~DerivedFromBlockListHeader();
      mr.deallocate(pheader, size, memory_resource::max_align);
   }

   void release(memory_resource &mr) BOOST_NOEXCEPT
   {
      list_node *n = list_algo::node_traits::get_next(&m_list);
      while(n != &m_list){
         DerivedFromBlockListHeader &d = static_cast<DerivedFromBlockListHeader&>(*n);
         n = list_algo::node_traits::get_next(n);
         std::size_t size = d.size;
         d.~DerivedFromBlockListHeader();
         mr.deallocate(reinterpret_cast<char*>(&d), size, memory_resource::max_align);         
      }
      list_algo::init_header(&m_list);
   }
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_BLOCK_LIST_HEADER

/* block_list.hpp
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
*/