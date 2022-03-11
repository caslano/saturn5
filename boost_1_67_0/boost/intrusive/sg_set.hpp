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
#ifndef BOOST_INTRUSIVE_SG_SET_HPP
#define BOOST_INTRUSIVE_SG_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/sgtree.hpp>
#include <boost/static_assert.hpp>
#include <boost/move/utility_core.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class sg_multiset_impl;
#endif

//! The class template sg_set is an intrusive container, that mimics most of
//! the interface of std::sg_set as described in the C++ standard.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c floating_point<>, \c size_type<> and
//! \c compare<>.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool FloatingPoint, typename HeaderHolder>
#endif
class sg_set_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public sgtree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, FloatingPoint, HeaderHolder>
#endif
{
   /// @cond
   typedef sgtree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, FloatingPoint, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(sg_set_impl)

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
   //! @copydoc ::boost::intrusive::sgtree::sgtree()
   sg_set_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::sgtree::sgtree(const key_compare &,const value_traits &)
   explicit sg_set_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::sgtree::sgtree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   sg_set_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(true, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::sgtree::sgtree(sgtree &&)
   sg_set_impl(BOOST_RV_REF(sg_set_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::sgtree::operator=(sgtree &&)
   sg_set_impl& operator=(BOOST_RV_REF(sg_set_impl) x)
   {  return static_cast<sg_set_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::sgtree::~sgtree()
   ~sg_set_impl();

   //! @copydoc ::boost::intrusive::sgtree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::sgtree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::sgtree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::sgtree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::sgtree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::sgtree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::sgtree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::sgtree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::sgtree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::sgtree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::sgtree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::sgtree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::sgtree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::sgtree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::sgtree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(iterator)
   static sg_set_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(const_iterator)
   static const sg_set_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(iterator)
   static sg_set_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(const_iterator)
   static const sg_set_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::sgtree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::sgtree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::sgtree::swap
   void swap(sg_set_impl& other);

   //! @copydoc ::boost::intrusive::sgtree::clone_from(const sgtree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const sg_set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::sgtree::clone_from(sgtree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(sg_set_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique(reference)
   std::pair<iterator, bool> insert(reference value)
   {  return tree_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_unique(hint, value);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const key_type &key, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, commit_data); }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const key_type &key
      ,insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, commit_data); }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_unique_commit
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::sgtree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::sgtree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::sgtree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::sgtree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::clear
   void clear();

   //! @copydoc ::boost::intrusive::sgtree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::sgtree::count(const key_type &)const
   size_type count(const key_type &key) const
   {  return static_cast<size_type>(this->tree_type::find(key) != this->tree_type::cend()); }

   //! @copydoc ::boost::intrusive::sgtree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return static_cast<size_type>(this->tree_type::find(key, comp) != this->tree_type::cend()); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp)
   {  return this->tree_type::equal_range(key, comp); }

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return this->tree_type::equal_range(key, comp); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::sgtree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::sgtree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::sgtree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::sgtree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::sgtree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::sgtree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::sgtree::rebalance
   void rebalance();

   //! @copydoc ::boost::intrusive::sgtree::rebalance_subtree
   iterator rebalance_subtree(iterator root);

   //! @copydoc ::boost::intrusive::sgtree::balance_factor()
   float balance_factor() const;

   //! @copydoc ::boost::intrusive::sgtree::balance_factor(float)
   void balance_factor(float new_alpha);

   //! @copydoc ::boost::intrusive::rbtree::merge_unique
   template<class ...Options2>
   void merge(sg_set<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::rbtree::merge_unique
   template<class ...Options2>
   void merge(sg_multiset<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(sg_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, FloatingPoint, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   template<class Compare2>
   void merge(sg_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, FloatingPoint, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(sg_set_impl<T, Options...> &x, sg_set_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c sg_set that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_sg_set
{
   /// @cond
   typedef typename pack_options
      < sgtree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef sg_set_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::size_type
         , packed_options::floating_point
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
class sg_set
   :  public make_sg_set<T,
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
   O1, O2, O3, O4, O5, O6
   #else
   Options...
   #endif
   >::type
{
   typedef typename make_sg_set
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(sg_set)
   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE sg_set()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit sg_set( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE sg_set( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE sg_set(BOOST_RV_REF(sg_set) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE sg_set& operator=(BOOST_RV_REF(sg_set) x)
   {  return static_cast<sg_set &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const sg_set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(sg_set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static sg_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<sg_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const sg_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static sg_set &container_from_iterator(iterator it)
   {  return static_cast<sg_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_set &container_from_iterator(const_iterator it)
   {  return static_cast<const sg_set &>(Base::container_from_iterator(it));   }
};

#endif

//! The class template sg_multiset is an intrusive container, that mimics most of
//! the interface of std::sg_multiset as described in the C++ standard.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c floating_point<>, \c size_type<> and
//! \c compare<>.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool FloatingPoint, typename HeaderHolder>
#endif
class sg_multiset_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public sgtree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, FloatingPoint, HeaderHolder>
#endif
{
   /// @cond
   typedef sgtree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, FloatingPoint, HeaderHolder> tree_type;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(sg_multiset_impl)
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
   //! @copydoc ::boost::intrusive::sgtree::sgtree()
   sg_multiset_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::sgtree::sgtree(const key_compare &,const value_traits &)
   explicit sg_multiset_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::sgtree::sgtree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   sg_multiset_impl( Iterator b, Iterator e
                , const key_compare &cmp = key_compare()
                , const value_traits &v_traits = value_traits())
      : tree_type(false, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::sgtree::sgtree(sgtree &&)
   sg_multiset_impl(BOOST_RV_REF(sg_multiset_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::sgtree::operator=(sgtree &&)
   sg_multiset_impl& operator=(BOOST_RV_REF(sg_multiset_impl) x)
   {  return static_cast<sg_multiset_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::sgtree::~sgtree()
   ~sg_multiset_impl();

   //! @copydoc ::boost::intrusive::sgtree::begin()
   iterator begin();

   //! @copydoc ::boost::intrusive::sgtree::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::sgtree::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::sgtree::end()
   iterator end();

   //! @copydoc ::boost::intrusive::sgtree::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::sgtree::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::sgtree::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::sgtree::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::sgtree::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::sgtree::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::sgtree::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::sgtree::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::sgtree::root()
   iterator root();

   //! @copydoc ::boost::intrusive::sgtree::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::sgtree::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(iterator)
   static sg_multiset_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(const_iterator)
   static const sg_multiset_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(iterator)
   static sg_multiset_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(const_iterator)
   static const sg_multiset_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::sgtree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::sgtree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::sgtree::swap
   void swap(sg_multiset_impl& other);

   //! @copydoc ::boost::intrusive::sgtree::clone_from(const sgtree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const sg_multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::sgtree::clone_from(sgtree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(sg_multiset_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_equal(reference)
   iterator insert(reference value)
   {  return tree_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_equal(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_equal(hint, value);  }

   //! @copydoc ::boost::intrusive::sgtree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::sgtree::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::sgtree::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::sgtree::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::sgtree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::clear
   void clear();

   //! @copydoc ::boost::intrusive::sgtree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::sgtree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::sgtree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::sgtree::s_iterator_to(reference)
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::sgtree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::sgtree::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::sgtree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::sgtree::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::sgtree::remove_node
   void remove_node(reference value);

   //! @copydoc ::boost::intrusive::sgtree::rebalance
   void rebalance();

   //! @copydoc ::boost::intrusive::sgtree::rebalance_subtree
   iterator rebalance_subtree(iterator root);

   //! @copydoc ::boost::intrusive::sgtree::balance_factor()
   float balance_factor() const;

   //! @copydoc ::boost::intrusive::sgtree::balance_factor(float)
   void balance_factor(float new_alpha);

   //! @copydoc ::boost::intrusive::treap::merge_unique
   template<class ...Options2>
   void merge(sg_multiset<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::treap::merge_unique
   template<class ...Options2>
   void merge(sg_set<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(sg_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, FloatingPoint, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   template<class Compare2>
   void merge(sg_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, FloatingPoint, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(sg_multiset_impl<T, Options...> &x, sg_multiset_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c sg_multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_sg_multiset
{
   /// @cond
   typedef typename pack_options
      < sgtree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef sg_multiset_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::size_type
         , packed_options::floating_point
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
class sg_multiset
   :  public make_sg_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_sg_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(sg_multiset)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE sg_multiset()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit sg_multiset( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE sg_multiset( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE sg_multiset(BOOST_RV_REF(sg_multiset) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE sg_multiset& operator=(BOOST_RV_REF(sg_multiset) x)
   {  return static_cast<sg_multiset &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const sg_multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(sg_multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static sg_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<sg_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const sg_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static sg_multiset &container_from_iterator(iterator it)
   {  return static_cast<sg_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const sg_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SG_SET_HPP

/* sg_set.hpp
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
*/