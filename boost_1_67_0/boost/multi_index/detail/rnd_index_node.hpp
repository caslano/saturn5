/* Copyright 2003-2018 Joaquin M Lopez Munoz.
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