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
   static rbtree_impl &container_from_end_iterator(iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_end_iterator(const_iterator)
   static const rbtree_impl &container_from_end_iterator(const_iterator end_iterator);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(iterator)
   static rbtree_impl &container_from_iterator(iterator it);

   //! @copydoc ::boost::intrusive::bstree::container_from_iterator(const_iterator)
   static const rbtree_impl &container_from_iterator(const_iterator it);

   //! @copydoc ::boost::intrusive::bstree::key_comp()const
   key_compare key_comp() const;

   //! @copydoc ::boost::intrusive::bstree::value_comp()const
   value_compare value_comp() const;

   //! @copydoc ::boost::intrusive::bstree::empty()const
   bool empty() const;

   //! @copydoc ::boost::intrusive::bstree::size()const
   size_type size() const;

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

   //! @copydoc ::boost::intrusive::bstree::erase(const key_type &key)
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

   BOOST_INTRUSIVE_FORCEINLINE static rbtree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<rbtree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const rbtree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const rbtree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static rbtree &container_from_iterator(iterator it)
   {  return static_cast<rbtree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const rbtree &container_from_iterator(const_iterator it)
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