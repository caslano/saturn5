///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATION_TYPE_HPP
#define BOOST_CONTAINER_ALLOCATION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
enum allocation_type_v
{
   // constants for allocation commands
   allocate_new_v   = 0x01,
   expand_fwd_v     = 0x02,
   expand_bwd_v     = 0x04,
//   expand_both    = expand_fwd | expand_bwd,
//   expand_or_new  = allocate_new | expand_both,
   shrink_in_place_v = 0x08,
   nothrow_allocation_v = 0x10,
   zero_memory_v = 0x20,
   try_shrink_in_place_v = 0x40
};

typedef unsigned int allocation_type;
#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
static const allocation_type allocate_new       = (allocation_type)allocate_new_v;
static const allocation_type expand_fwd         = (allocation_type)expand_fwd_v;
static const allocation_type expand_bwd         = (allocation_type)expand_bwd_v;
static const allocation_type shrink_in_place    = (allocation_type)shrink_in_place_v;
static const allocation_type try_shrink_in_place= (allocation_type)try_shrink_in_place_v;
static const allocation_type nothrow_allocation = (allocation_type)nothrow_allocation_v;
static const allocation_type zero_memory        = (allocation_type)zero_memory_v;

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_ALLOCATION_TYPE_HPP

/* allocation_type.hpp
GLSwZdc0okVV2PFtDWfRRYQ3zGLTa9oJFWR14iajEQTjJMah8n76NF3g9l4dYIGfyGB3YNyez+b/mMwm2zm1M/kXUEsDBAoAAAAIAC1nSlJkDITB7AMAAIoIAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fU0laRV9VUExPQUQuM1VUBQABtkgkYK1U72/bNhD9rr/ipmGDE6hy0nZou2bFVNtdhLiSYMnNPBgQaImKWEiiRlJJjKX/+46U1DQ/gOZDFTiUSL53x3fv6G5tOPxhj+VqOvjuk5pfig+OIygS/DPN1OOANL2B/g+BWxyfEGoKt6ib9ACehLqBiUGlQ6wT/Z6mTwi31Unqf1MN3qb6FWd65ICf8XYv2EWpYDI7gOM3b17DM3h+dPzKgTlpGK0gVrTZUXHhwEluZv4syfW1K+k7B6gCUrl3CJOSSZC8UFdEUMD3imW0kTQHIiGnMhNshx+sAVVSKFhFYRZGGz/4y4GrkmXlwLPnHciSd1UOJbmkIGhG2WVP0xKhgBfIgPw5kwo5O8V442J4CoqKWg40OglSSQ7kkrCK7DAcUVAq1crfp9OsExWeZJrzTE6zUQq3VPW9U20wm5rsgbcKFIdOUgf0fgdqnrNC
*/