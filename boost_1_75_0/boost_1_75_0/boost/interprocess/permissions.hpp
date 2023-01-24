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
vz2rZpVp9prbqkdA+ZI3+s1okpuFG+AtyVbTcas9LOZyr3qmX7CroDvokAcikfkgwimBhPV/XNQjCCGjSNySjCGWuklnDnsiPIOe2c9ldDMSDzhJOlNmtiBveVPPYg9yBkt6iSxMpaNgHzXUdqmEmyWEDUZkOPHW48wYAurohSMkJg3Lb+40enRev+Lvd/QosBCRNwuJ6L5Tfnj9ga5xyQ3ZIJibfd3iLbmdu/l54CJM048fg0vKta/ftdxZPzviDTXCjzzynWHtMp0oSegHatZpI63Qvnh7Axg7IkMEv1b6vMLmh9/KXKe97Td+Ywzvque4YfoEwvC7OJ+QDJ6L798HKCb0z1/P5oC5e2Toj8jGcs+SjHQ4GCIT/VvZ00yglRRVbMT+jtmOFHO0JVE1r0vDNw529tKQB1OCpHgHNxSsME866rqkICHnEZtCqVNiIzSsoLufpdIIeqWLDW0QiOOXpKVRLMXoPTfVp5+1UjMzf3d5ZIEidYffF+ZeyzHAo9qFd+KMIQLeVNzomSCf768p2SPTE6+3Cb5tzuSzou8t9kM/i5fAiAyZP/oPKEe9LlsMhMW93sM5BdBJUKT7GQ1WEDbWqhR+1169zdGo4ByTa3pX5SEq/sRy9Kn1DUWIFdV+znwRa/Zv2ZsCp7eytHt6XWo8tcF3tUlDjfthG7/DnutcnVmor9zY668UlJ2ZJd1t1nwhrgGmV9mp
*/