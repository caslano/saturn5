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
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
*/