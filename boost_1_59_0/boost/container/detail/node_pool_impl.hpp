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
#include <boost/move/detail/force_ptr.hpp>
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
      return *move_detail::force_ptr<node_t*>(reinterpret_cast<char*>(block) + blocksize);
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