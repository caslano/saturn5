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