//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_NODE_POOL_IMPL_HPP
#define BOOST_CONTAINER_DETAIL_NODE_POOL_IMPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>

#include <boost/container/detail/math_functions.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/pool_common.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/detail/type_traits.hpp>

#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/slist.hpp>

#include <boost/core/no_exceptions_support.hpp>
#include <boost/assert.hpp>
#include <cstddef>

namespace boost {
namespace container {
namespace dtl {

template<class SegmentManagerBase>
class private_node_pool_impl
{
   //Non-copyable
   private_node_pool_impl();
   private_node_pool_impl(const private_node_pool_impl &);
   private_node_pool_impl &operator=(const private_node_pool_impl &);

   //A node object will hold node_t when it's not allocated
   public:
   typedef typename SegmentManagerBase::void_pointer              void_pointer;
   typedef typename node_slist<void_pointer>::slist_hook_t        slist_hook_t;
   typedef typename node_slist<void_pointer>::node_t              node_t;
   typedef typename node_slist<void_pointer>::node_slist_t        free_nodes_t;
   typedef typename SegmentManagerBase::multiallocation_chain     multiallocation_chain;
   typedef typename SegmentManagerBase::size_type                 size_type;

   private:
   typedef typename bi::make_slist
      < node_t, bi::base_hook<slist_hook_t>
      , bi::linear<true>
      , bi::constant_time_size<false> >::type      blockslist_t;

   static size_type get_rounded_size(size_type orig_size, size_type round_to)
   {  return ((orig_size-1)/round_to+1)*round_to;  }

   public:

   //!Segment manager typedef
   typedef SegmentManagerBase segment_manager_base_type;

   //!Constructor from a segment manager. Never throws
   private_node_pool_impl(segment_manager_base_type *segment_mngr_base, size_type node_size, size_type nodes_per_block)
   :  m_nodes_per_block(nodes_per_block)
   ,  m_real_node_size(lcm(node_size, size_type(alignment_of<node_t>::value)))
      //General purpose allocator
   ,  mp_segment_mngr_base(segment_mngr_base)
   ,  m_blocklist()
   ,  m_freelist()
      //Debug node count
   ,  m_allocated(0)
   {}

   //!Destructor. Deallocates all allocated blocks. Never throws
   ~private_node_pool_impl()
   {  this->purge_blocks();  }

   size_type get_real_num_node() const
   {  return m_nodes_per_block; }

   //!Returns the segment manager. Never throws
   segment_manager_base_type* get_segment_manager_base()const
   {  return boost::movelib::to_raw_pointer(mp_segment_mngr_base);  }

   void *allocate_node()
   {  return this->priv_alloc_node();  }

   //!Deallocates an array pointed by ptr. Never throws
   void deallocate_node(void *ptr)
   {  this->priv_dealloc_node(ptr); }

   //!Allocates a singly linked list of n nodes ending in null pointer.
   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {
      //Preallocate all needed blocks to fulfill the request
      size_type cur_nodes = m_freelist.size();
      if(cur_nodes < n){
         this->priv_alloc_block(((n - cur_nodes) - 1)/m_nodes_per_block + 1);
      }

      //We just iterate the needed nodes to get the last we'll erase
      typedef typename free_nodes_t::iterator free_iterator;
      free_iterator before_last_new_it = m_freelist.before_begin();
      for(size_type j = 0; j != n; ++j){
         ++before_last_new_it;
      }

      //Cache the first node of the allocated range before erasing
      free_iterator first_node(m_freelist.begin());
      free_iterator last_node (before_last_new_it);

      //Erase the range. Since we already have the distance, this is O(1)
      m_freelist.erase_after( m_freelist.before_begin()
                            , ++free_iterator(before_last_new_it)
                            , n);

      //Now take the last erased node and just splice it in the end
      //of the intrusive list that will be traversed by the multialloc iterator.
      chain.incorporate_after(chain.before_begin(), &*first_node, &*last_node, n);
      m_allocated += n;
   }

   void deallocate_nodes(multiallocation_chain &chain)
   {
      typedef typename multiallocation_chain::iterator iterator;
      iterator it(chain.begin()), itend(chain.end());
      while(it != itend){
         void *pElem = &*it;
         ++it;
         this->priv_dealloc_node(pElem);
      }
   }

   //!Deallocates all the free blocks of memory. Never throws
   void deallocate_free_blocks()
   {
      typedef typename free_nodes_t::iterator nodelist_iterator;
      typename blockslist_t::iterator bit(m_blocklist.before_begin()),
                                      it(m_blocklist.begin()),
                                      itend(m_blocklist.end());
      free_nodes_t backup_list;
      nodelist_iterator backup_list_last = backup_list.before_begin();

      //Execute the algorithm and get an iterator to the last value
      size_type blocksize = (get_rounded_size)
         (m_real_node_size*m_nodes_per_block, (size_type) alignment_of<node_t>::value);

      while(it != itend){
         //Collect all the nodes from the block pointed by it
         //and push them in the list
         free_nodes_t free_nodes;
         nodelist_iterator last_it = free_nodes.before_begin();
         const void *addr = get_block_from_hook(&*it, blocksize);

         m_freelist.remove_and_dispose_if
            (is_between(addr, blocksize), push_in_list(free_nodes, last_it));

         //If the number of nodes is equal to m_nodes_per_block
         //this means that the block can be deallocated
         if(free_nodes.size() == m_nodes_per_block){
            //Unlink the nodes
            free_nodes.clear();
            it = m_blocklist.erase_after(bit);
            mp_segment_mngr_base->deallocate((void*)addr);
         }
         //Otherwise, insert them in the backup list, since the
         //next "remove_if" does not need to check them again.
         else{
            //Assign the iterator to the last value if necessary
            if(backup_list.empty() && !m_freelist.empty()){
               backup_list_last = last_it;
            }
            //Transfer nodes. This is constant time.
            backup_list.splice_after
               ( backup_list.before_begin()
               , free_nodes
               , free_nodes.before_begin()
               , last_it
               , free_nodes.size());
            bit = it;
            ++it;
         }
      }
      //We should have removed all the nodes from the free list
      BOOST_ASSERT(m_freelist.empty());

      //Now pass all the node to the free list again
      m_freelist.splice_after
         ( m_freelist.before_begin()
         , backup_list
         , backup_list.before_begin()
         , backup_list_last
         , backup_list.size());
   }

   size_type num_free_nodes()
   {  return m_freelist.size();  }

   //!Deallocates all used memory. Precondition: all nodes allocated from this pool should
   //!already be deallocated. Otherwise, undefined behaviour. Never throws
   void purge_blocks()
   {
      //check for memory leaks
      BOOST_ASSERT(m_allocated==0);
      size_type blocksize = (get_rounded_size)
         (m_real_node_size*m_nodes_per_block, (size_type)alignment_of<node_t>::value);

      //We iterate though the NodeBlock list to free the memory
      while(!m_blocklist.empty()){
         void *addr = get_block_from_hook(&m_blocklist.front(), blocksize);
         m_blocklist.pop_front();
         mp_segment_mngr_base->deallocate((void*)addr);
      }
      //Just clear free node list
      m_freelist.clear();
   }

   void swap(private_node_pool_impl &other)
   {
      BOOST_ASSERT(m_nodes_per_block == other.m_nodes_per_block);
      BOOST_ASSERT(m_real_node_size == other.m_real_node_size);
      std::swap(mp_segment_mngr_base, other.mp_segment_mngr_base);
      m_blocklist.swap(other.m_blocklist);
      m_freelist.swap(other.m_freelist);
      std::swap(m_allocated, other.m_allocated);
   }

   private:

   struct push_in_list
   {
      push_in_list(free_nodes_t &l, typename free_nodes_t::iterator &it)
         :  slist_(l), last_it_(it)
      {}

      void operator()(typename free_nodes_t::pointer p) const
      {
         slist_.push_front(*p);
         if(slist_.size() == 1){ //Cache last element
            ++last_it_ = slist_.begin();
         }
      }

      private:
      free_nodes_t &slist_;
      typename free_nodes_t::iterator &last_it_;
   };

   struct is_between
   {
      typedef typename free_nodes_t::value_type argument_type;
      typedef bool                              result_type;

      is_between(const void *addr, std::size_t size)
         :  beg_(static_cast<const char *>(addr)), end_(beg_+size)
      {}

      bool operator()(typename free_nodes_t::const_reference v) const
      {
         return (beg_ <= reinterpret_cast<const char *>(&v) &&
                 end_ >  reinterpret_cast<const char *>(&v));
      }
      private:
      const char *      beg_;
      const char *      end_;
   };

   //!Allocates one node, using single segregated storage algorithm.
   //!Never throws
   node_t *priv_alloc_node()
   {
      //If there are no free nodes we allocate a new block
      if (m_freelist.empty())
         this->priv_alloc_block(1);
      //We take the first free node
      node_t *n = (node_t*)&m_freelist.front();
      m_freelist.pop_front();
      ++m_allocated;
      return n;
   }

   //!Deallocates one node, using single segregated storage algorithm.
   //!Never throws
   void priv_dealloc_node(void *pElem)
   {
      //We put the node at the beginning of the free node list
      node_t * to_deallocate = static_cast<node_t*>(pElem);
      m_freelist.push_front(*to_deallocate);
      BOOST_ASSERT(m_allocated>0);
      --m_allocated;
   }

   //!Allocates several blocks of nodes. Can throw
   void priv_alloc_block(size_type num_blocks)
   {
      BOOST_ASSERT(num_blocks > 0);
      size_type blocksize =
         (get_rounded_size)(m_real_node_size*m_nodes_per_block, (size_type)alignment_of<node_t>::value);

      BOOST_TRY{
         for(size_type i = 0; i != num_blocks; ++i){
            //We allocate a new NodeBlock and put it as first
            //element in the free Node list
            char *pNode = reinterpret_cast<char*>
               (mp_segment_mngr_base->allocate(blocksize + sizeof(node_t)));
            char *pBlock = pNode;
            m_blocklist.push_front(get_block_hook(pBlock, blocksize));

            //We initialize all Nodes in Node Block to insert
            //them in the free Node list
            for(size_type j = 0; j < m_nodes_per_block; ++j, pNode += m_real_node_size){
               m_freelist.push_front(*new (pNode) node_t);
            }
         }
      }
      BOOST_CATCH(...){
         //to-do: if possible, an efficient way to deallocate allocated blocks
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   //!Deprecated, use deallocate_free_blocks
   void deallocate_free_chunks()
   {  this->deallocate_free_blocks(); }

   //!Deprecated, use purge_blocks
   void purge_chunks()
   {  this->purge_blocks(); }

   private:
   //!Returns a reference to the block hook placed in the end of the block
   static node_t & get_block_hook (void *block, size_type blocksize)
   {
      return *reinterpret_cast<node_t*>(reinterpret_cast<char*>(block) + blocksize);
   }

   //!Returns the starting address of the block reference to the block hook placed in the end of the block
   void *get_block_from_hook (node_t *hook, size_type blocksize)
   {
      return (reinterpret_cast<char*>(hook) - blocksize);
   }

   private:
   typedef typename boost::intrusive::pointer_traits
      <void_pointer>::template rebind_pointer<segment_manager_base_type>::type   segment_mngr_base_ptr_t;

   const size_type m_nodes_per_block;
   const size_type m_real_node_size;
   segment_mngr_base_ptr_t mp_segment_mngr_base;   //Segment manager
   blockslist_t      m_blocklist;      //Intrusive container of blocks
   free_nodes_t      m_freelist;       //Intrusive container of free nods
   size_type       m_allocated;      //Used nodes for debugging
};


}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP

/* node_pool_impl.hpp
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
*/