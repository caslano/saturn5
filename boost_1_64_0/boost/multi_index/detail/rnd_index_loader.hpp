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
0cImHNuCzwOPxsUeIEGEab+2nJArgIfB2lnK9H63CtTO4qFfFDPI6fgRJg8On/Y3fYTXhtUczBLkWppz0Bo4GMJ1nbjwEMyQHDKua0ig/5zE9DlDDd3ZWI5WRYAS21ZO5PnBe5Xzg9ksVuayEvncKjHzuQWqmO/0YR0HMUuQ6+hPtJglwcFQbZ30+STIdJ3DjkXAGBENuT3D0RecOVh+JUWAsu/AORgL7WAY5+DoaC/YxVzmCeT1o6IdlIWjHaBlNVMEqDELCwgZCHeKpnEOjnnafy9Qp8g5AneKVtd8rah7UFDFLDfaUTmzBDk+ziekHbSD+zgH3Qacgv3IB1gnWDtsDsyvw2ETs7BtohCgnIsqJeRu4OB+zsHTY1u0Emge81PoFfC75IdwcJCJbBKFAGVfem4CiariIDEjnRHDn3zmr07+8c/t+R6313/d4AEd0jt2aGd3uUiP69JSvW7t6pHEXvwWGl9iEq/UVWmD+X2O7hG+xD58dpLWPjmNbwDyj3bJ7dp36nhtx3bJaYX5afwX00b4qkri8CXkjHKxjeSf/6BVCjiLmqdzZlM4c7OJ0f/K2c233nNz6u2hqaDNPtzmcV4ybwVsShDeUCsG3A01cJelcPcgs1v+lbse/e9NHRiaGlZ1DVHBS7o3y8MmBuEOs2Iab1MNvDkU3nzMRf+Vt0EDevYPTe0KfQ7vJbc3b1DO0CoVGLe2JJDdEKuawz+veSftXYH6WSVw5qHiXNO4l3T7nn0dj/ossHmd3GreXuB3ePMddqfN70gbnuV3u12+tHzf8Cyvv12Bze8czi9tdj+Q3iW5a6dOXZM7Jqdx82qvqlN6lqeQr9F9nvSATbc7hqeBXb6nR9rAqqLuHMB/bN+pHdeqQ2cN0VTUvq4B/Qfeatap+NME0hbGrFztnP/Qr8cItJCdCczjqbjrcdzGTjTEOjkL+Jvg3uiQ6kSWJJARWgwISc1wKm17OCsCe9qN/62CNu8iNLQ6Zfvdro6hUqhqvVmWQK6Ed/QAI2RhnYGVAh3BZpra3WaEdpdrK7C7HN5OOb7QaFU1V+L2pxbolKf5F3e2GxzI2jjQpFP89JDrxNtcVm5eaNSB+MwE0omINudS2txINhn0ieefFm2u/MR+0jWk+rhc+YWukChDidbgEkhT0CVf0WUUKwZdKojQJZfrkh9iXXy5odOleHkCaQa6FCi6jP6bLlauyxsh18UbMl3KeBvLBV3cii5j2HbQpQza2Diuy+ch1YXnGrU7h4dEmcB4ujiBFII+HkWfsVKf/aDPdK5PPA2xPl5Hfij1STb0mwcVfR5ic0xtrZTrc1uo9QlVYwu8H9532oA+XkWfh9l0gz4alLplF3kopPrYXC53lq19l9BoVGUL5vG5DujjU/QZJ8fRStDHw/VZHFJ9+Hjj8+eFRpt/myePF+tZ0Kea9i6ntAnxGJqjeYHceU5HSFSqam+8/1wFc4JCbf/9hR1Q6UdYRiBvQKSYE5Q/G+o5AdfH69AWNyHTp5zP2w6CPsO5Pnm/9AWf2ARWAm2rHPLbF+1E0MdX6AmZQoF1I9epLug0Qjt/0fMZmLdNZL1BpxKYtw0J+bwtK9eRlZeVnRMajaimx+4EUh30KdLy+LwcDb7bR+U7KoJ3VBr6d1Ro89pD+pqC24XH/mYXpobcLrjcNnvIXpFoc58myL2mUcpe0yQWWJH2hnd0LOTvyD6S5410+bSlamhekZhj70ggLUGn0VynC2XZiwKZUeqa9hA9W3eFWKdC/is8uZmfr7yd7oLQaAX7w9v1dzVGucPhcWbV9QJ/Sqj1snlzhvNThPbQjUkpvO2lgD5juT5PPnfeK2r8hPDpw353I60=
*/