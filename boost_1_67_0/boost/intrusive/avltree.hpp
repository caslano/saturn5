/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_AVLTREE_HPP
#define BOOST_INTRUSIVE_AVLTREE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <cstddef>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>

#include <boost/static_assert.hpp>
#include <boost/intrusive/avl_set_hook.hpp>
#include <boost/intrusive/detail/avltree_node.hpp>
#include <boost/intrusive/bstree.hpp>
#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/avltree_algorithms.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/move/utility_core.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

struct default_avltree_hook_applier
{  template <class T> struct apply{ typedef typename T::default_avltree_hook type;  };  };

template<>
struct is_default_hook_tag<default_avltree_hook_applier>
{  static const bool value = true;  };

struct avltree_defaults
   : bstree_defaults
{
   typedef default_avltree_hook_applier proto_value_traits;
};

/// @endcond

//! The class template avltree is an intrusive AVL tree container, that
//! is used to construct intrusive avl_set and avl_multiset containers.
//! The no-throw guarantee holds only, if the key_compare object
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
class avltree_impl
   /// @cond
   :  public bstree_impl<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType, ConstantTimeSize, AvlTreeAlgorithms, HeaderHolder>
   /// @endcond
{
   public:
   typedef ValueTraits value_traits;
   /// @cond
   typedef bstree_impl< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, SizeType
                      , ConstantTimeSize, AvlTreeAlgorithms
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
   BOOST_MOVABLE_BUT_NOT_COPYABLE(avltree_impl)

   /// @endcond

   public:

   typedef typename implementation_defined::insert_commit_data insert_commit_data;

   //! @copydoc ::boost::intrusive::bstree::bstree()
   avltree_impl()
      :  tree_type()
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(const key_compare &,const value_traits &)
   explicit avltree_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  tree_type(cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bool,Iterator,Iterator,const key_compare &,const value_traits &)
   template<class Iterator>
   avltree_impl( bool unique, Iterator b, Iterator e
              , const key_compare &cmp     = key_compare()
              , const value_traits &v_traits = value_traits())
      : tree_type(unique, b, e, cmp, v_traits)
   {}

   //! @copydoc ::boost::intrusive::bstree::bstree(bstree &&)
   avltree_impl(BOOST_RV_REF(avltree_impl) x)
      :  tree_type(BOOST_MOVE_BASE(tree_type, x))
   {}

   //! @copydoc ::boost::intrusive::bstree::operator=(bstree &&)
   avltree_impl& operator=(BOOST_RV_REF(avltree_impl) x)
   {  return static_cast<avltree_impl&>(tree_type::operator=(BOOST_MOVE_BASE(tree_type, x))); }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::~bstree()
   ~avltree_impl();

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
   static avltree_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const avltree_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static avltree_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const avltree_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;

   //! @copydoc ::boost::intrusive::bstree::swap
   void swap(avltree_impl& other);

   //! @copydoc ::boost::intrusive::bstree::clone_from(const bstree&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(const avltree_impl &src, Cloner cloner, Disposer disposer);

   #else //BOOST_INTRUSIVE_DOXYGEN_INVOKED

   using tree_type::clone_from;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree::clone_from(bstree&&,Cloner,Disposer)
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(avltree_impl) src, Cloner cloner, Disposer disposer)
   {  tree_type::clone_from(BOOST_MOVE_BASE(tree_type, src), cloner, disposer);  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

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
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree::insert_unique(Iterator,Iterator)
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e);

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

   //! @copydoc ::boost::intrusive::bstree::count(const key_type &ke)const
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

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &key)
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

   //! @copydoc ::boost::intrusive::bstree::merge_unique(bstree<T, Options2...>&)
   template<class T, class ...Options2>
   void merge_unique(avltree<T, Options2...> &);

   //! @copydoc ::boost::intrusive::bstree::merge_equal(bstree<T, Options2...>&)
   template<class T, class ...Options2>
   void merge_equal(avltree<T, Options2...> &);

   friend bool operator< (const avltree_impl &x, const avltree_impl &y);

   friend bool operator==(const avltree_impl &x, const avltree_impl &y);

   friend bool operator!= (const avltree_impl &x, const avltree_impl &y);

   friend bool operator>(const avltree_impl &x, const avltree_impl &y);

   friend bool operator<=(const avltree_impl &x, const avltree_impl &y);

   friend bool operator>=(const avltree_impl &x, const avltree_impl &y);

   friend void swap(avltree_impl &x, avltree_impl &y);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
};


//! Helper metafunction to define a \c avltree that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_avltree
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

   typedef avltree_impl
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
class avltree
   :  public make_avltree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_avltree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(avltree)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;
   typedef typename Base::reverse_iterator           reverse_iterator;
   typedef typename Base::const_reverse_iterator     const_reverse_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE avltree()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit avltree( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE avltree( bool unique, Iterator b, Iterator e
         , const key_compare &cmp = key_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(unique, b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE avltree(BOOST_RV_REF(avltree) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE avltree& operator=(BOOST_RV_REF(avltree) x)
   {  return static_cast<avltree &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const avltree &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(avltree) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static avltree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<avltree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avltree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const avltree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static avltree &container_from_iterator(iterator it)
   {  return static_cast<avltree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avltree &container_from_iterator(const_iterator it)
   {  return static_cast<const avltree &>(Base::container_from_iterator(it));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_AVLTREE_HPP

/* avltree.hpp
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
*/