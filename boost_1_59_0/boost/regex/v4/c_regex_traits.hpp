/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         c_regex_traits.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression traits class that wraps the global C locale.
  */

#ifndef BOOST_C_REGEX_TRAITS_HPP_INCLUDED
#define BOOST_C_REGEX_TRAITS_HPP_INCLUDED

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/regex/config.hpp>
#endif
#ifndef BOOST_REGEX_WORKAROUND_HPP
#include <boost/regex/v4/regex_workaround.hpp>
#endif

#include <cctype>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{
   using ::strlen; using ::tolower;
}
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103 4244)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

namespace boost{

   namespace BOOST_REGEX_DETAIL_NS {

      enum
      {
         char_class_space = 1 << 0,
         char_class_print = 1 << 1,
         char_class_cntrl = 1 << 2,
         char_class_upper = 1 << 3,
         char_class_lower = 1 << 4,
         char_class_alpha = 1 << 5,
         char_class_digit = 1 << 6,
         char_class_punct = 1 << 7,
         char_class_xdigit = 1 << 8,
         char_class_alnum = char_class_alpha | char_class_digit,
         char_class_graph = char_class_alnum | char_class_punct,
         char_class_blank = 1 << 9,
         char_class_word = 1 << 10,
         char_class_unicode = 1 << 11,
         char_class_horizontal = 1 << 12,
         char_class_vertical = 1 << 13
      };

   }

template <class charT>
struct c_regex_traits;

template<>
struct c_regex_traits<char>
{
   c_regex_traits(){}
   typedef char char_type;
   typedef std::size_t size_type;
   typedef std::string string_type;
   struct locale_type{};
   typedef boost::uint32_t char_class_type;

   static size_type length(const char_type* p) 
   { 
      return (std::strlen)(p); 
   }

   char translate(char c) const 
   { 
      return c; 
   }
   char translate_nocase(char c) const 
   { 
      return static_cast<char>((std::tolower)(static_cast<unsigned char>(c))); 
   }

   static string_type BOOST_REGEX_CALL transform(const char* p1, const char* p2);
   static string_type BOOST_REGEX_CALL transform_primary(const char* p1, const char* p2);

   static char_class_type BOOST_REGEX_CALL lookup_classname(const char* p1, const char* p2);
   static string_type BOOST_REGEX_CALL lookup_collatename(const char* p1, const char* p2);

   static bool BOOST_REGEX_CALL isctype(char, char_class_type);
   static int BOOST_REGEX_CALL value(char, int);

   locale_type imbue(locale_type l)
   { return l; }
   locale_type getloc()const
   { return locale_type(); }

private:
   // this type is not copyable:
   c_regex_traits(const c_regex_traits&);
   c_regex_traits& operator=(const c_regex_traits&);
};

#ifndef BOOST_NO_WREGEX
template<>
struct c_regex_traits<wchar_t>
{
   c_regex_traits(){}
   typedef wchar_t char_type;
   typedef std::size_t size_type;
   typedef std::wstring string_type;
   struct locale_type{};
   typedef boost::uint32_t char_class_type;

   static size_type length(const char_type* p) 
   { 
      return (std::wcslen)(p); 
   }

   wchar_t translate(wchar_t c) const 
   { 
      return c; 
   }
   wchar_t translate_nocase(wchar_t c) const 
   { 
      return (std::towlower)(c); 
   }

   static string_type BOOST_REGEX_CALL transform(const wchar_t* p1, const wchar_t* p2);
   static string_type BOOST_REGEX_CALL transform_primary(const wchar_t* p1, const wchar_t* p2);

   static char_class_type BOOST_REGEX_CALL lookup_classname(const wchar_t* p1, const wchar_t* p2);
   static string_type BOOST_REGEX_CALL lookup_collatename(const wchar_t* p1, const wchar_t* p2);

   static bool BOOST_REGEX_CALL isctype(wchar_t, char_class_type);
   static int BOOST_REGEX_CALL value(wchar_t, int);

   locale_type imbue(locale_type l)
   { return l; }
   locale_type getloc()const
   { return locale_type(); }

private:
   // this type is not copyable:
   c_regex_traits(const c_regex_traits&);
   c_regex_traits& operator=(const c_regex_traits&);
};

#endif // BOOST_NO_WREGEX

inline c_regex_traits<char>::string_type BOOST_REGEX_CALL c_regex_traits<char>::transform(const char* p1, const char* p2)
{
   std::string result(10, ' ');
   std::size_t s = result.size();
   std::size_t r;
   std::string src(p1, p2);
   while (s < (r = std::strxfrm(&*result.begin(), src.c_str(), s)))
   {
#if defined(_CPPLIB_VER)
      //
      // A bug in VC11 and 12 causes the program to hang if we pass a null-string
      // to std::strxfrm, but only for certain locales :-(
      // Probably effects Intel and Clang or any compiler using the VC std library (Dinkumware).
      //
      if (r == INT_MAX)
      {
         result.erase();
         result.insert(result.begin(), static_cast<char>(0));
         return result;
      }
#endif
      result.append(r - s + 3, ' ');
      s = result.size();
   }
   result.erase(r);
   return result;
}

inline c_regex_traits<char>::string_type BOOST_REGEX_CALL c_regex_traits<char>::transform_primary(const char* p1, const char* p2)
{
   static char s_delim;
   static const int s_collate_type = ::boost::BOOST_REGEX_DETAIL_NS::find_sort_syntax(static_cast<c_regex_traits<char>*>(0), &s_delim);
   std::string result;
   //
   // What we do here depends upon the format of the sort key returned by
   // sort key returned by this->transform:
   //
   switch (s_collate_type)
   {
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_C:
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_unknown:
      // the best we can do is translate to lower case, then get a regular sort key:
   {
      result.assign(p1, p2);
      for (std::string::size_type i = 0; i < result.size(); ++i)
         result[i] = static_cast<char>((std::tolower)(static_cast<unsigned char>(result[i])));
      result = transform(&*result.begin(), &*result.begin() + result.size());
      break;
   }
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_fixed:
   {
      // get a regular sort key, and then truncate it:
      result = transform(p1, p2);
      result.erase(s_delim);
      break;
   }
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_delim:
      // get a regular sort key, and then truncate everything after the delim:
      result = transform(p1, p2);
      if ((!result.empty()) && (result[0] == s_delim))
         break;
      std::size_t i;
      for (i = 0; i < result.size(); ++i)
      {
         if (result[i] == s_delim)
            break;
      }
      result.erase(i);
      break;
   }
   if (result.empty())
      result = std::string(1, char(0));
   return result;
}

inline c_regex_traits<char>::char_class_type BOOST_REGEX_CALL c_regex_traits<char>::lookup_classname(const char* p1, const char* p2)
{
   using namespace BOOST_REGEX_DETAIL_NS;
   static const char_class_type masks[] =
   {
      0,
      char_class_alnum,
      char_class_alpha,
      char_class_blank,
      char_class_cntrl,
      char_class_digit,
      char_class_digit,
      char_class_graph,
      char_class_horizontal,
      char_class_lower,
      char_class_lower,
      char_class_print,
      char_class_punct,
      char_class_space,
      char_class_space,
      char_class_upper,
      char_class_unicode,
      char_class_upper,
      char_class_vertical,
      char_class_alnum | char_class_word,
      char_class_alnum | char_class_word,
      char_class_xdigit,
   };

   int idx = ::boost::BOOST_REGEX_DETAIL_NS::get_default_class_id(p1, p2);
   if (idx < 0)
   {
      std::string s(p1, p2);
      for (std::string::size_type i = 0; i < s.size(); ++i)
         s[i] = static_cast<char>((std::tolower)(static_cast<unsigned char>(s[i])));
      idx = ::boost::BOOST_REGEX_DETAIL_NS::get_default_class_id(&*s.begin(), &*s.begin() + s.size());
   }
   BOOST_REGEX_ASSERT(std::size_t(idx) + 1u < sizeof(masks) / sizeof(masks[0]));
   return masks[idx + 1];
}

inline bool BOOST_REGEX_CALL c_regex_traits<char>::isctype(char c, char_class_type mask)
{
   using namespace BOOST_REGEX_DETAIL_NS;
   return
      ((mask & char_class_space) && (std::isspace)(static_cast<unsigned char>(c)))
      || ((mask & char_class_print) && (std::isprint)(static_cast<unsigned char>(c)))
      || ((mask & char_class_cntrl) && (std::iscntrl)(static_cast<unsigned char>(c)))
      || ((mask & char_class_upper) && (std::isupper)(static_cast<unsigned char>(c)))
      || ((mask & char_class_lower) && (std::islower)(static_cast<unsigned char>(c)))
      || ((mask & char_class_alpha) && (std::isalpha)(static_cast<unsigned char>(c)))
      || ((mask & char_class_digit) && (std::isdigit)(static_cast<unsigned char>(c)))
      || ((mask & char_class_punct) && (std::ispunct)(static_cast<unsigned char>(c)))
      || ((mask & char_class_xdigit) && (std::isxdigit)(static_cast<unsigned char>(c)))
      || ((mask & char_class_blank) && (std::isspace)(static_cast<unsigned char>(c)) && !::boost::BOOST_REGEX_DETAIL_NS::is_separator(c))
      || ((mask & char_class_word) && (c == '_'))
      || ((mask & char_class_vertical) && (::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) || (c == '\v')))
      || ((mask & char_class_horizontal) && (std::isspace)(static_cast<unsigned char>(c)) && !::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) && (c != '\v'));
}

inline c_regex_traits<char>::string_type BOOST_REGEX_CALL c_regex_traits<char>::lookup_collatename(const char* p1, const char* p2)
{
   std::string s(p1, p2);
   s = ::boost::BOOST_REGEX_DETAIL_NS::lookup_default_collate_name(s);
   if (s.empty() && (p2 - p1 == 1))
      s.append(1, *p1);
   return s;
}

inline int BOOST_REGEX_CALL c_regex_traits<char>::value(char c, int radix)
{
   char b[2] = { c, '\0', };
   char* ep;
   int result = std::strtol(b, &ep, radix);
   if (ep == b)
      return -1;
   return result;
}

#ifndef BOOST_NO_WREGEX

inline c_regex_traits<wchar_t>::string_type BOOST_REGEX_CALL c_regex_traits<wchar_t>::transform(const wchar_t* p1, const wchar_t* p2)
{
   std::size_t r;
   std::size_t s = 10;
   std::wstring src(p1, p2);
   std::wstring result(s, L' ');
   while (s < (r = std::wcsxfrm(&*result.begin(), src.c_str(), s)))
   {
#if defined(_CPPLIB_VER)
      //
      // A bug in VC11 and 12 causes the program to hang if we pass a null-string
      // to std::strxfrm, but only for certain locales :-(
      // Probably effects Intel and Clang or any compiler using the VC std library (Dinkumware).
      //
      if (r == INT_MAX)
      {
         result.erase();
         result.insert(result.begin(), static_cast<wchar_t>(0));
         return result;
      }
#endif
      result.append(r - s + 3, L' ');
      s = result.size();
   }
   result.erase(r);
   return result;
}

inline c_regex_traits<wchar_t>::string_type BOOST_REGEX_CALL c_regex_traits<wchar_t>::transform_primary(const wchar_t* p1, const wchar_t* p2)
{
   static wchar_t s_delim;
   static const int s_collate_type = ::boost::BOOST_REGEX_DETAIL_NS::find_sort_syntax(static_cast<const c_regex_traits<wchar_t>*>(0), &s_delim);
   std::wstring result;
   //
   // What we do here depends upon the format of the sort key returned by
   // sort key returned by this->transform:
   //
   switch (s_collate_type)
   {
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_C:
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_unknown:
      // the best we can do is translate to lower case, then get a regular sort key:
   {
      result.assign(p1, p2);
      for (std::wstring::size_type i = 0; i < result.size(); ++i)
         result[i] = (std::towlower)(result[i]);
      result = c_regex_traits<wchar_t>::transform(&*result.begin(), &*result.begin() + result.size());
      break;
   }
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_fixed:
   {
      // get a regular sort key, and then truncate it:
      result = c_regex_traits<wchar_t>::transform(&*result.begin(), &*result.begin() + result.size());
      result.erase(s_delim);
      break;
   }
   case ::boost::BOOST_REGEX_DETAIL_NS::sort_delim:
      // get a regular sort key, and then truncate everything after the delim:
      result = c_regex_traits<wchar_t>::transform(&*result.begin(), &*result.begin() + result.size());
      if ((!result.empty()) && (result[0] == s_delim))
         break;
      std::size_t i;
      for (i = 0; i < result.size(); ++i)
      {
         if (result[i] == s_delim)
            break;
      }
      result.erase(i);
      break;
   }
   if (result.empty())
      result = std::wstring(1, char(0));
   return result;
}

inline c_regex_traits<wchar_t>::char_class_type BOOST_REGEX_CALL c_regex_traits<wchar_t>::lookup_classname(const wchar_t* p1, const wchar_t* p2)
{
   using namespace BOOST_REGEX_DETAIL_NS;
   static const char_class_type masks[] =
   {
      0,
      char_class_alnum,
      char_class_alpha,
      char_class_blank,
      char_class_cntrl,
      char_class_digit,
      char_class_digit,
      char_class_graph,
      char_class_horizontal,
      char_class_lower,
      char_class_lower,
      char_class_print,
      char_class_punct,
      char_class_space,
      char_class_space,
      char_class_upper,
      char_class_unicode,
      char_class_upper,
      char_class_vertical,
      char_class_alnum | char_class_word,
      char_class_alnum | char_class_word,
      char_class_xdigit,
   };

   int idx = ::boost::BOOST_REGEX_DETAIL_NS::get_default_class_id(p1, p2);
   if (idx < 0)
   {
      std::wstring s(p1, p2);
      for (std::wstring::size_type i = 0; i < s.size(); ++i)
         s[i] = (std::towlower)(s[i]);
      idx = ::boost::BOOST_REGEX_DETAIL_NS::get_default_class_id(&*s.begin(), &*s.begin() + s.size());
   }
   BOOST_REGEX_ASSERT(idx + 1 < static_cast<int>(sizeof(masks) / sizeof(masks[0])));
   return masks[idx + 1];
}

inline bool BOOST_REGEX_CALL c_regex_traits<wchar_t>::isctype(wchar_t c, char_class_type mask)
{
   using namespace BOOST_REGEX_DETAIL_NS;
   return
      ((mask & char_class_space) && (std::iswspace)(c))
      || ((mask & char_class_print) && (std::iswprint)(c))
      || ((mask & char_class_cntrl) && (std::iswcntrl)(c))
      || ((mask & char_class_upper) && (std::iswupper)(c))
      || ((mask & char_class_lower) && (std::iswlower)(c))
      || ((mask & char_class_alpha) && (std::iswalpha)(c))
      || ((mask & char_class_digit) && (std::iswdigit)(c))
      || ((mask & char_class_punct) && (std::iswpunct)(c))
      || ((mask & char_class_xdigit) && (std::iswxdigit)(c))
      || ((mask & char_class_blank) && (std::iswspace)(c) && !::boost::BOOST_REGEX_DETAIL_NS::is_separator(c))
      || ((mask & char_class_word) && (c == '_'))
      || ((mask & char_class_unicode) && (c & ~static_cast<wchar_t>(0xff)))
      || ((mask & char_class_vertical) && (::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) || (c == L'\v')))
      || ((mask & char_class_horizontal) && (std::iswspace)(c) && !::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) && (c != L'\v'));
}

inline c_regex_traits<wchar_t>::string_type BOOST_REGEX_CALL c_regex_traits<wchar_t>::lookup_collatename(const wchar_t* p1, const wchar_t* p2)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
   std::string name(p1, p2);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
   name = ::boost::BOOST_REGEX_DETAIL_NS::lookup_default_collate_name(name);
   if (!name.empty())
      return string_type(name.begin(), name.end());
   if (p2 - p1 == 1)
      return string_type(1, *p1);
   return string_type();
}

inline int BOOST_REGEX_CALL c_regex_traits<wchar_t>::value(wchar_t c, int radix)
{
#ifdef BOOST_BORLANDC
   // workaround for broken wcstol:
   if ((std::iswxdigit)(c) == 0)
      return -1;
#endif
   wchar_t b[2] = { c, '\0', };
   wchar_t* ep;
   int result = std::wcstol(b, &ep, radix);
   if (ep == b)
      return -1;
   return result;
}

#endif

}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif




/* c_regex_traits.hpp
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
*/