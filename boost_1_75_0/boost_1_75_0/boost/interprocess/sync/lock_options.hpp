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
HGKk4cX77qgKZgTaivZ9HXgu5KehcBlbRmI+aOm3XAkTzPHMCfJmnGFJv78WZn2Pb00bN+IVqaFvqNNAQhdgoyCYyZkRUYZbd0+P0IE+68/Gieivf7u+z9FLE716Xj7xnTTvu4o59p37HABiFEZ6wzqR3XZXfe+5KthC9qNXl3zS/067A1bl7bvKCwwGfc3Lq30tdcDxw35A2bnvVnzyXUoMBlkLSzx1Lr1qLRlpX+8XwnX9qaZWG1UY0iZSoPv8m4jGvNdr/SD3j1XBEvTRKSEjaskS1YDX08fe31tMKUTr07U3m1dN0yw+SmuHsyn7/uOTeebc4YP7DBNO+rCvs6la1Nzp7tN9lwL3/PROVXUAVYMu3K+vMjsSYqGXRXmv9k/ZKYNu/oeXJBN72/r8tfMn8zITGdrorlOXkqM/kBqzmRsp9lC4wy59OhfN8yY35eypk1H+/C4qDEzKK07B4WKk3fAT/0MlIv/jjXRCPe3j75B9t/rAiWGOcVkeoo5Aha6nVckDhSvmM2HFctFt0IekKr+myekaRknRJuCSW6ru7ImT5emLMWWnn5ZMDeDD3FlYyMtZGHJrlV2dJ5u9H7d4qX57iG/Jpb74gjWzEDqSn2mRqxcwwtA+DCRIlvgKIfTfG+iCEHZ3yPpPPNShZw1UOENp32Dwgd65uu5NZR0JW/FYJfif5oUmhpRMLXPciORnPjUVrP2YDFzd
*/