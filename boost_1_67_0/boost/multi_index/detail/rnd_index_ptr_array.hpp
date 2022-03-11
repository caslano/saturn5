/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_INDEX_PTR_ARRAY_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_INDEX_PTR_ARRAY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/rnd_index_node.hpp>
#include <boost/noncopyable.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* pointer structure for use by random access indices */

template<typename Allocator>
class random_access_index_ptr_array:private noncopyable
{
  typedef random_access_index_node_impl<
    typename rebind_alloc_for<
      Allocator,
      char
    >::type
  >                                         node_impl_type;

public:
  typedef typename node_impl_type::pointer  value_type;
  typedef typename rebind_alloc_for<
    Allocator,value_type
  >::type                                   value_allocator;
  typedef allocator_traits<value_allocator> alloc_traits;
  typedef typename alloc_traits::pointer    pointer;
  typedef typename alloc_traits::size_type  size_type;

  random_access_index_ptr_array(
    const Allocator& al,value_type end_,size_type sz):
    size_(sz),
    capacity_(sz),
    spc(al,capacity_+1)
  {
    *end()=end_;
    end_->up()=end();
  }

  size_type size()const{return size_;}
  size_type capacity()const{return capacity_;}

  void room_for_one()
  {
    if(size_==capacity_){
      reserve(capacity_<=10?15:capacity_+capacity_/2);
    }
  }

  void reserve(size_type c)
  {
    if(c>capacity_)set_capacity(c);
  }

  void shrink_to_fit()
  {
    if(capacity_>size_)set_capacity(size_);
  }

  pointer begin()const{return ptrs();}
  pointer end()const{return ptrs()+size_;}
  pointer at(size_type n)const{return ptrs()+n;}

  void push_back(value_type x)
  {
    *(end()+1)=*end();
    (*(end()+1))->up()=end()+1;
    *end()=x;
    (*end())->up()=end();
    ++size_;
  }

  void erase(value_type x)
  {
    node_impl_type::extract(x->up(),end()+1);
    --size_;
  }

  void clear()
  {
    *begin()=*end();
    (*begin())->up()=begin();
    size_=0;
  }

  void swap(random_access_index_ptr_array& x)
  {
    std::swap(size_,x.size_);
    std::swap(capacity_,x.capacity_);
    spc.swap(x.spc);
  }

  template<typename BoolConstant>
  void swap(random_access_index_ptr_array& x,BoolConstant swap_allocators)
  {
    std::swap(size_,x.size_);
    std::swap(capacity_,x.capacity_);
    spc.swap(x.spc,swap_allocators);
  }

private:
  size_type                        size_;
  size_type                        capacity_;
  auto_space<value_type,Allocator> spc;

  pointer ptrs()const
  {
    return spc.data();
  }

  void set_capacity(size_type c)
  {
    auto_space<value_type,Allocator> spc1(spc.get_allocator(),c+1);
    node_impl_type::transfer(begin(),end()+1,spc1.data());
    spc.swap(spc1);
    capacity_=c;
  }
};

template<typename Allocator>
void swap(
  random_access_index_ptr_array<Allocator>& x,
  random_access_index_ptr_array<Allocator>& y)
{
  x.swap(y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_index_ptr_array.hpp
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
*/