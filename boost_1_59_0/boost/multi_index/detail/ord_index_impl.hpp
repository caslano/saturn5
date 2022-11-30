/* Copyright 2003-2021 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 *
 * The internal implementation of red-black trees is based on that of SGI STL
 * stl_tree.h file: 
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/call_traits.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/foreach_fwd.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/adl_swap.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/bidir_node_iterator.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/invalidate_iterators.hpp>
#include <boost/multi_index/detail/modify_key_adaptor.hpp>
#include <boost/multi_index/detail/node_handle.hpp>
#include <boost/multi_index/detail/ord_index_node.hpp>
#include <boost/multi_index/detail/ord_index_ops.hpp>
#include <boost/multi_index/detail/safe_mode.hpp>
#include <boost/multi_index/detail/scope_guard.hpp>
#include <boost/multi_index/detail/unbounded.hpp>
#include <boost/multi_index/detail/value_compare.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/multi_index/detail/ord_index_impl_fwd.hpp>
#include <boost/ref.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <utility>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/archive/archive_exception.hpp>
#include <boost/bind/bind.hpp>
#include <boost/multi_index/detail/duplicates_iterator.hpp>
#include <boost/throw_exception.hpp> 
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
#define BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT_OF(x)                    \
  detail::scope_guard BOOST_JOIN(check_invariant_,__LINE__)=                 \
    detail::make_obj_guard(x,&ordered_index_impl::check_invariant_);         \
  BOOST_JOIN(check_invariant_,__LINE__).touch();
#define BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT                          \
  BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT_OF(*this)
#else
#define BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT_OF(x)
#define BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* ordered_index adds a layer of ordered indexing to a given Super and accepts
 * an augmenting policy for optional addition of order statistics.
 */

/* Most of the implementation of unique and non-unique indices is
 * shared. We tell from one another on instantiation time by using
 * these tags.
 */

struct ordered_unique_tag{};
struct ordered_non_unique_tag{};

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4355) /* this used in base member initializer list */
#endif

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
class ordered_index;

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
class ordered_index_impl:
  BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS SuperMeta::type
{ 
#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
/* The "ISO C++ Template Parser" option in CW8.3 has a problem with the
 * lifetime of const references bound to temporaries --precisely what
 * scopeguards are.
 */

#pragma parse_mfunc_templ off
#endif

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
  /* cross-index access */

  template <typename,typename,typename> friend class index_base;
#endif

  typedef typename SuperMeta::type                   super;

protected:
  typedef ordered_index_node<
    AugmentPolicy,typename super::index_node_type>   index_node_type;

protected: /* for the benefit of AugmentPolicy::augmented_interface */
  typedef typename index_node_type::impl_type        node_impl_type;
  typedef typename node_impl_type::pointer           node_impl_pointer;

public:
  /* types */

  typedef typename KeyFromValue::result_type         key_type;
  typedef typename index_node_type::value_type       value_type;
  typedef KeyFromValue                               key_from_value;
  typedef Compare                                    key_compare;
  typedef value_comparison<
    value_type,KeyFromValue,Compare>                 value_compare;
  typedef tuple<key_from_value,key_compare>          ctor_args;
  typedef typename super::final_allocator_type       allocator_type;
  typedef value_type&                                reference;
  typedef const value_type&                          const_reference;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_iterator<
    bidir_node_iterator<index_node_type> >           iterator;
#else
  typedef bidir_node_iterator<index_node_type>       iterator;
#endif

  typedef iterator                                   const_iterator;

private:
  typedef allocator_traits<allocator_type>           alloc_traits;

public:
  typedef typename alloc_traits::size_type           size_type;      
  typedef typename alloc_traits::difference_type     difference_type;
  typedef typename alloc_traits::pointer             pointer;
  typedef typename alloc_traits::const_pointer       const_pointer;
  typedef typename
    boost::reverse_iterator<iterator>                reverse_iterator;
  typedef typename
    boost::reverse_iterator<const_iterator>          const_reverse_iterator;
  typedef typename super::final_node_handle_type     node_type;
  typedef detail::insert_return_type<
    iterator,node_type>                              insert_return_type;
  typedef TagList                                    tag_list;

protected:
  typedef typename super::final_node_type            final_node_type;
  typedef tuples::cons<
    ctor_args, 
    typename super::ctor_args_list>                  ctor_args_list;
  typedef typename mpl::push_front<
    typename super::index_type_list,
    ordered_index<
      KeyFromValue,Compare,
      SuperMeta,TagList,Category,AugmentPolicy
    > >::type                                        index_type_list;
  typedef typename mpl::push_front<
    typename super::iterator_type_list,
    iterator>::type    iterator_type_list;
  typedef typename mpl::push_front<
    typename super::const_iterator_type_list,
    const_iterator>::type                            const_iterator_type_list;
  typedef typename super::copy_map_type              copy_map_type;

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  typedef typename super::index_saver_type           index_saver_type;
  typedef typename super::index_loader_type          index_loader_type;
#endif

protected:
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  typedef safe_mode::safe_container<iterator>        safe_container;
#endif

  typedef typename call_traits<
    value_type>::param_type                          value_param_type;
  typedef typename call_traits<
    key_type>::param_type                            key_param_type;

  /* needed to avoid commas in some macros */

  typedef std::pair<iterator,bool>                   pair_return_type;

public:

  /* construct/copy/destroy
   * Default and copy ctors are in the protected section as indices are
   * not supposed to be created on their own. No range ctor either.
   * Assignment operators defined at ordered_index rather than here.
   */

  allocator_type get_allocator()const BOOST_NOEXCEPT
  {
    return this->final().get_allocator();
  }

  /* iterators */

  iterator
    begin()BOOST_NOEXCEPT{return make_iterator(leftmost());}
  const_iterator
    begin()const BOOST_NOEXCEPT{return make_iterator(leftmost());}
  iterator
    end()BOOST_NOEXCEPT{return make_iterator(header());}
  const_iterator
    end()const BOOST_NOEXCEPT{return make_iterator(header());}
  reverse_iterator
    rbegin()BOOST_NOEXCEPT{return boost::make_reverse_iterator(end());}
  const_reverse_iterator
    rbegin()const BOOST_NOEXCEPT{return boost::make_reverse_iterator(end());}
  reverse_iterator
    rend()BOOST_NOEXCEPT{return boost::make_reverse_iterator(begin());}
  const_reverse_iterator
    rend()const BOOST_NOEXCEPT{return boost::make_reverse_iterator(begin());}
  const_iterator
    cbegin()const BOOST_NOEXCEPT{return begin();}
  const_iterator
    cend()const BOOST_NOEXCEPT{return end();}
  const_reverse_iterator
    crbegin()const BOOST_NOEXCEPT{return rbegin();}
  const_reverse_iterator
    crend()const BOOST_NOEXCEPT{return rend();}
 
  iterator iterator_to(const value_type& x)
  {
    return make_iterator(
      node_from_value<index_node_type>(boost::addressof(x)));
  }

  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(
      node_from_value<index_node_type>(boost::addressof(x)));
  }

  /* capacity */

  bool      empty()const BOOST_NOEXCEPT{return this->final_empty_();}
  size_type size()const BOOST_NOEXCEPT{return this->final_size_();}
  size_type max_size()const BOOST_NOEXCEPT{return this->final_max_size_();}

  /* modifiers */

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(
    pair_return_type,emplace,emplace_impl)

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(
    iterator,emplace_hint,emplace_hint_impl,iterator,position)

  std::pair<iterator,bool> insert(const value_type& x)
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_(x);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  std::pair<iterator,bool> insert(BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_rv_(x);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  iterator insert(iterator position,const value_type& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_(
      x,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }
    
  iterator insert(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_rv_(
      x,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }

  template<typename InputIterator>
  void insert(InputIterator first,InputIterator last)
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    index_node_type* hint=header(); /* end() */
    for(;first!=last;++first){
      hint=this->final_insert_ref_(
        *first,static_cast<final_node_type*>(hint)).first;
      index_node_type::increment(hint);
    }
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  void insert(std::initializer_list<value_type> list)
  {
    insert(list.begin(),list.end());
  }
#endif

  insert_return_type insert(BOOST_RV_REF(node_type) nh)
  {
    if(nh)BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,nh);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_nh_(nh);
    return insert_return_type(make_iterator(p.first),p.second,boost::move(nh));
  }

  iterator insert(const_iterator position,BOOST_RV_REF(node_type) nh)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    if(nh)BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,nh);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=this->final_insert_nh_(
      nh,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }

  node_type extract(const_iterator position)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    return this->final_extract_(
      static_cast<final_node_type*>(position.get_node()));
  }

  node_type extract(key_param_type x)
  {
    iterator position=lower_bound(x);
    if(position==end()||comp_(x,key(*position)))return node_type();
    else return extract(position);
  }

  iterator erase(iterator position)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    this->final_erase_(static_cast<final_node_type*>(position++.get_node()));
    return position;
  }
  
  size_type erase(key_param_type x)
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<iterator,iterator> p=equal_range(x);
    size_type s=0;
    while(p.first!=p.second){
      p.first=erase(p.first);
      ++s;
    }
    return s;
  }

  iterator erase(iterator first,iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,*this);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,*this);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    while(first!=last){
      first=erase(first);
    }
    return first;
  }

  bool replace(iterator position,const value_type& x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    return this->final_replace_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  bool replace(iterator position,BOOST_RV_REF(value_type) x)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    return this->final_replace_rv_(
      x,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier>
  bool modify(iterator position,Modifier mod)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer on safe mode code chokes if this
     * this is not added. Left it for all compilers as it does no
     * harm.
     */

    position.detach();
#endif

    return this->final_modify_(
      mod,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier,typename Rollback>
  bool modify(iterator position,Modifier mod,Rollback back_)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer on safe mode code chokes if this
     * this is not added. Left it for all compilers as it does no
     * harm.
     */

    position.detach();
#endif

    return this->final_modify_(
      mod,back_,static_cast<final_node_type*>(position.get_node()));
  }
  
  template<typename Modifier>
  bool modify_key(iterator position,Modifier mod)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    return modify(
      position,modify_key_adaptor<Modifier,value_type,KeyFromValue>(mod,key));
  }

  template<typename Modifier,typename Rollback>
  bool modify_key(iterator position,Modifier mod,Rollback back_)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    return modify(
      position,
      modify_key_adaptor<Modifier,value_type,KeyFromValue>(mod,key),
      modify_key_adaptor<Rollback,value_type,KeyFromValue>(back_,key));
  }

  void swap(
    ordered_index<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x)
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT_OF(x);
    this->final_swap_(x.final());
  }

  void clear()BOOST_NOEXCEPT
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    this->final_clear_();
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(ordered_index_impl,Index,void)
  merge(Index& x)
  {
    merge(x,x.begin(),x.end());
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(ordered_index_impl,Index,void)
  merge(BOOST_RV_REF(Index) x){merge(static_cast<Index&>(x));}

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(
    ordered_index_impl,Index,pair_return_type)
  merge(Index& x,BOOST_DEDUCED_TYPENAME Index::iterator i)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_DEREFERENCEABLE_ITERATOR(i);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(i,x);
    BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,x);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()==this->header()){ /* same container */
      return std::pair<iterator,bool>(
        make_iterator(static_cast<final_node_type*>(i.get_node())),true);
    }
    else{
      std::pair<final_node_type*,bool> p=this->final_transfer_(
        x,static_cast<final_node_type*>(i.get_node()));
      return std::pair<iterator,bool>(make_iterator(p.first),p.second);
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(
    ordered_index_impl,Index,pair_return_type)
  merge(BOOST_RV_REF(Index) x,BOOST_DEDUCED_TYPENAME Index::iterator i)
  {
    return merge(static_cast<Index&>(x),i);
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(ordered_index_impl,Index,void)
  merge(
    Index& x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(first);
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(last);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(first,x);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(last,x);
    BOOST_MULTI_INDEX_CHECK_VALID_RANGE(first,last);
    BOOST_MULTI_INDEX_CHECK_EQUAL_ALLOCATORS(*this,x);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    if(x.end().get_node()!=this->header()){ /* different containers */
      this->final_transfer_range_(x,first,last);
    }
  }

  template<typename Index>
  BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(ordered_index_impl,Index,void)
  merge(
    BOOST_RV_REF(Index) x,
    BOOST_DEDUCED_TYPENAME Index::iterator first,
    BOOST_DEDUCED_TYPENAME Index::iterator last)
  {
    merge(static_cast<Index&>(x),first,last);
  }

  /* observers */

  key_from_value key_extractor()const{return key;}
  key_compare    key_comp()const{return comp_;}
  value_compare  value_comp()const{return value_compare(key,comp_);}

  /* set operations */

  /* Internally, these ops rely on const_iterator being the same
   * type as iterator.
   */

  template<typename CompatibleKey>
  iterator find(const CompatibleKey& x)const
  {
    return make_iterator(ordered_index_find(root(),header(),key,x,comp_));
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  iterator find(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return make_iterator(ordered_index_find(root(),header(),key,x,comp));
  }

  template<typename CompatibleKey>
  size_type count(const CompatibleKey& x)const
  {
    return count(x,comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  size_type count(const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    std::pair<iterator,iterator> p=equal_range(x,comp);
    size_type n=static_cast<size_type>(std::distance(p.first,p.second));
    return n;
  }

  template<typename CompatibleKey>
  bool contains(const CompatibleKey& x)const
  {
    return contains(x,comp_);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  bool contains(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return find(x,comp)!=end();
  }

  template<typename CompatibleKey>
  iterator lower_bound(const CompatibleKey& x)const
  {
    return make_iterator(
      ordered_index_lower_bound(root(),header(),key,x,comp_));
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  iterator lower_bound(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return make_iterator(
      ordered_index_lower_bound(root(),header(),key,x,comp));
  }

  template<typename CompatibleKey>
  iterator upper_bound(const CompatibleKey& x)const
  {
    return make_iterator(
      ordered_index_upper_bound(root(),header(),key,x,comp_));
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  iterator upper_bound(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return make_iterator(
      ordered_index_upper_bound(root(),header(),key,x,comp));
  }

  template<typename CompatibleKey>
  std::pair<iterator,iterator> equal_range(
    const CompatibleKey& x)const
  {
    std::pair<index_node_type*,index_node_type*> p=
      ordered_index_equal_range(root(),header(),key,x,comp_);
    return std::pair<iterator,iterator>(
      make_iterator(p.first),make_iterator(p.second));
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  std::pair<iterator,iterator> equal_range(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    std::pair<index_node_type*,index_node_type*> p=
      ordered_index_equal_range(root(),header(),key,x,comp);
    return std::pair<iterator,iterator>(
      make_iterator(p.first),make_iterator(p.second));
  }

  /* range */

  template<typename LowerBounder,typename UpperBounder>
  std::pair<iterator,iterator>
  range(LowerBounder lower,UpperBounder upper)const
  {
    typedef typename mpl::if_<
      is_same<LowerBounder,unbounded_type>,
      BOOST_DEDUCED_TYPENAME mpl::if_<
        is_same<UpperBounder,unbounded_type>,
        both_unbounded_tag,
        lower_unbounded_tag
      >::type,
      BOOST_DEDUCED_TYPENAME mpl::if_<
        is_same<UpperBounder,unbounded_type>,
        upper_unbounded_tag,
        none_unbounded_tag
      >::type
    >::type dispatch;

    return range(lower,upper,dispatch());
  }

BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS:
  ordered_index_impl(const ctor_args_list& args_list,const allocator_type& al):
    super(args_list.get_tail(),al),
    key(tuples::get<0>(args_list.get_head())),
    comp_(tuples::get<1>(args_list.get_head()))

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    empty_initialize();
  }

  ordered_index_impl(
    const ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x):
    super(x),
    key(x.key),
    comp_(x.comp_)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    /* Copy ctor just takes the key and compare objects from x. The rest is
     * done in a subsequent call to copy_().
     */
  }

  ordered_index_impl(
     const ordered_index_impl<
       KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
     do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag()),
    key(x.key),
    comp_(x.comp_)

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    ,safe(*this)
#endif

  {
    empty_initialize();
  }

  ~ordered_index_impl()
  {
    /* the container is guaranteed to be empty by now */
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  iterator       make_iterator(index_node_type* node)
    {return iterator(node,&safe);}
  const_iterator make_iterator(index_node_type* node)const
    {return const_iterator(node,const_cast<safe_container*>(&safe));}
#else
  iterator       make_iterator(index_node_type* node){return iterator(node);}
  const_iterator make_iterator(index_node_type* node)const
                   {return const_iterator(node);}
#endif

  void copy_(
    const ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
    const copy_map_type& map)
  {
    if(!x.root()){
      empty_initialize();
    }
    else{
      header()->color()=x.header()->color();
      AugmentPolicy::copy(x.header()->impl(),header()->impl());

      index_node_type* root_cpy=map.find(
        static_cast<final_node_type*>(x.root()));
      header()->parent()=root_cpy->impl();

      index_node_type* leftmost_cpy=map.find(
        static_cast<final_node_type*>(x.leftmost()));
      header()->left()=leftmost_cpy->impl();

      index_node_type* rightmost_cpy=map.find(
        static_cast<final_node_type*>(x.rightmost()));
      header()->right()=rightmost_cpy->impl();

      typedef typename copy_map_type::const_iterator copy_map_iterator;
      for(copy_map_iterator it=map.begin(),it_end=map.end();it!=it_end;++it){
        index_node_type* org=it->first;
        index_node_type* cpy=it->second;

        cpy->color()=org->color();
        AugmentPolicy::copy(org->impl(),cpy->impl());

        node_impl_pointer parent_org=org->parent();
        if(parent_org==node_impl_pointer(0))cpy->parent()=node_impl_pointer(0);
        else{
          index_node_type* parent_cpy=map.find(
            static_cast<final_node_type*>(
              index_node_type::from_impl(parent_org)));
          cpy->parent()=parent_cpy->impl();
          if(parent_org->left()==org->impl()){
            parent_cpy->left()=cpy->impl();
          }
          else if(parent_org->right()==org->impl()){
            /* header() does not satisfy this nor the previous check */
            parent_cpy->right()=cpy->impl();
          }
        }

        if(org->left()==node_impl_pointer(0))
          cpy->left()=node_impl_pointer(0);
        if(org->right()==node_impl_pointer(0))
          cpy->right()=node_impl_pointer(0);
      }
    }
    
    super::copy_(x,map);
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,final_node_type*& x,Variant variant)
  {
    link_info inf;
    if(!link_point(key(v),inf,Category())){
      return static_cast<final_node_type*>(
        index_node_type::from_impl(inf.pos));
    }

    final_node_type* res=super::insert_(v,x,variant);
    if(res==x){
      node_impl_type::link(
        static_cast<index_node_type*>(x)->impl(),
        inf.side,inf.pos,header()->impl());
    }
    return res;
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,index_node_type* position,
    final_node_type*& x,Variant variant)
  {
    link_info inf;
    if(!hinted_link_point(key(v),position,inf,Category())){
      return static_cast<final_node_type*>(
        index_node_type::from_impl(inf.pos));
    }

    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x){
      node_impl_type::link(
        static_cast<index_node_type*>(x)->impl(),
        inf.side,inf.pos,header()->impl());
    }
    return res;
  }

  template<typename Dst>
  void extract_(index_node_type* x,Dst dst)
  {
    node_impl_type::rebalance_for_extract(
      x->impl(),header()->parent(),header()->left(),header()->right());
    super::extract_(x,dst.next());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    transfer_iterators(dst.get(),x);
#endif
  }

  void delete_all_nodes_()
  {
    delete_all_nodes(root());
  }

  void clear_()
  {
    super::clear_();
    empty_initialize();

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.detach_dereferenceable_iterators();
#endif
  }

  template<typename BoolConstant>
  void swap_(
    ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
    BoolConstant swap_allocators)
  {
    adl_swap(key,x.key);
    adl_swap(comp_,x.comp_);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.swap(x.safe);
#endif

    super::swap_(x,swap_allocators);
  }

  void swap_elements_(
    ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x)
  {
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe.swap(x.safe);
#endif

    super::swap_elements_(x);
  }

  template<typename Variant>
  bool replace_(value_param_type v,index_node_type* x,Variant variant)
  {
    if(in_place(v,x,Category())){
      return super::replace_(v,x,variant);
    }

    index_node_type* next=x;
    index_node_type::increment(next);

    node_impl_type::rebalance_for_extract(
      x->impl(),header()->parent(),header()->left(),header()->right());

    BOOST_TRY{
      link_info inf;
      if(link_point(key(v),inf,Category())&&super::replace_(v,x,variant)){
        node_impl_type::link(x->impl(),inf.side,inf.pos,header()->impl());
        return true;
      }
      node_impl_type::restore(x->impl(),next->impl(),header()->impl());
      return false;
    }
    BOOST_CATCH(...){
      node_impl_type::restore(x->impl(),next->impl(),header()->impl());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool modify_(index_node_type* x)
  {
    bool b;
    BOOST_TRY{
      b=in_place(x->value(),x,Category());
    }
    BOOST_CATCH(...){
      extract_(x,invalidate_iterators());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    if(!b){
      node_impl_type::rebalance_for_extract(
        x->impl(),header()->parent(),header()->left(),header()->right());
      BOOST_TRY{
        link_info inf;
        if(!link_point(key(x->value()),inf,Category())){
          super::extract_(x,invalidate_iterators());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
          detach_iterators(x);
#endif
          return false;
        }
        node_impl_type::link(x->impl(),inf.side,inf.pos,header()->impl());
      }
      BOOST_CATCH(...){
        super::extract_(x,invalidate_iterators());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
        detach_iterators(x);
#endif

        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }

    BOOST_TRY{
      if(!super::modify_(x)){
        node_impl_type::rebalance_for_extract(
          x->impl(),header()->parent(),header()->left(),header()->right());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
        detach_iterators(x);
#endif

        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      node_impl_type::rebalance_for_extract(
        x->impl(),header()->parent(),header()->left(),header()->right());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
      detach_iterators(x);
#endif

      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool modify_rollback_(index_node_type* x)
  {
    if(in_place(x->value(),x,Category())){
      return super::modify_rollback_(x);
    }

    index_node_type* next=x;
    index_node_type::increment(next);

    node_impl_type::rebalance_for_extract(
      x->impl(),header()->parent(),header()->left(),header()->right());

    BOOST_TRY{
      link_info inf;
      if(link_point(key(x->value()),inf,Category())&&
         super::modify_rollback_(x)){
        node_impl_type::link(x->impl(),inf.side,inf.pos,header()->impl());
        return true;
      }
      node_impl_type::restore(x->impl(),next->impl(),header()->impl());
      return false;
    }
    BOOST_CATCH(...){
      node_impl_type::restore(x->impl(),next->impl(),header()->impl());
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool check_rollback_(index_node_type* x)const
  {
    return in_place(x->value(),x,Category())&&super::check_rollback_(x);
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* serialization */

  template<typename Archive>
  void save_(
    Archive& ar,const unsigned int version,const index_saver_type& sm)const
  {
    save_(ar,version,sm,Category());
  }

  template<typename Archive>
  void load_(Archive& ar,const unsigned int version,const index_loader_type& lm)
  {
    load_(ar,version,lm,Category());
  }
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const
  {
    if(size()==0||begin()==end()){
      if(size()!=0||begin()!=end()||
         header()->left()!=header()->impl()||
         header()->right()!=header()->impl())return false;
    }
    else{
      if((size_type)std::distance(begin(),end())!=size())return false;

      std::size_t len=node_impl_type::black_count(
        leftmost()->impl(),root()->impl());
      for(const_iterator it=begin(),it_end=end();it!=it_end;++it){
        index_node_type* x=it.get_node();
        index_node_type* left_x=index_node_type::from_impl(x->left());
        index_node_type* right_x=index_node_type::from_impl(x->right());

        if(x->color()==red){
          if((left_x&&left_x->color()==red)||
             (right_x&&right_x->color()==red))return false;
        }
        if(left_x&&comp_(key(x->value()),key(left_x->value())))return false;
        if(right_x&&comp_(key(right_x->value()),key(x->value())))return false;
        if(!left_x&&!right_x&&
           node_impl_type::black_count(x->impl(),root()->impl())!=len)
          return false;
        if(!AugmentPolicy::invariant(x->impl()))return false;
      }
    
      if(leftmost()->impl()!=node_impl_type::minimum(root()->impl()))
        return false;
      if(rightmost()->impl()!=node_impl_type::maximum(root()->impl()))
        return false;
    }

    return super::invariant_();
  }

  
  /* This forwarding function eases things for the boost::mem_fn construct
   * in BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT. Actually,
   * final_check_invariant is already an inherited member function of
   * ordered_index_impl.
   */
  void check_invariant_()const{this->final_check_invariant_();}
#endif

protected: /* for the benefit of AugmentPolicy::augmented_interface */
  index_node_type* header()const
    {return this->final_header();}
  index_node_type* root()const
    {return index_node_type::from_impl(header()->parent());}
  index_node_type* leftmost()const
    {return index_node_type::from_impl(header()->left());}
  index_node_type* rightmost()const
    {return index_node_type::from_impl(header()->right());}

private:
  void empty_initialize()
  {
    header()->color()=red;
    /* used to distinguish header() from root, in iterator.operator++ */
    
    header()->parent()=node_impl_pointer(0);
    header()->left()=header()->impl();
    header()->right()=header()->impl();
  }

  struct link_info
  {
    /* coverity[uninit_ctor]: suppress warning */
    link_info():side(to_left){}

    ordered_index_side side;
    node_impl_pointer  pos;
  };

  bool link_point(key_param_type k,link_info& inf,ordered_unique_tag)
  {
    index_node_type* y=header();
    index_node_type* x=root();
    bool c=true;
    while(x){
      y=x;
      c=comp_(k,key(x->value()));
      x=index_node_type::from_impl(c?x->left():x->right());
    }
    index_node_type* yy=y;
    if(c){
      if(yy==leftmost()){
        inf.side=to_left;
        inf.pos=y->impl();
        return true;
      }
      else index_node_type::decrement(yy);
    }

    if(comp_(key(yy->value()),k)){
      inf.side=c?to_left:to_right;
      inf.pos=y->impl();
      return true;
    }
    else{
      inf.pos=yy->impl();
      return false;
    }
  }

  bool link_point(key_param_type k,link_info& inf,ordered_non_unique_tag)
  {
    index_node_type* y=header();
    index_node_type* x=root();
    bool c=true;
    while (x){
     y=x;
     c=comp_(k,key(x->value()));
     x=index_node_type::from_impl(c?x->left():x->right());
    }
    inf.side=c?to_left:to_right;
    inf.pos=y->impl();
    return true;
  }

  bool lower_link_point(key_param_type k,link_info& inf,ordered_non_unique_tag)
  {
    index_node_type* y=header();
    index_node_type* x=root();
    bool c=false;
    while (x){
     y=x;
     c=comp_(key(x->value()),k);
     x=index_node_type::from_impl(c?x->right():x->left());
    }
    inf.side=c?to_right:to_left;
    inf.pos=y->impl();
    return true;
  }

  bool hinted_link_point(
    key_param_type k,index_node_type* position,
    link_info& inf,ordered_unique_tag)
  {
    if(position->impl()==header()->left()){ 
      if(size()>0&&comp_(k,key(position->value()))){
        inf.side=to_left;
        inf.pos=position->impl();
        return true;
      }
      else return link_point(k,inf,ordered_unique_tag());
    } 
    else if(position==header()){ 
      if(comp_(key(rightmost()->value()),k)){
        inf.side=to_right;
        inf.pos=rightmost()->impl();
        return true;
      }
      else return link_point(k,inf,ordered_unique_tag());
    } 
    else{
      index_node_type* before=position;
      index_node_type::decrement(before);
      if(comp_(key(before->value()),k)&&comp_(k,key(position->value()))){
        if(before->right()==node_impl_pointer(0)){
          inf.side=to_right;
          inf.pos=before->impl();
          return true;
        }
        else{
          inf.side=to_left;
          inf.pos=position->impl();
          return true;
        }
      } 
      else return link_point(k,inf,ordered_unique_tag());
    }
  }

  bool hinted_link_point(
    key_param_type k,index_node_type* position,
    link_info& inf,ordered_non_unique_tag)
  {
    if(position->impl()==header()->left()){ 
      if(size()>0&&!comp_(key(position->value()),k)){
        inf.side=to_left;
        inf.pos=position->impl();
        return true;
      }
      else return lower_link_point(k,inf,ordered_non_unique_tag());
    } 
    else if(position==header()){
      if(!comp_(k,key(rightmost()->value()))){
        inf.side=to_right;
        inf.pos=rightmost()->impl();
        return true;
      }
      else return link_point(k,inf,ordered_non_unique_tag());
    } 
    else{
      index_node_type* before=position;
      index_node_type::decrement(before);
      if(!comp_(k,key(before->value()))){
        if(!comp_(key(position->value()),k)){
          if(before->right()==node_impl_pointer(0)){
            inf.side=to_right;
            inf.pos=before->impl();
            return true;
          }
          else{
            inf.side=to_left;
            inf.pos=position->impl();
            return true;
          }
        }
        else return lower_link_point(k,inf,ordered_non_unique_tag());
      } 
      else return link_point(k,inf,ordered_non_unique_tag());
    }
  }

  void delete_all_nodes(index_node_type* x)
  {
    if(!x)return;

    delete_all_nodes(index_node_type::from_impl(x->left()));
    delete_all_nodes(index_node_type::from_impl(x->right()));
    this->final_delete_node_(static_cast<final_node_type*>(x));
  }

  bool in_place(value_param_type v,index_node_type* x,ordered_unique_tag)const
  {
    index_node_type* y;
    if(x!=leftmost()){
      y=x;
      index_node_type::decrement(y);
      if(!comp_(key(y->value()),key(v)))return false;
    }

    y=x;
    index_node_type::increment(y);
    return y==header()||comp_(key(v),key(y->value()));
  }

  bool in_place(
    value_param_type v,index_node_type* x,ordered_non_unique_tag)const
  {
    index_node_type* y;
    if(x!=leftmost()){
      y=x;
      index_node_type::decrement(y);
      if(comp_(key(v),key(y->value())))return false;
    }

    y=x;
    index_node_type::increment(y);
    return y==header()||!comp_(key(y->value()),key(v));
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  void detach_iterators(index_node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::detach_equivalent_iterators(it);
  }

  template<typename Dst>
  void transfer_iterators(Dst& dst,index_node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::transfer_equivalent_iterators(dst,it);
  }
#endif

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  std::pair<iterator,bool> emplace_impl(BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool>p=
      this->final_emplace_(BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  template<BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  iterator emplace_hint_impl(
    iterator position,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    BOOST_MULTI_INDEX_CHECK_VALID_ITERATOR(position);
    BOOST_MULTI_INDEX_CHECK_IS_OWNER(position,*this);
    BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool>p=
      this->final_emplace_hint_(
        static_cast<final_node_type*>(position.get_node()),
        BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
    return make_iterator(p.first);
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<iterator,iterator>
  range(LowerBounder lower,UpperBounder upper,none_unbounded_tag)const
  {
    index_node_type* y=header();
    index_node_type* z=root();

    while(z){
      if(!lower(key(z->value()))){
        z=index_node_type::from_impl(z->right());
      }
      else if(!upper(key(z->value()))){
        y=z;
        z=index_node_type::from_impl(z->left());
      }
      else{
        return std::pair<iterator,iterator>(
          make_iterator(
            lower_range(index_node_type::from_impl(z->left()),z,lower)),
          make_iterator(
            upper_range(index_node_type::from_impl(z->right()),y,upper)));
      }
    }

    return std::pair<iterator,iterator>(make_iterator(y),make_iterator(y));
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<iterator,iterator>
  range(LowerBounder,UpperBounder upper,lower_unbounded_tag)const
  {
    return std::pair<iterator,iterator>(
      begin(),
      make_iterator(upper_range(root(),header(),upper)));
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<iterator,iterator>
  range(LowerBounder lower,UpperBounder,upper_unbounded_tag)const
  {
    return std::pair<iterator,iterator>(
      make_iterator(lower_range(root(),header(),lower)),
      end());
  }

  template<typename LowerBounder,typename UpperBounder>
  std::pair<iterator,iterator>
  range(LowerBounder,UpperBounder,both_unbounded_tag)const
  {
    return std::pair<iterator,iterator>(begin(),end());
  }

  template<typename LowerBounder>
  index_node_type * lower_range(
    index_node_type* top,index_node_type* y,LowerBounder lower)const
  {
    while(top){
      if(lower(key(top->value()))){
        y=top;
        top=index_node_type::from_impl(top->left());
      }
      else top=index_node_type::from_impl(top->right());
    }

    return y;
  }

  template<typename UpperBounder>
  index_node_type * upper_range(
    index_node_type* top,index_node_type* y,UpperBounder upper)const
  {
    while(top){
      if(!upper(key(top->value()))){
        y=top;
        top=index_node_type::from_impl(top->left());
      }
      else top=index_node_type::from_impl(top->right());
    }

    return y;
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  template<typename Archive>
  void save_(
    Archive& ar,const unsigned int version,const index_saver_type& sm,
    ordered_unique_tag)const
  {
    super::save_(ar,version,sm);
  }

  template<typename Archive>
  void load_(
    Archive& ar,const unsigned int version,const index_loader_type& lm,
    ordered_unique_tag)
  {
    super::load_(ar,version,lm);
  }

  template<typename Archive>
  void save_(
    Archive& ar,const unsigned int version,const index_saver_type& sm,
    ordered_non_unique_tag)const
  {
    typedef duplicates_iterator<index_node_type,value_compare> dup_iterator;

    sm.save(
      dup_iterator(begin().get_node(),end().get_node(),value_comp()),
      dup_iterator(end().get_node(),value_comp()),
      ar,version);
    super::save_(ar,version,sm);
  }

  template<typename Archive>
  void load_(
    Archive& ar,const unsigned int version,const index_loader_type& lm,
    ordered_non_unique_tag)
  {
    lm.load(
      ::boost::bind(
        &ordered_index_impl::rearranger,this,
        ::boost::arg<1>(),::boost::arg<2>()),
      ar,version);
    super::load_(ar,version,lm);
  }

  void rearranger(index_node_type* position,index_node_type *x)
  {
    if(!position||comp_(key(position->value()),key(x->value()))){
      position=lower_bound(key(x->value())).get_node();
    }
    else if(comp_(key(x->value()),key(position->value()))){
      /* inconsistent rearrangement */
      throw_exception(
        archive::archive_exception(
          archive::archive_exception::other_exception));
    }
    else index_node_type::increment(position);

    if(position!=x){
      node_impl_type::rebalance_for_extract(
        x->impl(),header()->parent(),header()->left(),header()->right());
      node_impl_type::restore(
        x->impl(),position->impl(),header()->impl());
    }
  }
#endif /* serialization */

protected: /* for the benefit of AugmentPolicy::augmented_interface */
  key_from_value key;
  key_compare    comp_;

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  safe_container safe;
#endif

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif
};

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
class ordered_index:
  public AugmentPolicy::template augmented_interface<
    ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy
    >
  >::type
{
  typedef typename AugmentPolicy::template
    augmented_interface<
      ordered_index_impl<
        KeyFromValue,Compare,
        SuperMeta,TagList,Category,AugmentPolicy
      >
    >::type                                       super;
public:
  typedef typename super::ctor_args_list          ctor_args_list;
  typedef typename super::allocator_type          allocator_type;
  typedef typename super::iterator                iterator;

  /* construct/copy/destroy
   * Default and copy ctors are in the protected section as indices are
   * not supposed to be created on their own. No range ctor either.
   */

  ordered_index& operator=(const ordered_index& x)
  {
    this->final()=x.final();
    return *this;
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  ordered_index& operator=(
    std::initializer_list<BOOST_DEDUCED_TYPENAME super::value_type> list)
  {
    this->final()=list;
    return *this;
  }
#endif

protected:
  ordered_index(
    const ctor_args_list& args_list,const allocator_type& al):
    super(args_list,al){}

  ordered_index(const ordered_index& x):super(x){}

  ordered_index(const ordered_index& x,do_not_copy_elements_tag):
    super(x,do_not_copy_elements_tag()){}
};

#if defined(BOOST_MSVC)
#pragma warning(pop) /* C4355 */
#endif

/* comparison */

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator==(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator!=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y)
{
  return !(x==y);
}

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y)
{
  return y<x;
}

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y)
{
  return !(x<y);
}

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y)
{
  return !(x>y);
}

/*  specialized algorithms */

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
void swap(
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

/* Boost.Foreach compatibility */

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>*&,
  boost_foreach_argument_dependent_lookup_hack)
{
  return 0;
}

#undef BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT
#undef BOOST_MULTI_INDEX_ORD_INDEX_CHECK_INVARIANT_OF

#endif

/* ord_index_impl.hpp
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
*/