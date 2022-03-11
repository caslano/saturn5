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
#ifndef BOOST_INTRUSIVE_AVL_SET_HPP
#define BOOST_INTRUSIVE_AVL_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/avltree.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class avl_multiset_impl;
#endif

//! The class template avl_set is an intrusive container, that mimics most of
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
class avl_set_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, AvlTreeAlgorithms, HeaderHolder>
#endif
{
   /// @cond
   typedef bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, AvlTreeAlgorithms, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(avl_set_impl)

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

   //! @copydoc ::boost::intrusive::avltree::avltree()
   avl_set_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::avltree::avltree(const key_compare &,const value_traits &)
   explicit avl_set_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::avltree::avltree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   avl_set_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(true, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::avltree::avltree(avltree &&)
   avl_set_impl(BOOST_RV_REF(avl_set_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::avltree::operator=(avltree &&)
   avl_set_impl& operator=(BOOST_RV_REF(avl_set_impl) x)
   {  return static_cast<avl_set_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::~avltree()
   ~avl_set_impl();

   //! @copydoc ::boost::intrusive::avltree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::avltree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::avltree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::avltree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::avltree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::avltree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::avltree::begin()
   reverse_iterator avlegin();

   //! @copydoc ::boost::intrusive::avltree::begin()const
   const_reverse_iterator avlegin() const;

   //! @copydoc ::boost::intrusive::avltree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::avltree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::avltree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::avltree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::avltree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::avltree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::avltree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(iterator)
   static avl_set_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(const_iterator)
   static const avl_set_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(iterator)
   static avl_set_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(const_iterator)
   static const avl_set_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::avltree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::avltree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::avltree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::avltree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::avltree::swap
   void swap(avl_set_impl& other);

   //! @copydoc ::boost::intrusive::avltree::clone_from(const avltree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const avl_set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::clone_from(avltree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(avl_set_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::avltree::insert_unique(reference)
   std::pair<iterator, bool> insert(reference value)
   {  return tree_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::avltree::insert_unique(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_unique(hint, value);  }

   //! @copydoc ::boost::intrusive::avltree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const key_type &key, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, commit_data); }

   //! @copydoc ::boost::intrusive::avltree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const key_type &key
      ,insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, commit_data); }

   //! @copydoc ::boost::intrusive::avltree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::avltree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::avltree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::avltree::insert_unique_commit
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::avltree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::avltree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::avltree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::avltree::erase(const key_type &key)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::clear
   void clear();

   //! @copydoc ::boost::intrusive::avltree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::count(const key_type &)const
   size_type count(const key_type &key) const
   {  return static_cast<size_type>(this->tree_type::find(key) != this->tree_type::cend()); }

   //! @copydoc ::boost::intrusive::avltree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return static_cast<size_type>(this->tree_type::find(key, comp) != this->tree_type::cend()); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::avltree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp)
   {  return this->tree_type::equal_range(key, comp); }

   //! @copydoc ::boost::intrusive::avltree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::avltree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return this->tree_type::equal_range(key, comp); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::avltree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::avltree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::avltree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::avltree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::avltree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::avltree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::avltree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::avltree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::avltree::merge_unique
   template<class ...Options2>
   void merge(avl_set<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::avltree::merge_unique
   template<class ...Options2>
   void merge(avl_multiset<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(avl_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }


   template<class Compare2>
   void merge(avl_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(avl_set_impl<T, Options...> &x, avl_set_impl<T, Options...> &y);

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
struct make_avl_set
{
   /// @cond
   typedef typename pack_options
      < avltree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef avl_set_impl
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
class avl_set
   :  public make_avl_set<T,
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
   O1, O2, O3, O4, O5, O6
   #else
   Options...
   #endif
   >::type
{
   typedef typename make_avl_set
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(avl_set)
   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE avl_set()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit avl_set( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE avl_set( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE avl_set(BOOST_RV_REF(avl_set) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE avl_set& operator=(BOOST_RV_REF(avl_set) x)
   {  return static_cast<avl_set &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const avl_set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(avl_set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static avl_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<avl_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const avl_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static avl_set &container_from_iterator(iterator it)
   {  return static_cast<avl_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_set &container_from_iterator(const_iterator it)
   {  return static_cast<const avl_set &>(Base::container_from_iterator(it));   }
};

#endif

//! The class template avl_multiset is an intrusive container, that mimics most of
//! the interface of std::_multiset as described in the C++ standard.
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
class avl_multiset_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, AvlTreeAlgorithms, HeaderHolder>
#endif
{
   /// @cond
   typedef bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, AvlTreeAlgorithms, HeaderHolder> tree_type;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(avl_multiset_impl)
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
   //! @copydoc ::boost::intrusive::avltree::avltree()
   avl_multiset_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::avltree::avltree(const key_compare &,const value_traits &)
   explicit avl_multiset_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::avltree::avltree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   avl_multiset_impl( Iterator b, Iterator e
                , const key_compare &cmp = key_compare()
                , const value_traits &v_traits = value_traits())
      : tree_type(false, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::avltree::avltree(avltree &&)
   avl_multiset_impl(BOOST_RV_REF(avl_multiset_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::avltree::operator=(avltree &&)
   avl_multiset_impl& operator=(BOOST_RV_REF(avl_multiset_impl) x)
   {  return static_cast<avl_multiset_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::avltree::~avltree()
   ~avl_multiset_impl();

   //! @copydoc ::boost::intrusive::avltree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::avltree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::avltree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::avltree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::avltree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::avltree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::avltree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::avltree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::avltree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::avltree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::avltree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::avltree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::avltree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::avltree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::avltree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(iterator)
   static avl_multiset_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(const_iterator)
   static const avl_multiset_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(iterator)
   static avl_multiset_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(const_iterator)
   static const avl_multiset_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::avltree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::avltree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::avltree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::avltree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::avltree::swap
   void swap(avl_multiset_impl& other);

   //! @copydoc ::boost::intrusive::avltree::clone_from(const avltree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const avl_multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::avltree::clone_from(avltree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(avl_multiset_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::avltree::insert_equal(reference)
   iterator insert(reference value)
   {  return tree_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::avltree::insert_equal(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_equal(hint, value);  }

   //! @copydoc ::boost::intrusive::avltree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::avltree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::avltree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::avltree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::avltree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::clear
   void clear();

   //! @copydoc ::boost::intrusive::avltree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::avltree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &key upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::avltree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::avltree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::avltree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::avltree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::avltree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::avltree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::avltree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::avltree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::avltree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::avltree::merge_equal
   template<class ...Options2>
   void merge(avl_multiset<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::avltree::merge_equal
   template<class ...Options2>
   void merge(avl_set<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(avl_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   template<class Compare2>
   void merge(avl_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(avl_multiset_impl<T, Options...> &x, avl_multiset_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c avl_multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_avl_multiset
{
   /// @cond
   typedef typename pack_options
      < avltree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef avl_multiset_impl
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
class avl_multiset
   :  public make_avl_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_avl_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(avl_multiset)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE avl_multiset()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit avl_multiset( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE avl_multiset( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE avl_multiset(BOOST_RV_REF(avl_multiset) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE avl_multiset& operator=(BOOST_RV_REF(avl_multiset) x)
   {  return static_cast<avl_multiset &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const avl_multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(avl_multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static avl_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<avl_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const avl_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static avl_multiset &container_from_iterator(iterator it)
   {  return static_cast<avl_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const avl_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_AVL_SET_HPP

/* avl_set.hpp
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
*/