/* Copyright 2016-2021 Joaquin M Lopez Munoz.
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

#include <boost/detail/workaround.hpp>
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

#if BOOST_WORKAROUND(BOOST_GCC_VERSION,>=90300)&&\
    BOOST_WORKAROUND(BOOST_GCC_VERSION,<100300)
/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95888 */

public:
#else
private:
#endif

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