//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_POOL_COMMON_HPP
#define BOOST_CONTAINER_DETAIL_POOL_COMMON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/intrusive/slist.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class VoidPointer>
struct node_slist
{
   //This hook will be used to chain the individual nodes
    typedef typename bi::make_slist_base_hook
      <bi::void_pointer<VoidPointer>, bi::link_mode<bi::normal_link> >::type slist_hook_t;

   //A node object will hold node_t when it's not allocated
   typedef slist_hook_t node_t;

   typedef typename bi::make_slist
      <node_t, bi::linear<true>, bi::cache_last<true>, bi::base_hook<slist_hook_t> >::type node_slist_t;
};

template<class T>
struct is_stateless_segment_manager
{
   static const bool value = false;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_IMPL_HPP

/* pool_common.hpp
RwQ8omAr0gBRk7DfN1F+XpNuIc7u3gHjSeNskr+2HNz93nFQlhhkgLSqRW4FREgIZESj2SBqb9HsClpbAc0uNDoQNDWxTElIOcwSbg2PkcMhqAlCj2jIIVEQ0wy/T7OR0G1DtxOyvdWi1w1oRppGI6DZCLhy5WGkkISRCZYSwqyqlFaSGI1GJTtElUjk6yZWqBjL1JFFKy6FEFy8dMm1EQKhEOJR+wfAjevX/6KQUls1Y6S1vv3cd797Wym1l2XZgVJq+qEf+ZEvAftCiEPgSEp5iHF7zhqNxpkNl+tFAjrJ8QwwV0WeUHni3dY2u25fTtpfj/N/f+/bXN17DoD/8x+YMc6/r/39o79yc2WV+/u3+fLv/i5aCGQQkGUZaE0QhsxmMddv7BGnztO17ktZNUKc8YOcBPL23ODrBQTHBBgFUhGFgnYzY6cf8MgDmks7gu0B9PuCKIzQRGRZmyQdkGRXSDOIU0hSSDKYpJAmKeogId1NUWmM1EMiOSEKprSjI9rRVSI5pRWNaYRTep2Afq9Br9um027z2ONP0Gy2abWaBEGYGy2lDa8eDocLpQVY7qlwv46Yzy+bLp4tskVceuABhBBCSumkh4uuLlf2nWvXPp97NITIhBAZWsdK6/2XXnxx//1PPfVl4G0hxNtCiLeAl958882jJ554Yi0Pw2IC4BH2s4r+7zr3PwfOnz+v6XcxQRb0x8LIWwYc
*/