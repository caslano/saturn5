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