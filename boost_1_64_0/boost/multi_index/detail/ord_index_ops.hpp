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
8yvmuAj1c/iQ8kMqAtTx4IhVzpGWK3OkTTK3h5WJ/YWlqPsLooqIMyRFgOJf2WQlY4GDFRoHO/s2gtZPz8NPlfXFmFgWDlvgKEC6xlkRoM6P1ljJj8DBSv6g/s6Obwt0C+0OMamp0aIvVGKe3xJVRIxDUwSo8YgrreQF4GAVf+A+fTZNoFtlTGpZhODAejYMHNiR50Z2+yXez7pN5oPUeGiqzZHDoX8Wsv5ZprnhMitpBe9/DX8w/sJzNwkNt9M2cWARosR42HB9GMZDmx9rp1ERoOSPX2CV9yisVe5R2EFXNoUVUzVC6mg2IywcoJ1kVSQo84J3rMQOHKzT7p6M7QKx2Tvp0ihYL0M+h6kfovYDW5b2D5olhOLN4+GbVtIG9F+v7bftG5Yp0F20HPxHvaPEXf4lqH52UUHMrC6KCHMuyDl6X9jAH/QfHDscRgE6x5Dzq5H2uRxz30VUEvNUsyLCzMMzVpIHMeob+YPILyIgAusTOpHp59e0aUJROuLdIlm5Nv4ffCDOEMxizHMlt5XsbCT4+Ig/uKf563C29VO6nUILgXj1yajxCDafn7u7fGjHOhUB6lzJaZXnuD7mD4p/WnJCoLvlWbbpTHBQFgYO3Nl4YQlmCdJOplhJWXXBwSb+IOvqGb8LLffQjHhYP0K8eiVmvHpVDRFDtU3ly35wg5XUB7ugxapW2H/sKTT8TJ7xJtAGMl4Mg/5ZWG4kWb46X+xqJRY4r7CFP9h7OOlroeFe2hL6AAE7UBIG/bPQ+4CUoNuBLlbSGsbIrVruq4WHICJvH51IoQ/A71buwJwr8JHL5XJys53vcvHOitYUTGLMcyfORyCn/Db+4PoR8+YFItTs0CYq4Henh4+PfKcPzTaY5ajnGDpbSWfgQxsb99z79Bmh8edyDy4Xfnd/+PhANBUmMeb1FeejHfCxgz/oNuAU3E/1BZ1p6i+Td4aNjyw/ltfNLMY8t+yk87FT4eNL2tcCa2743ZIw8hEe+yHEKPHenI/A3V27tHyaY1u0EugBOsbUXzaHkY/MsJgPIUaxp6eiyS3AR5nmj7jSD2eBDtKZ8dA+IsXaozfq2gMqKn/A5gN+MMfAHY8mTuDjE/6gxvtHVgr0KzoH/LTxcN/p5qWIvonMwuxsh1d8INkORYQ5poHzENi3+FTZt/j6b/cYJUcgxnbISiIGf6ky1L3cQ9HkAszBd1NuNe9qCH77chobCUrzzxiNhyltEHko4P+lF13bsT1ShKwiQF2LHogm6RAfv4d/Zt+wfZRAv6F7AvHxUZB/cxlmn6iq4gi3F8lvLcu/VL/9t7QhzDmPUeG33ozpsxX183lRW4AoXplTfRJN6kP+gL38wQxv2wECPUS7Bebc4K8tW47+/n0PepHc9qby5ZxhSzT5FmzAPv5gwuOrIJbhMD1jgfcfKfQvXhEO/ZHVN88h10WTZ6D/79fiGD7dM06gR6gdxsTe0P+tK/H1z3Vm4zYAIUDhgKyIJr1gPPxcOyuROwFOhh2lY2AcKAMO9uNz4HVkoRoBWb6cF5VGy3vMvuAPxlxfG/buvqNJVoh5BRtQsgpff1sB6hggy5exrm9Ekw2g/5f8waeHjjcIWP490bBuqCb0j1+Nrr/H6yxA7QMgQO0DT0eTccDBAW2/5vhuuJHje9od9m9L4gQHRWHhACvCUxGgxjzfFy33rA4q+7fH6f4a0CJqCw56r0HnoMDpQ20GsnyZO6RtNGkB+We/olyvqzMfERqeoMVgESfXgzsd16Lrn1+IdDxIFm8eC6+KJoNgLPyaf9ax9mou0JPSJ50UAXcZhkF/rPMPsnhzPFuTaLIK2n+5lod64J+bBPoD3Qx2MDEGzsI=
*/