/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2009-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_IS_STATEFUL_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_DETAIL_IS_STATEFUL_VALUE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1310)

#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct is_stateful_value_traits
{
   static const bool value = !detail::is_empty<ValueTraits>::value;
};

}}}

#else

#include <boost/intrusive/detail/function_detector.hpp>

BOOST_INTRUSIVE_CREATE_FUNCTION_DETECTOR(to_node_ptr, boost_intrusive)
BOOST_INTRUSIVE_CREATE_FUNCTION_DETECTOR(to_value_ptr, boost_intrusive)

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct is_stateful_value_traits
{
   typedef typename ValueTraits::node_ptr       node_ptr;
   typedef typename ValueTraits::pointer        pointer;
   typedef typename ValueTraits::value_type     value_type;
   typedef typename ValueTraits::const_node_ptr const_node_ptr;
   typedef typename ValueTraits::const_pointer  const_pointer;

   typedef ValueTraits value_traits;

   static const bool value =
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, node_ptr, to_node_ptr, (value_type&) )))
      ||
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, pointer, to_value_ptr, (node_ptr) )))
      ||
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, const_node_ptr, to_node_ptr, (const value_type&) )))
      ||
      (boost::intrusive::function_detector::NonStaticFunction ==
         (BOOST_INTRUSIVE_DETECT_FUNCTION(ValueTraits, boost_intrusive, const_pointer, to_value_ptr, (const_node_ptr) )))
      ;
};

}}}

#endif

#endif   //@ifndef BOOST_INTRUSIVE_DETAIL_IS_STATEFUL_VALUE_TRAITS_HPP

/* is_stateful_value_traits.hpp
Zm7hxU0ftSQmUlRmRJfq88Pzphnh4xh3peuAq5cfPjWNDFpg3lK3YIyDuyYPg8Vxh0rvJzttDlD1H7bOau+hxY1cUNbLTIoDl31Zsg3HhfjmSRL4j2MdgAoEEUculzuy3jLfovYO3bzQTE2mg2vD+eDN+zJbimO73Izdrq/eOAzfe3tJM1082y9XG5tY/xyAJEj86fhJSD9QRuvOagOLMExvyLolBOWv7fNQVWGYsw+hxtjGERvhXWTYS1fYA0TXXOf96zXNY1R0x1kasPaRmJHDvmZFVpzq+Ol9/gVqQDQjXDlJAN4c2/cCKy3CebJmfoXtfTu1cKXn9yz0XxW9vMjzpX0o1t+XkE+Ge5x4voYcqX4HNJU6xH17cnvZEtqOBP0FM2Vpp9GofYi6cPgFferWrXxtpAVBGZPhYWG4oYCGUIeexwdV3wuHKmmY4KWtEWxDWuSTAG4X3ktS+5Jhweubat8HA8WseVrQXcI1MGQrGup3Wi0M6riWGiY7BUTuAeWBLAsscPcweNTrv8hpdIf+Sobzj23v/01OXs7/XGHz/rcrbExE5JH0uMCwHnwS5LVFDPSouCaq+j60H7TIJHv78i/xuR1rQP8XImq0KU0zgYxYPgTVoyZSXmeLU36eCHqntdfS8uEcJ7DvGj1U0DrTNbPFtXSeVllapFpTZDP3xauj0hxPP8UiMWNd5LDLZ1rsIfvvz+H6w7nP
*/