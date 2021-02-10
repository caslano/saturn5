/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP
#define BOOST_MULTI_INDEX_DETAIL_VALUE_COMPARE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/call_traits.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename Value,typename KeyFromValue,typename Compare>
struct value_comparison
{
  typedef Value first_argument_type;
  typedef Value second_argument_type;
  typedef bool  result_type;

  value_comparison(
    const KeyFromValue& key_=KeyFromValue(),const Compare& comp_=Compare()):
    key(key_),comp(comp_)
  {
  }

  bool operator()(
    typename call_traits<Value>::param_type x,
    typename call_traits<Value>::param_type y)const
  {
    return comp(key(x),key(y));
  }

private:
  KeyFromValue key;
  Compare      comp;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* value_compare.hpp
RVVaJzOrZdsLGZKypEVsoR2xZ3i/XjlLvHGXcKu3xMw18JY5uu2ILzn2NX0OdiSeMIxRUoW92GyKbVQfjYMQBxv0gel91208Gf0xt3H7F8aHiOXFkYjbIBjfus7Andi6xFPyn+5ee+KsNtWv4cz3bjx3cAxqNMWw82MVz8bDkYMt+vUxx4/u5Ho0dU/wNEUG87Fbm8yr0emkak8AuJt4gXsz8/uBN/JtSNaCKXokZoLJ9yHPmuoJO1yXNPN9d3gCP8+/wTYz9f5EBayMF8vW/3qcaXLy2T3F//WEi9xk0h6H5/tyd7Nr193V27nC4a1KBKUhFmbVp6vxzVu7b7QWtoEW8tFN9j9QSwMECgAAAAgALWdKUl9+gFC2BAAAGwwAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1MjYuY1VUBQABtkgkYK1WXXPiNhR951fc0BfDeCGbp27IduoQZ8MuxQyYTWnT8QhbxtralkeSIbTZ/94rGQdoNgsPawYsS+fec+6HZLrtH3c1oA1Hr8B8A7zwbizGgn+hofo2OgieoPqg1QPej5F0YWfyFLTguMkTWMYk2LJc6XEQHCN60Nr0T1dbPgR6iDNopi37vNgItkwUWP0WvH337md4AxfnF+c2
*/