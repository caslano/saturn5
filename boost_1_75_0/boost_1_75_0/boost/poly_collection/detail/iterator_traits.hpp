/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ITERATOR_TRAITS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <iterator>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace common_impl{

template<typename Model,typename Allocator>
class poly_collection;

}

namespace detail{

/* (Internal) bunch of traits-grouped functions for const-preserving
 * interoperatibility between iterators and local iterators of a
 * poly_collection.
 */

template<typename Iterator>
struct poly_collection_of /* to be specialized for iterator impls */
{
 using type=void;
};

template<typename PolyCollection>
struct model_of;

template<typename Model,typename Allocator>
struct model_of<common_impl::poly_collection<Model,Allocator>>
{
  using type=Model;
};

template<typename Iterator>
struct iterator_traits
{
  using container_type=typename poly_collection_of<Iterator>::type;
  using is_const_iterator=typename std::is_const<
    typename std::remove_reference<
      typename std::iterator_traits<Iterator>::reference
    >::type
  >::type;
  using iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_iterator,   
    typename container_type::iterator
  >::type;
  using base_segment_info_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_base_segment_info_iterator,   
    typename container_type::base_segment_info_iterator
  >::type;
  using local_base_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::const_local_base_iterator,   
    typename container_type::local_base_iterator
  >::type;
  template<typename T>
  using local_iterator=typename std::conditional<
    is_const_iterator::value,
    typename container_type::template const_local_iterator<T>,   
    typename container_type::template local_iterator<T>
  >::type;

  static base_segment_info_iterator
  base_segment_info_iterator_from(iterator it)noexcept{return it.mapit;} 

  static base_segment_info_iterator
  base_segment_info_iterator_from(local_base_iterator it)noexcept
    {return it.mapit;}

  static base_segment_info_iterator
  end_base_segment_info_iterator_from(iterator it)noexcept{return it.mapend;} 

  static local_base_iterator
  local_base_iterator_from(iterator it)noexcept
  {
    return {
      it.mapit,
      model_of<container_type>::type::nonconst_iterator(it.segpos)
    };
  }

  static iterator 
  iterator_from(
    local_base_iterator lbit,base_segment_info_iterator mapend)noexcept
  {
    return {lbit.mapit,mapend.base(),lbit.base()};
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* iterator_traits.hpp
HTJVihhHN0AM/WZecqFiev6bETMvTAEzL/DlhfdjuLKni0yJC7md4nr+x3JWYBO2mRcUxJkXCneZU5IsskoWhdW8NzErSI2tFSSJ0Ari9oxyZ0Q7YfRtbuslO+GAhTn5AHdS/jaufSYPup504A9J4YS+fbKCHE6o+TZ1UjBtFn2lxhLYc2ACIvQR3V/ukNOR3Evjyj5LoLXIVIUZMeBGCA7E/bt5o4sb4XPZQVsJuiyC2xcqfAYbJh7E3SUc4EKoJjb3hXC3TcLeLjsuyQX3dDpTo64abHy/vRZHXUXvgsFNSUan7kXXT++Zey1RAc8IuCZZEp77GAlDYoImeVFXrbtgzmEpGYAMN3LCKMFVZdTefKMTcpFA/2Gc62dhR1ojuetUotdZdFyxC15ItNtnH8JVjg0p4NkUpIfjW7AV6jMT5jdYtKFn+5yoq+RdMMkW+RfC0dTQFgQCwss4UdxtoTDItDnbANGTERV43B2dx/iPhlERFppzeNy3A/Izp3ARkmNyIO/wbm3gnnOFf1EU6zQAondOruBWkbtjJNDfpyW327EARBhAvXazMQjmQr12iTwlHJNuQYgiuic67d3YnB9LPSN/m68U3nDPjFLZzqt+dPvVSVQNtcc1yZcA+zazF8DCPx+2IYAJ7xyOKBCqBQ5ozL0F+kOQrXxYK2kId0OTZ3i9P+9+cfCVwGc5J028utWnruxyaecknv+K
*/