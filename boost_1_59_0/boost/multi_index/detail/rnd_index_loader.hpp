/* Copyright 2003-2022 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_INDEX_LOADER_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_INDEX_LOADER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/noncopyable.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/rnd_index_ptr_array.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* This class implements a serialization rearranger for random access
 * indices. In order to achieve O(n) performance, the following strategy
 * is followed: the nodes of the index are handled as if in a bidirectional
 * list, where the next pointers are stored in the original
 * random_access_index_ptr_array and the prev pointers are stored in
 * an auxiliary array. Rearranging of nodes in such a bidirectional list
 * is constant time. Once all the arrangements are performed (on destruction
 * time) the list is traversed in reverse order and
 * pointers are swapped and set accordingly so that they recover its
 * original semantics ( *(node->up())==node ) while retaining the
 * new order.
 */

template<typename Allocator>
class random_access_index_loader_base:private noncopyable
{
protected:
  typedef random_access_index_node_impl<
    typename rebind_alloc_for<
      Allocator,
      char
    >::type
  >                                                 node_impl_type;
  typedef typename node_impl_type::pointer          node_impl_pointer;
  typedef random_access_index_ptr_array<Allocator>  ptr_array;

  random_access_index_loader_base(const Allocator& al_,ptr_array& ptrs_):
    al(al_),
    ptrs(ptrs_),
    header(*ptrs.end()),
    prev_spc(al,0),
    preprocessed(false)
  {}

  ~random_access_index_loader_base()
  {
    if(preprocessed)
    {
      node_impl_pointer n=header;
      next(n)=n;

      for(size_type i=ptrs.size();i--;){
        n=prev(n);
        size_type d=position(n);
        if(d!=i){
          node_impl_pointer m=prev(next_at(i));
          std::swap(m->up(),n->up());
          next_at(d)=next_at(i);
          std::swap(prev_at(d),prev_at(i));
        }
        next(n)=n;
      }
    }
  }

  void rearrange(node_impl_pointer position_,node_impl_pointer x)
  {
    preprocess(); /* only incur this penalty if rearrange() is ever called */
    if(position_==node_impl_pointer(0))position_=header;
    next(prev(x))=next(x);
    prev(next(x))=prev(x);
    prev(x)=position_;
    next(x)=next(position_);
    next(prev(x))=prev(next(x))=x;
  }

private:
  typedef allocator_traits<Allocator>      alloc_traits;
  typedef typename alloc_traits::size_type size_type;

  void preprocess()
  {
    if(!preprocessed){
      /* get space for the auxiliary prev array */
      auto_space<node_impl_pointer,Allocator> tmp(al,ptrs.size()+1);
      prev_spc.swap(tmp);

      /* prev_spc elements point to the prev nodes */
      std::rotate_copy(
        &*ptrs.begin(),&*ptrs.end(),&*ptrs.end()+1,&*prev_spc.data());

      /* ptrs elements point to the next nodes */
      std::rotate(&*ptrs.begin(),&*ptrs.begin()+1,&*ptrs.end()+1);

      preprocessed=true;
    }
  }

  size_type position(node_impl_pointer x)const
  {
    return (size_type)(x->up()-ptrs.begin());
  }

  node_impl_pointer& next_at(size_type n)const
  {
    return *ptrs.at(n);
  }

  node_impl_pointer& prev_at(size_type n)const
  {
    return *(prev_spc.data()+n);
  }

  node_impl_pointer& next(node_impl_pointer x)const
  {
    return *(x->up());
  }

  node_impl_pointer& prev(node_impl_pointer x)const
  {
    return prev_at(position(x));
  }

  Allocator                               al;
  ptr_array&                              ptrs;
  node_impl_pointer                       header;
  auto_space<node_impl_pointer,Allocator> prev_spc;
  bool                                    preprocessed;
};

template<typename Node,typename Allocator>
class random_access_index_loader:
  private random_access_index_loader_base<Allocator>
{
  typedef random_access_index_loader_base<Allocator> super;
  typedef typename super::node_impl_pointer          node_impl_pointer;
  typedef typename super::ptr_array                  ptr_array;

public:
  random_access_index_loader(const Allocator& al_,ptr_array& ptrs_):
    super(al_,ptrs_)
  {}

  void rearrange(Node* position_,Node *x)
  {
    super::rearrange(
      position_?position_->impl():node_impl_pointer(0),x->impl());
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_index_loader.hpp
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
*/