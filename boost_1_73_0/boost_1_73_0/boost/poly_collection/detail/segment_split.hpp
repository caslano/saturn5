/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_SEGMENT_SPLIT_HPP
#define BOOST_POLY_COLLECTION_DETAIL_SEGMENT_SPLIT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_facade.hpp>
#include <boost/poly_collection/detail/iterator_traits.hpp>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* breakdown of an iterator range into local_base_iterator segments */

template<typename PolyCollectionIterator>
class segment_splitter
{
  using traits=iterator_traits<PolyCollectionIterator>;
  using local_base_iterator=typename traits::local_base_iterator;
  using base_segment_info_iterator=typename traits::base_segment_info_iterator;

public:
  struct info
  {
    const std::type_info& type_info()const noexcept{return *pinfo_;}
    local_base_iterator   begin()const noexcept{return begin_;}
    local_base_iterator   end()const noexcept{return end_;}

    const std::type_info* pinfo_;
    local_base_iterator   begin_,end_;
  };

  struct iterator:iterator_facade<iterator,info,std::input_iterator_tag,info>
  {
    iterator()=default;

  private:
    friend class segment_splitter;
    friend class boost::iterator_core_access;

    iterator(
      base_segment_info_iterator it,
      const PolyCollectionIterator& first,const PolyCollectionIterator& last):
      it{it},pfirst{&first},plast{&last}{}
    iterator(
      const PolyCollectionIterator& first,const PolyCollectionIterator& last):
      it{traits::base_segment_info_iterator_from(first)},
      pfirst{&first},plast{&last}
      {}

    info dereference()const noexcept
    {
      return {
        &it->type_info(),
        it==traits::base_segment_info_iterator_from(*pfirst)?
          traits::local_base_iterator_from(*pfirst):it->begin(),
        it==traits::base_segment_info_iterator_from(*plast)?
          traits::local_base_iterator_from(*plast):it->end()
      };
    }

    bool equal(const iterator& x)const noexcept{return it==x.it;}
    void increment()noexcept{++it;}

    base_segment_info_iterator    it;
    const PolyCollectionIterator* pfirst;
    const PolyCollectionIterator* plast;
  };

  segment_splitter(
    const PolyCollectionIterator& first,const PolyCollectionIterator& last):
    pfirst{&first},plast{&last}{}

  iterator begin()const noexcept{return {*pfirst,*plast};}

  iterator end()const noexcept
  {
    auto slast=traits::base_segment_info_iterator_from(*plast);
    if(slast!=traits::end_base_segment_info_iterator_from(*plast))++slast;
    return {slast,*plast,*plast};
  }

private:
  const PolyCollectionIterator* pfirst;
  const PolyCollectionIterator* plast;
};

template<typename PolyCollectionIterator>
segment_splitter<PolyCollectionIterator>
segment_split(
  const PolyCollectionIterator& first,const PolyCollectionIterator& last)
{
  return {first,last};
}

#if 1
/* equivalent to for(auto i:segment_split(first,last))f(i) */

template<typename PolyCollectionIterator,typename F>
void for_each_segment(
  const PolyCollectionIterator& first,const PolyCollectionIterator& last,F&& f)
{
  using traits=iterator_traits<PolyCollectionIterator>;
  using info=typename segment_splitter<PolyCollectionIterator>::info;

  auto sfirst=traits::base_segment_info_iterator_from(first),
       slast=traits::base_segment_info_iterator_from(last),
       send=traits::end_base_segment_info_iterator_from(last);
  auto lbfirst=traits::local_base_iterator_from(first),
       lblast=traits::local_base_iterator_from(last);

  if(sfirst!=slast){
    for(;;){
      f(info{&sfirst->type_info(),lbfirst,sfirst->end()});
      ++sfirst;
      if(sfirst==slast)break;
      lbfirst=sfirst->begin();
    }
    if(sfirst!=send)f(info{&sfirst->type_info(),sfirst->begin(),lblast});
  }
  else if(sfirst!=send){
    f(info{&sfirst->type_info(),lbfirst,lblast});
  }
}
#else
template<typename PolyCollectionIterator,typename F>
void for_each_segment(
  const PolyCollectionIterator& first,const PolyCollectionIterator& last,F&& f)
{
  for(auto i:segment_split(first,last))f(i);  
}
#endif

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* segment_split.hpp
I7wZrBs+En0aYbm4T+t8CNyn/Ar6N6E3LWDXkk0hZ0oMN4bgotRjIUFYjuRoQ8MzZNQTyAl5hcYDe8d6YT3Tmn/QKtQxsF8YmhkJcS7StCK7QRfAhKomtb9HPIeXQS4GW46hZ/RGAGIGfC58mszVT+K6v2hqdARWDn3yqL/jEFF4QhSDVmhyKvpA9UTYh/TpRFaOqMrZFKK3Z7gBySHPTGW9wCr8hW3yOQJJOeBTpJA0ZSzc4Pct9DxkZ1iF9HWCRwzJGsBXiurg61T2M1gptAB7H3ShREdD6CWu8MlDytaxk5YOuvV5mWcoC2jHgn0d9NajzKX0kWd/fnF29sOrlzc3k+ub2+ub5Psb3ct/3+l/kxW75faL8tF8vSq26Gv/6V32Rn2lzvnRxd90t/vePw/HZqtFy9gi/z1b359X9xd6WrHd7OZble42y9tsVrxXny5m21k5e14/uc1X+fb8ohqcr7Yqr2/u3m8zfX9//l/VnIuz6hcB5BcJ/HKNSlZSAgP4d9vNbL69rZDnq/v1eTWrZMqlKtd2qUqiL/Ss+1m+vN2tlllRnNcQvtr/xsGletEITTBnC5VtNuvNC8C6+lTN1ON6vVFvZ6v/LtT97vffq98XWN+rYv02U9Xa8tlS6UVv1+WoXzJV7DaZ
*/