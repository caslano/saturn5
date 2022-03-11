//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP
#define BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// container
#include <boost/container/container_fwd.hpp>
#include <boost/container/throw_exception.hpp>
// container/detail
#include <boost/container/detail/pool_common.hpp>
#include <boost/container/detail/iterator.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#include <boost/container/detail/math_functions.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/detail/type_traits.hpp>
// intrusive
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/slist.hpp>
// other
#include <boost/assert.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <cstddef>

namespace boost {
namespace container {

namespace adaptive_pool_flag {

static const unsigned int none            = 0u;
static const unsigned int align_only      = 1u << 0u;
static const unsigned int size_ordered    = 1u << 1u;
static const unsigned int address_ordered = 1u << 2u;

}  //namespace adaptive_pool_flag{

namespace dtl {

template<class size_type>
struct hdr_offset_holder_t
{
   hdr_offset_holder_t(size_type offset = 0)
      : hdr_offset(offset)
   {}
   size_type hdr_offset;
};

template<class SizeType, unsigned int Flags>
struct less_func;

template<class SizeType>
struct less_func<SizeType, adaptive_pool_flag::none>
{
   static bool less(SizeType, SizeType, const void *, const void *)
   {  return true;   }
};

template<class SizeType>
struct less_func<SizeType, adaptive_pool_flag::size_ordered>
{
   static bool less(SizeType ls, SizeType rs, const void *, const void *)
   {  return ls < rs;   }
};

template<class SizeType>
struct less_func<SizeType, adaptive_pool_flag::address_ordered>
{
   static bool less(SizeType, SizeType, const void *la, const void *ra)
   {  return la < ra;   }
};

template<class SizeType>
struct less_func<SizeType, adaptive_pool_flag::size_ordered | adaptive_pool_flag::address_ordered>
{
   static bool less(SizeType ls, SizeType rs, const void *la, const void *ra)
   {  return (ls < rs) || ((ls == rs) && (la < ra));  }
};

template<class VoidPointer, class SizeType, unsigned OrderFlags>
struct block_container_traits
{
   typedef typename bi::make_set_base_hook
      < bi::void_pointer<VoidPointer>
      , bi::optimize_size<true>
      , bi::link_mode<bi::normal_link> >::type hook_t;

   template<class T>
   struct container
   {
      typedef typename bi::make_multiset
         <T, bi::base_hook<hook_t>, bi::size_type<SizeType> >::type  type;
   };

   template<class Container>
   static void reinsert_was_used(Container &container, typename Container::reference v, bool)
   {
      typedef typename Container::const_iterator const_block_iterator;
      typedef typename Container::iterator       block_iterator;
      typedef typename Container::value_compare  value_compare;

      const block_iterator this_block(Container::s_iterator_to(v));
      const const_block_iterator cendit(container.cend());
      block_iterator next_block(this_block);

      if(++next_block != cendit && value_compare()(*next_block, v)){
         const_block_iterator next2_block(next_block);
         //Test if v should be swapped with next (optimization)
         if(++next2_block == cendit || !value_compare()(*next2_block, v)){
            v.swap_nodes(*next_block);
            BOOST_ASSERT(++next_block == this_block);
         }
         else{
            container.erase(this_block);
            container.insert(v);
         }
      }
   }

   template<class Container>
   static void insert_was_empty(Container &container, typename Container::value_type &v, bool)
   {
      container.insert(v);
   }

   template<class Container>
   static void erase_first(Container &container)
   {
      container.erase(container.cbegin());
   }

   template<class Container>
   static void erase_last(Container &container)
   {
      container.erase(--container.cend());
   }
};

template<class VoidPointer, class SizeType>
struct block_container_traits<VoidPointer, SizeType, 0u>
{
   typedef typename bi::make_list_base_hook
      < bi::void_pointer<VoidPointer>
      , bi::link_mode<bi::normal_link> >::type hook_t;

   template<class T>
   struct container
   {
      typedef typename bi::make_list
         <T, bi::base_hook<hook_t>, bi::size_type<SizeType>, bi::constant_time_size<false> >::type  type;
   };

   template<class Container>
   static void reinsert_was_used(Container &container, typename Container::value_type &v, bool is_full)
   {
      if(is_full){
         container.erase(Container::s_iterator_to(v));
         container.push_back(v);
      }
   }

   template<class Container>
   static void insert_was_empty(Container &container, typename Container::value_type &v, bool is_full)
   {
      if(is_full){
         container.push_back(v);
      }
      else{
         container.push_front(v);
      }
   }

   template<class Container>
   static void erase_first(Container &container)
   {
      container.pop_front();
   }

   template<class Container>
   static void erase_last(Container &container)
   {
      container.pop_back();
   }
};

/////////////////////////////
//
//    adaptive_pool_types
//
/////////////////////////////
template<class MultiallocationChain, class VoidPointer, class SizeType, unsigned int Flags>
struct adaptive_pool_types
{
   typedef VoidPointer void_pointer;
   static const unsigned ordered = (Flags & (adaptive_pool_flag::size_ordered | adaptive_pool_flag::address_ordered));
   typedef block_container_traits<VoidPointer, SizeType, ordered> block_container_traits_t;
   typedef typename block_container_traits_t::hook_t hook_t;
   typedef hdr_offset_holder_t<SizeType> hdr_offset_holder;
   static const unsigned int order_flags = Flags & (adaptive_pool_flag::size_ordered | adaptive_pool_flag::address_ordered);
   typedef MultiallocationChain free_nodes_t;

   struct block_info_t
      : public hdr_offset_holder,
        public hook_t
   {
      //An intrusive list of free node from this block
      free_nodes_t free_nodes;
      friend bool operator <(const block_info_t &l, const block_info_t &r)
      {
         return less_func<SizeType, order_flags>::
            less(l.free_nodes.size(), r.free_nodes.size(), &l , &r);
      }

      friend bool operator ==(const block_info_t &l, const block_info_t &r)
      {  return &l == &r;  }
   };
   typedef typename block_container_traits_t:: template container<block_info_t>::type  block_container_t;
};


/////////////////////////////////////////////
//
//       candidate_power_of_2_ct
//
/////////////////////////////////////////////
template< std::size_t alignment
        , std::size_t real_node_size
        , std::size_t payload_per_allocation
        , std::size_t min_elements_per_block
        , std::size_t hdr_size
        , std::size_t hdr_offset_size
        , std::size_t overhead_percent>
struct candidate_power_of_2_ct_helper
{
   static const std::size_t hdr_subblock_elements_alone = (alignment - hdr_size - payload_per_allocation)/real_node_size;
   static const std::size_t hdr_subblock_elements_first = (alignment - hdr_size - payload_per_allocation)/real_node_size;
   static const std::size_t elements_per_b_subblock_mid = (alignment - hdr_offset_size)/real_node_size;
   static const std::size_t elements_per_b_subblock_end = (alignment - hdr_offset_size - payload_per_allocation)/real_node_size;
   static const std::size_t num_b_subblock =
      hdr_subblock_elements_alone >= min_elements_per_block
         ? 0
         : (   ((hdr_subblock_elements_first + elements_per_b_subblock_end) >= min_elements_per_block)
               ? 1
               : 2 + (min_elements_per_block - hdr_subblock_elements_first - elements_per_b_subblock_end - 1)/elements_per_b_subblock_mid
            )
         ;

   static const std::size_t num_b_subblock_mid = (num_b_subblock > 1) ? (num_b_subblock - 1) : 0;

   static const std::size_t total_nodes = (num_b_subblock == 0)
                                         ? hdr_subblock_elements_alone
                                         : ( (num_b_subblock == 1)
                                           ? (hdr_subblock_elements_first + elements_per_b_subblock_end)
                                           : (hdr_subblock_elements_first + num_b_subblock_mid*elements_per_b_subblock_mid + elements_per_b_subblock_end)
                                           )
                                         ;
   static const std::size_t total_data = total_nodes*real_node_size;
   static const std::size_t total_size = alignment*(num_b_subblock+1);
   static const bool overhead_satisfied = (total_size - total_data)*100/total_size < overhead_percent;
};

template< std::size_t initial_alignment
        , std::size_t real_node_size
        , std::size_t payload_per_allocation
        , std::size_t min_elements_per_block
        , std::size_t hdr_size
        , std::size_t hdr_offset_size
        , std::size_t overhead_percent
        , bool Loop = true>
struct candidate_power_of_2_ct
{
   typedef candidate_power_of_2_ct_helper
        < initial_alignment
        , real_node_size
        , payload_per_allocation
        , min_elements_per_block
        , hdr_size
        , hdr_offset_size
        , overhead_percent> helper_t;

   static const std::size_t candidate_power_of_2 = initial_alignment << std::size_t(!helper_t::overhead_satisfied);

   typedef typename candidate_power_of_2_ct
      < candidate_power_of_2
      , real_node_size
      , payload_per_allocation
      , min_elements_per_block
      , hdr_size
      , hdr_offset_size
      , overhead_percent
      , !helper_t::overhead_satisfied
      >::type type;

   static const std::size_t alignment     = type::alignment;
   static const std::size_t num_subblocks = type::num_subblocks;
   static const std::size_t real_num_node = type::real_num_node;
};

template< std::size_t initial_alignment
        , std::size_t real_node_size
        , std::size_t payload_per_allocation
        , std::size_t min_elements_per_block
        , std::size_t hdr_size
        , std::size_t hdr_offset_size
        , std::size_t overhead_percent
        >
struct candidate_power_of_2_ct
      < initial_alignment
      , real_node_size
      , payload_per_allocation
      , min_elements_per_block
      , hdr_size
      , hdr_offset_size
      , overhead_percent
      , false>
{
   typedef candidate_power_of_2_ct
      < initial_alignment
      , real_node_size
      , payload_per_allocation
      , min_elements_per_block
      , hdr_size
      , hdr_offset_size
      , overhead_percent
      , false> type;

   typedef candidate_power_of_2_ct_helper
        < initial_alignment
        , real_node_size
        , payload_per_allocation
        , min_elements_per_block
        , hdr_size
        , hdr_offset_size
        , overhead_percent> helper_t;

   static const std::size_t alignment = initial_alignment;
   static const std::size_t num_subblocks = helper_t::num_b_subblock+1;
   static const std::size_t real_num_node = helper_t::total_nodes;
};

/////////////////////////////////////////////
//
//       candidate_power_of_2_rt
//
/////////////////////////////////////////////
inline void candidate_power_of_2_rt ( std::size_t initial_alignment
                                    , std::size_t real_node_size
                                    , std::size_t payload_per_allocation
                                    , std::size_t min_elements_per_block
                                    , std::size_t hdr_size
                                    , std::size_t hdr_offset_size
                                    , std::size_t overhead_percent
                                    , std::size_t &alignment
                                    , std::size_t &num_subblocks
                                    , std::size_t &real_num_node)
{
   bool overhead_satisfied = false;
   std::size_t num_b_subblock = 0;
   std::size_t total_nodes = 0;

   while(!overhead_satisfied)
   {
      std::size_t hdr_subblock_elements_alone = (initial_alignment - hdr_size - payload_per_allocation)/real_node_size;
      std::size_t hdr_subblock_elements_first = (initial_alignment - hdr_size - payload_per_allocation)/real_node_size;
      std::size_t elements_per_b_subblock_mid = (initial_alignment - hdr_offset_size)/real_node_size;
      std::size_t elements_per_b_subblock_end = (initial_alignment - hdr_offset_size - payload_per_allocation)/real_node_size;

      num_b_subblock =
         hdr_subblock_elements_alone >= min_elements_per_block
            ? 0
            : (   ((hdr_subblock_elements_first + elements_per_b_subblock_end) >= min_elements_per_block)
                  ? 1
                  : 2 + (min_elements_per_block - hdr_subblock_elements_first - elements_per_b_subblock_end - 1)/elements_per_b_subblock_mid
               )
            ;

      std::size_t num_b_subblock_mid = (num_b_subblock > 1) ? (num_b_subblock - 1) : 0;

      total_nodes = (num_b_subblock == 0)
                                          ? hdr_subblock_elements_alone
                                          : ( (num_b_subblock == 1)
                                             ? (hdr_subblock_elements_first + elements_per_b_subblock_end)
                                             : (hdr_subblock_elements_first + num_b_subblock_mid*elements_per_b_subblock_mid + elements_per_b_subblock_end)
                                             )
                                          ;
      std::size_t total_data = total_nodes*real_node_size;
      std::size_t total_size = initial_alignment*(num_b_subblock+1);
      overhead_satisfied = (total_size - total_data)*100/total_size < overhead_percent;
      initial_alignment = initial_alignment << std::size_t(!overhead_satisfied);
   }
   alignment     = initial_alignment;
   num_subblocks = num_b_subblock+1;
   real_num_node = total_nodes;
}

/////////////////////////////////////////////
//
// private_adaptive_node_pool_impl_common
//
/////////////////////////////////////////////
template< class SegmentManagerBase, unsigned int Flags>
class private_adaptive_node_pool_impl_common
{
   public:
   //!Segment manager typedef
   typedef SegmentManagerBase                                        segment_manager_base_type;
   typedef typename SegmentManagerBase::multiallocation_chain        multiallocation_chain;
   typedef typename SegmentManagerBase::size_type                    size_type;
   //Flags
   //align_only
   static const bool AlignOnly      = (Flags & adaptive_pool_flag::align_only) != 0;
   typedef bool_<AlignOnly>            IsAlignOnly;
   typedef true_                       AlignOnlyTrue;
   typedef false_                      AlignOnlyFalse;

   typedef typename SegmentManagerBase::void_pointer void_pointer;
   static const typename SegmentManagerBase::
      size_type PayloadPerAllocation = SegmentManagerBase::PayloadPerAllocation;

   typedef typename boost::intrusive::pointer_traits
      <void_pointer>::template rebind_pointer<segment_manager_base_type>::type   segment_mngr_base_ptr_t;

   protected:
   typedef adaptive_pool_types
      <multiallocation_chain, void_pointer, size_type, Flags>        adaptive_pool_types_t;
   typedef typename adaptive_pool_types_t::free_nodes_t              free_nodes_t;
   typedef typename adaptive_pool_types_t::block_info_t              block_info_t;
   typedef typename adaptive_pool_types_t::block_container_t         block_container_t;
   typedef typename adaptive_pool_types_t::block_container_traits_t  block_container_traits_t;
   typedef typename block_container_t::iterator                      block_iterator;
   typedef typename block_container_t::const_iterator                const_block_iterator;
   typedef typename adaptive_pool_types_t::hdr_offset_holder         hdr_offset_holder;
   typedef private_adaptive_node_pool_impl_common                    this_type;

   static const size_type MaxAlign = alignment_of<void_pointer>::value;
   static const size_type HdrSize  = ((sizeof(block_info_t)-1)/MaxAlign+1)*MaxAlign;
   static const size_type HdrOffsetSize = ((sizeof(hdr_offset_holder)-1)/MaxAlign+1)*MaxAlign;

   segment_mngr_base_ptr_t             mp_segment_mngr_base;   //Segment manager
   block_container_t                   m_block_container;      //Intrusive block list
   size_type                           m_totally_free_blocks;  //Free blocks

   class block_destroyer;
   friend class block_destroyer;

   class block_destroyer
   {
      public:
      block_destroyer(const this_type *impl, multiallocation_chain &chain, const size_type num_subblocks, const size_type real_block_alignment, const size_type real_num_node)
         :  mp_impl(impl), m_chain(chain), m_num_subblocks(num_subblocks), m_real_block_alignment(real_block_alignment), m_real_num_node(real_num_node)
      {}

      void operator()(typename block_container_t::pointer to_deallocate)
      {  return this->do_destroy(to_deallocate, IsAlignOnly()); }

      private:
      void do_destroy(typename block_container_t::pointer to_deallocate, AlignOnlyTrue)
      {
         BOOST_ASSERT(to_deallocate->free_nodes.size() == m_real_num_node);
         m_chain.push_back(to_deallocate);
      }

      void do_destroy(typename block_container_t::pointer to_deallocate, AlignOnlyFalse)
      {
         BOOST_ASSERT(to_deallocate->free_nodes.size() == m_real_num_node);
         BOOST_ASSERT(0 == to_deallocate->hdr_offset);
         hdr_offset_holder *hdr_off_holder =
            mp_impl->priv_first_subblock_from_block(boost::movelib::to_raw_pointer(to_deallocate), m_num_subblocks, m_real_block_alignment);
         m_chain.push_back(hdr_off_holder);
      }

      const this_type *mp_impl;
      multiallocation_chain &m_chain;
      const size_type m_num_subblocks;
      const size_type m_real_block_alignment;
      const size_type m_real_num_node;
   };

   //This macro will activate invariant checking. Slow, but helpful for debugging the code.
   //#define BOOST_CONTAINER_ADAPTIVE_NODE_POOL_CHECK_INVARIANTS
   void priv_invariants(const size_type real_num_node, const size_type num_subblocks, const size_type real_block_alignment) const
   {
      (void)real_num_node; (void)num_subblocks; (void)real_block_alignment;
   #ifdef BOOST_CONTAINER_ADAPTIVE_NODE_POOL_CHECK_INVARIANTS
      //Check that the total totally free blocks are correct
      BOOST_ASSERT(m_block_container.size() >= m_totally_free_blocks);

      const const_block_iterator itend(m_block_container.cend());
      const const_block_iterator itbeg(m_block_container.cbegin());

      {  //Try to do checks in a single iteration
         const_block_iterator it(itbeg);
         size_type total_free_nodes = 0;
         size_type total_free_blocks = 0u;
         for(; it != itend; ++it){
            if(it != itbeg){
               //Check order invariant
               const_block_iterator prev(it);
               --prev;
               BOOST_ASSERT(!(m_block_container.key_comp()(*it, *prev)));
               (void)prev;   (void)it;
            }

            //free_nodes invariant
            const size_type free_nodes = it->free_nodes.size();
            BOOST_ASSERT(free_nodes <= real_num_node);
            BOOST_ASSERT(free_nodes != 0);

            //Acummulate total_free_nodes and total_free_blocks
            total_free_nodes += free_nodes;
            total_free_blocks += it->free_nodes.size() == real_num_node;

            if (!AlignOnly) {
               //Check that header offsets are correct
               hdr_offset_holder *hdr_off_holder = this->priv_first_subblock_from_block(const_cast<block_info_t *>(&*it), num_subblocks, real_block_alignment);
               for (size_type i = 0, max = num_subblocks; i < max; ++i) {
                  const size_type offset = reinterpret_cast<char*>(const_cast<block_info_t *>(&*it)) - reinterpret_cast<char*>(hdr_off_holder);
                  (void)offset;
                  BOOST_ASSERT(hdr_off_holder->hdr_offset == offset);
                  BOOST_ASSERT(0 == (reinterpret_cast<std::size_t>(hdr_off_holder) & (real_block_alignment - 1)));
                  BOOST_ASSERT(0 == (hdr_off_holder->hdr_offset & (real_block_alignment - 1)));
                  hdr_off_holder = reinterpret_cast<hdr_offset_holder *>(reinterpret_cast<char*>(hdr_off_holder) + real_block_alignment);
               }
            }
         }
         BOOST_ASSERT(total_free_blocks == m_totally_free_blocks);
         BOOST_ASSERT(total_free_nodes >= m_totally_free_blocks*real_num_node);
      }
   #endif
   }

   void priv_deallocate_free_blocks( const size_type max_free_blocks, const size_type real_num_node
                                   , const size_type num_subblocks, const size_type real_block_alignment)
   {  //Trampoline function to ease inlining
      if(m_totally_free_blocks > max_free_blocks){
         this->priv_deallocate_free_blocks_impl(max_free_blocks, real_num_node, num_subblocks, real_block_alignment);
      }
   }

   hdr_offset_holder *priv_first_subblock_from_block(block_info_t *block, const size_type num_subblocks, const size_type real_block_alignment) const
   {  return this->priv_first_subblock_from_block(block, num_subblocks, real_block_alignment, IsAlignOnly());   }

   hdr_offset_holder *priv_first_subblock_from_block(block_info_t *block, const size_type num_subblocks, const size_type real_block_alignment, AlignOnlyFalse) const
   {
      hdr_offset_holder *const hdr_off_holder = reinterpret_cast<hdr_offset_holder*>
            (reinterpret_cast<char*>(block) - (num_subblocks-1)*real_block_alignment);
      BOOST_ASSERT(hdr_off_holder->hdr_offset == size_type(reinterpret_cast<char*>(block) - reinterpret_cast<char*>(hdr_off_holder)));
      BOOST_ASSERT(0 == ((std::size_t)hdr_off_holder & (real_block_alignment - 1)));
      BOOST_ASSERT(0 == (hdr_off_holder->hdr_offset & (real_block_alignment - 1)));
      return hdr_off_holder;
   }

   hdr_offset_holder *priv_first_subblock_from_block(block_info_t *block, const size_type num_subblocks, const size_type real_block_alignment, AlignOnlyTrue) const
   {
      (void)num_subblocks; (void)real_block_alignment;
      return reinterpret_cast<hdr_offset_holder*>(block);
   }

   void priv_deallocate_free_blocks_impl( const size_type max_free_blocks, const size_type real_num_node
                                        , const size_type num_subblocks, const size_type real_block_alignment)
   {
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
      //Now check if we've reached the free nodes limit
      //and check if we have free blocks. If so, deallocate as much
      //as we can to stay below the limit
      multiallocation_chain chain;
      {
         if(Flags & adaptive_pool_flag::size_ordered){
            const_block_iterator it = m_block_container.cend();
            --it;
            size_type totally_free_blocks = m_totally_free_blocks;

            for( ; totally_free_blocks > max_free_blocks; --totally_free_blocks){
               BOOST_ASSERT(it->free_nodes.size() == real_num_node);
               void *addr = priv_first_subblock_from_block(const_cast<block_info_t*>(&*it), num_subblocks, real_block_alignment);
               --it;
               block_container_traits_t::erase_last(m_block_container);
               chain.push_front(void_pointer(addr));
            }
         }
         else{
            const_block_iterator it = m_block_container.cend();
            size_type totally_free_blocks = m_totally_free_blocks;

            while(totally_free_blocks > max_free_blocks){
               --it;
               if(it->free_nodes.size() == real_num_node){
                  void *addr = priv_first_subblock_from_block(const_cast<block_info_t*>(&*it), num_subblocks, real_block_alignment);
                  it = m_block_container.erase(it);
                  chain.push_front(void_pointer(addr));
                  --totally_free_blocks;
               }
            }
         }
         BOOST_ASSERT((m_totally_free_blocks - max_free_blocks) == chain.size());
         m_totally_free_blocks = max_free_blocks;
      }
      this->mp_segment_mngr_base->deallocate_many(chain);
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
   }

   void priv_fill_chain_remaining_to_block
      ( multiallocation_chain &chain, size_type target_elem_in_chain, block_info_t &c_info
      , char *mem_address, size_type max_node_in_mem
      , const size_type real_node_size)
   {
      BOOST_ASSERT(chain.size() <= target_elem_in_chain);

      //First add all possible nodes to the chain
      const size_type left = target_elem_in_chain - chain.size();
      const size_type add_to_chain = (max_node_in_mem < left) ? max_node_in_mem : left;
      char *free_mem_address = static_cast<char *>(boost::movelib::to_raw_pointer
         (chain.incorporate_after(chain.last(), void_pointer(mem_address), real_node_size, add_to_chain)));
      //Now store remaining nodes in the free list
      if(const size_type free = max_node_in_mem - add_to_chain){
         free_nodes_t & free_nodes = c_info.free_nodes;
         free_nodes.incorporate_after(free_nodes.last(), void_pointer(free_mem_address), real_node_size, free);
      }
   }

   //!Allocates a several blocks of nodes. Can throw
   void priv_append_from_new_blocks( size_type min_elements, multiallocation_chain &chain
                                   , const size_type max_free_blocks
                                   , const size_type real_block_alignment, const size_type real_node_size
                                   , const size_type real_num_node, const size_type num_subblocks
                                   , AlignOnlyTrue)
   {
      (void)num_subblocks;
      BOOST_ASSERT(m_block_container.empty());
      BOOST_ASSERT(min_elements > 0);
      const size_type n = (min_elements - 1)/real_num_node + 1;
      const size_type real_block_size = real_block_alignment - PayloadPerAllocation;
      const size_type target_elem_in_chain = chain.size() + min_elements;
      for(size_type i = 0; i != n; ++i){
         //We allocate a new NodeBlock and put it the last
         //element of the tree
         char *mem_address = static_cast<char*>
            (mp_segment_mngr_base->allocate_aligned(real_block_size, real_block_alignment));
         if(!mem_address){
            //In case of error, free memory deallocating all nodes (the new ones allocated
            //in this function plus previously stored nodes in chain).
            this->priv_deallocate_nodes(chain, max_free_blocks, real_num_node, num_subblocks, real_block_alignment);
            throw_bad_alloc();
         }
         block_info_t &c_info = *new(mem_address)block_info_t();
         mem_address += HdrSize;
         this->priv_fill_chain_remaining_to_block(chain, target_elem_in_chain, c_info, mem_address, real_num_node, real_node_size);
         const size_type free_nodes = c_info.free_nodes.size();
         if(free_nodes){
            const bool is_full = free_nodes == real_num_node;
            BOOST_ASSERT(free_nodes < real_num_node);
            m_totally_free_blocks += static_cast<size_type>(is_full);
            block_container_traits_t::insert_was_empty(m_block_container, c_info, is_full);
         }
      }
   }

   void priv_append_from_new_blocks( size_type min_elements, multiallocation_chain &chain
                                   , const size_type max_free_blocks
                                   , const size_type real_block_alignment, const size_type real_node_size
                                   , const size_type real_num_node, const size_type num_subblocks
                                   , AlignOnlyFalse)
   {
      BOOST_ASSERT(m_block_container.empty());
      BOOST_ASSERT(min_elements > 0);
      const size_type n = (min_elements - 1)/real_num_node + 1;
      const size_type real_block_size = real_block_alignment*num_subblocks - PayloadPerAllocation;
      const size_type elements_per_subblock_mid = (real_block_alignment - HdrOffsetSize)/real_node_size;
      const size_type elements_per_subblock_end = (real_block_alignment - HdrOffsetSize - PayloadPerAllocation) / real_node_size;
      const size_type hdr_subblock_elements = (real_block_alignment - HdrSize - PayloadPerAllocation)/real_node_size;
      const size_type target_elem_in_chain = chain.size() + min_elements;

      for(size_type i = 0; i != n; ++i){
         //We allocate a new NodeBlock and put it the last
         //element of the tree
         char *mem_address = static_cast<char*>
            (mp_segment_mngr_base->allocate_aligned(real_block_size, real_block_alignment));
         if(!mem_address){
            //In case of error, free memory deallocating all nodes (the new ones allocated
            //in this function plus previously stored nodes in chain).
            this->priv_deallocate_nodes(chain, max_free_blocks, real_num_node, num_subblocks, real_block_alignment);
            throw_bad_alloc();
         }
         //First initialize header information on the last subblock
         char *hdr_addr = mem_address + real_block_alignment*(num_subblocks-1);
         block_info_t &c_info = *new(hdr_addr)block_info_t();
         //Some structural checks
         BOOST_ASSERT(static_cast<void*>(&static_cast<hdr_offset_holder&>(c_info).hdr_offset) ==
                      static_cast<void*>(&c_info));   (void)c_info;
         for( size_type subblock = 0, maxsubblock = num_subblocks - 1
            ; subblock < maxsubblock
            ; ++subblock, mem_address += real_block_alignment){
            //Initialize header offset mark
            new(mem_address) hdr_offset_holder(size_type(hdr_addr - mem_address));
            const size_type elements_per_subblock = (subblock != (maxsubblock - 1)) ? elements_per_subblock_mid : elements_per_subblock_end;
            this->priv_fill_chain_remaining_to_block
               (chain, target_elem_in_chain, c_info, mem_address + HdrOffsetSize, elements_per_subblock, real_node_size);
         }
         this->priv_fill_chain_remaining_to_block
            (chain, target_elem_in_chain, c_info, hdr_addr + HdrSize, hdr_subblock_elements, real_node_size);
         m_totally_free_blocks += static_cast<size_type>(c_info.free_nodes.size() == real_num_node);
         if (c_info.free_nodes.size())
            m_block_container.push_front(c_info);
      }
   }

   //!Allocates array of count elements. Can throw
   void *priv_allocate_node( const size_type max_free_blocks, const size_type real_block_alignment, const size_type real_node_size
                           , const size_type real_num_node, const size_type num_subblocks)
   {
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
      //If there are no free nodes we allocate a new block
      if(!m_block_container.empty()){
         //We take the first free node the multiset can't be empty
         free_nodes_t &free_nodes = m_block_container.begin()->free_nodes;
         BOOST_ASSERT(!free_nodes.empty());
         const size_type free_nodes_count = free_nodes.size();
         void *first_node = boost::movelib::to_raw_pointer(free_nodes.pop_front());
         if(free_nodes.empty()){
            block_container_traits_t::erase_first(m_block_container);
         }
         m_totally_free_blocks -= static_cast<size_type>(free_nodes_count == real_num_node);
         this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
         return first_node;
      }
      else{
         multiallocation_chain chain;
         this->priv_append_from_new_blocks
            (1, chain, max_free_blocks, real_block_alignment, real_node_size, real_num_node, num_subblocks, IsAlignOnly());
         void *node = boost::movelib::to_raw_pointer(chain.pop_front());
         this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
         return node;
      }
   }

   void priv_allocate_nodes( const size_type n, multiallocation_chain &chain
                           , const size_type max_free_blocks, const size_type real_block_alignment, const size_type real_node_size
                           , const size_type real_num_node, const size_type num_subblocks)
   {
      size_type i = 0;
      BOOST_TRY{
         this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
         while(i != n){
            //If there are no free nodes we allocate all needed blocks
            if (m_block_container.empty()){
               this->priv_append_from_new_blocks
                  (n - i, chain, max_free_blocks, real_block_alignment, real_node_size, real_num_node, num_subblocks, IsAlignOnly());
               BOOST_ASSERT(m_block_container.empty() || (++m_block_container.cbegin() == m_block_container.cend()));
               BOOST_ASSERT(chain.size() == n);
               break;
            }
            free_nodes_t &free_nodes = m_block_container.begin()->free_nodes;
            const size_type free_nodes_count_before = free_nodes.size();
            m_totally_free_blocks -= static_cast<size_type>(free_nodes_count_before == real_num_node);
            const size_type num_left  = n-i;
            const size_type num_elems = (num_left < free_nodes_count_before) ? num_left : free_nodes_count_before;
            typedef typename free_nodes_t::iterator free_nodes_iterator;

            if(num_left < free_nodes_count_before){
               const free_nodes_iterator it_bbeg(free_nodes.before_begin());
               free_nodes_iterator it_bend(it_bbeg);
               for(size_type j = 0; j != num_elems; ++j){
                  ++it_bend;
               }
               free_nodes_iterator it_end = it_bend; ++it_end;
               free_nodes_iterator it_beg = it_bbeg; ++it_beg;
               free_nodes.erase_after(it_bbeg, it_end, num_elems);
               chain.incorporate_after(chain.last(), &*it_beg, &*it_bend, num_elems);
               //chain.splice_after(chain.last(), free_nodes, it_bbeg, it_bend, num_elems);
               BOOST_ASSERT(!free_nodes.empty());
            }
            else{
               const free_nodes_iterator it_beg(free_nodes.begin()), it_bend(free_nodes.last());
               free_nodes.clear();
               chain.incorporate_after(chain.last(), &*it_beg, &*it_bend, num_elems);
               block_container_traits_t::erase_first(m_block_container);
            }
            i += num_elems;
         }
      }
      BOOST_CATCH(...){
         this->priv_deallocate_nodes(chain, max_free_blocks, real_num_node, num_subblocks, real_block_alignment);
         this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
   }

   //!Deallocates an array pointed by ptr. Never throws
   void priv_deallocate_node( void *pElem
                            , const size_type max_free_blocks, const size_type real_num_node
                            , const size_type num_subblocks, const size_type real_block_alignment)
   {
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
      block_info_t &block_info = *this->priv_block_from_node(pElem, real_block_alignment);
      const size_type prev_free_nodes = block_info.free_nodes.size();
      BOOST_ASSERT(block_info.free_nodes.size() < real_num_node);

      //We put the node at the beginning of the free node list
      block_info.free_nodes.push_back(void_pointer(pElem));

      //The loop reinserts all blocks except the last one
      this->priv_reinsert_block(block_info, prev_free_nodes == 0, real_num_node);
      this->priv_deallocate_free_blocks(max_free_blocks, real_num_node, num_subblocks, real_block_alignment);
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
   }

   void priv_deallocate_nodes( multiallocation_chain &nodes
                             , const size_type max_free_blocks, const size_type real_num_node
                             , const size_type num_subblocks, const size_type real_block_alignment)
   {
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
      //To take advantage of node locality, wait until two
      //nodes belong to different blocks. Only then reinsert
      //the block of the first node in the block tree.
      //Cache of the previous block
      block_info_t *prev_block_info = 0;

      //If block was empty before this call, it's not already
      //inserted in the block tree.
      bool prev_block_was_empty     = false;
      typedef typename free_nodes_t::iterator free_nodes_iterator;
      {
         const free_nodes_iterator itbb(nodes.before_begin()), ite(nodes.end());
         free_nodes_iterator itf(nodes.begin()), itbf(itbb);
         size_type splice_node_count = size_type(-1);
         while(itf != ite){
            void *pElem = boost::movelib::to_raw_pointer(boost::movelib::iterator_to_raw_pointer(itf));
            block_info_t &block_info = *this->priv_block_from_node(pElem, real_block_alignment);
            BOOST_ASSERT(block_info.free_nodes.size() < real_num_node);
            ++splice_node_count;

            //If block change is detected calculate the cached block position in the tree
            if(&block_info != prev_block_info){
               if(prev_block_info){ //Make sure we skip the initial "dummy" cache
                  free_nodes_iterator it(itbb); ++it;
                  nodes.erase_after(itbb, itf, splice_node_count);
                  prev_block_info->free_nodes.incorporate_after(prev_block_info->free_nodes.last(), &*it, &*itbf, splice_node_count);
                  this->priv_reinsert_block(*prev_block_info, prev_block_was_empty, real_num_node);
                  splice_node_count = 0;
               }
               //Update cache with new data
               prev_block_was_empty = block_info.free_nodes.empty();
               prev_block_info = &block_info;
            }
            itbf = itf;
            ++itf;
         }
      }
      if(prev_block_info){
         //The loop reinserts all blocks except the last one
         const free_nodes_iterator itfirst(nodes.begin()), itlast(nodes.last());
         const size_type splice_node_count = nodes.size();
         nodes.clear();
         prev_block_info->free_nodes.incorporate_after(prev_block_info->free_nodes.last(), &*itfirst, &*itlast, splice_node_count);
         this->priv_reinsert_block(*prev_block_info, prev_block_was_empty, real_num_node);
         this->priv_deallocate_free_blocks(max_free_blocks, real_num_node, num_subblocks, real_block_alignment);
      }
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
   }

   void priv_reinsert_block(block_info_t &prev_block_info, const bool prev_block_was_empty, const size_type real_num_node)
   {
      //Cache the free nodes from the block
      const size_type this_block_free_nodes = prev_block_info.free_nodes.size();
      const bool is_full = this_block_free_nodes == real_num_node;

      //Update free block count
      m_totally_free_blocks += static_cast<size_type>(is_full);
      if(prev_block_was_empty){
         block_container_traits_t::insert_was_empty(m_block_container, prev_block_info, is_full);
      }
      else{
         block_container_traits_t::reinsert_was_used(m_block_container, prev_block_info, is_full);
      }
   }

   block_info_t *priv_block_from_node(void *node, const size_type real_block_alignment, AlignOnlyFalse) const
   {
      hdr_offset_holder *hdr_off_holder =
         reinterpret_cast<hdr_offset_holder*>((std::size_t)node & size_type(~(real_block_alignment - 1)));
      BOOST_ASSERT(0 == ((std::size_t)hdr_off_holder & (real_block_alignment - 1)));
      BOOST_ASSERT(0 == (hdr_off_holder->hdr_offset & (real_block_alignment - 1)));
      block_info_t *block = reinterpret_cast<block_info_t *>
         (reinterpret_cast<char*>(hdr_off_holder) + hdr_off_holder->hdr_offset);
      BOOST_ASSERT(block->hdr_offset == 0);
      return block;
   }

   block_info_t *priv_block_from_node(void *node, const size_type real_block_alignment, AlignOnlyTrue) const
   {
      return (block_info_t *)((std::size_t)node & std::size_t(~(real_block_alignment - 1)));
   }

   block_info_t *priv_block_from_node(void *node, const size_type real_block_alignment) const
   {  return this->priv_block_from_node(node, real_block_alignment, IsAlignOnly());   }

   //!Deallocates all used memory. Never throws
   void priv_clear(const size_type num_subblocks, const size_type real_block_alignment, const size_type real_num_node)
   {
      #ifndef NDEBUG
      block_iterator it    = m_block_container.begin();
      block_iterator itend = m_block_container.end();
      size_type n_free_nodes = 0;
      for(; it != itend; ++it){
         //Check for memory leak
         BOOST_ASSERT(it->free_nodes.size() == real_num_node);
         ++n_free_nodes;
      }
      BOOST_ASSERT(n_free_nodes == m_totally_free_blocks);
      #endif
      //Check for memory leaks
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
      multiallocation_chain chain;
      m_block_container.clear_and_dispose(block_destroyer(this, chain, num_subblocks, real_block_alignment, real_num_node));
      this->mp_segment_mngr_base->deallocate_many(chain);
      m_totally_free_blocks = 0;
      this->priv_invariants(real_num_node, num_subblocks, real_block_alignment);
   }

   public:
   private_adaptive_node_pool_impl_common(segment_manager_base_type *segment_mngr_base)
      //General purpose allocator
   :  mp_segment_mngr_base(segment_mngr_base)
   ,  m_block_container()
   ,  m_totally_free_blocks(0)
   {}

   size_type num_free_nodes()
   {
      typedef typename block_container_t::const_iterator citerator;
      size_type count = 0;
      citerator it (m_block_container.begin()), itend(m_block_container.end());
      for(; it != itend; ++it){
         count += it->free_nodes.size();
      }
      return count;
   }

   void swap(private_adaptive_node_pool_impl_common &other)
   {
      std::swap(mp_segment_mngr_base, other.mp_segment_mngr_base);
      std::swap(m_totally_free_blocks, other.m_totally_free_blocks);
      m_block_container.swap(other.m_block_container);
   }

   //!Returns the segment manager. Never throws
   segment_manager_base_type* get_segment_manager_base()const
   {  return boost::movelib::to_raw_pointer(mp_segment_mngr_base);  }
};

template< class SizeType
        , std::size_t HdrSize
        , std::size_t PayloadPerAllocation
        , std::size_t RealNodeSize
        , std::size_t NodesPerBlock
        , std::size_t HdrOffsetSize
        , std::size_t OverheadPercent
        , bool AlignOnly>
struct calculate_alignment_ct
{
   static const std::size_t alignment     = upper_power_of_2_ct<SizeType, HdrSize + RealNodeSize*NodesPerBlock>::value;
   static const std::size_t num_subblocks = 0;
   static const std::size_t real_num_node = (alignment - PayloadPerAllocation - HdrSize)/RealNodeSize;
};

template< class SizeType
        , std::size_t HdrSize
        , std::size_t PayloadPerAllocation
        , std::size_t RealNodeSize
        , std::size_t NodesPerBlock
        , std::size_t HdrOffsetSize
        , std::size_t OverheadPercent>
struct calculate_alignment_ct
   < SizeType
   , HdrSize
   , PayloadPerAllocation
   , RealNodeSize
   , NodesPerBlock
   , HdrOffsetSize
   , OverheadPercent
   , false>
{
   typedef typename candidate_power_of_2_ct
      < upper_power_of_2_ct<SizeType, HdrSize + PayloadPerAllocation + RealNodeSize>::value
      , RealNodeSize
      , PayloadPerAllocation
      , NodesPerBlock
      , HdrSize
      , HdrOffsetSize
      , OverheadPercent
      >::type type;

   static const std::size_t alignment     = type::alignment;
   static const std::size_t num_subblocks = type::num_subblocks;
   static const std::size_t real_num_node = type::real_num_node;
};


/////////////////////////////////////////////
//
//    private_adaptive_node_pool_impl_ct
//
/////////////////////////////////////////////
template< class SegmentManagerBase
        , std::size_t MaxFreeBlocks
        , std::size_t NodeSize
        , std::size_t NodesPerBlock
        , std::size_t OverheadPercent
        , unsigned int Flags>
class private_adaptive_node_pool_impl_ct
   : public private_adaptive_node_pool_impl_common<SegmentManagerBase, Flags>
{
   typedef private_adaptive_node_pool_impl_common<SegmentManagerBase, Flags> base_t;

   //Non-copyable
   private_adaptive_node_pool_impl_ct();
   private_adaptive_node_pool_impl_ct(const private_adaptive_node_pool_impl_ct &);
   private_adaptive_node_pool_impl_ct &operator=(const private_adaptive_node_pool_impl_ct &);

   public:
   typedef typename base_t::void_pointer              void_pointer;
   typedef typename base_t::size_type                 size_type;
   typedef typename base_t::multiallocation_chain     multiallocation_chain;
   typedef typename base_t::segment_manager_base_type segment_manager_base_type;

   static const typename base_t::size_type PayloadPerAllocation = base_t::PayloadPerAllocation;

   //align_only
   static const bool AlignOnly      = base_t::AlignOnly;

   private:
   static const size_type MaxAlign = base_t::MaxAlign;
   static const size_type HdrSize  = base_t::HdrSize;
   static const size_type HdrOffsetSize = base_t::HdrOffsetSize;

   static const size_type RealNodeSize = lcm_ct<NodeSize, alignment_of<void_pointer>::value>::value;

   typedef calculate_alignment_ct
      < size_type, HdrSize, PayloadPerAllocation
      , RealNodeSize, NodesPerBlock, HdrOffsetSize, OverheadPercent, AlignOnly> data_t;

   //Round the size to a power of two value.
   //This is the total memory size (including payload) that we want to
   //allocate from the general-purpose allocator
   static const size_type NumSubBlocks       = data_t::num_subblocks;
   static const size_type RealNumNode        = data_t::real_num_node;
   static const size_type RealBlockAlignment = data_t::alignment;

   public:

   //!Constructor from a segment manager. Never throws
   private_adaptive_node_pool_impl_ct(typename base_t::segment_manager_base_type *segment_mngr_base)
      //General purpose allocator
   :  base_t(segment_mngr_base)
   {}

   //!Destructor. Deallocates all allocated blocks. Never throws
   ~private_adaptive_node_pool_impl_ct()
   {  this->priv_clear(NumSubBlocks, data_t::alignment, RealNumNode);  }

   size_type get_real_num_node() const
   {  return RealNumNode; }

   //!Allocates array of count elements. Can throw
   void *allocate_node()
   {
      return this->priv_allocate_node
         (MaxFreeBlocks, data_t::alignment, RealNodeSize, RealNumNode, NumSubBlocks);
   }

   //!Allocates n nodes.
   //!Can throw
   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {
      this->priv_allocate_nodes
         (n, chain, MaxFreeBlocks, data_t::alignment, RealNodeSize, RealNumNode, NumSubBlocks);
   }

   //!Deallocates an array pointed by ptr. Never throws
   void deallocate_node(void *pElem)
   {
      this->priv_deallocate_node(pElem, MaxFreeBlocks, RealNumNode, NumSubBlocks, RealBlockAlignment);
   }

   //!Deallocates a linked list of nodes. Never throws
   void deallocate_nodes(multiallocation_chain &nodes)
   {
      this->priv_deallocate_nodes(nodes, MaxFreeBlocks, RealNumNode, NumSubBlocks, data_t::alignment);
   }

   void deallocate_free_blocks()
   {  this->priv_deallocate_free_blocks(0, RealNumNode, NumSubBlocks, data_t::alignment);  }

   //Deprecated, use deallocate_free_blocks
   void deallocate_free_chunks()
   {  this->priv_deallocate_free_blocks(0, RealNumNode, NumSubBlocks, data_t::alignment);   }
};

/////////////////////////////////////////////
//
//    private_adaptive_node_pool_impl_rt
//
/////////////////////////////////////////////
template<class SizeType>
struct private_adaptive_node_pool_impl_rt_data
{
   typedef SizeType size_type;

   private_adaptive_node_pool_impl_rt_data(size_type max_free_blocks, size_type real_node_size)
      : m_max_free_blocks(max_free_blocks), m_real_node_size(real_node_size)
      , m_real_block_alignment(), m_num_subblocks(), m_real_num_node()
   {}

   const size_type m_max_free_blocks;
   const size_type m_real_node_size;
   //Round the size to a power of two value.
   //This is the total memory size (including payload) that we want to
   //allocate from the general-purpose allocator
   size_type m_real_block_alignment;
   size_type m_num_subblocks;
   //This is the real number of nodes per block
   size_type m_real_num_node;
};


template<class SegmentManagerBase, unsigned int Flags>
class private_adaptive_node_pool_impl_rt
   : private private_adaptive_node_pool_impl_rt_data<typename SegmentManagerBase::size_type>
   , public  private_adaptive_node_pool_impl_common<SegmentManagerBase, Flags> 
{
   typedef private_adaptive_node_pool_impl_common<SegmentManagerBase, Flags> impl_t;
   typedef private_adaptive_node_pool_impl_rt_data<typename SegmentManagerBase::size_type> data_t;

   //Non-copyable
   private_adaptive_node_pool_impl_rt();
   private_adaptive_node_pool_impl_rt(const private_adaptive_node_pool_impl_rt &);
   private_adaptive_node_pool_impl_rt &operator=(const private_adaptive_node_pool_impl_rt &);

   protected:

   typedef typename impl_t::void_pointer           void_pointer;
   typedef typename impl_t::size_type              size_type;
   typedef typename impl_t::multiallocation_chain  multiallocation_chain;

   static const typename impl_t::size_type PayloadPerAllocation = impl_t::PayloadPerAllocation;

   //Flags
   //align_only
   static const bool AlignOnly      = impl_t::AlignOnly;

   static const size_type HdrSize  = impl_t::HdrSize;
   static const size_type HdrOffsetSize = impl_t::HdrOffsetSize;

   public:

   //!Segment manager typedef
   typedef SegmentManagerBase                 segment_manager_base_type;

   //!Constructor from a segment manager. Never throws
   private_adaptive_node_pool_impl_rt
      ( segment_manager_base_type *segment_mngr_base
      , size_type node_size
      , size_type nodes_per_block
      , size_type max_free_blocks
      , unsigned char overhead_percent
      )
   :  data_t(max_free_blocks, lcm(node_size, size_type(alignment_of<void_pointer>::value)))
   ,  impl_t(segment_mngr_base)
   {
      if(AlignOnly){
         this->m_real_block_alignment = upper_power_of_2(HdrSize + this->m_real_node_size*nodes_per_block);
         this->m_real_num_node = (this->m_real_block_alignment - PayloadPerAllocation - HdrSize)/this->m_real_node_size;
      }
      else{
         candidate_power_of_2_rt ( upper_power_of_2(HdrSize + PayloadPerAllocation + this->m_real_node_size)
                                 , this->m_real_node_size
                                 , PayloadPerAllocation
                                 , nodes_per_block
                                 , HdrSize
                                 , HdrOffsetSize
                                 , overhead_percent
                                 , this->m_real_block_alignment
                                 , this->m_num_subblocks
                                 , this->m_real_num_node);
      }
   }

   //!Destructor. Deallocates all allocated blocks. Never throws
   ~private_adaptive_node_pool_impl_rt()
   {  this->priv_clear(this->m_num_subblocks, this->m_real_block_alignment, this->m_real_num_node);  }

   size_type get_real_num_node() const
   {  return this->m_real_num_node; }

   //!Allocates array of count elements. Can throw
   void *allocate_node()
   {
      return this->priv_allocate_node
         (this->m_max_free_blocks, this->m_real_block_alignment, this->m_real_node_size, this->m_real_num_node, this->m_num_subblocks);
   }

   //!Allocates n nodes.
   //!Can throw
   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {

      this->priv_allocate_nodes
         (n, chain, this->m_max_free_blocks, this->m_real_block_alignment, this->m_real_node_size, this->m_real_num_node, this->m_num_subblocks);
   }

   //!Deallocates an array pointed by ptr. Never throws
   void deallocate_node(void *pElem)
   {
      this->priv_deallocate_node(pElem, this->m_max_free_blocks, this->m_real_num_node, this->m_num_subblocks, this->m_real_block_alignment);
   }

   //!Deallocates a linked list of nodes. Never throws
   void deallocate_nodes(multiallocation_chain &nodes)
   {
      this->priv_deallocate_nodes(nodes, this->m_max_free_blocks, this->m_real_num_node, this->m_num_subblocks, this->m_real_block_alignment);
   }

   void deallocate_free_blocks()
   {  this->priv_deallocate_free_blocks(0, this->m_real_num_node, this->m_num_subblocks, this->m_real_block_alignment);  }

   //Deprecated, use deallocate_free_blocks
   void deallocate_free_chunks()
   {  this->priv_deallocate_free_blocks(0, this->m_real_num_node, this->m_num_subblocks, this->m_real_block_alignment);   }
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP

/* adaptive_node_pool_impl.hpp
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
*/