//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_TREE_HPP
#define BOOST_CONTAINER_TREE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
// container
#include <boost/container/allocator_traits.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/options.hpp>
#include <boost/container/node_handle.hpp>

// container/detail
#include <boost/container/detail/algorithm.hpp> //algo_equal(), algo_lexicographical_compare
#include <boost/container/detail/compare_functors.hpp>
#include <boost/container/detail/destroyers.hpp>
#include <boost/container/detail/iterator.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/node_alloc_holder.hpp>
#include <boost/container/detail/pair.hpp>
#include <boost/container/detail/type_traits.hpp>
// intrusive
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/rbtree.hpp>
#include <boost/intrusive/avltree.hpp>
#include <boost/intrusive/splaytree.hpp>
#include <boost/intrusive/sgtree.hpp>
// intrusive/detail
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //pair
#include <boost/intrusive/detail/tree_value_compare.hpp>    //tree_value_compare
// move
#include <boost/move/utility_core.hpp>
// move/detail
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/detail/move_helpers.hpp>
#include <boost/move/detail/force_ptr.hpp>
// other
#include <boost/core/no_exceptions_support.hpp>



#include <boost/container/detail/std_fwd.hpp>

namespace boost {
namespace container {
namespace dtl {

using boost::intrusive::tree_value_compare;

template<class VoidPointer, boost::container::tree_type_enum tree_type_value, bool OptimizeSize>
struct intrusive_tree_hook;

template<class VoidPointer, bool OptimizeSize>
struct intrusive_tree_hook<VoidPointer, boost::container::red_black_tree, OptimizeSize>
{
   typedef typename dtl::bi::make_set_base_hook
      < dtl::bi::void_pointer<VoidPointer>
      , dtl::bi::link_mode<dtl::bi::normal_link>
      , dtl::bi::optimize_size<OptimizeSize>
      >::type  type;
};

template<class VoidPointer, bool OptimizeSize>
struct intrusive_tree_hook<VoidPointer, boost::container::avl_tree, OptimizeSize>
{
   typedef typename dtl::bi::make_avl_set_base_hook
      < dtl::bi::void_pointer<VoidPointer>
      , dtl::bi::link_mode<dtl::bi::normal_link>
      , dtl::bi::optimize_size<OptimizeSize>
      >::type  type;
};

template<class VoidPointer, bool OptimizeSize>
struct intrusive_tree_hook<VoidPointer, boost::container::scapegoat_tree, OptimizeSize>
{
   typedef typename dtl::bi::make_bs_set_base_hook
      < dtl::bi::void_pointer<VoidPointer>
      , dtl::bi::link_mode<dtl::bi::normal_link>
      >::type  type;
};

template<class VoidPointer, bool OptimizeSize>
struct intrusive_tree_hook<VoidPointer, boost::container::splay_tree, OptimizeSize>
{
   typedef typename dtl::bi::make_bs_set_base_hook
      < dtl::bi::void_pointer<VoidPointer>
      , dtl::bi::link_mode<dtl::bi::normal_link>
      >::type  type;
};

//This trait is used to type-pun std::pair because in C++03
//compilers std::pair is useless for C++11 features
template<class T>
struct tree_internal_data_type
{
   typedef T type;
};

template<class T1, class T2>
struct tree_internal_data_type< std::pair<T1, T2> >
{
   typedef pair<typename boost::move_detail::remove_const<T1>::type, T2> type;
};

template <class T, class VoidPointer, boost::container::tree_type_enum tree_type_value, bool OptimizeSize>
struct iiterator_node_value_type< base_node<T, intrusive_tree_hook<VoidPointer, tree_type_value, OptimizeSize> > >
{
  typedef T type;
};

template<class Node, class Icont>
class insert_equal_end_hint_functor
{
   Icont &icont_;

   public:
   BOOST_CONTAINER_FORCEINLINE insert_equal_end_hint_functor(Icont &icont)
      :  icont_(icont)
   {}

   BOOST_CONTAINER_FORCEINLINE void operator()(Node &n)
   {  this->icont_.insert_equal(this->icont_.cend(), n); }
};

template<class Node, class Icont>
class push_back_functor
{
   Icont &icont_;

   public:
   BOOST_CONTAINER_FORCEINLINE push_back_functor(Icont &icont)
      :  icont_(icont)
   {}

   BOOST_CONTAINER_FORCEINLINE void operator()(Node &n)
   {  this->icont_.push_back(n); }
};

}//namespace dtl {

namespace dtl {

template< class NodeType, class NodeCompareType
        , class SizeType,  class HookType
        , boost::container::tree_type_enum tree_type_value>
struct intrusive_tree_dispatch;

template<class NodeType, class NodeCompareType, class SizeType, class HookType>
struct intrusive_tree_dispatch
   <NodeType, NodeCompareType, SizeType, HookType, boost::container::red_black_tree>
{
   typedef typename dtl::bi::make_rbtree
      <NodeType
      ,dtl::bi::compare<NodeCompareType>
      ,dtl::bi::base_hook<HookType>
      ,dtl::bi::constant_time_size<true>
      ,dtl::bi::size_type<SizeType>
      >::type  type;
};

template<class NodeType, class NodeCompareType, class SizeType, class HookType>
struct intrusive_tree_dispatch
   <NodeType, NodeCompareType, SizeType, HookType, boost::container::avl_tree>
{
   typedef typename dtl::bi::make_avltree
      <NodeType
      ,dtl::bi::compare<NodeCompareType>
      ,dtl::bi::base_hook<HookType>
      ,dtl::bi::constant_time_size<true>
      ,dtl::bi::size_type<SizeType>
      >::type  type;
};

template<class NodeType, class NodeCompareType, class SizeType, class HookType>
struct intrusive_tree_dispatch
   <NodeType, NodeCompareType, SizeType, HookType, boost::container::scapegoat_tree>
{
   typedef typename dtl::bi::make_sgtree
      <NodeType
      ,dtl::bi::compare<NodeCompareType>
      ,dtl::bi::base_hook<HookType>
      ,dtl::bi::floating_point<true>
      ,dtl::bi::size_type<SizeType>
      >::type  type;
};

template<class NodeType, class NodeCompareType, class SizeType, class HookType>
struct intrusive_tree_dispatch
   <NodeType, NodeCompareType, SizeType, HookType, boost::container::splay_tree>
{
   typedef typename dtl::bi::make_splaytree
      <NodeType
      ,dtl::bi::compare<NodeCompareType>
      ,dtl::bi::base_hook<HookType>
      ,dtl::bi::constant_time_size<true>
      ,dtl::bi::size_type<SizeType>
      >::type  type;
};

template<class Allocator, class ValueCompare, boost::container::tree_type_enum tree_type_value, bool OptimizeSize>
struct intrusive_tree_type
{
   private:
   typedef typename boost::container::
      allocator_traits<Allocator>::value_type              value_type;
   typedef typename boost::container::
      allocator_traits<Allocator>::void_pointer            void_pointer;
   typedef typename boost::container::
      allocator_traits<Allocator>::size_type               size_type;
   typedef base_node<value_type, intrusive_tree_hook
      <void_pointer, tree_type_value, OptimizeSize> >        node_t;
   typedef value_to_node_compare
      <node_t, ValueCompare>                                node_compare_type;
   //Deducing the hook type from node_t (e.g. node_t::hook_type) would
   //provoke an early instantiation of node_t that could ruin recursive
   //tree definitions, so retype the complete type to avoid any problem.
   typedef typename intrusive_tree_hook
      <void_pointer, tree_type_value
      , OptimizeSize>::type                        hook_type;
   public:
   typedef typename intrusive_tree_dispatch
      < node_t, node_compare_type
      , size_type, hook_type
      , tree_type_value>::type                     type;
};

//Trait to detect manually rebalanceable tree types
template<boost::container::tree_type_enum tree_type_value>
struct is_manually_balanceable
{  static const bool value = true;  };

template<>  struct is_manually_balanceable<red_black_tree>
{  static const bool value = false; };

template<>  struct is_manually_balanceable<avl_tree>
{  static const bool value = false; };

//Proxy traits to implement different operations depending on the
//is_manually_balanceable<>::value
template< boost::container::tree_type_enum tree_type_value
        , bool IsManuallyRebalanceable = is_manually_balanceable<tree_type_value>::value>
struct intrusive_tree_proxy
{
   template<class Icont>
   BOOST_CONTAINER_FORCEINLINE static void rebalance(Icont &)   {}
};

template<boost::container::tree_type_enum tree_type_value>
struct intrusive_tree_proxy<tree_type_value, true>
{
   template<class Icont>
   BOOST_CONTAINER_FORCEINLINE static void rebalance(Icont &c)
   {  c.rebalance(); }
};

}  //namespace dtl {

namespace dtl {

//This functor will be used with Intrusive clone functions to obtain
//already allocated nodes from a intrusive container instead of
//allocating new ones. When the intrusive container runs out of nodes
//the node holder is used instead.
template<class AllocHolder, bool DoMove>
class RecyclingCloner
{
   typedef typename AllocHolder::intrusive_container  intrusive_container;
   typedef typename AllocHolder::Node                 node_t;
   typedef typename AllocHolder::NodePtr              node_ptr_type;

   public:
   RecyclingCloner(AllocHolder &holder, intrusive_container &itree)
      :  m_holder(holder), m_icont(itree)
   {}

   BOOST_CONTAINER_FORCEINLINE static void do_assign(node_ptr_type p, node_t &other, bool_<true>)
   {  p->do_move_assign(other.get_real_data());   }

   BOOST_CONTAINER_FORCEINLINE static void do_assign(node_ptr_type p, const node_t &other, bool_<false>)
   {  p->do_assign(other.get_real_data());   }

   node_ptr_type operator()
      (typename dtl::if_c<DoMove, node_t &, const node_t&>::type other) const
   {
      if(node_ptr_type p = m_icont.unlink_leftmost_without_rebalance()){
         //First recycle a node (this can't throw)
         BOOST_TRY{
            //This can throw
            this->do_assign(p, other, bool_<DoMove>());
            return p;
         }
         BOOST_CATCH(...){
            //If there is an exception destroy the whole source
            m_holder.destroy_node(p);
            while((p = m_icont.unlink_leftmost_without_rebalance())){
               m_holder.destroy_node(p);
            }
            BOOST_RETHROW
         }
         BOOST_CATCH_END
      }
      else{
         return m_holder.create_node(boost::move(other.get_real_data()));
      }
   }

   AllocHolder &m_holder;
   intrusive_container &m_icont;
};


template<class KeyCompare, class KeyOfValue>
struct key_node_compare
   :  public boost::intrusive::detail::ebo_functor_holder<KeyCompare>
{
   BOOST_CONTAINER_FORCEINLINE explicit key_node_compare(const KeyCompare &comp)
      :  base_t(comp)
   {}

   typedef boost::intrusive::detail::ebo_functor_holder<KeyCompare> base_t;
   typedef KeyCompare                  key_compare;
   typedef KeyOfValue                  key_of_value;
   typedef typename KeyOfValue::type   key_type;


   template <class T, class VoidPointer, boost::container::tree_type_enum tree_type_value, bool OptimizeSize>
   BOOST_CONTAINER_FORCEINLINE static const key_type &
      key_from(const base_node<T, intrusive_tree_hook<VoidPointer, tree_type_value, OptimizeSize> > &n)
   {
      return key_of_value()(n.get_data());
   }

   template <class T>
   BOOST_CONTAINER_FORCEINLINE static const T &
      key_from(const T &t)
   {
      return t;
   }

   BOOST_CONTAINER_FORCEINLINE const key_compare &key_comp() const
   {  return static_cast<const key_compare &>(*this);  }

   BOOST_CONTAINER_FORCEINLINE key_compare &key_comp()
   {  return static_cast<key_compare &>(*this);  }

   BOOST_CONTAINER_FORCEINLINE bool operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_comp()(key1, key2);  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const key_type &key1, const U &nonkey2) const
   {  return this->key_comp()(key1, this->key_from(nonkey2));  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const U &nonkey1, const key_type &key2) const
   {  return this->key_comp()(this->key_from(nonkey1), key2);  }

   template<class U, class V>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const U &nonkey1, const V &nonkey2) const
   {  return this->key_comp()(this->key_from(nonkey1), this->key_from(nonkey2));  }
};

template<class Options>
struct get_tree_opt
{
   typedef Options type;
};

template<>
struct get_tree_opt<void>
{
   typedef tree_assoc_defaults type;
};

template<class, class KeyOfValue>
struct real_key_of_value
{
   typedef KeyOfValue type;
};

template<class T>
struct real_key_of_value<T, void>
{
   typedef dtl::identity<T> type;
};

template<class T1, class T2>
struct real_key_of_value<std::pair<T1, T2>, int>
{
   typedef dtl::select1st<T1> type;
};

template<class T1, class T2>
struct real_key_of_value<boost::container::dtl::pair<T1, T2>, int>
{
   typedef dtl::select1st<T1> type;
};

template <class T, class KeyOfValue, class Compare, class Allocator, class Options>
class tree
   : public dtl::node_alloc_holder
      < typename real_allocator<T, Allocator>::type
      , typename dtl::intrusive_tree_type
         < typename real_allocator<T, Allocator>::type
         , tree_value_compare
            <typename allocator_traits<typename real_allocator<T, Allocator>::type>::pointer, Compare, typename real_key_of_value<T, KeyOfValue>::type>
         , get_tree_opt<Options>::type::tree_type
         , get_tree_opt<Options>::type::optimize_size
         >::type
      >
{
   typedef tree < T, KeyOfValue
                , Compare, Allocator, Options>              ThisType;
   public:
   typedef typename real_allocator<T, Allocator>::type      allocator_type;

   private:
   typedef allocator_traits<allocator_type>                 allocator_traits_t;
   typedef typename real_key_of_value<T, KeyOfValue>::type  key_of_value_t;
   typedef tree_value_compare
      < typename allocator_traits_t::pointer
      , Compare
      , key_of_value_t>                                     ValComp;
   typedef typename get_tree_opt<Options>::type             options_type;
   typedef typename dtl::intrusive_tree_type
         < allocator_type, ValComp
         , options_type::tree_type
         , options_type::optimize_size
         >::type                                            Icont;
   typedef dtl::node_alloc_holder
      <allocator_type, Icont>                               AllocHolder;
   typedef typename AllocHolder::NodePtr                    NodePtr;

   typedef typename AllocHolder::NodeAlloc                  NodeAlloc;
   typedef boost::container::
      allocator_traits<NodeAlloc>                           allocator_traits_type;
   typedef typename AllocHolder::ValAlloc                   ValAlloc;
   typedef typename AllocHolder::Node                       Node;
   typedef typename Icont::iterator                         iiterator;
   typedef typename Icont::const_iterator                   iconst_iterator;
   typedef dtl::allocator_node_destroyer<NodeAlloc> Destroyer;
   typedef typename AllocHolder::alloc_version              alloc_version;
   typedef intrusive_tree_proxy<options_type::tree_type>    intrusive_tree_proxy_t;

   BOOST_COPYABLE_AND_MOVABLE(tree)

   public:

   typedef typename key_of_value_t::type                    key_type;
   typedef T                                                value_type;
   typedef Compare                                          key_compare;
   typedef ValComp                                          value_compare;
   typedef typename boost::container::
      allocator_traits<allocator_type>::pointer             pointer;
   typedef typename boost::container::
      allocator_traits<allocator_type>::const_pointer       const_pointer;
   typedef typename boost::container::
      allocator_traits<allocator_type>::reference           reference;
   typedef typename boost::container::
      allocator_traits<allocator_type>::const_reference     const_reference;
   typedef typename boost::container::
      allocator_traits<allocator_type>::size_type           size_type;
   typedef typename boost::container::
      allocator_traits<allocator_type>::difference_type     difference_type;
   typedef dtl::iterator_from_iiterator
      <iiterator, false>                                    iterator;
   typedef dtl::iterator_from_iiterator
      <iiterator, true >                                    const_iterator;
   typedef boost::container::reverse_iterator
      <iterator>                                            reverse_iterator;
   typedef boost::container::reverse_iterator
      <const_iterator>                                      const_reverse_iterator;
   typedef node_handle
      < NodeAlloc, void>                                    node_type;
   typedef insert_return_type_base
      <iterator, node_type>                                 insert_return_type;

   typedef NodeAlloc                                        stored_allocator_type;

   private:

   typedef key_node_compare<key_compare, key_of_value_t>  KeyNodeCompare;

   public:

   BOOST_CONTAINER_FORCEINLINE tree()
      : AllocHolder()
   {}

   BOOST_CONTAINER_FORCEINLINE explicit tree(const key_compare& comp)
      : AllocHolder(ValComp(comp))
   {}

   BOOST_CONTAINER_FORCEINLINE explicit tree(const key_compare& comp, const allocator_type& a)
      : AllocHolder(ValComp(comp), a)
   {}

   BOOST_CONTAINER_FORCEINLINE explicit tree(const allocator_type& a)
      : AllocHolder(a)
   {}

   template <class InputIterator>
   tree(bool unique_insertion, InputIterator first, InputIterator last)
      : AllocHolder(value_compare(key_compare()))
   {
      this->tree_construct(unique_insertion, first, last);
      //AllocHolder clears in case of exception
   }

   template <class InputIterator>
   tree(bool unique_insertion, InputIterator first, InputIterator last, const key_compare& comp)
      : AllocHolder(value_compare(comp))
   {
      this->tree_construct(unique_insertion, first, last);
      //AllocHolder clears in case of exception
   }

   template <class InputIterator>
   tree(bool unique_insertion, InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& a)
      : AllocHolder(value_compare(comp), a)
   {
      this->tree_construct(unique_insertion, first, last);
      //AllocHolder clears in case of exception
   }

   //construct with ordered range
   template <class InputIterator>
   tree( ordered_range_t, InputIterator first, InputIterator last)
      : AllocHolder(value_compare(key_compare()))
   {
      this->tree_construct(ordered_range_t(), first, last);
   }

   template <class InputIterator>
   tree( ordered_range_t, InputIterator first, InputIterator last, const key_compare& comp)
      : AllocHolder(value_compare(comp))
   {
      this->tree_construct(ordered_range_t(), first, last);
   }

   template <class InputIterator>
   tree( ordered_range_t, InputIterator first, InputIterator last
         , const key_compare& comp, const allocator_type& a)
      : AllocHolder(value_compare(comp), a)
   {
      this->tree_construct(ordered_range_t(), first, last);
   }

   private:

   template <class InputIterator>
   void tree_construct(bool unique_insertion, InputIterator first, InputIterator last)
   {
      //Use cend() as hint to achieve linear time for
      //ordered ranges as required by the standard
      //for the constructor
      if(unique_insertion){
         const const_iterator end_it(this->cend());
         for ( ; first != last; ++first){
            this->insert_unique_hint_convertible(end_it, *first);
         }
      }
      else{
         this->tree_construct_non_unique(first, last);
      }
   }

   template <class InputIterator>
   void tree_construct_non_unique(InputIterator first, InputIterator last
      #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename dtl::enable_if_or
         < void
         , dtl::is_same<alloc_version, version_1>
         , dtl::is_input_iterator<InputIterator>
         >::type * = 0
      #endif
         )
   {
      //Use cend() as hint to achieve linear time for
      //ordered ranges as required by the standard
      //for the constructor
      const const_iterator end_it(this->cend());
      for ( ; first != last; ++first){
         this->insert_equal_hint_convertible(end_it, *first);
      }
   }

   template <class InputIterator>
   void tree_construct_non_unique(InputIterator first, InputIterator last
      #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename dtl::disable_if_or
         < void
         , dtl::is_same<alloc_version, version_1>
         , dtl::is_input_iterator<InputIterator>
         >::type * = 0
      #endif
         )
   {
      //Optimized allocation and construction
      this->allocate_many_and_construct
         ( first, boost::container::iterator_udistance(first, last)
         , insert_equal_end_hint_functor<Node, Icont>(this->icont()));
   }

   template <class InputIterator>
   void tree_construct( ordered_range_t, InputIterator first, InputIterator last
         #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename dtl::disable_if_or
         < void
         , dtl::is_same<alloc_version, version_1>
         , dtl::is_input_iterator<InputIterator>
         >::type * = 0
         #endif
         )
   {
      //Optimized allocation and construction
      this->allocate_many_and_construct
         ( first, boost::container::iterator_udistance(first, last)
         , dtl::push_back_functor<Node, Icont>(this->icont()));
      //AllocHolder clears in case of exception
   }

   template <class InputIterator>
   void tree_construct( ordered_range_t, InputIterator first, InputIterator last
         #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename dtl::enable_if_or
         < void
         , dtl::is_same<alloc_version, version_1>
         , dtl::is_input_iterator<InputIterator>
         >::type * = 0
         #endif
         )
   {
      for ( ; first != last; ++first){
         this->push_back_impl(*first);
      }
   }

   public:

   BOOST_CONTAINER_FORCEINLINE tree(const tree& x)
      :  AllocHolder(x, x.value_comp())
   {
      this->icont().clone_from
         (x.icont(), typename AllocHolder::cloner(*this), Destroyer(this->node_alloc()));
   }

   BOOST_CONTAINER_FORCEINLINE tree(BOOST_RV_REF(tree) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      :  AllocHolder(BOOST_MOVE_BASE(AllocHolder, x), x.value_comp())
   {}

   BOOST_CONTAINER_FORCEINLINE tree(const tree& x, const allocator_type &a)
      :  AllocHolder(x.value_comp(), a)
   {
      this->icont().clone_from
         (x.icont(), typename AllocHolder::cloner(*this), Destroyer(this->node_alloc()));
      //AllocHolder clears in case of exception
   }

   tree(BOOST_RV_REF(tree) x, const allocator_type &a)
      :  AllocHolder(x.value_comp(), a)
   {
      if(this->node_alloc() == x.node_alloc()){
         this->icont().swap(x.icont());
      }
      else{
         this->icont().clone_from
            (boost::move(x.icont()), typename AllocHolder::move_cloner(*this), Destroyer(this->node_alloc()));
      }
      //AllocHolder clears in case of exception
   }

   BOOST_CONTAINER_FORCEINLINE ~tree()
   {} //AllocHolder clears the tree

   tree& operator=(BOOST_COPY_ASSIGN_REF(tree) x)
   {
      if (BOOST_LIKELY(this != &x)) {
         NodeAlloc &this_alloc     = this->get_stored_allocator();
         const NodeAlloc &x_alloc  = x.get_stored_allocator();
         dtl::bool_<allocator_traits<NodeAlloc>::
            propagate_on_container_copy_assignment::value> flag;
         if(flag && this_alloc != x_alloc){
            this->clear();
         }
         this->AllocHolder::copy_assign_alloc(x);
         //Transfer all the nodes to a temporary tree
         //If anything goes wrong, all the nodes will be destroyed
         //automatically
         Icont other_tree(::boost::move(this->icont()));

         //Now recreate the source tree reusing nodes stored by other_tree
         this->icont().clone_from
            (x.icont()
            , RecyclingCloner<AllocHolder, false>(*this, other_tree)
            , Destroyer(this->node_alloc()));

         //If there are remaining nodes, destroy them
         NodePtr p;
         while((p = other_tree.unlink_leftmost_without_rebalance())){
            AllocHolder::destroy_node(p);
         }
      }
      return *this;
   }

   tree& operator=(BOOST_RV_REF(tree) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {
      if (BOOST_LIKELY(this != &x)) {
         NodeAlloc &this_alloc = this->node_alloc();
         NodeAlloc &x_alloc    = x.node_alloc();
         const bool propagate_alloc = allocator_traits<NodeAlloc>::
               propagate_on_container_move_assignment::value;
         const bool allocators_equal = this_alloc == x_alloc; (void)allocators_equal;
         //Resources can be transferred if both allocators are
         //going to be equal after this function (either propagated or already equal)
         if(propagate_alloc || allocators_equal){
            //Destroy
            this->clear();
            //Move allocator if needed
            this->AllocHolder::move_assign_alloc(x);
            //Obtain resources
            this->icont() = boost::move(x.icont());
         }
         //Else do a one by one move
         else{
            //Transfer all the nodes to a temporary tree
            //If anything goes wrong, all the nodes will be destroyed
            //automatically
            Icont other_tree(::boost::move(this->icont()));

            //Now recreate the source tree reusing nodes stored by other_tree
            this->icont().clone_from
               (::boost::move(x.icont())
               , RecyclingCloner<AllocHolder, true>(*this, other_tree)
               , Destroyer(this->node_alloc()));

            //If there are remaining nodes, destroy them
            NodePtr p;
            while((p = other_tree.unlink_leftmost_without_rebalance())){
               AllocHolder::destroy_node(p);
            }
         }
      }
      return *this;
   }

   public:
   // accessors:
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      value_compare value_comp() const
   {  return this->icont().value_comp().predicate(); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      key_compare key_comp() const
   {  return this->icont().value_comp().predicate().key_comp(); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      allocator_type get_allocator() const
   {  return allocator_type(this->node_alloc()); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const stored_allocator_type &get_stored_allocator() const
   {  return this->node_alloc(); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      stored_allocator_type &get_stored_allocator()
   {  return this->node_alloc(); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator begin()
   { return iterator(this->icont().begin()); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator begin() const
   {  return this->cbegin();  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator end()
   {  return iterator(this->icont().end());  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator end() const
   {  return this->cend();  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator rbegin() const
   {  return this->crbegin();  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator rend() const
   {  return this->crend();   }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cbegin() const
   { return const_iterator(this->non_const_icont().begin()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cend() const
   { return const_iterator(this->non_const_icont().end()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator crbegin() const
   { return const_reverse_iterator(cend()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator crend() const
   { return const_reverse_iterator(cbegin()); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool empty() const
   {  return !this->size();  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type size() const
   {  return this->icont().size();   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type max_size() const
   {  return AllocHolder::max_size();  }

   BOOST_CONTAINER_FORCEINLINE void swap(ThisType& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value )
   {  AllocHolder::swap(x);   }

   public:

   typedef typename Icont::insert_commit_data insert_commit_data;

   // insert/erase
   std::pair<iterator,bool> insert_unique_check
      (const key_type& key, insert_commit_data &data)
   {
      std::pair<iiterator, bool> ret =
         this->icont().insert_unique_check(key, KeyNodeCompare(key_comp()), data);
      return std::pair<iterator, bool>(iterator(ret.first), ret.second);
   }

   std::pair<iterator,bool> insert_unique_check
      (const_iterator hint, const key_type& key, insert_commit_data &data)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      std::pair<iiterator, bool> ret =
         this->icont().insert_unique_check(hint.get(), key, KeyNodeCompare(key_comp()), data);
      return std::pair<iterator, bool>(iterator(ret.first), ret.second);
   }

   template<class MovableConvertible>
   iterator insert_unique_commit
      (BOOST_FWD_REF(MovableConvertible) v, insert_commit_data &data)
   {
      NodePtr tmp = AllocHolder::create_node(boost::forward<MovableConvertible>(v));
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_unique_commit(*tmp, data));
      destroy_deallocator.release();
      return ret;
   }

   template<class MovableConvertible>
   std::pair<iterator,bool> insert_unique_convertible(BOOST_FWD_REF(MovableConvertible) v)
   {
      insert_commit_data data;
      std::pair<iterator,bool> ret =
         this->insert_unique_check(key_of_value_t()(v), data);
      if(ret.second){
         ret.first = this->insert_unique_commit(boost::forward<MovableConvertible>(v), data);
      }
      return ret;
   }

   template<class MovableConvertible>
   iterator insert_unique_hint_convertible(const_iterator hint, BOOST_FWD_REF(MovableConvertible) v)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      insert_commit_data data;
      std::pair<iterator,bool> ret =
         this->insert_unique_check(hint, key_of_value_t()(v), data);
      if(!ret.second)
         return ret.first;
      return this->insert_unique_commit(boost::forward<MovableConvertible>(v), data);
   }


   private:

   template<class KeyConvertible, class M>
   iiterator priv_insert_or_assign_commit
      (BOOST_FWD_REF(KeyConvertible) key, BOOST_FWD_REF(M) obj, insert_commit_data &data)
   {
      NodePtr tmp = AllocHolder::create_node(boost::forward<KeyConvertible>(key), boost::forward<M>(obj));
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iiterator ret(this->icont().insert_unique_commit(*tmp, data));
      destroy_deallocator.release();
      return ret;
   }

   bool priv_is_linked(const_iterator const position) const
   {
      iiterator const cur(position.get());
      return   cur == this->icont().end() ||
               cur == this->icont().root() ||
               iiterator(cur).go_parent().go_left()  == cur ||
               iiterator(cur).go_parent().go_right() == cur;
   }

   template<class MovableConvertible>
   void push_back_impl(BOOST_FWD_REF(MovableConvertible) v)
   {
      NodePtr tmp(AllocHolder::create_node(boost::forward<MovableConvertible>(v)));
      //push_back has no-throw guarantee so avoid any deallocator/destroyer
      this->icont().push_back(*tmp);
   }

   std::pair<iterator, bool> emplace_unique_node(NodePtr p)
   {
      value_type &v = p->get_data();
      insert_commit_data data;
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(p, this->node_alloc());
      std::pair<iterator,bool> ret =
         this->insert_unique_check(key_of_value_t()(v), data);
      if(!ret.second){
         return ret;
      }
      //No throw insertion part, release rollback
      destroy_deallocator.release();
      return std::pair<iterator,bool>
         ( iterator(this->icont().insert_unique_commit(*p, data))
         , true );
   }

   iterator emplace_hint_unique_node(const_iterator hint, NodePtr p)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      value_type &v = p->get_data();
      insert_commit_data data;
      std::pair<iterator,bool> ret =
         this->insert_unique_check(hint, key_of_value_t()(v), data);
      if(!ret.second){
         //Destroy unneeded node
         Destroyer(this->node_alloc())(p);
         return ret.first;
      }
      return iterator(this->icont().insert_unique_commit(*p, data));
   }

   public:

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> emplace_unique(BOOST_FWD_REF(Args)... args)
   {  return this->emplace_unique_node(AllocHolder::create_node(boost::forward<Args>(args)...));   }

   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint_unique(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {  return this->emplace_hint_unique_node(hint, AllocHolder::create_node(boost::forward<Args>(args)...));   }

   template <class... Args>
   iterator emplace_equal(BOOST_FWD_REF(Args)... args)
   {
      NodePtr tmp(AllocHolder::create_node(boost::forward<Args>(args)...));
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(this->icont().end(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   template <class... Args>
   iterator emplace_hint_equal(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      NodePtr tmp(AllocHolder::create_node(boost::forward<Args>(args)...));
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(hint.get(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   template <class KeyType, class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace
      (const_iterator hint, BOOST_FWD_REF(KeyType) key, BOOST_FWD_REF(Args)... args)
   {
      insert_commit_data data;
      const key_type & k = key;  //Support emulated rvalue references
      std::pair<iiterator, bool> ret =
         hint == const_iterator() ? this->icont().insert_unique_check(            k, KeyNodeCompare(key_comp()), data)
                                  : this->icont().insert_unique_check(hint.get(), k, KeyNodeCompare(key_comp()), data);
      if(ret.second){
         ret.first = this->icont().insert_unique_commit
            (*AllocHolder::create_node(try_emplace_t(), boost::forward<KeyType>(key), boost::forward<Args>(args)...), data);
      }
      return std::pair<iterator, bool>(iterator(ret.first), ret.second);
   }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_TREE_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   std::pair<iterator, bool> emplace_unique(BOOST_MOVE_UREF##N)\
   {  return this->emplace_unique_node(AllocHolder::create_node(BOOST_MOVE_FWD##N));  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_hint_unique(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->emplace_hint_unique_node(hint, AllocHolder::create_node(BOOST_MOVE_FWD##N)); }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_equal(BOOST_MOVE_UREF##N)\
   {\
      NodePtr tmp(AllocHolder::create_node(BOOST_MOVE_FWD##N));\
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());\
      iterator ret(this->icont().insert_equal(this->icont().end(), *tmp));\
      destroy_deallocator.release();\
      return ret;\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_hint_equal(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      BOOST_ASSERT((priv_is_linked)(hint));\
      NodePtr tmp(AllocHolder::create_node(BOOST_MOVE_FWD##N));\
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());\
      iterator ret(this->icont().insert_equal(hint.get(), *tmp));\
      destroy_deallocator.release();\
      return ret;\
   }\
   \
   template <class KeyType BOOST_MOVE_I##N BOOST_MOVE_CLASS##N>\
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool>\
      try_emplace(const_iterator hint, BOOST_FWD_REF(KeyType) key BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      insert_commit_data data;\
      const key_type & k = key;\
      std::pair<iiterator, bool> ret =\
         hint == const_iterator() ? this->icont().insert_unique_check(            k, KeyNodeCompare(key_comp()), data)\
                                  : this->icont().insert_unique_check(hint.get(), k, KeyNodeCompare(key_comp()), data);\
      if(ret.second){\
         ret.first = this->icont().insert_unique_commit\
            (*AllocHolder::create_node(try_emplace_t(), boost::forward<KeyType>(key) BOOST_MOVE_I##N BOOST_MOVE_FWD##N), data);\
      }\
      return std::pair<iterator, bool>(iterator(ret.first), ret.second);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_TREE_EMPLACE_CODE)
   #undef BOOST_CONTAINER_TREE_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert_unique, value_type, iterator, this->insert_unique_hint_convertible, const_iterator, const_iterator)

   template <class InputIterator>
   void insert_unique_range(InputIterator first, InputIterator last)
   {
      for( ; first != last; ++first)
         this->insert_unique_convertible(*first);
   }

   template<class MovableConvertible>
   iterator insert_equal_convertible(BOOST_FWD_REF(MovableConvertible) v)
   {
      NodePtr tmp(AllocHolder::create_node(boost::forward<MovableConvertible>(v)));
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(this->icont().end(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   template<class MovableConvertible>
   iterator insert_equal_hint_convertible(const_iterator hint, BOOST_FWD_REF(MovableConvertible) v)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      NodePtr tmp(AllocHolder::create_node(boost::forward<MovableConvertible>(v)));
      scoped_node_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(hint.get(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG
      (insert_equal, value_type, iterator, this->insert_equal_hint_convertible, const_iterator, const_iterator)

   template <class InputIterator>
   void insert_equal_range(InputIterator first, InputIterator last)
   {
      for( ; first != last; ++first)
         this->insert_equal_convertible(*first);
   }

   template<class KeyType, class M>
   std::pair<iterator, bool> insert_or_assign(const_iterator hint, BOOST_FWD_REF(KeyType) key, BOOST_FWD_REF(M) obj)
   {
      insert_commit_data data;
      const key_type & k = key;  //Support emulated rvalue references
      std::pair<iiterator, bool> ret =
         hint == const_iterator() ? this->icont().insert_unique_check(k, KeyNodeCompare(key_comp()), data)
                                  : this->icont().insert_unique_check(hint.get(), k, KeyNodeCompare(key_comp()), data);
      if(ret.second){
         ret.first = this->priv_insert_or_assign_commit(boost::forward<KeyType>(key), boost::forward<M>(obj), data);
      }
      else{
         ret.first->get_data().second = boost::forward<M>(obj);
      }
      return std::pair<iterator, bool>(iterator(ret.first), ret.second);
   }

   iterator erase(const_iterator position)
   {
      BOOST_ASSERT(position != this->cend() && (priv_is_linked)(position));
      return iterator(this->icont().erase_and_dispose(position.get(), Destroyer(this->node_alloc())));
   }

   BOOST_CONTAINER_FORCEINLINE size_type erase(const key_type& k)
   {  return AllocHolder::erase_key(k, KeyNodeCompare(key_comp()), alloc_version()); }

   size_type erase_unique(const key_type& k)
   {
      iterator i = this->find(k);
      size_type ret = static_cast<size_type>(i != this->end());
      if (ret)
         this->erase(i);
      return ret;
   }

   iterator erase(const_iterator first, const_iterator last)
   {
      BOOST_ASSERT(first == last || (first != this->cend() && (priv_is_linked)(first)));
      BOOST_ASSERT(first == last || (priv_is_linked)(last));
      return iterator(AllocHolder::erase_range(first.get(), last.get(), alloc_version()));
   }

   node_type extract(const key_type& k)
   {
      iterator const it = this->find(k);
      if(this->end() != it){
         return this->extract(it);
      }
      return node_type();
   }

   node_type extract(const_iterator position)
   {
      BOOST_ASSERT(position != this->cend() && (priv_is_linked)(position));
      iiterator const iit(position.get());
      this->icont().erase(iit);
      return node_type(iit.operator->(), this->node_alloc());
   }

   insert_return_type insert_unique_node(BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      return this->insert_unique_node(this->end(), boost::move(nh));
   }

   insert_return_type insert_unique_node(const_iterator hint, BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      insert_return_type irt; //inserted == false, node.empty()
      if(!nh.empty()){
         insert_commit_data data;
         std::pair<iterator,bool> ret =
            this->insert_unique_check(hint, key_of_value_t()(nh.value()), data);
         if(ret.second){
            irt.inserted = true;
            irt.position = iterator(this->icont().insert_unique_commit(*nh.get(), data));
            nh.release();
         }
         else{
            irt.position = ret.first;
            irt.node = boost::move(nh);
         }
      }
      else{
         irt.position = this->end();
      }
      return BOOST_MOVE_RET(insert_return_type, irt);
   }

   iterator insert_equal_node(BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      if(nh.empty()){
         return this->end();
      }
      else{
         NodePtr const p(nh.release());
         return iterator(this->icont().insert_equal(*p));
      }
   }

   iterator insert_equal_node(const_iterator hint, BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      if(nh.empty()){
         return this->end();
      }
      else{
         NodePtr const p(nh.release());
         return iterator(this->icont().insert_equal(hint.get(), *p));
      }
   }

   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge_unique(tree<T, KeyOfValue, C2, Allocator, Options>& source)
   {  return this->icont().merge_unique(source.icont()); }

   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge_equal(tree<T, KeyOfValue, C2, Allocator, Options>& source)
   {  return this->icont().merge_equal(source.icont());  }
   BOOST_CONTAINER_FORCEINLINE void clear()
   {  AllocHolder::clear(alloc_version());  }

   // search operations. Const and non-const overloads even if no iterator is returned
   // so splay implementations can to their rebalancing when searching in non-const versions
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator find(const key_type& k)
   {  return iterator(this->icont().find(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator find(const key_type& k) const
   {  return const_iterator(this->non_const_icont().find(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         find(const K& k)
   {  return iterator(this->icont().find(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         find(const K& k) const
   {  return const_iterator(this->non_const_icont().find(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const key_type& k) const
   {  return size_type(this->icont().count(k, KeyNodeCompare(key_comp()))); }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, size_type>::type
         count(const K& k) const
   {  return size_type(this->icont().count(k, KeyNodeCompare(key_comp()))); }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool contains(const key_type& x) const
   {  return this->find(x) != this->cend();  }

   template<typename K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, bool>::type
         contains(const K& x) const
   {  return this->find(x) != this->cend();  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator lower_bound(const key_type& k)
   {  return iterator(this->icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator lower_bound(const key_type& k) const
   {  return const_iterator(this->non_const_icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         lower_bound(const K& k)
   {  return iterator(this->icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         lower_bound(const K& k) const
   {  return const_iterator(this->non_const_icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator upper_bound(const key_type& k)
   {  return iterator(this->icont().upper_bound(k, KeyNodeCompare(key_comp())));   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator upper_bound(const key_type& k) const
   {  return const_iterator(this->non_const_icont().upper_bound(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         upper_bound(const K& k)
   {  return iterator(this->icont().upper_bound(k, KeyNodeCompare(key_comp())));   }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         upper_bound(const K& k) const
   {  return const_iterator(this->non_const_icont().upper_bound(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<iterator,iterator> equal_range(const key_type& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<iterator,iterator> >::type
         equal_range(const K& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<const_iterator, const_iterator> >::type
         equal_range(const K& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<iterator,iterator> lower_bound_range(const key_type& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<const_iterator, const_iterator> lower_bound_range(const key_type& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<iterator,iterator> >::type
         lower_bound_range(const K& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<const_iterator, const_iterator> >::type
         lower_bound_range(const K& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   BOOST_CONTAINER_FORCEINLINE void rebalance()
   {  intrusive_tree_proxy_t::rebalance(this->icont());   }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator==(const tree& x, const tree& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<(const tree& x, const tree& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator!=(const tree& x, const tree& y)
   {  return !(x == y);  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>(const tree& x, const tree& y)
   {  return y < x;  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<=(const tree& x, const tree& y)
   {  return !(y < x);  }

   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>=(const tree& x, const tree& y)
   {  return !(x < y);  }

   BOOST_CONTAINER_FORCEINLINE friend void swap(tree& x, tree& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value )
   {  x.swap(y);  }
};

} //namespace dtl {
} //namespace container {

template <class T>
struct has_trivial_destructor_after_move;

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class T, class KeyOfValue, class Compare, class Allocator, class Options>
struct has_trivial_destructor_after_move
   < 
      ::boost::container::dtl::tree
         <T, KeyOfValue, Compare, Allocator, Options>
   >
{
   typedef typename ::boost::container::dtl::tree<T, KeyOfValue, Compare, Allocator, Options>::allocator_type allocator_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::pointer pointer;
   static const bool value = ::boost::has_trivial_destructor_after_move<allocator_type>::value &&
                             ::boost::has_trivial_destructor_after_move<pointer>::value &&
                             ::boost::has_trivial_destructor_after_move<Compare>::value;
};

} //namespace boost  {

#include <boost/container/detail/config_end.hpp>

#endif //BOOST_CONTAINER_TREE_HPP

/* tree.hpp
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
*/