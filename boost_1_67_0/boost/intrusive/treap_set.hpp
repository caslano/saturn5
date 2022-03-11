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
   iterator begin();

   //! @copydoc ::boost::intrusive::treap::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::treap::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::treap::end()
   iterator end();

   //! @copydoc ::boost::intrusive::treap::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::treap::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::treap::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::treap::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::treap::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::treap::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::treap::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::treap::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::treap::root()
   iterator root();

   //! @copydoc ::boost::intrusive::treap::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::treap::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(iterator)
   static treap_set_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(const_iterator)
   static const treap_set_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(iterator)
   static treap_set_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(const_iterator)
   static const treap_set_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::treap::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::treap::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::treap::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::treap::size()const
   size_type size() const;

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
   iterator top();

   //! @copydoc ::boost::intrusive::treap::top()const
   const_iterator top() const;

   //! @copydoc ::boost::intrusive::treap::ctop()const
   const_iterator ctop() const;

   //! @copydoc ::boost::intrusive::treap::rtop()
   reverse_iterator rtop();

   //! @copydoc ::boost::intrusive::treap::rtop()const
   const_reverse_iterator rtop() const;

   //! @copydoc ::boost::intrusive::treap::crtop()const
   const_reverse_iterator crtop() const;

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
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return tree_type::insert_unique_commit(value, commit_data);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::treap::insert_before
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::treap::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::treap::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::treap::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::clear
   void clear();

   //! @copydoc ::boost::intrusive::treap::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

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
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::treap::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::treap::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::treap::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::treap::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::treap::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::treap::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::treap::remove_node
   void remove_node(reference value);


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

   BOOST_INTRUSIVE_FORCEINLINE static treap_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<treap_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const treap_set &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static treap_set &container_from_iterator(iterator it)
   {  return static_cast<treap_set &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_set &container_from_iterator(const_iterator it)
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
   iterator begin();

   //! @copydoc ::boost::intrusive::treap::begin()const
   const_iterator begin() const;

   //! @copydoc ::boost::intrusive::treap::cbegin()const
   const_iterator cbegin() const;

   //! @copydoc ::boost::intrusive::treap::end()
   iterator end();

   //! @copydoc ::boost::intrusive::treap::end()const
   const_iterator end() const;

   //! @copydoc ::boost::intrusive::treap::cend()const
   const_iterator cend() const;

   //! @copydoc ::boost::intrusive::treap::rbegin()
   reverse_iterator rbegin();

   //! @copydoc ::boost::intrusive::treap::rbegin()const
   const_reverse_iterator rbegin() const;

   //! @copydoc ::boost::intrusive::treap::crbegin()const
   const_reverse_iterator crbegin() const;

   //! @copydoc ::boost::intrusive::treap::rend()
   reverse_iterator rend();

   //! @copydoc ::boost::intrusive::treap::rend()const
   const_reverse_iterator rend() const;

   //! @copydoc ::boost::intrusive::treap::crend()const
   const_reverse_iterator crend() const;

   //! @copydoc ::boost::intrusive::treap::root()
   iterator root();

   //! @copydoc ::boost::intrusive::treap::root()const
   const_iterator root() const;

   //! @copydoc ::boost::intrusive::treap::croot()const
   const_iterator croot() const;

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(iterator)
   static treap_multiset_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::treap::container_from_end_iterator(const_iterator)
   static const treap_multiset_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(iterator)
   static treap_multiset_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::treap::container_from_iterator(const_iterator)
   static const treap_multiset_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::treap::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::treap::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::treap::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::treap::size()const
   size_type size() const;

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
   iterator top();

   //! @copydoc ::boost::intrusive::treap::top()const
   const_iterator top() const;

   //! @copydoc ::boost::intrusive::treap::ctop()const
   const_iterator ctop() const;

   //! @copydoc ::boost::intrusive::treap::rtop()
   reverse_iterator rtop();

   //! @copydoc ::boost::intrusive::treap::rtop()const
   const_reverse_iterator rtop() const;

   //! @copydoc ::boost::intrusive::treap::crtop()const
   const_reverse_iterator crtop() const;

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
   iterator insert_before(const_iterator pos, reference value);

   //! @copydoc ::boost::intrusive::treap::push_back
   void push_back(reference value);

   //! @copydoc ::boost::intrusive::treap::push_front
   void push_front(reference value);

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator)
   iterator erase(const_iterator i);

   //! @copydoc ::boost::intrusive::treap::erase(const_iterator,const_iterator)
   iterator erase(const_iterator b, const_iterator e);

   //! @copydoc ::boost::intrusive::treap::erase(const key_type &)
   size_type erase(const key_type &key);

   //! @copydoc ::boost::intrusive::treap::erase(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   size_type erase(const KeyType& key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const_iterator,const_iterator,Disposer)
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const key_type &, Disposer)
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::erase_and_dispose(const KeyType&,KeyTypeKeyCompare,Disposer)
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer);

   //! @copydoc ::boost::intrusive::treap::clear
   void clear();

   //! @copydoc ::boost::intrusive::treap::clear_and_dispose
   template<class Disposer>
   void clear_and_dispose(Disposer disposer);

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
   static iterator s_iterator_to(reference value);

   //! @copydoc ::boost::intrusive::treap::s_iterator_to(const_reference)
   static const_iterator s_iterator_to(const_reference value);

   //! @copydoc ::boost::intrusive::treap::iterator_to(reference)
   iterator iterator_to(reference value);

   //! @copydoc ::boost::intrusive::treap::iterator_to(const_reference)const
   const_iterator iterator_to(const_reference value) const;

   //! @copydoc ::boost::intrusive::treap::init_node(reference)
   static void init_node(reference value);

   //! @copydoc ::boost::intrusive::treap::unlink_leftmost_without_rebalance
   pointer unlink_leftmost_without_rebalance();

   //! @copydoc ::boost::intrusive::treap::replace_node
   void replace_node(iterator replace_this, reference with_this);

   //! @copydoc ::boost::intrusive::treap::remove_node
   void remove_node(reference value);

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

   BOOST_INTRUSIVE_FORCEINLINE static treap_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<treap_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const treap_multiset &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static treap_multiset &container_from_iterator(iterator it)
   {  return static_cast<treap_multiset &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const treap_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const treap_multiset &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TREAP_SET_HPP

/* treap_set.hpp
+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
*/