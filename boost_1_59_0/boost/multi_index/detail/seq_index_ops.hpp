/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_SEQ_INDEX_OPS_HPP
#define BOOST_MULTI_INDEX_DETAIL_SEQ_INDEX_OPS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/core/no_exceptions_support.hpp>
#include <boost/multi_index/detail/seq_index_node.hpp>
#include <boost/limits.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp> 
#include <cstddef>

namespace boost{

namespace multi_index{

namespace detail{

/* Common code for sequenced_index memfuns having templatized and
 * non-templatized versions.
 */

template <typename SequencedIndex,typename Predicate>
void sequenced_index_remove(SequencedIndex& x,Predicate pred)
{
  typedef typename SequencedIndex::iterator iterator;
  iterator first=x.begin(),last=x.end();
  while(first!=last){
    if(pred(*first))x.erase(first++);
    else ++first;
  }
}

template <typename SequencedIndex,class BinaryPredicate>
void sequenced_index_unique(SequencedIndex& x,BinaryPredicate binary_pred)
{
  typedef typename SequencedIndex::iterator iterator;
  iterator first=x.begin();
  iterator last=x.end();
  if(first!=last){
    for(iterator middle=first;++middle!=last;middle=first){
      if(binary_pred(*middle,*first))x.erase(middle);
      else first=middle;
    }
  }
}

template <typename SequencedIndex,typename Compare>
void sequenced_index_merge(SequencedIndex& x,SequencedIndex& y,Compare comp)
{
  typedef typename SequencedIndex::iterator iterator;
  if(&x!=&y){
    iterator first0=x.begin(),last0=x.end();
    iterator first1=y.begin(),last1=y.end();
    while(first0!=last0&&first1!=last1){
      if(comp(*first1,*first0))x.splice(first0,y,first1++);
      else ++first0;
    }
    x.splice(last0,y,first1,last1);
  }
}

/* sorting  */

/* auxiliary stuff */

template<typename Node,typename Compare>
void sequenced_index_collate(
  BOOST_DEDUCED_TYPENAME Node::impl_type* x,
  BOOST_DEDUCED_TYPENAME Node::impl_type* y,
  Compare comp)
{
  typedef typename Node::impl_type    impl_type;
  typedef typename Node::impl_pointer impl_pointer;

  impl_pointer first0=x->next();
  impl_pointer last0=x;
  impl_pointer first1=y->next();
  impl_pointer last1=y;
  while(first0!=last0&&first1!=last1){
    if(comp(
        Node::from_impl(first1)->value(),Node::from_impl(first0)->value())){
      impl_pointer tmp=first1->next();
      impl_type::relink(first0,first1);
      first1=tmp;
    }
    else first0=first0->next();
  }
  impl_type::relink(last0,first1,last1);
}

/* Some versions of CGG require a bogus typename in counter_spc
 * inside sequenced_index_sort if the following is defined
 * also inside sequenced_index_sort.
 */

BOOST_STATIC_CONSTANT(
  std::size_t,
  sequenced_index_sort_max_fill=
    (std::size_t)std::numeric_limits<std::size_t>::digits+1);

#include <boost/multi_index/detail/ignore_wstrict_aliasing.hpp>

template<typename Node,typename Compare>
void sequenced_index_sort(Node* header,Compare comp)
{
  /* Musser's mergesort, see http://www.cs.rpi.edu/~musser/gp/List/lists1.html.
   * The implementation is a little convoluted: in the original code
   * counter elements and carry are std::lists: here we do not want
   * to use multi_index instead, so we do things at a lower level, managing
   * directly the internal node representation.
   * Incidentally, the implementations I've seen of this algorithm (SGI,
   * Dinkumware, STLPort) are not exception-safe: this is. Moreover, we do not
   * use any dynamic storage.
   */

  if(header->next()==header->impl()||
     header->next()->next()==header->impl())return;

  typedef typename Node::impl_type      impl_type;
  typedef typename Node::impl_pointer   impl_pointer;

  typedef typename aligned_storage<
    sizeof(impl_type),
    alignment_of<impl_type>::value
  >::type                               carry_spc_type;
  carry_spc_type                        carry_spc;
  impl_type&                            carry=
    *reinterpret_cast<impl_type*>(&carry_spc);
  typedef typename aligned_storage<
    sizeof(
      impl_type
        [sequenced_index_sort_max_fill]),
    alignment_of<
      impl_type
        [sequenced_index_sort_max_fill]
    >::value
  >::type                               counter_spc_type;
  counter_spc_type                      counter_spc;
  impl_type*                            counter=
    reinterpret_cast<impl_type*>(&counter_spc);
  std::size_t                           fill=0;

  carry.prior()=carry.next()=static_cast<impl_pointer>(&carry);
  counter[0].prior()=counter[0].next()=static_cast<impl_pointer>(&counter[0]);

  BOOST_TRY{
    while(header->next()!=header->impl()){
      impl_type::relink(carry.next(),header->next());
      std::size_t i=0;
      while(i<fill&&counter[i].next()!=static_cast<impl_pointer>(&counter[i])){
        sequenced_index_collate<Node>(&carry,&counter[i++],comp);
      }
      impl_type::swap(
        static_cast<impl_pointer>(&carry),
        static_cast<impl_pointer>(&counter[i]));
      if(i==fill){
        ++fill;
        counter[fill].prior()=counter[fill].next()=
          static_cast<impl_pointer>(&counter[fill]);
      }
    }

    for(std::size_t i=1;i<fill;++i){
      sequenced_index_collate<Node>(&counter[i],&counter[i-1],comp);
    }
    impl_type::swap(
      header->impl(),static_cast<impl_pointer>(&counter[fill-1]));
  }
  BOOST_CATCH(...)
  {
    impl_type::relink(
      header->impl(),carry.next(),static_cast<impl_pointer>(&carry));
    for(std::size_t i=0;i<=fill;++i){
      impl_type::relink(
        header->impl(),counter[i].next(),
        static_cast<impl_pointer>(&counter[i]));
    }
    BOOST_RETHROW;
  }
  BOOST_CATCH_END
}

#include <boost/multi_index/detail/restore_wstrict_aliasing.hpp>

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* seq_index_ops.hpp
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
*/