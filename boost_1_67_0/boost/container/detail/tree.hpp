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

//The node to be store in the tree
template <class T, class VoidPointer, boost::container::tree_type_enum tree_type_value, bool OptimizeSize>
struct tree_node
   :  public intrusive_tree_hook<VoidPointer, tree_type_value, OptimizeSize>::type
{
   public:
   typedef typename intrusive_tree_hook
      <VoidPointer, tree_type_value, OptimizeSize>::type hook_type;
   typedef T value_type;
   typedef typename tree_internal_data_type<T>::type     internal_type;

   typedef tree_node< T, VoidPointer
                    , tree_type_value, OptimizeSize>     node_t;

   typedef typename boost::container::dtl::aligned_storage
      <sizeof(T), boost::container::dtl::alignment_of<T>::value>::type storage_t;
   storage_t m_storage;

   #if defined(BOOST_GCC) && (BOOST_GCC >= 40600) && (BOOST_GCC < 80000)
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wstrict-aliasing"
      #define BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE T &get_data()
   {  return *reinterpret_cast<T*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const T &get_data() const
   {  return *reinterpret_cast<const T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE T *get_data_ptr()
   {  return reinterpret_cast<T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE const T *get_data_ptr() const
   {  return reinterpret_cast<T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE internal_type &get_real_data()
   {  return *reinterpret_cast<internal_type*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const internal_type &get_real_data() const
   {  return *reinterpret_cast<const internal_type*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE internal_type *get_real_data_ptr()
   {  return reinterpret_cast<internal_type*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE const internal_type *get_real_data_ptr() const
   {  return reinterpret_cast<internal_type*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE ~tree_node()
   {  reinterpret_cast<internal_type*>(this->m_storage.data)->~internal_type();  }

   #if defined(BOOST_CONTAINER_DISABLE_ALIASING_WARNING)
      #pragma GCC diagnostic pop
      #undef BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE void destroy_header()
   {  static_cast<hook_type*>(this)->~hook_type();  }

   template<class T1, class T2>
   BOOST_CONTAINER_FORCEINLINE void do_assign(const std::pair<const T1, T2> &p)
   {
      const_cast<T1&>(this->get_real_data().first) = p.first;
      this->get_real_data().second  = p.second;
   }

   template<class T1, class T2>
   BOOST_CONTAINER_FORCEINLINE void do_assign(const pair<const T1, T2> &p)
   {
      const_cast<T1&>(this->get_real_data().first) = p.first;
      this->get_real_data().second  = p.second;
   }

   template<class V>
   BOOST_CONTAINER_FORCEINLINE void do_assign(const V &v)
   {  this->get_real_data() = v; }

   template<class T1, class T2>
   BOOST_CONTAINER_FORCEINLINE void do_move_assign(std::pair<const T1, T2> &p)
   {
      const_cast<T1&>(this->get_real_data().first) = ::boost::move(p.first);
      this->get_real_data().second = ::boost::move(p.second);
   }

   template<class T1, class T2>
   BOOST_CONTAINER_FORCEINLINE void do_move_assign(pair<const T1, T2> &p)
   {
      const_cast<T1&>(this->get_real_data().first) = ::boost::move(p.first);
      this->get_real_data().second  = ::boost::move(p.second);
   }

   template<class V>
   BOOST_CONTAINER_FORCEINLINE void do_move_assign(V &v)
   {  this->get_real_data() = ::boost::move(v); }
};

template <class T, class VoidPointer, boost::container::tree_type_enum tree_type_value, bool OptimizeSize>
struct iiterator_node_value_type< tree_node<T, VoidPointer, tree_type_value, OptimizeSize> > {
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
   typedef typename dtl::tree_node
         < value_type, void_pointer
         , tree_type_value, OptimizeSize>                   node_t;
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

   BOOST_CONTAINER_FORCEINLINE static void do_assign(node_ptr_type &p, const node_t &other, bool_<true>)
   {  p->do_move_assign(const_cast<node_t &>(other).get_real_data());   }

   BOOST_CONTAINER_FORCEINLINE static void do_assign(node_ptr_type &p, const node_t &other, bool_<false>)
   {  p->do_assign(other.get_real_data());   }

   node_ptr_type operator()(const node_t &other) const
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
         return m_holder.create_node(other.get_real_data());
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
      key_from(const tree_node<T, VoidPointer, tree_type_value, OptimizeSize> &n)
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
struct real_key_of_value<boost::container::pair<T1, T2>, int>
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
   typedef dtl::allocator_destroyer<NodeAlloc> Destroyer;
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
            this->insert_unique_convertible(end_it, *first);
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
         this->insert_equal_convertible(end_it, *first);
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
         ( first, boost::container::iterator_distance(first, last)
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
         ( first, boost::container::iterator_distance(first, last)
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
   BOOST_CONTAINER_FORCEINLINE value_compare value_comp() const
   {  return this->icont().value_comp().predicate(); }

   BOOST_CONTAINER_FORCEINLINE key_compare key_comp() const
   {  return this->icont().value_comp().predicate().key_comp(); }

   BOOST_CONTAINER_FORCEINLINE allocator_type get_allocator() const
   {  return allocator_type(this->node_alloc()); }

   BOOST_CONTAINER_FORCEINLINE const stored_allocator_type &get_stored_allocator() const
   {  return this->node_alloc(); }

   BOOST_CONTAINER_FORCEINLINE stored_allocator_type &get_stored_allocator()
   {  return this->node_alloc(); }

   BOOST_CONTAINER_FORCEINLINE iterator begin()
   { return iterator(this->icont().begin()); }

   BOOST_CONTAINER_FORCEINLINE const_iterator begin() const
   {  return this->cbegin();  }

   BOOST_CONTAINER_FORCEINLINE iterator end()
   {  return iterator(this->icont().end());  }

   BOOST_CONTAINER_FORCEINLINE const_iterator end() const
   {  return this->cend();  }

   BOOST_CONTAINER_FORCEINLINE reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator rbegin() const
   {  return this->crbegin();  }

   BOOST_CONTAINER_FORCEINLINE reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator rend() const
   {  return this->crend();   }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_iterator cbegin() const
   { return const_iterator(this->non_const_icont().begin()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_iterator cend() const
   { return const_iterator(this->non_const_icont().end()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator crbegin() const
   { return const_reverse_iterator(cend()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator crend() const
   { return const_reverse_iterator(cbegin()); }

   BOOST_CONTAINER_FORCEINLINE bool empty() const
   {  return !this->size();  }

   BOOST_CONTAINER_FORCEINLINE size_type size() const
   {  return this->icont().size();   }

   BOOST_CONTAINER_FORCEINLINE size_type max_size() const
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
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_unique_commit(*tmp, data));
      destroy_deallocator.release();
      return ret;
   }

   template<class MovableConvertible>
   std::pair<iterator,bool> insert_unique(BOOST_FWD_REF(MovableConvertible) v)
   {
      insert_commit_data data;
      std::pair<iterator,bool> ret =
         this->insert_unique_check(key_of_value_t()(v), data);
      if(ret.second){
         ret.first = this->insert_unique_commit(boost::forward<MovableConvertible>(v), data);
      }
      return ret;
   }

   private:

   template<class KeyConvertible, class M>
   iiterator priv_insert_or_assign_commit
      (BOOST_FWD_REF(KeyConvertible) key, BOOST_FWD_REF(M) obj, insert_commit_data &data)
   {
      NodePtr tmp = AllocHolder::create_node(boost::forward<KeyConvertible>(key), boost::forward<M>(obj));
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
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

   std::pair<iterator, bool> emplace_unique_impl(NodePtr p)
   {
      value_type &v = p->get_data();
      insert_commit_data data;
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(p, this->node_alloc());
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

   iterator emplace_unique_hint_impl(const_iterator hint, NodePtr p)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      value_type &v = p->get_data();
      insert_commit_data data;
      std::pair<iterator,bool> ret =
         this->insert_unique_check(hint, key_of_value_t()(v), data);
      if(!ret.second){
         Destroyer(this->node_alloc())(p);
         return ret.first;
      }
      return iterator(this->icont().insert_unique_commit(*p, data));
   }

   public:

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> emplace_unique(BOOST_FWD_REF(Args)... args)
   {  return this->emplace_unique_impl(AllocHolder::create_node(boost::forward<Args>(args)...));   }

   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint_unique(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {  return this->emplace_unique_hint_impl(hint, AllocHolder::create_node(boost::forward<Args>(args)...));   }

   template <class... Args>
   iterator emplace_equal(BOOST_FWD_REF(Args)... args)
   {
      NodePtr tmp(AllocHolder::create_node(boost::forward<Args>(args)...));
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(this->icont().end(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   template <class... Args>
   iterator emplace_hint_equal(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      NodePtr tmp(AllocHolder::create_node(boost::forward<Args>(args)...));
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
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
   {  return this->emplace_unique_impl(AllocHolder::create_node(BOOST_MOVE_FWD##N));  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_hint_unique(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->emplace_unique_hint_impl(hint, AllocHolder::create_node(BOOST_MOVE_FWD##N)); }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_equal(BOOST_MOVE_UREF##N)\
   {\
      NodePtr tmp(AllocHolder::create_node(BOOST_MOVE_FWD##N));\
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());\
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
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());\
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

   template<class MovableConvertible>
   iterator insert_unique_convertible(const_iterator hint, BOOST_FWD_REF(MovableConvertible) v)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      insert_commit_data data;
      std::pair<iterator,bool> ret =
         this->insert_unique_check(hint, key_of_value_t()(v), data);
      if(!ret.second)
         return ret.first;
      return this->insert_unique_commit(boost::forward<MovableConvertible>(v), data);
   }

   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert_unique, value_type, iterator, this->insert_unique_convertible, const_iterator, const_iterator)

   template <class InputIterator>
   void insert_unique(InputIterator first, InputIterator last)
   {
      for( ; first != last; ++first)
         this->insert_unique(*first);
   }

   iterator insert_equal(const value_type& v)
   {
      NodePtr tmp(AllocHolder::create_node(v));
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(this->icont().end(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   template<class MovableConvertible>
   iterator insert_equal(BOOST_FWD_REF(MovableConvertible) v)
   {
      NodePtr tmp(AllocHolder::create_node(boost::forward<MovableConvertible>(v)));
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(this->icont().end(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   template<class MovableConvertible>
   iterator insert_equal_convertible(const_iterator hint, BOOST_FWD_REF(MovableConvertible) v)
   {
      BOOST_ASSERT((priv_is_linked)(hint));
      NodePtr tmp(AllocHolder::create_node(boost::forward<MovableConvertible>(v)));
      scoped_destroy_deallocator<NodeAlloc> destroy_deallocator(tmp, this->node_alloc());
      iterator ret(this->icont().insert_equal(hint.get(), *tmp));
      destroy_deallocator.release();
      return ret;
   }

   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert_equal, value_type, iterator, this->insert_equal_convertible, const_iterator, const_iterator)

   template <class InputIterator>
   void insert_equal(InputIterator first, InputIterator last)
   {
      for( ; first != last; ++first)
         this->insert_equal(*first);
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
   BOOST_CONTAINER_FORCEINLINE iterator find(const key_type& k)
   {  return iterator(this->icont().find(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_FORCEINLINE const_iterator find(const key_type& k) const
   {  return const_iterator(this->non_const_icont().find(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         find(const K& k)
   {  return iterator(this->icont().find(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         find(const K& k) const
   {  return const_iterator(this->non_const_icont().find(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_FORCEINLINE size_type count(const key_type& k) const
   {  return size_type(this->icont().count(k, KeyNodeCompare(key_comp()))); }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, size_type>::type
         count(const K& k) const
   {  return size_type(this->icont().count(k, KeyNodeCompare(key_comp()))); }

   BOOST_CONTAINER_FORCEINLINE bool contains(const key_type& x) const
   {  return this->find(x) != this->cend();  }

   template<typename K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, bool>::type
         contains(const K& x) const
   {  return this->find(x) != this->cend();  }

   BOOST_CONTAINER_FORCEINLINE iterator lower_bound(const key_type& k)
   {  return iterator(this->icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_FORCEINLINE const_iterator lower_bound(const key_type& k) const
   {  return const_iterator(this->non_const_icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         lower_bound(const K& k)
   {  return iterator(this->icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         lower_bound(const K& k) const
   {  return const_iterator(this->non_const_icont().lower_bound(k, KeyNodeCompare(key_comp())));  }

   BOOST_CONTAINER_FORCEINLINE iterator upper_bound(const key_type& k)
   {  return iterator(this->icont().upper_bound(k, KeyNodeCompare(key_comp())));   }

   BOOST_CONTAINER_FORCEINLINE const_iterator upper_bound(const key_type& k) const
   {  return const_iterator(this->non_const_icont().upper_bound(k, KeyNodeCompare(key_comp())));  }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, iterator>::type
         upper_bound(const K& k)
   {  return iterator(this->icont().upper_bound(k, KeyNodeCompare(key_comp())));   }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, const_iterator>::type
         upper_bound(const K& k) const
   {  return const_iterator(this->non_const_icont().upper_bound(k, KeyNodeCompare(key_comp())));  }

   std::pair<iterator,iterator> equal_range(const key_type& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<iterator,iterator> >::type
         equal_range(const K& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<const_iterator, const_iterator> >::type
         equal_range(const K& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().equal_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   std::pair<iterator,iterator> lower_bound_range(const key_type& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   std::pair<const_iterator, const_iterator> lower_bound_range(const key_type& k) const
   {
      std::pair<iiterator, iiterator> ret =
         this->non_const_icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<const_iterator,const_iterator>
         (const_iterator(ret.first), const_iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
      typename dtl::enable_if_transparent<key_compare, K, std::pair<iterator,iterator> >::type
         lower_bound_range(const K& k)
   {
      std::pair<iiterator, iiterator> ret =
         this->icont().lower_bound_range(k, KeyNodeCompare(key_comp()));
      return std::pair<iterator,iterator>(iterator(ret.first), iterator(ret.second));
   }

   template <class K>
   BOOST_CONTAINER_FORCEINLINE
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

   BOOST_CONTAINER_FORCEINLINE friend bool operator==(const tree& x, const tree& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<(const tree& x, const tree& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!=(const tree& x, const tree& y)
   {  return !(x == y);  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>(const tree& x, const tree& y)
   {  return y < x;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<=(const tree& x, const tree& y)
   {  return !(y < x);  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>=(const tree& x, const tree& y)
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