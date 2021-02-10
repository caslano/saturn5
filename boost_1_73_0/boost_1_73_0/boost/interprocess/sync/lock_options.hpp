//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_LOCK_OPTIONS_HPP
#define BOOST_INTERPROCESS_LOCK_OPTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

//!\file
//!Describes the lock options with associated with interprocess_mutex lock constructors.

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

//!Type to indicate to a mutex lock constructor that must not lock the mutex.
struct defer_lock_type{};
//!Type to indicate to a mutex lock constructor that must try to lock the mutex.
struct try_to_lock_type {};
//!Type to indicate to a mutex lock constructor that the mutex is already locked.
struct accept_ownership_type{};

//!An object indicating that the locking
//!must be deferred.
static const defer_lock_type      defer_lock      = defer_lock_type();

//!An object indicating that a try_lock()
//!operation must be executed.
static const try_to_lock_type     try_to_lock    = try_to_lock_type();

//!An object indicating that the ownership of lockable
//!object must be accepted by the new owner.
static const accept_ownership_type  accept_ownership = accept_ownership_type();

} // namespace interprocess {
} // namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_LOCK_OPTIONS_HPP

/* lock_options.hpp
X/mRXu84z/uztpRIhlksEEAv8dR1bq/Ojr/Ozt6fIecFOS8CKxIEr8tQbdOYparPtJJeDCugpK7CWTwK7TGJnmEgXRazC8wuMLvA7GKrZhfrdXo3zS5Q2bfUsYbI8oT5ow3KBM3LHW0oU9hc3blF2nqGRU4oEFlXOrLOw/SX2/JHVQvOEllAhWGVTThWvWG+Yb5hvmG+K2q+o6oWZ3HdUek4zUeuN39lVuUAr/QIbsQXpvFBNURtk7i/+O9WJ8zeC/5udRyjxE7Ws82OS7PwBF4CL4GXMkx15PBS4qqAyvyi+sL2BvrBOjeYSSlmUm7GlDbYWdH5E/gN/AZ+q+LMK6G+2rYX3owgFVSxBpeoxiXqzJXSFrECsWQkFhT4BfWAelJPYyronZWPszAZAiPBscpUHwb0hCkVCAwEJp/AvL+RfYRVfjBK+RlFDSdtkVEqOAECL4GXwEvlnukER8g+wuo8mGmbmUm5GdMKM23b/An8Bn4Dv1Vl5hW5mTzbbKsyu57lbGsu2h3EVmaJW5mrPj2Kpg8JUyKQEEgIJIQ5DJfda5UhE6m+GiPXoKwLaKg6cyH5W9VAZiAzkFn5yEylORX7vrQysY8yDIJvloI4qjEL4rQJDSzCnUXwdUnwTDV5Bk5WJQgK0xzQTxL9
*/