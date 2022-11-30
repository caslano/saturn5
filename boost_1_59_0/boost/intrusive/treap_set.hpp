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
#ifndef BOOST_INTRUSIVE_TREAP_SET_HPP
#define BOOST_INTRUSIVE_TREAP_SET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/treap.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class VoidOrPrioOfValue, class VoidOrPrioComp, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class treap_multiset_impl;
#endif

//! The class template treap_set is an intrusive container, that mimics most of
//! the interface of std::set as described in the C++ standard.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<>, \c size_type<>,
//! \c compare<>, \c priority<> and \c priority_of_value<>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class VoidOrPrioOfValue, class VoidOrPrioComp, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class treap_set_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public treap_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder>
#endif
{
   /// @cond
   public:
   typedef treap_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(treap_set_impl)

   typedef tree_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::value_traits             value_traits;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
   typedef typename implementation_defined::reference                reference;
   typedef typename implementation_defined::const_reference          const_reference;
   typedef typename implementation_defined::difference_type          difference_type;
   typedef typename implementation_defined::size_type                size_type;
   typedef typename implementation_defined::value_compare            value_compare;
   typedef typename implementation_defined::key_compare              key_compare;
   typedef typename implementation_defined::priority_type            priority_type;
   typedef typename implementation_defined::priority_compare         priority_compare;
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

   static const bool constant_time_size = implementation_defined::constant_time_size;

   public:
   //! @copydoc ::boost::intrusive::treap::treap()
   treap_set_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::treap::treap(const key_compare &,const priority_compare &,const value_traits &)
   explicit treap_set_impl( const key_compare &cmp
                          , const priority_compare &pcmp  = priority_compare()
                          , const value_traits &v_traits  = value_traits())
      :  tree_type(cmp, pcmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::treap::treap(bool,Iterator,Iterator,const key_compare &,const priority_compare &,const value_traits &)
   template<class Iterator>
   treap_set_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const priority_compare &pcmp  = priority_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(true, b, e, cmp, pcmp, v_traits)
   {}

   //! <b>Effects</b>: to-do
   //!
   treap_set_impl(BOOST_RV_REF(treap_set_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! <b>Effects</b>: to-do
   //!
   treap_set_impl& operator=(BOOST_RV_REF(treap_set_impl) x)
   {  return static_cast<treap_set_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x)));  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::treap::~treap()
   ~treap_set_impl();

   //! @copydoc ::boost::intrusive::treap::begin()
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(iterator)
   static treap_set_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(const_iterator)
   static const treap_set_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(iterator)
   static treap_set_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(const_iterator)
   static const treap_set_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::treap::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::treap::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::size()const
   size_type size() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::swap
   void swap(treap_set_impl& other);

   //! @copydoc ::boost::intrusive::treap::clone_from(const treap&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const treap_set_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif

   //! @copydoc ::boost::intrusive::treap::clone_from(treap&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(treap_set_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! @copydoc ::boost::intrusive::treap::top()
   BOOST_INTRUSIVE_FORCEINLINE iterator top() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::top()const
   BOOST_INTRUSIVE_FORCEINLINE const_iterator top() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::ctop()const
   BOOST_INTRUSIVE_FORCEINLINE const_iterator ctop() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rtop()
   BOOST_INTRUSIVE_FORCEINLINE reverse_iterator rtop() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rtop()const
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator rtop() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crtop()const
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator crtop() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crtop() const
   priority_compare priority_comp() const;
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::treap::insert_unique(reference)
   std::pair<iterator, bool> insert(reference value)
   {  return tree_type::insert_unique(value);  }

   //! @copydoc ::boost::intrusive::treap::insert_unique(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_unique(hint, value);  }

   //! @copydoc ::boost::intrusive::treap::insert_unique_check(const key_type&,const priority_type &,insert_commit_data&)
   std::pair<iterator, bool> insert_check( const key_type &key, const priority_type &prio, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, prio, commit_data); }

   //! @copydoc ::boost::intrusive::treap::insert_unique_check(const_iterator,const key_type&,const priority_type &,insert_commit_data&)
   std::pair<iterator, bool> insert_check
      ( const_iterator hint, const key_type &key, const priority_type &prio, insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, prio, commit_data); }

   //! @copydoc ::boost::intrusive::treap::insert_unique_check(const KeyType&,KeyTypeKeyCompare,PrioValuePrioCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare, class PrioType, class PrioValuePrioCompare>
   std::pair<iterator, bool> insert_check
      ( const KeyType &key, KeyTypeKeyCompare comp, const PrioType &prio, PrioValuePrioCompare pcomp
      , insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(key, comp, prio, pcomp, commit_data); }

   //! @copydoc ::boost::intrusive::treap::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,PrioValuePrioCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare, class PrioType, class PrioValuePrioCompare>
   std::pair<iterator, bool> insert_check
      ( const_iterator hint
      , const KeyType &key, KeyTypeKeyCompare comp
      , const PrioType &prio, PrioValuePrioCompare pcomp
      , insert_commit_data &commit_data)
   {  return tree_type::insert_unique_check(hint, key, comp, prio, pcomp, commit_data); }

   //! @copydoc ::boost::intrusive::treap::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_unique(b, e);  }

   //! @copydoc ::boost::intrusive::treap::insert_unique_commit
   iterator insert_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::treap::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::treap::count(const key_type &)const
   size_type count(const key_type &key) const
   {  return static_cast<size_type>(this->tree_type::find(key) != this->tree_type::cend()); }

   //! @copydoc ::boost::intrusive::treap::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return static_cast<size_type>(this->tree_type::find(key, comp) != this->tree_type::cend()); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::treap::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   #endif   //   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::treap::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::treap::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp)
   {  return this->tree_type::equal_range(key, comp); }

   //! @copydoc ::boost::intrusive::treap::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->tree_type::lower_bound_range(key); }

   //! @copydoc ::boost::intrusive::treap::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const
   {  return this->tree_type::equal_range(key, comp); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::treap::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::treap::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::treap::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::treap::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::treap::s_iterator_to(reference)
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;


   //! @copydoc ::boost::intrusive::treap::merge_unique
   template<class ...Options2>
   void merge(treap_set<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::treap::merge_unique
   template<class ...Options2>
   void merge(treap_multiset<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(treap_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   template<class Compare2>
   void merge(treap_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_unique(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};


//! Helper metafunction to define a \c treap_set that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void
                , class O7 = void>
#endif
struct make_treap_set
{
   typedef typename pack_options
      < treap_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef treap_set_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::priority_of_value
         , typename packed_options::priority
         , typename packed_options::size_type
         , packed_options::constant_time_size
         , typename packed_options::header_holder_type
         > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6, class O7>
#else
template<class T, class ...Options>
#endif
class treap_set
   :  public make_treap_set<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_treap_set
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(treap_set)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::priority_compare   priority_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE treap_set()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit treap_set( const key_compare &cmp
                     , const priority_compare &pcmp = priority_compare()
                     , const value_traits &v_traits = value_traits())
      :  Base(cmp, pcmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE treap_set( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const priority_compare &pcmp = priority_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, pcmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE treap_set(BOOST_RV_REF(treap_set) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE treap_set& operator=(BOOST_RV_REF(treap_set) x)
   {  return static_cast<treap_set &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const treap_set &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(treap_set) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static treap_set &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<treap_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_set &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const treap_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static treap_set &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<treap_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_set &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const treap_set &>(Base::container_from_iterator(it));   }
};

#endif

//! The class template treap_multiset is an intrusive container, that mimics most of
//! the interface of std::treap_multiset as described in the C++ standard.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<>, \c size_type<>,
//! \c compare<>, \c priority<> and \c priority_of_value<>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class VoidOrPrioOfValue, class VoidOrPrioComp, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class treap_multiset_impl
#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public treap_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder>
#endif
{
   /// @cond
   typedef treap_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> tree_type;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(treap_multiset_impl)

   typedef tree_type implementation_defined;
   /// @endcond

   public:
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::value_traits             value_traits;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
   typedef typename implementation_defined::reference                reference;
   typedef typename implementation_defined::const_reference          const_reference;
   typedef typename implementation_defined::difference_type          difference_type;
   typedef typename implementation_defined::size_type                size_type;
   typedef typename implementation_defined::value_compare            value_compare;
   typedef typename implementation_defined::key_compare              key_compare;
   typedef typename implementation_defined::priority_type            priority_type;
   typedef typename implementation_defined::priority_compare         priority_compare;
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

   static const bool constant_time_size = implementation_defined::constant_time_size;

   public:

   //! @copydoc ::boost::intrusive::treap::treap()
   treap_multiset_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::treap::treap(const key_compare &,const priority_compare &,const value_traits &)
   explicit treap_multiset_impl( const key_compare &cmp
                          , const priority_compare &pcmp  = priority_compare()
                          , const value_traits &v_traits  = value_traits())
      :  tree_type(cmp, pcmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::treap::treap(bool,Iterator,Iterator,const key_compare &,const priority_compare &,const value_traits &)
   template<class Iterator>
   treap_multiset_impl( Iterator b, Iterator e
           , const key_compare &cmp = key_compare()
           , const priority_compare &pcmp  = priority_compare()
           , const value_traits &v_traits = value_traits())
      : tree_type(false, b, e, cmp, pcmp, v_traits)
   {}

   //! <b>Effects</b>: to-do
   //!
   treap_multiset_impl(BOOST_RV_REF(treap_multiset_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! <b>Effects</b>: to-do
   //!
   treap_multiset_impl& operator=(BOOST_RV_REF(treap_multiset_impl) x)
   {  return static_cast<treap_multiset_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x)));  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::treap::~treap()
   ~treap_multiset_impl();

   //! @copydoc ::boost::intrusive::treap::begin()
   iterator begin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::begin()const
   const_iterator begin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::cbegin()const
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::end()
   iterator end() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::end()const
   const_iterator end() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::cend()const
   const_iterator cend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rbegin()const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crbegin()const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rend()
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rend()const
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crend()const
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::root()
   iterator root() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::root()const
   const_iterator root() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::croot()const
   const_iterator croot() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(iterator)
   static treap_multiset_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(const_iterator)
   static const treap_multiset_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(iterator)
   static treap_multiset_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(const_iterator)
   static const treap_multiset_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::treap::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::treap::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::size()const
   size_type size() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::swap
   void swap(treap_multiset_impl& other);

   //! @copydoc ::boost::intrusive::treap::clone_from(const treap&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const treap_multiset_impl &src, Cloner cloner, Disposer disposer);

   #else

   using tree_type::clone_from;

   #endif

   //! @copydoc ::boost::intrusive::treap::clone_from(treap&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(treap_multiset_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! @copydoc ::boost::intrusive::treap::top()
   BOOST_INTRUSIVE_FORCEINLINE iterator top() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::top()const
   BOOST_INTRUSIVE_FORCEINLINE const_iterator top() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::ctop()const
   BOOST_INTRUSIVE_FORCEINLINE const_iterator ctop() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rtop()
   BOOST_INTRUSIVE_FORCEINLINE reverse_iterator rtop() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::rtop()const
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator rtop() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crtop()const
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator crtop() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::crtop() const
   priority_compare priority_comp() const;
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::treap::insert_equal(reference)
   iterator insert(reference value)
   {  return tree_type::insert_equal(value);  }

   //! @copydoc ::boost::intrusive::treap::insert_equal(const_iterator,reference)
   iterator insert(const_iterator hint, reference value)
   {  return tree_type::insert_equal(hint, value);  }

   //! @copydoc ::boost::intrusive::treap::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_type::insert_equal(b, e);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::treap::insert_before
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::push_back
   void push_back(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::push_front
   void push_front(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator)
   iterator erase(const_iterator i) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::clear
   void clear() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::count(const key_type &)const
   size_type count(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::count(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::lower_bound(const key_type &)
   iterator lower_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::lower_bound(const key_type &)const
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::lower_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::upper_bound(const key_type &)
   iterator upper_bound(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::upper_bound(const key_type &)const
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::upper_bound(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::find(const key_type &)
   iterator find(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::find(const key_type &)const
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::find(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::equal_range(const key_type &)
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::equal_range(const key_type &)const
   std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::treap::equal_range(const KeyType&,KeyTypeKeyCompare)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyTypeKeyCompare comp) const;

   //! @copydoc ::boost::intrusive::treap::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::treap::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::treap::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::treap::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)const
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator> bounded_range
         (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::treap::s_iterator_to(reference)
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::iterator_to(reference)
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::init_node(reference)
   static void init_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::replace_node
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::remove_node
   void remove_node(reference value) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::treap::merge_unique
   template<class ...Options2>
   void merge(treap_multiset<T, Options2...> &source);

   //! @copydoc ::boost::intrusive::treap::merge_unique
   template<class ...Options2>
   void merge(treap_set<T, Options2...> &source);

   #else

   template<class Compare2>
   void merge(treap_multiset_impl<ValueTraits, VoidOrKeyOfValue, Compare2, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   template<class Compare2>
   void merge(treap_set_impl<ValueTraits, VoidOrKeyOfValue, Compare2, VoidOrPrioOfValue, VoidOrPrioComp, SizeType, ConstantTimeSize, HeaderHolder> &source)
   {  return tree_type::merge_equal(source);  }

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};


//! Helper metafunction to define a \c treap_multiset that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void
                , class O7 = void>
#endif
struct make_treap_multiset
{
   typedef typename pack_options
      < treap_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;

   typedef treap_multiset_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::priority_of_value
         , typename packed_options::priority
         , typename packed_options::size_type
         , packed_options::constant_time_size
         , typename packed_options::header_holder_type
         > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4, class O5, class O6, class O7>
#else
template<class T, class ...Options>
#endif
class treap_multiset
   :  public make_treap_multiset<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_treap_multiset
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6, O7
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(treap_multiset)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::priority_compare   priority_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE treap_multiset()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit treap_multiset( const key_compare &cmp
                          , const priority_compare &pcmp = priority_compare()
                          , const value_traits &v_traits = value_traits())
      :  Base(cmp, pcmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE treap_multiset( Iterator b, Iterator e
      , const key_compare &cmp = key_compare()
      , const priority_compare &pcmp = priority_compare()
      , const value_traits &v_traits = value_traits())
      :  Base(b, e, cmp, pcmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE treap_multiset(BOOST_RV_REF(treap_multiset) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE treap_multiset& operator=(BOOST_RV_REF(treap_multiset) x)
   {  return static_cast<treap_multiset &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const treap_multiset &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(treap_multiset) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static treap_multiset &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<treap_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_multiset &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const treap_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static treap_multiset &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<treap_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_multiset &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const treap_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TREAP_SET_HPP

/* treap_set.hpp
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
*/