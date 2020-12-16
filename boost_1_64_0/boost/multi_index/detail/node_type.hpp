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
wNiWnnw/m8aD77dUttDJIy7QnK2khfDJF6Tqe2lbp3HKQEkd14k1hrZrMUm++4BvFeczedmvXyDSi3Kc+PEEvVZuZV0rGcN6MLb1vt/LpomY88o4KOv4rVBz9gk1Ofk8cE95yBWs73tsTZQrF6AZ3Hrn/SXvqXjn7yhvyqQtuIP5qYmDXQzeaTov7xVRLjVnxjZ805vZdDr4fpeIfj3zEZy7fUajk/DO5Xd3JfOcca81JeEKtjnuDE0xvpdk0+BUzbfyGl86Zgvs4c9peiJ0eqLW6as4dXp1TThSV9xYL4MkmA7b4inY/oKnsk29tXZ1C6By9W2ayy+oORV6LkXLfDunzOsnnFhbGmUGwZCwfapPZtMC6L33lZtocyLyWX1JHU48ZwLyvG1nlwWZaIkZhjgKZh8wN5v+gn/9AyLa59njUcP8K8qDr6B/BurJeIBBiB0DUIifD2dm06uQgw+JaI89u/VwspS0wOYd0l1jMJUfg3GhamYM4iiYuXBiNqUBg4+IaOClfVB/72vqDm9iawpyU/BjEGLXi6BgxSQdnU0rgcEKItr5ll7lmstvaBR86pSsMdjgBQa17BgYCsYeOjSbCBh8rHwk+bnwm31Lg1MwK7DnGfQPPwbsOjGOgtn3DcimzdCJK1UU9+Wn427Ud5QEn1kRdOIYDzBg1wegYMWm9c2m44GBsgDS1z19q+ZyNRUkwS6GHLR4gEFZiBsDUIjHoE9sb/CJtTdYQ3nJsbuCOyksOG3kahU5F2HK62YGt/3Gkncnfv1TtQp8PxuxSN9Tf3Bajn1R2lWcNqJ8vHAZ011RM7jtB+gT8wN8pqzB9ucm4Uak8Y0WIE9TO6vsy8cLVTHtjszgti+0ZzZVgndVUC48t2x/3fuD9PnAG5KM/fDPvLyz8e3eE2Zlmzhc5fC56Kxtubr3R2pOxF4Ye8I02peR53BoWOc/fFmOLRJu329mtsl7rYKtHopuG6h715n6u/Mw58tZ373zkHxpry0S7vNTXwyHr9QtlePO+lP3ru9ShzifVx5y1YcTBUPA7fteF6QxWP9Vrsa6jStG696f6LBk4wPuPB9q9AIDzinhomBizyQGjhx8bcnBz13kYCEvBiPUh1MObAIUdxYQk4NvLDn4xchBW4qWg7VeYMApBy4KRi++FqTlkINv1W3fM265G1WzaAr2A0vSdU62qZw52arKS+vKO/9lik23CNh+8iVBOhcYfKeq5Gytj+jeX6kpCWgkwWfIuTY4jyjPb0rrmfzl/0HD4PB0kPKBw2p1SrBhJDJYbqRV2B83oa5gzlJGu7gyPLa4vqpuqIwNZIql6ELBrI9PBU3swBorduA3Gu3KY9pfMOoE+YTqwxc3YBGw72osCFIx/CTfE1FowMiFuncTrYKdnAM52MotB+WVYUYZMKMbn/EdQboE73+tqoDx7PKHNXe/04he8Jv7EW/IGV/Gd0pqRja+gDlB+hjvW+UP6v3hVWdrrjbToESTL6fzb4sWM77vinCktLiCMd2/RcDOX3xd0NS++FHtBX55ep3u3dKl9kWOBxgw1r7oQsH4BmYGKQmxQor5ufM/QB2YrbTMya2Gv230AAO2kgf2+IZ/uipoan+sV5Ew3w36SnP4R5faHy0e8M9Y+yOegi0DoaCp+fCTup330WxYQNsojN8GJeq/bfUCA66SD67xzVnROUF6Hvr/Z4XHiXNxUvgnjUmDLkzTdQ7yf2W0BcurS0PqHyb2zfBuW3h0kKaA/19UNv/GfhN07180HTZgMBXx1Ycxrn94QM4a2xYJtw10WtDEWG9QvrGirZfq3r9pYFIsPq630gXLGOcBHpKzXpxFwu03OzpIg7Em/NoZL7M=
*/