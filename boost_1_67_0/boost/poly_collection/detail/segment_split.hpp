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