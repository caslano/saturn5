/* Copyright 2016-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_ALGORITHM_HPP
#define BOOST_POLY_COLLECTION_ALGORITHM_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <algorithm>
#include <boost/poly_collection/detail/auto_iterator.hpp>
#include <boost/poly_collection/detail/functional.hpp>
#include <boost/poly_collection/detail/iterator_traits.hpp>
#include <boost/poly_collection/detail/segment_split.hpp>
#include <boost/poly_collection/detail/type_restitution.hpp>
#include <iterator>
#include <random>
#include <type_traits>
#include <utility>

/* Improved performance versions of std algorithms over poly_collection.
 * poly_collection::alg is expected to be faster than the homonym std::alg
 * because the latter does a traversal over a segmented structured, where
 * incrementing requires checking for segment change, whereas the former
 * for-loops over flat segments.
 * Additionally, poly_collection::alg<Ti...>(...,f) *restitutes* Ti when
 * passing elements to f, i.e. if the concrete type of the element is Ti
 * then f is invoked with a [const] Ti&, which can dramatically improve
 * performance when f has specific overloads for Ti (like, for instance,
 * generic lambdas) as static optimization can kick in (devirtualization
 * being a particular example).
 */

namespace boost{

namespace poly_collection{

namespace detail{

namespace algorithm{

template<typename Iterator>
using enable_if_poly_collection_iterator=typename std::enable_if<
  !std::is_void<typename poly_collection_of<Iterator>::type>::value
>::type*;

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_all_of,std::all_of)

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool all_of(const Iterator& first,const Iterator& last,Predicate pred)
{
  auto alg=restitute_range<Ts...>(std_all_of{},pred);
  for(auto i:detail::segment_split(first,last))if(!alg(i))return false;
  return true;
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_any_of,std::any_of)

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool any_of(const Iterator& first,const Iterator& last,Predicate pred)
{
  auto alg=restitute_range<Ts...>(std_any_of{},pred);
  for(auto i:detail::segment_split(first,last))if(alg(i))return true;
  return false;
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_none_of,std::none_of)

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool none_of(const Iterator& first,const Iterator& last,Predicate pred)
{
  auto alg=restitute_range<Ts...>(std_none_of{},pred);
  for(auto i:detail::segment_split(first,last))if(!alg(i))return false;
  return true;
}

struct for_each_alg
{
  template<typename InputIterator,typename Function>
  void operator()(
    InputIterator first,InputIterator last,Function& f)const /* note the & */
  {
    for(;first!=last;++first)f(*first);
  }
};

template<
  typename... Ts,typename Iterator,typename Function,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Function for_each(const Iterator& first,const Iterator& last,Function f)
{
  for_each_segment(first,last,restitute_range<Ts...>(for_each_alg{},f));
  return f;
}

struct for_each_n_alg
{
  template<
    typename InputIterator,typename Size,typename Function
  >
  InputIterator operator()(
    InputIterator first,Size n,Function& f)const /* note the & */
  {
    for(;n>0;++first,(void)--n)f(*first);
    return first;
  }
};

template<
  typename... Ts,typename Iterator,typename Size,typename Function,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator for_each_n(const Iterator& first,Size n,Function f)
{
  using traits=iterator_traits<Iterator>;
  using local_base_iterator=typename traits::local_base_iterator;

  if(n<=0)return first;

  auto alg=restitute_iterator<Ts...>(
         cast_return<local_base_iterator>(for_each_n_alg{}));
  auto lbit=traits::local_base_iterator_from(first);
  auto sit=traits::base_segment_info_iterator_from(first);
  for(;;){
    auto m=sit->end()-lbit;
    if(n<=m){
      auto it=alg(sit->type_info(),lbit,n,f);
      return traits::iterator_from(
        it,traits::end_base_segment_info_iterator_from(first));
    }
    else{
      alg(sit->type_info(),lbit,m,f);
      n-=m;
    }
    ++sit;
    lbit=sit->begin();
  }
}

template<
  typename Algorithm,typename... Ts,
  typename Iterator,typename... Args,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator generic_find(
  const Iterator& first,const Iterator& last,Args&&... args)
{
  using traits=iterator_traits<Iterator>;
  using local_base_iterator=typename traits::local_base_iterator;

  auto alg=restitute_range<Ts...>(
    cast_return<local_base_iterator>(Algorithm{}),
    std::forward<Args>(args)...);
  for(auto i:detail::segment_split(first,last)){
    auto it=alg(i);
    if(it!=i.end())
      return traits::iterator_from(
        it,traits::end_base_segment_info_iterator_from(last));
  }
  return last;
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_find,std::find)

template<
  typename... Ts,typename Iterator,typename T,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find(const Iterator& first,const Iterator& last,const T& x)
{
  return generic_find<std_find,Ts...>(first,last,x);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_find_if,std::find_if)

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find_if(const Iterator& first,const Iterator& last,Predicate pred)
{
  return generic_find<std_find_if,Ts...>(first,last,pred);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_find_if_not,std::find_if_not)

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find_if_not(const Iterator& first,const Iterator& last,Predicate pred)
{
  return generic_find<std_find_if_not,Ts...>(first,last,pred);
}

/* find_end defined after search below */

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_find_first_of,std::find_first_of)

template<
  typename... Ts,typename Iterator,typename ForwardIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find_first_of(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2)
{
  return generic_find<std_find_first_of,Ts...>(first1,last1,first2,last2);
}

template<
  typename... Ts,typename Iterator,
  typename ForwardIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find_first_of(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2,BinaryPredicate pred)
{
  return generic_find<std_find_first_of,Ts...>(first1,last1,first2,last2,pred);
}

template<typename... Ts>
struct adjacent_find_alg
{
  template<
    typename LocalIterator,typename BinaryPredicate,typename LocalBaseIterator
  >
  LocalBaseIterator operator()(
    LocalIterator first,LocalIterator last,BinaryPredicate pred,
    bool& carry,const std::type_info* prev_info, /* note the &s */
    LocalBaseIterator& prev)const
  {
    if(first==last)return LocalBaseIterator{last};
    if(carry){
      auto p=restitute_iterator<Ts...>(deref_to(pred));
      if(p(*prev_info,prev,first))return prev;
    }
    auto res=std::adjacent_find(first,last,pred);
    if(res==last){
      carry=true;
      prev_info=&typeid(
        typename std::iterator_traits<LocalIterator>::value_type);
      prev=LocalBaseIterator{last-1};
    }
    else carry=false;
    return LocalBaseIterator{res};
  }
};

template<
  typename... Ts,typename Iterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator adjacent_find(
  const Iterator& first,const Iterator& last,BinaryPredicate pred)
{
  using traits=iterator_traits<Iterator>;
  using local_base_iterator=typename traits::local_base_iterator;

  bool                  carry=false;
  const std::type_info* prev_info{&typeid(void)};
  local_base_iterator   prev;
  return generic_find<adjacent_find_alg<Ts...>,Ts...>(
    first,last,pred,carry,prev_info,prev);  
}

template<
  typename... Ts,typename Iterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator adjacent_find(const Iterator& first,const Iterator& last)
{
  return algorithm::adjacent_find<Ts...>(first,last,transparent_equal_to{});
}

template<
  typename Algorithm,typename... Ts,
  typename Iterator,typename... Args,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::ptrdiff_t generic_count(
  const Iterator& first,const Iterator& last,Args&&... args)
{
  auto alg=restitute_range<Ts...>(Algorithm{},std::forward<Args>(args)...);
  std::ptrdiff_t res=0;
  for(auto i:detail::segment_split(first,last))res+=alg(i);
  return res;
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_count,std::count)

template<
  typename... Ts,typename Iterator,typename T,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::ptrdiff_t count(const Iterator& first,const Iterator& last,const T& x)
{
  return generic_count<std_count,Ts...>(first,last,x);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_count_if,std::count_if)

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::ptrdiff_t count_if(
  const Iterator& first,const Iterator& last,Predicate pred)
{
  return generic_count<std_count_if,Ts...>(first,last,pred);
}

struct mismatch_alg
{
  template<
    typename InputIterator1,
    typename InputIterator2,typename BinaryPredicate
  >
  InputIterator1 operator()(
    InputIterator1 first1,InputIterator1 last1,
    InputIterator2& first2,BinaryPredicate pred)const /* note the & */
  {
    while(first1!=last1&&pred(*first1,*first2)){
      ++first1;
      ++first2;
    }
    return first1;
  }

  template<
    typename InputIterator1,
    typename InputIterator2,typename BinaryPredicate
  >
  InputIterator1 operator()(
    InputIterator1 first1,InputIterator1 last1,
    InputIterator2& first2,InputIterator2 last2, /* note the & */
    BinaryPredicate pred)const
  {
    while(first1!=last1&&first2!=last2&&pred(*first1,*first2)){
      ++first1;
      ++first2;
    }
    return first1;
  }
};

template<
  typename... Ts,typename Iterator,
  typename InputIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::pair<Iterator,InputIterator> mismatch(
  const Iterator& first1,const Iterator& last1,
  InputIterator first2,BinaryPredicate pred)
{
  auto it=generic_find<mismatch_alg,Ts...>(first1,last1,first2,pred);
  return {it,first2};
}

template<
  typename... Ts,typename Iterator,typename InputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::pair<Iterator,InputIterator> mismatch(
  const Iterator& first1,const Iterator& last1,InputIterator first2)
{
  return algorithm::mismatch<Ts...>(
    first1,last1,first2,transparent_equal_to{});
}

template<
  typename... Ts,typename Iterator,
  typename InputIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::pair<Iterator,InputIterator> mismatch(
  const Iterator& first1,const Iterator& last1,
  InputIterator first2,InputIterator last2,BinaryPredicate pred)
{
  auto it=generic_find<mismatch_alg,Ts...>(first1,last1,first2,last2,pred);
  return {it,first2};
}

template<
  typename... Ts,typename Iterator,typename InputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::pair<Iterator,InputIterator> mismatch(
  const Iterator& first1,const Iterator& last1,
  InputIterator first2,InputIterator last2)
{
  return algorithm::mismatch<Ts...>(
    first1,last1,first2,last2,transparent_equal_to{});
}

struct equal_alg
{
  template<
    typename InputIterator1,
    typename InputIterator2,typename BinaryPredicate
  >
  bool operator()(
    InputIterator1 first1,InputIterator1 last1,
    InputIterator2& first2,BinaryPredicate pred)const /* note the & */
  {
    for(;first1!=last1;++first1,++first2){
      if(!pred(*first1,*first2))return false;
    }
    return true;
  }

  template<
    typename InputIterator1,
    typename InputIterator2,typename BinaryPredicate
  >
  bool operator()(
    InputIterator1 first1,InputIterator1 last1,
    InputIterator2& first2,InputIterator2 last2, /* note the & */
    BinaryPredicate pred)const
  {
    for(;first1!=last1&&first2!=last2;++first1,++first2){
      if(!pred(*first1,*first2))return false;
    }
    return first1==last1; /* don't check first2==last2 as op is partial */
  }
};

template<
  typename... Ts,typename Iterator,
  typename InputIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool equal(
  const Iterator& first1,const Iterator& last1,
  InputIterator first2,BinaryPredicate pred)
{
  auto alg=restitute_range<Ts...>(equal_alg{},first2,pred);
  for(auto i:detail::segment_split(first1,last1))if(!alg(i))return false;
  return true;
}

template<
  typename... Ts,typename Iterator,typename InputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool equal(
  const Iterator& first1,const Iterator& last1,InputIterator first2)
{
  return algorithm::equal<Ts...>(first1,last1,first2,transparent_equal_to{});
}

template<
  typename... Ts,typename Iterator,
  typename InputIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool equal(
  const Iterator& first1,const Iterator& last1,
  InputIterator first2,InputIterator last2,BinaryPredicate pred)
{
  auto alg=restitute_range<Ts...>(equal_alg{},first2,last2,pred);
  for(auto i:detail::segment_split(first1,last1))if(!alg(i))return false;
  return first2==last2;
}

template<
  typename... Ts,typename Iterator,typename InputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool equal(
  const Iterator& first1,const Iterator& last1,
  InputIterator first2,InputIterator last2)
{
  return algorithm::equal<Ts...>(
    first1,last1,first2,last2,transparent_equal_to{});
}

template<
  typename Iterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::ptrdiff_t fast_distance(const Iterator& first,const Iterator& last)
{
  using traits=iterator_traits<Iterator>;

  if(first==last)return 0;

  auto sfirst=traits::base_segment_info_iterator_from(first),
       slast=traits::base_segment_info_iterator_from(last);
  if(sfirst==slast){
    return std::distance(
      traits::local_base_iterator_from(first),
      traits::local_base_iterator_from(last));
  }
  else{
    std::ptrdiff_t m=std::distance(
      traits::local_base_iterator_from(first),sfirst->end());
    while(++sfirst!=slast)m+=std::distance(sfirst->begin(),sfirst->end());
    if(slast!=traits::end_base_segment_info_iterator_from(last)){
      m+=std::distance(
        slast->begin(),traits::local_base_iterator_from(last));
    }
    return m;
  }
}

template<
  typename... Ts,typename Iterator,
  typename ForwardIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool is_permutation_suffix(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2,BinaryPredicate pred)
{
  using traits=iterator_traits<Iterator>;

  auto send=traits::end_base_segment_info_iterator_from(last1);
  for(auto i:detail::segment_split(first1,last1)){
    for(auto lbscan=i.begin();lbscan!=i.end();++lbscan){
      auto& info=i.type_info();
      auto p=head_closure(
        restitute_iterator<Ts...>(deref_1st_to(pred)),info,lbscan);
      auto scan=traits::iterator_from(lbscan,send);
      if(algorithm::find_if<Ts...>(first1,scan,p)!=scan)continue;
      std::ptrdiff_t matches=std::count_if(first2,last2,p);
      if(matches==0||
         matches!=algorithm::count_if<Ts...>(scan,last1,p))return false;
    }
  }
  return true;
}

template<
  typename... Ts,typename Iterator,
  typename ForwardIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool is_permutation(
  Iterator first1,Iterator last1,ForwardIterator first2,BinaryPredicate pred)
{
  std::tie(first1,first2)=algorithm::mismatch<Ts...>(first1,last1,first2,pred);
  auto last2=std::next(first2,algorithm::fast_distance(first1,last1));
  return is_permutation_suffix<Ts...>(first1,last1,first2,last2,pred);
}

template<
  typename... Ts,typename Iterator,typename ForwardIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool is_permutation(
  const Iterator& first1,const Iterator& last1,ForwardIterator first2)
{
  return algorithm::is_permutation<Ts...>(
    first1,last1,first2,transparent_equal_to{});
}

template<
  typename... Ts,typename Iterator,
  typename ForwardIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool is_permutation(
  Iterator first1,Iterator last1,
  ForwardIterator first2,ForwardIterator last2,BinaryPredicate pred)
{
  std::tie(first1,first2)=algorithm::mismatch<Ts...>(
    first1,last1,first2,last2,pred);
  if(algorithm::fast_distance(first1,last1)!=std::distance(first2,last2))
    return false;
  else return is_permutation_suffix<Ts...>(first1,last1,first2,last2,pred);
}

template<
  typename... Ts,typename Iterator,typename ForwardIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool is_permutation(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2)
{
  return algorithm::is_permutation<Ts...>(
    first1,last1,first2,last2,transparent_equal_to{});
}

template<
  typename... Ts,typename Iterator,
  typename ForwardIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator search(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2,BinaryPredicate pred)
{
  using traits=iterator_traits<Iterator>;

  auto send=traits::end_base_segment_info_iterator_from(last1);
  for(auto i:detail::segment_split(first1,last1)){
    for(auto lbit=i.begin(),lbend=i.end();lbit!=lbend;++lbit){
      Iterator it=traits::iterator_from(lbit,send);
      if(algorithm::mismatch<Ts...>(it,last1,first2,last2,pred).second==last2)
        return it;
    }
  }
  return last1;
}

template<
  typename... Ts,typename Iterator,typename ForwardIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator search(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2)
{
  return algorithm::search<Ts...>(
    first1,last1,first2,last2,transparent_equal_to{});
}

template<
  typename... Ts,typename Iterator,
  typename ForwardIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find_end(
  Iterator first1,Iterator last1,
  ForwardIterator first2,ForwardIterator last2,BinaryPredicate pred)
{
  if(first2==last2)return last1;

  for(Iterator res=last1;;){
    Iterator res1=algorithm::search<Ts...>(first1,last1,first2,last2,pred);
    if(res1==last1)return res;
    else{
      first1=res=res1;
      ++first1;
    }
  }
}

template<
  typename... Ts,typename Iterator,typename ForwardIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator find_end(
  const Iterator& first1,const Iterator& last1,
  ForwardIterator first2,ForwardIterator last2)
{
  return algorithm::find_end<Ts...>(
    first1,last1,first2,last2,transparent_equal_to{});
}

struct search_n_alg
{
  template<
    typename ForwardIterator,typename Size,
    typename T,typename BinaryPredicate
  >
  ForwardIterator operator()(
    ForwardIterator first,ForwardIterator last,
    Size count,bool& carry,Size& remain,const T& x, /* note the &s */
    BinaryPredicate pred)const
  {
    for(;first!=last;++first){
      if(!pred(*first,x)){carry=false;remain=count;continue;}
      auto res=first;
      for(;;){
        if(--remain==0||++first==last)return res;
        if(!pred(*first,x)){carry=false;remain=count;break;}
      } 
    }
    return last;
  }
};

template<
  typename... Ts,typename Iterator,
  typename Size,typename T,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator search_n(
  const Iterator& first,const Iterator& last,
  Size count,const T& x,BinaryPredicate pred)
{
  using traits=iterator_traits<Iterator>;
  using local_base_iterator=typename traits::local_base_iterator;

  if(count<=0)return first;

  bool                carry=false;
  auto                remain=count;
  auto                alg=restitute_range<Ts...>(
                        cast_return<local_base_iterator>(search_n_alg{}),
                        count,carry,remain,x,pred);
  local_base_iterator prev;
  for(auto i:detail::segment_split(first,last)){
    auto it=alg(i);
    if(it!=i.end()){
      if(remain==0)
        return traits::iterator_from(
          carry?prev:it,
          traits::end_base_segment_info_iterator_from(last));
      else if(!carry){prev=it;carry=true;}
    }
  }
  return last;
}

template<
  typename... Ts,typename Iterator,
  typename Size,typename T,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator search_n(
  const Iterator& first,const Iterator& last,Size count,const T& x)
{
  return algorithm::search_n<Ts...>(
    first,last,count,x,transparent_equal_to{});
}

template<
  typename Algorithm,typename... Ts,
  typename Iterator,typename OutputIterator,typename... Args,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator generic_copy(
  const Iterator& first,const Iterator& last,OutputIterator res,Args&&... args)
{
  for(auto i:detail::segment_split(first,last)){
    auto alg=restitute_range<Ts...>(
      Algorithm{},res,std::forward<Args>(args)...);
    res=alg(i);
  }
  return res;
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_copy,std::copy)

template<
  typename... Ts,typename Iterator,typename OutputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator copy(
  const Iterator& first,const Iterator& last,OutputIterator res)
{
  return generic_copy<std_copy,Ts...>(first,last,res);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_copy_n,std::copy_n)

template<
  typename... Ts,typename Iterator,typename Size,typename OutputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator copy_n(const Iterator& first,Size count,OutputIterator res)
{
  using traits=iterator_traits<Iterator>;

  if(count<=0)return res;

  auto lbit=traits::local_base_iterator_from(first);
  auto sit=traits::base_segment_info_iterator_from(first);
  for(;;){
    auto n=(std::min)(count,sit->end()-lbit);
    auto alg=restitute_iterator<Ts...>(std_copy_n{},n,res);
    res=alg(sit->type_info(),lbit);
    if((count-=n)==0)break;
    ++sit;
    lbit=sit->begin();
  }
  return res;
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_copy_if,std::copy_if)

template<
  typename... Ts,typename Iterator,typename OutputIterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator copy_if(
  const Iterator& first,const Iterator& last,OutputIterator res,Predicate pred)
{
  return generic_copy<std_copy_if,Ts...>(first,last,res,pred);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_move,std::move)

template<
  typename... Ts,typename Iterator,typename OutputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator move(
  const Iterator& first,const Iterator& last,OutputIterator res)
{
  return generic_copy<std_move,Ts...>(first,last,res);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_transform,std::transform)

template<
  typename... Ts,typename Iterator,
  typename OutputIterator,typename UnaryOperation,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator transform(
  const Iterator& first,const Iterator& last,
  OutputIterator res,UnaryOperation op)
{
  return generic_copy<std_transform,Ts...>(first,last,res,op);
}

struct transform2_alg
{
  template<
    typename InputIterator1,typename InputIterator2,
    typename OutputIterator,typename BinaryOperation
  >
  OutputIterator operator()(
    InputIterator1 first1,InputIterator1 last1,
    OutputIterator res, /* third place for compatibility with generic_copy */
    InputIterator2& first2, BinaryOperation op)const         /* note the & */
  {
    while(first1!=last1)*res++=op(*first1++,*first2++);
    return res;
  }
};

template<
  typename... Ts,typename Iterator,typename InputIterator,
  typename OutputIterator,typename BinaryOperation,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator transform(
  const Iterator& first1,const Iterator& last1,InputIterator first2,
  OutputIterator res,BinaryOperation op)
{
  return generic_copy<transform2_alg,Ts...>(first1,last1,res,first2,op);  
}

struct replace_copy_alg
{
  /* std::replace_copy broken in VS2015, internal ticket VSO#279818 
   * "<algorithm>: replace_copy() and replace_copy_if() shouldn't use the
   * conditional operator".
   */

  template<typename InputIterator,typename OutputIterator,typename T>
  OutputIterator operator()(
    InputIterator first,InputIterator last,OutputIterator res,
    const T& old_x,const T& new_x)
  {
    for(;first!=last;++first,++res){
      if(*first==old_x)*res=new_x;
      else             *res=*first;
    }
    return res;
  }
};

template<
  typename... Ts,typename Iterator,typename OutputIterator,typename T,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator replace_copy(
  const Iterator& first,const Iterator& last,OutputIterator res,
  const T& old_x,const T& new_x)
{
  return generic_copy<replace_copy_alg,Ts...>(first,last,res,old_x,new_x);
}

struct replace_copy_if_alg
{
  /* std::replace_copy_if broken in VS2015, internal ticket VSO#279818 
   * "<algorithm>: replace_copy() and replace_copy_if() shouldn't use the
   * conditional operator".
   */

  template<
    typename InputIterator,typename OutputIterator,
    typename Predicate,typename T
  >
  OutputIterator operator()(
    InputIterator first,InputIterator last,OutputIterator res,
    Predicate pred,const T& new_x)
  {
    for(;first!=last;++first,++res){
      if(pred(*first))*res=new_x;
      else            *res=*first;
    }
    return res;
  }
};

template<
  typename... Ts,typename Iterator,typename OutputIterator,
  typename Predicate,typename T,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator replace_copy_if(
  const Iterator& first,const Iterator& last,OutputIterator res,
  Predicate pred,const T& new_x)
{
  return generic_copy<replace_copy_if_alg,Ts...>(first,last,res,pred,new_x);  
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(std_remove_copy,std::remove_copy)

template<
  typename... Ts,typename Iterator,typename OutputIterator,typename T,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator remove_copy(
  const Iterator& first,const Iterator& last,OutputIterator res,const T& x)
{
  return generic_copy<std_remove_copy,Ts...>(first,last,res,x);  
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(
  std_remove_copy_if,std::remove_copy_if)

template<
  typename... Ts,typename Iterator,typename OutputIterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator remove_copy_if(
  const Iterator& first,const Iterator& last,OutputIterator res,Predicate pred)
{
  return generic_copy<std_remove_copy_if,Ts...>(first,last,res,pred);  
}

template<typename... Ts>
struct unique_copy_alg
{
  template<
    typename LocalIterator,typename OutputIterator,
    typename BinaryPredicate,typename LocalBaseIterator
  >
  OutputIterator operator()(
    LocalIterator first,LocalIterator last,
    OutputIterator res, BinaryPredicate pred,
    bool& carry,const std::type_info* prev_info, /* note the &s */
    LocalBaseIterator& prev)const
  {
    if(carry){
      auto p=restitute_iterator<Ts...>(deref_to(pred));
      for(;first!=last;++first)if(!p(*prev_info,prev,first))break;
    }
    if(first==last)return res;
    res=std::unique_copy(first,last,res,pred);
    carry=true;
    prev_info=&typeid(
      typename std::iterator_traits<LocalIterator>::value_type);
    prev=LocalBaseIterator{last-1};
    return res;
  }
};

template<
  typename... Ts,typename Iterator,
  typename OutputIterator,typename BinaryPredicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator unique_copy(
  const Iterator& first,const Iterator& last,
  OutputIterator res,BinaryPredicate pred)
{
  using traits=iterator_traits<Iterator>;
  using local_base_iterator=typename traits::local_base_iterator;

  bool                  carry=false;
  const std::type_info* prev_info{&typeid(void)};
  local_base_iterator   prev;
  return generic_copy<unique_copy_alg<Ts...>,Ts...>(
    first,last,res,pred,carry,prev_info,prev);  
}

template<
  typename... Ts,typename Iterator,typename OutputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator unique_copy(
  const Iterator& first,const Iterator& last,OutputIterator res)
{
  return algorithm::unique_copy<Ts...>(first,last,res,transparent_equal_to{});
}

template<
  typename... Ts,typename Iterator,typename OutputIterator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator rotate_copy(
  const Iterator& first,const Iterator& middle,const Iterator& last,
  OutputIterator res)
{
  res=algorithm::copy<Ts...>(middle,last,res);
  return algorithm::copy<Ts...>(first,middle,res);
}

struct sample_alg
{
  template<
    typename InputIterator,typename OutputIterator,
    typename Distance,typename UniformRandomBitGenerator
  >
  OutputIterator operator()(
    InputIterator first,InputIterator last,
    OutputIterator res,Distance& n,Distance& m, /* note the &s */
    UniformRandomBitGenerator& g)const 
  {
    for(;first!=last&&n!=0;++first){
      auto r=std::uniform_int_distribution<Distance>(0,--m)(g);
      if (r<n){
        *res++=*first;
        --n;
      }
    }
    return res;
  }
};

template<
  typename... Ts,typename Iterator,typename OutputIterator,
  typename Distance,typename UniformRandomBitGenerator,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
OutputIterator sample(
  const Iterator& first,const Iterator& last,
  OutputIterator res,Distance n,UniformRandomBitGenerator&& g)
{
  Distance m=algorithm::fast_distance(first,last);
  n=(std::min)(n,m);

  for(auto i:detail::segment_split(first,last)){
    auto alg=restitute_range<Ts...>(sample_alg{},res,n,m,g);
    res=alg(i);
    if(n==0)return res;
  }
  return res; /* never reached */
}

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
bool is_partitioned(const Iterator& first,const Iterator& last,Predicate pred)
{
  auto it=algorithm::find_if_not<Ts...>(first,last,pred);
  if(it==last)return true;
  return algorithm::none_of<Ts...>(++it,last,pred);
}

BOOST_POLY_COLLECTION_DEFINE_OVERLOAD_SET(
  std_partition_copy,std::partition_copy)

template<
  typename... Ts,typename Iterator,
  typename OutputIterator1,typename OutputIterator2,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
std::pair<OutputIterator1,OutputIterator2> partition_copy(
  const Iterator& first,const Iterator& last,
  OutputIterator1 rest,OutputIterator2 resf,Predicate pred)
{
  for(auto i:detail::segment_split(first,last)){
    auto alg=restitute_range<Ts...>(std_partition_copy{},rest,resf,pred);
    std::tie(rest,resf)=alg(i);
  }
  return {rest,resf};
}

template<typename Predicate,typename... Ts>
struct partition_point_pred
{
  partition_point_pred(const Predicate& pred):pred(pred){}

  template<typename Iterator>
  bool operator()(const Iterator& it)const
  {
    using traits=iterator_traits<Iterator>;
    auto p=restitute_iterator<Ts...>(deref_to(pred));
    return p(
      traits::base_segment_info_iterator_from(it)->type_info(),
      traits::local_base_iterator_from(it));
  }

  Predicate pred;
};

template<
  typename... Ts,typename Iterator,typename Predicate,
  enable_if_poly_collection_iterator<Iterator> =nullptr
>
Iterator partition_point(
  const Iterator& first,const Iterator& last,Predicate pred)
{
  auto_iterator<Iterator>               afirst{first},alast{last};
  partition_point_pred<Predicate,Ts...> p{pred};
  return *std::partition_point(afirst,alast,p);
}

} /* namespace poly_collection::detail::algorithm */

} /* namespace poly_collection::detail */

/* non-modifying sequence operations */

using detail::algorithm::all_of;
using detail::algorithm::any_of;
using detail::algorithm::none_of;
using detail::algorithm::for_each;
using detail::algorithm::for_each_n;
using detail::algorithm::find;
using detail::algorithm::find_if;
using detail::algorithm::find_if_not;
using detail::algorithm::find_end;
using detail::algorithm::find_first_of;
using detail::algorithm::adjacent_find;
using detail::algorithm::count;
using detail::algorithm::count_if;
using detail::algorithm::mismatch;
using detail::algorithm::equal;
using detail::algorithm::is_permutation;
using detail::algorithm::search;
using detail::algorithm::search_n;

/* modifying sequence operations */

using detail::algorithm::copy;
using detail::algorithm::copy_n;
using detail::algorithm::copy_if;
                      /* copy_backward requires BidirectionalIterator */
using detail::algorithm::move;
                      /* move_backward requires BidirectionalIterator */
                      /* swap_ranges requires Swappable */
                      /* iter_swap requires Swappable */
using detail::algorithm::transform;
                      /* replace requires Assignable */
                      /* replace_if requires Assignable */
using detail::algorithm::replace_copy;
using detail::algorithm::replace_copy_if;
                      /* fill requires Assignable */
                      /* fill_n requires Assignable */
                      /* generate requires Assignable */
                      /* generate_n requires Assignable */
                      /* remove requires MoveAssignable */
                      /* remove_if requires MoveAssignable */
using detail::algorithm::remove_copy;
using detail::algorithm::remove_copy_if;
                      /* unique requires MoveAssignable */
using detail::algorithm::unique_copy;
                      /* reverse requires BidirectionalIterator */
                      /* reverse_copy requires BidirectionalIterator */
                      /* rotate requires MoveAssignable */
using detail::algorithm::rotate_copy;
using detail::algorithm::sample;
                      /* shuffle requires RandomAccessIterator */
using detail::algorithm::is_partitioned;
                      /* partition requires Swappable */
                      /* stable_partition requires Swappable */
using detail::algorithm::partition_copy;
using detail::algorithm::partition_point;

/* sorting and related operations not provided */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* algorithm.hpp
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
*/