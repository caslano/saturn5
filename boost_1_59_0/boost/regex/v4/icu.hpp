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
  *   FILE         icu.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Unicode regular expressions on top of the ICU Library.
  */

#ifndef BOOST_REGEX_ICU_V4_HPP
#define BOOST_REGEX_ICU_V4_HPP

#include <boost/config.hpp>
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/coll.h>
#include <boost/regex.hpp>
#include <boost/regex/v4/unicode_iterator.hpp>
#include <boost/mpl/int_fwd.hpp>
#include <boost/static_assert.hpp>
#include <bitset>

#ifdef BOOST_MSVC
#pragma warning (push)
#pragma warning (disable: 4251)
#endif

namespace boost {

   namespace BOOST_REGEX_DETAIL_NS {

      // 
      // Implementation details:
      //
      class icu_regex_traits_implementation
      {
         typedef UChar32                      char_type;
         typedef std::size_t                  size_type;
         typedef std::vector<char_type>       string_type;
         typedef U_NAMESPACE_QUALIFIER Locale locale_type;
         typedef boost::uint_least32_t        char_class_type;
      public:
         icu_regex_traits_implementation(const U_NAMESPACE_QUALIFIER Locale& l)
            : m_locale(l)
         {
            UErrorCode success = U_ZERO_ERROR;
            m_collator.reset(U_NAMESPACE_QUALIFIER Collator::createInstance(l, success));
            if (U_SUCCESS(success) == 0)
               init_error();
            m_collator->setStrength(U_NAMESPACE_QUALIFIER Collator::IDENTICAL);
            success = U_ZERO_ERROR;
            m_primary_collator.reset(U_NAMESPACE_QUALIFIER Collator::createInstance(l, success));
            if (U_SUCCESS(success) == 0)
               init_error();
            m_primary_collator->setStrength(U_NAMESPACE_QUALIFIER Collator::PRIMARY);
         }
         U_NAMESPACE_QUALIFIER Locale getloc()const
         {
            return m_locale;
         }
         string_type do_transform(const char_type* p1, const char_type* p2, const U_NAMESPACE_QUALIFIER Collator* pcoll) const
         {
            // TODO make thread safe!!!! :
            typedef u32_to_u16_iterator<const char_type*, ::UChar> itt;
            itt i(p1), j(p2);
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
            std::vector< ::UChar> t(i, j);
#else
            std::vector< ::UChar> t;
            while (i != j)
               t.push_back(*i++);
#endif
            ::uint8_t result[100];
            ::int32_t len;
            if (!t.empty())
               len = pcoll->getSortKey(&*t.begin(), static_cast< ::int32_t>(t.size()), result, sizeof(result));
            else
               len = pcoll->getSortKey(static_cast<UChar const*>(0), static_cast< ::int32_t>(0), result, sizeof(result));
            if (std::size_t(len) > sizeof(result))
            {
               scoped_array< ::uint8_t> presult(new ::uint8_t[len + 1]);
               if (!t.empty())
                  len = pcoll->getSortKey(&*t.begin(), static_cast< ::int32_t>(t.size()), presult.get(), len + 1);
               else
                  len = pcoll->getSortKey(static_cast<UChar const*>(0), static_cast< ::int32_t>(0), presult.get(), len + 1);
               if ((0 == presult[len - 1]) && (len > 1))
                  --len;
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
               return string_type(presult.get(), presult.get() + len);
#else
               string_type sresult;
               ::uint8_t const* ia = presult.get();
               ::uint8_t const* ib = presult.get() + len;
               while (ia != ib)
                  sresult.push_back(*ia++);
               return sresult;
#endif
            }
            if ((0 == result[len - 1]) && (len > 1))
               --len;
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
            return string_type(result, result + len);
#else
            string_type sresult;
            ::uint8_t const* ia = result;
            ::uint8_t const* ib = result + len;
            while (ia != ib)
               sresult.push_back(*ia++);
            return sresult;
#endif
         }
         string_type transform(const char_type* p1, const char_type* p2) const
         {
            return do_transform(p1, p2, m_collator.get());
         }
         string_type transform_primary(const char_type* p1, const char_type* p2) const
         {
            return do_transform(p1, p2, m_primary_collator.get());
         }
      private:
         void init_error()
         {
            std::runtime_error e("Could not initialize ICU resources");
            boost::throw_exception(e);
         }
         U_NAMESPACE_QUALIFIER Locale m_locale;                                  // The ICU locale that we're using
         boost::scoped_ptr< U_NAMESPACE_QUALIFIER Collator> m_collator;          // The full collation object
         boost::scoped_ptr< U_NAMESPACE_QUALIFIER Collator> m_primary_collator;  // The primary collation object
      };

      inline boost::shared_ptr<icu_regex_traits_implementation> get_icu_regex_traits_implementation(const U_NAMESPACE_QUALIFIER Locale& loc)
      {
         return boost::shared_ptr<icu_regex_traits_implementation>(new icu_regex_traits_implementation(loc));
      }

   }

   class icu_regex_traits
   {
   public:
      typedef UChar32                      char_type;
      typedef std::size_t                  size_type;
      typedef std::vector<char_type>       string_type;
      typedef U_NAMESPACE_QUALIFIER Locale locale_type;
#ifdef BOOST_NO_INT64_T
      typedef std::bitset<64>              char_class_type;
#else
      typedef boost::uint64_t              char_class_type;
#endif

      struct boost_extensions_tag {};

      icu_regex_traits()
         : m_pimpl(BOOST_REGEX_DETAIL_NS::get_icu_regex_traits_implementation(U_NAMESPACE_QUALIFIER Locale()))
      {
      }
      static size_type length(const char_type* p)
      {
         size_type result = 0;
         while (*p)
         {
            ++p;
            ++result;
         }
         return result;
      }
      ::boost::regex_constants::syntax_type syntax_type(char_type c)const
      {
         return ((c < 0x7f) && (c > 0)) ? BOOST_REGEX_DETAIL_NS::get_default_syntax_type(static_cast<char>(c)) : regex_constants::syntax_char;
      }
      ::boost::regex_constants::escape_syntax_type escape_syntax_type(char_type c) const
      {
         return ((c < 0x7f) && (c > 0)) ? BOOST_REGEX_DETAIL_NS::get_default_escape_syntax_type(static_cast<char>(c)) : regex_constants::syntax_char;
      }
      char_type translate(char_type c) const
      {
         return c;
      }
      char_type translate_nocase(char_type c) const
      {
         return ::u_foldCase(c, U_FOLD_CASE_DEFAULT);
      }
      char_type translate(char_type c, bool icase) const
      {
         return icase ? translate_nocase(c) : translate(c);
      }
      char_type tolower(char_type c) const
      {
         return ::u_tolower(c);
      }
      char_type toupper(char_type c) const
      {
         return ::u_toupper(c);
      }
      string_type transform(const char_type* p1, const char_type* p2) const
      {
         return m_pimpl->transform(p1, p2);
      }
      string_type transform_primary(const char_type* p1, const char_type* p2) const
      {
         return m_pimpl->transform_primary(p1, p2);
      }
      char_class_type lookup_classname(const char_type* p1, const char_type* p2) const
      {
         static const char_class_type mask_blank = char_class_type(1) << offset_blank;
         static const char_class_type mask_space = char_class_type(1) << offset_space;
         static const char_class_type mask_xdigit = char_class_type(1) << offset_xdigit;
         static const char_class_type mask_underscore = char_class_type(1) << offset_underscore;
         static const char_class_type mask_unicode = char_class_type(1) << offset_unicode;
         static const char_class_type mask_any = char_class_type(1) << offset_any;
         static const char_class_type mask_ascii = char_class_type(1) << offset_ascii;
         static const char_class_type mask_horizontal = char_class_type(1) << offset_horizontal;
         static const char_class_type mask_vertical = char_class_type(1) << offset_vertical;

         static const char_class_type masks[] =
         {
            0,
            U_GC_L_MASK | U_GC_ND_MASK,
            U_GC_L_MASK,
            mask_blank,
            U_GC_CC_MASK | U_GC_CF_MASK | U_GC_ZL_MASK | U_GC_ZP_MASK,
            U_GC_ND_MASK,
            U_GC_ND_MASK,
            (0x3FFFFFFFu) & ~(U_GC_CC_MASK | U_GC_CF_MASK | U_GC_CS_MASK | U_GC_CN_MASK | U_GC_Z_MASK),
            mask_horizontal,
            U_GC_LL_MASK,
            U_GC_LL_MASK,
            ~(U_GC_C_MASK),
            U_GC_P_MASK,
            char_class_type(U_GC_Z_MASK) | mask_space,
            char_class_type(U_GC_Z_MASK) | mask_space,
            U_GC_LU_MASK,
            mask_unicode,
            U_GC_LU_MASK,
            mask_vertical,
            char_class_type(U_GC_L_MASK | U_GC_ND_MASK | U_GC_MN_MASK) | mask_underscore,
            char_class_type(U_GC_L_MASK | U_GC_ND_MASK | U_GC_MN_MASK) | mask_underscore,
            char_class_type(U_GC_ND_MASK) | mask_xdigit,
         };

         int idx = ::boost::BOOST_REGEX_DETAIL_NS::get_default_class_id(p1, p2);
         if (idx >= 0)
            return masks[idx + 1];
         char_class_type result = lookup_icu_mask(p1, p2);
         if (result != 0)
            return result;

         if (idx < 0)
         {
            string_type s(p1, p2);
            string_type::size_type i = 0;
            while (i < s.size())
            {
               s[i] = static_cast<char>((::u_tolower)(s[i]));
               if (::u_isspace(s[i]) || (s[i] == '-') || (s[i] == '_'))
                  s.erase(s.begin() + i, s.begin() + i + 1);
               else
               {
                  s[i] = static_cast<char>((::u_tolower)(s[i]));
                  ++i;
               }
            }
            if (!s.empty())
               idx = ::boost::BOOST_REGEX_DETAIL_NS::get_default_class_id(&*s.begin(), &*s.begin() + s.size());
            if (idx >= 0)
               return masks[idx + 1];
            if (!s.empty())
               result = lookup_icu_mask(&*s.begin(), &*s.begin() + s.size());
            if (result != 0)
               return result;
         }
         BOOST_ASSERT(std::size_t(idx + 1) < sizeof(masks) / sizeof(masks[0]));
         return masks[idx + 1];
      }
      string_type lookup_collatename(const char_type* p1, const char_type* p2) const
      {
         string_type result;
#ifdef BOOST_NO_CXX98_BINDERS
         if (std::find_if(p1, p2, std::bind(std::greater< ::UChar32>(), std::placeholders::_1, 0x7f)) == p2)
#else
         if (std::find_if(p1, p2, std::bind2nd(std::greater< ::UChar32>(), 0x7f)) == p2)
#endif
         {
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
            std::string s(p1, p2);
#else
            std::string s;
            const char_type* p3 = p1;
            while (p3 != p2)
               s.append(1, *p3++);
#endif
            // Try Unicode name:
            UErrorCode err = U_ZERO_ERROR;
            UChar32 c = ::u_charFromName(U_UNICODE_CHAR_NAME, s.c_str(), &err);
            if (U_SUCCESS(err))
            {
               result.push_back(c);
               return result;
            }
            // Try Unicode-extended name:
            err = U_ZERO_ERROR;
            c = ::u_charFromName(U_EXTENDED_CHAR_NAME, s.c_str(), &err);
            if (U_SUCCESS(err))
            {
               result.push_back(c);
               return result;
            }
            // try POSIX name:
            s = ::boost::BOOST_REGEX_DETAIL_NS::lookup_default_collate_name(s);
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
            result.assign(s.begin(), s.end());
#else
            result.clear();
            std::string::const_iterator si, sj;
            si = s.begin();
            sj = s.end();
            while (si != sj)
               result.push_back(*si++);
#endif
         }
         if (result.empty() && (p2 - p1 == 1))
            result.push_back(*p1);
         return result;
      }
      bool isctype(char_type c, char_class_type f) const
      {
         static const char_class_type mask_blank = char_class_type(1) << offset_blank;
         static const char_class_type mask_space = char_class_type(1) << offset_space;
         static const char_class_type mask_xdigit = char_class_type(1) << offset_xdigit;
         static const char_class_type mask_underscore = char_class_type(1) << offset_underscore;
         static const char_class_type mask_unicode = char_class_type(1) << offset_unicode;
         static const char_class_type mask_any = char_class_type(1) << offset_any;
         static const char_class_type mask_ascii = char_class_type(1) << offset_ascii;
         static const char_class_type mask_horizontal = char_class_type(1) << offset_horizontal;
         static const char_class_type mask_vertical = char_class_type(1) << offset_vertical;

         // check for standard catagories first:
         char_class_type m = char_class_type(static_cast<char_class_type>(1) << u_charType(c));
         if ((m & f) != 0)
            return true;
         // now check for special cases:
         if (((f & mask_blank) != 0) && u_isblank(c))
            return true;
         if (((f & mask_space) != 0) && u_isspace(c))
            return true;
         if (((f & mask_xdigit) != 0) && (u_digit(c, 16) >= 0))
            return true;
         if (((f & mask_unicode) != 0) && (c >= 0x100))
            return true;
         if (((f & mask_underscore) != 0) && (c == '_'))
            return true;
         if (((f & mask_any) != 0) && (c <= 0x10FFFF))
            return true;
         if (((f & mask_ascii) != 0) && (c <= 0x7F))
            return true;
         if (((f & mask_vertical) != 0) && (::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) || (c == static_cast<char_type>('\v')) || (m == U_GC_ZL_MASK) || (m == U_GC_ZP_MASK)))
            return true;
         if (((f & mask_horizontal) != 0) && !::boost::BOOST_REGEX_DETAIL_NS::is_separator(c) && u_isspace(c) && (c != static_cast<char_type>('\v')))
            return true;
         return false;
      }
      boost::intmax_t toi(const char_type*& p1, const char_type* p2, int radix)const
      {
         return BOOST_REGEX_DETAIL_NS::global_toi(p1, p2, radix, *this);
      }
      int value(char_type c, int radix)const
      {
         return u_digit(c, static_cast< ::int8_t>(radix));
      }
      locale_type imbue(locale_type l)
      {
         locale_type result(m_pimpl->getloc());
         m_pimpl = BOOST_REGEX_DETAIL_NS::get_icu_regex_traits_implementation(l);
         return result;
      }
      locale_type getloc()const
      {
         return locale_type();
      }
      std::string error_string(::boost::regex_constants::error_type n) const
      {
         return BOOST_REGEX_DETAIL_NS::get_default_error_string(n);
      }
   private:
      icu_regex_traits(const icu_regex_traits&);
      icu_regex_traits& operator=(const icu_regex_traits&);

      //
      // define the bitmasks offsets we need for additional character properties:
      //
      enum {
         offset_blank = U_CHAR_CATEGORY_COUNT,
         offset_space = U_CHAR_CATEGORY_COUNT + 1,
         offset_xdigit = U_CHAR_CATEGORY_COUNT + 2,
         offset_underscore = U_CHAR_CATEGORY_COUNT + 3,
         offset_unicode = U_CHAR_CATEGORY_COUNT + 4,
         offset_any = U_CHAR_CATEGORY_COUNT + 5,
         offset_ascii = U_CHAR_CATEGORY_COUNT + 6,
         offset_horizontal = U_CHAR_CATEGORY_COUNT + 7,
         offset_vertical = U_CHAR_CATEGORY_COUNT + 8
      };

      static char_class_type lookup_icu_mask(const ::UChar32* p1, const ::UChar32* p2)
      {
         static const char_class_type mask_blank = char_class_type(1) << offset_blank;
         static const char_class_type mask_space = char_class_type(1) << offset_space;
         static const char_class_type mask_xdigit = char_class_type(1) << offset_xdigit;
         static const char_class_type mask_underscore = char_class_type(1) << offset_underscore;
         static const char_class_type mask_unicode = char_class_type(1) << offset_unicode;
         static const char_class_type mask_any = char_class_type(1) << offset_any;
         static const char_class_type mask_ascii = char_class_type(1) << offset_ascii;
         static const char_class_type mask_horizontal = char_class_type(1) << offset_horizontal;
         static const char_class_type mask_vertical = char_class_type(1) << offset_vertical;

         static const ::UChar32 prop_name_table[] = {
            /* any */  'a', 'n', 'y',
            /* ascii */  'a', 's', 'c', 'i', 'i',
            /* assigned */  'a', 's', 's', 'i', 'g', 'n', 'e', 'd',
            /* c* */  'c', '*',
            /* cc */  'c', 'c',
            /* cf */  'c', 'f',
            /* closepunctuation */  'c', 'l', 'o', 's', 'e', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* cn */  'c', 'n',
            /* co */  'c', 'o',
            /* connectorpunctuation */  'c', 'o', 'n', 'n', 'e', 'c', 't', 'o', 'r', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* control */  'c', 'o', 'n', 't', 'r', 'o', 'l',
            /* cs */  'c', 's',
            /* currencysymbol */  'c', 'u', 'r', 'r', 'e', 'n', 'c', 'y', 's', 'y', 'm', 'b', 'o', 'l',
            /* dashpunctuation */  'd', 'a', 's', 'h', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* decimaldigitnumber */  'd', 'e', 'c', 'i', 'm', 'a', 'l', 'd', 'i', 'g', 'i', 't', 'n', 'u', 'm', 'b', 'e', 'r',
            /* enclosingmark */  'e', 'n', 'c', 'l', 'o', 's', 'i', 'n', 'g', 'm', 'a', 'r', 'k',
            /* finalpunctuation */  'f', 'i', 'n', 'a', 'l', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* format */  'f', 'o', 'r', 'm', 'a', 't',
            /* initialpunctuation */  'i', 'n', 'i', 't', 'i', 'a', 'l', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* l* */  'l', '*',
            /* letter */  'l', 'e', 't', 't', 'e', 'r',
            /* letternumber */  'l', 'e', 't', 't', 'e', 'r', 'n', 'u', 'm', 'b', 'e', 'r',
            /* lineseparator */  'l', 'i', 'n', 'e', 's', 'e', 'p', 'a', 'r', 'a', 't', 'o', 'r',
            /* ll */  'l', 'l',
            /* lm */  'l', 'm',
            /* lo */  'l', 'o',
            /* lowercaseletter */  'l', 'o', 'w', 'e', 'r', 'c', 'a', 's', 'e', 'l', 'e', 't', 't', 'e', 'r',
            /* lt */  'l', 't',
            /* lu */  'l', 'u',
            /* m* */  'm', '*',
            /* mark */  'm', 'a', 'r', 'k',
            /* mathsymbol */  'm', 'a', 't', 'h', 's', 'y', 'm', 'b', 'o', 'l',
            /* mc */  'm', 'c',
            /* me */  'm', 'e',
            /* mn */  'm', 'n',
            /* modifierletter */  'm', 'o', 'd', 'i', 'f', 'i', 'e', 'r', 'l', 'e', 't', 't', 'e', 'r',
            /* modifiersymbol */  'm', 'o', 'd', 'i', 'f', 'i', 'e', 'r', 's', 'y', 'm', 'b', 'o', 'l',
            /* n* */  'n', '*',
            /* nd */  'n', 'd',
            /* nl */  'n', 'l',
            /* no */  'n', 'o',
            /* nonspacingmark */  'n', 'o', 'n', 's', 'p', 'a', 'c', 'i', 'n', 'g', 'm', 'a', 'r', 'k',
            /* notassigned */  'n', 'o', 't', 'a', 's', 's', 'i', 'g', 'n', 'e', 'd',
            /* number */  'n', 'u', 'm', 'b', 'e', 'r',
            /* openpunctuation */  'o', 'p', 'e', 'n', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* other */  'o', 't', 'h', 'e', 'r',
            /* otherletter */  'o', 't', 'h', 'e', 'r', 'l', 'e', 't', 't', 'e', 'r',
            /* othernumber */  'o', 't', 'h', 'e', 'r', 'n', 'u', 'm', 'b', 'e', 'r',
            /* otherpunctuation */  'o', 't', 'h', 'e', 'r', 'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* othersymbol */  'o', 't', 'h', 'e', 'r', 's', 'y', 'm', 'b', 'o', 'l',
            /* p* */  'p', '*',
            /* paragraphseparator */  'p', 'a', 'r', 'a', 'g', 'r', 'a', 'p', 'h', 's', 'e', 'p', 'a', 'r', 'a', 't', 'o', 'r',
            /* pc */  'p', 'c',
            /* pd */  'p', 'd',
            /* pe */  'p', 'e',
            /* pf */  'p', 'f',
            /* pi */  'p', 'i',
            /* po */  'p', 'o',
            /* privateuse */  'p', 'r', 'i', 'v', 'a', 't', 'e', 'u', 's', 'e',
            /* ps */  'p', 's',
            /* punctuation */  'p', 'u', 'n', 'c', 't', 'u', 'a', 't', 'i', 'o', 'n',
            /* s* */  's', '*',
            /* sc */  's', 'c',
            /* separator */  's', 'e', 'p', 'a', 'r', 'a', 't', 'o', 'r',
            /* sk */  's', 'k',
            /* sm */  's', 'm',
            /* so */  's', 'o',
            /* spaceseparator */  's', 'p', 'a', 'c', 'e', 's', 'e', 'p', 'a', 'r', 'a', 't', 'o', 'r',
            /* spacingcombiningmark */  's', 'p', 'a', 'c', 'i', 'n', 'g', 'c', 'o', 'm', 'b', 'i', 'n', 'i', 'n', 'g', 'm', 'a', 'r', 'k',
            /* surrogate */  's', 'u', 'r', 'r', 'o', 'g', 'a', 't', 'e',
            /* symbol */  's', 'y', 'm', 'b', 'o', 'l',
            /* titlecase */  't', 'i', 't', 'l', 'e', 'c', 'a', 's', 'e',
            /* titlecaseletter */  't', 'i', 't', 'l', 'e', 'c', 'a', 's', 'e', 'l', 'e', 't', 't', 'e', 'r',
            /* uppercaseletter */  'u', 'p', 'p', 'e', 'r', 'c', 'a', 's', 'e', 'l', 'e', 't', 't', 'e', 'r',
            /* z* */  'z', '*',
            /* zl */  'z', 'l',
            /* zp */  'z', 'p',
            /* zs */  'z', 's',
         };

         static const BOOST_REGEX_DETAIL_NS::character_pointer_range< ::UChar32> range_data[] = {
            { prop_name_table + 0, prop_name_table + 3, }, // any
            { prop_name_table + 3, prop_name_table + 8, }, // ascii
            { prop_name_table + 8, prop_name_table + 16, }, // assigned
            { prop_name_table + 16, prop_name_table + 18, }, // c*
            { prop_name_table + 18, prop_name_table + 20, }, // cc
            { prop_name_table + 20, prop_name_table + 22, }, // cf
            { prop_name_table + 22, prop_name_table + 38, }, // closepunctuation
            { prop_name_table + 38, prop_name_table + 40, }, // cn
            { prop_name_table + 40, prop_name_table + 42, }, // co
            { prop_name_table + 42, prop_name_table + 62, }, // connectorpunctuation
            { prop_name_table + 62, prop_name_table + 69, }, // control
            { prop_name_table + 69, prop_name_table + 71, }, // cs
            { prop_name_table + 71, prop_name_table + 85, }, // currencysymbol
            { prop_name_table + 85, prop_name_table + 100, }, // dashpunctuation
            { prop_name_table + 100, prop_name_table + 118, }, // decimaldigitnumber
            { prop_name_table + 118, prop_name_table + 131, }, // enclosingmark
            { prop_name_table + 131, prop_name_table + 147, }, // finalpunctuation
            { prop_name_table + 147, prop_name_table + 153, }, // format
            { prop_name_table + 153, prop_name_table + 171, }, // initialpunctuation
            { prop_name_table + 171, prop_name_table + 173, }, // l*
            { prop_name_table + 173, prop_name_table + 179, }, // letter
            { prop_name_table + 179, prop_name_table + 191, }, // letternumber
            { prop_name_table + 191, prop_name_table + 204, }, // lineseparator
            { prop_name_table + 204, prop_name_table + 206, }, // ll
            { prop_name_table + 206, prop_name_table + 208, }, // lm
            { prop_name_table + 208, prop_name_table + 210, }, // lo
            { prop_name_table + 210, prop_name_table + 225, }, // lowercaseletter
            { prop_name_table + 225, prop_name_table + 227, }, // lt
            { prop_name_table + 227, prop_name_table + 229, }, // lu
            { prop_name_table + 229, prop_name_table + 231, }, // m*
            { prop_name_table + 231, prop_name_table + 235, }, // mark
            { prop_name_table + 235, prop_name_table + 245, }, // mathsymbol
            { prop_name_table + 245, prop_name_table + 247, }, // mc
            { prop_name_table + 247, prop_name_table + 249, }, // me
            { prop_name_table + 249, prop_name_table + 251, }, // mn
            { prop_name_table + 251, prop_name_table + 265, }, // modifierletter
            { prop_name_table + 265, prop_name_table + 279, }, // modifiersymbol
            { prop_name_table + 279, prop_name_table + 281, }, // n*
            { prop_name_table + 281, prop_name_table + 283, }, // nd
            { prop_name_table + 283, prop_name_table + 285, }, // nl
            { prop_name_table + 285, prop_name_table + 287, }, // no
            { prop_name_table + 287, prop_name_table + 301, }, // nonspacingmark
            { prop_name_table + 301, prop_name_table + 312, }, // notassigned
            { prop_name_table + 312, prop_name_table + 318, }, // number
            { prop_name_table + 318, prop_name_table + 333, }, // openpunctuation
            { prop_name_table + 333, prop_name_table + 338, }, // other
            { prop_name_table + 338, prop_name_table + 349, }, // otherletter
            { prop_name_table + 349, prop_name_table + 360, }, // othernumber
            { prop_name_table + 360, prop_name_table + 376, }, // otherpunctuation
            { prop_name_table + 376, prop_name_table + 387, }, // othersymbol
            { prop_name_table + 387, prop_name_table + 389, }, // p*
            { prop_name_table + 389, prop_name_table + 407, }, // paragraphseparator
            { prop_name_table + 407, prop_name_table + 409, }, // pc
            { prop_name_table + 409, prop_name_table + 411, }, // pd
            { prop_name_table + 411, prop_name_table + 413, }, // pe
            { prop_name_table + 413, prop_name_table + 415, }, // pf
            { prop_name_table + 415, prop_name_table + 417, }, // pi
            { prop_name_table + 417, prop_name_table + 419, }, // po
            { prop_name_table + 419, prop_name_table + 429, }, // privateuse
            { prop_name_table + 429, prop_name_table + 431, }, // ps
            { prop_name_table + 431, prop_name_table + 442, }, // punctuation
            { prop_name_table + 442, prop_name_table + 444, }, // s*
            { prop_name_table + 444, prop_name_table + 446, }, // sc
            { prop_name_table + 446, prop_name_table + 455, }, // separator
            { prop_name_table + 455, prop_name_table + 457, }, // sk
            { prop_name_table + 457, prop_name_table + 459, }, // sm
            { prop_name_table + 459, prop_name_table + 461, }, // so
            { prop_name_table + 461, prop_name_table + 475, }, // spaceseparator
            { prop_name_table + 475, prop_name_table + 495, }, // spacingcombiningmark
            { prop_name_table + 495, prop_name_table + 504, }, // surrogate
            { prop_name_table + 504, prop_name_table + 510, }, // symbol
            { prop_name_table + 510, prop_name_table + 519, }, // titlecase
            { prop_name_table + 519, prop_name_table + 534, }, // titlecaseletter
            { prop_name_table + 534, prop_name_table + 549, }, // uppercaseletter
            { prop_name_table + 549, prop_name_table + 551, }, // z*
            { prop_name_table + 551, prop_name_table + 553, }, // zl
            { prop_name_table + 553, prop_name_table + 555, }, // zp
            { prop_name_table + 555, prop_name_table + 557, }, // zs
         };

         static const icu_regex_traits::char_class_type icu_class_map[] = {
            mask_any, // any
            mask_ascii, // ascii
            (0x3FFFFFFFu) & ~(U_GC_CN_MASK), // assigned
            U_GC_C_MASK, // c*
            U_GC_CC_MASK, // cc
            U_GC_CF_MASK, // cf
            U_GC_PE_MASK, // closepunctuation
            U_GC_CN_MASK, // cn
            U_GC_CO_MASK, // co
            U_GC_PC_MASK, // connectorpunctuation
            U_GC_CC_MASK, // control
            U_GC_CS_MASK, // cs
            U_GC_SC_MASK, // currencysymbol
            U_GC_PD_MASK, // dashpunctuation
            U_GC_ND_MASK, // decimaldigitnumber
            U_GC_ME_MASK, // enclosingmark
            U_GC_PF_MASK, // finalpunctuation
            U_GC_CF_MASK, // format
            U_GC_PI_MASK, // initialpunctuation
            U_GC_L_MASK, // l*
            U_GC_L_MASK, // letter
            U_GC_NL_MASK, // letternumber
            U_GC_ZL_MASK, // lineseparator
            U_GC_LL_MASK, // ll
            U_GC_LM_MASK, // lm
            U_GC_LO_MASK, // lo
            U_GC_LL_MASK, // lowercaseletter
            U_GC_LT_MASK, // lt
            U_GC_LU_MASK, // lu
            U_GC_M_MASK, // m*
            U_GC_M_MASK, // mark
            U_GC_SM_MASK, // mathsymbol
            U_GC_MC_MASK, // mc
            U_GC_ME_MASK, // me
            U_GC_MN_MASK, // mn
            U_GC_LM_MASK, // modifierletter
            U_GC_SK_MASK, // modifiersymbol
            U_GC_N_MASK, // n*
            U_GC_ND_MASK, // nd
            U_GC_NL_MASK, // nl
            U_GC_NO_MASK, // no
            U_GC_MN_MASK, // nonspacingmark
            U_GC_CN_MASK, // notassigned
            U_GC_N_MASK, // number
            U_GC_PS_MASK, // openpunctuation
            U_GC_C_MASK, // other
            U_GC_LO_MASK, // otherletter
            U_GC_NO_MASK, // othernumber
            U_GC_PO_MASK, // otherpunctuation
            U_GC_SO_MASK, // othersymbol
            U_GC_P_MASK, // p*
            U_GC_ZP_MASK, // paragraphseparator
            U_GC_PC_MASK, // pc
            U_GC_PD_MASK, // pd
            U_GC_PE_MASK, // pe
            U_GC_PF_MASK, // pf
            U_GC_PI_MASK, // pi
            U_GC_PO_MASK, // po
            U_GC_CO_MASK, // privateuse
            U_GC_PS_MASK, // ps
            U_GC_P_MASK, // punctuation
            U_GC_S_MASK, // s*
            U_GC_SC_MASK, // sc
            U_GC_Z_MASK, // separator
            U_GC_SK_MASK, // sk
            U_GC_SM_MASK, // sm
            U_GC_SO_MASK, // so
            U_GC_ZS_MASK, // spaceseparator
            U_GC_MC_MASK, // spacingcombiningmark
            U_GC_CS_MASK, // surrogate
            U_GC_S_MASK, // symbol
            U_GC_LT_MASK, // titlecase
            U_GC_LT_MASK, // titlecaseletter
            U_GC_LU_MASK, // uppercaseletter
            U_GC_Z_MASK, // z*
            U_GC_ZL_MASK, // zl
            U_GC_ZP_MASK, // zp
            U_GC_ZS_MASK, // zs
         };


         const BOOST_REGEX_DETAIL_NS::character_pointer_range< ::UChar32>* ranges_begin = range_data;
         const BOOST_REGEX_DETAIL_NS::character_pointer_range< ::UChar32>* ranges_end = range_data + (sizeof(range_data) / sizeof(range_data[0]));

         BOOST_REGEX_DETAIL_NS::character_pointer_range< ::UChar32> t = { p1, p2, };
         const BOOST_REGEX_DETAIL_NS::character_pointer_range< ::UChar32>* p = std::lower_bound(ranges_begin, ranges_end, t);
         if ((p != ranges_end) && (t == *p))
            return icu_class_map[p - ranges_begin];
         return 0;
      }

      boost::shared_ptr< ::boost::BOOST_REGEX_DETAIL_NS::icu_regex_traits_implementation> m_pimpl;
   };

} // namespace boost

namespace boost {

   // types:
   typedef basic_regex< ::UChar32, icu_regex_traits> u32regex;
   typedef match_results<const ::UChar32*> u32match;
   typedef match_results<const ::UChar*> u16match;

   //
   // Construction of 32-bit regex types from UTF-8 and UTF-16 primitives:
   //
   namespace BOOST_REGEX_DETAIL_NS {

#if !defined(BOOST_NO_MEMBER_TEMPLATES) && !defined(__IBMCPP__)
      template <class InputIterator>
      inline u32regex do_make_u32regex(InputIterator i,
         InputIterator j,
         boost::regex_constants::syntax_option_type opt,
         const boost::mpl::int_<1>*)
      {
         typedef boost::u8_to_u32_iterator<InputIterator, UChar32> conv_type;
         return u32regex(conv_type(i, i, j), conv_type(j, i, j), opt);
      }

      template <class InputIterator>
      inline u32regex do_make_u32regex(InputIterator i,
         InputIterator j,
         boost::regex_constants::syntax_option_type opt,
         const boost::mpl::int_<2>*)
      {
         typedef boost::u16_to_u32_iterator<InputIterator, UChar32> conv_type;
         return u32regex(conv_type(i, i, j), conv_type(j, i, j), opt);
      }

      template <class InputIterator>
      inline u32regex do_make_u32regex(InputIterator i,
         InputIterator j,
         boost::regex_constants::syntax_option_type opt,
         const boost::mpl::int_<4>*)
      {
         return u32regex(i, j, opt);
      }
#else
      template <class InputIterator>
      inline u32regex do_make_u32regex(InputIterator i,
         InputIterator j,
         boost::regex_constants::syntax_option_type opt,
         const boost::mpl::int_<1>*)
      {
         typedef boost::u8_to_u32_iterator<InputIterator, UChar32> conv_type;
         typedef std::vector<UChar32> vector_type;
         vector_type v;
         conv_type a(i, i, j), b(j, i, j);
         while (a != b)
         {
            v.push_back(*a);
            ++a;
         }
         if (v.size())
            return u32regex(&*v.begin(), v.size(), opt);
         return u32regex(static_cast<UChar32 const*>(0), static_cast<u32regex::size_type>(0), opt);
      }

      template <class InputIterator>
      inline u32regex do_make_u32regex(InputIterator i,
         InputIterator j,
         boost::regex_constants::syntax_option_type opt,
         const boost::mpl::int_<2>*)
      {
         typedef boost::u16_to_u32_iterator<InputIterator, UChar32> conv_type;
         typedef std::vector<UChar32> vector_type;
         vector_type v;
         conv_type a(i, i, j), b(j, i, j);
         while (a != b)
         {
            v.push_back(*a);
            ++a;
         }
         if (v.size())
            return u32regex(&*v.begin(), v.size(), opt);
         return u32regex(static_cast<UChar32 const*>(0), static_cast<u32regex::size_type>(0), opt);
      }

      template <class InputIterator>
      inline u32regex do_make_u32regex(InputIterator i,
         InputIterator j,
         boost::regex_constants::syntax_option_type opt,
         const boost::mpl::int_<4>*)
      {
         typedef std::vector<UChar32> vector_type;
         vector_type v;
         while (i != j)
         {
            v.push_back((UChar32)(*i));
            ++i;
         }
         if (v.size())
            return u32regex(&*v.begin(), v.size(), opt);
         return u32regex(static_cast<UChar32 const*>(0), static_cast<u32regex::size_type>(0), opt);
      }
#endif
   }

   // BOOST_REGEX_UCHAR_IS_WCHAR_T
   //
   // Source inspection of unicode/umachine.h in ICU version 59 indicates that:
   //
   // On version 59, UChar is always char16_t in C++ mode (and uint16_t in C mode)
   //
   // On earlier versions, the logic is
   //
   // #if U_SIZEOF_WCHAR_T==2
   //   typedef wchar_t OldUChar;
   // #elif defined(__CHAR16_TYPE__)
   //   typedef __CHAR16_TYPE__ OldUChar;
   // #else
   //   typedef uint16_t OldUChar;
   // #endif
   //
   // That is, UChar is wchar_t only on versions below 59, when U_SIZEOF_WCHAR_T==2
   //
   // Hence,

#define BOOST_REGEX_UCHAR_IS_WCHAR_T (U_ICU_VERSION_MAJOR_NUM < 59 && U_SIZEOF_WCHAR_T == 2)

#if BOOST_REGEX_UCHAR_IS_WCHAR_T
   BOOST_STATIC_ASSERT((boost::is_same<UChar, wchar_t>::value));
#else
   BOOST_STATIC_ASSERT(!(boost::is_same<UChar, wchar_t>::value));
#endif

   //
   // Construction from an iterator pair:
   //
   template <class InputIterator>
   inline u32regex make_u32regex(InputIterator i,
      InputIterator j,
      boost::regex_constants::syntax_option_type opt)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(i, j, opt, static_cast<boost::mpl::int_<sizeof(*i)> const*>(0));
   }
   //
   // construction from UTF-8 nul-terminated strings:
   //
   inline u32regex make_u32regex(const char* p, boost::regex_constants::syntax_option_type opt = boost::regex_constants::perl)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(p, p + std::strlen(p), opt, static_cast<boost::mpl::int_<1> const*>(0));
   }
   inline u32regex make_u32regex(const unsigned char* p, boost::regex_constants::syntax_option_type opt = boost::regex_constants::perl)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(p, p + std::strlen(reinterpret_cast<const char*>(p)), opt, static_cast<boost::mpl::int_<1> const*>(0));
   }
   //
   // construction from UTF-16 nul-terminated strings:
   //
#ifndef BOOST_NO_WREGEX
   inline u32regex make_u32regex(const wchar_t* p, boost::regex_constants::syntax_option_type opt = boost::regex_constants::perl)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(p, p + std::wcslen(p), opt, static_cast<boost::mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
#if !BOOST_REGEX_UCHAR_IS_WCHAR_T
   inline u32regex make_u32regex(const UChar* p, boost::regex_constants::syntax_option_type opt = boost::regex_constants::perl)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(p, p + u_strlen(p), opt, static_cast<boost::mpl::int_<2> const*>(0));
   }
#endif
   //
   // construction from basic_string class-template:
   //
   template<class C, class T, class A>
   inline u32regex make_u32regex(const std::basic_string<C, T, A>& s, boost::regex_constants::syntax_option_type opt = boost::regex_constants::perl)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(s.begin(), s.end(), opt, static_cast<boost::mpl::int_<sizeof(C)> const*>(0));
   }
   //
   // Construction from ICU string type:
   //
   inline u32regex make_u32regex(const U_NAMESPACE_QUALIFIER UnicodeString& s, boost::regex_constants::syntax_option_type opt = boost::regex_constants::perl)
   {
      return BOOST_REGEX_DETAIL_NS::do_make_u32regex(s.getBuffer(), s.getBuffer() + s.length(), opt, static_cast<boost::mpl::int_<2> const*>(0));
   }

   //
   // regex_match overloads that widen the character type as appropriate:
   //
   namespace BOOST_REGEX_DETAIL_NS {
      template<class MR1, class MR2, class NSubs>
      void copy_results(MR1& out, MR2 const& in, NSubs named_subs)
      {
         // copy results from an adapted MR2 match_results:
         out.set_size(in.size(), in.prefix().first.base(), in.suffix().second.base());
         out.set_base(in.base().base());
         out.set_named_subs(named_subs);
         for (int i = 0; i < (int)in.size(); ++i)
         {
            if (in[i].matched || !i)
            {
               out.set_first(in[i].first.base(), i);
               out.set_second(in[i].second.base(), i, in[i].matched);
            }
         }
#ifdef BOOST_REGEX_MATCH_EXTRA
         // Copy full capture info as well:
         for (int i = 0; i < (int)in.size(); ++i)
         {
            if (in[i].captures().size())
            {
               out[i].get_captures().assign(in[i].captures().size(), typename MR1::value_type());
               for (int j = 0; j < (int)out[i].captures().size(); ++j)
               {
                  out[i].get_captures()[j].first = in[i].captures()[j].first.base();
                  out[i].get_captures()[j].second = in[i].captures()[j].second.base();
                  out[i].get_captures()[j].matched = in[i].captures()[j].matched;
               }
            }
         }
#endif
      }

      template <class BidiIterator, class Allocator>
      inline bool do_regex_match(BidiIterator first, BidiIterator last,
         match_results<BidiIterator, Allocator>& m,
         const u32regex& e,
         match_flag_type flags,
         boost::mpl::int_<4> const*)
      {
         return ::boost::regex_match(first, last, m, e, flags);
      }
      template <class BidiIterator, class Allocator>
      bool do_regex_match(BidiIterator first, BidiIterator last,
         match_results<BidiIterator, Allocator>& m,
         const u32regex& e,
         match_flag_type flags,
         boost::mpl::int_<2> const*)
      {
         typedef u16_to_u32_iterator<BidiIterator, UChar32> conv_type;
         typedef match_results<conv_type>                   match_type;
         //typedef typename match_type::allocator_type        alloc_type;
         match_type what;
         bool result = ::boost::regex_match(conv_type(first, first, last), conv_type(last, first, last), what, e, flags);
         // copy results across to m:
         if (result) copy_results(m, what, e.get_named_subs());
         return result;
      }
      template <class BidiIterator, class Allocator>
      bool do_regex_match(BidiIterator first, BidiIterator last,
         match_results<BidiIterator, Allocator>& m,
         const u32regex& e,
         match_flag_type flags,
         boost::mpl::int_<1> const*)
      {
         typedef u8_to_u32_iterator<BidiIterator, UChar32>  conv_type;
         typedef match_results<conv_type>                   match_type;
         //typedef typename match_type::allocator_type        alloc_type;
         match_type what;
         bool result = ::boost::regex_match(conv_type(first, first, last), conv_type(last, first, last), what, e, flags);
         // copy results across to m:
         if (result) copy_results(m, what, e.get_named_subs());
         return result;
      }
   } // namespace BOOST_REGEX_DETAIL_NS

   template <class BidiIterator, class Allocator>
   inline bool u32regex_match(BidiIterator first, BidiIterator last,
      match_results<BidiIterator, Allocator>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(first, last, m, e, flags, static_cast<mpl::int_<sizeof(*first)> const*>(0));
   }
   inline bool u32regex_match(const UChar* p,
      match_results<const UChar*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + u_strlen(p), m, e, flags, static_cast<mpl::int_<2> const*>(0));
   }
#if !BOOST_REGEX_UCHAR_IS_WCHAR_T && !defined(BOOST_NO_WREGEX)
   inline bool u32regex_match(const wchar_t* p,
      match_results<const wchar_t*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + std::wcslen(p), m, e, flags, static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_match(const char* p,
      match_results<const char*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + std::strlen(p), m, e, flags, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_match(const unsigned char* p,
      match_results<const unsigned char*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + std::strlen((const char*)p), m, e, flags, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_match(const std::string& s,
      match_results<std::string::const_iterator>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(s.begin(), s.end(), m, e, flags, static_cast<mpl::int_<1> const*>(0));
   }
#ifndef BOOST_NO_STD_WSTRING
   inline bool u32regex_match(const std::wstring& s,
      match_results<std::wstring::const_iterator>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(s.begin(), s.end(), m, e, flags, static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_match(const U_NAMESPACE_QUALIFIER UnicodeString& s,
      match_results<const UChar*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_match(s.getBuffer(), s.getBuffer() + s.length(), m, e, flags, static_cast<mpl::int_<2> const*>(0));
   }
   //
   // regex_match overloads that do not return what matched:
   //
   template <class BidiIterator>
   inline bool u32regex_match(BidiIterator first, BidiIterator last,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<BidiIterator> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(first, last, m, e, flags, static_cast<mpl::int_<sizeof(*first)> const*>(0));
   }
   inline bool u32regex_match(const UChar* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const UChar*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + u_strlen(p), m, e, flags, static_cast<mpl::int_<2> const*>(0));
   }
#if !BOOST_REGEX_UCHAR_IS_WCHAR_T && !defined(BOOST_NO_WREGEX)
   inline bool u32regex_match(const wchar_t* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const wchar_t*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + std::wcslen(p), m, e, flags, static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_match(const char* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const char*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + std::strlen(p), m, e, flags, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_match(const unsigned char* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const unsigned char*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(p, p + std::strlen((const char*)p), m, e, flags, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_match(const std::string& s,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<std::string::const_iterator> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(s.begin(), s.end(), m, e, flags, static_cast<mpl::int_<1> const*>(0));
   }
#ifndef BOOST_NO_STD_WSTRING
   inline bool u32regex_match(const std::wstring& s,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<std::wstring::const_iterator> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(s.begin(), s.end(), m, e, flags, static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_match(const U_NAMESPACE_QUALIFIER UnicodeString& s,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const UChar*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_match(s.getBuffer(), s.getBuffer() + s.length(), m, e, flags, static_cast<mpl::int_<2> const*>(0));
   }

   //
   // regex_search overloads that widen the character type as appropriate:
   //
   namespace BOOST_REGEX_DETAIL_NS {
      template <class BidiIterator, class Allocator>
      inline bool do_regex_search(BidiIterator first, BidiIterator last,
         match_results<BidiIterator, Allocator>& m,
         const u32regex& e,
         match_flag_type flags,
         BidiIterator base,
         boost::mpl::int_<4> const*)
      {
         return ::boost::regex_search(first, last, m, e, flags, base);
      }
      template <class BidiIterator, class Allocator>
      bool do_regex_search(BidiIterator first, BidiIterator last,
         match_results<BidiIterator, Allocator>& m,
         const u32regex& e,
         match_flag_type flags,
         BidiIterator base,
         boost::mpl::int_<2> const*)
      {
         typedef u16_to_u32_iterator<BidiIterator, UChar32> conv_type;
         typedef match_results<conv_type>                   match_type;
         //typedef typename match_type::allocator_type        alloc_type;
         match_type what;
         bool result = ::boost::regex_search(conv_type(first, first, last), conv_type(last, first, last), what, e, flags, conv_type(base));
         // copy results across to m:
         if (result) copy_results(m, what, e.get_named_subs());
         return result;
      }
      template <class BidiIterator, class Allocator>
      bool do_regex_search(BidiIterator first, BidiIterator last,
         match_results<BidiIterator, Allocator>& m,
         const u32regex& e,
         match_flag_type flags,
         BidiIterator base,
         boost::mpl::int_<1> const*)
      {
         typedef u8_to_u32_iterator<BidiIterator, UChar32>  conv_type;
         typedef match_results<conv_type>                   match_type;
         //typedef typename match_type::allocator_type        alloc_type;
         match_type what;
         bool result = ::boost::regex_search(conv_type(first, first, last), conv_type(last, first, last), what, e, flags, conv_type(base));
         // copy results across to m:
         if (result) copy_results(m, what, e.get_named_subs());
         return result;
      }
   }

   template <class BidiIterator, class Allocator>
   inline bool u32regex_search(BidiIterator first, BidiIterator last,
      match_results<BidiIterator, Allocator>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(first, last, m, e, flags, first, static_cast<mpl::int_<sizeof(*first)> const*>(0));
   }
   template <class BidiIterator, class Allocator>
   inline bool u32regex_search(BidiIterator first, BidiIterator last,
      match_results<BidiIterator, Allocator>& m,
      const u32regex& e,
      match_flag_type flags,
      BidiIterator base)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(first, last, m, e, flags, base, static_cast<mpl::int_<sizeof(*first)> const*>(0));
   }
   inline bool u32regex_search(const UChar* p,
      match_results<const UChar*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + u_strlen(p), m, e, flags, p, static_cast<mpl::int_<2> const*>(0));
   }
#if !BOOST_REGEX_UCHAR_IS_WCHAR_T && !defined(BOOST_NO_WREGEX)
   inline bool u32regex_search(const wchar_t* p,
      match_results<const wchar_t*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + std::wcslen(p), m, e, flags, p, static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_search(const char* p,
      match_results<const char*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + std::strlen(p), m, e, flags, p, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_search(const unsigned char* p,
      match_results<const unsigned char*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + std::strlen((const char*)p), m, e, flags, p, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_search(const std::string& s,
      match_results<std::string::const_iterator>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(s.begin(), s.end(), m, e, flags, s.begin(), static_cast<mpl::int_<1> const*>(0));
   }
#ifndef BOOST_NO_STD_WSTRING
   inline bool u32regex_search(const std::wstring& s,
      match_results<std::wstring::const_iterator>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(s.begin(), s.end(), m, e, flags, s.begin(), static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_search(const U_NAMESPACE_QUALIFIER UnicodeString& s,
      match_results<const UChar*>& m,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::do_regex_search(s.getBuffer(), s.getBuffer() + s.length(), m, e, flags, s.getBuffer(), static_cast<mpl::int_<2> const*>(0));
   }
   template <class BidiIterator>
   inline bool u32regex_search(BidiIterator first, BidiIterator last,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<BidiIterator> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(first, last, m, e, flags, first, static_cast<mpl::int_<sizeof(*first)> const*>(0));
   }
   inline bool u32regex_search(const UChar* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const UChar*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + u_strlen(p), m, e, flags, p, static_cast<mpl::int_<2> const*>(0));
   }
#if !BOOST_REGEX_UCHAR_IS_WCHAR_T && !defined(BOOST_NO_WREGEX)
   inline bool u32regex_search(const wchar_t* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const wchar_t*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + std::wcslen(p), m, e, flags, p, static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_search(const char* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const char*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + std::strlen(p), m, e, flags, p, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_search(const unsigned char* p,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const unsigned char*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(p, p + std::strlen((const char*)p), m, e, flags, p, static_cast<mpl::int_<1> const*>(0));
   }
   inline bool u32regex_search(const std::string& s,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<std::string::const_iterator> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(s.begin(), s.end(), m, e, flags, s.begin(), static_cast<mpl::int_<1> const*>(0));
   }
#ifndef BOOST_NO_STD_WSTRING
   inline bool u32regex_search(const std::wstring& s,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<std::wstring::const_iterator> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(s.begin(), s.end(), m, e, flags, s.begin(), static_cast<mpl::int_<sizeof(wchar_t)> const*>(0));
   }
#endif
   inline bool u32regex_search(const U_NAMESPACE_QUALIFIER UnicodeString& s,
      const u32regex& e,
      match_flag_type flags = match_default)
   {
      match_results<const UChar*> m;
      return BOOST_REGEX_DETAIL_NS::do_regex_search(s.getBuffer(), s.getBuffer() + s.length(), m, e, flags, s.getBuffer(), static_cast<mpl::int_<2> const*>(0));
   }

   //
   // overloads for regex_replace with utf-8 and utf-16 data types:
   //
   namespace BOOST_REGEX_DETAIL_NS {
      template <class I>
      inline std::pair< boost::u8_to_u32_iterator<I>, boost::u8_to_u32_iterator<I> >
         make_utf32_seq(I i, I j, mpl::int_<1> const*)
      {
         return std::pair< boost::u8_to_u32_iterator<I>, boost::u8_to_u32_iterator<I> >(boost::u8_to_u32_iterator<I>(i, i, j), boost::u8_to_u32_iterator<I>(j, i, j));
      }
      template <class I>
      inline std::pair< boost::u16_to_u32_iterator<I>, boost::u16_to_u32_iterator<I> >
         make_utf32_seq(I i, I j, mpl::int_<2> const*)
      {
         return std::pair< boost::u16_to_u32_iterator<I>, boost::u16_to_u32_iterator<I> >(boost::u16_to_u32_iterator<I>(i, i, j), boost::u16_to_u32_iterator<I>(j, i, j));
      }
      template <class I>
      inline std::pair< I, I >
         make_utf32_seq(I i, I j, mpl::int_<4> const*)
      {
         return std::pair< I, I >(i, j);
      }
      template <class charT>
      inline std::pair< boost::u8_to_u32_iterator<const charT*>, boost::u8_to_u32_iterator<const charT*> >
         make_utf32_seq(const charT* p, mpl::int_<1> const*)
      {
         std::size_t len = std::strlen((const char*)p);
         return std::pair< boost::u8_to_u32_iterator<const charT*>, boost::u8_to_u32_iterator<const charT*> >(boost::u8_to_u32_iterator<const charT*>(p, p, p + len), boost::u8_to_u32_iterator<const charT*>(p + len, p, p + len));
      }
      template <class charT>
      inline std::pair< boost::u16_to_u32_iterator<const charT*>, boost::u16_to_u32_iterator<const charT*> >
         make_utf32_seq(const charT* p, mpl::int_<2> const*)
      {
         std::size_t len = u_strlen((const UChar*)p);
         return std::pair< boost::u16_to_u32_iterator<const charT*>, boost::u16_to_u32_iterator<const charT*> >(boost::u16_to_u32_iterator<const charT*>(p, p, p + len), boost::u16_to_u32_iterator<const charT*>(p + len, p, p + len));
      }
      template <class charT>
      inline std::pair< const charT*, const charT* >
         make_utf32_seq(const charT* p, mpl::int_<4> const*)
      {
         return std::pair< const charT*, const charT* >(p, p + icu_regex_traits::length((UChar32 const*)p));
      }
      template <class OutputIterator>
      inline OutputIterator make_utf32_out(OutputIterator o, mpl::int_<4> const*)
      {
         return o;
      }
      template <class OutputIterator>
      inline utf16_output_iterator<OutputIterator> make_utf32_out(OutputIterator o, mpl::int_<2> const*)
      {
         return o;
      }
      template <class OutputIterator>
      inline utf8_output_iterator<OutputIterator> make_utf32_out(OutputIterator o, mpl::int_<1> const*)
      {
         return o;
      }

      template <class OutputIterator, class I1, class I2>
      OutputIterator do_regex_replace(OutputIterator out,
         std::pair<I1, I1> const& in,
         const u32regex& e,
         const std::pair<I2, I2>& fmt,
         match_flag_type flags
      )
      {
         // unfortunately we have to copy the format string in order to pass in onward:
         std::vector<UChar32> f;
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
         f.assign(fmt.first, fmt.second);
#else
         f.clear();
         I2 pos = fmt.first;
         while (pos != fmt.second)
            f.push_back(*pos++);
#endif

         regex_iterator<I1, UChar32, icu_regex_traits> i(in.first, in.second, e, flags);
         regex_iterator<I1, UChar32, icu_regex_traits> j;
         if (i == j)
         {
            if (!(flags & regex_constants::format_no_copy))
               out = BOOST_REGEX_DETAIL_NS::copy(in.first, in.second, out);
         }
         else
         {
            I1 last_m = in.first;
            while (i != j)
            {
               if (!(flags & regex_constants::format_no_copy))
                  out = BOOST_REGEX_DETAIL_NS::copy(i->prefix().first, i->prefix().second, out);
               if (!f.empty())
                  out = ::boost::BOOST_REGEX_DETAIL_NS::regex_format_imp(out, *i, &*f.begin(), &*f.begin() + f.size(), flags, e.get_traits());
               else
                  out = ::boost::BOOST_REGEX_DETAIL_NS::regex_format_imp(out, *i, static_cast<UChar32 const*>(0), static_cast<UChar32 const*>(0), flags, e.get_traits());
               last_m = (*i)[0].second;
               if (flags & regex_constants::format_first_only)
                  break;
               ++i;
            }
            if (!(flags & regex_constants::format_no_copy))
               out = BOOST_REGEX_DETAIL_NS::copy(last_m, in.second, out);
         }
         return out;
      }
      template <class BaseIterator>
      inline const BaseIterator& extract_output_base(const BaseIterator& b)
      {
         return b;
      }
      template <class BaseIterator>
      inline BaseIterator extract_output_base(const utf8_output_iterator<BaseIterator>& b)
      {
         return b.base();
      }
      template <class BaseIterator>
      inline BaseIterator extract_output_base(const utf16_output_iterator<BaseIterator>& b)
      {
         return b.base();
      }
   }  // BOOST_REGEX_DETAIL_NS

   template <class OutputIterator, class BidirectionalIterator, class charT>
   inline OutputIterator u32regex_replace(OutputIterator out,
      BidirectionalIterator first,
      BidirectionalIterator last,
      const u32regex& e,
      const charT* fmt,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::extract_output_base
      (
         BOOST_REGEX_DETAIL_NS::do_regex_replace(
            BOOST_REGEX_DETAIL_NS::make_utf32_out(out, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
            BOOST_REGEX_DETAIL_NS::make_utf32_seq(first, last, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
            e,
            BOOST_REGEX_DETAIL_NS::make_utf32_seq(fmt, static_cast<mpl::int_<sizeof(*fmt)> const*>(0)),
            flags)
      );
   }

   template <class OutputIterator, class Iterator, class charT>
   inline OutputIterator u32regex_replace(OutputIterator out,
      Iterator first,
      Iterator last,
      const u32regex& e,
      const std::basic_string<charT>& fmt,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::extract_output_base
      (
         BOOST_REGEX_DETAIL_NS::do_regex_replace(
            BOOST_REGEX_DETAIL_NS::make_utf32_out(out, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
            BOOST_REGEX_DETAIL_NS::make_utf32_seq(first, last, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
            e,
            BOOST_REGEX_DETAIL_NS::make_utf32_seq(fmt.begin(), fmt.end(), static_cast<mpl::int_<sizeof(charT)> const*>(0)),
            flags)
      );
   }

   template <class OutputIterator, class Iterator>
   inline OutputIterator u32regex_replace(OutputIterator out,
      Iterator first,
      Iterator last,
      const u32regex& e,
      const U_NAMESPACE_QUALIFIER UnicodeString& fmt,
      match_flag_type flags = match_default)
   {
      return BOOST_REGEX_DETAIL_NS::extract_output_base
      (
         BOOST_REGEX_DETAIL_NS::do_regex_replace(
            BOOST_REGEX_DETAIL_NS::make_utf32_out(out, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
            BOOST_REGEX_DETAIL_NS::make_utf32_seq(first, last, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
            e,
            BOOST_REGEX_DETAIL_NS::make_utf32_seq(fmt.getBuffer(), fmt.getBuffer() + fmt.length(), static_cast<mpl::int_<2> const*>(0)),
            flags)
      );
   }

   template <class charT>
   std::basic_string<charT> u32regex_replace(const std::basic_string<charT>& s,
      const u32regex& e,
      const charT* fmt,
      match_flag_type flags = match_default)
   {
      std::basic_string<charT> result;
      BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<charT> > i(result);
      u32regex_replace(i, s.begin(), s.end(), e, fmt, flags);
      return result;
   }

   template <class charT>
   std::basic_string<charT> u32regex_replace(const std::basic_string<charT>& s,
      const u32regex& e,
      const std::basic_string<charT>& fmt,
      match_flag_type flags = match_default)
   {
      std::basic_string<charT> result;
      BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<charT> > i(result);
      u32regex_replace(i, s.begin(), s.end(), e, fmt.c_str(), flags);
      return result;
   }

   namespace BOOST_REGEX_DETAIL_NS {

      class unicode_string_out_iterator
      {
         U_NAMESPACE_QUALIFIER UnicodeString* out;
      public:
         unicode_string_out_iterator(U_NAMESPACE_QUALIFIER UnicodeString& s) : out(&s) {}
         unicode_string_out_iterator& operator++() { return *this; }
         unicode_string_out_iterator& operator++(int) { return *this; }
         unicode_string_out_iterator& operator*() { return *this; }
         unicode_string_out_iterator& operator=(UChar v)
         {
            *out += v;
            return *this;
         }
         typedef std::ptrdiff_t difference_type;
         typedef UChar value_type;
         typedef value_type* pointer;
         typedef value_type& reference;
         typedef std::output_iterator_tag iterator_category;
      };

   }

   inline U_NAMESPACE_QUALIFIER UnicodeString u32regex_replace(const U_NAMESPACE_QUALIFIER UnicodeString& s,
      const u32regex& e,
      const UChar* fmt,
      match_flag_type flags = match_default)
   {
      U_NAMESPACE_QUALIFIER UnicodeString result;
      BOOST_REGEX_DETAIL_NS::unicode_string_out_iterator i(result);
      u32regex_replace(i, s.getBuffer(), s.getBuffer() + s.length(), e, fmt, flags);
      return result;
   }

   inline U_NAMESPACE_QUALIFIER UnicodeString u32regex_replace(const U_NAMESPACE_QUALIFIER UnicodeString& s,
      const u32regex& e,
      const U_NAMESPACE_QUALIFIER UnicodeString& fmt,
      match_flag_type flags = match_default)
   {
      U_NAMESPACE_QUALIFIER UnicodeString result;
      BOOST_REGEX_DETAIL_NS::unicode_string_out_iterator i(result);
      BOOST_REGEX_DETAIL_NS::do_regex_replace(
         BOOST_REGEX_DETAIL_NS::make_utf32_out(i, static_cast<mpl::int_<2> const*>(0)),
         BOOST_REGEX_DETAIL_NS::make_utf32_seq(s.getBuffer(), s.getBuffer() + s.length(), static_cast<mpl::int_<2> const*>(0)),
         e,
         BOOST_REGEX_DETAIL_NS::make_utf32_seq(fmt.getBuffer(), fmt.getBuffer() + fmt.length(), static_cast<mpl::int_<2> const*>(0)),
         flags);
      return result;
   }

} // namespace boost.

#ifdef BOOST_MSVC
#pragma warning (pop)
#endif

#include <boost/regex/v4/u32regex_iterator.hpp>
#include <boost/regex/v4/u32regex_token_iterator.hpp>

#endif

/* icu.hpp
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
*/