/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <cstddef>

namespace boost {
namespace intrusive {
namespace detail {

template<class NodeTraits>
class common_slist_algorithms
{
   public:
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef NodeTraits                           node_traits;

   static node_ptr get_previous_node(node_ptr p, const node_ptr & this_node)
   {
      for( node_ptr p_next
         ; this_node != (p_next = NodeTraits::get_next(p))
         ; p = p_next){
         //Logic error: possible use of linear lists with
         //operations only permitted with circular lists
         BOOST_INTRUSIVE_INVARIANT_ASSERT(p);
      }
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static void init(node_ptr this_node)
   {  NodeTraits::set_next(this_node, node_ptr());  }

   BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr & this_node)
   {
      node_ptr next = NodeTraits::get_next(this_node);
      return !next || next == this_node;
   }

   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const const_node_ptr & this_node)
   {  return !NodeTraits::get_next(this_node); }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink_after(node_ptr prev_node)
   {
      const_node_ptr this_node(NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, NodeTraits::get_next(this_node));
   }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink_after(node_ptr prev_node, node_ptr last_node)
   {  NodeTraits::set_next(prev_node, last_node);  }

   BOOST_INTRUSIVE_FORCEINLINE static void link_after(node_ptr prev_node, node_ptr this_node)
   {
      NodeTraits::set_next(this_node, NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, this_node);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void incorporate_after(node_ptr bp, node_ptr b, node_ptr be)
   {
      node_ptr p(NodeTraits::get_next(bp));
      NodeTraits::set_next(bp, b);
      NodeTraits::set_next(be, p);
   }

   static void transfer_after(node_ptr bp, node_ptr bb, node_ptr be)
   {
      if (bp != bb && bp != be && bb != be) {
         node_ptr next_b = NodeTraits::get_next(bb);
         node_ptr next_e = NodeTraits::get_next(be);
         node_ptr next_p = NodeTraits::get_next(bp);
         NodeTraits::set_next(bb, next_e);
         NodeTraits::set_next(be, next_p);
         NodeTraits::set_next(bp, next_b);
      }
   }

   struct stable_partition_info
   {
      std::size_t num_1st_partition;
      std::size_t num_2nd_partition;
      node_ptr    beg_2st_partition;
      node_ptr    new_last_node;
   };

   template<class Pred>
   static void stable_partition(node_ptr before_beg, node_ptr end, Pred pred, stable_partition_info &info)
   {
      node_ptr bcur = before_beg;
      node_ptr cur  = node_traits::get_next(bcur);
      node_ptr new_f = end;

      std::size_t num1 = 0, num2 = 0;
      while(cur != end){
         if(pred(cur)){
            ++num1;
            bcur = cur;
            cur  = node_traits::get_next(cur);
         }
         else{
            ++num2;
            node_ptr last_to_remove = bcur;
            new_f = cur;
            bcur = cur;
            cur  = node_traits::get_next(cur);
            BOOST_TRY{
               //Main loop
               while(cur != end){
                  if(pred(cur)){ //Might throw
                     ++num1;
                     //Process current node
                     node_traits::set_next(last_to_remove, cur);
                     last_to_remove = cur;
                     node_ptr nxt = node_traits::get_next(cur);
                     node_traits::set_next(bcur, nxt);
                     cur = nxt;
                  }
                  else{
                     ++num2;
                     bcur = cur;
                     cur  = node_traits::get_next(cur);
                  }
               }
            }
            BOOST_CATCH(...){
               node_traits::set_next(last_to_remove, new_f);
               BOOST_RETHROW;
            }
            BOOST_CATCH_END
            node_traits::set_next(last_to_remove, new_f);
            break;
         }
      }
      info.num_1st_partition = num1;
      info.num_2nd_partition = num2;
      info.beg_2st_partition = new_f;
      info.new_last_node = bcur;
   }

   //! <b>Requires</b>: f and l must be in a circular list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in the range [f, l).
   //!
   //! <b>Complexity</b>: Linear
   //!
   //! <b>Throws</b>: Nothing.
   static std::size_t distance(const const_node_ptr &f, const const_node_ptr &l)
   {
      const_node_ptr i(f);
      std::size_t result = 0;
      while(i != l){
         i = NodeTraits::get_next(i);
         ++result;
      }
      return result;
   }
};

/// @endcond

} //namespace detail

/// @cond

template<class NodeTraits>
struct get_algo<CommonSListAlgorithms, NodeTraits>
{
   typedef detail::common_slist_algorithms<NodeTraits> type;
};


} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP

/* common_slist_algorithms.hpp
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
*/