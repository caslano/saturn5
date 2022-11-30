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
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::begin()
   reverse_iterator avlegin();

   //! @copydoc ::boost::intrusive::avltree::begin()const
   const_reverse_iterator avlegin() const;

   //! @copydoc ::boost::intrusive::avltree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(iterator)
   static avl_set_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(const_iterator)
   static const avl_set_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(iterator)
   static avl_set_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(const_iterator)
   static const avl_set_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::avltree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::avltree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::size()const
   size_type size() const BOOST_NOEXCEPT;

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
   iterator insert_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::avltree::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase(const key_type &key)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

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
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

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

   BOOST_INTRUSIVE_FORCEINLINE static avl_set &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<avl_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_set &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const avl_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static avl_set &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<avl_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_set &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(iterator)
   static avl_multiset_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_end_iterator(const_iterator)
   static const avl_multiset_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(iterator)
   static avl_multiset_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::container_from_iterator(const_iterator)
   static const avl_multiset_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::avltree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::avltree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::size()const
   size_type size() const BOOST_NOEXCEPT;

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
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::avltree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::avltree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

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
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::avltree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

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

   BOOST_INTRUSIVE_FORCEINLINE static avl_multiset &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<avl_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_multiset &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const avl_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static avl_multiset &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<avl_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avl_multiset &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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