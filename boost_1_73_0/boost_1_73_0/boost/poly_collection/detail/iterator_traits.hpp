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
+flJXTikxs1bG+Rh5foUVzpKheNHZ8p67q6mzvVA39BIwtr9cYR3Y9PwENs+HwevI+K7uyMZEWzXe8eyQobH8dfJRjvGfFdfakxPwiPr9dz8T6RJPvkZ+XhMOOiMx6LM3V+SF3lGvNT3EqF41Z4Fm+2D4xjXXzjvd/0B5RZ7fabMnq2fsyzLp7V7H1e+NFuurq9xra7m4vF8zc0GGFtwSOu+3uRbOI6v6DgGwHvKio6tJ23gH1dhIoO7TzWXI1Bb9jO8b+G6g2WNTVUWyodkrJMlCm8iM0Y0i+g7uR/sOxTzToZjKme1NTzKziTz4x1pl71/vZ+i/S9bv+VrWvL0xrzfqTeFrKXdY92ggT6uu3JGxhU0tmI3748teQzNvKfuQiL7/SZ3L8qZM0N1onNT/sfrteKYEyOtahRHl5oK8gcnNGJsYFiRi/PdiesPuvhNvLPWWEV141uXKipF/n3llNb7USqnyvi/p1a/9tXSPX7E1/r8yKpB4QpeJxavD/nQ7v/8ZqyWbLrlISzfLn5keog5orcy9/kfc8LJUjtZoO/Cs6pfXJ1jqxseSjyydz7kD1qtrm2NTZjdemcbbtJ5WWPSgIf9gVslohjUkDM18YTjRztXTvJkb4Et8ng2rZy/PIuLiGyhpS+NJwWn
*/