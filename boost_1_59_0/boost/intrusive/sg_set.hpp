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
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(iterator)
   static sg_set_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(const_iterator)
   static const sg_set_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(iterator)
   static sg_set_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(const_iterator)
   static const sg_set_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::size()const
   size_type size() const BOOST_NOEXCEPT;

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
   iterator insert_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::sgtree::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

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
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rebalance
   void rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rebalance_subtree
   iterator rebalance_subtree(iterator root) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::balance_factor()
   float balance_factor() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::balance_factor(float)
   void balance_factor(float new_alpha) BOOST_NOEXCEPT;

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

   BOOST_INTRUSIVE_FORCEINLINE static sg_set &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<sg_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_set &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const sg_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static sg_set &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<sg_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_set &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(iterator)
   static sg_multiset_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_end_iterator(const_iterator)
   static const sg_multiset_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(iterator)
   static sg_multiset_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::container_from_iterator(const_iterator)
   static const sg_multiset_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::sgtree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::size()const
   size_type size() const BOOST_NOEXCEPT;

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
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::sgtree::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::sgtree::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

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
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rebalance
   void rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::rebalance_subtree
   iterator rebalance_subtree(iterator root) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::balance_factor()
   float balance_factor() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::sgtree::balance_factor(float)
   void balance_factor(float new_alpha) BOOST_NOEXCEPT;

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

   BOOST_INTRUSIVE_FORCEINLINE static sg_multiset &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<sg_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_multiset &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const sg_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static sg_multiset &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<sg_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const sg_multiset &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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