//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/container_fwd.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! <b>Returns</b>: A pointer to a static-duration object of a type derived from
//!   memory_resource that can serve as a resource for allocating memory using
//!   global `operator new` and global `operator delete`. The same value is returned every time this function
//!   is called. For return value p and memory resource r, p->is_equal(r) returns &r == p.
BOOST_CONTAINER_DECL memory_resource* new_delete_resource() BOOST_NOEXCEPT;

//! <b>Returns</b>: A pointer to a static-duration object of a type derived from
//!   memory_resource for which allocate() always throws bad_alloc and for which
//!   deallocate() has no effect. The same value is returned every time this function
//!   is called. For return value p and memory resource r, p->is_equal(r) returns &r == p.
BOOST_CONTAINER_DECL memory_resource* null_memory_resource() BOOST_NOEXCEPT;

//! <b>Effects</b>: If r is non-null, sets the value of the default memory resource
//!   pointer to r, otherwise sets the default memory resource pointer to new_delete_resource().
//!
//! <b>Postconditions</b>: get_default_resource() == r.
//!
//! <b>Returns</b>: The previous value of the default memory resource pointer.
//!
//! <b>Remarks</b>: Calling the set_default_resource and get_default_resource functions shall
//!   not incur a data race. A call to the set_default_resource function shall synchronize
//!   with subsequent calls to the set_default_resource and get_default_resource functions.
BOOST_CONTAINER_DECL memory_resource* set_default_resource(memory_resource* r) BOOST_NOEXCEPT;

//! <b>Returns</b>: The current value of the default
//!   memory resource pointer.
BOOST_CONTAINER_DECL memory_resource* get_default_resource() BOOST_NOEXCEPT;

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_GLOBAL_RESOURCE_HPP

/* global_resource.hpp
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
*/