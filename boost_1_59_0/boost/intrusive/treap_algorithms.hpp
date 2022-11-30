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

   void operator () (const_node_ptr p,
                     const return_type& check_return_left, const return_type& check_return_right,
                     return_type& check_return)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_traits::get_left(p) || !prio_comp_(node_traits::get_left(p), p));
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_traits::get_right(p) || !prio_comp_(node_traits::get_right(p), p));
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const_node_ptr)
   static node_ptr get_header(const_node_ptr n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node) BOOST_NOEXCEPT;
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
   static node_ptr unlink_leftmost_without_rebalance(node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::unique(const_node_ptr)
   static bool unique(const_node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::size(const_node_ptr)
   static std::size_t size(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::next_node(node_ptr)
   static node_ptr next_node(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::prev_node(node_ptr)
   static node_ptr prev_node(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::init(node_ptr)
   static void init(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::init_header(node_ptr)
   static void init_header(node_ptr header) BOOST_NOEXCEPT;
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
   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const_node_ptr,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(node_ptr,Disposer)
   template<class Disposer>
   static void clear_and_dispose(node_ptr header, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const_node_ptr, const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const_node_ptr,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (const_node_ptr header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const_node_ptr,const KeyType&,KeyNodePtrCompare)
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
      (node_ptr header, node_ptr new_node, const insert_commit_data &commit_data) BOOST_NOEXCEPT
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
   static bool is_header(const_node_ptr p) BOOST_NOEXCEPT;
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
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
*/