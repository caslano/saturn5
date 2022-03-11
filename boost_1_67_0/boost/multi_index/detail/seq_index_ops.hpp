/* Copyright 2003-2016 Joaquin M Lopez Munoz.
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
#include <boost/detail/no_exceptions_support.hpp>
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