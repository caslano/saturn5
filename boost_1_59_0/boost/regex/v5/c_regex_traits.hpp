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

#include <boost/regex/config.hpp>
#include <boost/regex/v5/regex_workaround.hpp>
#include <cctype>

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
   typedef std::uint32_t char_class_type;

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

   static string_type  transform(const char* p1, const char* p2);
   static string_type  transform_primary(const char* p1, const char* p2);

   static char_class_type  lookup_classname(const char* p1, const char* p2);
   static string_type  lookup_collatename(const char* p1, const char* p2);

   static bool  isctype(char, char_class_type);
   static int  value(char, int);

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
   typedef std::uint32_t char_class_type;

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

   static string_type  transform(const wchar_t* p1, const wchar_t* p2);
   static string_type  transform_primary(const wchar_t* p1, const wchar_t* p2);

   static char_class_type  lookup_classname(const wchar_t* p1, const wchar_t* p2);
   static string_type  lookup_collatename(const wchar_t* p1, const wchar_t* p2);

   static bool  isctype(wchar_t, char_class_type);
   static int  value(wchar_t, int);

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

inline c_regex_traits<char>::string_type  c_regex_traits<char>::transform(const char* p1, const char* p2)
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

inline c_regex_traits<char>::string_type  c_regex_traits<char>::transform_primary(const char* p1, const char* p2)
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

inline c_regex_traits<char>::char_class_type  c_regex_traits<char>::lookup_classname(const char* p1, const char* p2)
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

inline bool  c_regex_traits<char>::isctype(char c, char_class_type mask)
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

inline c_regex_traits<char>::string_type  c_regex_traits<char>::lookup_collatename(const char* p1, const char* p2)
{
   std::string s(p1, p2);
   s = ::boost::BOOST_REGEX_DETAIL_NS::lookup_default_collate_name(s);
   if (s.empty() && (p2 - p1 == 1))
      s.append(1, *p1);
   return s;
}

inline int  c_regex_traits<char>::value(char c, int radix)
{
   char b[2] = { c, '\0', };
   char* ep;
   int result = std::strtol(b, &ep, radix);
   if (ep == b)
      return -1;
   return result;
}

#ifndef BOOST_NO_WREGEX

inline c_regex_traits<wchar_t>::string_type  c_regex_traits<wchar_t>::transform(const wchar_t* p1, const wchar_t* p2)
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

inline c_regex_traits<wchar_t>::string_type  c_regex_traits<wchar_t>::transform_primary(const wchar_t* p1, const wchar_t* p2)
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

inline c_regex_traits<wchar_t>::char_class_type  c_regex_traits<wchar_t>::lookup_classname(const wchar_t* p1, const wchar_t* p2)
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

inline bool  c_regex_traits<wchar_t>::isctype(wchar_t c, char_class_type mask)
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

inline c_regex_traits<wchar_t>::string_type  c_regex_traits<wchar_t>::lookup_collatename(const wchar_t* p1, const wchar_t* p2)
{
   std::string name;
   // Usual msvc warning suppression does not work here with std::string template constructor.... use a workaround instead:
   for (const wchar_t* pos = p1; pos != p2; ++pos)
      name.push_back((char)*pos);
   name = ::boost::BOOST_REGEX_DETAIL_NS::lookup_default_collate_name(name);
   if (!name.empty())
      return string_type(name.begin(), name.end());
   if (p2 - p1 == 1)
      return string_type(1, *p1);
   return string_type();
}

inline int  c_regex_traits<wchar_t>::value(wchar_t c, int radix)
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

#endif




/* c_regex_traits.hpp
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
*/