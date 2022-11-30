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
   static avltree_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const avltree_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static avltree_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const avltree_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const BOOST_NOEXCEPT;

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

   BOOST_INTRUSIVE_FORCEINLINE static avltree &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<avltree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avltree &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const avltree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static avltree &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<avltree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const avltree &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
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