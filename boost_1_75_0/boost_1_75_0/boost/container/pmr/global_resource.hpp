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
Rfpyiv0xs8Ghq0ktI5Qrm7k92jyk0FoTRhHDUQKJQLZMoEsg7TJgnATgIb12orqpS0pBqxnS6Ua0GgHHMiVTzMulc3Imfia/wwXrqgbOux0pcuOfJQQIKy0ERlogLKQHhVUpnETiSyK2DTfztQap0Eh0pshSs1FonJATgCzVpKFAOvOGZeHCe1ftIWOOY+5VsvlXrkIuuECpLn/IKpJ9aZjqjIDCe+4Pe95t9+OpED7yV7cE64YJg16bNKv3ADic8V2AFfje8lEwEAI2Es31Uuc/uejB+SO9g/N2+Z0LkfAQwzil/Gd+eXOTJIlBflHkFd7HunXrCEFo4oKsG7CI5AIhlR12f+bZHYE0NBqSQS+i1zXEZJplaHcUl6+7OyTU0pMi6iQWp5M7aUcXM1VDKYpQZ1YlSCyBSKx3wUkNApQnKQiJIRDuqDCnahi1Q6sQEditwhNlFgPNJNMZZm1ACmGqTURgCfHdvWOxFKK9mONRxSs7RKwOQSVde8M0JzPVTZVFaoMnjJXarNJmCgkgPwfQbgKSJZpeI2Z7+zKp3QnIVwPc3Imi8t6TPnEAnq/p9RwUh4N6iF8kFY3eCViG/O860pcy1l5Wbgo4sC5ApbUxAmqjv0ohUCrh7WsHIJtG/7fc33Aga+VVNU1oY/3WmCXDrXZItxPSbEhmcYbO8MRqxVw0ixd9V8IUW3f5JAs/rDeAUigxlJb45uVt
*/