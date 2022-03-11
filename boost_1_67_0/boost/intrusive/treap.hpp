/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_TREAP_HPP
#define BOOST_INTRUSIVE_TREAP_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/bs_set_hook.hpp>
#include <boost/intrusive/bstree.hpp>
#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/treap_algorithms.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/priority_compare.hpp>
#include <boost/intrusive/detail/node_cloner_disposer.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>

#include <boost/static_assert.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>

#include <cstddef>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //std::pair

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

struct treap_defaults
   : bstree_defaults
{
   typedef void priority;
   typedef void priority_of_value;
};

template<class ValuePtr, class VoidOrPrioOfValue, class VoidOrPrioComp>
struct treap_prio_types
{
   typedef typename
      boost::movelib::pointer_element<ValuePtr>::type value_type;
   typedef typename get_key_of_value
      < VoidOrPrioOfValue, value_type>::type          priority_of_value;
   typedef typename priority_of_value::type           priority_type;
   typedef typename get_prio_comp< VoidOrPrioComp
                      , priority_type
                      >::type                         priority_compare;
};

struct treap_tag;

/// @endcond

//! The class template treap is an intrusive treap container that
//! is used to construct intrusive set and multiset containers. The no-throw
//! guarantee holds only, if the key_compare object and priority_compare object
//! don't throw.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<>, \c size_type<>,
//! \c compare<>, \c priority<> and \c priority_of_value<>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class VoidOrPrioOfValue, class VoidOrPrioComp, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class treap_impl
   /// @cond
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType, ConstantTimeSize, BsTreeAlgorithms, HeaderHolder>
   //Use public inheritance to avoid MSVC bugs with closures
   , public detail::ebo_functor_holder
         < typename treap_prio_types<typename ValueTraits::pointer, VoidOrPrioOfValue, VoidOrPrioComp>::priority_compare
         , treap_tag>
   /// @endcond
{
   public:
   typedef ValueTraits                                               value_traits;
   /// @cond
   typedef bstree_impl< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType
                      , ConstantTimeSize, BsTreeAlgorithms
                      , HeaderHolder>                                tree_type;
   typedef tree_type                                                 implementation_defined;
   typedef treap_prio_types
      < typename ValueTraits::pointer
      , VoidOrPrioOfValue, VoidOrPrioComp>                           treap_prio_types_t;

   typedef detail::ebo_functor_holder
      <typename treap_prio_types_t::priority_compare, treap_tag>     prio_base;

   /// @endcond

   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
   typedef typename implementation_defined::reference                reference;
   typedef typename implementation_defined::const_reference          const_reference;
   typedef typename implementation_defined::difference_type          difference_type;
   typedef typename implementation_defined::size_type                size_type;
   typedef typename implementation_defined::value_compare            value_compare;
   typedef typename implementation_defined::key_compare              key_compare;
   typedef typename implementation_defined::iterator                 iterator;
   typedef typename implementation_defined::const_iterator           const_iterator;
   typedef typename implementation_defined::reverse_iterator         reverse_iterator;
   typedef typename implementation_defined::const_reverse_iterator   const_reverse_iterator;
   typedef typename implementation_defined::node_traits              node_traits;
   typedef typename implementation_defined::node                     node;
   typedef typename implementation_defined::node_ptr                 node_ptr;
   typedef typename implementation_defined::const_node_ptr           const_node_ptr;
   typedef BOOST_INTRUSIVE_IMPDEF(treap_algorithms<node_traits>)     node_algorithms;
   typedef BOOST_INTRUSIVE_IMPDEF
      (typename treap_prio_types_t::priority_type)                   priority_type;
   typedef BOOST_INTRUSIVE_IMPDEF
      (typename treap_prio_types_t::priority_of_value)               priority_of_value;
   typedef BOOST_INTRUSIVE_IMPDEF
      (typename treap_prio_types_t::priority_compare)                priority_compare;

   static const bool constant_time_size      = implementation_defined::constant_time_size;
   static const bool stateful_value_traits   = implementation_defined::stateful_value_traits;
   static const bool safemode_or_autounlink = is_safe_autounlink<value_traits::link_mode>::value;

   typedef detail::key_nodeptr_comp<priority_compare, value_traits, priority_of_value> prio_node_prio_comp_t;

   template<class PrioPrioComp>
   detail::key_nodeptr_comp<PrioPrioComp, value_traits, priority_of_value> prio_node_prio_comp(PrioPrioComp priopriocomp) const
   {  return detail::key_nodeptr_comp<PrioPrioComp, value_traits, priority_of_value>(priopriocomp, &this->get_value_traits());  }

   /// @cond
   private:

   //noncopyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(treap_impl)

   const priority_compare &priv_pcomp() const
   {  return static_cast<const prio_base&>(*this).get();  }

   priority_compare &priv_pcomp()
   {  return static_cast<prio_base&>(*this).get();  }

   /// @endcond

   public:
   typedef typename node_algorithms::insert_commit_data insert_commit_data;

   //! <b>Effects</b>: Constructs an empty container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor of the value_compare/priority_compare objects throw. Basic guarantee.
   treap_impl()
      : tree_type(), prio_base()
   {}

   //! <b>Effects</b>: Constructs an empty container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor of the value_compare/priority_compare objects throw. Basic guarantee.
   explicit treap_impl( const key_compare &cmp
                      , const priority_compare &pcmp = priority_compare()
                      , const value_traits &v_traits = value_traits())
      : tree_type(cmp, v_traits), prio_base(pcmp)
   {}

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue of type value_type.
   //!   cmp must be a comparison function that induces a strict weak ordering.
   //!
   //! <b>Effects</b>: Constructs an empty container and inserts elements from
   //!   [b, e).
   //!
   //! <b>Complexity</b>: Linear in N if [b, e) is already sorted using
   //!   comp and otherwise N * log N, where N is the distance between first and last.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor/operator() of the key_compare/priority_compare objects
   //!   throw. Basic guarantee.
   template<class Iterator>
   treap_impl( bool unique, Iterator b, Iterator e
            , const key_compare &cmp     = key_compare()
            , const priority_compare &pcmp = priority_compare()
            , const value_traits &v_traits = value_traits())
      : tree_type(cmp, v_traits), prio_base(pcmp)
   {
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   treap_impl(BOOST_RV_REF(treap_impl) x)
      : tree_type(BOOST_MOVE_BASE(tree_type, x))
      , prio_base(::boost::move(x.priv_pcomp()))
   {}

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   treap_impl& operator=(BOOST_RV_REF(treap_impl) x)
   {  this->swap(x); return *this;  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~treap_impl();

   //! @copydoc ::boost::intrusive::bstree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::bstree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::bstree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::bstree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::bstree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::bstree::cend()const
   const_iterator cend() const;
   #endif

   //! <b>Effects</b>: Returns an iterator pointing to the highest priority object of the treap.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   iterator top()
   {  return this->tree_type::root();   }

   //! <b>Effects</b>: Returns a const_iterator pointing to the highest priority object of the treap..
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator top() const
   {  return this->ctop();   }

   //! <b>Effects</b>: Returns a const_iterator pointing to the highest priority object of the treap..
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator ctop() const
   {  return this->tree_type::root();   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::bstree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::bstree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::bstree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::bstree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::bstree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::bstree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::bstree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::bstree::croot()const
   const_iterator croot() const;

   #endif

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the highest priority object of the
   //!    reversed treap.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   reverse_iterator rtop()
   {  return reverse_iterator(this->top());  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the highest priority objec
   //!    of the reversed treap.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_reverse_iterator rtop() const
   {  return const_reverse_iterator(this->top());  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the highest priority object
   //!    of the reversed treap.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_reverse_iterator crtop() const
   {  return const_reverse_iterator(this->top());  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(iterator)
   static treap_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const treap_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static treap_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const treap_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Effects</b>: Returns the priority_compare object used by the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If priority_compare copy-constructor throws.
   priority_compare priority_comp() const
   {  return this->priv_pcomp();   }

   //! <b>Effects</b>: Swaps the contents of two treaps.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If the comparison functor's swap call throws.
   void swap(treap_impl& other)
   {
      //This can throw
      ::boost::adl_move_swap(this->priv_pcomp(), other.priv_pcomp());
      tree_type::swap(other);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!   Cloner should yield to nodes equivalent to the original nodes.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the
   //!   elements from src calling Cloner::operator()(const_reference )
   //!   and inserts them on *this. Copies the predicate from the source container.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //!
   //! <b>Throws</b>: If cloner throws or predicate copy assignment throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(const treap_impl &src, Cloner cloner, Disposer disposer)
   {
      tree_type::clone_from(src, cloner, disposer);
      this->priv_pcomp() = src.priv_pcomp();
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!   Cloner should yield to nodes equivalent to the original nodes.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the
   //!   elements from src calling Cloner::operator()(reference)
   //!   and inserts them on *this. Copies the predicate from the source container.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //!
   //! <b>Throws</b>: If cloner throws or predicate copy assignment throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(treap_impl) src, Cloner cloner, Disposer disposer)
   {
      tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);
      this->priv_pcomp() = ::boost::move(src.priv_pcomp());
   }

   //! <b>Requires</b>: value must be an lvalue
   //!
   //! <b>Effects</b>: Inserts value into the container before the upper bound.
   //!
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //!
   //! <b>Throws</b>: If the internal key_compare or priority_compare functions throw. Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert_equal(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      iterator ret
         ( node_algorithms::insert_equal_upper_bound
            ( this->tree_type::header_ptr()
            , to_insert
            , this->key_node_comp(this->key_comp())
            , this->prio_node_prio_comp(this->priv_pcomp()))
         , this->priv_value_traits_ptr());
      this->tree_type::sz_traits().increment();
      return ret;
   }

   //! <b>Requires</b>: value must be an lvalue, and "hint" must be
   //!   a valid iterator.
   //!
   //! <b>Effects</b>: Inserts x into the container, using "hint" as a hint to
   //!   where it will be inserted. If "hint" is the upper_bound
   //!   the insertion takes constant time (two comparisons in the worst case)
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it is amortized
   //!   constant time if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the internal key_compare or priority_compare functions throw. Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert_equal(const_iterator hint, reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      iterator ret
         (node_algorithms::insert_equal
            ( this->tree_type::header_ptr()
            , hint.pointed_node()
            , to_insert
            , this->key_node_comp(this->key_comp())
            , this->prio_node_prio_comp(this->priv_pcomp()))
         , this->priv_value_traits_ptr());
      this->tree_type::sz_traits().increment();
      return ret;
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue
   //!   of type value_type.
   //!
   //! <b>Effects</b>: Inserts a each element of a range into the container
   //!   before the upper bound of the key of each element.
   //!
   //! <b>Complexity</b>: Insert range is in general O(N * log(N)), where N is the
   //!   size of the range. However, it is linear in N if the range is already sorted
   //!   by key_comp().
   //!
   //! <b>Throws</b>: If the internal key_compare or priority_compare functions throw.
   //!   Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

   //! <b>Requires</b>: value must be an lvalue
   //!
   //! <b>Effects</b>: Inserts value into the container if the value
   //!   is not already present.
   //!
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //!
   //! <b>Throws</b>: If the internal key_compare or priority_compare functions throw.
   //!   Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   std::pair<iterator, bool> insert_unique(reference value)
   {
      insert_commit_data commit_data;
      std::pair<iterator, bool> ret = this->insert_unique_check(key_of_value()(value), priority_of_value()(value), commit_data);
      if(!ret.second)
         return ret;
      return std::pair<iterator, bool> (this->insert_unique_commit(value, commit_data), true);
   }

   //! <b>Requires</b>: value must be an lvalue, and "hint" must be
   //!   a valid iterator
   //!
   //! <b>Effects</b>: Tries to insert x into the container, using "hint" as a hint
   //!   to where it will be inserted.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it is amortized
   //!   constant time (two comparisons in the worst case)
   //!   if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the internal key_compare or priority_compare functions throw.
   //!   Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert_unique(const_iterator hint, reference value)
   {
      insert_commit_data commit_data;
      std::pair<iterator, bool> ret = this->insert_unique_check(hint, key_of_value()(value), priority_of_value()(value), commit_data);
      if(!ret.second)
         return ret.first;
      return this->insert_unique_commit(value, commit_data);
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue
   //!   of type value_type.
   //!
   //! <b>Effects</b>: Tries to insert each element of a range into the container.
   //!
   //! <b>Complexity</b>: Insert range is in general O(N * log(N)), where N is the
   //!   size of the range. However, it is linear in N if the range is already sorted
   //!   by key_comp().
   //!
   //! <b>Throws</b>: If the internal key_compare or priority_compare functions throw.
   //!   Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e)
   {
      if(this->empty()){
         iterator iend(this->end());
         for (; b != e; ++b)
            this->insert_unique(iend, *b);
      }
      else{
         for (; b != e; ++b)
            this->insert_unique(*b);
      }
   }

   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Average complexity is at most logarithmic.
   //!
   //! <b>Throws</b>: If the comparison or predicate functions throw. Strong guarantee.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the value_type and this function offers the possibility to use that
   //!   part to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the container.
   std::pair<iterator, bool> insert_unique_check
      ( const key_type &key, const priority_type &prio, insert_commit_data &commit_data)
   {  return this->insert_unique_check(key, this->key_comp(), prio, this->priv_pcomp(), commit_data); }

   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself, using "hint"
   //!   as a hint to where it will be inserted.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it's amortized
   //!   constant time if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the comparison or predicate functions throw. Strong guarantee.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   constructing that is used to impose the order is much cheaper to construct
   //!   than the value_type and this function offers the possibility to use that key
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time. This can give a total
   //!   constant-time complexity to the insertion: check(O(1)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the container.
   std::pair<iterator, bool> insert_unique_check
      ( const_iterator hint, const key_type &key, const priority_type &prio, insert_commit_data &commit_data)
   {  return this->insert_unique_check(hint, key, this->key_comp(), prio, this->priv_pcomp(), commit_data); }

   //! <b>Requires</b>: comp must be a comparison function that induces
   //!   the same strict weak ordering as key_compare.
   //!   prio_value_pcomp must be a comparison function that induces
   //!   the same strict weak ordering as priority_compare. The difference is that
   //!   prio_value_pcomp and comp compare an arbitrary key/priority with the contained values.
   //!
   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Average complexity is at most logarithmic.
   //!
   //! <b>Throws</b>: If the comp or prio_value_pcomp
   //!   ordering functions throw. Strong guarantee.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the value_type and this function offers the possibility to use that
   //!   part to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the container.
   template<class KeyType, class KeyTypeKeyCompare, class PrioType, class PrioValuePrioCompare>
   BOOST_INTRUSIVE_DOC1ST(std::pair<iterator BOOST_INTRUSIVE_I bool>
      , typename detail::disable_if_convertible
         <KeyType BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I 
         std::pair<iterator BOOST_INTRUSIVE_I bool> >::type)
      insert_unique_check
      ( const KeyType &key, KeyTypeKeyCompare comp
      , const PrioType &prio, PrioValuePrioCompare prio_value_pcomp, insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> const ret =
         (node_algorithms::insert_unique_check
            ( this->tree_type::header_ptr()
            , key, this->key_node_comp(comp)
            , prio, this->prio_node_prio_comp(prio_value_pcomp)
            , commit_data));
      return std::pair<iterator, bool>(iterator(ret.first, this->priv_value_traits_ptr()), ret.second);
   }

   //! <b>Requires</b>: comp must be a comparison function that induces
   //!   the same strict weak ordering as key_compare.
   //!   prio_value_pcomp must be a comparison function that induces
   //!   the same strict weak ordering as priority_compare. The difference is that
   //!   prio_value_pcomp and comp compare an arbitrary key/priority with the contained values.
   //!
   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself, using "hint"
   //!   as a hint to where it will be inserted.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it's amortized
   //!   constant time if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the comp or prio_value_pcomp
   //!   ordering functions throw. Strong guarantee.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   constructing that is used to impose the order is much cheaper to construct
   //!   than the value_type and this function offers the possibility to use that key
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time. This can give a total
   //!   constant-time complexity to the insertion: check(O(1)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the container.
   template<class KeyType, class KeyTypeKeyCompare, class PrioType, class PrioValuePrioCompare>
   std::pair<iterator, bool> insert_unique_check
      ( const_iterator hint
      , const KeyType &key
      , KeyTypeKeyCompare comp
      , const PrioType &prio
      , PrioValuePrioCompare prio_value_pcomp
      , insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> const ret =
         (node_algorithms::insert_unique_check
            ( this->tree_type::header_ptr(), hint.pointed_node()
            , key, this->key_node_comp(comp)
            , prio, this->prio_node_prio_comp(prio_value_pcomp)
            , commit_data));
      return std::pair<iterator, bool>(iterator(ret.first, this->priv_value_traits_ptr()), ret.second);
   }

   //! <b>Requires</b>: value must be an lvalue of type value_type. commit_data
   //!   must have been obtained from a previous call to "insert_check".
   //!   No objects should have been inserted or erased from the container between
   //!   the "insert_check" that filled "commit_data" and the call to "insert_commit".
   //!
   //! <b>Effects</b>: Inserts the value in the avl_set using the information obtained
   //!   from the "commit_data" that a previous "insert_check" filled.
   //!
   //! <b>Returns</b>: An iterator to the newly inserted object.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Notes</b>: This function has only sense if a "insert_check" has been
   //!   previously executed to fill "commit_data". No value should be inserted or
   //!   erased between the "insert_check" and "insert_commit" calls.
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      node_algorithms::insert_unique_commit(this->tree_type::header_ptr(), to_insert, commit_data);
      this->tree_type::sz_traits().increment();
      return iterator(to_insert, this->priv_value_traits_ptr());
   }

   //! <b>Requires</b>: value must be an lvalue, "pos" must be
   //!   a valid iterator (or end) and must be the succesor of value
   //!   once inserted according to the predicate
   //!
   //! <b>Effects</b>: Inserts x into the container before "pos".
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: If the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: This function does not check preconditions so if "pos" is not
   //! the successor of "value" container ordering invariant will be broken.
   //! This is a low-level function to be used only for performance reasons
   //! by advanced users.
   iterator insert_before(const_iterator pos, reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      iterator ret
         ( node_algorithms::insert_before
            ( this->tree_type::header_ptr()
            , pos.pointed_node()
            , to_insert
            , this->prio_node_prio_comp(this->priv_pcomp())
            )
         , this->priv_value_traits_ptr());
      this->tree_type::sz_traits().increment();
      return ret;
   }

   //! <b>Requires</b>: value must be an lvalue, and it must be no less
   //!   than the greatest inserted key
   //!
   //! <b>Effects</b>: Inserts x into the container in the last position.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: If the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: This function does not check preconditions so if value is
   //!   less than the greatest inserted key container ordering invariant will be broken.
   //!   This function is slightly more efficient than using "insert_before".
   //!   This is a low-level function to be used only for performance reasons
   //!   by advanced users.
   void push_back(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      node_algorithms::push_back
         (this->tree_type::header_ptr(), to_insert, this->prio_node_prio_comp(this->priv_pcomp()));
      this->tree_type::sz_traits().increment();
   }

   //! <b>Requires</b>: value must be an lvalue, and it must be no greater
   //!   than the minimum inserted key
   //!
   //! <b>Effects</b>: Inserts x into the container in the first position.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: If the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: This function does not check preconditions so if value is
   //!   greater than the minimum inserted key container ordering invariant will be broken.
   //!   This function is slightly more efficient than using "insert_before".
   //!   This is a low-level function to be used only for performance reasons
   //!   by advanced users.
   void push_front(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      node_algorithms::push_front
         (this->tree_type::header_ptr(), to_insert, this->prio_node_prio_comp(this->priv_pcomp()));
      this->tree_type::sz_traits().increment();
   }

   //! <b>Effects</b>: Erases the element pointed to by i.
   //!
   //! <b>Complexity</b>: Average complexity for erase element is constant time.
   //!
   //! <b>Throws</b>: if the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   iterator erase(const_iterator i)
   {
      const_iterator ret(i);
      ++ret;
      node_ptr to_erase(i.pointed_node());
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(to_erase));
      node_algorithms::erase
         (this->tree_type::header_ptr(), to_erase, this->prio_node_prio_comp(this->priv_pcomp()));
      this->tree_type::sz_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      return ret.unconst();
   }

   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!
   //! <b>Complexity</b>: Average complexity for erase range is at most
   //!   O(log(size() + N)), where N is the number of elements in the range.
   //!
   //! <b>Throws</b>: if the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   iterator erase(const_iterator b, const_iterator e)
   {  size_type n;   return private_erase(b, e, n);   }

   //! <b>Effects</b>: Erases all the elements with the given value.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: if the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   size_type erase(const key_type &key)
   {  return this->erase(key, this->key_comp());   }

   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "comp".
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: if the internal priority_compare function throws.
   //!   Equivalent guarantee to <i>while(beg != end) erase(beg++);</i>
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class KeyType, class KeyTypeKeyCompare>
   BOOST_INTRUSIVE_DOC1ST(size_type
      , typename detail::disable_if_convertible<KeyTypeKeyCompare BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I size_type>::type)
      erase(const KeyType& key, KeyTypeKeyCompare comp)
   {
      std::pair<iterator,iterator> p = this->equal_range(key, comp);
      size_type n;
      private_erase(p.first, p.second, n);
      return n;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed to by i.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Complexity</b>: Average complexity for erase element is constant time.
   //!
   //! <b>Throws</b>: if the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {
      node_ptr to_erase(i.pointed_node());
      iterator ret(this->erase(i));
      disposer(this->get_value_traits().to_value_ptr(to_erase));
      return ret;
   }

   #if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   template<class Disposer>
   iterator erase_and_dispose(iterator i, Disposer disposer)
   {  return this->erase_and_dispose(const_iterator(i), disposer);   }
   #endif

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Complexity</b>: Average complexity for erase range is at most
   //!   O(log(size() + N)), where N is the number of elements in the range.
   //!
   //! <b>Throws</b>: if the internal priority_compare function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  size_type n;   return private_erase(b, e, n, disposer);   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given value.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: if the priority_compare function throws then weak guarantee and heap invariants are broken.
   //!   The safest thing would be to clear or destroy the container.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer)
   {
      std::pair<iterator,iterator> p = this->equal_range(key);
      size_type n;
      private_erase(p.first, p.second, n, disposer);
      return n;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "comp".
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: if the priority_compare function throws then weak guarantee and heap invariants are broken.
   //!   The safest thing would be to clear or destroy the container.
   //!
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   BOOST_INTRUSIVE_DOC1ST(size_type
      , typename detail::disable_if_convertible<KeyTypeKeyCompare BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I size_type>::type)
      erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer)
   {
      std::pair<iterator,iterator> p = this->equal_range(key, comp);
      size_type n;
      private_erase(p.first, p.second, n, disposer);
      return n;
   }

   //! <b>Effects</b>: Erases all of the elements.
   //!
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   if it's a safe-mode or auto-unlink value_type. Constant time otherwise.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   void clear()
   {  tree_type::clear(); }

   //! <b>Effects</b>: Erases all of the elements calling disposer(p) for
   //!   each node to be erased.
   //! <b>Complexity</b>: Average complexity for is at most O(log(size() + N)),
   //!   where N is the number of elements in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. Calls N times to disposer functor.
   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {
      node_algorithms::clear_and_dispose(this->tree_type::header_ptr()
         , detail::node_disposer<Disposer, value_traits, TreapAlgorithms>(disposer, &this->get_value_traits()));
      node_algorithms::init_header(this->tree_type::header_ptr());
      this->tree_type::sz_traits().set_size(0);
   }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   //! @copydoc ::boost::intrusive::bstree::merge_unique
   template<class T, class ...Options2> void merge_unique(sgtree<T, Options2...> &);
   #else
   template<class Compare2>
   void merge_unique(treap_impl
      <ValueTraits, VoidOrKeyOfValue, Compare2, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> &source)
   #endif
   {
      node_ptr it   (node_algorithms::begin_node(source.header_ptr()))
             , itend(node_algorithms::end_node  (source.header_ptr()));

      while(it != itend){
         node_ptr const p(it);
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(p));
         it = node_algorithms::next_node(it);

         if( node_algorithms::transfer_unique
               ( this->header_ptr(), this->key_node_comp(this->key_comp())
               , this->prio_node_prio_comp(this->priv_pcomp()), source.header_ptr(), p) ){
            this->sz_traits().increment();
            source.sz_traits().decrement();
         }
      }
   }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   //! @copydoc ::boost::intrusive::bstree::merge_equal(bstree<T, Options2...>&)
   template<class T, class ...Options2> void merge_equal(sgtree<T, Options2...> &);
   #else
   template<class Compare2>
   void merge_equal(treap_impl
      <ValueTraits, VoidOrKeyOfValue, Compare2, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> &source)
   #endif
   {
      node_ptr it   (node_algorithms::begin_node(source.header_ptr()))
             , itend(node_algorithms::end_node  (source.header_ptr()));

      while(it != itend){
         node_ptr const p(it);
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(p));
         it = node_algorithms::next_node(it);
         node_algorithms::transfer_equal
            ( this->header_ptr(), this->key_node_comp(this->key_comp())
            , this->prio_node_prio_comp(this->priv_pcomp()), source.header_ptr(), p);
         this->sz_traits().increment();
         source.sz_traits().decrement();
      }
   }

   //! @copydoc ::boost::intrusive::bstree::check(ExtraChecker)const
   template <class ExtraChecker>
   void check(ExtraChecker extra_checker) const
   {
      typedef detail::key_nodeptr_comp<priority_compare, value_traits, priority_of_value> nodeptr_prio_comp_t;
      tree_type::check(detail::treap_node_extra_checker
         <ValueTraits, nodeptr_prio_comp_t, ExtraChecker>
            (this->prio_node_prio_comp(this->priv_pcomp()), extra_checker));
   }

   //! @copydoc ::boost::intrusive::bstree::check()const
   void check() const
   {  check(detail::empty_node_checker<ValueTraits>());  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::bstree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::bstree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::bstree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::bstree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::bstree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::bstree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::bstree::remove_node
   void remove_node(reference value);

   friend bool operator< (const treap_impl &x, const treap_impl &y);

   friend bool operator==(const treap_impl &x, const treap_impl &y);

   friend bool operator!= (const treap_impl &x, const treap_impl &y);

   friend bool operator>(const treap_impl &x, const treap_impl &y);

   friend bool operator<=(const treap_impl &x, const treap_impl &y);

   friend bool operator>=(const treap_impl &x, const treap_impl &y);

   friend void swap(treap_impl &x, treap_impl &y);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   /// @cond
   private:
   template<class Disposer>
   iterator private_erase(const_iterator b, const_iterator e, size_type &n, Disposer disposer)
   {
      for(n = 0; b != e; ++n)
        this->erase_and_dispose(b++, disposer);
      return b.unconst();
   }

   iterator private_erase(const_iterator b, const_iterator e, size_type &n)
   {
      for(n = 0; b != e; ++n)
        this->erase(b++);
      return b.unconst();
   }
   /// @endcond
};


//! Helper metafunction to define a \c treap that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void
                , class O7 = void>
#endif
struct make_treap
{
   typedef typename pack_options
      < treap_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef treap_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::priority_of_value
         , typename packed_options::priority
         , typename packed_options::size_type
         , packed_options::constant_time_size
         , typename packed_options::header_holder_type
         > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6, class O7>
#else
template<class T, class ...Options>
#endif
class treap
   :  public make_treap<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_treap
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(treap)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::priority_compare   priority_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::reverse_iterator           reverse_iterator;
   typedef typename Base::const_reverse_iterator     const_reverse_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE treap()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit treap( const key_compare &cmp
                 , const priority_compare &pcmp = priority_compare()
                 , const value_traits &v_traits = value_traits())
      :  Base(cmp, pcmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE treap( bool unique, Iterator b, Iterator e
       , const key_compare &cmp = key_compare()
       , const priority_compare &pcmp = priority_compare()
       , const value_traits &v_traits = value_traits())
      :  Base(unique, b, e, cmp, pcmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE treap(BOOST_RV_REF(treap) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE treap& operator=(BOOST_RV_REF(treap) x)
   {  return static_cast<treap&>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const treap &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(treap) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static treap &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<treap &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const treap &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static treap &container_from_iterator(iterator it)
   {  return static_cast<treap &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap &container_from_iterator(const_iterator it)
   {  return static_cast<const treap &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TREAP_HPP

/* treap.hpp
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
*/