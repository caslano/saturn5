/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_ANY_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_ANY_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/any_collection_fwd.hpp>
#include <boost/poly_collection/detail/any_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Concept,typename Allocator>
class any_collection:
 public common_impl::poly_collection<detail::any_model<Concept>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::any_model<Concept>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  any_collection()=default;
  any_collection(const any_collection& x)=default;
  any_collection(any_collection&& x)=default;
  any_collection& operator=(const any_collection& x)=default;
  any_collection& operator=(any_collection&& x)=default;
 
  template<typename C,typename A>
  friend bool operator==(
    const any_collection<C,A>&,const any_collection<C,A>&);
};

template<typename Concept,typename Allocator>
bool operator==(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Concept,typename Allocator>
bool operator!=(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y)
{
 return !(x==y);
}

template<typename Concept,typename Allocator>
void swap(
  any_collection<Concept,Allocator>& x,any_collection<Concept,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::any_collection;

} /* namespace boost */

#endif

/* any_collection.hpp
oEYiWQt56WPLa3AF3c3FtCNbeUNZPhO5BGZoUSMUty2XO0vIMiG7GoV859qYa5HyKeHzYWBDe7Rhbp3bneXcyeC+c6o1ZdT7rw3wi0bM5dLJRKwI7W82QzYWbX6M/hyDXbozxIGk12kkvngt12u+Me9P0QZC5TYlCoHhmab4K09bXIvTyFWDQl/6OvjHjRqws7X942gT362+c3axiQP9GIMdyDskdA2i6+huMdv3i9leiOHS+/bwYDLZP5nEJ5O940nb3lRT8VlQUc/hpFG/Sz0bOK+HmInD8xIqQ2YMay4yc8CvaN3/PKPDt+PxMokU5orW3XWFwLVqg8nN0rq7NhTcMzDGIFdEgfj6GlKXoYTr2hqF/h0GrVzrEjI5xK5ou6bfVPuZDbMZU43ooOB420oYG3ULOfhd59n62+aPrAuFqgw1EsJMo7ggiRsUA1kJP/ByIhFnwYAB2NwlRU8bXHfp4UM1dAnk8T7fbW9DInbRJw//e3U6CruLSNBgfWXTC+tizTuqmGnfhVf308LEvoGs49bvuzlq3a3GKvVrU61zKiuNiZ3NmwFW6XdCHJMmsn4gCqao2eAHXmxcvnMW85thYgpj1ttJfPQqfr3/+uj4nae4dldkQoICygM9+TzLEJfcdzC46YLrzArr
*/