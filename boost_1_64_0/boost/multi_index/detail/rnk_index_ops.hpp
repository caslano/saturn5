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
eV1QFzIvmOG60cTEUXnMkTao6LQP6AeySGmZyHId/3s7xuAxixjLbNHA49nQnsfUfMhoXHfJcjGzjnx0DXked2+hZF4ww3UHWVqYYb0mC4QZzpPJMsEM51msvABjv5P5w/TxiRPJdZGmq0vQCffpQk+4Ly/MJM8oskCYIT4Tc5FlguljFyfdW8hJFUMGQwxhZF4ww3UxWVqYPoZoskCY4bxc1kWa/ryOlecn9x3FmCfzZja4+K0oxHfKImoxW3Q13UTU02Ddd94fjHFN5sNsvuaYivYkKyUtHVnnusvGod9PyxikNShx8zvajCwvs4CAG+Wx1pF5MyueP2wI+pbsoKasU8p33dAuZ+X7YNLOBJ4OQDqXRcy0KLvW7J8OSHfBIioKZcem+6jfll2U7x5IC+z9KBZ5ks1h9vTQBifa85LsW2l382S/g/jIKjM7NaSBWrPIGjEL+6NAfeR52SLyM5vWbbL63S6Zi1nzud5lMZauWEQVZp927N6PteeqRYQy23lz0UeUR9aEWejPvIXQ71f19TwbkXU62uyaRQxmVnfxxydoa7LUMMM9q+tyXEvTvWt73X26EDI/mOE3MWSVpKU1/JYtjuyytDRk/wzOo37Te8MipjLbWn+LevfgpkX0YlaybeIG1POWRcQxC/7nCuZRIlkHZqmCR6rnQLctIj2zQ1ei+mK8kI1glnvno1do6zsWsZfZ2U3eMWiXBIuweiZbarLLD/LcQQyPqDxLsvlaqG5tX1XBvH0q+0Ga7hyTzOWdbKnI2uSfjfcZxCeLKGBXFrQ3aiVMs4qCzD41Dq4L87KKLh7JlpIs9vXW54g9lVV81pItBVnNgoPyoq3TWNHvPmSHU/64jHoa7K9P0WjPMLLezIZF5K6KPjKku5xvQ3aUl9Yq6jDbd7XNLLRnWvd1iTXYotDU6l6QwbynBGEsJZBlYVajbfkxqEs6q/BmtuHuxhD0H1kGZu0btlPntGSlmF0/+kFdT5M1YTbx/YwOav8eq6jHrNDPQpEYu2R2ZscHfJyBdiGbxKx5Xss41CW9Vaxh1uBdg5qIwd8qCjML6Hwf4zrcXx9Duw+f1L53ZA5mvcOOqGt0E3ORFWJ252IXK9o6g1XU9FA2f9GpBMSexSomWpTVbTXrLfo9yCp2MxtkL7EYeea0ivSaslQLfvkbeQZbk9dradWtq/xRT7JUzN4euqjewSIrwKxtVF6MpZBcVryL4002NPU8tS8AWSCzpj+aHcSYMEkXT5ad2fugSidRF7I6Hsp8d8Q1QHkF3KeLIXvHbMboQy9QXkGrCGDWf/O+M5grZLmYTe4VmAdtXciK3797kYWk2h+NupCVZRa48+MyjCWylJqy5juH1kaeIVbRVigL33v/D8RA1tFLWXWfh79gTJSTY1faVp8t7dBmZC5W3tr52WphroRaxW27ssLX56rfltW0ikFWZXOH/lEA86+2VcxjeQ5vYD2MeoZZk89DpGXccOca6kJWjVlan79TYv2saxWbZJ5OsqqBdVNh7Na3it+Z5Vxy2A9t1tAqPLmNy1cC/dDIKp4KZVtEL1hMYznmpTXdGDkBfURWhFl8lUiBGMjqMms0v0JHlNfEKh4xK//pUALarKlV/MPsuPN2CPqhGcXHLGRi0Dz0LVlDZrPqVb+L2P+U80ja9D7tLiJPsg/SHGSj+hcsiLo0t4rMzFrMCzyH2JvLvpXmN/iA2qOgJY0Xi7KxRw6MR+wR1uTzM2nrgiPw3oVoQ2uPTGdPup+Vc0hazLF21Eeasjff+qkx0VHNabvh90fRZAM1ZXHd+yL28M5W8cVT2ZUsHY+gvB5W8YblOXbmqES0Zy+rGMuslnfNXoidrDo=
*/