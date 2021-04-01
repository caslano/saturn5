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
ANO97LC0I60+/VrEuA1bQkqsAy6EdJVWGklarTKJ05yGjRfvivQyRJOuiKuO4xLl0DBEhsPALepotWZIBoh0ndHdvNqyiKyJCA1Iv14vzC0+ckewEgKvzy//mcKlu+PfGzfaaECxcIj6EeJp52AhnxHE8QF0dWpf4+b562P5oIcloGaPQfL4DZVGARk75rSk7plvuzUJ9CXWFY0FFcVVuom7FlxSqKT0KGfHioNQNqBznOjS9rSd18DNEQ4iCYjrR1H7DbkYGZvevyVteMABDuGZq9sKD7RbYiiGimLqGZ1ACLJ8Phjn8VRPJRxyX3rD1zav46lcvgFl+H2lTyUclob8lSFpYaDnc4nfKg4/4rxjBinCgCAwOY9fWLBO0qNGF2jnrr3LcePvo19B8W52IP0ValTeCSgVnd4wow06cURH+FjH+2IZ/TmOb49NdptD/yAEY5w/nZj9fJwB0QzUpySkLPc2eo5+bSUuc5LzfrgG7CN04p94zjFsZrjeGDAFRbRXAbhuxcYM4f7Af+LtcZ7qiGpWji9WW8+fQIVmI4dq5scNZNwlizlkqQ==
*/