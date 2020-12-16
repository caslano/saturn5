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
+FXR6Gefreh3F2tqxn7Fvkia2Es0kmJrTftyKdO+Z7EpaurI0Euk3XCtvPxINUyutO71d1ttnyGDqckqMFuzaNFlfM6uJzP+qKey+3XknuQZf1rfxzXHvb5aGUUzfO1fYjxML5hizh/ncEaZZJgvmv55bsGtKJyRruXP+WLI+myfUaLYkoZbyEw/rB2dw8Q997tbrZV1P7/bwtu6TjBZa3tJY2a9Rkd9Kbbh2jgy3Je3txteq8jeYIQZyJyZjXOeXAjLInNl1rx0x4Ji0yUY2Zod7KorbkqDe8AKyHTF+/LdkmsMewbTt7GXqJjN6HtvKcxMVp2tOSL28RmYNNJeUoVZTMsS8TAlWRizv58Oy8NzQQoZXnPUdr3j06fdcoGlk7kx87j81hOWKeTO+xeOhxnJpMzmvWjyHmYSbFBKWlVYvmBvdkzIhElU9HkBs/oVbh+CycjKMuutXT0dFkHmySwiu05dmJrMl5nUeU8vmI6Mz9dz68LNsDShl5WjSpyGZZL5MNvnvnYXzChYpxez7GAmsiBmO/xHRsOKhNyS99NyYdIo2178blQJhoUK5ho4LAqmJONrFp3wy4FphNyFtIcJMB2ZNzNFy1rnYWlkrsxe7dYPghnI3JhdHGc3HZZFxs/9Yb2162G5ZPyMUvpsGAezCL00n7LZekZFZPz8vCu1bgGTtrW1spsXFMFCBfOq92c7mJLMj1nVqn9bYHFkXrze1QAlLIWsDLPWjwtMMAOZJ7NF2q9hsBzB2jaIawnLE9bs1nLvLlg+Gd+z+Kb9LsCcom33Oq/nWSNMTsZzpo0Ph8GUZHz2DrWCa8HiyHif1ZP+nANLIeN93mu6MwhmEOqpCv8aATMKa749cSYEZiLje115QOoWWL6wpnNqgRzmFGN7vaQpvubA5GR8zYQh7x/AImKE6zPL39qLmozX+2dc/xMwHZkbs6jfZ9aH6YV6Ix+/84MZyMoym5VaLRFmJHNntnTs2YawPGG+3r6+92AWYYYSYbd2wYqEGSp4ObaDydrR/QuzpgMSusIiyAKZzU+6bZ0vjoz3uXPoLHeYjoz30lj9NQWWRubK7MvaTy4wAxmfb9RQR2u9HLIyzCaMfBAPM5H5MXv/5tE5WIFglm1lW8Ok7W1nSGoiXQGTk/Hzm2L+NBwWQVaaWfB9ZUWYiozvdX3t3CowLRmf/ZcNpVJhKWT+zG5KNIUwA1lZZsPOn+gOM5KV4fNtn1MfZiZzYebu1qo8LF/os8q54HMwpw72kmBmoQcvP4cpyCowS46YfRimIfNhNnh0aCxMR8brxUU6Xoalk8mYLV12oRYsh4zPF5CR8xFmEtZM/S/TerYFZN7Mws9mnIY5qW37nKT5mAuTk/Fcz1oVnWERZPyMppasvhymIeO9PEty2ABLIeMzVJv93B5mIPNitt0QfROWI9iYejVuw/LIPJgNDCl/HGYR6h1Uh+XBJB1tr6UOneI1MDkZn8FL+vM+S0nmzmzDu/9awtRkLsxmjFqaAIsj82S2vl3idVgKWRiztiveWWfIIfNjttBjSRbMRBbE7OngRa1gRUJOutzfApN1srXlT4NiYBFk/Nz3b3F9BlOTefCzVW+cCdMKlrDha3+Ynoyfw8Pr3R1hmYKNnHPY2kuu0MsMt/aJMLOQ0/1SEAYrIgthNjxvViVYaGfbs82erKwCU5EFMgufu/AdTEcmZXa75dbdsDSyCszs35+fBssh431G7t3aHWYSbKXP9bGwAjJ+RgXe739Y72Rpl5/vuTrazbJv96FfVZiKLJyZy52wgzA9WVVmFy6r8opN28/I1uxEf4836NPsEbACskrMxr5xKAOTd7W1gZ/Ms/C+X02m+fE=
*/