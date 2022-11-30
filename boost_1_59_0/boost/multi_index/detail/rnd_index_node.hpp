/* Copyright 2003-2021 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_INDEX_NODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_INDEX_NODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/integer/common_factor_rt.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <cstddef>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Allocator>
struct random_access_index_node_impl
{
  typedef typename rebind_alloc_for<
    Allocator,random_access_index_node_impl
  >::type                                             node_allocator;
  typedef allocator_traits<node_allocator>            node_alloc_traits;
  typedef typename node_alloc_traits::pointer         pointer;
  typedef typename node_alloc_traits::const_pointer   const_pointer;
  typedef typename node_alloc_traits::difference_type difference_type;
  typedef typename rebind_alloc_for<
    Allocator,pointer
  >::type                                             ptr_allocator;
  typedef allocator_traits<ptr_allocator>             ptr_alloc_traits;
  typedef typename ptr_alloc_traits::pointer          ptr_pointer;

  ptr_pointer& up(){return up_;}
  ptr_pointer  up()const{return up_;}

  /* interoperability with rnd_node_iterator */

  static void increment(pointer& x)
  {
    x=*(x->up()+1);
  }

  static void decrement(pointer& x)
  {
    x=*(x->up()-1);
  }

  static void advance(pointer& x,difference_type n)
  {
    x=*(x->up()+n);
  }

  static difference_type distance(pointer x,pointer y)
  {
    return static_cast<difference_type>(y->up()-x->up());
  }

  /* algorithmic stuff */

  static void relocate(ptr_pointer pos,ptr_pointer x)
  {
    pointer n=*x;
    if(x<pos){
      extract(x,pos);
      *(pos-1)=n;
      n->up()=pos-1;
    }
    else{
      while(x!=pos){
        *x=*(x-1);
        (*x)->up()=x;
        --x;
      }
      *pos=n;
      n->up()=pos;
    }
  };

  static void relocate(ptr_pointer pos,ptr_pointer first,ptr_pointer last)
  {
    ptr_pointer begin,middle,end;
    if(pos<first){
      begin=pos;
      middle=first;
      end=last;
    }
    else{
      begin=first;
      middle=last;
      end=pos;
    }

    std::ptrdiff_t n=end-begin;
    std::ptrdiff_t m=middle-begin;
    std::ptrdiff_t n_m=n-m;
    std::ptrdiff_t p=integer::gcd(n,m);

    for(std::ptrdiff_t i=0;i<p;++i){
      pointer tmp=begin[i];
      for(std::ptrdiff_t j=i,k;;){
        if(j<n_m)k=j+m;
        else     k=j-n_m;
        if(k==i){
          *(begin+j)=tmp;
          (*(begin+j))->up()=begin+j;
          break;
        }
        else{
          *(begin+j)=*(begin+k);
          (*(begin+j))->up()=begin+j;
        }

        if(k<n_m)j=k+m;
        else     j=k-n_m;
        if(j==i){
          *(begin+k)=tmp;
          (*(begin+k))->up()=begin+k;
          break;
        }
        else{
          *(begin+k)=*(begin+j);
          (*(begin+k))->up()=begin+k;
        }
      }
    }
  };

  static void extract(ptr_pointer x,ptr_pointer pend)
  {
    --pend;
    while(x!=pend){
      *x=*(x+1);
      (*x)->up()=x;
      ++x;
    }
  }

  static void transfer(
    ptr_pointer pbegin0,ptr_pointer pend0,ptr_pointer pbegin1)
  {
    while(pbegin0!=pend0){
      *pbegin1=*pbegin0++;
      (*pbegin1)->up()=pbegin1;
      ++pbegin1;
    }
  }

  static void reverse(ptr_pointer pbegin,ptr_pointer pend)
  {
    std::ptrdiff_t d=(pend-pbegin)/2;
    for(std::ptrdiff_t i=0;i<d;++i){
      std::swap(*pbegin,*--pend);
      (*pbegin)->up()=pbegin;
      (*pend)->up()=pend;
      ++pbegin;
    }
  }

  static ptr_pointer gather_nulls(
    ptr_pointer pbegin,ptr_pointer pend,ptr_pointer x)
  {
    for(ptr_pointer p=pbegin;p!=x;++p){
      if(*p){
        *pbegin=*p;
        (*pbegin)->up()=pbegin;
        ++pbegin;
      }
    }
    for(ptr_pointer p=pend;p!=x;){
      if(*--p){
        *--pend=*p;
        (*pend)->up()=pend;
      }
    }
    return pbegin;
  }

private:
  ptr_pointer up_;
};

template<typename Super>
struct random_access_index_node_trampoline:
  random_access_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  >
{
  typedef random_access_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  > impl_type;
};

template<typename Super>
struct random_access_index_node:
  Super,random_access_index_node_trampoline<Super>
{
private:
  typedef random_access_index_node_trampoline<Super> trampoline;

public:
  typedef typename trampoline::impl_type         impl_type;
  typedef typename trampoline::pointer           impl_pointer;
  typedef typename trampoline::const_pointer     const_impl_pointer;
  typedef typename trampoline::difference_type   difference_type;
  typedef typename trampoline::ptr_pointer       impl_ptr_pointer;

  impl_ptr_pointer& up(){return trampoline::up();}
  impl_ptr_pointer  up()const{return trampoline::up();}

  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }

  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }

  static random_access_index_node* from_impl(impl_pointer x)
  {
    return
      static_cast<random_access_index_node*>(
        static_cast<trampoline*>(
          raw_ptr<impl_type*>(x)));
  }

  static const random_access_index_node* from_impl(const_impl_pointer x)
  {
    return
      static_cast<const random_access_index_node*>(
        static_cast<const trampoline*>(
          raw_ptr<const impl_type*>(x)));
  }

  /* interoperability with rnd_node_iterator */

  static void increment(random_access_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }

  static void decrement(random_access_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }

  static void advance(random_access_index_node*& x,difference_type n)
  {
    impl_pointer xi=x->impl();
    trampoline::advance(xi,n);
    x=from_impl(xi);
  }

  static difference_type distance(
    random_access_index_node* x,random_access_index_node* y)
  {
    return trampoline::distance(x->impl(),y->impl());
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_index_node.hpp
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
*/