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
#ifndef BOOST_INTRUSIVE_SPLAY_SET_HPP
#define BOOST_INTRUSIVE_SPLAY_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/splaytree.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class splay_multiset_impl;
#endif

namespace boost {
namespace intrusive {

//! The class template splay_set is an intrusive container, that mimics most of
//! the interface of std::set as described in the C++ standard.
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
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class splay_set_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public splaytree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, HeaderHolder>
#endif
{
   /// @cond
   typedef splaytree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(splay_set_impl)

   typedef tree_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
   typedef typename implementation_defined::value_traits             value_traits;
   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
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
   typedef typename implementation_defined::insert_commit_data       insert_commit_data;
   typedef typename implementation_defined::node_traits              node_traits;
   typedef typename implementation_defined::node                     node;
   typedef typename implementation_defined::node_ptr                 node_ptr;
   typedef typename implementation_defined::const_node_ptr           const_node_ptr;
   typedef typename implementation_defined::node_algorithms          node_algorithms;

   static const bool constant_time_size = tree_type::constant_time_size;

   public:
   //! @copydoc ::boost::intrusive::splaytree::splaytree()
   splay_set_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::splaytree::splaytree(const key_compare &,const value_traits &)
   explicit splay_set_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::splaytree::splaytree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   splay_set_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(true, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::splaytree::splaytree(splaytree &&)
   splay_set_impl(BOOST_RV_REF(splay_set_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::splaytree::operator=(splaytree &&)
   splay_set_impl& operator=(BOOST_RV_REF(splay_set_impl) x)
   {  return static_cast<splay_set_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::splaytree::~splaytree()
   ~splay_set_impl();

   //! @copydoc ::boost::intrusive::splaytree::begin()
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(iterator)
   static splay_set_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(const_iterator)
   static const splay_set_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(iterator)
   static splay_set_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(const_iterator)
   static const splay_set_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::size()const
   size_type size() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::swap
   void swap(splay_set_impl& other);

   //! @copydoc ::boost::intrusive::splaytree::clone_from(const splaytree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const splay_set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::splaytree::clone_from(splaytree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(splay_set_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::splaytree::insert_unique(reference)
   std::pair<iterator, bool> insert(reference value)
   {  return tree_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::splaytree::insert_unique(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_unique(hint, value);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const key_type &key, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, commit_data); }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const key_type &key
      ,insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, commit_data); }

   //! @copydoc ::boost::intrusive::splaytree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::splaytree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::splaytree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::splaytree::insert_unique_commit
   iterator insert_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::splaytree::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::splaytree::count(const key_type &)const
   size_type count(const key_type &key) const
   {  return static_cast<size_type>(this->tree_type::find(key) != this->tree_type::cend()); }

   //! @copydoc ::boost::intrusive::splaytree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return static_cast<size_type>(this->tree_type::find(key, comp) != this->tree_type::cend()); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::splaytree::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp)
   {  return this->tree_type::equal_range(key, comp); }

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return this->tree_type::equal_range(key, comp); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const key_type&,const key_type&,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const key_type&,const key_type&,bool,bool)const
   std::pair<const_iterator, const_iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::splaytree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::splay_up(iterator)
   void splay_up(iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator splay_down(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const key_type &key)
   iterator splay_down(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::rebalance
   void rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rebalance_subtree
   iterator rebalance_subtree(iterator root) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::merge_unique
   template<class ...Options2>
   void merge(splay_set<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::splaytree::merge_unique
   template<class ...Options2>
   void merge(splay_multiset<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(splay_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }


   template<class Compare2>
   void merge(splay_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(splay_set_impl<T, Options...> &x, splay_set_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c splay_set that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_splay_set
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

   typedef splay_set_impl
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
class splay_set
   :  public make_splay_set<T,
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
   O1, O2, O3, O4, O5, O6
   #else
   Options...
   #endif
   >::type
{
   typedef typename make_splay_set
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(splay_set)
   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE splay_set()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit splay_set( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE splay_set( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE splay_set(BOOST_RV_REF(splay_set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}

   BOOST_INTRUSIVE_FORCEINLINE splay_set& operator=(BOOST_RV_REF(splay_set) x)
   {  return static_cast<splay_set &>(this->Base::operator=(::boost::move(static_cast<Base&>(x))));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const splay_set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(splay_set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static splay_set &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<splay_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_set &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const splay_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static splay_set &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<splay_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_set &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const splay_set &>(Base::container_from_iterator(it));   }
};

#endif

//! The class template splay_multiset is an intrusive container, that mimics most of
//! the interface of std::multiset as described in the C++ standard.
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
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class splay_multiset_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public splaytree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, HeaderHolder>
#endif
{
   /// @cond
   typedef splaytree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, HeaderHolder> tree_type;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(splay_multiset_impl)
   typedef tree_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
   typedef typename implementation_defined::value_traits             value_traits;
   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
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
   typedef typename implementation_defined::insert_commit_data       insert_commit_data;
   typedef typename implementation_defined::node_traits              node_traits;
   typedef typename implementation_defined::node                     node;
   typedef typename implementation_defined::node_ptr                 node_ptr;
   typedef typename implementation_defined::const_node_ptr           const_node_ptr;
   typedef typename implementation_defined::node_algorithms          node_algorithms;

   static const bool constant_time_size = tree_type::constant_time_size;

   public:
   //! @copydoc ::boost::intrusive::splaytree::splaytree()
   splay_multiset_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::splaytree::splaytree(const key_compare &,const value_traits &)
   explicit splay_multiset_impl(const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::splaytree::splaytree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   splay_multiset_impl( Iterator b, Iterator e
                , const key_compare &cmp = key_compare()
                , const value_traits &v_traits = value_traits())
      : tree_type(false, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::splaytree::splaytree(splaytree &&)
   splay_multiset_impl(BOOST_RV_REF(splay_multiset_impl) x)
      :  tree_type(::boost::move(static_cast<tree_type&>(x)))
   {}

   //! @copydoc ::boost::intrusive::splaytree::operator=(splaytree &&)
   splay_multiset_impl& operator=(BOOST_RV_REF(splay_multiset_impl) x)
   {  return static_cast<splay_multiset_impl&>(tree_type::operator=(::boost::move(static_cast<tree_type&>(x)))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::splaytree::~splaytree()
   ~splay_multiset_impl();

   //! @copydoc ::boost::intrusive::splaytree::begin()
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(iterator)
   static splay_multiset_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(const_iterator)
   static const splay_multiset_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(iterator)
   static splay_multiset_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(const_iterator)
   static const splay_multiset_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::size()const
   size_type size() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::swap
   void swap(splay_multiset_impl& other);

   //! @copydoc ::boost::intrusive::splaytree::clone_from(const splaytree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const splay_multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::splaytree::clone_from(splaytree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(splay_multiset_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::splaytree::insert_equal(reference)
   iterator insert(reference value)
   {  return tree_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::splaytree::insert_equal(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_equal(hint, value);  }

   //! @copydoc ::boost::intrusive::splaytree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::splaytree::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase(const key_type&)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const key_type&, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::count(const key_type&)
   size_type count(const key_type&);

   //! @copydoc ::boost::intrusive::splaytree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const key_type&)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const key_type&)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const key_type&)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const key_type&)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::find(const key_type&)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::find(const key_type&)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::equal_range(const key_type&)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::equal_range(const key_type&)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::splaytree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const key_type&, const key_type&,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const_reference lower_value, const_reference upper_value, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const key_type&, const key_type&,bool,bool)const
   std::pair<const_iterator, const_iterator> bounded_range
      (const_reference lower_value, const_reference upper_value, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::splaytree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::splaytree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::splay_up(iterator)
   void splay_up(iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator splay_down(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const key_type &key)
   iterator splay_down(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::rebalance
   void rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::rebalance_subtree
   iterator rebalance_subtree(iterator root) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::splaytree::merge_equal
   template<class ...Options2>
   void merge(splay_multiset<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::splaytree::merge_equal
   template<class ...Options2>
   void merge(splay_set<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(splay_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   template<class Compare2>
   void merge(splay_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(splay_multiset_impl<T, Options...> &x, splay_multiset_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c splay_multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_splay_multiset
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

   typedef splay_multiset_impl
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
class splay_multiset
   :  public make_splay_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_splay_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(splay_multiset)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE splay_multiset()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit splay_multiset( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE splay_multiset( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE splay_multiset(BOOST_RV_REF(splay_multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}

   BOOST_INTRUSIVE_FORCEINLINE splay_multiset& operator=(BOOST_RV_REF(splay_multiset) x)
   {  return static_cast<splay_multiset &>(this->Base::operator=(::boost::move(static_cast<Base&>(x))));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const splay_multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(splay_multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static splay_multiset &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<splay_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_multiset &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const splay_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static splay_multiset &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<splay_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_multiset &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const splay_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SPLAY_SET_HPP

/* splay_set.hpp
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
*/