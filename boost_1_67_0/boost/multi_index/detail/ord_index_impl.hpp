/* Copyright 2003-2020 Joaquin M Lopez Munoz.
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
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/foreach_fwd.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/move/core.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/multi_index/detail/access_specifier.hpp>
#include <boost/multi_index/detail/adl_swap.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/bidir_node_iterator.hpp>
#include <boost/multi_index/detail/do_not_copy_elements_tag.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/modify_key_adaptor.hpp>
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

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  ,public safe_mode::safe_container<
    ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy> >
#endif

{ 
#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)&&\
    BOOST_WORKAROUND(__MWERKS__,<=0x3003)
/* The "ISO C++ Template Parser" option in CW8.3 has a problem with the
 * lifetime of const references bound to temporaries --precisely what
 * scopeguards are.
 */

#pragma parse_mfunc_templ off
#endif

  typedef typename SuperMeta::type                   super;

protected:
  typedef ordered_index_node<
    AugmentPolicy,typename super::node_type>         node_type;

protected: /* for the benefit of AugmentPolicy::augmented_interface */
  typedef typename node_type::impl_type              node_impl_type;
  typedef typename node_impl_type::pointer           node_impl_pointer;

public:
  /* types */

  typedef typename KeyFromValue::result_type         key_type;
  typedef typename node_type::value_type             value_type;
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
    bidir_node_iterator<node_type>,
    ordered_index_impl>                              iterator;
#else
  typedef bidir_node_iterator<node_type>             iterator;
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
  typedef safe_mode::safe_container<
    ordered_index_impl>                              safe_super;
#endif

  typedef typename call_traits<
    value_type>::param_type                          value_param_type;
  typedef typename call_traits<
    key_type>::param_type                            key_param_type;

  /* Needed to avoid commas in BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL
   * expansion.
   */

  typedef std::pair<iterator,bool>                   emplace_return_type;

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
    return make_iterator(node_from_value<node_type>(boost::addressof(x)));
  }

  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(node_from_value<node_type>(boost::addressof(x)));
  }

  /* capacity */

  bool      empty()const BOOST_NOEXCEPT{return this->final_empty_();}
  size_type size()const BOOST_NOEXCEPT{return this->final_size_();}
  size_type max_size()const BOOST_NOEXCEPT{return this->final_max_size_();}

  /* modifiers */

  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(
    emplace_return_type,emplace,emplace_impl)

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
    node_type* hint=header(); /* end() */
    for(;first!=last;++first){
      hint=this->final_insert_ref_(
        *first,static_cast<final_node_type*>(hint)).first;
      node_type::increment(hint);
    }
  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
  void insert(std::initializer_list<value_type> list)
  {
    insert(list.begin(),list.end());
  }
#endif

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
    std::pair<node_type*,node_type*> p=
      ordered_index_equal_range(root(),header(),key,x,comp_);
    return std::pair<iterator,iterator>(
      make_iterator(p.first),make_iterator(p.second));
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  std::pair<iterator,iterator> equal_range(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    std::pair<node_type*,node_type*> p=
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
  {
    empty_initialize();
  }

  ordered_index_impl(
    const ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x):
    super(x),

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super(),
#endif

    key(x.key),
    comp_(x.comp_)
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

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super(),
#endif

    key(x.key),
    comp_(x.comp_)
  {
    empty_initialize();
  }

  ~ordered_index_impl()
  {
    /* the container is guaranteed to be empty by now */
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  iterator       make_iterator(node_type* node){return iterator(node,this);}
  const_iterator make_iterator(node_type* node)const
    {return const_iterator(node,const_cast<ordered_index_impl*>(this));}
#else
  iterator       make_iterator(node_type* node){return iterator(node);}
  const_iterator make_iterator(node_type* node)const
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

      node_type* root_cpy=map.find(static_cast<final_node_type*>(x.root()));
      header()->parent()=root_cpy->impl();

      node_type* leftmost_cpy=map.find(
        static_cast<final_node_type*>(x.leftmost()));
      header()->left()=leftmost_cpy->impl();

      node_type* rightmost_cpy=map.find(
        static_cast<final_node_type*>(x.rightmost()));
      header()->right()=rightmost_cpy->impl();

      typedef typename copy_map_type::const_iterator copy_map_iterator;
      for(copy_map_iterator it=map.begin(),it_end=map.end();it!=it_end;++it){
        node_type* org=it->first;
        node_type* cpy=it->second;

        cpy->color()=org->color();
        AugmentPolicy::copy(org->impl(),cpy->impl());

        node_impl_pointer parent_org=org->parent();
        if(parent_org==node_impl_pointer(0))cpy->parent()=node_impl_pointer(0);
        else{
          node_type* parent_cpy=map.find(
            static_cast<final_node_type*>(node_type::from_impl(parent_org)));
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
      return static_cast<final_node_type*>(node_type::from_impl(inf.pos));
    }

    final_node_type* res=super::insert_(v,x,variant);
    if(res==x){
      node_impl_type::link(
        static_cast<node_type*>(x)->impl(),inf.side,inf.pos,header()->impl());
    }
    return res;
  }

  template<typename Variant>
  final_node_type* insert_(
    value_param_type v,node_type* position,final_node_type*& x,Variant variant)
  {
    link_info inf;
    if(!hinted_link_point(key(v),position,inf,Category())){
      return static_cast<final_node_type*>(node_type::from_impl(inf.pos));
    }

    final_node_type* res=super::insert_(v,position,x,variant);
    if(res==x){
      node_impl_type::link(
        static_cast<node_type*>(x)->impl(),inf.side,inf.pos,header()->impl());
    }
    return res;
  }

  void erase_(node_type* x)
  {
    node_impl_type::rebalance_for_erase(
      x->impl(),header()->parent(),header()->left(),header()->right());
    super::erase_(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    detach_iterators(x);
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
    safe_super::detach_dereferenceable_iterators();
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
    safe_super::swap(x);
#endif

    super::swap_(x,swap_allocators);
  }

  void swap_elements_(
    ordered_index_impl<
      KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x)
  {
#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
    safe_super::swap(x);
#endif

    super::swap_elements_(x);
  }

  template<typename Variant>
  bool replace_(value_param_type v,node_type* x,Variant variant)
  {
    if(in_place(v,x,Category())){
      return super::replace_(v,x,variant);
    }

    node_type* next=x;
    node_type::increment(next);

    node_impl_type::rebalance_for_erase(
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

  bool modify_(node_type* x)
  {
    bool b;
    BOOST_TRY{
      b=in_place(x->value(),x,Category());
    }
    BOOST_CATCH(...){
      erase_(x);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    if(!b){
      node_impl_type::rebalance_for_erase(
        x->impl(),header()->parent(),header()->left(),header()->right());
      BOOST_TRY{
        link_info inf;
        if(!link_point(key(x->value()),inf,Category())){
          super::erase_(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
          detach_iterators(x);
#endif
          return false;
        }
        node_impl_type::link(x->impl(),inf.side,inf.pos,header()->impl());
      }
      BOOST_CATCH(...){
        super::erase_(x);

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
        detach_iterators(x);
#endif

        BOOST_RETHROW;
      }
      BOOST_CATCH_END
    }

    BOOST_TRY{
      if(!super::modify_(x)){
        node_impl_type::rebalance_for_erase(
          x->impl(),header()->parent(),header()->left(),header()->right());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
        detach_iterators(x);
#endif

        return false;
      }
      else return true;
    }
    BOOST_CATCH(...){
      node_impl_type::rebalance_for_erase(
        x->impl(),header()->parent(),header()->left(),header()->right());

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
      detach_iterators(x);
#endif

      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }

  bool modify_rollback_(node_type* x)
  {
    if(in_place(x->value(),x,Category())){
      return super::modify_rollback_(x);
    }

    node_type* next=x;
    node_type::increment(next);

    node_impl_type::rebalance_for_erase(
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

  bool check_rollback_(node_type* x)const
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
        node_type* x=it.get_node();
        node_type* left_x=node_type::from_impl(x->left());
        node_type* right_x=node_type::from_impl(x->right());

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
  node_type* header()const{return this->final_header();}
  node_type* root()const{return node_type::from_impl(header()->parent());}
  node_type* leftmost()const{return node_type::from_impl(header()->left());}
  node_type* rightmost()const{return node_type::from_impl(header()->right());}

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
    node_type* y=header();
    node_type* x=root();
    bool c=true;
    while(x){
      y=x;
      c=comp_(k,key(x->value()));
      x=node_type::from_impl(c?x->left():x->right());
    }
    node_type* yy=y;
    if(c){
      if(yy==leftmost()){
        inf.side=to_left;
        inf.pos=y->impl();
        return true;
      }
      else node_type::decrement(yy);
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
    node_type* y=header();
    node_type* x=root();
    bool c=true;
    while (x){
     y=x;
     c=comp_(k,key(x->value()));
     x=node_type::from_impl(c?x->left():x->right());
    }
    inf.side=c?to_left:to_right;
    inf.pos=y->impl();
    return true;
  }

  bool lower_link_point(key_param_type k,link_info& inf,ordered_non_unique_tag)
  {
    node_type* y=header();
    node_type* x=root();
    bool c=false;
    while (x){
     y=x;
     c=comp_(key(x->value()),k);
     x=node_type::from_impl(c?x->right():x->left());
    }
    inf.side=c?to_right:to_left;
    inf.pos=y->impl();
    return true;
  }

  bool hinted_link_point(
    key_param_type k,node_type* position,link_info& inf,ordered_unique_tag)
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
      node_type* before=position;
      node_type::decrement(before);
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
    key_param_type k,node_type* position,link_info& inf,ordered_non_unique_tag)
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
      node_type* before=position;
      node_type::decrement(before);
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

  void delete_all_nodes(node_type* x)
  {
    if(!x)return;

    delete_all_nodes(node_type::from_impl(x->left()));
    delete_all_nodes(node_type::from_impl(x->right()));
    this->final_delete_node_(static_cast<final_node_type*>(x));
  }

  bool in_place(value_param_type v,node_type* x,ordered_unique_tag)const
  {
    node_type* y;
    if(x!=leftmost()){
      y=x;
      node_type::decrement(y);
      if(!comp_(key(y->value()),key(v)))return false;
    }

    y=x;
    node_type::increment(y);
    return y==header()||comp_(key(v),key(y->value()));
  }

  bool in_place(value_param_type v,node_type* x,ordered_non_unique_tag)const
  {
    node_type* y;
    if(x!=leftmost()){
      y=x;
      node_type::decrement(y);
      if(comp_(key(v),key(y->value())))return false;
    }

    y=x;
    node_type::increment(y);
    return y==header()||!comp_(key(y->value()),key(v));
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_SAFE_MODE)
  void detach_iterators(node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::detach_equivalent_iterators(it);
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
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(!lower(key(z->value()))){
        z=node_type::from_impl(z->right());
      }
      else if(!upper(key(z->value()))){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else{
        return std::pair<iterator,iterator>(
          make_iterator(
            lower_range(node_type::from_impl(z->left()),z,lower)),
          make_iterator(
            upper_range(node_type::from_impl(z->right()),y,upper)));
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
  node_type * lower_range(node_type* top,node_type* y,LowerBounder lower)const
  {
    while(top){
      if(lower(key(top->value()))){
        y=top;
        top=node_type::from_impl(top->left());
      }
      else top=node_type::from_impl(top->right());
    }

    return y;
  }

  template<typename UpperBounder>
  node_type * upper_range(node_type* top,node_type* y,UpperBounder upper)const
  {
    while(top){
      if(!upper(key(top->value()))){
        y=top;
        top=node_type::from_impl(top->left());
      }
      else top=node_type::from_impl(top->right());
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
    typedef duplicates_iterator<node_type,value_compare> dup_iterator;

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

  void rearranger(node_type* position,node_type *x)
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
    else node_type::increment(position);

    if(position!=x){
      node_impl_type::rebalance_for_erase(
        x->impl(),header()->parent(),header()->left(),header()->right());
      node_impl_type::restore(
        x->impl(),position->impl(),header()->impl());
    }
  }
#endif /* serialization */

protected: /* for the benefit of AugmentPolicy::augmented_interface */
  key_from_value key;
  key_compare    comp_;

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