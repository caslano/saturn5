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
Hr0zvS++EjvwMUyusdb7bhVqrv4frAsZvvv8ZoNfZ40stuTkODLM0IV+o/Rm1Z8L8HupTDKVpLheN/q91ImE4J9/O97jp3Wn35/Nv1t4Ge/D45hp7CSSkr2Hrvix5vBcZj3sppTYc/Udnuu08p4/rSe9L/4yCt9bDNXpmfWyq1n99w8N8beI/S1kaXbF1ps+86h+4tw65Iy9f87Xh/6+cVHJHlUxQwEZ1uxL31OuGjqxbrFNKaHq83M/4+g7tynbHzSG6ckiv5v6u7V46VEaZiary3IuV5Jm4/sxWd+fvfSzi499csKkganJqjA7dWB+iPVvJslCf9iv9HvFmsp9JX/MNzKHWbzdwMHT1jY8UGz1e1uY9bdLHhih2rwQJo2l12JmQ19pW8AiyFyYZeaOUMBUZK7M4q/7dIVphNxfK/0Tim2qvZYMz8kJdlPtj3+yqwDLZJZIFu064C7MTIY905LtqHDSASaN+2kDyf4YfW8+TMVsEJlb3z+yYXqyaj/sN7IW1bY0hxnJ0Mtgsk9TYn6HFZBV/mFJZP/8L/o5TN7P3vrvIR9CdnDHOF9YyK/Wz3e/Ww/tm60wBRnuGb7ZJoemFpiKrBqza0uzU4ttmr2eDJ9nDbWbZv+pRvRTq8Vbc9+tX9Yf9WB7yOy+56RKHZmE/gczkuF6+Waqz8amsHyycGa973bJgMn7//ysazhZdq/wX4ot1V5BVvGHjbJLtW9xodAFFkeGGUaTtWvT8LHVEqyPh+/2S6s1obB0MnyX9c1M/6xqDjOQObFcjavTnWHryUqy3D9dnzyE5Qi5MiV878JyyXBvk0L255ycdJiFzJdZSI+GN2CSAXSfxWzepX5nYDIyd2bajJKrYAoy7MsYssCjqVeslmi9rr9bpzqnT8H6k+Hz+W/2Ymqn1TAdmTPLbZxbsQ5MT+bELemfXFg6WSCzC5GbH8OMzMaSjTkbcwxmIQtgpov7owTMSWtr3Vsv6AJTkPE118ck74dpBDu2rZInTC/YqnMz+sKyBOul/uMpzCRYiMeEcbAiwX5fHfQZJh9oa/U/PH4CUwn2398j98J0gk1+XFEGMwj2KChmPSxXsFDVfQMsX7DT5t/bw6SDhBn6lpsMiyDzZKatH/gJpibzZxZff5TVdGQuzCrPLn0KpieryGzf125nYTlkeE0dRzakbly0BP++ZjL9j2t+Fv07aEvf/9ABlv6b9Zr/blNjnw6B5TGbTTZyzqiKxZYwRDL4x2uVRKmcS78TP3qi/DLc20jJcE+UTvc2B4pGNsB9gYwM92Dz6b5gyeJbafhNt4rM88eaC+l+ySFhYiYsbjDuk4vN7tTG1qiXTobP4BdTPZfuqgOol0eG55AlVO/iXy5dYPlkTsyutKiWCCsi82KmLVnlMEyaZJvrfy2gN0xO5s3st3vdM2ARZPgO85vpSnRuD1OSVWI5zy76srDBQs71UlZLmI5MznI+LxL+gxmEPlfWj9gHyyILZNbEz+88zETG92zNqxOlYAVkFZj9WeODHiYbQtcEsx1N31SEhZIF8vnKN10FUws506eVF2FxZHxf6il+rQ5LF6x+N/1+WC6ZG7M7X7N3wExC7sMM91EwyVDbPTuUoZ8Ak5Lx3IgVdWNhSiHXSBLQHKYmC2cW+e+vOlgaWWlmo6ftsOYMQm56yIudMJOQ67Lw+FeYhSyM2fGvw/xgPjrrY/O7nVDFLYTJyfgZ3d0RHQJTkfH9rHW04WiYhozvi/F3XRlYGpknM/ccQzAsU8gd8FswD2YSbMzpgPYwyTB6fWfW0ze5CkxKxnOfrlZJhCnJXJnFlqvtBlOThTIrsfH3djA9GZ9hQm6bAzCDkLPPXXkNlkc=
*/