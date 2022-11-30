/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_SEQ_INDEX_NODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_SEQ_INDEX_NODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* doubly-linked node for use by sequenced_index */

template<typename Allocator>
struct sequenced_index_node_impl
{
  typedef typename rebind_alloc_for<
    Allocator,sequenced_index_node_impl
  >::type                                        node_allocator;
  typedef allocator_traits<node_allocator>       alloc_traits;
  typedef typename alloc_traits::pointer         pointer;
  typedef typename alloc_traits::const_pointer   const_pointer;
  typedef typename alloc_traits::difference_type difference_type;

  pointer& prior(){return prior_;}
  pointer  prior()const{return prior_;}
  pointer& next(){return next_;}
  pointer  next()const{return next_;}

  /* interoperability with bidir_node_iterator */

  static void increment(pointer& x){x=x->next();}
  static void decrement(pointer& x){x=x->prior();}

  /* algorithmic stuff */

  static void link(pointer x,pointer header)
  {
    x->prior()=header->prior();
    x->next()=header;
    x->prior()->next()=x->next()->prior()=x;
  }

  static void unlink(pointer x)
  {
    x->prior()->next()=x->next();
    x->next()->prior()=x->prior();
  }

  static void relink(pointer position,pointer x)
  {
    unlink(x);
    x->prior()=position->prior();
    x->next()=position;
    x->prior()->next()=x->next()->prior()=x;
  }

  static void relink(pointer position,pointer x,pointer y)
  {
    /* position is assumed not to be in [x,y) */

    if(x!=y){
      pointer z=y->prior();
      x->prior()->next()=y;
      y->prior()=x->prior();
      x->prior()=position->prior();
      z->next()=position;
      x->prior()->next()=x;
      z->next()->prior()=z;
    }
  }

  static void reverse(pointer header)
  {
    pointer x=header;
    do{
      pointer y=x->next();
      std::swap(x->prior(),x->next());
      x=y;
    }while(x!=header);
  }

  static void swap(pointer x,pointer y)
  {
    /* This swap function does not exchange the header nodes,
     * but rather their pointers. This is *not* used for implementing
     * sequenced_index::swap.
     */

    if(x->next()!=x){
      if(y->next()!=y){
        std::swap(x->next(),y->next());
        std::swap(x->prior(),y->prior());
        x->next()->prior()=x->prior()->next()=x;
        y->next()->prior()=y->prior()->next()=y;
      }
      else{
        y->next()=x->next();
        y->prior()=x->prior();
        x->next()=x->prior()=x;
        y->next()->prior()=y->prior()->next()=y;
      }
    }
    else if(y->next()!=y){
      x->next()=y->next();
      x->prior()=y->prior();
      y->next()=y->prior()=y;
      x->next()->prior()=x->prior()->next()=x;
    }
  }

private:
  pointer prior_;
  pointer next_;
};

template<typename Super>
struct sequenced_index_node_trampoline:
  sequenced_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  >
{
  typedef sequenced_index_node_impl<
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  > impl_type;
};

template<typename Super>
struct sequenced_index_node:Super,sequenced_index_node_trampoline<Super>
{
private:
  typedef sequenced_index_node_trampoline<Super> trampoline;

public:
  typedef typename trampoline::impl_type       impl_type;
  typedef typename trampoline::pointer         impl_pointer;
  typedef typename trampoline::const_pointer   const_impl_pointer;
  typedef typename trampoline::difference_type difference_type;

  impl_pointer& prior(){return trampoline::prior();}
  impl_pointer  prior()const{return trampoline::prior();}
  impl_pointer& next(){return trampoline::next();}
  impl_pointer  next()const{return trampoline::next();}

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

  static sequenced_index_node* from_impl(impl_pointer x)
  {
    return
      static_cast<sequenced_index_node*>(
        static_cast<trampoline*>(
          raw_ptr<impl_type*>(x)));
  }

  static const sequenced_index_node* from_impl(const_impl_pointer x)
  {
    return
      static_cast<const sequenced_index_node*>(
        static_cast<const trampoline*>(
          raw_ptr<const impl_type*>(x)));
  }

  /* interoperability with bidir_node_iterator */

  static void increment(sequenced_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }

  static void decrement(sequenced_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* seq_index_node.hpp
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
*/