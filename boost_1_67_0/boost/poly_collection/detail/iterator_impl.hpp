/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ITERATOR_IMPL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ITERATOR_IMPL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/poly_collection/detail/is_constructible.hpp>
#include <boost/poly_collection/detail/iterator_traits.hpp>
#include <type_traits>
#include <typeinfo>

namespace boost{

namespace poly_collection{

namespace detail{

/* Implementations of poly_collection::[const_][local_[base_]]iterator moved
 * out of class to allow for use in deduced contexts.
 */

template<typename PolyCollection,bool Const>
using iterator_impl_value_type=typename std::conditional<
  Const,
  const typename PolyCollection::value_type,
  typename PolyCollection::value_type
>::type;

template<typename PolyCollection,bool Const>
class iterator_impl:
  public boost::iterator_facade<
    iterator_impl<PolyCollection,Const>,
    iterator_impl_value_type<PolyCollection,Const>,
    boost::forward_traversal_tag
  >
{
  using segment_type=typename PolyCollection::segment_type;
  using const_segment_base_iterator=
    typename PolyCollection::const_segment_base_iterator;
  using const_segment_base_sentinel=
    typename PolyCollection::const_segment_base_sentinel;
  using const_segment_map_iterator=
    typename PolyCollection::const_segment_map_iterator;

public:
  using value_type=iterator_impl_value_type<PolyCollection,Const>;

private:
  iterator_impl(
    const_segment_map_iterator mapit,
    const_segment_map_iterator mapend)noexcept:
    mapit{mapit},mapend{mapend}
  {
    next_segment_position();
  }

  iterator_impl(
    const_segment_map_iterator mapit_,const_segment_map_iterator mapend_,
    const_segment_base_iterator segpos_)noexcept:
    mapit{mapit_},mapend{mapend_},segpos{segpos_}
  {
    if(mapit!=mapend&&segpos==sentinel()){
      ++mapit;
      next_segment_position();
    }
  }

public:
  iterator_impl()=default;
  iterator_impl(const iterator_impl&)=default;
  iterator_impl& operator=(const iterator_impl&)=default;

  template<bool Const2,typename std::enable_if<!Const2>::type* =nullptr>
  iterator_impl(const iterator_impl<PolyCollection,Const2>& x):
    mapit{x.mapit},mapend{x.mapend},segpos{x.segpos}{}
      
private:
  template<typename,bool>
  friend class iterator_impl;
  friend PolyCollection;
  friend class boost::iterator_core_access;
  template<typename>
  friend struct iterator_traits;

  value_type& dereference()const noexcept
    {return const_cast<value_type&>(*segpos);}
  bool equal(const iterator_impl& x)const noexcept{return segpos==x.segpos;}

  void increment()noexcept
  {
    if(++segpos==sentinel()){
      ++mapit;
      next_segment_position();
    }
  }

  void next_segment_position()noexcept
  {
    for(;mapit!=mapend;++mapit){
      segpos=segment().begin();
      if(segpos!=sentinel())return;
    }
    segpos=nullptr;
  }

  segment_type&       segment()noexcept
    {return const_cast<segment_type&>(mapit->second);}
  const segment_type& segment()const noexcept{return mapit->second;}

  const_segment_base_sentinel sentinel()const noexcept
    {return segment().sentinel();}

  const_segment_map_iterator  mapit,mapend;
  const_segment_base_iterator segpos;
};

template<typename PolyCollection,bool Const>
struct poly_collection_of<iterator_impl<PolyCollection,Const>>
{
  using type=PolyCollection;
};

template<typename PolyCollection,typename BaseIterator>
class local_iterator_impl:
  public boost::iterator_adaptor<
    local_iterator_impl<PolyCollection,BaseIterator>,
    BaseIterator
  >
{
  using segment_type=typename PolyCollection::segment_type;
  using segment_base_iterator=typename PolyCollection::segment_base_iterator;
  using const_segment_map_iterator=
    typename PolyCollection::const_segment_map_iterator;

  template<typename Iterator>
  local_iterator_impl(
    const_segment_map_iterator mapit,
    Iterator it):
    local_iterator_impl::iterator_adaptor_{BaseIterator(it)},
    mapit{mapit}
  {}

public:
  using base_iterator=BaseIterator;

  local_iterator_impl()=default;
  local_iterator_impl(const local_iterator_impl&)=default;
  local_iterator_impl& operator=(const local_iterator_impl&)=default;

  template<
    typename BaseIterator2,
    typename std::enable_if<
      std::is_convertible<BaseIterator2,BaseIterator>::value
    >::type* =nullptr
  >
  local_iterator_impl(
    const local_iterator_impl<PolyCollection,BaseIterator2>& x):
    local_iterator_impl::iterator_adaptor_{x.base()},
    mapit{x.mapit}{}

  template<
    typename BaseIterator2,
    typename std::enable_if<
      !std::is_convertible<BaseIterator2,BaseIterator>::value&&
      is_constructible<BaseIterator,BaseIterator2>::value
    >::type* =nullptr
  >
  explicit local_iterator_impl(
    const local_iterator_impl<PolyCollection,BaseIterator2>& x):
    local_iterator_impl::iterator_adaptor_{BaseIterator(x.base())},
    mapit{x.mapit}{}

  template<
    typename BaseIterator2,
    typename std::enable_if<
      !is_constructible<BaseIterator,BaseIterator2>::value&&
      is_constructible<BaseIterator,segment_base_iterator>::value&&
      is_constructible<BaseIterator2,segment_base_iterator>::value
    >::type* =nullptr
  >
  explicit local_iterator_impl(
    const local_iterator_impl<PolyCollection,BaseIterator2>& x):
    local_iterator_impl::iterator_adaptor_{
      base_iterator_from(x.segment(),x.base())},
    mapit{x.mapit}{}

  /* define [] to avoid Boost.Iterator operator_brackets_proxy mess */

  template<typename DifferenceType>
  typename std::iterator_traits<BaseIterator>::reference
  operator[](DifferenceType n)const{return *(*this+n);}

private:
  template<typename,typename>
  friend class local_iterator_impl;
  friend PolyCollection;
  template<typename>
  friend struct iterator_traits;

  template<typename BaseIterator2>
  static BaseIterator base_iterator_from(
    const segment_type& s,BaseIterator2 it)
  {
    segment_base_iterator bit=s.begin();
    return BaseIterator{bit+(it-static_cast<BaseIterator2>(bit))};
  } 

  base_iterator              base()const noexcept
    {return local_iterator_impl::iterator_adaptor_::base();}
  const std::type_info&      type_info()const{return *mapit->first;}
  segment_type&              segment()noexcept
    {return const_cast<segment_type&>(mapit->second);}
  const segment_type&        segment()const noexcept{return mapit->second;}

  const_segment_map_iterator mapit;
};

template<typename PolyCollection,typename BaseIterator>
struct poly_collection_of<local_iterator_impl<PolyCollection,BaseIterator>>
{
  using type=PolyCollection;
};


} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* iterator_impl.hpp
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
*/