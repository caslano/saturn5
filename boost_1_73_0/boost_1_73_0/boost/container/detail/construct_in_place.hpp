//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP
#define BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/value_init.hpp>

namespace boost {
namespace container {

//In place construction

template<class Allocator, class T, class InpIt>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T* dest, InpIt source)
{     boost::container::allocator_traits<Allocator>::construct(a, dest, *source);  }

template<class Allocator, class T, class U, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, value_init_construct_iterator<U, D>)
{
   boost::container::allocator_traits<Allocator>::construct(a, dest);
}

template <class T, class Difference>
class default_init_construct_iterator;

template<class Allocator, class T, class U, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, default_init_construct_iterator<U, D>)
{
   boost::container::allocator_traits<Allocator>::construct(a, dest, default_init);
}

template <class T, class EmplaceFunctor, class Difference>
class emplace_iterator;

template<class Allocator, class T, class U, class EF, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, emplace_iterator<U, EF, D> ei)
{
   ei.construct_in_place(a, dest);
}

//Assignment

template<class DstIt, class InpIt>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, InpIt source)
{  *dest = *source;  }

template<class DstIt, class U, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, value_init_construct_iterator<U, D>)
{
   dtl::value_init<U> val;
   *dest = boost::move(val.get());
}

template <class DstIt, class Difference>
class default_init_construct_iterator;

template<class DstIt, class U, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, default_init_construct_iterator<U, D>)
{
   U u;
   *dest = boost::move(u);
}

template <class T, class EmplaceFunctor, class Difference>
class emplace_iterator;

template<class DstIt, class U, class EF, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, emplace_iterator<U, EF, D> ei)
{
   ei.assign_in_place(dest);
}

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP

/* construct_in_place.hpp
CO9vdwhQXg0h/wFQSwMECgAAAAgALWdKUlVYI3TuAwAAkggAADUACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19TUEVFRF9VUExPQUQuM1VUBQABtkgkYK1UbW/bNhD+rl9x07DBCVy5b0PbNSum2u4ixJEEy25mwIBAS6eIgyxqJJUXLP3vO1IS8go0HypDJkXe3XN87jl6WxcOf9jjeCYcfPdJ7ZvSQ+PgFEvxD2b6aYc0vYHuR45bGp8BNYFbr5v0AJ7ldQMj65X2WEdmnqbPgNuaJM3fxDhvUzOllc6z95+K5lry81LDaHoArz58eA8v4PXLV+/GMGM1xwoSjfUO5fkYjnK78mfJrq48hZ/GgBpY5d0LuCq5AiUKfckkAs0rnmGtMAemIEeVSb6jD16DLhEKXiFMo3gThH+N4bLkWdnHuRYtqFK0VQ4lu0CQmCG/6MI0TGoQBUWg+DlXmmK2movaI3gEjXKv+jAmCVYpAeyC8YrtCI5pKLVu1O+TSdbKik4yyUWmJtlAhVfq/YNTbSibPbsG0WjQAlqFYzD2Y9iLnBdmJIposWl3FVfl+DYtAqzziZCgsKr6cOTKUXVHQEh6tsbGEhrKnmszKFErg3ZZiv09Q6K1D1S0
*/