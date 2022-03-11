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