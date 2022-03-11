/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_SET_HPP
#define BOOST_INTRUSIVE_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/rbtree.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class multiset_impl;
#endif

//! The class template set is an intrusive container, that mimics most of
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
class set_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, RbTreeAlgorithms, HeaderHolder>
#endif
{
   /// @cond
   typedef bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, RbTreeAlgorithms, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(set_impl)

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
   //! @copydoc ::boost::intrusive::rbtree::rbtree()
   set_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::rbtree::rbtree(const key_compare &,const value_traits &)
   explicit set_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::rbtree::rbtree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   set_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(true, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::rbtree::rbtree(rbtree &&)
   set_impl(BOOST_RV_REF(set_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::rbtree::operator=(rbtree &&)
   set_impl& operator=(BOOST_RV_REF(set_impl) x)
   {  return static_cast<set_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::rbtree::~rbtree()
   ~set_impl();

   //! @copydoc ::boost::intrusive::rbtree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::rbtree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::rbtree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::rbtree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::rbtree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::rbtree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::rbtree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::rbtree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::rbtree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::rbtree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::rbtree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::rbtree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::rbtree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::rbtree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::rbtree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::rbtree::container_from_end_iterator(iterator)
   static set_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::rbtree::container_from_end_iterator(const_iterator)
   static const set_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::rbtree::container_from_iterator(iterator)
   static set_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::rbtree::container_from_iterator(const_iterator)
   static const set_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::rbtree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::rbtree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::rbtree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::rbtree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::rbtree::swap
   void swap(set_impl& other);

   //! @copydoc ::boost::intrusive::rbtree::clone_from(const rbtree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::rbtree::clone_from(rbtree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(set_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique(reference)
   std::pair<iterator, bool> insert(reference value)
   {  return tree_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique(const_iterator,reference)
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

   //! @copydoc ::boost::intrusive::rbtree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_unique_commit
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::rbtree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::rbtree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::rbtree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::rbtree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::rbtree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::rbtree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::clear
   void clear();

   //! @copydoc ::boost::intrusive::rbtree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::rbtree::count(const key_type &)const
   size_type count(const key_type &key) const
   {  return static_cast<size_type>(this->tree_type::find(key) != this->tree_type::cend()); }

   //! @copydoc ::boost::intrusive::rbtree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return static_cast<size_type>(this->tree_type::find(key, comp) != this->tree_type::cend()); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::find(const KeyType&,KeyTypeKeyCompare)const
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

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::rbtree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::rbtree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::rbtree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::rbtree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::rbtree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::rbtree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::rbtree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::rbtree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::rbtree::merge_unique
   template<class ...Options2>
   void merge(set<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::rbtree::merge_unique
   template<class ...Options2>
   void merge(multiset<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }


   template<class Compare2>
   void merge(multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const set_impl<T, Options...> &x, const set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(set_impl<T, Options...> &x, set_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c set that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_set
{
   /// @cond
   typedef typename pack_options
      < rbtree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef set_impl
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
class set
   :  public make_set<T,
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
   O1, O2, O3, O4, O5, O6
   #else
   Options...
   #endif
   >::type
{
   typedef typename make_set
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(set)
   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE set()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit set( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE set( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE set(BOOST_RV_REF(set) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE set& operator=(BOOST_RV_REF(set) x)
   {  return static_cast<set &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static set &container_from_iterator(iterator it)
   {  return static_cast<set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const set &container_from_iterator(const_iterator it)
   {  return static_cast<const set &>(Base::container_from_iterator(it));   }
};

#endif

//! The class template multiset is an intrusive container, that mimics most of
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
class multiset_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, RbTreeAlgorithms, HeaderHolder>
#endif
{
   /// @cond
   typedef bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, RbTreeAlgorithms, HeaderHolder> tree_type;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(multiset_impl)
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
   //! @copydoc ::boost::intrusive::rbtree::rbtree()
   multiset_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::rbtree::rbtree(const key_compare &,const value_traits &)
   explicit multiset_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::rbtree::rbtree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   multiset_impl( Iterator b, Iterator e
                , const key_compare &cmp = key_compare()
                , const value_traits &v_traits = value_traits())
      : tree_type(false, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::rbtree::rbtree(rbtree &&)
   multiset_impl(BOOST_RV_REF(multiset_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::rbtree::operator=(rbtree &&)
   multiset_impl& operator=(BOOST_RV_REF(multiset_impl) x)
   {  return static_cast<multiset_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::rbtree::~rbtree()
   ~multiset_impl();

   //! @copydoc ::boost::intrusive::rbtree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::rbtree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::rbtree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::rbtree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::rbtree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::rbtree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::rbtree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::rbtree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::rbtree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::rbtree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::rbtree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::rbtree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::rbtree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::rbtree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::rbtree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::rbtree::container_from_end_iterator(iterator)
   static multiset_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::rbtree::container_from_end_iterator(const_iterator)
   static const multiset_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::rbtree::container_from_iterator(iterator)
   static multiset_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::rbtree::container_from_iterator(const_iterator)
   static const multiset_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::rbtree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::rbtree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::rbtree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::rbtree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::rbtree::swap
   void swap(multiset_impl& other);

   //! @copydoc ::boost::intrusive::rbtree::clone_from(const rbtree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::rbtree::clone_from(rbtree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(multiset_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_equal(reference)
   iterator insert(reference value)
   {  return tree_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_equal(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_equal(hint, value);  }

   //! @copydoc ::boost::intrusive::rbtree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::rbtree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::rbtree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::rbtree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::rbtree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::rbtree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::rbtree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::clear
   void clear();

   //! @copydoc ::boost::intrusive::rbtree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   //! @copydoc ::boost::intrusive::rbtree::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::rbtree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::rbtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::rbtree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::rbtree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::rbtree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::rbtree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::rbtree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::rbtree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::rbtree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::rbtree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::rbtree::merge_equal
   template<class ...Options2>
   void merge(multiset<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::rbtree::merge_equal
   template<class ...Options2>
   void merge(set<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   template<class Compare2>
   void merge(set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(multiset_impl<T, Options...> &x, multiset_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_multiset
{
   /// @cond
   typedef typename pack_options
      < rbtree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef multiset_impl
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
class multiset
   :  public make_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(multiset)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE multiset()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit multiset( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE multiset( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE multiset(BOOST_RV_REF(multiset) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE multiset& operator=(BOOST_RV_REF(multiset) x)
   {  return static_cast<multiset &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static multiset &container_from_iterator(iterator it)
   {  return static_cast<multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SET_HPP

/* set.hpp
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
*/