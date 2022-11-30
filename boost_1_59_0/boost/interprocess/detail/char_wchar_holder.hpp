//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2020-2021. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_CHAR_WCHAR_HOLDER_HPP
#define BOOST_INTERPROCESS_DETAIL_CHAR_WCHAR_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <cwchar>
#include <cstring>

namespace boost {
namespace interprocess {

class char_wchar_holder
{
   public:
   char_wchar_holder()
      : m_str(), m_is_wide()
   {
      m_str.n = 0;
   }

   char_wchar_holder(const char *nstr)
      : m_str(), m_is_wide()
   {
      m_str.n = new char [std::strlen(nstr)+1];
      std::strcpy(m_str.n, nstr);
   }

   char_wchar_holder(const wchar_t *wstr)
      : m_str(), m_is_wide(true)
   {
      m_str.w = new wchar_t [std::wcslen(wstr)+1];
      std::wcscpy(m_str.w, wstr);
   }

   char_wchar_holder& operator=(const char *nstr)
   {
      char *tmp = new char [std::strlen(nstr)+1];
      this->delete_mem();
      m_str.n = tmp;
      std::strcpy(m_str.n, nstr);
      return *this;
   }

   char_wchar_holder& operator=(const wchar_t *wstr)
   {
      wchar_t *tmp = new wchar_t [std::wcslen(wstr)+1];
      this->delete_mem();
      m_str.w = tmp;
      std::wcscpy(m_str.w, wstr);
      return *this;
   }

   char_wchar_holder& operator=(const char_wchar_holder &other)
   {
      if (other.m_is_wide)
         *this = other.getn();
      else
         *this = other.getw();
      return *this;
   }

   ~char_wchar_holder()
   {
      this->delete_mem();
   }

   wchar_t *getw() const
   {  return m_is_wide ? m_str.w : 0; }

   char *getn() const
   {  return !m_is_wide ? m_str.n : 0; }

   void swap(char_wchar_holder& other)
   {
      char_wchar tmp;
      std::memcpy(&tmp, &m_str, sizeof(char_wchar));
      std::memcpy(&m_str, &other.m_str, sizeof(char_wchar));
      std::memcpy(&other.m_str, &tmp, sizeof(char_wchar));
      //
      bool b_tmp(m_is_wide);
      m_is_wide = other.m_is_wide;
      other.m_is_wide = b_tmp;
   }

   private:

   void delete_mem()
   {
      if(m_is_wide)
         delete [] m_str.w;
      else
         delete [] m_str.n;
   }

   union char_wchar
   {
      char    *n;
      wchar_t *w;
   } m_str;
   bool m_is_wide;
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_CHAR_WCHAR_HOLDER_HPP

/* char_wchar_holder.hpp
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
*/