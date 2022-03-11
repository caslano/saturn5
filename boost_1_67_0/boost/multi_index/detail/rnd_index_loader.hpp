/* Copyright 2003-2018 Joaquin M Lopez Munoz.
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
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/rnd_index_ptr_array.hpp>
#include <boost/noncopyable.hpp>

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