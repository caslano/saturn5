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
   typedef int    os_permissions_type;
   #endif
   os_permissions_type  m_perm;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs a permissions object from a user provided os-dependent
   //!permissions.
   permissions(os_permissions_type type)
      : m_perm(type)
   {}

   //!Constructs a default permissions object:
   //!A null security attributes pointer for windows or 0644
   //!for UNIX.
   permissions()
   {  set_default(); }

   //!Sets permissions to default values:
   //!A null security attributes pointer for windows or 0644
   //!for UNIX.
   void set_default()
   {
      #if defined (BOOST_INTERPROCESS_WINDOWS)
      m_perm = 0;
      #else
      m_perm = 0644;
      #endif
   }

   //!Sets permissions to unrestricted access:
   //!A null DACL for windows or 0666 for UNIX.
   void set_unrestricted()
   {
      #if defined (BOOST_INTERPROCESS_WINDOWS)
      m_perm = &ipcdetail::unrestricted_permissions_holder<0>::unrestricted;
      #else
      m_perm = 0666;
      #endif
   }

   //!Sets permissions from a user provided os-dependent
   //!permissions.
   void set_permissions(os_permissions_type perm)
   {  m_perm = perm; }

   //!Returns stored os-dependent
   //!permissions
   os_permissions_type get_permissions() const
   {  return m_perm; }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_PERMISSIONS_HPP


/* permissions.hpp
pH0L6FI7zAHmnkTWoFb0T/IFqdep1kJlakoatgHW7hgxPnc/CfZksNt7eNzDM8Nv6lFr8oKfbmaiDYQJJowklN3vLLfYwQpm+BcrX0Kth4tYwBFpcMiJXna/rk5jMsLjJEQmcQQBO95ar8f8TmQG62Xad1+/vZMf1rnaGbizEM2nH37BK+hpahgi2R0XM87UIwlFfo8qW1MYjvTADnafQTT/O2KJ1MXn350AjXUDiXYQf/+RNdCzK2E5zwe38lRyH6+zy+BU4NTwjuIWuEfGovHo8+YOiYk+/T6C8NQ/hrZzyvwBXE7297Kr0Cr0xeiBkzHtCOwZImT78rN2Nw4p15Q3sZy7aydWMdU3QXQafrQcB8W7iU5o0MzheeuuyiegaY7/969UvW5BOEnsNWSPY03GIMEyrvfrcQdpM0VdVObwpVpTcimAVBXV6hnj0uoAQ7u/UWdhL7YPdrcK6WI6xRV6hNJS7IVgUCf1e2iGWt2ngud6Nadjl/tZi7Ak0nx/iZx5yHIAqfPaxWjlacXJPItzEnJmv929WqL1yQyjI9dnblcuQMNoaPQ+iQ==
*/