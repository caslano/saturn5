/* Copyright 2003-2014 Joaquin M Lopez Munoz.
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

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_OPS_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_OPS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/and.hpp>
#include <boost/multi_index/detail/promotes_arg.hpp>
#include <utility>

namespace boost{

namespace multi_index{

namespace detail{

/* Common code for index memfuns having templatized and
 * non-templatized versions.
 * Implementation note: When CompatibleKey is consistently promoted to
 * KeyFromValue::result_type for comparison, the promotion is made once in
 * advance to increase efficiency.
 */

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_find(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ordered_index_find(
    top,y,key,x,comp,
    mpl::and_<
      promotes_1st_arg<CompatibleCompare,CompatibleKey,key_type>,
      promotes_2nd_arg<CompatibleCompare,key_type,CompatibleKey> >());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline Node* ordered_index_find(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ordered_index_find(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_find(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  Node* y0=y;

  while (top){
    if(!comp(key(top->value()),x)){
      y=top;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }
    
  return (y==y0||comp(x,key(y->value())))?y0:y;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_lower_bound(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ordered_index_lower_bound(
    top,y,key,x,comp,
    promotes_2nd_arg<CompatibleCompare,key_type,CompatibleKey>());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline Node* ordered_index_lower_bound(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ordered_index_lower_bound(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_lower_bound(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  while(top){
    if(!comp(key(top->value()),x)){
      y=top;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }

  return y;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_upper_bound(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ordered_index_upper_bound(
    top,y,key,x,comp,
    promotes_1st_arg<CompatibleCompare,CompatibleKey,key_type>());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline Node* ordered_index_upper_bound(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ordered_index_upper_bound(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_upper_bound(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  while(top){
    if(comp(x,key(top->value()))){
      y=top;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }

  return y;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline std::pair<Node*,Node*> ordered_index_equal_range(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ordered_index_equal_range(
    top,y,key,x,comp,
    mpl::and_<
      promotes_1st_arg<CompatibleCompare,CompatibleKey,key_type>,
      promotes_2nd_arg<CompatibleCompare,key_type,CompatibleKey> >());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline std::pair<Node*,Node*> ordered_index_equal_range(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ordered_index_equal_range(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline std::pair<Node*,Node*> ordered_index_equal_range(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  while(top){
    if(comp(key(top->value()),x)){
      top=Node::from_impl(top->right());
    }
    else if(comp(x,key(top->value()))){
      y=top;
      top=Node::from_impl(top->left());
    }
    else{
      return std::pair<Node*,Node*>(
        ordered_index_lower_bound(
          Node::from_impl(top->left()),top,key,x,comp,mpl::false_()),
        ordered_index_upper_bound(
          Node::from_impl(top->right()),y,key,x,comp,mpl::false_()));
    }
  }

  return std::pair<Node*,Node*>(y,y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_ops.hpp
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
*/