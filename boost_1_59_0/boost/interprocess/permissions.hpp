//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PERMISSIONS_HPP
#define BOOST_INTERPROCESS_PERMISSIONS_HPP

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>

#if defined(BOOST_INTERPROCESS_WINDOWS)

#include <boost/interprocess/detail/win32_api.hpp>

#else

#include <sys/stat.h>

#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes permissions class

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#if defined(BOOST_INTERPROCESS_WINDOWS)

namespace ipcdetail {

template <int Dummy>
struct unrestricted_permissions_holder
{
   static winapi::interprocess_all_access_security unrestricted;
};

template<int Dummy>
winapi::interprocess_all_access_security unrestricted_permissions_holder<Dummy>::unrestricted;

}  //namespace ipcdetail {

#endif   //defined BOOST_INTERPROCESS_WINDOWS

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!The permissions class represents permissions to be set to shared memory or
//!files, that can be constructed form usual permission representations:
//!a SECURITY_ATTRIBUTES pointer in windows or ORed rwx chmod integer in UNIX.
class permissions
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   #if defined(BOOST_INTERPROCESS_WINDOWS)
   typedef void*  os_permissions_type;
   #else
   typedef ::mode_t    os_permissions_type;
   #endif
   os_permissions_type  m_perm;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs a permissions object from a user provided os-dependent
   //!permissions.
   permissions(os_permissions_type type) BOOST_NOEXCEPT
      : m_perm(type)
   {}

   //!Constructs a default permissions object:
   //!A null security attributes pointer for windows or 0644
   //!for UNIX.
   permissions() BOOST_NOEXCEPT
   {  set_default(); }

   //!Sets permissions to default values:
   //!A null security attributes pointer for windows or 0644
   //!for UNIX.
   void set_default() BOOST_NOEXCEPT
   {
      #if defined (BOOST_INTERPROCESS_WINDOWS)
      m_perm = 0;
      #else
      m_perm = 0644;
      #endif
   }

   //!Sets permissions to unrestricted access:
   //!A null DACL for windows or 0666 for UNIX.
   void set_unrestricted() BOOST_NOEXCEPT
   {
      #if defined (BOOST_INTERPROCESS_WINDOWS)
      m_perm = &ipcdetail::unrestricted_permissions_holder<0>::unrestricted;
      #else
      m_perm = 0666;
      #endif
   }

   //!Sets permissions from a user provided os-dependent
   //!permissions.
   void set_permissions(os_permissions_type perm) BOOST_NOEXCEPT
   {  m_perm = perm; }

   //!Returns stored os-dependent
   //!permissions
   os_permissions_type get_permissions() const BOOST_NOEXCEPT
   {  return m_perm; }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_PERMISSIONS_HPP


/* permissions.hpp
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
*/