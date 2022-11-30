/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_RBTREE_HPP
#define BOOST_INTRUSIVE_RBTREE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <cstddef>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //std::pair

#include <boost/intrusive/set_hook.hpp>
#include <boost/intrusive/detail/rbtree_node.hpp>
#include <boost/intrusive/bstree.hpp>
#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/intrusive/link_mode.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

struct default_rbtree_hook_applier
{  template <class T> struct apply{ typedef typename T::default_rbtree_hook type;  };  };

template<>
struct is_default_hook_tag<default_rbtree_hook_applier>
{  static const bool value = true;  };

struct rbtree_defaults
   : bstree_defaults
{
   typedef default_rbtree_hook_applier proto_value_traits;
};

/// @endcond

//! The class template rbtree is an intrusive red-black tree container, that
//! is used to construct intrusive set and multiset containers. The no-throw
//! guarantee holds only, if the key_compare object
//! doesn't throw.
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
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class rbtree_impl
   /// @cond
   :  public bstree_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType, ConstantTimeSize, RbTreeAlgorithms, HeaderHolder>
   /// @endcond
{
   public:
   typedef ValueTraits                                               value_traits;
   /// @cond
   typedef bstree_impl< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType
                      , ConstantTimeSize, RbTreeAlgorithms
                      , HeaderHolder>                                tree_type;
   typedef tree_type                                                 implementation_defined;
   /// @endcond

   typedef typename implementation_defined::pointer                  pointer;
   typedef typename implementation_defined::const_pointer            const_pointer;
   typedef typename implementation_defined::value_type               value_type;
   typedef typename implementation_defined::key_type                 key_type;
   typedef typename implementation_defined::key_of_value             key_of_value;
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
   typedef typename implementation_defined::node_traits              node_traits;
   typedef typename implementation_defined::node                     node;
   typedef typename implementation_defined::node_ptr                 node_ptr;
   typedef typename implementation_defined::const_node_ptr           const_node_ptr;
   typedef typename implementation_defined::node_algorithms          node_algorithms;

   static const bool constant_time_size = implementation_defined::constant_time_size;
   /// @cond
   private:

   //noncopyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(rbtree_impl)

   /// @endcond

   public:

   typedef typename implementation_defined::insert_commit_data insert_commit_data;

   //! @copydoc ::boost::intrusive::bstree::bstree()
   rbtree_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(const key_compare &,const value_traits &)
   explicit rbtree_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   rbtree_impl( bool unique, Iterator b, Iterator e
              , const key_compare &cmp     = key_compare()
              , const value_traits &v_traits = value_traits())
      : tree_type(unique, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   rbtree_impl(BOOST_RV_REF(rbtree_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   rbtree_impl& operator=(BOOST_RV_REF(rbtree_impl) x)
   {  return static_cast<rbtree_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~rbtree_impl();

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
   static rbtree_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const rbtree_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static rbtree_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const rbtree_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::swap
   void swap(rbtree_impl& other);

   //! @copydoc ::boost::intrusive::bstree::clone_from(const bstree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const rbtree_impl &src, Cloner cloner, Disposer disposer);

   #else //BOOST_INTRUSIVE_DOXYGEN_INVOKED

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(rbtree_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(rbtree_impl &&src, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree::insert_equal(reference)
   iterator insert_equal(reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_equal(const_iterator,reference)
   iterator insert_equal(const_iterator hint, reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_equal(Iterator,Iterator)
   template<class Iterator>
   void insert_equal(Iterator b, Iterator e);

   //! @copydoc ::boost::intrusive::bstree::insert_unique(reference)
   std::pair<iterator, bool> insert_unique(reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_unique(const_iterator,reference)
   iterator insert_unique(const_iterator hint, reference value);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const KeyType&,KeyTypeKeyCompare,insert_commit_data&)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_unique_check
      (const key_type &key, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_check(const_iterator,const key_type&,insert_commit_data&)
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const key_type &key, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique_commit
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e);

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

   //! @copydoc ::boost::intrusive::bstree::erase(const key_type &key)
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
      (const key_type &lower, const key_type &upper_key, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType& lower_key, const KeyType& upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)const
   std::pair<const_iterator, const_iterator>
      bounded_range(const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

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

   //! @copydoc ::boost::intrusive::bstree::merge_unique(bstree<T, Options2...>&)
   template<class T, class ...Options2>
   void merge_unique(rbtree<T, Options2...> &);

   //! @copydoc ::boost::intrusive::bstree::merge_equal(bstree<T, Options2...>&)
   template<class T, class ...Options2>
   void merge_equal(rbtree<T, Options2...> &);

   friend bool operator< (const rbtree_impl &x, const rbtree_impl &y);

   friend bool operator==(const rbtree_impl &x, const rbtree_impl &y);

   friend bool operator!= (const rbtree_impl &x, const rbtree_impl &y);

   friend bool operator>(const rbtree_impl &x, const rbtree_impl &y);

   friend bool operator<=(const rbtree_impl &x, const rbtree_impl &y);

   friend bool operator>=(const rbtree_impl &x, const rbtree_impl &y);

   friend void swap(rbtree_impl &x, rbtree_impl &y);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};


//! Helper metafunction to define a \c rbtree that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_rbtree
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

   typedef rbtree_impl
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
class rbtree
   :  public make_rbtree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_rbtree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(rbtree)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::reverse_iterator           reverse_iterator;
   typedef typename Base::const_reverse_iterator     const_reverse_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE rbtree()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit rbtree( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE rbtree( bool unique, Iterator b, Iterator e
         , const key_compare &cmp = key_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(unique, b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE rbtree(BOOST_RV_REF(rbtree) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE rbtree& operator=(BOOST_RV_REF(rbtree) x)
   {  return static_cast<rbtree &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const rbtree &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(rbtree) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static rbtree &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<rbtree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const rbtree &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const rbtree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static rbtree &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<rbtree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const rbtree &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const rbtree &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_HPP

/* rbtree.hpp
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
*/