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