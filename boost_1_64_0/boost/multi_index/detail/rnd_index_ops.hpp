/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_INDEX_OPS_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_INDEX_OPS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/multi_index/detail/rnd_index_ptr_array.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Common code for random_access_index memfuns having templatized and
 * non-templatized versions.
 */

template<typename Node,typename Allocator,typename Predicate>
Node* random_access_index_remove(
  random_access_index_ptr_array<Allocator>& ptrs,Predicate pred)
{
  typedef typename Node::value_type value_type;
  typedef typename Node::impl_ptr_pointer impl_ptr_pointer;

  impl_ptr_pointer first=ptrs.begin(),
                   res=first,
                   last=ptrs.end();
  for(;first!=last;++first){
    if(!pred(
        const_cast<const value_type&>(Node::from_impl(*first)->value()))){
      if(first!=res){
        std::swap(*first,*res);
        (*first)->up()=first;
        (*res)->up()=res;
      }
      ++res;
    }
  }
  return Node::from_impl(*res);
}

template<typename Node,typename Allocator,class BinaryPredicate>
Node* random_access_index_unique(
  random_access_index_ptr_array<Allocator>& ptrs,BinaryPredicate binary_pred)
{
  typedef typename Node::value_type       value_type;
  typedef typename Node::impl_ptr_pointer impl_ptr_pointer;

  impl_ptr_pointer first=ptrs.begin(),
                   res=first,
                   last=ptrs.end();
  if(first!=last){
    for(;++first!=last;){
      if(!binary_pred(
           const_cast<const value_type&>(Node::from_impl(*res)->value()),
           const_cast<const value_type&>(Node::from_impl(*first)->value()))){
        ++res;
        if(first!=res){
          std::swap(*first,*res);
          (*first)->up()=first;
          (*res)->up()=res;
        }
      }
    }
    ++res;
  }
  return Node::from_impl(*res);
}

template<typename Node,typename Allocator,typename Compare>
void random_access_index_inplace_merge(
  const Allocator& al,
  random_access_index_ptr_array<Allocator>& ptrs,
  BOOST_DEDUCED_TYPENAME Node::impl_ptr_pointer first1,Compare comp)
{
  typedef typename Node::value_type       value_type;
  typedef typename Node::impl_pointer     impl_pointer;
  typedef typename Node::impl_ptr_pointer impl_ptr_pointer;

  auto_space<impl_pointer,Allocator> spc(al,ptrs.size());

  impl_ptr_pointer first0=ptrs.begin(),
                   last0=first1,
                   last1=ptrs.end(),
                   out=spc.data();
  while(first0!=last0&&first1!=last1){
    if(comp(
        const_cast<const value_type&>(Node::from_impl(*first1)->value()),
        const_cast<const value_type&>(Node::from_impl(*first0)->value()))){
      *out++=*first1++;
    }
    else{
      *out++=*first0++;
    }
  }
  std::copy(&*first0,&*last0,&*out);
  std::copy(&*first1,&*last1,&*out);

  first1=ptrs.begin();
  out=spc.data();
  while(first1!=last1){
    *first1=*out++;
    (*first1)->up()=first1;
    ++first1;
  }
}

/* sorting */

/* auxiliary stuff */

template<typename Node,typename Compare>
struct random_access_index_sort_compare
{
  typedef typename Node::impl_pointer first_argument_type;
  typedef typename Node::impl_pointer second_argument_type;
  typedef bool                        result_type;

  random_access_index_sort_compare(Compare comp_=Compare()):comp(comp_){}

  bool operator()(
    typename Node::impl_pointer x,typename Node::impl_pointer y)const
  {
    typedef typename Node::value_type value_type;

    return comp(
      const_cast<const value_type&>(Node::from_impl(x)->value()),
      const_cast<const value_type&>(Node::from_impl(y)->value()));
  }

private:
  Compare comp;
};

template<typename Node,typename Allocator,class Compare>
void random_access_index_sort(
  const Allocator& al,
  random_access_index_ptr_array<Allocator>& ptrs,
  Compare comp)
{
  /* The implementation is extremely simple: an auxiliary
   * array of pointers is sorted using stdlib facilities and
   * then used to rearrange the index. This is suboptimal
   * in space and time, but has some advantages over other
   * possible approaches:
   *   - Use std::stable_sort() directly on ptrs using some
   *     special iterator in charge of maintaining pointers
   *     and up() pointers in sync: we cannot guarantee
   *     preservation of the container invariants in the face of
   *     exceptions, if, for instance, std::stable_sort throws
   *     when ptrs transitorily contains duplicate elements.
   *   - Rewrite the internal algorithms of std::stable_sort
   *     adapted for this case: besides being a fair amount of
   *     work, making a stable sort compatible with Boost.MultiIndex
   *     invariants (basically, no duplicates or missing elements
   *     even if an exception is thrown) is complicated, error-prone
   *     and possibly won't perform much better than the
   *     solution adopted.
   */

  if(ptrs.size()<=1)return;

  typedef typename Node::impl_pointer       impl_pointer;
  typedef typename Node::impl_ptr_pointer   impl_ptr_pointer;
  typedef random_access_index_sort_compare<
    Node,Compare>                           ptr_compare;
  
  impl_ptr_pointer   first=ptrs.begin();
  impl_ptr_pointer   last=ptrs.end();
  auto_space<
    impl_pointer,
    Allocator>       spc(al,ptrs.size());
  impl_ptr_pointer   buf=spc.data();

  std::copy(&*first,&*last,&*buf);
  std::stable_sort(&*buf,&*buf+ptrs.size(),ptr_compare(comp));

  while(first!=last){
    *first=*buf++;
    (*first)->up()=first;
    ++first;
  }
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_index_ops.hpp
gueJgO8Fwco4ttCALd85frd8RymU3GjA5i0Y+Zq0BTdTUmTA1s555hYpj2NvUB0r6tRjsSyzB+WZY3Ws056Xtknde1FSg+rYjIUDKiTX3EDGG763v8nZy+X3uFF6iujYD73ubCzfex9K+hiwt3sdGyrrybEpETr2SvXiB+T760dJa4O8ilmx8+QYN5CSToYyX23y3SuyLXGsqwG7+bl9+4PnNIHvDaKkuwG74eVfR8vvDQKuAbtswuxusp73UFLNgI188ugEWSbH1hi/914factTB1MSZ8CiS76pJr/HsfMG7NDRQVRyNoSSRAO2beNlVtmWOFZPYmr/q+BYLYmp/S/+3n/+XnIQLDUI5jFhR0c9eEy2F45dYcA6TH2rixyPONaU6pj3uK2jrMswSmoSHXNuaPuQrAvH2hqwyZPZ6OD5fIDPNGgvgDWsP2Or5Ixj+Qbsypc+2ivt0n1ivgQY5OyHMjlWTWKmtSHH6hiw8RfaJ8r3x7FUA1bw0Pw7ZT+6n5ImElPXAZ77YS4F2HNuFittcjol/aiOXbPwrvulvAwq1o2AjSmPvEqWaePvwYCtKu57ROpngzEAsJLndjSWZXKstgFbVO9cavDcUvDeMylpZsDapP0py6zIhH4L2NKhDT6SdcmiJNeATZp9vrZsL3ZKig3Yrz2mSFtOHJR0NGA96i27JngeMOibOfD+AFPWcRwrNWB/rDgwSX4vl5JZTMdeOH1irGwTefBuAVPWeBzzG7Buj9h/lPJclEy3GOriG7M0eD434HMEJbEWHVv8wLyZwfPhAdcPU2JhOtbs16zxwfMJgn4cu9+A7fU0Lpbfm0AJpTrWddjeiVK/iTB3A6zBgBt1f8GjlPxswJr/caGOtAWPqfJqfJ33gmyfHOtvwNiKP2vJ9z4J2hJgPefb5NymjGPdDFjfDpHPyrpMBjsP2NZdraUNiX+ckhoG7C++7gKqqmyNA/g+98INQMVAxAIDO1BHx5axY0axYwzEVlTsdjDGDsbWMbBbsVuxW6/dit2K9Wx9H4v9/vs7Z7171nIt1+K3dny7Tt59NgZffYLYDdZt4rnXiIHMn9nbSm9mY26SlWG2dbF/EPqPLIiZR/1ZvdDvhnQnAnfURezj9HWpXdW2HGOXzJvZ7KC/2qMu4/Tlja7YzYnxQuYH0x8D4skKwvTrtRiviRHMYrN0uoKxNF6Xp+6Y4yJLDdMf4xJNzHeC+zxDJrhPF/Z/0pntM2q+F6ssb6ImGjD7crRGLbQnWW5mt1KknYk8yT4zm9BxeUPEN1kTa6zKDp9ePg/tOZXWLE3Z/Etr7yLP6Zr4h+W5/Y9u3jimzqB7Op7KItaWmY15O08TWwTLc16t6miX+ZqY66EsvVg3BWNwibxekValj7U55thSTdA/WLUmHtfQZsvl8VbahV196iFPMj+Yvo/CTSyaLDVM3++x/yed+X7DMoYVmmjFrN6ifQ7kSdaJ2b3OjXMivpVy/kmrMqZva8RH1oDZlb5dTqNvyXIxO91nfhMcV0zyTCTzYjbZZ8YezM1V8rxVWtURR7NinJGlYrb12uP0iIHsHrNsuR5uwjyig21hZo8fTuiKcbZaX89sPSI7os3ImjLrXX7uE9Rljewjabo5bWJhZPGastljJ6/BmFgn7+lI+3r28jakW0/XVcwu23KNQj+QhbA8z6fVHqEuGzTRTCj7dV32M4iPrJSmzGvH6tJIt0lLvrctrW32NiUwzjZr4g9m0//c1Mx8X3BZT7JgZteL3mqP8UJWgdnVRo1WoC5bNHHIqaxz6aJol6j9mojQlBX6lGKt6V7t0sQheT9L2oIW0+YjBrK8FmVF5n9W718d1URbD2WtZ/w=
*/