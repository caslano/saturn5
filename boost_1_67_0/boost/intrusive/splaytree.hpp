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

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(iterator)
   static splaytree_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const splaytree_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static splaytree_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const splaytree_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;

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
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e);

   //! @copydoc ::boost::intrusive::bstree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::bstree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::bstree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::bstree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::bstree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::bstree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::bstree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::clear
   void clear();

   //! @copydoc ::boost::intrusive::bstree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

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
   void splay_up(iterator i)
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
   void rebalance();

   //! @copydoc ::boost::intrusive::bstree::rebalance_subtree
   iterator rebalance_subtree(iterator root);

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

   BOOST_INTRUSIVE_FORCEINLINE static splaytree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<splaytree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splaytree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const splaytree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static splaytree &container_from_iterator(iterator it)
   {  return static_cast<splaytree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splaytree &container_from_iterator(const_iterator it)
   {  return static_cast<const splaytree &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SPLAYTREE_HPP

/* splaytree.hpp
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
*/