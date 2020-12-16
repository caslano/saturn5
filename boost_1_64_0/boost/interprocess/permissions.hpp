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
s/cWpfOEeRcPpGy++hu1x3oGFPm+Rh6YUgdzOTVcqnvQTbxn6qlenRo+l9KlIsNkzd9zwj845o3a1/PQ+z8woNrraPinKYfufpAtyfeunTElb+bYVDkDqssrO6+/UB2jxL3LIx5Oqo9UGUHGuEfxaOyCS8EpH8AQ2edVyQevvBpO45EZ/btVk3+EyHsy2vkxlLP7EQ906Whs+7VkqtKv9Du6wqdqbWnzU7MFyS3wjRmNdF6C2ao/nU9+qayf8lLd5ued3Co6uUukh29K99Jf+e+8qCL/DRfVuL/Lolr94oqqgp9GccXpF0xUmf8+iV/xqLDdws5HCVVyF7Ddbx+Cet098O2BYnpNKhjnSc67o0b5PgFga/Ul/46or+8vqIq+8V5j84c5CjV4XmvnM3U+mxpSY8HK8swLnk/vqSaYDtpgUigDqQUWe6r0HOl5N/umjvfGBlRaFyq6E/fVSeGlso7Aewn1V8GG9erb/RzZ88K1EJVzuoCaUxa0WDPXT/f+iO79sC3u3949kXVX1/uFCiqMbqisqaiukJK+T0BE5ylZfrjecOIT923K+tdXVfFP1k3B6dBeDadWiTnBI2xmXjXk3KMg2yrrMAmqNJs6DSO5//GjOu1EepHELfgypk2oCnfGCpOMKjBvKnATXQVPOqTBNRT7omD+MkrO/l86n1kPc4pQB5wWdF6PA4XHx0B2u3vIT9x03/jttxKo8jZBNQPhmRnweGjIQQ8tqM45Gp+Hhk49NFUFCzsQ6qEFIvxp4KGpyldfKNRDQ/LV3kDQQ1OtemhBle4b9NDc2l5VeDw0VW0WUT00pHB/jAivP4Yi4I+hC/HHVE2z5z8NlNdpE4f7aMQEfDR0IQ4Z2lCHDH3AIUMX4pBtqsml/vbkOOCjoVMfzRHGVQr4aOg8PhqyJucXHXuDzut7BTWFDAd9NJReHw2FywPziZqOqjQR2/bkf2sRXT4aks9Hy6sCCm9hAj6aKr1FUR/MK7mO8Wbb66Oh8PhoyCE+Gtqgj4YyzEdD7XbJAgqn+wV8NHQBHw1dwEfzKlUV4qOhLuajEeXz0QKqvbZGfTQkv4+GyuOjIQd8NHRuHw3R46Mhe300FF4fDYXfR0Pl9dG8Gj2Ny0dDE/TRUAZ8NHR+Hw1VwEdD5/LRkNRHK0gquH005IKPxk+Pj4Yc8NHQ+X00VRU6ufpom9K9Cr/UR0Ph89HQBH001arPhKqoj6ZxjASnnwRcNpQel82veFTYbmGnp8AquQyxKrUSPP6a2Hg9OhhX5LBihxTbnRv2ekgwTg8LeIDF9JpcMM6TnHdHjfJ7jWjdXiOi32tEVdxr1Nj8YY5CTbDX/vqMr8/Kh1R0sI69M5V6gyEaTSfgNRaUgdQCC1BV6pEBrxGdeo0+ldaFiu7EvXWiXiOC4yvqL8eWebxGZL/XGFQVThf0GgvagvVVr9Et6n4Fa+f2Gt2y7urxGlGpRxiUNRXV5VNye42IjtfID5eb6BOdqvd5jajUa0RQr9Gn4dQqMUt5BM2822v0KPLZ9nuNQZVmUxcGPq9RddqJ1Gt0C76MaROqQjOmXqMq8qsz9RoLgiedQhqjg1peHoDz6DiVX5eXR1h9ucYbMn3dofb5XNDzCuqeUHB8ckEfK+f3sXKhXtSYz9c6HnAM0XlWagHFvshI67CnTMh2maCWKYfgyyUqby5RhOTyOFp/rtB5MhFQ7Ato5MGMUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUiiFUig=
*/