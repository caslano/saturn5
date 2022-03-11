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