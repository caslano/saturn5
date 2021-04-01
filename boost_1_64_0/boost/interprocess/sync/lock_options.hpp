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
hzSdF7RPOBl2rURR7sctKGuJGVskKa9BCw2w52leWblxYdq59FKv5KkSZ59JuSttRlw8+nu+aDQdZwP0sn2yEx1pJ5eawW25jbWWc4Po5+PqB45euNFO33Wl4aHSpgD+rT69BUZNpytkWbqgdHBpEC+xGFHYRmJxPoKB1m8SmNsrW2CU1Ew7dfBP8D52ZqC4plBJpxhwUFKBuNyEhTMeDr1zphc6F4LD8buZU0PUR5nM5jQ7xd0sV8wX1EQpy5zt1TlmCP8C9evsrmAWxSf/1sj9ZYWdwbBbGqcyqJbdWAT/P9l4E6FsG69COlQv6C37gPIhe1ov9hv1Uyyug8fivsStedJOuDAnhJa13VJffZPdvRQwFPUBwr/slP+VMiQ6vqeliGi8ksjicpp59Oa87AqSNHX6zsu4N863N8kSbxEGC1MjgrnSws8Ue03mnONmTkvd6/NCOIp6Xrw6tXg3AL0xqMK41YD6NngYWO6FZKdwC/1D5622Schhh+mgXt0U1NNSVpJ6cQ/QQuoHVEWOFGYocUbTnybaT/MmMKEgEE2R4X9h+yS2/H+7YA==
*/