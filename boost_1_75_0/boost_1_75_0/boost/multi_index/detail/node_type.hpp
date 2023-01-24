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
NvvSDN+Ry11fj0IGsbN96TSLy750XUq9NwauI+F6bQosbU6t8rwVPqB6r0aZvctXZyFRpNZY6TXEDom7H6M5OFKtMtrK3SaNfhZy16JKf/3rhs9ZDJ+7mD+Xhp/LStlifDch7GNT9I8djeSPuQNkaYbxpUZGo7Hdd/T4yquhIrdzgJ5dQ13A7D8UGyfjZvvSSDN0hWPjlGNEqJwDyj8jtfbn4hSrRW2hQXx/GIKqXCnfVo9349qgxjHqieJ6FDfMuIH6NiaSuQxFsCBTziO+Zdz7wVjGvcsY9+YbTUSwwSWTBNmFe8C1vDcB4kUMiL931vRbeYf5KKutYwajpo7prBy5mpOnV34dYaqLeQ0DrxMfrtnxDa7VTeRSKZ7/7sbx/Fefs5hWUzz/hxrF89/0aoSI548m9elo+Y0RaiR/R13/n2zSkhiyIR8F7P98jGZMT4Z8utt7WOh/OBeieSD6OOSvYBw3v4rj0MsG4dguf1Ubm02M7RRKKuJ++DHKJO9hc/QM609w5+3swrhkcYvhWml7ApWLcV/BNdbJkoSCOEuu9MjtYe/A1vOwi1i6JGvG4CQ5Myj78FgqZp2DemseO5zwuAJxbmi67tWjZ1SOQ+OWd8MJFA2nlGVWcBAGXYhehsds0AnduBrqpmE6Wewj4Ka4WOzjvX9RHxOwj36Y37h2orci1iOfgndWNvAHNOgOWZJlHbNTF9Oh4Ics
*/