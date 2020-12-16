/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//
// Scapegoat tree algorithms are taken from the paper titled:
// "Scapegoat Trees" by Igal Galperin Ronald L. Rivest.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_SGTREE_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_SGTREE_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <cstddef>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! sgtree_algorithms is configured with a NodeTraits class, which encapsulates the
//! information about the node to be manipulated. NodeTraits must support the
//! following interface:
//!
//! <b>Typedefs</b>:
//!
//! <tt>node</tt>: The type of the node that forms the binary search tree
//!
//! <tt>node_ptr</tt>: A pointer to a node
//!
//! <tt>const_node_ptr</tt>: A pointer to a const node
//!
//! <b>Static functions</b>:
//!
//! <tt>static node_ptr get_parent(const_node_ptr n);</tt>
//!
//! <tt>static void set_parent(node_ptr n, node_ptr parent);</tt>
//!
//! <tt>static node_ptr get_left(const_node_ptr n);</tt>
//!
//! <tt>static void set_left(node_ptr n, node_ptr left);</tt>
//!
//! <tt>static node_ptr get_right(const_node_ptr n);</tt>
//!
//! <tt>static void set_right(node_ptr n, node_ptr right);</tt>
template<class NodeTraits>
class sgtree_algorithms
   #ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_algorithms<NodeTraits>
   #endif
{
   public:
   typedef typename NodeTraits::node            node;
   typedef NodeTraits                           node_traits;
   typedef typename NodeTraits::node_ptr       node_ptr;
   typedef typename NodeTraits::const_node_ptr const_node_ptr;

   /// @cond
   private:

   typedef bstree_algorithms<NodeTraits>  bstree_algo;

   /// @endcond

   public:
   //! This type is the information that will be
   //! filled by insert_unique_check
   struct insert_commit_data
      : bstree_algo::insert_commit_data
   {
      std::size_t depth;
   };

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const const_node_ptr&)
   static node_ptr get_header(const_node_ptr n);

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const_node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const_node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node);

   //Unlink is not possible since tree metadata is needed to update the tree
   //!static void unlink(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink_leftmost_without_rebalance
   static node_ptr unlink_leftmost_without_rebalance(node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::unique(const const_node_ptr&)
   static bool unique(const_node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::size(const const_node_ptr&)
   static std::size_t size(const_node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::next_node(const node_ptr&)
   static node_ptr next_node(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::prev_node(const node_ptr&)
   static node_ptr prev_node(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::init(node_ptr)
   static void init(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::init_header(node_ptr)
   static void init_header(node_ptr header);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::erase(node_ptr,node_ptr)
   template<class AlphaByMaxSize>
   static node_ptr erase(node_ptr header, node_ptr z, std::size_t tree_size, std::size_t &max_tree_size, AlphaByMaxSize alpha_by_maxsize)
   {
      bstree_algo::erase(header, z);
      --tree_size;
      if (tree_size > 0 &&
          tree_size < alpha_by_maxsize(max_tree_size)){
         bstree_algo::rebalance(header);
         max_tree_size = tree_size;
      }
      return z;
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const const_node_ptr&,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(const node_ptr&,Disposer)
   template<class Disposer>
   static void clear_and_dispose(node_ptr header, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const const_node_ptr&, const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const const_node_ptr&,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (const_node_ptr header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count(const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_upper_bound(node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare, class H_Alpha>
   static node_ptr insert_equal_upper_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_equal_upper_bound(h, new_node, comp, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_lower_bound(node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare, class H_Alpha>
   static node_ptr insert_equal_lower_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_equal_lower_bound(h, new_node, comp, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal(node_ptr,node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare, class H_Alpha>
   static node_ptr insert_equal
      (node_ptr header, node_ptr hint, node_ptr new_node, NodePtrCompare comp
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_equal(header, hint, new_node, comp, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_before(node_ptr,node_ptr,node_ptr)
   template<class H_Alpha>
   static node_ptr insert_before
      (node_ptr header, node_ptr pos, node_ptr new_node
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_before(header, pos, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_back(node_ptr,node_ptr)
   template<class H_Alpha>
   static void push_back(node_ptr header, node_ptr new_node
         ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::push_back(header, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   template<class H_Alpha>
   static void push_front(node_ptr header, node_ptr new_node
         ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::push_front(header, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      std::size_t depth;
      std::pair<node_ptr, bool> ret =
         bstree_algo::insert_unique_check(header, key, comp, commit_data, &depth);
      commit_data.depth = depth;
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header, node_ptr hint, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      std::size_t depth;
      std::pair<node_ptr, bool> ret =
         bstree_algo::insert_unique_check
            (header, hint, key, comp, commit_data, &depth);
      commit_data.depth = depth;
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_commit(node_ptr,node_ptr,const insert_commit_data&)
   template<class H_Alpha>
   BOOST_INTRUSIVE_FORCEINLINE static void insert_unique_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {  return insert_commit(header, new_value, commit_data, tree_size, h_alpha, max_tree_size);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_unique
   template<class NodePtrCompare, class H_Alpha, class AlphaByMaxSize>
   static bool transfer_unique
      ( node_ptr header1, NodePtrCompare comp, std::size_t tree1_size, std::size_t &max_tree1_size
      , node_ptr header2, node_ptr z,   std::size_t tree2_size, std::size_t &max_tree2_size
      ,H_Alpha h_alpha, AlphaByMaxSize alpha_by_maxsize)
   {
      insert_commit_data commit_data;
      bool const transferable = insert_unique_check(header1, z, comp, commit_data).second;
      if(transferable){
         erase(header2, z, tree2_size, max_tree2_size, alpha_by_maxsize);
         insert_commit(header1, z, commit_data, tree1_size, h_alpha, max_tree1_size);
      }
      return transferable;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_equal
   template<class NodePtrCompare, class H_Alpha, class AlphaByMaxSize>
   static void transfer_equal
      ( node_ptr header1, NodePtrCompare comp, std::size_t tree1_size, std::size_t &max_tree1_size
      , node_ptr header2, node_ptr z,   std::size_t tree2_size, std::size_t &max_tree2_size
      ,H_Alpha h_alpha, AlphaByMaxSize alpha_by_maxsize)
   {
      insert_commit_data commit_data;
      insert_equal_upper_bound_check(header1, z, comp, commit_data);
      erase(header2, z, tree2_size, max_tree2_size, alpha_by_maxsize);
      insert_commit(header1, z, commit_data, tree1_size, h_alpha, max_tree1_size);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const_node_ptr p);

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static void rebalance(node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance_subtree
   static node_ptr rebalance_subtree(node_ptr old_root)
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   /// @cond
   private:

   template<class KeyType, class KeyNodePtrCompare>
   static void insert_equal_upper_bound_check
      (node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      std::size_t depth;
      bstree_algo::insert_equal_upper_bound_check(header, key, comp, commit_data, &depth);
      commit_data.depth = depth;
   }

   template<class H_Alpha>
   static void insert_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      bstree_algo::insert_unique_commit(header, new_value, commit_data);
      rebalance_after_insertion(new_value, commit_data.depth, tree_size+1, h_alpha, max_tree_size);
   }

   template<class H_Alpha>
   static void rebalance_after_insertion
      (node_ptr x, std::size_t depth
      , std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      if(tree_size > max_tree_size)
         max_tree_size = tree_size;

      if(tree_size > 2 && //Nothing to do with only the root
         //Check if the root node is unbalanced
         //Scapegoat paper depth counts root depth as zero and "depth" counts root as 1,
         //but since "depth" is the depth of the ancestor of x, i == depth
         depth > h_alpha(tree_size)){

         //Find the first non height-balanced node
         //as described in the section 4.2 of the paper.
         //This method is the alternative method described
         //in the paper. Authors claim that this method
         //may tend to yield more balanced trees on the average
         //than the weight balanced method.
         node_ptr s = x;
         std::size_t size = 1;
         for(std::size_t ancestor = 1; ancestor != depth; ++ancestor){
            const node_ptr s_parent = NodeTraits::get_parent(s);
            const node_ptr s_parent_left = NodeTraits::get_left(s_parent);
            //Obtain parent's size (previous size + parent + sibling tree)
            const node_ptr s_sibling = s_parent_left == s ? NodeTraits::get_right(s_parent) : s_parent_left;
            size += 1 + bstree_algo::subtree_size(s_sibling);
            s = s_parent;
            if(ancestor > h_alpha(size)){ //is 's' scapegoat?
               bstree_algo::rebalance_subtree(s);
               return;
            }
         }
         //The whole tree must be rebuilt
         max_tree_size = tree_size;
         bstree_algo::rebalance_subtree(NodeTraits::get_parent(s));
      }
   }
   /// @endcond
};

/// @cond

template<class NodeTraits>
struct get_algo<SgTreeAlgorithms, NodeTraits>
{
   typedef sgtree_algorithms<NodeTraits> type;
};

template <class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker<SgTreeAlgorithms, ValueTraits, NodePtrCompare, ExtraChecker>
{
   typedef detail::bstree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SGTREE_ALGORITHMS_HPP

/* sgtree_algorithms.hpp
kTgSR+JIHIkjcSSOxBH9+DDn/xubumP+vzfzxd/t51IL6VmdVrWoclmtn8SXNfnVuds5t1qd44L+yrqFlY1qO0sh5+7g3MHmwDl/5fzaKuKt9QQ78122H4tpspHuRXfgexa/A+9E7lBatiu4nmDWBbMvnGX5sOG8vjcOsPeAH1X8e91fpoQfdRv92Eia+v66RbWVlzapNAoJZ6Zb5x9yX+5K5vsfqcZ9d3oa381R+8jZR2fey6nzMk3Or7rKpVUGv4NG3SobLx0e4M3XePPDeL1JwjsiwFus8RaH8W5SJY4tlja4TpI96p9ReV7sHoT06dA5fNV/OleZ506zdXHJvkBkVPr5SuZeN2+64CxwnYqFl1C77nCnu4ayvzrNTZ3w8h4ZZX1JmfjyyEzNHJg5IfNj/B2WORAPdpba4enb+7g/bqWPHn3FX944Fd6Cnc50XcL+7hp2B93MNS35zSpP5Ehs8MrRo0dz0aHDE5izeNjSIeus4D5JSiawv92ivqJrO3yPwOdt3pQ5gH+WgvkY0EpnDef2Qo9a6fRs/lH4PnmLciWdw/Dtsvh6XHlJkG8i19N5ppHxxyyejCuvCPIczFZlQXuR/aFaWXw6g7zTXnNVGEup8CBK26fSHUQaVr3cQBrN0EbodvktYYsouwtV+tepDaV2ewykC/ZRZTzaXewqdFtrSLCzHGY/Qj2VHrrPwM49pIArZF+ptLPg/mPaDXG0G+HLBvlDnGofKi4/KCvtgDhV97xJEjci1IdAu/QjfUXRE6B9pDkzM7wfWUC/WbeM+qLsOxO5rdDjyu9i5z7m0hyXI78Auk+eLeIncJgwfAy6y+o7I3TAl0GZK2Kfb2HQP6Di703KtIJofgLhCfoz2JesvmsjdbRvl74ctEPbFxyxB9gu20niSzBNhKzgD8nXLmO+KiwjqrzV5Sr/DFZRm/Kg5J2sWQrqZ6VXIOnp+m0RxSZDGdAE6NVC6oRBP+VThCoafh/JFZ9Gf1AyA119zH4OJU131L4rw2edz5Qwa8cUf+y+ahoFWpYmfVWPsoi+qqu2+6a6RrErlX+q7cZha2mDShf0Iw79wsp3jvgmLAkAZRPwHVLmM5Sv+Oew8rWVPKUh+4TymdZT24fvLF+nq/SzXekO6oiu77vpkfX1Aa4zz6iv6psc1dd5vu6pr+szOvVS1xL9Ggz6yVjLkX4Nx6lfsB8bLz4Fm6BMqB66zprEj9AP34ou8XmrxiF+k17IhY9tAnkK+iG7UZ2fx768JNOYy5a37tcbKbs9mYGxRWZmZimjik9mDkvB001y1DZ5f1ib3KfCBTHb5GiusRsKjB9OMY4fgnHN0e+vtg63qWvmhbXP6D7MKE+rLYbeR6XcNF9b9Beh9+ieUFs/wj0MtqqQ8buMvRjXiy1MdpM0+JcrvNSE2oWKvTNfBYon03GdI53OfEid0zPwmtS5A9BeFCnT8rGgumrBEmkPVp1bkBPVB5vIuSP6+b5S585V539NOMnVBK2HdpnrH2kZnxtMY354w8fbDYh03ts3q/OzSfdExge9Iupsb+GrVXyNlNFg11lc4SJ4g/XXm6XGx2qsnY39N2YxflVj7cWMXD1p/EnOtwbZ6b7UVDAX5dR9Br71kIxl7zGNZU+SNMt6BtqYd3jmkMwJKUneHGllMcbt10ldCNMzZjtrQZ/SnsF2NiNmO9ud33U7a1I6FDluZ9ShTl93hvuiL3QMi9zZOVuta8g41gr/Iiz8j7CwL0vC/QL97AjxJXN1XkCht6XuHIZug6c1VdV5nt6lshueew11XuTcetuwn20fUudedd3NXWc7ZKjnyEd/Ps4nvF2d/6vrAf7ugkz1X9dB6ojtD20=
*/