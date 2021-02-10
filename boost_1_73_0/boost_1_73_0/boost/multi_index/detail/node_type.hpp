/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_NODE_TYPE_HPP
#define BOOST_MULTI_INDEX_DETAIL_NODE_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/reverse_iter_fold.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <boost/multi_index/detail/header_holder.hpp>
#include <boost/multi_index/detail/index_node_base.hpp>
#include <boost/multi_index/detail/is_index_list.hpp>
#include <boost/static_assert.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* MPL machinery to construct the internal node type associated to an
 * index list.
 */

struct index_node_applier
{
  template<typename IndexSpecifierIterator,typename Super>
  struct apply
  {
    typedef typename mpl::deref<IndexSpecifierIterator>::type index_specifier;
    typedef typename index_specifier::
      BOOST_NESTED_TEMPLATE node_class<Super>::type type;
  }; 
};

template<typename Value,typename IndexSpecifierList,typename Allocator>
struct multi_index_node_type
{
  BOOST_STATIC_ASSERT(detail::is_index_list<IndexSpecifierList>::value);

  typedef typename mpl::reverse_iter_fold<
    IndexSpecifierList,
    index_node_base<Value,Allocator>,
    mpl::bind2<index_node_applier,mpl::_2,mpl::_1>
  >::type type;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* node_type.hpp
x7npV7Nr79Sri+1Xe3WbJFP6Haka9R5mDi3eCmDNwEIC1TqXep2up3A+DiaH4+nAg+6wxqimSIKMxKz/F9DxoHc0mJQ4z7vTCA7OpoPqVvV7/eO6iPtSTm5k1iNVinoUOnMRXI5yV+SjnNsrOcs57RXCfhCtysWaaKtJ/FixrR8k24aXL+EF3aVCu+Wd1tWVccXQzzMhLFek2nBjL0yRiTzbtUXU3qW1qt2x8cRud2W3uJyxQgxYmraq/srdcghV0UXj5eyxxTfuG/8BUEsDBAoAAAAIAC1nSlKr0l6mlgMAAGgIAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTEzLmNVVAUAAbZIJGCtVdtu4zYQfddXDLwvtqFacdpiL9kWlZ2s14grGbaMRYAAAi2NLbaUqJKUE6PZf+9QlyQNunUeVkFCiTxzzvDMkPGG3+9xYAgnn7j+jemhsY5YKvkHJua/0XH8AM0PRd3SeErEg6eQh3gAp0MeoF+HxK3KR/sex6eEbm1u9o9nI29j+0ozFGYjp7I8Kr7PDPSnAxi/f/8OfoDzs/MzFy5ZwVHA2mCxRbV34WNaz/yWsfv7kcZfXUADTIxaqijjGrTcmTumEOhd8AQLjSkwDSnqRPEtffAC
*/