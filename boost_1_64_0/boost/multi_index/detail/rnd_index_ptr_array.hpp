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
7Yu5eUoTsZqyS9H9ZmGtO0Pj06qs862radEuFzQRpCnrZC+gntlc0sQPZvOth8uj/67IPpJ2cm0RO8b1VU0cYBZ65Fh22DV9u/xbYfwgrFnXabyw8oYvbHIdY/6mvM8nbc+nU+0RA1k9Zg1jryxEDLc00YNZvZyfLiEd2WZW3rA6le5gTNxxX150gibqMgsPv78c6wvZ78z27du0QT3noj5i/Xd6Xet1qOdjTURZlJWcWTATxtIzuV5L0x2nybxg+uNDuEm6aDI/mH6diDWxeBNLMDHx3H1dgp67TxdqYuEmFm1isSZ1iX9uEp+JiRfuLeiF+/JCX5jERzaF2R/XevdAni81kZFZ/Pz6W5An2RJmi4bMGYt59EoTfZhNXDw/zPw7GzJ2sm6asrKXj1VAukRNeApljZ7k74D2JDvDLG5M20isS29ku0jTndOS+cFku5h+F0XGTrbOouwPn3WT0e8fZHnSdP1O5gcz9LuJif8kzz9puvnnS3aG2b/vN8lntP//GzcYu5800Ugo6566e7z5N4LkWvBN3lOVVjbIsyViJ8vObNX74YnoB5N0Qd81EcPKO9dhc2eMT2ERg4SyTMNsH9AumkWMZJbws9ZcjBfN4rY8YbGIrMw2fWxyCOugwUo/7HMLdTHYuXy3C+GYY7B6v3nlR7+TecH097NcZAeYJf4MuAizWkQlZhNOBAegnh4W0YjZDr9OA9EPZMWY3Z2Z4wLGGVk4szP7UoebfyNLjnm7Jfk+u7QThc5p6D+HRbRgFlBjdlnUhcyf5fliZz01rr306ebe21Lb/Jtlsjwfi5jKbNK+nl9gKS2YfyWN6yCZH0zOMZPvxJl/S0+Os9QWEcPs1tXquH8WlcYimjFb3mcpxmcCWQSzCUcfLEVd0srxIk2OF5PvGsrxQnbYqsznQbNoxJAhOXZputjjyFprylpUS9fL/HuSsq0DLaKgpqxceNcmQph8i9PkW6Xm33KVdSHzgunbJZosLUx/XzjWJM94kzxdJnkmkgXC9Pd3g3K4tzCyTDD9vd/o/2em3/iVdSHzh+nj882p4gsxxBdElhamjy+ULBCmjyGKLJMyWU+z7zHLtpZ1kaZva1kXafq2JuvG7MOKR+fVc1+LOKYpi3vU/iXKy50cgzRdDIlkmWDJMZh/W1u2C5kXTB9DGFlamD6GKJM8Y0zyjDXJM54sG7Na2+ZtRXxkqy3KDowqfQP1LGARqZg17ZSQDekKyTaTphvXhd1bGFkmmGFc/z8z/Z67TEcLR2WLssaPamB9CS+R3J7SdO0ZTeYF07dnDFlamL4948jmaMo2nu1LS5jZt/flHCuVXBdpurqEkHnB9HUJJUsL09clnKwIs3PPTqjn4WTNmfUeMS8v+ogO6t4w/b3mELLOzAIq1b6DsUQWCDPMFbJMMMNcoZPH5dLyk82JLP0Z6cjaMQtNtxzH4qiyFtGQWf0byzE+E8hqW5ItX1K6r/nC1fN+i3golNXOWTcK5YVaxF0t2ZLub9x/+DUS47OSRXSR6fKQ9XIeCEF5ZI2Ylc/56DbSVZbtIu1F4pXlGGdkrZhNr95LnWNWsQiHRdk///ZohDFYjY6pmrKYn1/aox9qWMRCq7KaD1tMRl2oUWKYRecetwHtUs8i6rM8C3svK4p6NrCIDE5lpRof/4rYW1nEBU3ZwDZz/DBeIixiOyvvfOsvfZCuvUWMYLG3WJr/GOLroM7B8hjOweJMzEXmBzM8fydLJ+9r5Ca7WbDuRsy/rsnjU5runZpQsqzMdlysPwBjkGywRZmzWncPxBBF80hT9qT7lQmIvYdFrGV51owZ/wz919MilrA8h3xcPBL17GsRw6zK4oLr50I=
*/