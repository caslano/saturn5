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
+eF65AkJHZEvZ4jST2yHvHRd/Cu/uRz8W5eOBLQOCPBoTRwNWeUa6OMYqa/vTkAiS9FDYwwa1yy3B3b9xWvprzaikaWAuCBocg4bTwhiPr2EvvS0c9QPWzac4UMtHo7SOV57aotllZrj+unBe8YjVSFHol7Pf2e3xqOIDS6fFNS8pdE5L/8gzNijJU8kCvHm3joKc+CB8uOl7amUmewIqLEviNdnEhAwOJFm7c6GaY0SLZ0THkd7iQgU3EKS71nMAqp5Lvk/R9EBspkp5doJ202F5aF7AmjQT3W4HkG+ZblSQz0uQE3sCmcwDHQ/md7LVGAZYwE6LY84O0mhS6vxTMzXoM+tffEoNI/jwZu2VRJSe38h/5XPnucHiJ7NjVaHME25iOXj5gGIMz1Ra8VoA3xEpd4yZzhKSxbqntNcU5J6PSeRSmV8H8uE4H9jDmWL5sMQ8IvzHRpWA4I8Nje7uw1A2F350sQsAM2W3LTMyj3ZfaSJcjsqExnzMS8xxfeVJARoo7Z+9eeD7OfmbgHCOv9a/eDJ+lJJS9viXb0Ct8qFSkayhBGUfyKx4Q==
*/