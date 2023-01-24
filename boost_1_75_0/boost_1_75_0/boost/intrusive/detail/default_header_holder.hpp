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
W4dm6xa6YSLenQHFYXlUxMrQHcU7wmsc3ti4lY8cO+hufP1lat+o1H4/O1XqoOnG8R2tTg30vB9Kxu/EiRIt/d6TPwtCwbiXwcAgikaXjJV0IUOWlujy1Vv740N8jnqwNMZjmIpvZ1SbFwhuU8gPvXJfKpbwYwF98QXL4gsjjwPei7u+8iyTYOgEOSUui/AfsQN5BI/zLPSJZzw5VLykXFj9dGbLgjbUG4H+Rkp9nCk+wkQ3F/0f1+hyqn5xZSfshVfu66ynb48yWoYcVv/+3cJlVTvlE28//HgzL7kR2bJij5q5LmQjNKbhKFDHZdIqZ95cnZubi00bdyGyPM9ZuCOqoQFgD3f2bqGiEjFjMcHrmCq1vGMQJOKaSndG/dJooNHFS4AO3/5HH3ibMdxWeNqX05ux9gPNWVIpCp4Sqm4/nYzNxQqzO82xnkOUvs/5tcMaAdd+US8FeT9Xh3UyyYmtvVmg4hh5YpUvv8dr24X9LdoT3LkhXPtEb34QOsD3NbC707aZZfrTJu7mXJUFhHdIIGwQSwGtzW57zvC3GoPzrOCc/fDOwcTjBgzlT9acnqN0MGdX04NxZPr1bxf58hkUoyGDMbXLpSy4oe2VP60HtjvM/eG73LQwVuWaGxvdo0FLh2u7tra3vUS5yakCNjHeS4mpGojywMNpF2M1hcMe1Di9j0m0uspePXFKT1EazCw6mAdU54Rs7gw/
*/