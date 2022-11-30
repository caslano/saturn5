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
#ifndef BOOST_INTRUSIVE_BSTREE_HPP
#define BOOST_INTRUSIVE_BSTREE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/bs_set_hook.hpp>
#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/detail/tree_iterator.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>
#include <boost/intrusive/detail/empty_node_checker.hpp>
#include <boost/intrusive/detail/default_header_holder.hpp>
#include <boost/intrusive/detail/reverse_iterator.hpp>
#include <boost/intrusive/detail/exception_disposer.hpp>
#include <boost/intrusive/detail/node_cloner_disposer.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>
#include <boost/intrusive/detail/simple_disposers.hpp>
#include <boost/intrusive/detail/size_holder.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/detail/algorithm.hpp>
#include <boost/intrusive/detail/tree_value_compare.hpp>

#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/parent_from_member.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>

#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <cstddef>   //size_t...
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//less, equal_to

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

struct default_bstree_hook_applier
{  template <class T> struct apply{ typedef typename T::default_bstree_hook type;  };  };

template<>
struct is_default_hook_tag<default_bstree_hook_applier>
{  static const bool value = true;  };

struct bstree_defaults
{
   typedef default_bstree_hook_applier proto_value_traits;
   static const bool constant_time_size = true;
   typedef std::size_t size_type;
   typedef void compare;
   typedef void key_of_value;
   static const bool floating_point = true;  //For sgtree
   typedef void priority;  //For treap
   typedef void header_holder_type;
};

template<class ValueTraits, algo_types AlgoType, typename HeaderHolder>
struct bstbase3
{
   typedef ValueTraits                                               value_traits;
   typedef typename value_traits::node_traits                        node_traits;
   typedef typename node_traits::node                                node_type;
   typedef typename get_algo<AlgoType, node_traits>::type            node_algorithms;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef tree_iterator<value_traits, false>                                                   iterator;
   typedef tree_iterator<value_traits, true>                                                    const_iterator;
   typedef boost::intrusive::reverse_iterator<iterator>                                         reverse_iterator;
   typedef boost::intrusive::reverse_iterator<const_iterator>                                   const_reverse_iterator;
   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::pointer)                               pointer;
   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::const_pointer)                         const_pointer;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<pointer>::element_type)               value_type;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<pointer>::reference)                  reference;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<const_pointer>::reference)            const_reference;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<const_pointer>::difference_type)      difference_type;
   typedef typename detail::get_header_holder_type
      < value_traits,HeaderHolder >::type                                                       header_holder_type;

   static const bool safemode_or_autounlink = is_safe_autounlink<value_traits::link_mode>::value;
   static const bool stateful_value_traits = detail::is_stateful_value_traits<value_traits>::value;
   static const bool has_container_from_iterator =
        detail::is_same< header_holder_type, detail::default_header_holder< node_traits > >::value;

   struct holder_t : public ValueTraits
   {
      BOOST_INTRUSIVE_FORCEINLINE explicit holder_t(const ValueTraits &vtraits)
         : ValueTraits(vtraits)
      {}
      header_holder_type root;
   } holder;

   static bstbase3 &get_tree_base_from_end_iterator(const const_iterator &end_iterator)
   {
      BOOST_STATIC_ASSERT(has_container_from_iterator);
      node_ptr p = end_iterator.pointed_node();
      header_holder_type* h = header_holder_type::get_holder(p);
      holder_t *holder = get_parent_from_member<holder_t, header_holder_type>(h, &holder_t::root);
      bstbase3 *base   = get_parent_from_member<bstbase3, holder_t> (holder, &bstbase3::holder);
      return *base;
   }

   BOOST_INTRUSIVE_FORCEINLINE bstbase3(const ValueTraits &vtraits)
      : holder(vtraits)
   {
      node_algorithms::init_header(this->header_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE node_ptr header_ptr()
   { return holder.root.get_node(); }

   BOOST_INTRUSIVE_FORCEINLINE const_node_ptr header_ptr() const
   { return holder.root.get_node(); }

   BOOST_INTRUSIVE_FORCEINLINE const value_traits &get_value_traits() const
   {  return this->holder;  }

   BOOST_INTRUSIVE_FORCEINLINE value_traits &get_value_traits()
   {  return this->holder;  }

   typedef typename boost::intrusive::value_traits_pointers
      <ValueTraits>::const_value_traits_ptr const_value_traits_ptr;

   BOOST_INTRUSIVE_FORCEINLINE const_value_traits_ptr priv_value_traits_ptr() const
   {  return pointer_traits<const_value_traits_ptr>::pointer_to(this->get_value_traits());  }

   BOOST_INTRUSIVE_FORCEINLINE iterator begin() BOOST_NOEXCEPT
   {  return iterator(node_algorithms::begin_node(this->header_ptr()), this->priv_value_traits_ptr());   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator begin() const BOOST_NOEXCEPT
   {  return cbegin();   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator cbegin() const BOOST_NOEXCEPT
   {  return const_iterator(node_algorithms::begin_node(this->header_ptr()), this->priv_value_traits_ptr());   }

   BOOST_INTRUSIVE_FORCEINLINE iterator end() BOOST_NOEXCEPT
   {  return iterator(node_algorithms::end_node(this->header_ptr()), this->priv_value_traits_ptr());   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator end() const BOOST_NOEXCEPT
   {  return cend();  }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator cend() const BOOST_NOEXCEPT
   {  return const_iterator(node_algorithms::end_node(this->header_ptr()), this->priv_value_traits_ptr());   }

   BOOST_INTRUSIVE_FORCEINLINE iterator root()
   {  return iterator(node_algorithms::root_node(this->header_ptr()), this->priv_value_traits_ptr());   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator root() const
   {  return croot();   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator croot() const
   {  return const_iterator(node_algorithms::root_node(this->header_ptr()), this->priv_value_traits_ptr());   }

   BOOST_INTRUSIVE_FORCEINLINE reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator rbegin() const
   {  return const_reverse_iterator(end());  }

   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(end());  }

   BOOST_INTRUSIVE_FORCEINLINE reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator rend() const
   {  return const_reverse_iterator(begin());   }

   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator crend() const
   {  return const_reverse_iterator(begin());   }

   void replace_node(iterator replace_this, reference with_this)
   {
      node_algorithms::replace_node( get_value_traits().to_node_ptr(*replace_this)
                                   , this->header_ptr()
                                   , get_value_traits().to_node_ptr(with_this));
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
         node_algorithms::init(replace_this.pointed_node());
   }

   BOOST_INTRUSIVE_FORCEINLINE void rebalance() BOOST_NOEXCEPT
   {  node_algorithms::rebalance(this->header_ptr()); }

   iterator rebalance_subtree(iterator r) BOOST_NOEXCEPT
   {  return iterator(node_algorithms::rebalance_subtree(r.pointed_node()), this->priv_value_traits_ptr()); }

   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!stateful_value_traits));
      return iterator (value_traits::to_node_ptr(value), const_value_traits_ptr());
   }

   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!stateful_value_traits));
      return const_iterator (value_traits::to_node_ptr(*pointer_traits<pointer>::const_cast_from(pointer_traits<const_pointer>::pointer_to(value))), const_value_traits_ptr());
   }

   iterator iterator_to(reference value) BOOST_NOEXCEPT
   {  return iterator (this->get_value_traits().to_node_ptr(value), this->priv_value_traits_ptr()); }

   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT
   {  return const_iterator (this->get_value_traits().to_node_ptr(*pointer_traits<pointer>::const_cast_from(pointer_traits<const_pointer>::pointer_to(value))), this->priv_value_traits_ptr()); }

   BOOST_INTRUSIVE_FORCEINLINE static void init_node(reference value)
   { node_algorithms::init(value_traits::to_node_ptr(value)); }

};

template<class Less, class T>
struct get_compare
{
   typedef Less type;
};

template<class T>
struct get_compare<void, T>
{
   typedef ::std::less<T> type;
};

template<class KeyOfValue, class T>
struct get_key_of_value
{
   typedef KeyOfValue type;
};

template<class T>
struct get_key_of_value<void, T>
{
   typedef ::boost::intrusive::detail::identity<T> type;
};

template<class ValuePtr, class VoidOrKeyOfValue, class VoidOrKeyComp>
struct bst_key_types
{
   typedef typename
      boost::movelib::pointer_element<ValuePtr>::type value_type;
   typedef typename get_key_of_value
      < VoidOrKeyOfValue, value_type>::type           key_of_value;
   typedef typename key_of_value::type                key_type;
   typedef typename get_compare< VoidOrKeyComp
                      , key_type
                      >::type                         key_compare;
   typedef tree_value_compare
      <ValuePtr, key_compare, key_of_value>           value_compare;
};

template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, algo_types AlgoType, typename HeaderHolder>
struct bstbase2
   //Put the (possibly empty) functor in the first position to get EBO in MSVC
   //Use public inheritance to avoid MSVC bugs with closures
   : public detail::ebo_functor_holder
            < typename bst_key_types
               < typename ValueTraits::pointer
               , VoidOrKeyOfValue
               , VoidOrKeyComp
               
               >::value_compare
            >
   , public bstbase3<ValueTraits, AlgoType, HeaderHolder>
{
   typedef bstbase3<ValueTraits, AlgoType, HeaderHolder>             treeheader_t;
   typedef bst_key_types< typename ValueTraits::pointer
                        , VoidOrKeyOfValue
                        , VoidOrKeyComp>                             key_types;
   typedef typename treeheader_t::value_traits                       value_traits;
   typedef typename treeheader_t::node_algorithms                    node_algorithms;
   typedef typename ValueTraits::value_type                          value_type;
   typedef typename key_types::key_type                              key_type;
   typedef typename key_types::key_of_value                          key_of_value;
   typedef typename key_types::key_compare                           key_compare;
   typedef typename key_types::value_compare                         value_compare;
   typedef typename treeheader_t::iterator                           iterator;
   typedef typename treeheader_t::const_iterator                     const_iterator;
   typedef typename treeheader_t::node_ptr                           node_ptr;
   typedef typename treeheader_t::const_node_ptr                     const_node_ptr;

   bstbase2(const key_compare &comp, const ValueTraits &vtraits)
      : detail::ebo_functor_holder<value_compare>(value_compare(comp)), treeheader_t(vtraits)
   {}

   const value_compare &get_comp() const
   {  return this->get();  }

   value_compare &get_comp()
   {  return this->get();  }

   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::pointer)                               pointer;
   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::const_pointer)                         const_pointer;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<pointer>::reference)                  reference;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<const_pointer>::reference)            const_reference;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<const_pointer>::difference_type)      difference_type;
   typedef typename node_algorithms::insert_commit_data insert_commit_data;

   BOOST_INTRUSIVE_FORCEINLINE value_compare value_comp() const
   {  return this->get_comp();   }

   BOOST_INTRUSIVE_FORCEINLINE key_compare key_comp() const
   {  return this->get_comp().key_comp();   }

   //lower_bound
   BOOST_INTRUSIVE_FORCEINLINE iterator lower_bound(const key_type &key)
   {  return this->lower_bound(key, this->key_comp());   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator lower_bound(const key_type &key) const
   {  return this->lower_bound(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType &key, KeyTypeKeyCompare comp)
   {
      return iterator(node_algorithms::lower_bound
         (this->header_ptr(), key, this->key_node_comp(comp)), this->priv_value_traits_ptr());
   }

   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType &key, KeyTypeKeyCompare comp) const
   {
      return const_iterator(node_algorithms::lower_bound
         (this->header_ptr(), key, this->key_node_comp(comp)), this->priv_value_traits_ptr());
   }

   //upper_bound
   BOOST_INTRUSIVE_FORCEINLINE iterator upper_bound(const key_type &key)
   {  return this->upper_bound(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType &key, KeyTypeKeyCompare comp)
   {
      return iterator(node_algorithms::upper_bound
         (this->header_ptr(), key, this->key_node_comp(comp)), this->priv_value_traits_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator upper_bound(const key_type &key) const
   {  return this->upper_bound(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType &key, KeyTypeKeyCompare comp) const
   {
      return const_iterator(node_algorithms::upper_bound
         (this->header_ptr(), key, this->key_node_comp(comp)), this->priv_value_traits_ptr());
   }

   template<class KeyTypeKeyCompare>
   struct key_node_comp_ret
   {  typedef detail::key_nodeptr_comp<KeyTypeKeyCompare, value_traits, key_of_value> type;  };

   template<class KeyTypeKeyCompare>
   BOOST_INTRUSIVE_FORCEINLINE typename key_node_comp_ret<KeyTypeKeyCompare>::type key_node_comp(KeyTypeKeyCompare comp) const
   {
      return detail::key_nodeptr_comp<KeyTypeKeyCompare, value_traits, key_of_value>(comp, &this->get_value_traits());
   }

   //find
   BOOST_INTRUSIVE_FORCEINLINE iterator find(const key_type &key)
   {  return this->find(key, this->key_comp()); }

   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType &key, KeyTypeKeyCompare comp)
   {
      return iterator
         (node_algorithms::find(this->header_ptr(), key, this->key_node_comp(comp)), this->priv_value_traits_ptr());
   }

   BOOST_INTRUSIVE_FORCEINLINE const_iterator find(const key_type &key) const
   {  return this->find(key, this->key_comp()); }

   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType &key, KeyTypeKeyCompare comp) const
   {
      return const_iterator
         (node_algorithms::find(this->header_ptr(), key, this->key_node_comp(comp)), this->priv_value_traits_ptr());
   }

   //equal_range
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator,iterator> equal_range(const key_type &key)
   {  return this->equal_range(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType &key, KeyTypeKeyCompare comp)
   {
      std::pair<node_ptr, node_ptr> ret = 
         node_algorithms::equal_range(this->header_ptr(), key, this->key_node_comp(comp));
      return std::pair<iterator, iterator>( iterator(ret.first, this->priv_value_traits_ptr())
                                          , iterator(ret.second, this->priv_value_traits_ptr()));
   }

   BOOST_INTRUSIVE_FORCEINLINE std::pair<const_iterator, const_iterator>
      equal_range(const key_type &key) const
   {  return this->equal_range(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType &key, KeyTypeKeyCompare comp) const
   {
      std::pair<node_ptr, node_ptr> ret =
         node_algorithms::equal_range(this->header_ptr(), key, this->key_node_comp(comp));
      return std::pair<const_iterator, const_iterator>( const_iterator(ret.first, this->priv_value_traits_ptr())
                                                      , const_iterator(ret.second, this->priv_value_traits_ptr()));
   }

   //lower_bound_range
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator,iterator> lower_bound_range(const key_type &key)
   {  return this->lower_bound_range(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> lower_bound_range(const KeyType &key, KeyTypeKeyCompare comp)
   {
      std::pair<node_ptr, node_ptr> ret =
         node_algorithms::lower_bound_range(this->header_ptr(), key, this->key_node_comp(comp));
      return std::pair<iterator, iterator>( iterator(ret.first, this->priv_value_traits_ptr())
                                          , iterator(ret.second, this->priv_value_traits_ptr()));
   }

   BOOST_INTRUSIVE_FORCEINLINE std::pair<const_iterator, const_iterator>
      lower_bound_range(const key_type &key) const
   {  return this->lower_bound_range(key, this->key_comp());   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      lower_bound_range(const KeyType &key, KeyTypeKeyCompare comp) const
   {
      std::pair<node_ptr, node_ptr> ret =
         node_algorithms::lower_bound_range(this->header_ptr(), key, this->key_node_comp(comp));
      return std::pair<const_iterator, const_iterator>( const_iterator(ret.first, this->priv_value_traits_ptr())
                                                      , const_iterator(ret.second, this->priv_value_traits_ptr()));
   }

   //bounded_range
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed)
   {  return this->bounded_range(lower_key, upper_key, this->key_comp(), left_closed, right_closed);   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType &lower_key, const KeyType &upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed)
   {
      std::pair<node_ptr, node_ptr> ret =
         node_algorithms::bounded_range
            (this->header_ptr(), lower_key, upper_key, this->key_node_comp(comp), left_closed, right_closed);
      return std::pair<iterator, iterator>( iterator(ret.first, this->priv_value_traits_ptr())
                                          , iterator(ret.second, this->priv_value_traits_ptr()));
   }

   BOOST_INTRUSIVE_FORCEINLINE std::pair<const_iterator,const_iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const
   {  return this->bounded_range(lower_key, upper_key, this->key_comp(), left_closed, right_closed);   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator,const_iterator> bounded_range
      (const KeyType &lower_key, const KeyType &upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const
   {
      std::pair<node_ptr, node_ptr> ret =
         node_algorithms::bounded_range
            (this->header_ptr(), lower_key, upper_key, this->key_node_comp(comp), left_closed, right_closed);
      return std::pair<const_iterator, const_iterator>( const_iterator(ret.first, this->priv_value_traits_ptr())
                                                      , const_iterator(ret.second, this->priv_value_traits_ptr()));
   }

   //insert_unique_check
   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator, bool> insert_unique_check
      (const key_type &key, insert_commit_data &commit_data)
   {  return this->insert_unique_check(key, this->key_comp(), commit_data);   }

   BOOST_INTRUSIVE_FORCEINLINE std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const key_type &key, insert_commit_data &commit_data)
   {  return this->insert_unique_check(hint, key, this->key_comp(), commit_data);   }

   template<class KeyType, class KeyTypeKeyCompare>
   BOOST_INTRUSIVE_DOC1ST(std::pair<iterator BOOST_INTRUSIVE_I bool>
      , typename detail::disable_if_convertible
         <KeyType BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I 
         std::pair<iterator BOOST_INTRUSIVE_I bool> >::type)
      insert_unique_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> ret =
         (node_algorithms::insert_unique_check
            (this->header_ptr(), key, this->key_node_comp(comp), commit_data));
      return std::pair<iterator, bool>(iterator(ret.first, this->priv_value_traits_ptr()), ret.second);
   }

   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data)
   {
      std::pair<node_ptr, bool> ret =
         (node_algorithms::insert_unique_check
            (this->header_ptr(), hint.pointed_node(), key, this->key_node_comp(comp), commit_data));
      return std::pair<iterator, bool>(iterator(ret.first, this->priv_value_traits_ptr()), ret.second);
   }
};

//Due to MSVC's EBO implementation, to save space and maintain the ABI, we must put the non-empty size member
//in the first position, but if size is not going to be stored then we'll use an specialization
//that doesn't inherit from size_holder
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, bool ConstantTimeSize, class SizeType, algo_types AlgoType, typename HeaderHolder>
struct bstbase_hack
   : public detail::size_holder<ConstantTimeSize, SizeType>
   , public bstbase2 < ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, AlgoType, HeaderHolder>
{
   typedef bstbase2< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, AlgoType, HeaderHolder> base_type;
   typedef typename base_type::key_compare         key_compare;
   typedef typename base_type::value_compare       value_compare;
   typedef SizeType                                size_type;
   typedef typename base_type::node_traits         node_traits;
   typedef typename get_algo
      <AlgoType, node_traits>::type                algo_type;

   BOOST_INTRUSIVE_FORCEINLINE bstbase_hack(const key_compare & comp, const ValueTraits &vtraits)
      : base_type(comp, vtraits)
   {
      this->sz_traits().set_size(size_type(0));
   }

   typedef detail::size_holder<ConstantTimeSize, SizeType>     size_traits;

   BOOST_INTRUSIVE_FORCEINLINE size_traits &sz_traits()
   {  return static_cast<size_traits &>(*this);  }

   BOOST_INTRUSIVE_FORCEINLINE const size_traits &sz_traits() const
   {  return static_cast<const size_traits &>(*this);  }
};

//Specialization for ConstantTimeSize == false
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class SizeType, algo_types AlgoType, typename HeaderHolder>
struct bstbase_hack<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, false, SizeType, AlgoType, HeaderHolder>
   : public bstbase2 < ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, AlgoType, HeaderHolder>
{
   typedef bstbase2< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, AlgoType, HeaderHolder> base_type;
   typedef typename base_type::value_compare       value_compare;
   typedef typename base_type::key_compare         key_compare;
   BOOST_INTRUSIVE_FORCEINLINE bstbase_hack(const key_compare & comp, const ValueTraits &vtraits)
      : base_type(comp, vtraits)
   {}

   typedef detail::size_holder<false, SizeType>     size_traits;

   BOOST_INTRUSIVE_FORCEINLINE size_traits sz_traits() const
   {  return size_traits();  }
};

//This class will
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, bool ConstantTimeSize, class SizeType, algo_types AlgoType, typename HeaderHolder>
struct bstbase
   : public bstbase_hack< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, ConstantTimeSize, SizeType, AlgoType, HeaderHolder>
{
   typedef bstbase_hack< ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, ConstantTimeSize, SizeType, AlgoType, HeaderHolder> base_type;
   typedef ValueTraits                             value_traits;
   typedef typename base_type::value_compare       value_compare;
   typedef typename base_type::key_compare         key_compare;
   typedef typename base_type::const_reference     const_reference;
   typedef typename base_type::reference           reference;
   typedef typename base_type::iterator            iterator;
   typedef typename base_type::const_iterator      const_iterator;
   typedef typename base_type::node_traits         node_traits;
   typedef typename get_algo
      <AlgoType, node_traits>::type                node_algorithms;
   typedef SizeType                                size_type;

   BOOST_INTRUSIVE_FORCEINLINE bstbase(const key_compare & comp, const ValueTraits &vtraits)
      : base_type(comp, vtraits)
   {}

   //Detach all inserted nodes. This will add exception safety to bstree_impl
   //constructors inserting elements.
   ~bstbase()
   {
      if(is_safe_autounlink<value_traits::link_mode>::value){
         node_algorithms::clear_and_dispose
            ( this->header_ptr()
            , detail::node_disposer<detail::null_disposer, value_traits, AlgoType>
               (detail::null_disposer(), &this->get_value_traits()));
         node_algorithms::init(this->header_ptr());
      }
   }
};


/// @endcond

//! The class template bstree is an unbalanced intrusive binary search tree
//! container. The no-throw guarantee holds only, if the key_compare object
//! doesn't throw.
//!
//! The complexity guarantees only hold if the tree is balanced, logarithmic
//! complexity would increase to linear if the tree is totally unbalanced.
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
template<class ValueTraits, class VoidOrKeyOfValue, class VoidOrKeyComp, class SizeType, bool ConstantTimeSize, algo_types AlgoType, typename HeaderHolder>
#endif
class bstree_impl
   :  public bstbase<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, ConstantTimeSize, SizeType, AlgoType, HeaderHolder>
{
   public:
   /// @cond
   typedef bstbase<ValueTraits, VoidOrKeyOfValue, VoidOrKeyComp, ConstantTimeSize, SizeType, AlgoType, HeaderHolder> data_type;
   typedef tree_iterator<ValueTraits, false> iterator_type;
   typedef tree_iterator<ValueTraits, true>  const_iterator_type;
   /// @endcond

   typedef BOOST_INTRUSIVE_IMPDEF(ValueTraits)                                                  value_traits;
   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::pointer)                               pointer;
   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::const_pointer)                         const_pointer;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<pointer>::element_type)               value_type;
   typedef BOOST_INTRUSIVE_IMPDEF(typename data_type::key_type)                                 key_type;
   typedef BOOST_INTRUSIVE_IMPDEF(typename data_type::key_of_value)                             key_of_value;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<pointer>::reference)                  reference;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<const_pointer>::reference)            const_reference;
   typedef BOOST_INTRUSIVE_IMPDEF(typename pointer_traits<const_pointer>::difference_type)      difference_type;
   typedef BOOST_INTRUSIVE_IMPDEF(SizeType)                                                     size_type;
   typedef BOOST_INTRUSIVE_IMPDEF(typename data_type::value_compare)                            value_compare;
   typedef BOOST_INTRUSIVE_IMPDEF(typename data_type::key_compare)                              key_compare;
   typedef BOOST_INTRUSIVE_IMPDEF(iterator_type)                                                iterator;
   typedef BOOST_INTRUSIVE_IMPDEF(const_iterator_type)                                          const_iterator;
   typedef BOOST_INTRUSIVE_IMPDEF(boost::intrusive::reverse_iterator<iterator>)                 reverse_iterator;
   typedef BOOST_INTRUSIVE_IMPDEF(boost::intrusive::reverse_iterator<const_iterator>)           const_reverse_iterator;
   typedef BOOST_INTRUSIVE_IMPDEF(typename value_traits::node_traits)                           node_traits;
   typedef BOOST_INTRUSIVE_IMPDEF(typename node_traits::node)                                   node;
   typedef BOOST_INTRUSIVE_IMPDEF(typename node_traits::node_ptr)                               node_ptr;
   typedef BOOST_INTRUSIVE_IMPDEF(typename node_traits::const_node_ptr)                         const_node_ptr;
   /// @cond
   typedef typename get_algo<AlgoType, node_traits>::type                                       algo_type;
   /// @endcond
   typedef BOOST_INTRUSIVE_IMPDEF(algo_type)                                                    node_algorithms;

   static const bool constant_time_size = ConstantTimeSize;
   static const bool stateful_value_traits = detail::is_stateful_value_traits<value_traits>::value;
   /// @cond
   private:

   //noncopyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(bstree_impl)

   static const bool safemode_or_autounlink = is_safe_autounlink<value_traits::link_mode>::value;

   //Constant-time size is incompatible with auto-unlink hooks!
   BOOST_STATIC_ASSERT(!(constant_time_size && ((int)value_traits::link_mode == (int)auto_unlink)));


   protected:


   /// @endcond

   public:

   typedef typename node_algorithms::insert_commit_data insert_commit_data;

   //! <b>Effects</b>: Constructs an empty container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor of the key_compare object throws. Basic guarantee.
   bstree_impl()
      :  data_type(key_compare(), value_traits())
   {}

   //! <b>Effects</b>: Constructs an empty container with given comparison and traits.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor of the key_compare object throws. Basic guarantee.
   explicit bstree_impl( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  data_type(cmp, v_traits)
   {}

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue of type value_type.
   //!   cmp must be a comparison function that induces a strict weak ordering.
   //!
   //! <b>Effects</b>: Constructs an empty container and inserts elements from
   //!   [b, e).
   //!
   //! <b>Complexity</b>: Linear in N if [b, e) is already sorted using
   //!   comp and otherwise N * log N, where N is the distance between first and last.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor/operator() of the key_compare object throws. Basic guarantee.
   template<class Iterator>
   bstree_impl( bool unique, Iterator b, Iterator e
              , const key_compare &cmp     = key_compare()
              , const value_traits &v_traits = value_traits())
      : data_type(cmp, v_traits)
   {
      //bstbase releases elements in case of exceptions
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   //! <b>Effects</b>: Constructs a container moving resources from another container.
   //!   Internal comparison object and value traits are move constructed and
   //!   nodes belonging to x (except the node representing the "end") are linked to *this.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node's
   //!   move constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the move constructor of the comparison objet throws.
   bstree_impl(BOOST_RV_REF(bstree_impl) x)
      : data_type(::boost::move(x.get_comp()), ::boost::move(x.get_value_traits()))
   {
      this->swap(x);
   }

   //! <b>Effects</b>: Equivalent to swap
   //!
   BOOST_INTRUSIVE_FORCEINLINE bstree_impl& operator=(BOOST_RV_REF(bstree_impl) x)
   {  this->swap(x); return *this;  }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! <b>Effects</b>: Detaches all elements from this. The objects in the set
   //!   are not deleted (i.e. no destructors are called), but the nodes according to
   //!   the value_traits template parameter are reinitialized and thus can be reused.
   //!
   //! <b>Complexity</b>: Linear to elements contained in *this.
   //!
   //! <b>Throws</b>: Nothing.
   ~bstree_impl()
   {}

   //! <b>Effects</b>: Returns an iterator pointing to the beginning of the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   iterator begin() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning of the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator begin() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning of the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator cbegin() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns an iterator pointing to the end of the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   iterator end() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator end() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator cend() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning of the
   //!    reversed container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   reverse_iterator rbegin() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //!    of the reversed container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //!    of the reversed container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //!    of the reversed container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   reverse_iterator rend() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //!    of the reversed container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_reverse_iterator rend() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //!    of the reversed container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_reverse_iterator crend() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a iterator pointing to the root node of the container or end() if not present.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   iterator root() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_iterator pointing to the root node of the container or cend() if not present.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator root() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns a const_iterator pointing to the root node of the container or cend() if not present.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator croot() const BOOST_NOEXCEPT;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Precondition</b>: end_iterator must be a valid end iterator
   //!   of the container.
   //!
   //! <b>Effects</b>: Returns a const reference to the container associated to the end iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   static bstree_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {
      return static_cast<bstree_impl&>
               (data_type::get_tree_base_from_end_iterator(end_iterator));
   }

   //! <b>Precondition</b>: end_iterator must be a valid end const_iterator
   //!   of the container.
   //!
   //! <b>Effects</b>: Returns a const reference to the container associated to the iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   static const bstree_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {
      return static_cast<bstree_impl&>
               (data_type::get_tree_base_from_end_iterator(end_iterator));
   }

   //! <b>Precondition</b>: it must be a valid iterator
   //!   of the container.
   //!
   //! <b>Effects</b>: Returns a const reference to the container associated to the iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Logarithmic.
   static bstree_impl &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return container_from_end_iterator(it.end_iterator_from_it());   }

   //! <b>Precondition</b>: it must be a valid end const_iterator
   //!   of container.
   //!
   //! <b>Effects</b>: Returns a const reference to the container associated to the end iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Logarithmic.
   static const bstree_impl &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return container_from_end_iterator(it.end_iterator_from_it());   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Effects</b>: Returns the key_compare object used by the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If key_compare copy-constructor throws.
   key_compare key_comp() const;

   //! <b>Effects</b>: Returns the value_compare object used by the container.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_compare copy-constructor throws.
   value_compare value_comp() const;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Effects</b>: Returns true if the container is empty.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   bool empty() const BOOST_NOEXCEPT
   {
      if(ConstantTimeSize){
         return !this->data_type::sz_traits().get_size();
      }
      else{
         return algo_type::unique(this->header_ptr());
      }
   }

   //! <b>Effects</b>: Returns the number of elements stored in the container.
   //!
   //! <b>Complexity</b>: Linear to elements contained in *this
   //!   if constant-time size option is disabled. Constant time otherwise.
   //!
   //! <b>Throws</b>: Nothing.
   size_type size() const BOOST_NOEXCEPT
   {
      BOOST_IF_CONSTEXPR(constant_time_size)
         return this->sz_traits().get_size();
      else{
         return (size_type)node_algorithms::size(this->header_ptr());
      }
   }

   //! <b>Effects</b>: Swaps the contents of two containers.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If the comparison functor's swap call throws.
   void swap(bstree_impl& other)
   {
      //This can throw
      ::boost::adl_move_swap(this->get_comp(), other.get_comp());
      //These can't throw
      node_algorithms::swap_tree(this->header_ptr(), node_ptr(other.header_ptr()));
      this->sz_traits().swap(other.sz_traits());
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!   Cloner should yield to nodes equivalent to the original nodes.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the
   //!   elements from src calling Cloner::operator()(const_reference )
   //!   and inserts them on *this. Copies the predicate from the source container.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //!
   //! <b>Throws</b>: If cloner throws or predicate copy assignment throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(const bstree_impl &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      if(!src.empty()){
         detail::exception_disposer<bstree_impl, Disposer>
            rollback(*this, disposer);
         node_algorithms::clone
            (src.header_ptr()
            ,this->header_ptr()
            ,detail::node_cloner <Cloner,    value_traits, AlgoType>(cloner,   &this->get_value_traits())
            ,detail::node_disposer<Disposer, value_traits, AlgoType>(disposer, &this->get_value_traits()));
         this->sz_traits().set_size(src.sz_traits().get_size());
         this->get_comp() = src.get_comp();
         rollback.release();
      }
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!   Cloner should yield to nodes equivalent to the original nodes.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the
   //!   elements from src calling Cloner::operator()(reference)
   //!   and inserts them on *this. Copies the predicate from the source container.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //!
   //! <b>Throws</b>: If cloner throws or predicate copy assignment throws. Basic guarantee.
   //!
   //! <b>Note</b>: This version can modify the source container, useful to implement
   //!    move semantics.
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(bstree_impl) src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      if(!src.empty()){
         detail::exception_disposer<bstree_impl, Disposer>
            rollback(*this, disposer);
         node_algorithms::clone
            (src.header_ptr()
            ,this->header_ptr()
            ,detail::node_cloner <Cloner,    value_traits, AlgoType, false>(cloner,   &this->get_value_traits())
            ,detail::node_disposer<Disposer, value_traits, AlgoType>(disposer, &this->get_value_traits()));
         this->sz_traits().set_size(src.sz_traits().get_size());
         this->get_comp() = src.get_comp();
         rollback.release();
      }
   }

   //! <b>Requires</b>: value must be an lvalue
   //!
   //! <b>Effects</b>: Inserts value into the container before the upper bound.
   //!
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //!
   //! <b>Throws</b>: If the internal key_compare ordering function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert_equal(reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      iterator ret(node_algorithms::insert_equal_upper_bound
         (this->header_ptr(), to_insert, this->key_node_comp(this->key_comp())), this->priv_value_traits_ptr());
      this->sz_traits().increment();
      return ret;
   }

   //! <b>Requires</b>: value must be an lvalue, and "hint" must be
   //!   a valid iterator.
   //!
   //! <b>Effects</b>: Inserts x into the container, using "hint" as a hint to
   //!   where it will be inserted. If "hint" is the upper_bound
   //!   the insertion takes constant time (two comparisons in the worst case)
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it is amortized
   //!   constant time if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the internal key_compare ordering function throws. Strong guarantee.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert_equal(const_iterator hint, reference value)
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      iterator ret(node_algorithms::insert_equal
         (this->header_ptr(), hint.pointed_node(), to_insert, this->key_node_comp(this->key_comp())), this->priv_value_traits_ptr());
      this->sz_traits().increment();
      return ret;
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue
   //!   of type value_type.
   //!
   //! <b>Effects</b>: Inserts a each element of a range into the container
   //!   before the upper bound of the key of each element.
   //!
   //! <b>Complexity</b>: Insert range is in general O(N * log(N)), where N is the
   //!   size of the range. However, it is linear in N if the range is already sorted
   //!   by value_comp().
   //!
   //! <b>Throws</b>: If the comparison functor call throws.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

   //! <b>Requires</b>: value must be an lvalue
   //!
   //! <b>Effects</b>: Inserts value into the container if the value
   //!   is not already present.
   //!
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //!
   //! <b>Throws</b>: If the comparison functor call throws.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   std::pair<iterator, bool> insert_unique(reference value)
   {
      insert_commit_data commit_data;
      std::pair<node_ptr, bool> ret =
         (node_algorithms::insert_unique_check
            (this->header_ptr(), key_of_value()(value), this->key_node_comp(this->key_comp()), commit_data));
      return std::pair<iterator, bool>
         ( ret.second ? this->insert_unique_commit(value, commit_data)
                      : iterator(ret.first, this->priv_value_traits_ptr())
         , ret.second);
   }

   //! <b>Requires</b>: value must be an lvalue, and "hint" must be
   //!   a valid iterator
   //!
   //! <b>Effects</b>: Tries to insert x into the container, using "hint" as a hint
   //!   to where it will be inserted.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it is amortized
   //!   constant time (two comparisons in the worst case)
   //!   if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the comparison functor call throws.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert_unique(const_iterator hint, reference value)
   {
      insert_commit_data commit_data;
      std::pair<node_ptr, bool> ret =
         (node_algorithms::insert_unique_check
            (this->header_ptr(), hint.pointed_node(), key_of_value()(value), this->key_node_comp(this->key_comp()), commit_data));
      return ret.second ? this->insert_unique_commit(value, commit_data)
                        : iterator(ret.first, this->priv_value_traits_ptr());
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue
   //!   of type value_type.
   //!
   //! <b>Effects</b>: Tries to insert each element of a range into the container.
   //!
   //! <b>Complexity</b>: Insert range is in general O(N * log(N)), where N is the
   //!   size of the range. However, it is linear in N if the range is already sorted
   //!   by value_comp().
   //!
   //! <b>Throws</b>: If the comparison functor call throws.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   template<class Iterator>
   void insert_unique(Iterator b, Iterator e)
   {
      if(this->empty()){
         iterator iend(this->end());
         for (; b != e; ++b)
            this->insert_unique(iend, *b);
      }
      else{
         for (; b != e; ++b)
            this->insert_unique(*b);
      }
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Average complexity is at most logarithmic.
   //!
   //! <b>Throws</b>: If the comp ordering function throws. Strong guarantee.
   std::pair<iterator, bool> insert_unique_check(const key_type &key, insert_commit_data &commit_data);

   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself, using "hint"
   //!   as a hint to where it will be inserted.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it's amortized
   //!   constant time if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the comp ordering function throws. Strong guarantee.
   std::pair<iterator, bool> insert_unique_check(const_iterator hint, const key_type &key, insert_commit_data &commit_data);

   //! <b>Requires</b>: comp must be a comparison function that induces
   //!   the same strict weak ordering as key_compare. The difference is that
   //!   comp compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Average complexity is at most logarithmic.
   //!
   //! <b>Throws</b>: If the comp ordering function throws. Strong guarantee.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the value_type and this function offers the possibility to use that
   //!   part to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the container.
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const KeyType &key, KeyTypeKeyCompare comp, insert_commit_data &commit_data);

   //! <b>Requires</b>: comp must be a comparison function that induces
   //!   the same strict weak ordering as key_compare. The difference is that
   //!   comp compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Checks if a value can be inserted in the container, using
   //!   a user provided key instead of the value itself, using "hint"
   //!   as a hint to where it will be inserted.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it's amortized
   //!   constant time if t is inserted immediately before hint.
   //!
   //! <b>Throws</b>: If the comp ordering function throws. Strong guarantee.
   //!
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   constructing that is used to impose the order is much cheaper to construct
   //!   than the value_type and this function offers the possibility to use that key
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time. This can give a total
   //!   constant-time complexity to the insertion: check(O(1)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the container.
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator, bool> insert_unique_check
      (const_iterator hint, const KeyType &key
      ,KeyTypeKeyCompare comp, insert_commit_data &commit_data);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! <b>Requires</b>: value must be an lvalue of type value_type. commit_data
   //!   must have been obtained from a previous call to "insert_check".
   //!   No objects should have been inserted or erased from the container between
   //!   the "insert_check" that filled "commit_data" and the call to "insert_commit".
   //!
   //! <b>Effects</b>: Inserts the value in the container using the information obtained
   //!   from the "commit_data" that a previous "insert_check" filled.
   //!
   //! <b>Returns</b>: An iterator to the newly inserted object.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Notes</b>: This function has only sense if a "insert_check" has been
   //!   previously executed to fill "commit_data". No value should be inserted or
   //!   erased between the "insert_check" and "insert_commit" calls.
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));

      #if !(defined(BOOST_DISABLE_ASSERTS) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && defined(NDEBUG) ))
      //Test insertion position is correct
      iterator p(commit_data.node, this->priv_value_traits_ptr());
      if(!commit_data.link_left){
         ++p;
      }
      //Check if the insertion point is correct to detect wrong
      //uses insert_unique_check
      BOOST_ASSERT(( p == this->end()   || !this->get_comp()(*p, value)   ));
      BOOST_ASSERT(( p == this->begin() || !this->get_comp()(value, *--p) ));
      #endif

      node_algorithms::insert_unique_commit
               (this->header_ptr(), to_insert, commit_data);
      this->sz_traits().increment();
      return iterator(to_insert, this->priv_value_traits_ptr());
   }

   //! <b>Requires</b>: value must be an lvalue, "pos" must be
   //!   a valid iterator (or end) and must be the succesor of value
   //!   once inserted according to the predicate
   //!
   //! <b>Effects</b>: Inserts x into the container before "pos".
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: This function does not check preconditions so if "pos" is not
   //! the successor of "value" container ordering invariant will be broken.
   //! This is a low-level function to be used only for performance reasons
   //! by advanced users.
   iterator insert_before(const_iterator pos, reference value) BOOST_NOEXCEPT
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      this->sz_traits().increment();
      return iterator(node_algorithms::insert_before
         (this->header_ptr(), pos.pointed_node(), to_insert), this->priv_value_traits_ptr());
   }

   //! <b>Requires</b>: value must be an lvalue, and it must be no less
   //!   than the greatest inserted key
   //!
   //! <b>Effects</b>: Inserts x into the container in the last position.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: This function does not check preconditions so if value is
   //!   less than the greatest inserted key container ordering invariant will be broken.
   //!   This function is slightly more efficient than using "insert_before".
   //!   This is a low-level function to be used only for performance reasons
   //!   by advanced users.
   void push_back(reference value) BOOST_NOEXCEPT
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      this->sz_traits().increment();
      node_algorithms::push_back(this->header_ptr(), to_insert);
   }

   //! <b>Requires</b>: value must be an lvalue, and it must be no greater
   //!   than the minimum inserted key
   //!
   //! <b>Effects</b>: Inserts x into the container in the first position.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: This function does not check preconditions so if value is
   //!   greater than the minimum inserted key container ordering invariant will be broken.
   //!   This function is slightly more efficient than using "insert_before".
   //!   This is a low-level function to be used only for performance reasons
   //!   by advanced users.
   void push_front(reference value) BOOST_NOEXCEPT
   {
      node_ptr to_insert(this->get_value_traits().to_node_ptr(value));
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(to_insert));
      this->sz_traits().increment();
      node_algorithms::push_front(this->header_ptr(), to_insert);
   }

   //! <b>Effects</b>: Erases the element pointed to by i.
   //!
   //! <b>Complexity</b>: Average complexity for erase element is constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   iterator erase(const_iterator i) BOOST_NOEXCEPT
   {
      const_iterator ret(i);
      ++ret;
      node_ptr to_erase(i.pointed_node());
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(to_erase));
      node_algorithms::erase(this->header_ptr(), to_erase);
      this->sz_traits().decrement();
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      return ret.unconst();
   }

   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!
   //! <b>Complexity</b>: Average complexity for erase range is at most
   //!   O(log(size() + N)), where N is the number of elements in the range.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT
   {  size_type n;   return this->private_erase(b, e, n);   }

   //! <b>Effects</b>: Erases all the elements with the given value.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   size_type erase(const key_type &key) BOOST_NOEXCEPT
   {  return this->erase(key, this->key_comp());   }

   //! <b>Requires</b>: key is a value such that `*this` is partitioned with respect to
   //!   comp(nk, key) and !comp(key, nk), with comp(nk, key) implying !comp(key, nk),
   //!   with nk the key_type of a value_type inserted into `*this`.
   //!
   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "comp".
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class KeyType, class KeyTypeKeyCompare>
   BOOST_INTRUSIVE_DOC1ST(size_type
      , typename detail::disable_if_convertible<KeyTypeKeyCompare BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I size_type>::type)
      erase(const KeyType& key, KeyTypeKeyCompare comp)
   {
      std::pair<iterator,iterator> p = this->equal_range(key, comp);
      size_type n;
      this->private_erase(p.first, p.second, n);
      return n;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed to by i.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Complexity</b>: Average complexity for erase element is constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT
   {
      node_ptr to_erase(i.pointed_node());
      iterator ret(this->erase(i));
      disposer(this->get_value_traits().to_value_ptr(to_erase));
      return ret;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given value.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Disposer>
   size_type erase_and_dispose(const key_type &key, Disposer disposer)
   {
      std::pair<iterator,iterator> p = this->equal_range(key);
      size_type n;
      this->private_erase(p.first, p.second, n, disposer);
      return n;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Complexity</b>: Average complexity for erase range is at most
   //!   O(log(size() + N)), where N is the number of elements in the range.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT
   {  size_type n;   return this->private_erase(b, e, n, disposer);   }

   //! <b>Requires</b>: key is a value such that `*this` is partitioned with respect to
   //!   comp(nk, key) and !comp(key, nk), with comp(nk, key) implying !comp(key, nk)
   //!   and nk the key_type of a value_type inserted into `*this`.
   //!
   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "comp".
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //!
   //! <b>Complexity</b>: O(log(size() + N).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class KeyType, class KeyTypeKeyCompare, class Disposer>
   BOOST_INTRUSIVE_DOC1ST(size_type
      , typename detail::disable_if_convertible<KeyTypeKeyCompare BOOST_INTRUSIVE_I const_iterator BOOST_INTRUSIVE_I size_type>::type)
      erase_and_dispose(const KeyType& key, KeyTypeKeyCompare comp, Disposer disposer)
   {
      std::pair<iterator,iterator> p = this->equal_range(key, comp);
      size_type n;
      this->private_erase(p.first, p.second, n, disposer);
      return n;
   }

   //! <b>Effects</b>: Erases all of the elements.
   //!
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   if it's a safe-mode or auto-unlink value_type. Constant time otherwise.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   void clear() BOOST_NOEXCEPT
   {
      BOOST_IF_CONSTEXPR(safemode_or_autounlink){
         this->clear_and_dispose(detail::null_disposer());
      }
      else{
         node_algorithms::init_header(this->header_ptr());
         this->sz_traits().set_size(0);
      }
   }

   //! <b>Effects</b>: Erases all of the elements calling disposer(p) for
   //!   each node to be erased.
   //! <b>Complexity</b>: Average complexity for is at most O(log(size() + N)),
   //!   where N is the number of elements in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. Calls N times to disposer functor.
   template<class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT
   {
      node_algorithms::clear_and_dispose(this->header_ptr()
         , detail::node_disposer<Disposer, value_traits, AlgoType>(disposer, &this->get_value_traits()));
      node_algorithms::init_header(this->header_ptr());
      this->sz_traits().set_size(0);
   }

   //! <b>Effects</b>: Returns the number of contained elements with the given value
   //!
   //! <b>Complexity</b>: Logarithmic to the number of elements contained plus lineal
   //!   to number of objects with the given value.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   size_type count(const key_type &key) const
   {  return size_type(this->count(key, this->key_comp()));   }

   //! <b>Requires</b>: key is a value such that `*this` is partitioned with respect to
   //!   comp(nk, key) and !comp(key, nk), with comp(nk, key) implying !comp(key, nk),
   //!   and nk the key_type of a value_type inserted into `*this`.
   //!
   //! <b>Effects</b>: Returns the number of contained elements with the given key
   //!
   //! <b>Complexity</b>: Logarithmic to the number of elements contained plus lineal
   //!   to number of objects with the given key.
   //!
   //! <b>Throws</b>: If `comp` throws.
   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType &key, KeyTypeKeyCompare comp) const
   {
      std::pair<const_iterator, const_iterator> ret = this->equal_range(key, comp);
      size_type n = 0;
      for(; ret.first != ret.second; ++ret.first){ ++n; }
      return n;
   }

   #if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //Add non-const overloads to theoretically const members
   //as some algorithms have different behavior when non-const versions are used (like splay trees).
   size_type count(const key_type &key)
   {  return size_type(this->count(key, this->key_comp()));   }

   template<class KeyType, class KeyTypeKeyCompare>
   size_type count(const KeyType &key, KeyTypeKeyCompare comp)
   {
      std::pair<const_iterator, const_iterator> ret = this->equal_range(key, comp);
      size_type n = 0;
      for(; ret.first != ret.second; ++ret.first){ ++n; }
      return n;
   }

   #else //defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Returns an iterator to the first element whose
   //!   key is not less than k or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   iterator lower_bound(const key_type &key);

   //! <b>Effects</b>: Returns an iterator to the first element whose
   //!   key is not less than k or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   const_iterator lower_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const key_type &)
   template<class KeyType, class KeyTypeKeyCompare>
   iterator lower_bound(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::lower_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator lower_bound(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! <b>Effects</b>: Returns an iterator to the first element whose
   //!   key is greater than k or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   iterator upper_bound(const key_type &key);

   //! <b>Requires</b>: key is a value such that `*this` is partitioned with respect to
   //!   !comp(key, nk), with nk the key_type of a value_type inserted into `*this`.
   //!
   //! <b>Effects</b>: Returns an iterator to the first element whose
   //!   key is greater than k according to comp or end() if that element
   //!   does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `comp` throws.
   template<class KeyType, class KeyTypeKeyCompare>
   iterator upper_bound(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const key_type &)
   const_iterator upper_bound(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::upper_bound(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator upper_bound(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! <b>Effects</b>: Finds an iterator to the first element whose key is
   //!   k or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   iterator find(const key_type &key);

   //! <b>Requires</b>: key is a value such that `*this` is partitioned with respect to
   //!   comp(nk, key) and !comp(key, nk), with comp(nk, key) implying !comp(key, nk),
   //!   and nk the key_type of a value_type inserted into `*this`.
   //!
   //! <b>Effects</b>: Finds an iterator to the first element whose key is
   //!   k or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `comp` throws.
   template<class KeyType, class KeyTypeKeyCompare>
   iterator find(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::find(const key_type &)
   const_iterator find(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::find(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   const_iterator find(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! <b>Effects</b>: Finds a range containing all elements whose key is k or
   //!   an empty range that indicates the position where those elements would be
   //!   if they there is no elements with key k.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   std::pair<iterator,iterator> equal_range(const key_type &key);

   //! <b>Requires</b>: key is a value such that `*this` is partitioned with respect to
   //!   comp(nk, key) and !comp(key, nk), with comp(nk, key) implying !comp(key, nk),
   //!   with nk the key_type of a value_type inserted into `*this`.
   //!
   //! <b>Effects</b>: Finds a range containing all elements whose key is k or
   //!   an empty range that indicates the position where those elements would be
   //!   if they there is no elements with key k.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `comp` throws.
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> equal_range(const KeyType &key, KeyTypeKeyCompare comp);

   //! @copydoc ::boost::intrusive::bstree::equal_range(const key_type &)
   std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

   //! @copydoc ::boost::intrusive::bstree::equal_range(const KeyType&,KeyTypeKeyCompare)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType &key, KeyTypeKeyCompare comp) const;

   //! <b>Requires</b>:
   //!   `upper_key` shall not precede `lower_key` according to key_compare.
   //!   [key_comp()(upper_key, lower_key) shall be false]
   //!
   //!   If `lower_key` is equivalent to `upper_key`
   //!   [!key_comp()(upper_key, lower_key) && !key_comp()(lower_key, upper_key)] then
   //!   ('left_closed' || 'right_closed') must be false.
   //!
   //! <b>Effects</b>: Returns an a pair with the following criteria:
   //!
   //!   first = lower_bound(lower_key) if left_closed, upper_bound(lower_key) otherwise
   //!
   //!   second = upper_bound(upper_key) if right_closed, lower_bound(upper_key) otherwise
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `key_compare` throws.
   //!
   //! <b>Note</b>: This function can be more efficient than calling upper_bound
   //!   and lower_bound for lower_value and upper_value.
   //!
   //! <b>Note</b>: Experimental function, the interface might change in future releases.
   std::pair<iterator,iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_value, bool left_closed, bool right_closed);

   //! <b>Requires</b>:
   //!   `lower_key` is a value such that `*this` is partitioned with respect to
   //!   comp(nk, lower_key) if left_closed is true, with respect to !comp(lower_key, nk) otherwise.
   //!
   //! `upper_key` is a value such that `*this` is partitioned with respect to
   //!   !comp(upper_key, nk) if right_closed is true, with respect to comp(nk, upper_key) otherwise.
   //!
   //!   `upper_key` shall not precede `lower_key` according to comp
   //!   [comp(upper_key, lower_key) shall be false]
   //!
   //!   If `lower_key` is equivalent to `upper_key`
   //!   [!comp(upper_key, lower_key) && !comp(lower_key, upper_key)] then
   //!   ('left_closed' || 'right_closed') must be false.
   //!
   //! <b>Effects</b>: Returns an a pair with the following criteria:
   //!
   //!   first = lower_bound(lower_key, comp) if left_closed, upper_bound(lower_key, comp) otherwise
   //!
   //!   second = upper_bound(upper_key, comp) if right_closed, lower_bound(upper_key, comp) otherwise
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: If `comp` throws.
   //!
   //! <b>Note</b>: This function can be more efficient than calling upper_bound
   //!   and lower_bound for lower_key and upper_key.
   //!
   //! <b>Note</b>: Experimental function, the interface might change in future releases.
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<iterator,iterator> bounded_range
      (const KeyType &lower_key, const KeyType &upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed);
   
   //! @copydoc ::boost::intrusive::bstree::bounded_range(const key_type &,const key_type &,bool,bool)
   std::pair<const_iterator,const_iterator> bounded_range
      (const key_type &lower_key, const key_type &upper_key, bool left_closed, bool right_closed) const;

   //! @copydoc ::boost::intrusive::bstree::bounded_range(const KeyType&,const KeyType&,KeyTypeKeyCompare,bool,bool)
   template<class KeyType, class KeyTypeKeyCompare>
   std::pair<const_iterator,const_iterator> bounded_range
      (const KeyType &lower_key, const KeyType &upper_key, KeyTypeKeyCompare comp, bool left_closed, bool right_closed) const;

   //! <b>Requires</b>: value must be an lvalue and shall be in a set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //!
   //! <b>Effects</b>: Returns: a valid iterator i belonging to the set
   //!   that points to the value
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: This static function is available only if the <i>value traits</i>
   //!   is stateless.
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT;

   //! <b>Requires</b>: value must be an lvalue and shall be in a set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //!
   //! <b>Effects</b>: Returns: a valid const_iterator i belonging to the
   //!   set that points to the value
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: This static function is available only if the <i>value traits</i>
   //!   is stateless.
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT;

   //! <b>Requires</b>: value must be an lvalue and shall be in a set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //!
   //! <b>Effects</b>: Returns: a valid iterator i belonging to the set
   //!   that points to the value
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   iterator iterator_to(reference value) BOOST_NOEXCEPT;

   //! <b>Requires</b>: value must be an lvalue and shall be in a set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //!
   //! <b>Effects</b>: Returns: a valid const_iterator i belonging to the
   //!   set that points to the value
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT;

   //! <b>Requires</b>: value shall not be in a container.
   //!
   //! <b>Effects</b>: init_node puts the hook of a value in a well-known default
   //!   state.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Note</b>: This function puts the hook in the well-known default state
   //!   used by auto_unlink and safe hooks.
   static void init_node(reference value) BOOST_NOEXCEPT;

   #endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Unlinks the leftmost node from the container.
   //!
   //! <b>Complexity</b>: Average complexity is constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Notes</b>: This function breaks the container and the container can
   //!   only be used for more unlink_leftmost_without_rebalance calls.
   //!   This function is normally used to achieve a step by step
   //!   controlled destruction of the container.
   pointer unlink_leftmost_without_rebalance() BOOST_NOEXCEPT
   {
      node_ptr to_be_disposed(node_algorithms::unlink_leftmost_without_rebalance
                           (this->header_ptr()));
      if(!to_be_disposed)
         return 0;
      this->sz_traits().decrement();
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)//If this is commented does not work with normal_link
         node_algorithms::init(to_be_disposed);
      return this->get_value_traits().to_value_ptr(to_be_disposed);
   }

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Requires</b>: replace_this must be a valid iterator of *this
   //!   and with_this must not be inserted in any container.
   //!
   //! <b>Effects</b>: Replaces replace_this in its position in the
   //!   container with with_this. The container does not need to be rebalanced.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Note</b>: This function will break container ordering invariants if
   //!   with_this is not equivalent to *replace_this according to the
   //!   ordering rules. This function is faster than erasing and inserting
   //!   the node, since no rebalancing or comparison is needed.
   void replace_node(iterator replace_this, reference with_this) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Rebalances the tree.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear.
   void rebalance() BOOST_NOEXCEPT;

   //! <b>Requires</b>: old_root is a node of a tree.
   //!
   //! <b>Effects</b>: Rebalances the subtree rooted at old_root.
   //!
   //! <b>Returns</b>: The new root of the subtree.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the elements in the subtree.
   iterator rebalance_subtree(iterator r) BOOST_NOEXCEPT;

   #endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: removes "value" from the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Logarithmic time.
   //!
   //! <b>Note</b>: This static function is only usable with non-constant
   //! time size containers that have stateless comparison functors.
   //!
   //! If the user calls
   //! this function with a constant time size container or stateful comparison
   //! functor a compilation error will be issued.
   static void remove_node(reference value) BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!constant_time_size));
      node_ptr to_remove(value_traits::to_node_ptr(value));
      node_algorithms::unlink(to_remove);
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
         node_algorithms::init(to_remove);
   }

   //! <b>Requires</b>: "source" container's Options can only can differ in the comparison
   //!   function from *this.
   //! 
   //! <b>Effects</b>: Attempts to extract each element in source and insert it into a using
   //!   the comparison object of *this. If there is an element in a with key equivalent to the
   //!   key of an element from source, then that element is not extracted from source.
   //! 
   //! <b>Postcondition</b>: Pointers and references to the transferred elements of source refer
   //!   to those same elements but as members of *this. Iterators referring to the transferred
   //!   elements will continue to refer to their elements, but they now behave as iterators into *this,
   //!   not into source.
   //!
   //! <b>Throws</b>: Nothing unless the comparison object throws.
   //!
   //! <b>Complexity</b>: N log(a.size() + N) (N has the value source.size())
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   template<class T, class ...Options2> void merge_unique(bstree<T, Options2...> &);
   #else
   template<class Compare2>
   void merge_unique(bstree_impl
      <ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, AlgoType, HeaderHolder> &source)
   #endif
   {
      node_ptr it   (node_algorithms::begin_node(source.header_ptr()))
             , itend(node_algorithms::end_node  (source.header_ptr()));

      while(it != itend){
         node_ptr const p(it);
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(p));
         it = node_algorithms::next_node(it);
         if( node_algorithms::transfer_unique(this->header_ptr(), this->key_node_comp(this->key_comp()), source.header_ptr(), p) ){
            source.sz_traits().decrement();
            this->sz_traits().increment();
         }
      }
   }

   //! <b>Requires</b>: "source" container's Options can only can differ in the comparison
   //!   function from *this.
   //! 
   //! <b>Effects</b>: Extracts each element in source and insert it into a using
   //!   the comparison object of *this.
   //! 
   //! <b>Postcondition</b>: Pointers and references to the transferred elements of source refer
   //!   to those same elements but as members of *this. Iterators referring to the transferred
   //!   elements will continue to refer to their elements, but they now behave as iterators into *this,
   //!   not into source.
   //!
   //! <b>Throws</b>: Nothing unless the comparison object throws.
   //!
   //! <b>Complexity</b>: N log(a.size() + N) (N has the value source.size())
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   template<class T, class ...Options2> void merge_equal(bstree<T, Options2...> &);
   #else
   template<class Compare2>
   void merge_equal(bstree_impl
      <ValueTraits, VoidOrKeyOfValue, Compare2, SizeType, ConstantTimeSize, AlgoType, HeaderHolder> &source)
   #endif
   {
      node_ptr it   (node_algorithms::begin_node(source.header_ptr()))
             , itend(node_algorithms::end_node  (source.header_ptr()));

      while(it != itend){
         node_ptr const p(it);
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || !node_algorithms::unique(p));
         it = node_algorithms::next_node(it);
         node_algorithms::transfer_equal(this->header_ptr(), this->key_node_comp(this->key_comp()), source.header_ptr(), p);
         source.sz_traits().decrement();
         this->sz_traits().increment();
      }
   }

   //! <b>Effects</b>: Asserts the integrity of the container with additional checks provided by the user.
   //!
   //! <b>Complexity</b>: Linear time.
   //!
   //! <b>Note</b>: The method might not have effect when asserts are turned off (e.g., with NDEBUG).
   //!   Experimental function, interface might change in future versions.
   template <class ExtraChecker>
   void check(ExtraChecker extra_checker) const
   {
      typedef detail::key_nodeptr_comp<key_compare, value_traits, key_of_value> nodeptr_comp_t;
      nodeptr_comp_t nodeptr_comp(this->key_comp(), &this->get_value_traits());
      typedef typename get_node_checker<AlgoType, ValueTraits, nodeptr_comp_t, ExtraChecker>::type node_checker_t;
      typename node_checker_t::return_type checker_return;
      node_algorithms::check(this->header_ptr(), node_checker_t(nodeptr_comp, extra_checker), checker_return);
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!constant_time_size || this->sz_traits().get_size() == checker_return.node_count);
   }

   //! <b>Effects</b>: Asserts the integrity of the container.
   //!
   //! <b>Complexity</b>: Linear time.
   //!
   //! <b>Note</b>: The method has no effect when asserts are turned off (e.g., with NDEBUG).
   //!   Experimental function, interface might change in future versions.
   void check() const
   {
      check(detail::empty_node_checker<ValueTraits>());
   }

   friend bool operator==(const bstree_impl &x, const bstree_impl &y)
   {
      if(constant_time_size && x.size() != y.size()){
         return false;
      }
      return boost::intrusive::algo_equal(x.cbegin(), x.cend(), y.cbegin(), y.cend());
   }

   friend bool operator!=(const bstree_impl &x, const bstree_impl &y)
   {  return !(x == y); }

   friend bool operator<(const bstree_impl &x, const bstree_impl &y)
   {  return ::boost::intrusive::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   friend bool operator>(const bstree_impl &x, const bstree_impl &y)
   {  return y < x;  }

   friend bool operator<=(const bstree_impl &x, const bstree_impl &y)
   {  return !(x > y);  }

   friend bool operator>=(const bstree_impl &x, const bstree_impl &y)
   {  return !(x < y);  }

   friend void swap(bstree_impl &x, bstree_impl &y)
   {  x.swap(y);  }

   /// @cond
   private:
   template<class Disposer>
   iterator private_erase(const_iterator b, const_iterator e, size_type &n, Disposer disposer)
   {
      for(n = 0; b != e; ++n)
        this->erase_and_dispose(b++, disposer);
      return b.unconst();
   }

   iterator private_erase(const_iterator b, const_iterator e, size_type &n)
   {
      for(n = 0; b != e; ++n)
        this->erase(b++);
      return b.unconst();
   }
   /// @endcond
};

//! Helper metafunction to define a \c bstree that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void
                , class O3 = void, class O4 = void
                , class O5 = void, class O6 = void>
#endif
struct make_bstree
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

   typedef bstree_impl
         < value_traits
         , typename packed_options::key_of_value
         , typename packed_options::compare
         , typename packed_options::size_type
         , packed_options::constant_time_size
         , BsTreeAlgorithms
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
class bstree
   :  public make_bstree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type
{
   typedef typename make_bstree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4, O5, O6
      #else
      Options...
      #endif
      >::type   Base;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(bstree)

   public:
   typedef typename Base::key_compare        key_compare;
   typedef typename Base::value_traits       value_traits;
   typedef typename Base::iterator           iterator;
   typedef typename Base::const_iterator     const_iterator;

   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename value_traits::value_type, T>::value));

   BOOST_INTRUSIVE_FORCEINLINE bstree()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit bstree( const key_compare &cmp, const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE bstree( bool unique, Iterator b, Iterator e
         , const key_compare &cmp = key_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(unique, b, e, cmp, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bstree(BOOST_RV_REF(bstree) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE bstree& operator=(BOOST_RV_REF(bstree) x)
   {  return static_cast<bstree &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const bstree &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(bstree) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static bstree &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<bstree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bstree &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const bstree &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static bstree &container_from_iterator(iterator it) BOOST_NOEXCEPT
   {  return static_cast<bstree &>(Base::container_from_iterator(it));   }

   BOOST_INTRUSIVE_FORCEINLINE static const bstree &container_from_iterator(const_iterator it) BOOST_NOEXCEPT
   {  return static_cast<const bstree &>(Base::container_from_iterator(it));   }
};

#endif
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_BSTREE_HPP

/* bstree.hpp
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
*/