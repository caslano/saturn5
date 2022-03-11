/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TREAP_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_TREAP_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <cstddef>

#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

namespace detail
{

template<class ValueTraits, class NodePtrPrioCompare, class ExtraChecker>
struct treap_node_extra_checker
      : public ExtraChecker
{
   typedef ExtraChecker                            base_checker_t;
   typedef ValueTraits                             value_traits;
   typedef typename value_traits::node_traits      node_traits;
   typedef typename node_traits::const_node_ptr const_node_ptr;

   typedef typename base_checker_t::return_type    return_type;

   treap_node_extra_checker(const NodePtrPrioCompare& prio_comp, ExtraChecker extra_checker)
      : base_checker_t(extra_checker), prio_comp_(prio_comp)
   {}

   void operator () (const const_node_ptr& p,
                     const return_type& check_return_left, const return_type& check_return_right,
                     return_type& check_return)
   {
      if (node_traits::get_left(p))
         BOOST_INTRUSIVE_INVARIANT_ASSERT(!prio_comp_(node_traits::get_left(p), p));
      if (node_traits::get_right(p))
         BOOST_INTRUSIVE_INVARIANT_ASSERT(!prio_comp_(node_traits::get_right(p), p));
      base_checker_t::operator()(p, check_return_left, check_return_right, check_return);
   }

   const NodePtrPrioCompare prio_comp_;
};

} // namespace detail

#endif   //#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

//! treap_algorithms provides basic algorithms to manipulate
//! nodes forming a treap.
//!
//! (1) the header node is maintained with links not only to the root
//! but also to the leftmost node of the tree, to enable constant time
//! begin(), and to the rightmost node of the tree, to enable linear time
//! performance when used with the generic set algorithms (set_union,
//! etc.);
//!
//! (2) when a node being deleted has two children its successor node is
//! relinked into its place, rather than copied, so that the only
//! pointers invalidated are those referring to the deleted node.
//!
//! treap_algorithms is configured with a NodeTraits class, which encapsulates the
//! information about the node to be manipulated. NodeTraits must support the
//! following interface:
//!
//! <b>Typedefs</b>:
//!
//! <tt>node</tt>: The type of the node that forms the treap
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
class treap_algorithms
   #ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_algorithms<NodeTraits>
   #endif
{
   public:
   typedef NodeTraits                           node_traits;
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr       node_ptr;
   typedef typename NodeTraits::const_node_ptr const_node_ptr;

   /// @cond
   private:

   typedef bstree_algorithms<NodeTraits>  bstree_algo;

   class rerotate_on_destroy
   {
      rerotate_on_destroy& operator=(const rerotate_on_destroy&);

      public:
      rerotate_on_destroy(node_ptr header, node_ptr p, std::size_t &n)
         :  header_(header), p_(p), n_(n), remove_it_(true)
      {}

      ~rerotate_on_destroy()
      {
         if(remove_it_){
            rotate_up_n(header_, p_, n_);
         }
      }

      void release()
      {  remove_it_ = false;  }

      const node_ptr header_;
      const node_ptr p_;
      std::size_t &n_;
      bool remove_it_;
   };

   static void rotate_up_n(const node_ptr header, const node_ptr p, std::size_t n)
   {
      node_ptr p_parent(NodeTraits::get_parent(p));
      node_ptr p_grandparent(NodeTraits::get_parent(p_parent));
      while(n--){
         if(p == NodeTraits::get_left(p_parent)){  //p is left child
            bstree_algo::rotate_right(p_parent, p, p_grandparent, header);
         }
         else{ //p is right child
            bstree_algo::rotate_left(p_parent, p, p_grandparent, header);
         }
         p_parent      = p_grandparent;
         p_grandparent = NodeTraits::get_parent(p_parent);
      }
   }

   /// @endcond

   public:
   //! This type is the information that will be
   //! filled by insert_unique_check
   struct insert_commit_data
      /// @cond
      :  public bstree_algo::insert_commit_data
      /// @endcond
   {
      /// @cond
      std::size_t rotations;
      /// @endcond
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
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink(node_ptr)
   template<class NodePtrPriorityCompare>
   static void unlink(node_ptr node, NodePtrPriorityCompare pcomp)
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!bstree_algo::is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node, pcomp);
      }
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
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
   template<class NodePtrPriorityCompare>
   static node_ptr erase(node_ptr header, node_ptr z, NodePtrPriorityCompare pcomp)
   {
      rebalance_for_erasure(header, z, pcomp);
      bstree_algo::erase(header, z);
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

   //! <b>Requires</b>: "h" must be the header node of a tree.
   //!   NodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares two node_ptrs.
   //!   NodePtrPriorityCompare is a priority function object that induces a strict weak
   //!   ordering compatible with the one used to create the
   //!   the tree. NodePtrPriorityCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts new_node into the tree before the upper bound
   //!   according to "comp" and rotates the tree according to "pcomp".
   //!
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //!
   //! <b>Throws</b>: If "comp" throw or "pcomp" throw.
   template<class NodePtrCompare, class NodePtrPriorityCompare>
   static node_ptr insert_equal_upper_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp, NodePtrPriorityCompare pcomp)
   {
      insert_commit_data commit_data;
      bstree_algo::insert_equal_upper_bound_check(h, new_node, comp, commit_data);
      rebalance_check_and_commit(h, new_node, pcomp, commit_data);
      return new_node;
   }

   //! <b>Requires</b>: "h" must be the header node of a tree.
   //!   NodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares two node_ptrs.
   //!   NodePtrPriorityCompare is a priority function object that induces a strict weak
   //!   ordering compatible with the one used to create the
   //!   the tree. NodePtrPriorityCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts new_node into the tree before the upper bound
   //!   according to "comp" and rotates the tree according to "pcomp".
   //!
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //!
   //! <b>Throws</b>: If "comp" throws.
   template<class NodePtrCompare, class NodePtrPriorityCompare>
   static node_ptr insert_equal_lower_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp, NodePtrPriorityCompare pcomp)
   {
      insert_commit_data commit_data;
      bstree_algo::insert_equal_lower_bound_check(h, new_node, comp, commit_data);
      rebalance_check_and_commit(h, new_node, pcomp, commit_data);
      return new_node;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   NodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares two node_ptrs. "hint" is node from
   //!   the "header"'s tree.
   //!   NodePtrPriorityCompare is a priority function object that induces a strict weak
   //!   ordering compatible with the one used to create the
   //!   the tree. NodePtrPriorityCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts new_node into the tree, using "hint" as a hint to
   //!   where it will be inserted. If "hint" is the upper_bound
   //!   the insertion takes constant time (two comparisons in the worst case).
   //!   Rotates the tree according to "pcomp".
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it is amortized
   //!   constant time if new_node is inserted immediately before "hint".
   //!
   //! <b>Throws</b>: If "comp" throw or "pcomp" throw.
   template<class NodePtrCompare, class NodePtrPriorityCompare>
   static node_ptr insert_equal
      (node_ptr h, node_ptr hint, node_ptr new_node, NodePtrCompare comp, NodePtrPriorityCompare pcomp)
   {
      insert_commit_data commit_data;
      bstree_algo::insert_equal_check(h, hint, new_node, comp, commit_data);
      rebalance_check_and_commit(h, new_node, pcomp, commit_data);
      return new_node;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   "pos" must be a valid node of the tree (including header end) node.
   //!   "pos" must be a node pointing to the successor to "new_node"
   //!   once inserted according to the order of already inserted nodes. This function does not
   //!   check "pos" and this precondition must be guaranteed by the caller.
   //!   NodePtrPriorityCompare is a priority function object that induces a strict weak
   //!   ordering compatible with the one used to create the
   //!   the tree. NodePtrPriorityCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts new_node into the tree before "pos"
   //!   and rotates the tree according to "pcomp".
   //!
   //! <b>Complexity</b>: Constant-time.
   //!
   //! <b>Throws</b>: If "pcomp" throws, strong guarantee.
   //!
   //! <b>Note</b>: If "pos" is not the successor of the newly inserted "new_node"
   //! tree invariants might be broken.
   template<class NodePtrPriorityCompare>
   static node_ptr insert_before
      (node_ptr header, node_ptr pos, node_ptr new_node, NodePtrPriorityCompare pcomp)
   {
      insert_commit_data commit_data;
      bstree_algo::insert_before_check(header, pos, commit_data);
      rebalance_check_and_commit(header, new_node, pcomp, commit_data);
      return new_node;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   "new_node" must be, according to the used ordering no less than the
   //!   greatest inserted key.
   //!   NodePtrPriorityCompare is a priority function object that induces a strict weak
   //!   ordering compatible with the one used to create the
   //!   the tree. NodePtrPriorityCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts x into the tree in the last position
   //!   and rotates the tree according to "pcomp".
   //!
   //! <b>Complexity</b>: Constant-time.
   //!
   //! <b>Throws</b>: If "pcomp" throws, strong guarantee.
   //!
   //! <b>Note</b>: If "new_node" is less than the greatest inserted key
   //! tree invariants are broken. This function is slightly faster than
   //! using "insert_before".
   template<class NodePtrPriorityCompare>
   static void push_back(node_ptr header, node_ptr new_node, NodePtrPriorityCompare pcomp)
   {
      insert_commit_data commit_data;
      bstree_algo::push_back_check(header, commit_data);
      rebalance_check_and_commit(header, new_node, pcomp, commit_data);
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   "new_node" must be, according to the used ordering, no greater than the
   //!   lowest inserted key.
   //!   NodePtrPriorityCompare is a priority function object that induces a strict weak
   //!   ordering compatible with the one used to create the
   //!   the tree. NodePtrPriorityCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts x into the tree in the first position
   //!   and rotates the tree according to "pcomp".
   //!
   //! <b>Complexity</b>: Constant-time.
   //!
   //! <b>Throws</b>: If "pcomp" throws, strong guarantee.
   //!
   //! <b>Note</b>: If "new_node" is greater than the lowest inserted key
   //! tree invariants are broken. This function is slightly faster than
   //! using "insert_before".
   template<class NodePtrPriorityCompare>
   static void push_front(node_ptr header, node_ptr new_node, NodePtrPriorityCompare pcomp)
   {
      insert_commit_data commit_data;
      bstree_algo::push_front_check(header, commit_data);
      rebalance_check_and_commit(header, new_node, pcomp, commit_data);
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares KeyType with a node_ptr.
   //!
   //! <b>Effects</b>: Checks if there is an equivalent node to "key" in the
   //!   tree according to "comp" and obtains the needed information to realize
   //!   a constant-time node insertion if there is no equivalent node.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing a node_ptr to the already present node
   //!   and false. If there is not equivalent key can be inserted returns true
   //!   in the returned pair's boolean and fills "commit_data" that is meant to
   //!   be used with the "insert_commit" function to achieve a constant-time
   //!   insertion function.
   //!
   //! <b>Complexity</b>: Average complexity is at most logarithmic.
   //!
   //! <b>Throws</b>: If "comp" throws.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a node is expensive and the user does not want to have two equivalent nodes
   //!   in the tree: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the node and this function offers the possibility to use that part
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the node and use
   //!   "insert_commit" to insert the node in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_unique_commit" only
   //!   if no more objects are inserted or erased from the set.
   template<class KeyType, class KeyNodePtrCompare, class PrioType, class PrioNodePtrPrioCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      ( const_node_ptr header
      , const KeyType &key, KeyNodePtrCompare comp
      , const PrioType &prio, PrioNodePtrPrioCompare pcomp
      , insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> ret =
         bstree_algo::insert_unique_check(header, key, comp, commit_data);
      if(ret.second)
         rebalance_after_insertion_check(header, commit_data.node, prio, pcomp, commit_data.rotations);
      return ret;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares KeyType with a node_ptr.
   //!   "hint" is node from the "header"'s tree.
   //!
   //! <b>Effects</b>: Checks if there is an equivalent node to "key" in the
   //!   tree according to "comp" using "hint" as a hint to where it should be
   //!   inserted and obtains the needed information to realize
   //!   a constant-time node insertion if there is no equivalent node.
   //!   If "hint" is the upper_bound the function has constant time
   //!   complexity (two comparisons in the worst case).
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing a node_ptr to the already present node
   //!   and false. If there is not equivalent key can be inserted returns true
   //!   in the returned pair's boolean and fills "commit_data" that is meant to
   //!   be used with the "insert_commit" function to achieve a constant-time
   //!   insertion function.
   //!
   //! <b>Complexity</b>: Average complexity is at most logarithmic, but it is
   //!   amortized constant time if new_node should be inserted immediately before "hint".
   //!
   //! <b>Throws</b>: If "comp" throws.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a node is expensive and the user does not want to have two equivalent nodes
   //!   in the tree: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the node and this function offers the possibility to use that part
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the node and use
   //!   "insert_commit" to insert the node in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_unique_commit" only
   //!   if no more objects are inserted or erased from the set.
   template<class KeyType, class KeyNodePtrCompare, class PrioType, class PrioNodePtrPrioCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      ( const_node_ptr header, node_ptr hint
      , const KeyType &key, KeyNodePtrCompare comp
      , const PrioType &prio, PrioNodePtrPrioCompare pcomp
      , insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> ret =
         bstree_algo::insert_unique_check(header, hint, key, comp, commit_data);
      if(ret.second)
         rebalance_after_insertion_check(header, commit_data.node, prio, pcomp, commit_data.rotations);
      return ret;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   "commit_data" must have been obtained from a previous call to
   //!   "insert_unique_check". No objects should have been inserted or erased
   //!   from the set between the "insert_unique_check" that filled "commit_data"
   //!   and the call to "insert_commit".
   //!
   //!
   //! <b>Effects</b>: Inserts new_node in the set using the information obtained
   //!   from the "commit_data" that a previous "insert_check" filled.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Notes</b>: This function has only sense if a "insert_unique_check" has been
   //!   previously executed to fill "commit_data". No value should be inserted or
   //!   erased between the "insert_check" and "insert_commit" calls.
   static void insert_unique_commit
      (node_ptr header, node_ptr new_node, const insert_commit_data &commit_data)
   {
      bstree_algo::insert_unique_commit(header, new_node, commit_data);
      rotate_up_n(header, new_node, commit_data.rotations);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_unique
   template<class NodePtrCompare, class PrioNodePtrPrioCompare>
   static bool transfer_unique
      (node_ptr header1, NodePtrCompare comp, PrioNodePtrPrioCompare pcomp, node_ptr header2, node_ptr z)
   {
      insert_commit_data commit_data;
      bool const transferable = insert_unique_check(header1, z, comp, z, pcomp, commit_data).second;
      if(transferable){
         erase(header2, z, pcomp);
         insert_unique_commit(header1, z, commit_data);         
      }
      return transferable;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_equal
   template<class NodePtrCompare, class PrioNodePtrPrioCompare>
   static void transfer_equal
      (node_ptr header1, NodePtrCompare comp, PrioNodePtrPrioCompare pcomp, node_ptr header2, node_ptr z)
   {
      insert_commit_data commit_data;
      bstree_algo::insert_equal_upper_bound_check(header1, z, comp, commit_data);
      rebalance_after_insertion_check(header1, commit_data.node, z, pcomp, commit_data.rotations);
      rebalance_for_erasure(header2, z, pcomp);
      bstree_algo::erase(header2, z);
      bstree_algo::insert_unique_commit(header1, z, commit_data);
      rotate_up_n(header1, z, commit_data.rotations);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const_node_ptr p);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   /// @cond
   private:

   template<class NodePtrPriorityCompare>
   static void rebalance_for_erasure(node_ptr header, node_ptr z, NodePtrPriorityCompare pcomp)
   {
      std::size_t n = 0;
      rerotate_on_destroy rb(header, z, n);

      node_ptr z_left  = NodeTraits::get_left(z);
      node_ptr z_right = NodeTraits::get_right(z);
      while(z_left || z_right){
         const node_ptr z_parent(NodeTraits::get_parent(z));
         if(!z_right || (z_left && pcomp(z_left, z_right))){
            bstree_algo::rotate_right(z, z_left, z_parent, header);
         }
         else{
            bstree_algo::rotate_left(z, z_right, z_parent, header);
         }
         ++n;
         z_left  = NodeTraits::get_left(z);
         z_right = NodeTraits::get_right(z);
      }
      rb.release();
   }

   template<class NodePtrPriorityCompare>
   static void rebalance_check_and_commit
      (node_ptr h, node_ptr new_node, NodePtrPriorityCompare pcomp, insert_commit_data &commit_data)
   {
      rebalance_after_insertion_check(h, commit_data.node, new_node, pcomp, commit_data.rotations);
      //No-throw
      bstree_algo::insert_unique_commit(h, new_node, commit_data);
      rotate_up_n(h, new_node, commit_data.rotations);
   }

   template<class Key, class KeyNodePriorityCompare>
   static void rebalance_after_insertion_check
      (const_node_ptr header, const_node_ptr up, const Key &k
      , KeyNodePriorityCompare pcomp, std::size_t &num_rotations)
   {
      const_node_ptr upnode(up);
      //First check rotations since pcomp can throw
      num_rotations = 0;
      std::size_t n = 0;
      while(upnode != header && pcomp(k, upnode)){
         ++n;
         upnode = NodeTraits::get_parent(upnode);
      }
      num_rotations = n;
   }

   template<class NodePtrPriorityCompare>
   static bool check_invariant(const_node_ptr header, NodePtrPriorityCompare pcomp)
   {
      node_ptr beg = begin_node(header);
      node_ptr end = end_node(header);

      while(beg != end){
         node_ptr p = NodeTraits::get_parent(beg);
         if(p != header){
            if(pcomp(beg, p))
               return false;
         }
         beg = next_node(beg);
      }
      return true;
   }

   /// @endcond
};

/// @cond

template<class NodeTraits>
struct get_algo<TreapAlgorithms, NodeTraits>
{
   typedef treap_algorithms<NodeTraits> type;
};

template <class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker<TreapAlgorithms, ValueTraits, NodePtrCompare, ExtraChecker>
{
   typedef detail::bstree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TREAP_ALGORITHMS_HPP

/* treap_algorithms.hpp
B9J4M80QTt+EZIynnvEJwmlO+W/zs4W2FkXgI0Wn+A6z4XAiiq8d15JyW9VRTftNU3ErC3Q97ucnlRfzbah8xZXLHvW6E0KK/5QFv2yKmqorTuT1kA9TPlpEpgoMqgOeXwR1hXsLrNhMHQjq8rHNkBL0lwFl032NxZnuTuqN7q0EDBWbS3n+tyGxRrcigV4FKqvRLUngwjAUuHKO93MOfF9QvufLplv+gkcPJMjHhZjVIDDhiYOrLxIExr+GokozBPy5FQnoRpfI8z00HBNUfwYJCJsivXPLi9y5h/tFwFD7o5waVDfPtqLQHbvPYnwtZp/lbmvMPov6hxvss7TbQgqs3A6wHl2vusdutVIe3MsDegqy8BMZJAvfjN++cyjclXlPoLj/QCXTSQa1im8EgG7nh7rsxWW+HHtHmtipMO4PIUNQV25A8OsWrOfgmip5cwgqA0vogN9qA+p5zaSdrDColaOLVcNJqZx8QNlE4+49P3+PfO039zBY7n1QQRYowmfs/p0AgN1S2VnuNQRLNiMge81sl2wqAXiz3NshqyO0TsJtCutROwvbjaNP2a2nfLXX7VbEHlvltvXfah99tH8WWDM2Tgf0aCOk7/CIROv7XY7u0yS1alFvVKLU0A1H6G+8Az3/BvF2dgk6cdluvewr+x868dt9aCV1v5kD4BB2wNbegTtw+wt6MYj3YrdsWvoC9uKvSi+6Ui/OQi/O2a3nfJ//T6Dge3egdHWV7u+FuhCKd9IJPHfqr5XJsM51n7mpqPtghCD3Nb5ANhOR/ccVfEDvCj6W5gouTHcFJyZfo7u72ZN6NxvE7FoXezLbnXnezb4V2UkY3NsFxsBpNHZ5nhBcwbG17mBeA6hl1mFGfxFZzQEFp9Uksbw20dpiXIWHyljeZfz2v4ry/FKtylj8J/yyqr1d0SVVNIMW8KVLU0PnhEuCkLbCW7Rc5Vn4eJMPuFZuxTo8t3AL4O1m+JI+7kcLoxPfQEes+jtEs7FaviCorj3SuDvxE8gWm6gVPW7C/wyMyHBpDpHJfpey+f7Cn9C/G7LL1YK/MhlHgtvUzTkyHjZtRucfN7OnZ512Zp12Z9a8ne61Zu3L6bJoqBAar2d2GFvZgnimhp9FSXIFcNlka5eFaeHvWQUAg4k1yTBHHdjcmqSwxsGaEW4C+8Y6bOFkQa4Uyo9rBc1RlncOILQgh0Nt4SBn4LRX57Bmegfhh/Wxy94Mv1Xl64p0dknobvVHajv6fjoAsm5NjV1uiHQdRAc6ZhICLcPFHgDAPga/CwUXOx67PXOjPYB02gD4mXwJ6kDr6I9GW09eGluaKmju1kNMF9xdqwMsBl1snF6EtLGhVDVuIWnKBau0LJF2kfTWPQvCqIKE7LIrlFo2ChisNqxBnLxuP1IhjiKLa56L6ibuuXoEUKJAGGiwM63a33bVBypYnIvtkMZQDtwtcnnyMY8jmBQXs/dtZxfQrxFG2yj96TukPHrofQ9kiDbrMr12hTYIf2OpMqfJ0ULTryvEHJA9Qpuz6mDtTCyltQMiK609Zqj+EdD4gowOKTWQ5jd8DBHUy+bHbqG8vzIdhnR9/4G0twj9nf2zklU1drrKo6aoVsWfBK0u8sJPXnXRefyBAkPOUwG8PmazAdf4X3qRNuHHmBZZiVwFDW4mc8kSSg5uJR+mgIx+47qmVqzDz/2uGP5IT6JxgJe4+5ZrDOfX9Fs2DXgGVpfhK1j0rE02HXw2StGEkKAm84E0+2KE1HuzmOHD05ilQTbd/2ys1aAFHQpNnZ9BAjVWLwc14Xhp0o+wxo4gSX7m2etvKVDst0/IUTaiDwnJkv00hhW2CahqLO6v5j6o7TYq5iJXZJ10jjKPFXjoBx6aykONPDSHh3bw0Hwe2sZDS3joAwqxQsWxSSet4xHksx7STUTDnrUW4gMQ/wVOB8gBZ3rSLLFNKu5nb8GiPVrkBF8XKDPjF+4fa8GCHSQRCpZCoW09IrP4L148MoveTJQtJgzFlnJvgsJ4bkL3zlkMt3k7+e9S+RIwx/6h0Vmd34NbtVtO8ZPo2dfgPYCJGXSnOAKb0UhklE0XQjjVP4VpitFetjbE63jhKq0+WgzKvKyTZFlSdSdaPBNo8xM0vV1CKI69DzX422SvEGNdsrdFcWQQM7CwgiN3hqiGW9Dpsl7aeRkr+ZlFcYTIGSAKu6yc/OfrEcb+2V+4bFY36HrZ7PW/xMhm/xwUI5vN/s+NfGB+U6Z5Qpt1hLwygPFdCLR6OwmeVunWb2VZDPXoENaI7Aj6rhR/jqarVtBxPIu1Ulxssj37gWRj8V95eor0QxP3hPKMBqLfgu5dZ6WTTWhxahQ8Tq2oaXRZz3qtOTO0kHnzDTJ/hnGhcclKAVdokiZZSm1Bs6FXm1UWHrEhrtip8upa4/Xe2+ytWrMav9Xe7vitxW+t12gv1ppB+Y736sh3llWGdTGXE1wndURkHvITUhdl35OX1+TtXZTtHg+/3YqyiUlnSvkwPSCG0kTvTIEJkUZizCaKWdFRsuC8lqj4bnXEF4BVOa7f450SK4VYnMAuGehMF9GL5OsLaMOT/n6U35+SIf3nEt7fgnX6ZdlYjEKJ3XrF+Mx3KopZobOu0C7TSbNS0APihPQoFvSM048JaZvYCDVuDkiTY+L8y9RalbeHZI+JEzzT1FrpDozRVJL5DgD9oIM8013skAuk3D9AtyTDDeq58M319Zz4JlqPfZOGTuQexNMLlSM4LciQfoEc4Vsc7D2uMLGPzfwAFu7+wZzMRydy6Li5OREdFo5cjAXxrosREMPgvYkAihU66eFk9ASK6e4XbbSQLTG7hDQXQJtGlEwCcQAmuihHEb2YnQ559PIvgRF1FTw24J8TstHhhrky5H3hDlKTEamU4ivmiRM05f4/alXLOoueMVrBc4/exZISRI820a0pd2nKKm+4Bx/xgQHhA+YZrYsdpffQfO1HH7os2Tn4u5zhK5ZIZV/TSnGxuy2CR0hyh+Z21ErvXhtpZwM6Bk6vcAqeGjE0olBa8zURHZfHCZJpozT7a5oTrRuyw7xsEth+QVMrXeSG9yR5l8u/XRs4vbImrLF/rJZrrCOXlSgX00T8Fuyrq65zdrHFYm3RKe7mcAGERQd6NDpufY/f2HDrXLOAf2xSnwvYqcI2YgzF5kZcNEYe16LEcZfpxfnoRFlL36MFZZNphk1kKy0ieyQD94dnSl/ijAY3YEmpjr7XYs3SZ0RvS/lRpXsy6GSLZCZqQztq+WLOvKneHjXcG5vrzlSkJFs5GWazE3KRc8seqaeiytChI7aNui3CL3Y1vDxyyk+6uw0pQVmcgr/Yef82akLlTf+XGhXDZ69gJ0BCdYfGpjtZXpodZHQ76xg2iKFx6Q52dxqbomWdZNO+pxB76VDFtF83ij4bM3FZ5CNiV8ASBLHZZysaSdib7V+RpvUNLlqRjvvl3pvg41b8SICP3vABXJiNy5DuPUrEM5H37BcgU1LxeehecBMBdAnungY30VThHRGAYz1cTGsWarRqfsi+Uiiqwim/dkH9lj+chRxt2kR2TMTrBJxsjhZlfaPbc1qq/UqW3aFpOlU7Z3mFjv+eBm7w7lcKmxiNbCKGuSyBLDkz9L6k83TFnbH4Edw0NgbqlnSEzHqXRmsWWRPt17WW6713IRmAcf8lmx9FQNkJo3ZKASWmC035uAxXMMkshKboJTMAxRXUmps1dOhvpHe8UsdEpcT3qkgd9uz2OyREz92pLjYlA+MHnQSkWJGqNwZwU8uV08NsLP6EdLUkc/jlnAfTYITfHlZGeHdaZIS8HYCEL1v6gW9HL+MNNfLQH0TPlFTsJPVn6SXas3KzCszyWTPQ0onSBzyng5dbz0N38ib/cBgL1GKTQAaQxdZLK3iO1NUdzNrWxu515w9r9rDDaKMHcmfqCOQOGKZeOpEIX3w7R7m1CmjzTKKsUT/A6/d0DqNx5Dzde+jVgT4Qjnd5lugFzXBp1xXc0fMOl2t9s5xZ+xw5E9O8RmlPI0KkAZUwEWhuCE8QwDBfIGG7QTH/sD12oMSZkVJJ0ktYyjPxmiKzeBElcwepfyIJl9dfUBGRg9IiBA0vexOBG62nuWoGtHUD8WCHRRDE3ej69yUCtc8h7Oca5RaiyEUybbhT14kcwRoQsKdhvUjfHSICnCSyPcArVvODFm5WXYL3t0EVXFgGEYSl0NU2UH1wEm617ydlXRrxH5SupuGSjyi3xyPrLqK3JNPm7eRrRImZRTkaALubnaHrlUAVO2Ms/gm3cV88C2LFNoXgclIt+Dc1Eb2aLC3hNizp8hn4zfFjtPeuopEk/QwrGknS0B1ov2ykcexGH1w0mLrQ/LOb38SDbu0DDtPFOIFlyJ6XJ+GGbR1dfvAGJ+8huksIj51xI2sxgdzBapxsJ0F5Dx9/NtQDYMJEq2jON/oz6XDtkiQxNO+c0zpbZVyDt8E4rI+0GZ8lNrDgIELcKIRSg4JnvBZ+n/MvS25ReftI9/46CQSV5BZp5MFrBJ67pYG/XclNv1XJhS+jlRQuSVb5CqQTX/4qa6sj+ZTNN1baCUnoNVhMSCTX0UV4/JIj/8Nmi0rw1AF0qWQoqRSpIEJYU8sPM0MKQXn4lSh00BRRkxqMAdWqw3QO4VWOnv6qme0Ue7qC+1FZNBZ5QnPKgavzA8nTHyEj2AXn4Fby0a53kyuYo8Q3Whr6E6Km+6jIKknW2sVapIQDdI8gD0vsp0jI2rKilwB5HcBzBv6ELt6727NlQEQ4Eb/uhy/W4r8qL9NZF6Is++cOKlXRXcjfjIFGPLe2Mk1rDDwHM160kvO5zvBBfM4AH8jnjIEF5C670qIyBpA3SG+0oAhI/E1lLF4E1UjPYRTjLC9A3+OzRba+jW6amn2v9CSMQzG37ZGmDSbHB50UH+2NbyD2xHdbpBc3RXqRoPTCl0Q9gEL7dNDGrbwLejV1YS8226kFgbMeo6S4Fu6y66cgNVpJl7UYA6/RTQKnnTkDzCsmZbVKz+9HN2jRDDpSdUTyXhkTxyXvx/e3I3TIdPPX5BEmybvpJP3Ndnm74K9OdVoHmJd9IBmggztRHNgj/XAOp7SnJ0hHG0bDjP0kBqePlo71Jhu+leJNH39Gl+Rg0k9SPdS5U2Sz741M06C4yDTdFvdfp0mPGZcmqYxP5fGD7YuFkHMPXaIWcRCscaADwP6I6VL6Ha4adw2bvMe6w+hPohPFM5PtOV5zi/HZ46QPec3njM+ShPnoPhAvPAPMTqD4l0WN5Ay0Gp/B1SY9so9mHAToCUlAiZK1QtB5SJoQE8uSkoPu+kDdimHScIp2HxLZaEhKACqO3QESH3SekD4iVdTXjTnrBb/zkFauDTrrA2Ur6+zybhCtU8OrVzvnicx5r32jugSWuAvoXoubEzcQbZ0nBP5twaWfIbLHx7vYl7i6+B7E/SAkh/WO1b7RmATDhsHL5S5/VWrQXQMgWKUGNuosbjUG1qBIoukLwV65COcFK9jCdNDBDajBz9iL2FAdIW8e0s3H7OUs0pOXDgoOpOEhUEk8Syhig4U9un2FDm6Q5dVuGggyLrrtjlzB/ECNZKRY6XjoVeC5S2CWpDtOt2O8VyftVA4NSfxcYek1AuT0SsSDRfWFy+epfAMALCvd/HQHQgnwAmDCbwzdgy5vHDQaBM1LEh5HveasntSaTrj67FO/2m+6gS42hfuCN5PRA03B0mIyHm0jPdS/icT6LQhV+6b+wE/tm/vhX7oNxJddZEWU91ocORpfsn9pmtGXKBQtnUkI392R09HbmRn77Ci6gPi+INFRvNhsDOA9xSxP+3aBsRg9dvwrcXvgMTUpDSVEoQLTMdSU7r0LqvANdwOP4OL4lzhBWSDlsUZ/G5LI0UgiF9DiqSdXmS/RB/7PQESbu/Jzr+nYte5sYTanqYuxgJ2clsdmwNoKw8qtoYp3S3/fA8WOUZeAXd/O4vtUECYZV+2iyHSVt5Nk2oMcbTxgTLmCTcbiDyCZQ8L3OABBs+CRoqW0xBc9KLA8i3+JXuW9STq7mwyMFtFzn57EXWcWivze4caNxea1pN3sginn60LZHmUHaW1EdldZPZEFNGTY5f3hEZF8vCRHlkjWg1hwNa8ZCpZEChLe2FFGm4b7wXNxd9VLt+faABunRc+ISfNOkmrYoJhAtfLesEp6cEDkBAe3DxnuO4ObqllPKu67cgNk+gwdYmLPfwghwzt0llvzJO35ms/EnA8hPpyMMiie5wgKEeP5DoF9Jf0LnRXHpgmeltbyVb4u0kN4vYwqAedjbFq6v1ZuHqJGNcfmNUh3Uxo5Jx3LktEnoWtwqb61HFSmID/dmOz/9qoQ1ATHpoEKCmn+pp/8tXHBvLR3kJL67pDuuJM2rS2CtRHm+lYemgkhX0dAkI+GEhvUo2yLdtnzeWm4uo3FIaQ9mQKbmJz5WLKADu5BDcszAy3M0wdOr+jqYNuh+MghaE8P3+uvS4ceNN8FAAGk9PbxX73qvYWwtxp4S1uiWuX/tpdQ3qYTHqubKmiSKsLxAMDCr2Ccdn26t0vWPrbbERoVJ72Tif1rk0GuJUFnbPJqmPMSdbjzZ2pV5ND0bmhcqszCpq1XjIHtV/HuNKIldO/z3Ihv2q/2ravtaSo0zayUZkvKCWZWSsJy8GbACy63j9ULVpPvG6BwnVkhyrUB3eITAEq9lHwrP1bFdC8eQ1fcPD1eWpKXzEoomyEfsyVIX/eJnEDOS26lGuJ8qX7KE1edl6YOxxuT484aV6qvpWOG5h9Vqsr28zWTgZahc38yd+5v4c7923BDm5z7m7ToVNvGfmaH0fqtkyZ3AxR62DyfNry9eCIVr1mRxhzm2sZ8gS7/ciejqzzZYfJl0yeLcKm9qVdz2ALZRI9bCa9WR+QfhmwgW4U7djasdaYQuRd5KrIGfgmPO5lWKiiXWXWSA0qGewgsoMf+BgO85kiIK1UUgiHOh8XrBZZbKJt6LsJdOdya6bgoeuN0m4+QE++9SvJfkr3xgKTz6QBdqEk5MgCsU8bLDVroqMIDoKcvtKA2NW3GdL6euYK5pYtWVWbHw/GvkoF/90IlDhVnvqfs97XvdV27pwh41QxkYcxphDc/7vSzbLrZRySaaC1u0yO4bsXjNTNFUPbS5YZfn0yxoHoauZtLepB87Og+YuK1kYseAIiL+TYhXrArhgz37UeDM4jqjpBNb030ZsplLk2Dv23ggp9D9tP+tpTFHTbhdk1lUbkDj3jiFrr/Qie78e6ySmGtnTnKtZXKeb7vyAPDlyCEdI8BIoW1QAv4hYyUXh+TPj6SnkrpUV/rt2LyZEbzBNOkZ77DqTDdfEChm2IoPxkmzApdsgfjfsN/lm4P5ody82mbQkRY/wxI1egI5WWg2yoedm+QilFDA0RIkwZDhYqfwBfoqQsE8y3UWwPfeXV4Ndk3NU5pFK1kXxP8a3AVodn+rkUJNc5G+FgZjs8Lac1BZ6PI3Hh5ESC2GybrkF3+Ei8Hb/VOC5QtccnuxiVAE5wNJWn4V5DxMqaGcCqI0A0wQ13Rat0me2/FRMyrLUkLJyuJly/wRC2rCRtzpjcWjApOK7hqXFcZyrsa0fuVi0yWErYql9FG938s6AhyGN1BRyOfGoV+sLlR1MkQca258T6SCgEUuJDh0DAAxt/pmuUnNQVBK245p0sJVxFQxDw6SpevRKEWvEJQ4/hJWLnzxn7N6WKor4jXp7dmHXGxy/6VerWvn+Cp3rLeSH4GeC4rpBt+ks5zAjUwyqYvnyARpZ8MCFWT7L9kXlYXuy2DZhq2jO+a26dVCp5KQVPm8purAMHDR260n/+FmbsHVYF+xc4LwJICp73d/Uv1aq+J3CYeeIL8J6Q9Dbhm+qjQhUCQd/sOQKG/0BXvY9sQiB39VrWvg2zKxPyUZ4/v+I0380FPh3Hdg4U1dQKDocl9T83n27OxMFIO3h3+nDuI59acQQmyi/R2vEoVGtdTwtNS/PBAh53IzC4JGlghAy80oCvosivAYbSsOvzk5gzSX45Ed4iN0rjLOFv8XEB4Kl08JRWoyNxVz4v6BvJZMHnm88MAyMHrQZKTbmov2xo2uILTrqjCHaQNe+iuKkOPvVjoFigU9t9oUq7BQxycEMoV8CpzzRHBP+Koypci/UKIhvvYKdKTJAEmHW3fjARYbZiHsDJMOEk/9/Cfifxn0kl+XQ90xY4xct8d85Dwxpwrjd08Y4ezZID1zKxWttd/Ms5YvB2J28k470P4x41/pvpParwT/Se13tv9Jzt4O8s7vEMlw6Uour8MSzUMuk/fumY6d1MBP81ryL+kbzWP+gJ+wssg/AEPv4XhudK2o5E7H3x6JDNkg2Cl/JK3HaJHFw6oVDn3ab03o7+Mi5UJ5U2grlcI1toF0jXBhTrMFpdVJ4Zm6d1sgDmMa8vCW+sPP2TaxoHKpi1/QJYsufxX1HQG4DIRt9O+RHvIrZFOASbtDMhePdCZSTARpf5Lem+K/1JHL7BIrTcet9kywgNE9nnksvQMwf8P/FZBTt/NDrYR1eWap/AvQiGsc+COECbmMIMBRsT2In1hOh18a2qte5f/TvDsoJXwFA3d/3CtXiVXIJdjhv+gs+R+6bWvuXkdeobHJrYADn6BR3+sR30G9uIGciYAAhvWsXr4sR71dsIuJ0CXjYE0fKciSP21HjUGEvC2gCD1svmKcv98VKC3XHM+O2gwSSQzXfsbc8eLQSshvhc8rpxnwCuqGuAjnm/Jx1179l/Ze+/57Do6Z1ay7rfOmcW8sxFb7hFebub/23K37QEMSCS06iibPprLxUwsBUQqfM1Gv8DKN7vvV6kKcvReDfqde4QRgqY2q6woB58u8iVt6RiHqRPSjC+Una3cKXrsI0CywPs7NOV246e2VKfx06kdxoREVRreuXALm5AkWvctSGR2vaZCtDYsMNrR7Fie4bTWLziGLbDy2Pu1QE4QWTmIJceCaN+qk35PZ/W8vd2Z5S7WgDElMnf0NDKbuVzqdb7B36RWQE36kRjSfbKSyzQNIM90At7qr0j2t3VecAbbW4s8gTnK9JU3uB+N5AXlxiqmo3vy+e0teEkYuyCtR3+31sgBoB/xcPY4jbTiLnTlUBuLfUrE43cR1TT4cyu+VuFZPrxmuEi+TKa8TSSzDtw=
*/