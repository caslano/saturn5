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
   iterator begin();

   //! @copydoc ::boost::intrusive::splaytree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::splaytree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::splaytree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::splaytree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::splaytree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::splaytree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::splaytree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::splaytree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::splaytree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::splaytree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::splaytree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::splaytree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::splaytree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::splaytree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(iterator)
   static splay_set_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(const_iterator)
   static const splay_set_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(iterator)
   static splay_set_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(const_iterator)
   static const splay_set_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::splaytree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::splaytree::size()const
   size_type size() const;

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
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::splaytree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::splaytree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::splaytree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::splaytree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::clear
   void clear();

   //! @copydoc ::boost::intrusive::splaytree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

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
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::splaytree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::splaytree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::splaytree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::splaytree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::splaytree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::splaytree::splay_up(iterator)
   void splay_up(iterator i);

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator splay_down(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const key_type &key)
   iterator splay_down(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::rebalance
   void rebalance();

   //! @copydoc ::boost::intrusive::splaytree::rebalance_subtree
   iterator rebalance_subtree(iterator root);

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

   BOOST_INTRUSIVE_FORCEINLINE static splay_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<splay_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const splay_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static splay_set &container_from_iterator(iterator it)
   {  return static_cast<splay_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_set &container_from_iterator(const_iterator it)
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
   iterator begin();

   //! @copydoc ::boost::intrusive::splaytree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::splaytree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::splaytree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::splaytree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::splaytree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::splaytree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::splaytree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::splaytree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::splaytree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::splaytree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::splaytree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::splaytree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::splaytree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::splaytree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(iterator)
   static splay_multiset_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::splaytree::container_from_end_iterator(const_iterator)
   static const splay_multiset_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(iterator)
   static splay_multiset_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::splaytree::container_from_iterator(const_iterator)
   static const splay_multiset_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::splaytree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::splaytree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::splaytree::size()const
   size_type size() const;

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
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::splaytree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::splaytree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::splaytree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::splaytree::erase(const key_type&)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const key_type&, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::splaytree::clear
   void clear();

   //! @copydoc ::boost::intrusive::splaytree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

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
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::splaytree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::splaytree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::splaytree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::splaytree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::splaytree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::splaytree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::splaytree::splay_up(iterator)
   void splay_up(iterator i);

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator splay_down(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::splaytree::splay_down(const key_type &key)
   iterator splay_down(const key_type &key);

   //! @copydoc ::boost::intrusive::splaytree::rebalance
   void rebalance();

   //! @copydoc ::boost::intrusive::splaytree::rebalance_subtree
   iterator rebalance_subtree(iterator root);

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

   BOOST_INTRUSIVE_FORCEINLINE static splay_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<splay_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const splay_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static splay_multiset &container_from_iterator(iterator it)
   {  return static_cast<splay_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const splay_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const splay_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SPLAY_SET_HPP

/* splay_set.hpp
sEADsFWw5wAkBbDpAOp87C4wljGIIAI4FKDIAhYL1CawdcjyAuFZylOgRQBXgZxZ7DEgt2BAmpDhOqDpkJV+8V1kB1gfuB6Q1r54Q6gFlJVDqGPAY+fSYPkw+XT5ePm8GWx8JCHhGETpITRHER3EgDpEQKQIGfHCRAyRqLEEF5FIGxGoRF4JUCcY9TPNQ7b5MI66P5p2NBDq53JpWa4hrmGqk++RTyGqI3z/+CbtzHsNXhrRd6N0osgKKxVYvTB4I3PFsWc3TgmkBmnqGDOAj2PaDRHYMLMDRY2UaCAn+57aEL1Dv+IwnUsdekZZV6cInSO93TYivF8UiJsym2Obg5ujVcc7pu0MW+u5VylqfiT/8mOFeBPAxAoUzXqeEvHY0WCFi6vlW1qAZYX6BR7nY89OnbK5gK+HueUzatCkhY1+AG2EshrRamCzBSg6PoE7DnAo/hH9oyFHRB6bPDy+l+JI51zjrMUx48Cf4cjbFoA9AXuAdOO4RAMAAOYA9uNf/el/VuTZyhAqBCSFjTjVJ4tafM5OdqG4KJWd6THHApUJgwkInFXTGQlnWkUHOTQPs2VpQqU5XppQft5OAMUgnpIBhI7LJDm1epJgKn6/5BM5WhyGb01EB/42hO7DVihfUXJk406txJTsWuW5D+txYCA0RBtTq6a1DlAiB/+NXL5ckECJ0rik3bljtiif/cBSTNEc+hwHHcMfk1EVHU/Lrc6slqOpgpXDtAKPBXs6FMbnq0KSKDWBjCGkWAjSAIImUo+3Nebf7lNPAShPf0CSQLmNrWclUSY6FKWEijSGt4oEKuYibQsoTJFIXZwHT6owy2Egr3IxWx1WEVni/TlAkdumOoDwDghubQwRZoABlDWjY22MIcCA3CcDIlzXbtAf0T8NhQ9nLtEKIz/a6B4q8g9h4jCSqZ0NB0Bv3QGZTwUZEHNvEDGSu06Jp3tEmJkHM5BBIQlXHI+ggU5SXJJtWJ5lLaGQJFlSNTwOVDzEprWRoesgqWeYcV52+XnrNXrg0BR92it0ytfak5BUXsINUe3GF2V25elqQku0yNj6iQ2pxP+c3ryy98ldb7mJIcB78CdrlmhNK5O62q1X69RBwo7bz2q+jerv1xUMIqmP/1ulAfxWU4DSzdOKH92np8NgkQRgLV+v7USf1LH8WZi9d/rJ65WXfhlzUV0Xa41HpUvOkOvUOnQ0Db2e3a7WNnf6Fve0xh3Bzl029Zc9KiYy10fZqhne360Dzbujha+cI+Qqtch3d5LMPC+UFvbDu0/2eFk4D5R0aYzWaxQX3WmKHLTDn+3jxF69HkXrS3TNh/TSYRAW2qwurn0e3iK6L9HBNxKoGhUnyWfshK1aztRnMhXqiqOBQnXIByxsVFHaq8pc6Gt+6Kl7K3AGWfz0tpoavEwZ3HjiWUcP7ARVNWHKLpk/f05LZiUCJbZZsRrLksdvyt8Dwn4KEiQFBFJiiwoDQH0W67D+doW5oU0eiF1eVKsuSghCfnXdsmHxbnQqiAMO7iH+Bm/kwtmUCJFhXyFg5Ehb53Nzg82Vtr8E2AbVqnGYcwVi9LkMt4K8BfKfRck5svOMq+2UX57HOArfPM+v2fiwl9al1JYPa9AvMzQt66+LdDt9/HuqPu4qYKdetFunKTYmhNA8GoGZ8G2qV1U42tkrvGUBLq/rf8vFa4U/nk7aqz1eLEJ9TSwyTf4lP0pG60Ih0eka0es+ZPrl7iw8dyYCfSzuutqpNYF+zJXEoZEy2yxX8QGmLCJt3rULx7FbXgvTw+eKIv11T7uuw8V+Lj/4WcCb98IQOBXHC6s3hKf/1h9+6Q8tjrz5dr8bLJFGInEyguHzvzjwNSL+99OJVQb83c9KdvPyHAUz2Kp23ea/OugipTvgnWr/SrMwt/IX6GUHHg1lk5dYij3KDkK1hOcaIYzDb8m5X9ej51XOxnW7+IzXei752FWO3rjQS3ywwTLRm9qpp7Spg5MllMcGfadFD15cnY7ij3aLt1FGpKt8vy8iu0GYb+OwTdFnn/uOyuczJ/2tQuHnyWceOltmTlcbmVn2lGV6VbguO6507U9wg5H9+bKFpG18835K3kS1LL+L8HcYba630tfosJ9+qUS3PRLsyfS0aW4PdQ9OV7ay+kuKpcuDaKSt/nVm5yiRczv8X3A1DjzXmtuOFA13s/Wsu3f7WDn8P3p/f2ZtCru6JC+MSTmR+In2DBbBNxQBIDUsP4VsvkJNHxsE7iGC6QGRdtkGduGE8VRJvK14crMuU3lc3lnEzP0tpBXbfxqrJajemyj1/lxSonnSBXYPIXHeLs0DAMoAlHcv5RK/kAXconsfULzmdeDgAbaOP80jJVOmwbUK30yhaEOj1clhugc5ijQju8LUTbw7v/sKQQo5W26e09oVz27LRgNyVx9GQ3o1MIrjtzWVa7ecpVSWtqOgy87XW/c+G78vzRhZvsj1Ld2Zf/CMRGfyg44OYbsv0zGerXxhRU5q2Kv+HJ7Ci+c1MZ8ny2T3KDXlZLzssnj/YahmvvJYEKEqKv4UHRvGWaEl02T/t9M8Iy2Z0dNHYtCgH+R4pNz0N8p5hmD8MkfXy3V5Qni+Z8c9B8P06JuIeT2glfk9cQnVy41nHJqVznnr8O7WYmcz+JC4yN3TA3xj272qHFdmg61ITbXkX+bOZGVuPXvO2XXzvQn2YEDuYvciWUd7JYqIVxU82h+baRuOSfcY1HD0nDQquKW1D7Nj98Xchk5hXbiUDkiOCjN4w4mCFwWz1Lj1I590TzlD3b1nfhKyJXznAayYZacBkxYROtJ/1/0QcgjesOSoYi6Ve1BiIPXTwxlkisUTh5MEdH1NsAb7d2EmYZfOI/cmkMLFBgjrkiPDyVlZ56lBN39ibqoSY3kUhzIo3IYpj0F5mrAc32Y7j/X4giONqcQKC+ACCf84GnAEBwJgG/nl48cxwNSFnaXrPt01/QssZ9uZz6NCHZVKj0AKa6Ti5bJ9Z5LsosF0AnDLKteOi0uIMB48KIlajccYX1kFyiPYp9clUo3Yx+j/xhc7G8/g6hIYgRj1t0w7NoveL2ZcH+5F8Wjzz/Gf+9mZfxwLI6dS/lCNP5g5rBSIO6hnn35OK6d/kmPKfoDSE0X3qPVsvjkVUNjiYwltrJGrrSuymB3h4Kp0Yv4S01SZ/LNfL9icxr0yQRfGkXq5zI/TPbcqgEnpHkXjFsXNcvIeEp4sjS5QTUoXLwWeBpX22TBK498oGq1pkd219G3n6ni8FUg0nUS+NZFasjbnG6gfy+XHoPEaTNJkP7Pu2xq3bFu7luc6IWHV1TEzYMtlPrzw2hqUTnYFBn8PfnayWP+iZNKbiTkWanAfhv3z+mkKUl0heMywwlnQzEjltpBRpc9ZIZZ+6byXg7tfO9yIkMeK3T4JtUJH05GyqZ+68fNeLfy2+kYf+nmvH27Z8Xsxy7OSreVX8h+VTeTm56GBbQL+ZlpJHPH+mSSJzswNCWFB+JCIGnAoaJESZvAvBAdLBYdQxKZVAk1UBQY04bXG3Q1bsIWoQGlI3dKX/JhRIsJNYAk6QSIAmyb24DMzGWBr4O7DFbznnw4DeO/NgpV7SMSwpeN5dTl67UkI65Kt7u44yPvxeOizM5Bjnp2+670V3BtNsAr78X4/KUmuZpMn2RN/nYn4ME0QVTcd/4quSfy8apVf5JmcbMhMU2puKCRotSsseoO31gXPfrIz531lhaKe5D0xWm6D6m652GjJHfsix1UuKnmCOvC29SbD6+loTi+ucKOaYHQpD192H47Z9mWWNMh5//7ma3bPq5vf2mIj9oc7MDJy+rcXMQ7tjZeU/W+oA9VIbnsbIMN9St9d75ZH2XT0n6yfdjzMdAfL0qi3ocKJfTFy/9ZyB6/Ky0qs65QnWg+QcqO5A2jR90pHmrG68ocuvan9eKpaKvZA9Um0dOfaDBJtBZqdn1Jj1ZuQuevsILU6+WPzIqzPAveCe05uE4KkO12302YmKdWaK2FB3gGIuJQ/MyfQCTDpFAL59STh/jQJL5175pdd1Xl6UFgawnEJP8LLRG90G06AFbYAh4gjCxDawQGdA5Vs2jhm4VGURqZOhxBSEWEDDSEdLhSAEK2D7w/AZt1R9EGxkViGDhZ9Upm/j+347cJziQQ5k4DIoCGAAQMTNOitPzB6EHguhPR/fzVedXt6JKs+c+SyQMpKC2vZ5tsoERpkBoFBzSNFQcoewnYFEkX/JTAo3o8AFgLisKG1bNpDqi462B2AieM6b9uLIcpej6VLKaERSlSk+ttFmi9al/L0leN8nc1CMH3y4N0zcxN/8/DpU+x543fTfpJ7letda6qRAvezM673Ta70KZ1XD9/jafG03D8Ffs37s+DO+qXWteN6tdS6Qutf8DQ9mgT/FkVD3eystmz+bre2pNx7fFpE38V6+aSejsbW/XgVP7jJ7Kat7O9zLjBI3wq7tdxq/KxtzXPR0VXj/7AFm+729V2gup/e6rf0dZt5MLy81IuN75GvwttzXS06Tm2/QPPxGYw6Odnbk7+xrOvxNIdsah+DYagey/O+/7LR670XGZy8xFrhZ2xDzOdZvcMtac+r9ypjuVPi3dNWKf4ah07v9/O4fy5f+nkRvyyZFrkVz8ci0mN60/6RNwPhQ++G2bofSG3P8zM/UdTp5zX4siBfujxHvt5BZ9HlK9Hq7/OZ1rbfWH2Q7HTDa8z5Gs+dx6nRdqqwsrGz2Ww01mcQgqIPGqHTVcDHmac8K05L0KgnLVj2SU/51/x7wM2QnW7aSbr1R862doUVPx5pneSKZjJmpbTWv88p77efP5yGDFiN/9dzkCgOTUNQpLWP6hzP9rR28+Lufd49yxyvek35+QVIaNs3X9Oq/e52XYSw2f6Al+lu2xmNpoSzzBLCnBOYJiP989RaffOhkocB+p4l9MDb2ADGx5SCMZWAYZdgePbSewjGy2l8ZiMZy5TWhoH2kH3vDvK29WasCwwO/y8usdd+DN0Ic3Tiq3Gn4vV9cRlNemCt60+0I75Z4K0rsB1DyQu88PbfLFV6G7Ve/qOr8NjwFR71Zlfz+ZebH0ffm1RxcfN4TA73mwnyDlpu1p+ceK0Rf3OZLI+5x13VG610ToXF2lHn8iL2iFxWbX3soBlvDKAvNCusbc2H24Mfz315fg5XZtkX2bF2Htan+krwbY6vQ+N3ko8g5EEvd4nXLvkH3bh0e8vcZrsT8ZIFupNr6G52KvfnHHC+6WZTng+p+1y+L7c42Vr6K1bfWA6T0YiRm3DcPy9m7+bCA19w/gYc9V9HD7W+PhfOmg+5SaV2V53/NizPVfXdZ3Q7wWm9j9au6b9dP4ZEh+G73r+d0Xe4vz7Tzppb5ao0WOce9mTDPsuUO07kOk6Gl4D1pr6U2b8mOzasc/2VPex+8lXX/YHZXxnkqltQlr70pQDs89mbsEVX0G3rXGLlfILMFJSq9lBDNp8VRgVzaOrLyaTznoPWBQPcneN1t76nQWxPIsF+xtv8n/m5rm3m2aT9ZBKLBYtoWp66oe0vuZEPiu61WgfGogQFAqy4zAknVpuMakiP11Wtlri/8nRObLrcJcBnpOkvx1j4kLnqjQ54HjrXjbP5G74e40NjlfWu+Q+Pyx1P4Fy+Vx1eb6Y8d/D+NLyh/xS4plPDLX5x3mXjq/Mn8Pu89JVg89x8o6x/bRvv14gjp7vP2Gcu72u+b2KsxJzon7G1quf543r1PJYvQIJ9fBB34GHdarzg46Gk22f78/kOL9kdxGyY1/rcOp+tifNtWNO1PyRxWOqcbSZfQNlVlLNts7nt7tiiY4nFtEqlm8n6uCi9VBSEZjH5G22GH3wvdL9IO9/Mh39wQaOd7eAuWFpIrpXc4fN3Xx7CX+RcTwEr4Xt3dZ1UiU/geTwEC8cf83a3G8mMh0fe4Hh8wJ3Q2gIHqy/kJvSe+zwKqO6Q6/vbquqIT1a0vT6/nTJYpHbAQrxzimyB/uhj19kZCEYL1p+lNWnAXKza/agDB4kquwTHFL/BYqbwUpBbz84SvvxA9ctgq2s9++sxbHW+4G9ZSytdt658++yCndaZLHojKzt54chx8tkvLgHDw2r1rL2snC9c6L3Olfg9b2uyxvtxlhguc90w6b7MoJ95ebrHXre8N6u7l3Q9Py0PDO3M/PUiPbhjnyG7uXuEk/25dfRtf8iL314R1kH9sXoem8PVw32KpbV9WvDvPhn/R94MT+9LeZ1jh4//VVhxmG31g3Q1JryWml2Rl7Wi62q3dLdNzN/e7jV6CF6y4l3z9RHv24u/m1nu+eIk2/pZn7me/MJ9TivNFfP5Ibz354XpQzZm53ZZqvNh9COO9ma+/qeyPXSnq22//0Ro/bxFu1T2zc8g0/1MW7eTR//v+8EQ+Aq6Ki/ngdDPjNnmArWfsdV7WTjNkiSteVqNtptZC9t35gGtPQpt243rzM+edzZtxc/DC5t8PJ77C/fXvGyi/8/6e/uZ66vuz+5Fqf/8Ta9sNsWV2oKAlDkZ/1cNW07JTnVp65l79P0H5tf+R5bGTuz2ks9rOVyFMeONVctfrzL3IerKSsK6qFFYh79EN0ZoFcTxxvOdWY4TnVlR7MdgrID0t9UdX7qyqk1V5yuG32tO4VpPfLmpXapTO2s0omXg2+sQXURKKg/ddU9WS0wWFY+dP9/Tx7Xf1krl880/D9zZ/CqUuBXfNzc2NZMnrhXXgf7cfh85U6SDDEKxo09vpe9PNzbTJ5iWMRBrcm3xlT393NmfvHJBkANg8afxKj/H3n+cm3DUHvFOts5/fninf478g35UxBRYtEMSzopMmqUg+lsf7W5Oo7OFHLI06UG6jx+9Ca07+uggCAcXwG8HRsix8z3GHr0hIKrU2KaCHJYRA5sFEm0IFY5zyELIMm2BNoizwa7Vy3H+GbaYXm380/+HE12iiX34QAptg/UY4DkVtFsrlacYedRQPx0sw2IOPhET53VqzLa0iDjBaAPQ2CillyIl+pEdpjuFnmGHR8NEWCkFwVWHjQ7qplEXN/fxuFQ0v6Rpusc/Vrrwcbp+gAlUmS4Li3K7HTxVpizTz4ez3z1uNAbICIG95sI/wwoQfNZw9mqHEz7Xg4moYOAtqkZWJ7bWlLdfEOd7K4i+Cc2AkZ3QrKw1jw288O+hYOeNuaYbIX63OuCdOqAlJVL+mlZW3RNW05QxGLSvTCAqAgHgb1c7ei3k1LR0Gc0I+gQRQb1sSIcZEA1Pq7ghIyo4BQCLibJBbdSxToLsVt0gy32CIaJKLGcBF/hhCJ+pwWxQ/6dVQClU8FpDOX2aeYpiiJehQ+1mlIQq60PghH7sSRBz5XSmappqerM8W3cPtPQ1ogZw4AVAwWBtaSPuT1I9Uobo1iRwEfB4WM3zWrjG6PREacgWYsx9HOCtzmblriluC0jiV8M5iECRy2fRLk+IVf5DovtHDF3tmsztJ8jEa60bA59+GPDkSKBq8YPmpPi/bCjfJkP81BrUnIYhw4bre4AS9+HjRw7Q/GdZpi1i6qt+CHohjlYMr/B4zQqo6Z7QheHl28/ZWd/F2VEzwEFRVQ1H7iQB6bWuEv6v9DQ1BelSz4nLUmld+z2GPle7+BGrlFU77MV6XItLUVhj7tTg2rP1E0bKLv4QfYZWsBldK52vQK5awOUpuTH0S068fQJKfH+PoGzymEPIgw3ksNsQnVwHb++gVPLHXciw5xCOXAfIDCAiGZCdzzIEapkEeapLOBsWEwuwRaf9/XLRrk7M6FCYkzoNhRe+Twllz54Tj54q3xDWPa+J1uQTaEM+6MPJ9ROIWCXh6y4w0G4qBmOFVgRmIErJpKw7KA6dgLU6KdgYKoCqtGmXwfeLEIUZZAbe6QTd6LGb2mRLX0K8ws4uG68UdQ6Ncoc6Gyx4xonsgLrdwJD7i11aHmMgE5hRYLG/HpD2YPrms9zeFkJ/BFgPoH1LH7j/CgjT1XKKYkHqlpCWPaoXKPvAmhGL2CZfJV8mXykD1EiD+F9XKqgcGU3ZLZM0JMO5jZgnBKm/UbtUQtDD9obTfOMyVXXiSlDEBu4Y+zhkewIv5XjDN9NhRzvfET14EL5WYMLvQ/THT9kXbSLrmOXe/Eu6AsD4nB7hR2OvnFhPVz0JuIHREFrTInxkx0EmA0LMbQj2v/+nkmIbjyZwX2uCE4GpWd8u4+obuLoJR9qqE65TCXuaPYgnFSX+jer0lxlE3hZhvNCs1aBa/zCQ8ccQRE7HFhdwVxGKpzcYiAg0dz9wjhhl1qfPeRsV8id1oH2QIAakNawGAWl11o8Yob2y2e1YDoln4R+bBfvO9B+qjAVJigCugE+Z0DFLhPLQP2e3vMg9T9NVC7dvDIg2jBzoEhq312QwssMJoEJIYWZcGrw+rSCjzaD4XVUCmcne9EK7UrSPws5oG24KrP3aHp6nKCiq+TjKBua2NAH1ulOaVHsm3jj9iRo1vkSeien5EcTM7m2q1etBzlbwnGG6cEBC2HaN8175VIDUCRQ9sgGKCmGYNTCjOK2IrygwD+q09fwWeXZ5YujpVI/jed42HD1RThi3T3X3ME+tXVG0g6mSp1qTd81wndMuPyEe7MeD6umXMkdQqQY3APdrFNFx0JFUtDA+IdQmK9DL96J9JrCgizkNWBUeaKAatKA4KBr9wO6iWZ/gM5w0SH71YVk9wANu3wklYzCtQmNH9Cv7PqbIITqCzcQLCQHtBNuYi8K46U51gTp6e/AoEjWqw0li7/QKJ9JjVA/6Q+StVF/oiz04/sOcP8P90eCQuVAGcGU96aYHI/sciHnAeo0Ty7An/uGfV2CuJd065wb8OwYv7OVXI7GmfVhU0FLMBMJkn41uncdL0T9PnRgM3M5AHzHD4In2V7dxqe4YwNVU0/k0UV118JQYupfG80tzOKg38SaJsuTWRXn4y2IitP5Lf6QILSymxBKXby1503JAywW3HhBIcbsIJhWYE+7anyIc3s6ruNYWW3Je+6qfoPAFPAVbWbAF31jl17uJ2SypSFVtyAuzwp/iuOknSTsKbte2Yc8csJE0Bw0maO3KIM8lAzs9BOQD+zeMufEz6ROvDEqLBheH+g97wrRSz1fujVT4gMR8wHbWvxFnCTrLoM5NbbdRLPZnBhN88VJqdheCYwHXVjgdhtyVRQpBAsm0Eak=
*/