/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_DEFAULT_HEADER_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_DEFAULT_HEADER_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>

namespace boost {
namespace intrusive {
namespace detail {

// trivial header node holder
template < typename NodeTraits >
struct default_header_holder : public NodeTraits::node
{
   typedef NodeTraits node_traits;
   typedef typename node_traits::node node;
   typedef typename node_traits::node_ptr node_ptr;
   typedef typename node_traits::const_node_ptr const_node_ptr;

   default_header_holder() : node() {}

   BOOST_INTRUSIVE_FORCEINLINE const_node_ptr get_node() const
   { return pointer_traits< const_node_ptr >::pointer_to(*static_cast< const node* >(this)); }

   BOOST_INTRUSIVE_FORCEINLINE node_ptr get_node()
   { return pointer_traits< node_ptr >::pointer_to(*static_cast< node* >(this)); }

   // (unsafe) downcast used to implement container-from-iterator
   BOOST_INTRUSIVE_FORCEINLINE static default_header_holder* get_holder(const node_ptr &p)
   { return static_cast< default_header_holder* >(boost::movelib::to_raw_pointer(p)); }
};

// type function producing the header node holder
template < typename ValueTraits, typename HeaderHolder >
struct get_header_holder_type
{
   typedef HeaderHolder type;
};
template < typename ValueTraits >
struct get_header_holder_type< ValueTraits, void >
{
   typedef default_header_holder< typename ValueTraits::node_traits > type;
};

} //namespace detail
} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_DEFAULT_HEADER_HOLDER_HPP

/* default_header_holder.hpp
xu/3B90g34jtbc7SPT5qHbVeHb06/qV13GlHnbG89svc61rRnKpuq/V99d/tXDcm3xfffP/WO379fbvA7532sloubYjOVSrWooHJRZXnB8tSDx17TKtYlsqliphOJ1U41M2/BubYJlNiuppRuHP+nkZbxfKtLKabiVUXHNGL2SZ69Lw5lTCeObSn4GhetkDYWE6vjtdIXtYkYRxnqJhhDEVkVAufl1MzlYXPy1GqcB7L6Z0uazRHda608ZzezTJHtJx5OcXvET4v7yoibCyXOy/vdkzCOC5vXg79lkrKrJzwGyUpc3JYkRJGcVKHyxzF4Y6VOoqTuljeKJY3E8dGOKXMw5tqCBq/5c/Bm50SPnbLmX93fi0tJVqR8CtkKbGKUufftA6X6d0Jmn/TuljeKJYXoYhdv5QSnyhx/k3ubPmjV0BkIr57pY3c6F0+5M1+Me0p3bwx9YrSXfIdG9ka0ZqLGelR2ypJf/hI3a5I+g0ZKVvJM3y6KqKGaGTvhaEgXQehN40azzopGZXS59IIyaTdLmLn84ieK3CrlEeXxO0OZa55S3iWSq5ZnPrSV2iFP1El1Vu+7so8VeXcx1WB21PUk1VeZcQNVvFPV3m1EHwDqZLvouIzVqpsEm8d0bO86CetfDoIip1E7xUv
*/