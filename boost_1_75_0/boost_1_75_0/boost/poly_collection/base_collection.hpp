/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_BASE_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_BASE_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/base_collection_fwd.hpp>
#include <boost/poly_collection/detail/base_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Base,typename Allocator>
class base_collection:
 public common_impl::poly_collection<detail::base_model<Base>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::base_model<Base>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  base_collection()=default;
  base_collection(const base_collection& x)=default;
  base_collection(base_collection&& x)=default;
  base_collection& operator=(const base_collection& x)=default;
  base_collection& operator=(base_collection&& x)=default;
   
  template<typename B,typename A>
  friend bool operator==(
    const base_collection<B,A>&,const base_collection<B,A>&);
};

template<typename Base,typename Allocator>
bool operator==(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Base,typename Allocator>
bool operator!=(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y)
{
 return !(x==y);
}

template<typename Base,typename Allocator>
void swap(
  base_collection<Base,Allocator>& x,base_collection<Base,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::base_collection;

} /* namespace boost */

#endif

/* base_collection.hpp
6TXSNr+y/RpJj0JmV4lSdqpcXfntK0tNKZQn2VcLf2CsveOq72i8ncy14sNxy85L3FSxLzFyZnhmk3Z8gMYELLyRTjnkJvvcF3fv6pZ+O4oyTA6zPzphRaTpDf7UpdgW3kyvUeoBtZ0/28lYxG2k9uplxV8IbOA0cT1c63jH3fmsdhhlfn56vtTTewd4+SClNc798tZHqkV1Nd6i5jVtp6vdVSMGWm5XR/U4BbYH1o5s6Jf924W5bZsFTg+nybZw3f5zOu1L329aj7RmSTe0W7H1cwe8jnOrzo8iUVWRHg3iY76aGpa0eODioA0F77QNzqt8/TbS8AiYF33HeNObAy/nm+46eYLLXunyUVFw3yPZCfk9nfm7sOWIKzb/fZujJBN8UfI+XDPAluLUzwPeu3Vq9z9B+4QgfbcDJ4E2Uzaf0zCjzOo5ozBN/V4HflqvLb/MUm0LbyZL77ez4yqzWNi8p2iMqAjaTezF5PPiEAEuEN9VUIXvrsKv+6KXOG57chYv1b5nRVdF5MK5WZHOoYp+xl9d2Uw1l6hnhPtPnXged+xubVuiSXl2M/t+clloLqoIBKlarYLS/HMC2wnD585oqmii+wK4ROqXMTvz15cO8ZeWd7vErgLJakNF3PX1X78ckJ8kI/jmWOVmYVY+1wnIaFw0YOw0DsAU6f3kE40Iyw7f2HhHZboWEE5zf17DPWq4tLqUYq4eEGeU
*/