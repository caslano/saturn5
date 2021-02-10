/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RAW_PTR_HPP
#define BOOST_MULTI_INDEX_DETAIL_RAW_PTR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* gets the underlying pointer of a pointer-like value */

template<typename RawPointer>
inline RawPointer raw_ptr(RawPointer const& p,mpl::true_)
{
  return p;
}

template<typename RawPointer,typename Pointer>
inline RawPointer raw_ptr(Pointer const& p,mpl::false_)
{
  return p==Pointer(0)?0:&*p;
}

template<typename RawPointer,typename Pointer>
inline RawPointer raw_ptr(Pointer const& p)
{
  return raw_ptr<RawPointer>(p,is_same<RawPointer,Pointer>());
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* raw_ptr.hpp
j+rqsoGAzpnQDHltIrHq8BLdeLwEtTcvAzvmYo97/Tfj0H2oHvZ+CnFuO/9NZnySdTt29zAZcGMLqTqj4RteqgwCgUtbIm9E9Q9LATDOcnN1W7bJxvlug+HTqgvLbDV9CtZ25cYsw41+tWsqs8wFhV64CNa07sK1emd7VB1Nn7/feXVT1amqkFWSa+xaI7k7TtVO/wNQSwMECgAAAAgALWdKUoWlEVReBQAA2QwAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1MTcuY1VUBQABtkgkYK1WbZPaNhD+zq/YkpkOUOfgMv3QhJApAS6hofgGO71eex2PbMtYrbFcSz5Ce/nv3ZVlXuaS0s7E92Jb2n2efZf7vS93taAHZ6/A/AV44d1oXJfydx7pT0sHwQPUP6h1h/dzJH04qDwEXTiv8gAdoxJYlpf0HATniO7INvrXJ827gB5xBdVIcyKLXSnWqYbOpAuXz59/B0/h2eDZwIEpywXPwNM8D3m5duBlbFa+T9mHDxeKv3KAa2DZhYXyU6FAyURvWckBnzMR8VzxGJiCmKuoFCG+iBx0yiERGYeJe307X75xYJuKKCWQnaxApbLKYkjZPYeSR1zc1xgFKzXIBNURPBZKI2ClhcwvkJuD
*/