/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RNK_INDEX_OPS_HPP
#define BOOST_MULTI_INDEX_DETAIL_RNK_INDEX_OPS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/core/pointer_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/multi_index/detail/promotes_arg.hpp>
#include <utility>

namespace boost{

namespace multi_index{

namespace detail{

/* Common code for ranked_index memfuns having templatized and
 * non-templatized versions.
 */

template<typename Pointer>
struct ranked_node_size_type
{
  typedef typename boost::pointer_traits<Pointer>::
    element_type::size_type type;
};

template<typename Pointer>
inline typename ranked_node_size_type<Pointer>::type
ranked_node_size(Pointer x)
{
  return x!=Pointer(0)?x->size:0;
}

template<typename Pointer>
inline Pointer ranked_index_nth(
  BOOST_DEDUCED_TYPENAME ranked_node_size_type<Pointer>::type n,Pointer end_)
{
  typedef typename ranked_node_size_type<Pointer>::type size_type;

  Pointer top=end_->parent();
  if(top==Pointer(0)||n>=top->size)return end_;

  for(;;){
    size_type s=ranked_node_size(top->left());
    if(n==s)return top;
    if(n<s)top=top->left();
    else{
      top=top->right();
      n-=s+1;
    }
  }
}

template<typename Pointer>
inline typename ranked_node_size_type<Pointer>::type
ranked_index_rank(Pointer x,Pointer end_)
{
  typedef typename ranked_node_size_type<Pointer>::type size_type;

  Pointer top=end_->parent();
  if(top==Pointer(0))return 0;
  if(x==end_)return top->size;

  size_type s=ranked_node_size(x->left());
  while(x!=top){
    Pointer z=x->parent();
    if(x==z->right()){
      s+=ranked_node_size(z->left())+1;
    }
    x=z;
  }
  return s;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline typename Node::size_type ranked_index_find_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ranked_index_find_rank(
    top,y,key,x,comp,
    mpl::and_<
      promotes_1st_arg<CompatibleCompare,CompatibleKey,key_type>,
      promotes_2nd_arg<CompatibleCompare,key_type,CompatibleKey> >());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline typename Node::size_type ranked_index_find_rank(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ranked_index_find_rank(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline typename Node::size_type ranked_index_find_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  typedef typename Node::size_type size_type;

  if(!top)return 0;

  size_type s=top->impl()->size,
            s0=s;
  Node*     y0=y;

  do{
    if(!comp(key(top->value()),x)){
      y=top;
      s-=ranked_node_size(y->right())+1;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }while(top);
    
  return (y==y0||comp(x,key(y->value())))?s0:s;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline typename Node::size_type ranked_index_lower_bound_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ranked_index_lower_bound_rank(
    top,y,key,x,comp,
    promotes_2nd_arg<CompatibleCompare,key_type,CompatibleKey>());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline typename Node::size_type ranked_index_lower_bound_rank(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ranked_index_lower_bound_rank(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline typename Node::size_type ranked_index_lower_bound_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  typedef typename Node::size_type size_type;

  if(!top)return 0;

  size_type s=top->impl()->size;

  do{
    if(!comp(key(top->value()),x)){
      y=top;
      s-=ranked_node_size(y->right())+1;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }while(top);

  return s;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline typename Node::size_type ranked_index_upper_bound_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ranked_index_upper_bound_rank(
    top,y,key,x,comp,
    promotes_1st_arg<CompatibleCompare,CompatibleKey,key_type>());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline typename Node::size_type ranked_index_upper_bound_rank(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ranked_index_upper_bound_rank(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline typename Node::size_type ranked_index_upper_bound_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  typedef typename Node::size_type size_type;

  if(!top)return 0;

  size_type s=top->impl()->size;

  do{
    if(comp(x,key(top->value()))){
      y=top;
      s-=ranked_node_size(y->right())+1;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }while(top);

  return s;
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline std::pair<typename Node::size_type,typename Node::size_type>
ranked_index_equal_range_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  typedef typename KeyFromValue::result_type key_type;

  return ranked_index_equal_range_rank(
    top,y,key,x,comp,
    mpl::and_<
      promotes_1st_arg<CompatibleCompare,CompatibleKey,key_type>,
      promotes_2nd_arg<CompatibleCompare,key_type,CompatibleKey> >());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleCompare
>
inline std::pair<typename Node::size_type,typename Node::size_type>
ranked_index_equal_range_rank(
  Node* top,Node* y,const KeyFromValue& key,
  const BOOST_DEDUCED_TYPENAME KeyFromValue::result_type& x,
  const CompatibleCompare& comp,mpl::true_)
{
  return ranked_index_equal_range_rank(top,y,key,x,comp,mpl::false_());
}

template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline std::pair<typename Node::size_type,typename Node::size_type>
ranked_index_equal_range_rank(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp,mpl::false_)
{
  typedef typename Node::size_type size_type;

  if(!top)return std::pair<size_type,size_type>(0,0);

  size_type s=top->impl()->size;

  do{
    if(comp(key(top->value()),x)){
      top=Node::from_impl(top->right());
    }
    else if(comp(x,key(top->value()))){
      y=top;
      s-=ranked_node_size(y->right())+1;
      top=Node::from_impl(top->left());
    }
    else{
      return std::pair<size_type,size_type>(
        s-top->impl()->size+
          ranked_index_lower_bound_rank(
           Node::from_impl(top->left()),top,key,x,comp,mpl::false_()),
        s-ranked_node_size(top->right())+
          ranked_index_upper_bound_rank(
            Node::from_impl(top->right()),y,key,x,comp,mpl::false_()));
    }
  }while(top);

  return std::pair<size_type,size_type>(s,s);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnk_index_ops.hpp
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
*/