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
s0u+LdGbfBKYM4gYrEdR5BJAaXbbE9vmXUphJlGY1nZfowcwXx0SW6f2e/uXhZI0lwFva2kmkGbVk2/p5w67laPoWuwaAvsqXqFKGuF0+Q1I6RjBL1RfIzNBmX9bk/O3pB1G5Pz07LxuglIO39MdKiMN4OI1mpKj3KuC/Hs1oSLoWtvsLcMjyZnSJTxK5yg2IT3J90yc3mg87A0+PTXHVB9LBsPXPPazvfKVI4FapzB0QojVJBRwpRVwlmmBwtse5WmK7Zr2vJzmSNEcZajAkwJ8ngtWsiFTBkEKYleMu1wy0nAGbtCnQgCP7TEnPlWy6i2BYvmc7euLSBfMGXLGwotsXZrrPnFzew/5UZsEcDlrkJIhidKLAivbl9r+vp7Z5MpLMgHNqhQGRCkw/GuuoZxQA7Qleq53iShFkFC0i21MYaGy3IFzqUgAhqV10cIdA9vsUhRtItfZC3Tn97nnWwRZIiOVpvxtq2MpdcmCmY2NtV6uipBlXpkNi9IW/Q23DwIG42ShybAGn/EkNlvhqFmD1npJdYdZTr1uWXnXYNXr0uAYIwxqRUwAdf6js95M7EonsCMi3gWY4qgdWZEdP5Wqvu04s+l2JiJh6rgI4ovvO9OXDIMkKpVR7whMJXI8FZmqYkcJGysRsTJ6
*/