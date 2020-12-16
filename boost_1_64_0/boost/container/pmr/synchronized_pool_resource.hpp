//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SYNCHRONIZED_POOL_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_SYNCHRONIZED_POOL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/detail/pool_resource.hpp>
#include <boost/container/detail/thread_mutex.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! A synchronized_pool_resource is a general-purpose memory resources having
//! the following qualities:
//!
//! - Each resource owns the allocated memory, and frees it on destruction,
//!   even if deallocate has not been called for some of the allocated blocks.
//!
//! - A pool resource consists of a collection of pools, serving
//!   requests for different block sizes. Each individual pool manages a
//!   collection of chunks that are in turn divided into blocks of uniform size,
//!   returned via calls to do_allocate. Each call to do_allocate(size, alignment)
//!   is dispatched to the pool serving the smallest blocks accommodating at
//!   least size bytes.
//!
//! - When a particular pool is exhausted, allocating a block from that pool
//!   results in the allocation of an additional chunk of memory from the upstream
//!   allocator (supplied at construction), thus replenishing the pool. With
//!   each successive replenishment, the chunk size obtained increases
//!   geometrically. [ Note: By allocating memory in chunks, the pooling strategy
//!   increases the chance that consecutive allocations will be close together
//!   in memory. - end note ]
//!
//! - Allocation requests that exceed the largest block size of any pool are
//!   fulfilled directly from the upstream allocator.
//!
//! - A pool_options struct may be passed to the pool resource constructors to
//!   tune the largest block size and the maximum chunk size.
//!
//! A synchronized_pool_resource may be accessed from multiple threads without
//! external synchronization and may have thread-specific pools to reduce
//! synchronization costs.
class BOOST_CONTAINER_DECL synchronized_pool_resource
   : public memory_resource
{
   dtl::thread_mutex m_mut;
   pool_resource     m_pool_resource;

   public:

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource(const pool_options&,memory_resource*)
   synchronized_pool_resource(const pool_options& opts, memory_resource* upstream) BOOST_NOEXCEPT;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource()
   synchronized_pool_resource() BOOST_NOEXCEPT;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource(memory_resource*)
   explicit synchronized_pool_resource(memory_resource* upstream) BOOST_NOEXCEPT;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource(const pool_options&)
   explicit synchronized_pool_resource(const pool_options& opts) BOOST_NOEXCEPT;

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   synchronized_pool_resource(const synchronized_pool_resource&) = delete;
   synchronized_pool_resource operator=(const synchronized_pool_resource&) = delete;
   #else
   private:
   synchronized_pool_resource          (const synchronized_pool_resource&);
   synchronized_pool_resource operator=(const synchronized_pool_resource&);
   public:
   #endif

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::~unsynchronized_pool_resource()
   virtual ~synchronized_pool_resource();

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::release()
   void release();

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::upstream_resource()const
   memory_resource* upstream_resource() const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::options()const
   pool_options options() const;

   protected:

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::do_allocate()
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment);

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::do_deallocate(void*,std::size_t,std::size_t)
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment);

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::do_is_equal(const memory_resource&)const
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT;

   //Non-standard observers
   public:
   
   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_count()
   std::size_t pool_count() const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_index(std::size_t)const
   std::size_t pool_index(std::size_t bytes) const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_next_blocks_per_chunk(std::size_t)const
   std::size_t pool_next_blocks_per_chunk(std::size_t pool_idx) const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_block(std::size_t)const
   std::size_t pool_block(std::size_t pool_idx) const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_cached_blocks(std::size_t)const
   std::size_t pool_cached_blocks(std::size_t pool_idx) const;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_SYNCHRONIZED_POOL_RESOURCE_HPP

/* synchronized_pool_resource.hpp
F/no71NELXybVRfY5vn8HvGf1F0FcCxFED2kKj8fCBLcJTgEYri7uxM4Lnub5Phn3F74wd2tcHf3opDCpXAt3AunKLTwgqKQ7ux2rjN/dnd6dpMUFHv3czvdr7unp6dHdnatcvT64QetYfumZDgzTRDOayWYAxqU7wEDPjQmYvyCeaeAJ9UDtz3IpGIANmGQ/CirbM69YqkH9a9Ubv0S8Zf7xhyWMsTtXfiwiPzIpsjTbO8C9WOU+1M7521kqebwXBR4AibxJXmonSNvsh+vb+SDPH1eVO+3FZFHWF1H+5Oa7xxeTGdPwHbA55o2lInsa15nSeYOFikiVnyeJ9Hl22l2vqfqQTRwD+jidXlwmqpLMj1OstRDgrFHChizzhqPs9wIjj1GNH+4d2ByPeIwnrbESNI+zj9Q3j5M6sM9UF4fhKvqsxmjRfzuA7WxDfB4fOPykKzx8X/mAyk+me3vkuztilv/f7WAuGbr/3F6XFlIrofEd8sFO9+VYKw3ARizTwDGB4N2GEpeEepnayxpnlNI5L7FUm6e820V+CNvq4in5h2tgyF5R8K9XR8PxMe6GwfGrs1W4O814fq3P5N5Fq4z4doDLt5+qF743Moy/eHzFrPPFE//s5uM/omE9GcmpO+NpG/Yt81N3o/9mNevRTW1JFvj4zgftPpYDwPW7s3+OvhZU5Ovg+nyP1W/0/PhGLMq+tF+BJAP+KOMyJ/W01FetpYPfJvbGuvwM/fR3iY5r+XzKEMYP7P8FMv/yGzL9GVrgKExCLCj93kBPmBEyRCO/7uTngw2+E/NiA+6pCfDzH1mcpyjkeODVrkcTS0oC5ZBLKIhf0EawvexDnCoT0D6sPEo0UTbl+vT7qAM5raNsivwBjzVBiRTMK+m7BH6u0/WXkzr6YW+5P5KdYT8Vd0oDiAu1+eiPh4DkK+ZXiY6uTPqBDLK9Zq5zy4eoJ9zebpTkoe1SShnlo+9kuPYJCPJIPNdet6CfAvKAyb1TdS+1HGVj31ZDnkiFvLVjzfI96h/U/O9wVxYvhcvD8rQnSNdkZ7GjZwP2dTHyORQD6QhXdB2SMvn/XhuQOv3Zs+r6dbEXzrAxz/L4Pk0LKPa6KIDwm2kjpdJF7Ib2UyVDXnlA7kQR5ULcWlPBF/DyLJyyBexHm32ea52APpj5PMjtJ4J8lCepBvT658fAd6AS3mXT/9Xlj9LQtjqfBvihD0/Qs+OyHR9NsuwlOczQD7SE+QkXfV6tmnq++JsOnOvBwKft6ZkMj81ZTLrwPdxU+RjOIoteI/PI5M9fwzsgfzWyfL9jz49x3hrK5QXv8P7faSbmo3u79XYslRAy8tcG9iI9li/v7/q5ygH5fHU/kletAe1f5QNdee2IB3838kWt+yvz6F5LFH3CPP7vzN7UlwlTKKZvj/i+fjc1sSD5CL+RL+lT0f4GjnjZSEZFtDIwPI1uOhv3Vw31Ynefz/fD3FJPsRAfJkf3r0f4nH76PxQ/5tq76P3QwzOn/OVtced95O3P539Ft8PsfT38Pdde/17HFst920vlg1ZPwzhff8IjdncwIm94fMD+L1UL9mT5OXthNexXpYf9m3IMqi5/zDeV+tDifG8HZ62L/Fq4Kvy7MUwdTIty+6r937eJ/ze4xH3zoi4t09wb/l9/Pu/7a33B7yehHtk7yhbY9mzDcvqZNp/b3oe33y+hcZJswb5izoHssre0c+ffNBqPucSNd+DvDnuX3thnh2fsyXFeX6vZBjAH3AIg/gjFhubGWDong0f3Cu9+VhV77UMZGpuo2dh9TFHjdc8Bk3Zi3IAikMoA+nBY1J6z/W9u6fd8wakn4rzaHO0DW/a03xvPPV5anw=
*/