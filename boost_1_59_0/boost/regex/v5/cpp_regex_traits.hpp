/*
 *
 * Copyright (c) 2004 John Maddock
 * Copyright 2011 Garmin Ltd. or its subsidiaries
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         cpp_regex_traits.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression traits class cpp_regex_traits.
  */

#ifndef BOOST_CPP_REGEX_TRAITS_HPP_INCLUDED
#define BOOST_CPP_REGEX_TRAITS_HPP_INCLUDED

#include <boost/regex/config.hpp>
#include <cstdint>
#include <locale>
#include <type_traits>

#include <boost/regex/pattern_except.hpp>
#include <boost/regex/v5/regex_traits_defaults.hpp>

#ifdef BOOST_HAS_THREADS
#include <mutex>
#endif
#include <boost/regex/v5/primary_transform.hpp>
#include <boost/regex/v5/object_cache.hpp>

#include <climits>
#include <ios>
#include <istream>

#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable:4786 4251)
#endif

namespace boost{ 

//
// forward declaration is needed by some compilers:
//
template <class charT>
class cpp_regex_traits;
   
namespace BOOST_REGEX_DETAIL_NS{

//
// class parser_buf:
// acts as a stream buffer which wraps around a pair of pointers:
//
template <class charT,
          class traits = ::std::char_traits<charT> >
class parser_buf : public ::std::basic_streambuf<charT, traits>
{
   typedef ::std::basic_streambuf<charT, traits> base_type;
   typedef typename base_type::int_type int_type;
   typedef typename base_type::char_type char_type;
   typedef typename base_type::pos_type pos_type;
   typedef ::std::streamsize streamsize;
   typedef typename base_type::off_type off_type;
public:
   parser_buf() : base_type() { setbuf(0, 0); }
   const charT* getnext() { return this->gptr(); }
protected:
   std::basic_streambuf<charT, traits>* setbuf(char_type* s, streamsize n) override;
   typename parser_buf<charT, traits>::pos_type seekpos(pos_type sp, ::std::ios_base::openmode which) override;
   typename parser_buf<charT, traits>::pos_type seekoff(off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which) override;
private:
   parser_buf& operator=(const parser_buf&);
   parser_buf(const parser_buf&);
};

template<class charT, class traits>
std::basic_streambuf<charT, traits>*
parser_buf<charT, traits>::setbuf(char_type* s, streamsize n)
{
   this->setg(s, s, s + n);
   return this;
}

template<class charT, class traits>
typename parser_buf<charT, traits>::pos_type
parser_buf<charT, traits>::seekoff(off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which)
{
   if(which & ::std::ios_base::out)
      return pos_type(off_type(-1));
   std::ptrdiff_t size = this->egptr() - this->eback();
   std::ptrdiff_t pos = this->gptr() - this->eback();
   charT* g = this->eback();
   switch(static_cast<std::intmax_t>(way))
   {
   case ::std::ios_base::beg:
      if((off < 0) || (off > size))
         return pos_type(off_type(-1));
      else
         this->setg(g, g + off, g + size);
      break;
   case ::std::ios_base::end:
      if((off < 0) || (off > size))
         return pos_type(off_type(-1));
      else
         this->setg(g, g + size - off, g + size);
      break;
   case ::std::ios_base::cur:
   {
      std::ptrdiff_t newpos = static_cast<std::ptrdiff_t>(pos + off);
      if((newpos < 0) || (newpos > size))
         return pos_type(off_type(-1));
      else
         this->setg(g, g + newpos, g + size);
      break;
   }
   default: ;
   }
#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable:4244)
#endif
   return static_cast<pos_type>(this->gptr() - this->eback());
#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif
}

template<class charT, class traits>
typename parser_buf<charT, traits>::pos_type
parser_buf<charT, traits>::seekpos(pos_type sp, ::std::ios_base::openmode which)
{
   if(which & ::std::ios_base::out)
      return pos_type(off_type(-1));
   off_type size = static_cast<off_type>(this->egptr() - this->eback());
   charT* g = this->eback();
   if(off_type(sp) <= size)
   {
      this->setg(g, g + off_type(sp), g + size);
   }
   return pos_type(off_type(-1));
}

//
// class cpp_regex_traits_base:
// acts as a container for locale and the facets we are using.
//
template <class charT>
struct cpp_regex_traits_base
{
   cpp_regex_traits_base(const std::locale& l)
   { (void)imbue(l); }
   std::locale imbue(const std::locale& l);

   std::locale m_locale;
   std::ctype<charT> const* m_pctype;
   std::messages<charT> const* m_pmessages;
   std::collate<charT> const* m_pcollate;

   bool operator<(const cpp_regex_traits_base& b)const
   {
      if(m_pctype == b.m_pctype)
      {
         if(m_pmessages == b.m_pmessages)
         {
            return m_pcollate < b.m_pcollate;
         }
         return m_pmessages < b.m_pmessages;
      }
      return m_pctype < b.m_pctype;
   }
   bool operator==(const cpp_regex_traits_base& b)const
   {
      return (m_pctype == b.m_pctype) 
         && (m_pmessages == b.m_pmessages) 
         && (m_pcollate == b.m_pcollate);
   }
};

template <class charT>
std::locale cpp_regex_traits_base<charT>::imbue(const std::locale& l)
{
   std::locale result(m_locale);
   m_locale = l;
   m_pctype = &std::use_facet<std::ctype<charT>>(l);
   m_pmessages = std::has_facet<std::messages<charT> >(l) ? &std::use_facet<std::messages<charT> >(l) : 0;
   m_pcollate = &std::use_facet<std::collate<charT> >(l);
   return result;
}

//
// class cpp_regex_traits_char_layer:
// implements methods that require specialization for narrow characters:
//
template <class charT>
class cpp_regex_traits_char_layer : public cpp_regex_traits_base<charT>
{
   typedef std::basic_string<charT> string_type;
   typedef std::map<charT, regex_constants::syntax_type> map_type;
   typedef typename map_type::const_iterator map_iterator_type;
public:
   cpp_regex_traits_char_layer(const std::locale& l)
      : cpp_regex_traits_base<charT>(l)
   {
      init();
   }
   cpp_regex_traits_char_layer(const cpp_regex_traits_base<charT>& b)
      : cpp_regex_traits_base<charT>(b)
   {
      init();
   }
   void init();

   regex_constants::syntax_type syntax_type(charT c)const
   {
      map_iterator_type i = m_char_map.find(c);
      return ((i == m_char_map.end()) ? 0 : i->second);
   }
   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      map_iterator_type i = m_char_map.find(c);
      if(i == m_char_map.end())
      {
         if(this->m_pctype->is(std::ctype_base::lower, c)) return regex_constants::escape_type_class;
         if(this->m_pctype->is(std::ctype_base::upper, c)) return regex_constants::escape_type_not_class;
         return 0;
      }
      return i->second;
   }

private:
   string_type get_default_message(regex_constants::syntax_type);
   // TODO: use a hash table when available!
   map_type m_char_map;
};

template <class charT>
void cpp_regex_traits_char_layer<charT>::init()
{
   // we need to start by initialising our syntax map so we know which
   // character is used for which purpose:
#ifndef __IBMCPP__
   typename std::messages<charT>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
   typename std::messages<charT>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
   std::string cat_name(cpp_regex_traits<charT>::get_catalog_name());
   if((!cat_name.empty()) && (this->m_pmessages != 0))
   {
      cat = this->m_pmessages->open(
         cat_name, 
         this->m_locale);
      if((int)cat < 0)
      {
         std::string m("Unable to open message catalog: ");
         std::runtime_error err(m + cat_name);
         boost::BOOST_REGEX_DETAIL_NS::raise_runtime_error(err);
      }
   }
   //
   // if we have a valid catalog then load our messages:
   //
   if((int)cat >= 0)
   {
#ifndef BOOST_NO_EXCEPTIONS
      try{
#endif
         for(regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
         {
            string_type mss = this->m_pmessages->get(cat, 0, i, get_default_message(i));
            for(typename string_type::size_type j = 0; j < mss.size(); ++j)
            {
               m_char_map[mss[j]] = i;
            }
         }
         this->m_pmessages->close(cat);
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
         if(this->m_pmessages)
            this->m_pmessages->close(cat);
         throw;
      }
#endif
   }
   else
   {
      for(regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
      {
         const char* ptr = get_default_syntax(i);
         while(ptr && *ptr)
         {
            m_char_map[this->m_pctype->widen(*ptr)] = i;
            ++ptr;
         }
      }
   }
}

template <class charT>
typename cpp_regex_traits_char_layer<charT>::string_type 
   cpp_regex_traits_char_layer<charT>::get_default_message(regex_constants::syntax_type i)
{
   const char* ptr = get_default_syntax(i);
   string_type result;
   while(ptr && *ptr)
   {
      result.append(1, this->m_pctype->widen(*ptr));
      ++ptr;
   }
   return result;
}

//
// specialized version for narrow characters:
//
template <>
class cpp_regex_traits_char_layer<char> : public cpp_regex_traits_base<char>
{
   typedef std::string string_type;
public:
   cpp_regex_traits_char_layer(const std::locale& l)
   : cpp_regex_traits_base<char>(l)
   {
      init();
   }
   cpp_regex_traits_char_layer(const cpp_regex_traits_base<char>& l)
   : cpp_regex_traits_base<char>(l)
   {
      init();
   }

   regex_constants::syntax_type syntax_type(char c)const
   {
      return m_char_map[static_cast<unsigned char>(c)];
   }
   regex_constants::escape_syntax_type escape_syntax_type(char c) const
   {
      return m_char_map[static_cast<unsigned char>(c)];
   }

private:
   regex_constants::syntax_type m_char_map[1u << CHAR_BIT];
   void init();
};

//
// class cpp_regex_traits_implementation:
// provides pimpl implementation for cpp_regex_traits.
//
template <class charT>
class cpp_regex_traits_implementation : public cpp_regex_traits_char_layer<charT>
{
public:
   typedef typename cpp_regex_traits<charT>::char_class_type      char_class_type;
   typedef typename std::ctype<charT>::mask                       native_mask_type;
   typedef typename std::make_unsigned<native_mask_type>::type    unsigned_native_mask_type;
   static const char_class_type mask_blank = 1u << 24;
   static const char_class_type mask_word = 1u << 25;
   static const char_class_type mask_unicode = 1u << 26;
   static const char_class_type mask_horizontal = 1u << 27;
   static const char_class_type mask_vertical = 1u << 28;

   typedef std::basic_string<charT> string_type;
   typedef charT char_type;
   //cpp_regex_traits_implementation();
   cpp_regex_traits_implementation(const std::locale& l)
      : cpp_regex_traits_char_layer<charT>(l)
   {
      init();
   }
   cpp_regex_traits_implementation(const cpp_regex_traits_base<charT>& l)
      : cpp_regex_traits_char_layer<charT>(l)
   {
      init();
   }
   std::string error_string(regex_constants::error_type n) const
   {
      if(!m_error_strings.empty())
      {
         std::map<int, std::string>::const_iterator p = m_error_strings.find(n);
         return (p == m_error_strings.end()) ? std::string(get_default_error_string(n)) : p->second;
      }
      return get_default_error_string(n);
   }
   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      char_class_type result = lookup_classname_imp(p1, p2);
      if(result == 0)
      {
         string_type temp(p1, p2);
         this->m_pctype->tolower(&*temp.begin(), &*temp.begin() + temp.size());
         result = lookup_classname_imp(&*temp.begin(), &*temp.begin() + temp.size());
      }
      return result;
   }
   string_type lookup_collatename(const charT* p1, const charT* p2) const;
   string_type transform_primary(const charT* p1, const charT* p2) const;
   string_type transform(const charT* p1, const charT* p2) const;
private:
   std::map<int, std::string>     m_error_strings;   // error messages indexed by numberic ID
   std::map<string_type, char_class_type>  m_custom_class_names; // character class names
   std::map<string_type, string_type>      m_custom_collate_names; // collating element names
   unsigned                       m_collate_type;    // the form of the collation string
   charT                          m_collate_delim;   // the collation group delimiter
   //
   // helpers:
   //
   char_class_type lookup_classname_imp(const charT* p1, const charT* p2) const;
   void init();
};

template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type const cpp_regex_traits_implementation<charT>::mask_blank;
template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type const cpp_regex_traits_implementation<charT>::mask_word;
template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type const cpp_regex_traits_implementation<charT>::mask_unicode;
template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type const cpp_regex_traits_implementation<charT>::mask_vertical;
template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type const cpp_regex_traits_implementation<charT>::mask_horizontal;

template <class charT>
typename cpp_regex_traits_implementation<charT>::string_type 
   cpp_regex_traits_implementation<charT>::transform_primary(const charT* p1, const charT* p2) const
{
   //
   // PRECONDITIONS:
   //
   // A bug in gcc 3.2 (and maybe other versions as well) treats
   // p1 as a null terminated string, for efficiency reasons 
   // we work around this elsewhere, but just assert here that
   // we adhere to gcc's (buggy) preconditions...
   //
   BOOST_REGEX_ASSERT(*p2 == 0);
   string_type result;
#if defined(_CPPLIB_VER)
   //
   // A bug in VC11 and 12 causes the program to hang if we pass a null-string
   // to std::collate::transform, but only for certain locales :-(
   // Probably effects Intel and Clang or any compiler using the VC std library (Dinkumware).
   //
   if(*p1 == 0)
   {
      return string_type(1, charT(0));
   }
#endif
   //
   // swallowing all exceptions here is a bad idea
   // however at least one std lib will always throw
   // std::bad_alloc for certain arguments...
   //
#ifndef BOOST_NO_EXCEPTIONS
   try{
#endif
      //
      // What we do here depends upon the format of the sort key returned by
      // sort key returned by this->transform:
      //
      switch(m_collate_type)
      {
      case sort_C:
      case sort_unknown:
         // the best we can do is translate to lower case, then get a regular sort key:
         {
            result.assign(p1, p2);
            this->m_pctype->tolower(&*result.begin(), &*result.begin() + result.size());
            result = this->m_pcollate->transform(&*result.begin(), &*result.begin() + result.size());
            break;
         }
      case sort_fixed:
         {
            // get a regular sort key, and then truncate it:
            result.assign(this->m_pcollate->transform(p1, p2));
            result.erase(this->m_collate_delim);
            break;
         }
      case sort_delim:
            // get a regular sort key, and then truncate everything after the delim:
            result.assign(this->m_pcollate->transform(p1, p2));
            std::size_t i;
            for(i = 0; i < result.size(); ++i)
            {
               if(result[i] == m_collate_delim)
                  break;
            }
            result.erase(i);
            break;
      }
#ifndef BOOST_NO_EXCEPTIONS
   }catch(...){}
#endif
   while((!result.empty()) && (charT(0) == *result.rbegin()))
      result.erase(result.size() - 1);
   if(result.empty())
   {
      // character is ignorable at the primary level:
      result = string_type(1, charT(0));
   }
   return result;
}

template <class charT>
typename cpp_regex_traits_implementation<charT>::string_type 
   cpp_regex_traits_implementation<charT>::transform(const charT* p1, const charT* p2) const
{
   //
   // PRECONDITIONS:
   //
   // A bug in gcc 3.2 (and maybe other versions as well) treats
   // p1 as a null terminated string, for efficiency reasons 
   // we work around this elsewhere, but just assert here that
   // we adhere to gcc's (buggy) preconditions...
   //
   BOOST_REGEX_ASSERT(*p2 == 0);
   //
   // swallowing all exceptions here is a bad idea
   // however at least one std lib will always throw
   // std::bad_alloc for certain arguments...
   //
   string_type result, result2;
#if defined(_CPPLIB_VER)
   //
   // A bug in VC11 and 12 causes the program to hang if we pass a null-string
   // to std::collate::transform, but only for certain locales :-(
   // Probably effects Intel and Clang or any compiler using the VC std library (Dinkumware).
   //
   if(*p1 == 0)
   {
      return result;
   }
#endif
#ifndef BOOST_NO_EXCEPTIONS
   try{
#endif
      result = this->m_pcollate->transform(p1, p2);
      //
      // some implementations (Dinkumware) append unnecessary trailing \0's:
      while((!result.empty()) && (charT(0) == *result.rbegin()))
         result.erase(result.size() - 1);
      //
      // We may have NULL's used as separators between sections of the collate string,
      // an example would be Boost.Locale.  We have no way to detect this case via
      // #defines since this can be used with any compiler/platform combination.
      // Unfortunately our state machine (which was devised when all implementations
      // used underlying C language API's) can't cope with that case.  One workaround
      // is to replace each character with 2, fortunately this code isn't used that
      // much as this is now slower than before :-(
      //
      typedef typename std::make_unsigned<charT>::type uchar_type;
      result2.reserve(result.size() * 2 + 2);
      for(unsigned i = 0; i < result.size(); ++i)
      {
         if(static_cast<uchar_type>(result[i]) == (std::numeric_limits<uchar_type>::max)())
         {
            result2.append(1, charT((std::numeric_limits<uchar_type>::max)())).append(1, charT('b'));
         }
         else
         {
            result2.append(1, static_cast<charT>(1 + static_cast<uchar_type>(result[i]))).append(1, charT('b') - 1);
         }
      }
      BOOST_REGEX_ASSERT(std::find(result2.begin(), result2.end(), charT(0)) == result2.end());
#ifndef BOOST_NO_EXCEPTIONS
   }
   catch(...)
   {
   }
#endif
   return result2;
}


template <class charT>
typename cpp_regex_traits_implementation<charT>::string_type 
   cpp_regex_traits_implementation<charT>::lookup_collatename(const charT* p1, const charT* p2) const
{
   typedef typename std::map<string_type, string_type>::const_iterator iter_type;
   if(!m_custom_collate_names.empty())
   {
      iter_type pos = m_custom_collate_names.find(string_type(p1, p2));
      if(pos != m_custom_collate_names.end())
         return pos->second;
   }
   std::string name(p1, p2);
   name = lookup_default_collate_name(name);
   if(!name.empty())
      return string_type(name.begin(), name.end());
   if(p2 - p1 == 1)
      return string_type(1, *p1);
   return string_type();
}

template <class charT>
void cpp_regex_traits_implementation<charT>::init()
{
#ifndef __IBMCPP__
   typename std::messages<charT>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
   typename std::messages<charT>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
   std::string cat_name(cpp_regex_traits<charT>::get_catalog_name());
   if((!cat_name.empty()) && (this->m_pmessages != 0))
   {
      cat = this->m_pmessages->open(
         cat_name, 
         this->m_locale);
      if((int)cat < 0)
      {
         std::string m("Unable to open message catalog: ");
         std::runtime_error err(m + cat_name);
         boost::BOOST_REGEX_DETAIL_NS::raise_runtime_error(err);
      }
   }
   //
   // if we have a valid catalog then load our messages:
   //
   if((int)cat >= 0)
   {
      //
      // Error messages:
      //
      for(boost::regex_constants::error_type i = static_cast<boost::regex_constants::error_type>(0); 
         i <= boost::regex_constants::error_unknown; 
         i = static_cast<boost::regex_constants::error_type>(i + 1))
      {
         const char* p = get_default_error_string(i);
         string_type default_message;
         while(*p)
         {
            default_message.append(1, this->m_pctype->widen(*p));
            ++p;
         }
         string_type s = this->m_pmessages->get(cat, 0, i+200, default_message);
         std::string result;
         for(std::string::size_type j = 0; j < s.size(); ++j)
         {
            result.append(1, this->m_pctype->narrow(s[j], 0));
         }
         m_error_strings[i] = result;
      }
      //
      // Custom class names:
      //
      static const char_class_type masks[16] = 
      {
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::alnum),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::alpha),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::cntrl),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::digit),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::graph),
         cpp_regex_traits_implementation<charT>::mask_horizontal,
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::lower),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::print),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::punct),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::space),
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::upper),
         cpp_regex_traits_implementation<charT>::mask_vertical,
         static_cast<unsigned_native_mask_type>(std::ctype<charT>::xdigit),
         cpp_regex_traits_implementation<charT>::mask_blank,
         cpp_regex_traits_implementation<charT>::mask_word,
         cpp_regex_traits_implementation<charT>::mask_unicode,
      };
      static const string_type null_string;
      for(unsigned int j = 0; j <= 13; ++j)
      {
         string_type s(this->m_pmessages->get(cat, 0, j+300, null_string));
         if(!s.empty())
            this->m_custom_class_names[s] = masks[j];
      }
   }
   //
   // get the collation format used by m_pcollate:
   //
   m_collate_type = BOOST_REGEX_DETAIL_NS::find_sort_syntax(this, &m_collate_delim);
}

template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type 
   cpp_regex_traits_implementation<charT>::lookup_classname_imp(const charT* p1, const charT* p2) const
{
   static const char_class_type masks[22] = 
   {
      0,
      static_cast<unsigned_native_mask_type>(std::ctype<char>::alnum),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::alpha),
      cpp_regex_traits_implementation<charT>::mask_blank,
      static_cast<unsigned_native_mask_type>(std::ctype<char>::cntrl),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::digit),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::digit),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::graph),
      cpp_regex_traits_implementation<charT>::mask_horizontal,
      static_cast<unsigned_native_mask_type>(std::ctype<char>::lower),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::lower),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::print),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::punct),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::space),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::space),
      static_cast<unsigned_native_mask_type>(std::ctype<char>::upper),
      cpp_regex_traits_implementation<charT>::mask_unicode,
      static_cast<unsigned_native_mask_type>(std::ctype<char>::upper),
      cpp_regex_traits_implementation<charT>::mask_vertical,
      static_cast<unsigned_native_mask_type>(std::ctype<char>::alnum) | cpp_regex_traits_implementation<charT>::mask_word, 
      static_cast<unsigned_native_mask_type>(std::ctype<char>::alnum) | cpp_regex_traits_implementation<charT>::mask_word, 
      static_cast<unsigned_native_mask_type>(std::ctype<char>::xdigit),
   };
   if(!m_custom_class_names.empty())
   {
      typedef typename std::map<std::basic_string<charT>, char_class_type>::const_iterator map_iter;
      map_iter pos = m_custom_class_names.find(string_type(p1, p2));
      if(pos != m_custom_class_names.end())
         return pos->second;
   }
   std::size_t state_id = 1 + BOOST_REGEX_DETAIL_NS::get_default_class_id(p1, p2);
   BOOST_REGEX_ASSERT(state_id < sizeof(masks) / sizeof(masks[0]));
   return masks[state_id];
}

template <class charT>
inline std::shared_ptr<const cpp_regex_traits_implementation<charT> > create_cpp_regex_traits(const std::locale& l)
{
   cpp_regex_traits_base<charT> key(l);
   return ::boost::object_cache<cpp_regex_traits_base<charT>, cpp_regex_traits_implementation<charT> >::get(key, 5);
}

} // BOOST_REGEX_DETAIL_NS

template <class charT>
class cpp_regex_traits
{
private:
   typedef std::ctype<charT>            ctype_type;
public:
   typedef charT                        char_type;
   typedef std::size_t                  size_type;
   typedef std::basic_string<char_type> string_type;
   typedef std::locale                  locale_type;
   typedef std::uint_least32_t          char_class_type;

   struct boost_extensions_tag{};

   cpp_regex_traits()
      : m_pimpl(BOOST_REGEX_DETAIL_NS::create_cpp_regex_traits<charT>(std::locale()))
   { }
   static size_type length(const char_type* p)
   {
      return std::char_traits<charT>::length(p);
   }
   regex_constants::syntax_type syntax_type(charT c)const
   {
      return m_pimpl->syntax_type(c);
   }
   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      return m_pimpl->escape_syntax_type(c);
   }
   charT translate(charT c) const
   {
      return c;
   }
   charT translate_nocase(charT c) const
   {
      return m_pimpl->m_pctype->tolower(c);
   }
   charT translate(charT c, bool icase) const
   {
      return icase ? m_pimpl->m_pctype->tolower(c) : c;
   }
   charT tolower(charT c) const
   {
      return m_pimpl->m_pctype->tolower(c);
   }
   charT toupper(charT c) const
   {
      return m_pimpl->m_pctype->toupper(c);
   }
   string_type transform(const charT* p1, const charT* p2) const
   {
      return m_pimpl->transform(p1, p2);
   }
   string_type transform_primary(const charT* p1, const charT* p2) const
   {
      return m_pimpl->transform_primary(p1, p2);
   }
   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      return m_pimpl->lookup_classname(p1, p2);
   }
   string_type lookup_collatename(const charT* p1, const charT* p2) const
   {
      return m_pimpl->lookup_collatename(p1, p2);
   }
   bool isctype(charT c, char_class_type f) const
   {
      typedef typename std::ctype<charT>::mask ctype_mask;

      static const ctype_mask mask_base = 
         static_cast<ctype_mask>(
            std::ctype<charT>::alnum 
            | std::ctype<charT>::alpha
            | std::ctype<charT>::cntrl
            | std::ctype<charT>::digit
            | std::ctype<charT>::graph
            | std::ctype<charT>::lower
            | std::ctype<charT>::print
            | std::ctype<charT>::punct
            | std::ctype<charT>::space
            | std::ctype<charT>::upper
            | std::ctype<charT>::xdigit);

      if((f & mask_base) 
         && (m_pimpl->m_pctype->is(
            static_cast<ctype_mask>(f & mask_base), c)))
         return true;
      else if((f & BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT>::mask_unicode) && BOOST_REGEX_DETAIL_NS::is_extended(c))
         return true;
      else if((f & BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT>::mask_word) && (c == '_'))
         return true;
      else if((f & BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT>::mask_blank) 
         && m_pimpl->m_pctype->is(std::ctype<charT>::space, c)
         && !BOOST_REGEX_DETAIL_NS::is_separator(c))
         return true;
      else if((f & BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT>::mask_vertical) 
         && (::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) || (c == '\v')))
         return true;
      else if((f & BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT>::mask_horizontal) 
         && this->isctype(c, std::ctype<charT>::space) && !this->isctype(c, BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT>::mask_vertical))
         return true;
#ifdef __CYGWIN__
      //
      // Cygwin has a buggy ctype facet, see https://www.cygwin.com/ml/cygwin/2012-08/msg00178.html:
      //
      else if((f & std::ctype<charT>::xdigit) == std::ctype<charT>::xdigit)
      {
         if((c >= 'a') && (c <= 'f'))
            return true;
         if((c >= 'A') && (c <= 'F'))
            return true;
      }
#endif
      return false;
   }
   std::intmax_t toi(const charT*& p1, const charT* p2, int radix)const;
   int value(charT c, int radix)const
   {
      const charT* pc = &c;
      return (int)toi(pc, pc + 1, radix);
   }
   locale_type imbue(locale_type l)
   {
      std::locale result(getloc());
      m_pimpl = BOOST_REGEX_DETAIL_NS::create_cpp_regex_traits<charT>(l);
      return result;
   }
   locale_type getloc()const
   {
      return m_pimpl->m_locale;
   }
   std::string error_string(regex_constants::error_type n) const
   {
      return m_pimpl->error_string(n);
   }

   //
   // extension:
   // set the name of the message catalog in use (defaults to "boost_regex").
   //
   static std::string catalog_name(const std::string& name);
   static std::string get_catalog_name();

private:
   std::shared_ptr<const BOOST_REGEX_DETAIL_NS::cpp_regex_traits_implementation<charT> > m_pimpl;
   //
   // catalog name handler:
   //
   static std::string& get_catalog_name_inst();

#ifdef BOOST_HAS_THREADS
   static std::mutex& get_mutex_inst();
#endif
};


template <class charT>
std::intmax_t cpp_regex_traits<charT>::toi(const charT*& first, const charT* last, int radix)const
{
   BOOST_REGEX_DETAIL_NS::parser_buf<charT>   sbuf;            // buffer for parsing numbers.
   std::basic_istream<charT>      is(&sbuf);       // stream for parsing numbers.

   // we do NOT want to parse any thousands separators inside the stream:
   last = std::find(first, last, std::use_facet<std::numpunct<charT>>(is.getloc()).thousands_sep());

   sbuf.pubsetbuf(const_cast<charT*>(static_cast<const charT*>(first)), static_cast<std::streamsize>(last-first));
   is.clear();
   if(std::abs(radix) == 16) is >> std::hex;
   else if(std::abs(radix) == 8) is >> std::oct;
   else is >> std::dec;
   std::intmax_t val;
   if(is >> val)
   {
      first = first + ((last - first) - sbuf.in_avail());
      return val;
   }
   else
      return -1;
}

template <class charT>
std::string cpp_regex_traits<charT>::catalog_name(const std::string& name)
{
#ifdef BOOST_HAS_THREADS
   std::lock_guard<std::mutex> lk(get_mutex_inst());
#endif
   std::string result(get_catalog_name_inst());
   get_catalog_name_inst() = name;
   return result;
}

template <class charT>
std::string& cpp_regex_traits<charT>::get_catalog_name_inst()
{
   static std::string s_name;
   return s_name;
}

template <class charT>
std::string cpp_regex_traits<charT>::get_catalog_name()
{
#ifdef BOOST_HAS_THREADS
   std::lock_guard<std::mutex> lk(get_mutex_inst());
#endif
   std::string result(get_catalog_name_inst());
   return result;
}

#ifdef BOOST_HAS_THREADS
template <class charT>
std::mutex& cpp_regex_traits<charT>::get_mutex_inst()
{
   static std::mutex s_mutex;
   return s_mutex;
}
#endif

namespace BOOST_REGEX_DETAIL_NS {

   inline void cpp_regex_traits_char_layer<char>::init()
   {
      // we need to start by initialising our syntax map so we know which
      // character is used for which purpose:
      std::memset(m_char_map, 0, sizeof(m_char_map));
#ifndef __IBMCPP__
      std::messages<char>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
      std::messages<char>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
      std::string cat_name(cpp_regex_traits<char>::get_catalog_name());
      if ((!cat_name.empty()) && (m_pmessages != 0))
      {
         cat = this->m_pmessages->open(
            cat_name,
            this->m_locale);
         if ((int)cat < 0)
         {
            std::string m("Unable to open message catalog: ");
            std::runtime_error err(m + cat_name);
            boost::BOOST_REGEX_DETAIL_NS::raise_runtime_error(err);
         }
      }
      //
      // if we have a valid catalog then load our messages:
      //
      if ((int)cat >= 0)
      {
#ifndef BOOST_NO_EXCEPTIONS
         try {
#endif
            for (regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
            {
               string_type mss = this->m_pmessages->get(cat, 0, i, get_default_syntax(i));
               for (string_type::size_type j = 0; j < mss.size(); ++j)
               {
                  m_char_map[static_cast<unsigned char>(mss[j])] = i;
               }
            }
            this->m_pmessages->close(cat);
#ifndef BOOST_NO_EXCEPTIONS
         }
         catch (...)
         {
            this->m_pmessages->close(cat);
            throw;
         }
#endif
      }
      else
      {
         for (regex_constants::syntax_type j = 1; j < regex_constants::syntax_max; ++j)
         {
            const char* ptr = get_default_syntax(j);
            while (ptr && *ptr)
            {
               m_char_map[static_cast<unsigned char>(*ptr)] = j;
               ++ptr;
            }
         }
      }
      //
      // finish off by calculating our escape types:
      //
      unsigned char i = 'A';
      do
      {
         if (m_char_map[i] == 0)
         {
            if (this->m_pctype->is(std::ctype_base::lower, i))
               m_char_map[i] = regex_constants::escape_type_class;
            else if (this->m_pctype->is(std::ctype_base::upper, i))
               m_char_map[i] = regex_constants::escape_type_not_class;
         }
      } while (0xFF != i++);
   }

} // namespace detail


} // boost

#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif


#endif

/* cpp_regex_traits.hpp
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
*/