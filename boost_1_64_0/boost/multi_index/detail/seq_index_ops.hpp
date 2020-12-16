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
MlkJq7LxeXeq32zlsYu1QlmWQ7c/o83y2kVDLdnu0P9pHVWzq29h03xg1qv6qpaoC/1wLocs73bSWp4/YjjGSxG7mGNTFtNldy3kWcouJtiVPR4+vBfqWdEuimnKpvSvORLjs7JdnGTmKN9FvRta1S6eM3t3srf6bXwNu6jM6nJ+2X6b+j2JXez2VDbzWvNK6NsmdjHMQ5nf80vN1D0rtZ7dMqxnCSaWaGKipXvzNbEgshSeyiqny9kKbd3WLrxtyuwet5ehvEi7mOql7Lw2+jD6doBd/PBRVqVt0ELM97F0nLYo2/DiwhX00QTKUygr5bfhqNpL1i5+Y/auj4/a24CsDbPi3qt3oJ6T7Hg2fzNpTj+7kBr9TnbcqmzK4zZnUZepdhEolOUXXuo9Y7KeHsomFTg2R+21SuuZpiz8UnAVzJU5djGTWc9XL2ywuXYxkpU3u8qntOiHeXaR2aKs1eJpV9R7nDSPmPV7Fm0V2LPRLg6yPFNW3x4PW6zsRlL/3X/mD1tiFz0syk6feKj26V5O54OaskJzTmxAP6y0i6fMeq5+sxpjd7VdeLI8V+46+hrp1tlFSaGs8uUMXqgL2TdmrvXPa6n7E3YRwazE0n3q9+hkNWH6421inOrb60nX72XSVEB70pZDQy3K3m3trN7V3KxPN6RFIuZDFJk/Mw+vwWiXGEO6PcOHqm9NGdIduvQ2Cm1N9kRTNuNIlQSs89vswmVRlurb/Uik22kXaZCn/pvPYpcd7ysmvV/yo+MIH4x5shBmJV7OSoW5QtaY2YQfp9XxaLc835W2ZmLOa+hbsvsWZet+yZwFbR0vj5vS1q7cpX5btt8uRjFrNPlxQ7QZ2WTZLlfp/xXnL0bDDspzBmn3bSk3orzDcp2XZv/h8xl9dNQuWnC7V6KG2pPELu7JGK7QH0aM3TMMY+mUXVTXlE1v/nkv8jxD50sWZbYuy9Q3a85RPZ3JdjlpvvcsWB/9d9MuWsk8LyZdr5Q7pb7FRD+YzMtMXPRQ3zFKkGudtBOlMvZDu5AtZFYmYEhe1POuXQxnee6ck/Mq6nnfLn7KGC4kvbNXO8NyzIfHcm5K67V2j5rTT+Q1ibTc30fGwZ7S2GVWfnsm9Z7OM3W9ed5wPzmRrJO0c0nr2ZqHu5Hnczp305RlPtdjK9rlpV10Z5bQNUjtX/BKXjdKO1SnfTb0+2u7yM/sWcBQ9TtTsi3MNnY4U0vdD5HXR9LSH+z2E+P6jbq+dSUdi3P3zow1hOyht7J2Nfeo35YJh2ieRVlEz4i1yDPY4T5PsnsszzrZhmRFnr84MG/PJh3HhuQIxnghKyTtDP2hZP03B9R7Ce4t1MSimZ02WDxZcWmnkt45aTrpPeIr4cB9qZNJY7ff+vUoz8SiyBozK5hpicAcI8sn7UTSu8ub7qv3En51YI+J45p+j4mocg48Fz2m6feY8A11YB+Jo5p+H4mE2g5x2EtZyZ/9rFh3mzvEMWaFYiJqI10nB/aROKLp95GI6u4QZwKS7XDSGpl9oXp+NJnSyXoeSnpmet1DfZd7ikOEpVR2blSGoUi3xIFzxYNJ50uNfdQ9XLICzIo/W7BR7b+r7EDScfPKnxEYZ2RlmZ1P7JoG6xlZOmYP67fbhLqQdWa23W/GVuS5TF9ehoUZ5mFukmVmtjBj8HrkSfaQ2eF1/0mnzm0cYgezmm9cwxD7Cocoyuy3sxVhvisdeM94f9K1tk+J/agL2QVmzi6rBGJf5RClme3NtfES1iUyL5jhm8+rqW+ZPU8blgblkVXUlO3JOqwyrqvWOsQHZvlnVWyL6831DtGaWbYbVXG/LmqDQ4Sw8pZNDj6DdGRLBSuvTs1xmO8=
*/