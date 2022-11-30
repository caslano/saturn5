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
#ifndef BOOST_INTRUSIVE_SPLAYTREE_HPP
#define BOOST_INTRUSIVE_SPLAYTREE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <cstddef>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //std::pair

#include <boost/static_assert.hpp>
#include <boost/intrusive/bstree.hpp>
#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/function_detector.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/splaytree_algorithms.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>
#include <boost/move/utility_core.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

struct splaytree_defaults
   : bstree_defaults
{};

/// @endcond

//! The class template splaytree is an intrusive splay tree container that
//! is used to construct intrusive splay_set and splay_multiset containers. The no-throw
//! guarantee holds only, if the key_compare object
//! doesn't throw.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<>, \c size_type<> and
//! \c compare<>.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class splaytree_impl
   /// @cond
   :  public bstree_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType, ConstantTimeSize, SplayTreeAlgorithms, HeaderHolder>
   /// @endcond
{
   public:
   typedef ValueTraits                                               value_traits;
   /// @cond
   typedef bstree_impl< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType
                      , ConstantTimeSize, SplayTreeAlgorithms
                      , HeaderHolder>                                tree_type;
   typedef tree_type                                                 implementation_defined;
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
   typedef typename implementation_defined::node_algorithms          node_algorithms;

   static const bool constant_time_size = implementation_defined::constant_time_size;
   /// @cond
   private:

   //noncopyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(splaytree_impl)

   /// @endcond

   public:

   typedef typename implementation_defined::insert_commit_data insert_commit_data;

   //! @copydoc ::boost::intrusive::bstree::bstree()
   splaytree_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(const key_compare &,const value_traits &)
   explicit splaytree_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   splaytree_impl( bool unique, Iterator b, Iterator e
              , const key_compare &cmp     = key_compare()
              , const value_traits &v_traits = value_traits())
      : tree_type(cmp, v_traits)
   {
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   splaytree_impl(BOOST_RV_REF(splaytree_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   splaytree_impl& operator=(BOOST_RV_REF(splaytree_impl) x)
   {  return static_cast<splaytree_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~splaytree_impl();

   //! @copydoc ::boost::intrusive::bstree::begin()
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(iterator)
   static splaytree_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const splaytree_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static splaytree_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const splaytree_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::swap
   void swap(splaytree_impl& other);

   //! @copydoc ::boost::intrusive::bstree::clone_from(const bstree&,Cloner,Disposer)
   //! Additional notes: it also copies the alpha factor from the source container.
   template <class Cloner, class Disposer>
   void clone_from(const splaytree_impl &src, Cloner cloner, Disposer disposer);

   #else //BOOST_INTRUSIVE_DOXYGEN_INVOKED

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(splaytree_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::insert_equal(reference)
   iterator insert_equal(reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_equal(const_iterator,reference)
   iterator insert_equal(const_iterator hint, reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert_equal(Iterator b, Iterator e);

   //! @copydoc ::boost::intrusive::bstree::insert_unique(reference)
   std::pair<iterator, bool> insert_unique(reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_unique(const_iterator,reference)
   iterator insert_unique(const_iterator hint, reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_unique_check
      (const key_type &key, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const key_type &key, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_commit
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e);

   //! @copydoc ::boost::intrusive::bstree::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::count(const key_type &)const
   //! Additional note: non-const function, splaying is performed.
   size_type count(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::count(const KeyType&,KeyTypeKeyCompare)const
   //! Additional note: non-const function, splaying is performed.
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::count(const key_type &)const
   //! Additional note: const function, no splaying is performed
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::count(const KeyType&,KeyTypeKeyCompare)const
   //! Additional note: const function, no splaying is performed
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)
   //! Additional note: non-const function, splaying is performed.
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)const
   //! Additional note: const function, no splaying is performed
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "key"
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   //! Additional note: const function, no splaying is performed
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "value"
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)const
   //! Additional note: const function, no splaying is performed
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "key"
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   //! Additional note: const function, no splaying is performed
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "value"
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)const
   //! Additional note: const function, no splaying is performed
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "key"
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)const
   //! Additional note: const function, no splaying is performed
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "value"
   std::pair<iterator, iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)const
   //! Additional note: const function, no splaying is performed
   std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)
   //! Additional note: non-const function, splaying is performed for the first
   //! element of the equal range of "key"
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, iterator> equal_range(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   //! Additional note: const function, no splaying is performed
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> equal_range(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::merge_unique(bstree<T, Options2...>&)
   template<class T, class ...Options2>
   void merge_unique(splaytree<T, Options2...> &);

   //! @copydoc ::boost::intrusive::bstree::merge_equal(bstree<T, Options2...>&)
   template<class T, class ...Options2>
   void merge_equal(splaytree<T, Options2...> &);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Requires</b>: i must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Rearranges the container so that the element pointed by i
   //!   is placed as the root of the tree, improving future searches of this value.
   //!
   //! <b>Complexity</b>: Amortized logarithmic.
   //!
   //! <b>Throws</b>: Nothing.
   void splay_up(iterator i) BOOST_NOEXCEPT
   {  return node_algorithms::splay_up(i.pointed_node(), tree_type::header_ptr());   }

   //! <b>Effects</b>: Rearranges the container so that if *this stores an element
   //!   with a key equivalent to value the element is placed as the root of the
   //!   tree. If the element is not present returns the last node compared with the key.
   //!   If the tree is empty, end() is returned.
   //!
   //! <b>Complexity</b>: Amortized logarithmic.
   //!
   //! <b>Returns</b>: An iterator to the new root of the tree, end() if the tree is empty.
   //!
   //! <b>Throws</b>: If the comparison functor throws.
   template<class KeyType, class KeyTypeKeyCompare>
   iterator splay_down(const KeyType &key, KeyTypeKeyCompare comp)
   {
      detail::key_nodeptr_comp<value_compare, value_traits>
         key_node_comp(comp, &this->get_value_traits());
      node_ptr r = node_algorithms::splay_down(tree_type::header_ptr(), key, key_node_comp);
      return iterator(r, this->priv_value_traits_ptr());
   }

   //! <b>Effects</b>: Rearranges the container so that if *this stores an element
   //!   with a key equivalent to value the element is placed as the root of the
   //!   tree.
   //!
   //! <b>Complexity</b>: Amortized logarithmic.
   //!
   //! <b>Returns</b>: An iterator to the new root of the tree, end() if the tree is empty.
   //!
   //! <b>Throws</b>: If the predicate throws.
   iterator splay_down(const key_type &key)
   {  return this->splay_down(key, this->key_comp());   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::rebalance
   void rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::rebalance_subtree
   iterator rebalance_subtree(iterator root) BOOST_NOEXCEPT;

   friend bool operator< (const splaytree_impl &x, const splaytree_impl &y);

   friend bool operator==(const splaytree_impl &x, const splaytree_impl &y);

   friend bool operator!= (const splaytree_impl &x, const splaytree_impl &y);

   friend bool operator>(const splaytree_impl &x, const splaytree_impl &y);

   friend bool operator<=(const splaytree_impl &x, const splaytree_impl &y);

   friend bool operator>=(const splaytree_impl &x, const splaytree_impl &y);

   friend void swap(splaytree_impl &x, splaytree_impl &y);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

//! Helper metafunction to define a \c splaytree that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_splaytree
{
   /// @cond
   typedef typename pack_options
      < splaytree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef splaytree_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::size_type
         , packed_options::constant_time_size
         , typename packed_options::header_holder_type
         > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};


#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6>
#else
template<class T, class ...Options>
#endif
class splaytree
   :  public make_splaytree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_splaytree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(splaytree)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::reverse_iterator           reverse_iterator;
   typedef typename Base::const_reverse_iterator     const_reverse_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE splaytree()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit splaytree( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE splaytree( bool unique, Iterator b, Iterator e
         , const key_compare &cmp = key_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(unique, b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE splaytree(BOOST_RV_REF(splaytree) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE splaytree& operator=(BOOST_RV_REF(splaytree) x)
   {  return static_cast<splaytree &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const splaytree &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(splaytree) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static splaytree &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<splaytree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splaytree &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const splaytree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static splaytree &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<splaytree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splaytree &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const splaytree &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SPLAYTREE_HPP

/* splaytree.hpp
Y6XxdchD1chpyOVcOy8eNdWTAIVIFzTMRZuq9rKYm8WhdxPBfnCS/ZDF3RMjPq/GN2ZgQkmxI6+ZTzeLbosaL34nI509SFS4AeV/Eeu780w89vuJY6hnJfdbtQJMNoYUBRU+5zhHO1piEVF02qczCvpTLGKxyi6hqjByvfGcg7TnzuyEANKmAJCxmzpJLMf1XJy4fGPxZV4RCec0Ff9p+7nXXDlVzC9PilfcCRfhNzGxRx0wUWuHP29nKZpZkcfEuBvGymKuoaHfBIP9pRL7dRurmS5+wHul24p4glBKO24B2ULQAot1O746gyWZN0LeZQZcqSaly+/VpPWJ87eU8gS5E3U1mNRf/bTPuhWFkwv1AO6IRBd+Wf/fxcrySHNQF7m0LOgEqffqwb5B0sk6I/H2F6BtMwQp0paCXpM7oqLrHXWu1Hv1swTHy3qeY8V4DDjJW23SXyqE18fuZZU6FBO+7flHcb47YoybnRJH1Pj4ak4smeM028LK3x4NdsCQcXaaNKJdpdy2r9V/hZ1FTkvaKfP1I3JTc9dFc2/MYkoCev8zMMW2ArE7u309UClutProu9K7XFC04iKzz7SSIo52cexZr0XQaNEIKF+xuKk/ilkDEs/yNHi5m7vgZobk1UlLmMxb6N0OVmC4gi5EgMMOCbSC+REcse8vIWwgl8vIxSq5rbqWCGDrEgZO+w5jpxqW+KWMlgIlXRzSjaIRPdHfhfUPx15gciLc8xivh5KfIx9NXLBrAh4mC3oTF7+jsnwPVYoXavce2GlhIIbLk1FTtp7hXm9PF0TflY/3zvil87LIq93P1/GZVPD6Un27d4KKZnalwo+h3jx0DkzteF1kgXLedNZCDjvK9twM+hycEdksg0ERwXCWx3a54v2TaHvFdNeldNnTf/5mZJabl4zgAno2zWpCf/2yfpuAtB7idZbO3NDRVPnYq94YbR/CJhqTW29eE/CQnWxRca/LrqBFQ4hDBx0i6YSWoHPEwWypxup+jCH0CkVty5L4rbP1TlXKzFDOM7s+cSptH7vH+OuwbsrQ71BC7OyhDbktjJn0/NBPvlKm9NQd9nOhdfS4Be3+3Zer+h7RP6bp0wGJ3Z9S80xkyYxkxqT+xrIWvBAdlvDrdtPpFXNqfFYQ6v+KTXDfc5Qk4qpXMbnJisOlPou7UZsCp593BDUSD4LpTSZS2fFjCozAEWprWTiFW9K0L5kA7nzzuvw1sTamh3nGXjKVSGMBZDxlhDK/piybK/Tg6iVfwFkz5wPzy/AJC2wIQKnWg1TAU0jiNqNciHrzqCEb1Q+t4de+kgNHxNbt1K2frdKGUeJ9qKtiYbICwB31J05IqDy3XjvEROEaipP9SS+3cPvUQOIgw6FIMsaJI1o4xoqaTTlXUFTSTdvD5g1ok0VZrhRPe52quLNcVM9HXuDcnulRp+Ng1NZ+55N+dwChEqdZBwJBlvfmInhHPbLJhI1k+ystGvrFJD9+JWii9BndyyfFMAL61wTYu/JJ5iahYTixLXV9buTHxgLqz4eDCyU+Mo6RTd8vQ+Fq5Z7G2NdYKX7vXO+KU6lEzBPqa+BLXDw2hDrXg7XSH00nmDR6J/2rCn3y1gr+BE6T/z/WNueJbpqx02ip2ZbeG9WbDCZ+anYSxlxgaUkaD5s+fXHvO93zF62S29N7dRcEaMML/U+81QUV07+U6hTUWtcnV5tsNR0SHCPcGgb91RvlHkp3Pryd8prvS4v8qNBsv4k8sw8BhWqoTRv7y5bGyA+61yOJDL9y7XN4Fo/Xn4tnG9hbNdL1D7o6rEbu6SXHE3v+C95uoanunU5MCakIa4JOfu5FMHj9cdOHnz2FcudxdWySeSPhulTjdBWSNoZ8Rw5qWk1D8TQ8mWRLVoUCLCcXWW5ZrSp3XDhG/SBtkIKd4dZ2ykrsCvfdPQwE6ky/3NM/ihOnDj5puVQn8bLBsyHW8y11HL5Tt3oMA5tO+7ZEChC/XBVCDTtam87nBkEc0ZGTiBcylIy6EZRSWqc3cjZtOh2Cg0unw/Y7oaJdgeXk+fWYLmlZDiRe7G75npV8NCtVLLvnCwmEynSm1gf9/MwYEvubJcoD6zMAaDAQO/4S1zLokmkMKrrcNBgq7OkTeJTlzAPSFqTEXo1JMGmPSAO5p7rUahh9sv1Y1OjyIvFDwMsU4c6BSSMzDwRqJubimoVrQ6q4u55ekSmVXrS4omPzQUn+vj9kpda2+KVxPndSu/AdvnkGB8fel1VBTag1z6Pi263+Kw6vIPgLCW4bv9KaJLMi9NxBYaCfWKDuydeXg+Ce/xnrmOU0g9/DKVHedceDeyH4zAwNf75zpjTZTDwF1QCInoCue7HyqFVHq93GObPOWbW+Y5utmPx34SpF75XUcYsSmV8fGxSSe7361SH5XFiQGW1FHbiPVOqzu7NuHDtOuS4uic52rFq5HDinYT+5wnb+jr+rOOswYkw7USESN/8VJt8xMZ4acpwDsCp+as2Cjjk6nfOJQf+Mfm2y4mO3wLYJrMCr1ndkM07r53uigIerOq+58mFTKyQNCYYuY8V3jLrwfUyl/oZWzH3dHT9G2f9WsicHvFA1z20iIHkRDhxD3q01AtUt0rsl6EUCqNBMQo1HARJyjYzCRe0WBrJq6uuC/O/LEPP2jnw8qWAOqbsNeUmEgKfCaCbScU7LbDDIcXoLrxeoi5fxAgrnREIm1+l/tBfhjy5zzQKRCJLdV6zwXbDxnPqs+KOusupVOvSWywF0pfvBxf3v0zA5Gb6+KhNRLmITaKzH5k5mwTBi2T7wLyM4Zd9TiWWPtVJciTBO/umvi1JR2pl0pQCEJwLUa6z5Ei8snR0pdHu3MTXPT6MtVjaDTFC3DG7Uw2aelckIbpEN7Uokk0zNYZjALRDVpnrjy96X/SMBr4yIKLe2AQOtl3rzln6cqKbweCG4ZMhU9KBVM+C7mo+w6oqi0ez/jWKs4IbVvyvgumKiEIEEKOYkLA6VE8XsJX20uEr8WX5yN69M2Ao5s4YY6VWqkzVmS5h8zlLGHw8idiSFic3FKlbQOv2bEETju8Gs21qS8YGu0yAW5UunbIbPAjAfT40+uHcaZDIQhtsuBywhzGBnSnUhmNoJsiqaAFM1fazwzhTnnhJbay3tDsXTNLUO7UYjgR5BRxdzmkgnpfBolEBfc3mzRQGgmKkwsKx50dQWIMBFPln4leVxA0n8IkHhU4/JTkIWoB0ibtN6DFPfzF08+zBXPi8ghOac8KMMGfKjzzKGheSqFGXlmATag/y/gIo7NLaJ0ukVMe7VTMFKB+ZfnJsgsoO/e+DH/DJFX+Ts8m/HeiF3tP4r/caSV+LTe31YVukNb5QVO42fSONqYeoBtGOACbAmA+XnU+TujXJiS4NDAq4GORaolOaIZMvnjH2TLAK3svr3AUHVrRCOAFoZIKEqAdORGBKAaP0qEDgUO28DRqULUuVJ9rNtZy70ojyHVCetWl9pLA9yzEcIArkrl7LExQQAlD4z6Vxo8CK6u3IiKf1Hsj0ASFfRl04jjr341EqszTP6n/UgU9kNTWhNzitzJxH5EbDl3mujqobsr+x2CLnGrF2IbnEbqL4VX1+s+faek0EjRws+yx1BSs15S+yDVgYaqMPb2eD1ggdxO6ojIyneLMUmol/123c57t2VjOV5YnxddtiRzQu3q4Z8iV/F5CLl3XQv0xNI7k0aDLb6oomFNpEStbtSJbxUNT2bme+xD5TAXIlnA6AgfIEhA/1qBZT04zI74fpv+TwlyFrp3bx8W5Mcfl0d22khkDqd8COhPD2Lw5Qu3NvPvCNHytJ5d0tLX07kA7AqxXr1eL96Xx0Fplo7whC7dXqk3y7scqjXthqVdbpo595BOC5vzfP/D0jL4m7u+Rxh+OQRecFYTyx2JYr/kmD2VucEgtgpQ5+t0BkrivJMudsvVszd9LPV3vNPl1DKq7WZh/XqTFQysQ5AAM6nhNS9a3Se+IsXHxI2Acm/ezDMsPanaIhJVcR7TzAxQEXIhZMVwpvNxFKfWO9SCs9B/H5qfYKy39fR3V9VDRY7fw1ufBnLucNuG6fcKRrH4XUPjOeEo3HKtkn0fNath3Qz+igm8pW48nAHwnFLbEjf3CXAguxjb2Z1F9vtPlOqtPqaOdRhtQCsBH6sy71A6uu8A4qX5Wo0K9ASrs5Qd3akubxjqB5ra+RO39BD4GAy1iBhRHhdtb+t26lYxaCW2xWKQ3cdxJUMxVTdxua2IXYIsW1YlgoHpAWewYY58yCnLwuwrMfEnPT8MnCDATMIPJdhpCNeWDedJ9kTe+Stcu6yAB3Ubu65PCO3IGwQhLszkCXO9oOxS65/rQoxdo40Cg10yf5m0xzxF5SSm6wztf7KloEWgn/bgcJCLqTupQW3y0tVVlhxnuIU5lFCPjehJ+YeyH6ND51g7a98DoIHufhCP9KNc6GWIMVPFp2A7rW5VCX3WpYfbnDLVKtwDKhUVx1+K4NsH+1/28mBRXvW8qL6tt5QQ60LfnMnca0vDZ0czkT74L1fZJ+dX2MwcI4VVrYc/Cg7R7mqqK3LtJrMzZVJeY5d0vVG+3yG4XAt/QQNZ1ZVcTKOLHgaj29AVG/rnBiTU8YlysNsNLKc5ODF0GNjVOVWnh+eD1p3dXcv+0xCV7bebhn6LOgXUz18EWuS0BSA+IDteyYRgiyDcOu9UeB7y9JppE+Lt3y3LBFfxsf/oXOYj31SEIXsctC7cBWoVDtXkxejzrHhr/EMG1sSLQ2+tRohGznWdyDfI1FxXbKvOqPeXx2LLk06TMqoSus7Cb6wPY3gw0FtOaZvObYE+NIJmf3OaLfhpUzcSsUTU3uxhWx5AZ34FX6ufqxa6oG7DQl4YIOM9bTv8gyPS//iJDnycMDv7EiOhPrkHs0Ci9RKc+Z8Bv09dkGIb1ms19s+6Wi1H8iBMxJAsyG24+bbrTkqB9O9IY8V0LYUFHY/aOljx3lT6AyyEM0aZnklHyaF6XYZJo5rG1Q/ixhoNoROkzQA60mFEAkiVzY6wGQ6iCIVYkt3Dszod/ntMtYoSonoqa/5pt07xsN1CT2J6+EV/5PhAUMyav3nGM8bMaJcYT+Jjqxb7COkx/sfBWeoSBhHs1MJAXPNBMuMo1GkfaDs3j8FOfRGXkjiP6gkUMoolRHrr0VpkexaWlcMBXKty5k8eLJ/crq7x8PbibXm1bL2KOGv0qTAYmmVhg3u16q1dvGNkJVGCaV7b76tLLzAp+j4JALc6PTVJlutlfDPeCP6DnSQ2zUqTSNAbvtYHY2wWerVlI9uA5FVC4NtBTtq2eMzvM2Wmfu6pnNEF0IXipt7udJJ54ouTKwU8lj3Ct499NzOEQgXzS1b32Sl0FxNdaMKJ0+c8zdoqS1LhxEmhmM9KSYl6+OArpZoB0nHgsistOwrA6WjGb6cMcHIKrupK+o5Hu/vMjnb43hv22IZLNb8o1LN7C4UV1WLhfj+LYTKg1zS2BF70Qa3XaKrjVZAXOuA3DtVawQnzB5SuitUYGFtiYXRFWRAFyVXAbem8JqUgs7jYkUVjl0xjGeIv6lfAmZy9kFOwrPePTuBCO9m+hGP+CVl3eEw1vYbjCicWT/Houi6uByl2HsCyV5umpnTqVdMk84lQxMGoK6baOwf19FxL1NnDF/547Bemtq+P/5sSoanvuvveXcwZ/oSi3xcKuexRkPmYMKhEdzdEbh42tGP9Ul6VOlfCglrwzYlq4UcCuozcvwLuZXGNvO1cjg9LgAdii/TKzKTTifJJWkZ49m/Yr0u0wJeBA4SmSyq9f4j6u1/86cbb43o46gINnIPKQGaFHwDUuB/BR42m9fC7ozkIzuyJ5E7gtXczLHOGYuRqj/iXW3TaCqyRyDUqKEKfcahWhq4V4P7JzJzfdgknKrQpfM1QrkAX1EUDwWKHIm0L5xE53KVU87FvAOliyTZD9WWXgvBd0cQnTwkjIvQkCONm3DedpazD/3kAtudevDlxwrEgVD3ttQY7wUUMvO9AtOf2PQbqwMVFOYIVJzaODli14Qe6t4QvP7QOrWLaLouNyTp3i0qgEM4HYGpOciqUrsGm1cNRTHQYSXX0C1fEEb13sHCPg1e9ERl6mmbodxB5di38gKj1zoz8JQudn0WP5l4uNuD3riGE8rqi8pSTVhnc+Dfffs845PjP/JmPyyYt6HnQHZA8TYfIkGSwOM7713h73c9XpCSwCywP1Napw+pWmj4EXwOW0i7SZRG/ySxjTaGCGS9ZmRNHYjpKI5PoEARik/y+p2be9i6BmsCN4PDnYzK1G1HiddJfDjCHBYQtkIEAsDHh5XynX5cahbw833PjfEZ3h8lyY9egypZxgU/7FSgEjVEOqUZ4kwJ/bSRazce7kiFmAoKBOL7wj8bgHMm51tanzScN4+mAGRnb0F+kxFqiVLv1TH7h6AH7kfmketfkEqXcC17PW9mFTSLm1VNz5xkpfeBMii3PkG486aD5pGsnXIr2iELR4fVykf/TaBAmF0lm/CleJ2KEpohiqNY63JHumQuV/8YzNZyCzJ9WEel35gVSCOHcZVN0RaPF3DHig60ALnHaDJDB/vDEZvfy6UKafDypcNZzNhCYtOox0GoByk2Nso7DN6RS6qd/VeRKTCE0D2o8wL7DkgrRRgHahI3tX+VxdB+o07i+LMnjpycUVMwK+ZLBSecTZKW52aZ5CWdctbb0wkMioMDZzvvqjTkzB2SjizhnXrOepAklrVTfx/ZkQEYNtikZZ9i92Yz13/78XSg70g8xs6pacKSJjtCJqXHvpgIekzaQcBVELmtAOELqKAFrVPC1uAq8Q+KyeXQaKgpXtY7MMdm4+QjxTMhk9+jtzZtiVzJ9KKR5cH6UFuDOpLyhheica2C5Tjc6mcmLq9gGk9RS6sMZu3bbtyyqZGcW6HElf2Ze87faDriHOujMzwVtc3j+4TbHX051xRh8to6VGWXmTg082UwoiyVOIOu9xwf2g6+pQlUC9jqTlva1WHyvLUHcw5Miu1M8fwzY/wyxmZwTpRknqpwEoyBIUXIdyNPs5k/bFTOn6vsrI1AEVs/HFNFX/PP4T13hfW1E71PCkdwIVN95mdhApqCAcEd2cNt0MERFQPnh1Xs88z8jxemiJaEooernBucPQeyqHbdyOywTrSsevKF7ZUCYfdbsBkXkYFLF+zBIu9eCzute4kMOPbBf9lchBCIa+HMK2fKw37IgRNHVHkrbanWVUSxRjG+RAtle12EMJ7RydZQGN2YZN/dR3ybSMP60UF3OXmXE4+gWknvRh1jxgxdM1ahB6zJKqwyYZ8H/BFINHBa0IDqkID0wuO/TvCVV8SHrag/7EvIqLXX7yQp5Zlf1zHrVuvUXw6+fZkY4/tiWJGLQw+jvzBzTCtj9cMarmrQPmeo0UEcNL7Zdimm3qM/H4A3W0ZiImUddFLrhixSQ2exAQNBBg2kzfRWmIGi1041q/SnXjiykxBc5ByJDVUD2iSrpf8UBFMqmeVUw4CdPFX5xo69MMRjY6Ahq29E4SBMm9OBsXkENUvauBj1RtYwu07HO1XNKGZ9gEwIWdzEiu1nlLlFGjIArWm9pJ6LyUUl1lfoonAqUEIC
*/