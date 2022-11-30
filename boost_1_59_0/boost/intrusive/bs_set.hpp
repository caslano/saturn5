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
   static bs_set_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const bs_set_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static bs_set_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const bs_set_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const BOOST_NOEXCEPT;

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
   iterator insert_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
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

   BOOST_INTRUSIVE_FORCEINLINE static bs_set &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<bs_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_set &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const bs_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static bs_set &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<bs_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_set &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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
   static bs_multiset_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const bs_multiset_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static bs_multiset_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const bs_multiset_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const BOOST_NOEXCEPT;

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

   BOOST_INTRUSIVE_FORCEINLINE static bs_multiset &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<bs_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_multiset &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const bs_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static bs_multiset &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<bs_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bs_multiset &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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