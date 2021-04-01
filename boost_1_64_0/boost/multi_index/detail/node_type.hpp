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
nKGiuP+og69emqrccsC1w92J7agZY2zp6pTIGLSxzZo8dKUu9PiOljrWqaQrwy3xCB7kgonhpt1S9roiWr1IATotKbohXjoq+zu3uRZVGWFP9jJ+ZaSGHwwuQL5xybREdSaW0Ks5sFrk185S82/+Hsi1ZuM3S/UU1eEDD015Q2KVKaFSIowt/HooJbSX1RnC0O4HYtNFw4jkfptREG3CCUNVMqwz9oMgo7j9NzR89jKMrfyinb4npld8SVppT22bcFdXgVmG23h+vepILn/TNyMWlryiToN8xg4PdRH+OeoP07GtNVW+84UNQI1rCTAssby1C23bJPFsweEFnPC9oO0+wd8JuEznWwPSto5gaJ5QfqEK268O1bCUegHlycjJ+w1Kqh3MoE9jFNaK9bg4+4Hzt1KU5/XTA4PXrIzao1Sp7q2HqJPrFvyf8ifsoVudA426ff0YEVwm0UcsIN4DV5of5jSOZSRFqDeBOGbjlvQByJcTjuSb/mlEK0g1w71mXIaEn0k3kEj8Nv4xtKpyxvCmJ1L84BwYRLZ2F8rAAPUZpc5aOMs1VFP8YA==
*/