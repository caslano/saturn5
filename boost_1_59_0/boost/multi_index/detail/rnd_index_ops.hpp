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
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
*/