/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2013-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_BS_SET_HPP
#define BOOST_INTRUSIVE_BS_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/bstree.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class ValueTraits, class VoidOrKeyOfValue, class Compare, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class bs_multiset_impl;
#endif

namespace boost {
namespace intrusive {

//! The class template bs_set is an intrusive container, that mimics most of
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
class bs_set_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, BsTreeAlgorithms, HeaderHolder>
#endif
{
   /// @cond
   typedef bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, BsTreeAlgorithms, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(bs_set_impl)

   typedef tree_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
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
   //! @copydoc ::boost::intrusive::bstree::bstree()
   bs_set_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(const key_compare &,const value_traits &)
   explicit bs_set_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   bs_set_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(true, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   bs_set_impl(BOOST_RV_REF(bs_set_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   bs_set_impl& operator=(BOOST_RV_REF(bs_set_impl) x)
   {  return static_cast<bs_set_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~bs_set_impl();

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
   static bs_set_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const bs_set_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static bs_set_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const bs_set_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::bstree::swap
   void swap(bs_set_impl& other);

   //! @copydoc ::boost::intrusive::bstree::clone_from(const bstree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const bs_set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(bs_set_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::bstree::insert_unique(reference)
   std::pair<iterator, bool> insert(reference value)
   {  return tree_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::bstree::insert_unique(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_unique(hint, value);  }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const key_type &key, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, commit_data); }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const key_type &key
      ,insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, commit_data); }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, comp, commit_data); }

   //! @copydoc ::boost::intrusive::bstree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::bstree::insert_unique_commit
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
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

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::count(const key_type &)const
   size_type count(const key_type &key) const
   {  return static_cast<size_type>(this->tree_type::find(key) != this->tree_type::cend()); }

   //! @copydoc ::boost::intrusive::bstree::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return static_cast<size_type>(this->tree_type::find(key, comp) != this->tree_type::cend()); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)
   iterator lower_bound(const key_type &);

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

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp)
   {  return this->tree_type::equal_range(key, comp); }

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return this->tree_type::equal_range(key, comp); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type&,const key_type&,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type& lower_key, const key_type& upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type&,const key_type&,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type& lower_key, const key_type& upper_key, bool left_closed, bool right_closed) const;

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

   //! @copydoc ::boost::intrusive::bstree::merge_unique
   template<class ...Options2>
   void merge(bs_set<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::bstree::merge_unique
   template<class ...Options2>
   void merge(bs_multiset<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(bs_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }


   template<class Compare2>
   void merge(bs_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const bs_set_impl<T, Options...> &x, const bs_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const bs_set_impl<T, Options...> &x, const bs_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const bs_set_impl<T, Options...> &x, const bs_set_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const bs_set_impl<T, Options...> &x, const bs_set_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(bs_set_impl<T, Options...> &x, bs_set_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c bs_set that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_bs_set
{
   /// @cond
   typedef typename pack_options
      < bstree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef bs_set_impl
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
class bs_set
   :  public make_bs_set<T,
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
   O1, O2, O3, O4, O5, O6
   #else
   Options...
   #endif
   >::type
{
   typedef typename make_bs_set
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(bs_set)
   public:
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE bs_set()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit bs_set( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE bs_set( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bs_set(BOOST_RV_REF(bs_set) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE bs_set& operator=(BOOST_RV_REF(bs_set) x)
   {  return static_cast<bs_set &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const bs_set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(bs_set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static bs_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<bs_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const bs_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static bs_set &container_from_iterator(iterator it)
   {  return static_cast<bs_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_set &container_from_iterator(const_iterator it)
   {  return static_cast<const bs_set &>(Base::container_from_iterator(it));   }
};

#endif

//! The class template bs_multiset is an intrusive container, that mimics most of
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
class bs_multiset_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, BsTreeAlgorithms, HeaderHolder>
#endif
{
   /// @cond
   typedef bstree_impl<ValueTraits, VoidOrKeyOfValue, Compare, SizeType, ConstantTimeSize, BsTreeAlgorithms, HeaderHolder> tree_type;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(bs_multiset_impl)
   typedef tree_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
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
   //! @copydoc ::boost::intrusive::bstree::bstree()
   bs_multiset_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(const key_compare &,const value_traits &)
   explicit bs_multiset_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   bs_multiset_impl( Iterator b, Iterator e
                , const key_compare &cmp = key_compare()
                , const value_traits &v_traits = value_traits())
      : tree_type(false, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   bs_multiset_impl(BOOST_RV_REF(bs_multiset_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   bs_multiset_impl& operator=(BOOST_RV_REF(bs_multiset_impl) x)
   {  return static_cast<bs_multiset_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~bs_multiset_impl();

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
   static bs_multiset_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const bs_multiset_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static bs_multiset_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const bs_multiset_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::bstree::swap
   void swap(bs_multiset_impl& other);

   //! @copydoc ::boost::intrusive::bstree::clone_from(const bstree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const bs_multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(bs_multiset_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   //! @copydoc ::boost::intrusive::bstree::insert_equal(reference)
   iterator insert(reference value)
   {  return tree_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::bstree::insert_equal(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_equal(hint, value);  }

   //! @copydoc ::boost::intrusive::bstree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
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
      (const key_type & lower_key, const key_type & upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type & lower_key, const key_type & upper_key, bool left_closed, bool right_closed) const;

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

   //! @copydoc ::boost::intrusive::bstree::merge_equal
   template<class ...Options2>
   void merge(bs_multiset<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::bstree::merge_equal
   template<class ...Options2>
   void merge(bs_set<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(bs_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   template<class Compare2>
   void merge(bs_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

template<class T, class ...Options>
bool operator!= (const bs_multiset_impl<T, Options...> &x, const bs_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>(const bs_multiset_impl<T, Options...> &x, const bs_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator<=(const bs_multiset_impl<T, Options...> &x, const bs_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
bool operator>=(const bs_multiset_impl<T, Options...> &x, const bs_multiset_impl<T, Options...> &y);

template<class T, class ...Options>
void swap(bs_multiset_impl<T, Options...> &x, bs_multiset_impl<T, Options...> &y);

#endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

//! Helper metafunction to define a \c bs_multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_bs_multiset
{
   /// @cond
   typedef typename pack_options
      < bstree_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef bs_multiset_impl
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
class bs_multiset
   :  public make_bs_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_bs_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;

   BOOST_MOVABLE_BUT_NOT_COPYABLE(bs_multiset)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE bs_multiset()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit bs_multiset( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE bs_multiset( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bs_multiset(BOOST_RV_REF(bs_multiset) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE bs_multiset& operator=(BOOST_RV_REF(bs_multiset) x)
   {  return static_cast<bs_multiset &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const bs_multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(bs_multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static bs_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<bs_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const bs_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static bs_multiset &container_from_iterator(iterator it)
   {  return static_cast<bs_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const bs_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_BS_SET_HPP

/* bs_set.hpp
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
*/