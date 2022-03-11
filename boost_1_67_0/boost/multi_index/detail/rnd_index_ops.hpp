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