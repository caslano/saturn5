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
  *   FILE         regex_traits_defaults.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares API's for access to regex_traits default properties.
  */

#ifndef BOOST_REGEX_TRAITS_DEFAULTS_HPP_INCLUDED
#define BOOST_REGEX_TRAITS_DEFAULTS_HPP_INCLUDED

#include <boost/regex/config.hpp>

#include <boost/regex/v5/syntax_type.hpp>
#include <boost/regex/v5/error_type.hpp>
#include <boost/regex/v5/regex_workaround.hpp>
#include <type_traits>
#include <cstdint>
#include <cctype>
#include <locale>
#include <cwctype>
#include <limits>

namespace boost{ namespace BOOST_REGEX_DETAIL_NS{


//
// helpers to suppress warnings:
//
template <class charT>
inline bool is_extended(charT c)
{
   typedef typename std::make_unsigned<charT>::type unsigned_type; 
   return (sizeof(charT) > 1) && (static_cast<unsigned_type>(c) >= 256u); 
}
inline bool is_extended(char)
{ return false; }

inline const char*  get_default_syntax(regex_constants::syntax_type n)
{
   // if the user hasn't supplied a message catalog, then this supplies
   // default "messages" for us to load in the range 1-100.
   const char* messages[] = {
         "",
         "(",
         ")",
         "$",
         "^",
         ".",
         "*",
         "+",
         "?",
         "[",
         "]",
         "|",
         "\\",
         "#",
         "-",
         "{",
         "}",
         "0123456789",
         "b",
         "B",
         "<",
         ">",
         "",
         "",
         "A`",
         "z'",
         "\n",
         ",",
         "a",
         "f",
         "n",
         "r",
         "t",
         "v",
         "x",
         "c",
         ":",
         "=",
         "e",
         "",
         "",
         "",
         "",
         "",
         "",
         "",
         "",
         "E",
         "Q",
         "X",
         "C",
         "Z",
         "G",
         "!",
         "p",
         "P",
         "N",
         "gk",
         "K",
         "R",
   };

   return ((n >= (sizeof(messages) / sizeof(messages[1]))) ? "" : messages[n]);
}

inline const char*  get_default_error_string(regex_constants::error_type n)
{
   static const char* const s_default_error_messages[] = {
      "Success",                                                            /* REG_NOERROR 0 error_ok */
      "No match",                                                           /* REG_NOMATCH 1 error_no_match */
      "Invalid regular expression.",                                        /* REG_BADPAT 2 error_bad_pattern */
      "Invalid collation character.",                                       /* REG_ECOLLATE 3 error_collate */
      "Invalid character class name, collating name, or character range.",  /* REG_ECTYPE 4 error_ctype */
      "Invalid or unterminated escape sequence.",                           /* REG_EESCAPE 5 error_escape */
      "Invalid back reference: specified capturing group does not exist.",  /* REG_ESUBREG 6 error_backref */
      "Unmatched [ or [^ in character class declaration.",                  /* REG_EBRACK 7 error_brack */
      "Unmatched marking parenthesis ( or \\(.",                            /* REG_EPAREN 8 error_paren */
      "Unmatched quantified repeat operator { or \\{.",                     /* REG_EBRACE 9 error_brace */
      "Invalid content of repeat range.",                                   /* REG_BADBR 10 error_badbrace */
      "Invalid range end in character class",                               /* REG_ERANGE 11 error_range */
      "Out of memory.",                                                     /* REG_ESPACE 12 error_space NOT USED */
      "Invalid preceding regular expression prior to repetition operator.", /* REG_BADRPT 13 error_badrepeat */
      "Premature end of regular expression",                                /* REG_EEND 14 error_end NOT USED */
      "Regular expression is too large.",                                   /* REG_ESIZE 15 error_size NOT USED */
      "Unmatched ) or \\)",                                                 /* REG_ERPAREN 16 error_right_paren NOT USED */
      "Empty regular expression.",                                          /* REG_EMPTY 17 error_empty */
      "The complexity of matching the regular expression exceeded predefined bounds.  "
      "Try refactoring the regular expression to make each choice made by the state machine unambiguous.  "
      "This exception is thrown to prevent \"eternal\" matches that take an "
      "indefinite period time to locate.",                                  /* REG_ECOMPLEXITY 18 error_complexity */
      "Ran out of stack space trying to match the regular expression.",     /* REG_ESTACK 19 error_stack */
      "Invalid or unterminated Perl (?...) sequence.",                      /* REG_E_PERL 20 error_perl */
      "Unknown error.",                                                     /* REG_E_UNKNOWN 21 error_unknown */
   };

   return (n > ::boost::regex_constants::error_unknown) ? s_default_error_messages[::boost::regex_constants::error_unknown] : s_default_error_messages[n];
}

inline regex_constants::syntax_type  get_default_syntax_type(char c)
{
   //
   // char_syntax determines how the compiler treats a given character
   // in a regular expression.
   //
   static regex_constants::syntax_type char_syntax[] = {
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_newline,     /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /* */    // 32
      regex_constants::syntax_not,        /*!*/
      regex_constants::syntax_char,        /*"*/
      regex_constants::syntax_hash,        /*#*/
      regex_constants::syntax_dollar,        /*$*/
      regex_constants::syntax_char,        /*%*/
      regex_constants::syntax_char,        /*&*/
      regex_constants::escape_type_end_buffer,  /*'*/
      regex_constants::syntax_open_mark,        /*(*/
      regex_constants::syntax_close_mark,        /*)*/
      regex_constants::syntax_star,        /***/
      regex_constants::syntax_plus,        /*+*/
      regex_constants::syntax_comma,        /*,*/
      regex_constants::syntax_dash,        /*-*/
      regex_constants::syntax_dot,        /*.*/
      regex_constants::syntax_char,        /*/*/
      regex_constants::syntax_digit,        /*0*/
      regex_constants::syntax_digit,        /*1*/
      regex_constants::syntax_digit,        /*2*/
      regex_constants::syntax_digit,        /*3*/
      regex_constants::syntax_digit,        /*4*/
      regex_constants::syntax_digit,        /*5*/
      regex_constants::syntax_digit,        /*6*/
      regex_constants::syntax_digit,        /*7*/
      regex_constants::syntax_digit,        /*8*/
      regex_constants::syntax_digit,        /*9*/
      regex_constants::syntax_colon,        /*:*/
      regex_constants::syntax_char,        /*;*/
      regex_constants::escape_type_left_word, /*<*/
      regex_constants::syntax_equal,        /*=*/
      regex_constants::escape_type_right_word, /*>*/
      regex_constants::syntax_question,        /*?*/
      regex_constants::syntax_char,        /*@*/
      regex_constants::syntax_char,        /*A*/
      regex_constants::syntax_char,        /*B*/
      regex_constants::syntax_char,        /*C*/
      regex_constants::syntax_char,        /*D*/
      regex_constants::syntax_char,        /*E*/
      regex_constants::syntax_char,        /*F*/
      regex_constants::syntax_char,        /*G*/
      regex_constants::syntax_char,        /*H*/
      regex_constants::syntax_char,        /*I*/
      regex_constants::syntax_char,        /*J*/
      regex_constants::syntax_char,        /*K*/
      regex_constants::syntax_char,        /*L*/
      regex_constants::syntax_char,        /*M*/
      regex_constants::syntax_char,        /*N*/
      regex_constants::syntax_char,        /*O*/
      regex_constants::syntax_char,        /*P*/
      regex_constants::syntax_char,        /*Q*/
      regex_constants::syntax_char,        /*R*/
      regex_constants::syntax_char,        /*S*/
      regex_constants::syntax_char,        /*T*/
      regex_constants::syntax_char,        /*U*/
      regex_constants::syntax_char,        /*V*/
      regex_constants::syntax_char,        /*W*/
      regex_constants::syntax_char,        /*X*/
      regex_constants::syntax_char,        /*Y*/
      regex_constants::syntax_char,        /*Z*/
      regex_constants::syntax_open_set,        /*[*/
      regex_constants::syntax_escape,        /*\*/
      regex_constants::syntax_close_set,        /*]*/
      regex_constants::syntax_caret,        /*^*/
      regex_constants::syntax_char,        /*_*/
      regex_constants::syntax_char,        /*`*/
      regex_constants::syntax_char,        /*a*/
      regex_constants::syntax_char,        /*b*/
      regex_constants::syntax_char,        /*c*/
      regex_constants::syntax_char,        /*d*/
      regex_constants::syntax_char,        /*e*/
      regex_constants::syntax_char,        /*f*/
      regex_constants::syntax_char,        /*g*/
      regex_constants::syntax_char,        /*h*/
      regex_constants::syntax_char,        /*i*/
      regex_constants::syntax_char,        /*j*/
      regex_constants::syntax_char,        /*k*/
      regex_constants::syntax_char,        /*l*/
      regex_constants::syntax_char,        /*m*/
      regex_constants::syntax_char,        /*n*/
      regex_constants::syntax_char,        /*o*/
      regex_constants::syntax_char,        /*p*/
      regex_constants::syntax_char,        /*q*/
      regex_constants::syntax_char,        /*r*/
      regex_constants::syntax_char,        /*s*/
      regex_constants::syntax_char,        /*t*/
      regex_constants::syntax_char,        /*u*/
      regex_constants::syntax_char,        /*v*/
      regex_constants::syntax_char,        /*w*/
      regex_constants::syntax_char,        /*x*/
      regex_constants::syntax_char,        /*y*/
      regex_constants::syntax_char,        /*z*/
      regex_constants::syntax_open_brace,        /*{*/
      regex_constants::syntax_or,        /*|*/
      regex_constants::syntax_close_brace,        /*}*/
      regex_constants::syntax_char,        /*~*/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
      regex_constants::syntax_char,        /**/
   };

   return char_syntax[(unsigned char)c];
}

inline regex_constants::escape_syntax_type  get_default_escape_syntax_type(char c)
{
   //
   // char_syntax determines how the compiler treats a given character
   // in a regular expression.
   //
   static regex_constants::escape_syntax_type char_syntax[] = {
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,     /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /* */    // 32
      regex_constants::escape_type_identity,        /*!*/
      regex_constants::escape_type_identity,        /*"*/
      regex_constants::escape_type_identity,        /*#*/
      regex_constants::escape_type_identity,        /*$*/
      regex_constants::escape_type_identity,        /*%*/
      regex_constants::escape_type_identity,        /*&*/
      regex_constants::escape_type_end_buffer,        /*'*/
      regex_constants::syntax_open_mark,        /*(*/
      regex_constants::syntax_close_mark,        /*)*/
      regex_constants::escape_type_identity,        /***/
      regex_constants::syntax_plus,                 /*+*/
      regex_constants::escape_type_identity,        /*,*/
      regex_constants::escape_type_identity,        /*-*/
      regex_constants::escape_type_identity,        /*.*/
      regex_constants::escape_type_identity,        /*/*/
      regex_constants::escape_type_decimal,        /*0*/
      regex_constants::escape_type_backref,        /*1*/
      regex_constants::escape_type_backref,        /*2*/
      regex_constants::escape_type_backref,        /*3*/
      regex_constants::escape_type_backref,        /*4*/
      regex_constants::escape_type_backref,        /*5*/
      regex_constants::escape_type_backref,        /*6*/
      regex_constants::escape_type_backref,        /*7*/
      regex_constants::escape_type_backref,        /*8*/
      regex_constants::escape_type_backref,        /*9*/
      regex_constants::escape_type_identity,        /*:*/
      regex_constants::escape_type_identity,        /*;*/
      regex_constants::escape_type_left_word,        /*<*/
      regex_constants::escape_type_identity,        /*=*/
      regex_constants::escape_type_right_word,        /*>*/
      regex_constants::syntax_question,              /*?*/
      regex_constants::escape_type_identity,         /*@*/
      regex_constants::escape_type_start_buffer,     /*A*/
      regex_constants::escape_type_not_word_assert,  /*B*/
      regex_constants::escape_type_C,                /*C*/
      regex_constants::escape_type_not_class,        /*D*/
      regex_constants::escape_type_E,                /*E*/
      regex_constants::escape_type_not_class,        /*F*/
      regex_constants::escape_type_G,                /*G*/
      regex_constants::escape_type_not_class,        /*H*/
      regex_constants::escape_type_not_class,        /*I*/
      regex_constants::escape_type_not_class,        /*J*/
      regex_constants::escape_type_reset_start_mark, /*K*/
      regex_constants::escape_type_not_class,        /*L*/
      regex_constants::escape_type_not_class,        /*M*/
      regex_constants::escape_type_named_char,       /*N*/
      regex_constants::escape_type_not_class,        /*O*/
      regex_constants::escape_type_not_property,     /*P*/
      regex_constants::escape_type_Q,                /*Q*/
      regex_constants::escape_type_line_ending,      /*R*/
      regex_constants::escape_type_not_class,        /*S*/
      regex_constants::escape_type_not_class,        /*T*/
      regex_constants::escape_type_not_class,        /*U*/
      regex_constants::escape_type_not_class,        /*V*/
      regex_constants::escape_type_not_class,        /*W*/
      regex_constants::escape_type_X,                /*X*/
      regex_constants::escape_type_not_class,        /*Y*/
      regex_constants::escape_type_Z,                /*Z*/
      regex_constants::escape_type_identity,        /*[*/
      regex_constants::escape_type_identity,        /*\*/
      regex_constants::escape_type_identity,        /*]*/
      regex_constants::escape_type_identity,        /*^*/
      regex_constants::escape_type_identity,        /*_*/
      regex_constants::escape_type_start_buffer,        /*`*/
      regex_constants::escape_type_control_a,        /*a*/
      regex_constants::escape_type_word_assert,        /*b*/
      regex_constants::escape_type_ascii_control,        /*c*/
      regex_constants::escape_type_class,        /*d*/
      regex_constants::escape_type_e,        /*e*/
      regex_constants::escape_type_control_f,       /*f*/
      regex_constants::escape_type_extended_backref,  /*g*/
      regex_constants::escape_type_class,        /*h*/
      regex_constants::escape_type_class,        /*i*/
      regex_constants::escape_type_class,        /*j*/
      regex_constants::escape_type_extended_backref, /*k*/
      regex_constants::escape_type_class,        /*l*/
      regex_constants::escape_type_class,        /*m*/
      regex_constants::escape_type_control_n,       /*n*/
      regex_constants::escape_type_class,           /*o*/
      regex_constants::escape_type_property,        /*p*/
      regex_constants::escape_type_class,           /*q*/
      regex_constants::escape_type_control_r,       /*r*/
      regex_constants::escape_type_class,           /*s*/
      regex_constants::escape_type_control_t,       /*t*/
      regex_constants::escape_type_class,         /*u*/
      regex_constants::escape_type_control_v,       /*v*/
      regex_constants::escape_type_class,           /*w*/
      regex_constants::escape_type_hex,             /*x*/
      regex_constants::escape_type_class,           /*y*/
      regex_constants::escape_type_end_buffer,      /*z*/
      regex_constants::syntax_open_brace,           /*{*/
      regex_constants::syntax_or,                   /*|*/
      regex_constants::syntax_close_brace,          /*}*/
      regex_constants::escape_type_identity,        /*~*/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
      regex_constants::escape_type_identity,        /**/
   };

   return char_syntax[(unsigned char)c];
}

// is charT c a combining character?
inline bool  is_combining_implementation(std::uint_least16_t c)
{
   const std::uint_least16_t combining_ranges[] = { 0x0300, 0x0361,
                           0x0483, 0x0486,
                           0x0903, 0x0903,
                           0x093E, 0x0940,
                           0x0949, 0x094C,
                           0x0982, 0x0983,
                           0x09BE, 0x09C0,
                           0x09C7, 0x09CC,
                           0x09D7, 0x09D7,
                           0x0A3E, 0x0A40,
                           0x0A83, 0x0A83,
                           0x0ABE, 0x0AC0,
                           0x0AC9, 0x0ACC,
                           0x0B02, 0x0B03,
                           0x0B3E, 0x0B3E,
                           0x0B40, 0x0B40,
                           0x0B47, 0x0B4C,
                           0x0B57, 0x0B57,
                           0x0B83, 0x0B83,
                           0x0BBE, 0x0BBF,
                           0x0BC1, 0x0BCC,
                           0x0BD7, 0x0BD7,
                           0x0C01, 0x0C03,
                           0x0C41, 0x0C44,
                           0x0C82, 0x0C83,
                           0x0CBE, 0x0CBE,
                           0x0CC0, 0x0CC4,
                           0x0CC7, 0x0CCB,
                           0x0CD5, 0x0CD6,
                           0x0D02, 0x0D03,
                           0x0D3E, 0x0D40,
                           0x0D46, 0x0D4C,
                           0x0D57, 0x0D57,
                           0x0F7F, 0x0F7F,
                           0x20D0, 0x20E1,
                           0x3099, 0x309A,
                           0xFE20, 0xFE23,
                           0xffff, 0xffff, };

   const std::uint_least16_t* p = combining_ranges + 1;
   while (*p < c) p += 2;
   --p;
   if ((c >= *p) && (c <= *(p + 1)))
      return true;
   return false;
}

template <class charT>
inline bool is_combining(charT c)
{
   return (c <= static_cast<charT>(0)) ? false : ((c >= static_cast<charT>((std::numeric_limits<uint_least16_t>::max)())) ? false : is_combining_implementation(static_cast<unsigned short>(c)));
}
template <>
inline bool is_combining<char>(char)
{
   return false;
}
template <>
inline bool is_combining<signed char>(signed char)
{
   return false;
}
template <>
inline bool is_combining<unsigned char>(unsigned char)
{
   return false;
}
#ifdef _MSC_VER
template<>
inline bool is_combining<wchar_t>(wchar_t c)
{
   return is_combining_implementation(static_cast<unsigned short>(c));
}
#elif !defined(__DECCXX) && !defined(__osf__) && !defined(__OSF__) && defined(WCHAR_MIN) && (WCHAR_MIN == 0) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
#if defined(WCHAR_MAX) && (WCHAR_MAX <= USHRT_MAX)
template<>
inline bool is_combining<wchar_t>(wchar_t c)
{
   return is_combining_implementation(static_cast<unsigned short>(c));
}
#else
template<>
inline bool is_combining<wchar_t>(wchar_t c)
{
   return (c >= (std::numeric_limits<uint_least16_t>::max)()) ? false : is_combining_implementation(static_cast<unsigned short>(c));
}
#endif
#endif

//
// is a charT c a line separator?
//
template <class charT>
inline bool is_separator(charT c)
{
   return BOOST_REGEX_MAKE_BOOL(
      (c == static_cast<charT>('\n'))
      || (c == static_cast<charT>('\r'))
      || (c == static_cast<charT>('\f'))
      || (static_cast<std::uint16_t>(c) == 0x2028u)
      || (static_cast<std::uint16_t>(c) == 0x2029u)
      || (static_cast<std::uint16_t>(c) == 0x85u));
}
template <>
inline bool is_separator<char>(char c)
{
   return BOOST_REGEX_MAKE_BOOL((c == '\n') || (c == '\r') || (c == '\f'));
}

//
// get a default collating element:
//
inline std::string  lookup_default_collate_name(const std::string& name)
{
   //
   // these are the POSIX collating names:
   //
   static const char* def_coll_names[] = {
   "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "alert", "backspace", "tab", "newline",
   "vertical-tab", "form-feed", "carriage-return", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK",
   "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "IS4", "IS3", "IS2", "IS1", "space", "exclamation-mark",
   "quotation-mark", "number-sign", "dollar-sign", "percent-sign", "ampersand", "apostrophe",
   "left-parenthesis", "right-parenthesis", "asterisk", "plus-sign", "comma", "hyphen",
   "period", "slash", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
   "colon", "semicolon", "less-than-sign", "equals-sign", "greater-than-sign",
   "question-mark", "commercial-at", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
   "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "left-square-bracket", "backslash",
   "right-square-bracket", "circumflex", "underscore", "grave-accent", "a", "b", "c", "d", "e", "f",
   "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "left-curly-bracket",
   "vertical-line", "right-curly-bracket", "tilde", "DEL", "",
   };

   // these multi-character collating elements
   // should keep most Western-European locales
   // happy - we should really localise these a
   // little more - but this will have to do for
   // now:

   static const char* def_multi_coll[] = {
      "ae",
      "Ae",
      "AE",
      "ch",
      "Ch",
      "CH",
      "ll",
      "Ll",
      "LL",
      "ss",
      "Ss",
      "SS",
      "nj",
      "Nj",
      "NJ",
      "dz",
      "Dz",
      "DZ",
      "lj",
      "Lj",
      "LJ",
      "",
   };

   unsigned int i = 0;
   while (*def_coll_names[i])
   {
      if (def_coll_names[i] == name)
      {
         return std::string(1, char(i));
      }
      ++i;
   }
   i = 0;
   while (*def_multi_coll[i])
   {
      if (def_multi_coll[i] == name)
      {
         return def_multi_coll[i];
      }
      ++i;
   }
   return std::string();
}

//
// get the state_id of a character classification, the individual
// traits classes then transform that state_id into a bitmask:
//
template <class charT>
struct character_pointer_range
{
   const charT* p1;
   const charT* p2;

   bool operator < (const character_pointer_range& r)const
   {
      return std::lexicographical_compare(p1, p2, r.p1, r.p2);
   }
   bool operator == (const character_pointer_range& r)const
   {
      // Not only do we check that the ranges are of equal size before
      // calling std::equal, but there is no other algorithm available:
      // not even a non-standard MS one.  So forward to unchecked_equal
      // in the MS case.
#ifdef __cpp_lib_robust_nonmodifying_seq_ops
      return std::equal(p1, p2, r.p1, r.p2);
#elif defined(BOOST_REGEX_MSVC)
      if (((p2 - p1) != (r.p2 - r.p1)))
         return false;
      const charT* with = r.p1;
      const charT* pos = p1;
      while (pos != p2)
         if (*pos++ != *with++) return false;
      return true;

#else
      return ((p2 - p1) == (r.p2 - r.p1)) && std::equal(p1, p2, r.p1);
#endif
   }
};
template <class charT>
int get_default_class_id(const charT* p1, const charT* p2)
{
   static const charT data[73] = {
      'a', 'l', 'n', 'u', 'm',
      'a', 'l', 'p', 'h', 'a',
      'b', 'l', 'a', 'n', 'k',
      'c', 'n', 't', 'r', 'l',
      'd', 'i', 'g', 'i', 't',
      'g', 'r', 'a', 'p', 'h',
      'l', 'o', 'w', 'e', 'r',
      'p', 'r', 'i', 'n', 't',
      'p', 'u', 'n', 'c', 't',
      's', 'p', 'a', 'c', 'e',
      'u', 'n', 'i', 'c', 'o', 'd', 'e',
      'u', 'p', 'p', 'e', 'r',
      'v',
      'w', 'o', 'r', 'd',
      'x', 'd', 'i', 'g', 'i', 't',
   };

   static const character_pointer_range<charT> ranges[21] =
   {
      {data+0, data+5,}, // alnum
      {data+5, data+10,}, // alpha
      {data+10, data+15,}, // blank
      {data+15, data+20,}, // cntrl
      {data+20, data+21,}, // d
      {data+20, data+25,}, // digit
      {data+25, data+30,}, // graph
      {data+29, data+30,}, // h
      {data+30, data+31,}, // l
      {data+30, data+35,}, // lower
      {data+35, data+40,}, // print
      {data+40, data+45,}, // punct
      {data+45, data+46,}, // s
      {data+45, data+50,}, // space
      {data+57, data+58,}, // u
      {data+50, data+57,}, // unicode
      {data+57, data+62,}, // upper
      {data+62, data+63,}, // v
      {data+63, data+64,}, // w
      {data+63, data+67,}, // word
      {data+67, data+73,}, // xdigit
   };
   const character_pointer_range<charT>* ranges_begin = ranges;
   const character_pointer_range<charT>* ranges_end = ranges + (sizeof(ranges)/sizeof(ranges[0]));

   character_pointer_range<charT> t = { p1, p2, };
   const character_pointer_range<charT>* p = std::lower_bound(ranges_begin, ranges_end, t);
   if((p != ranges_end) && (t == *p))
      return static_cast<int>(p - ranges);
   return -1;
}

//
// helper functions:
//
template <class charT>
std::ptrdiff_t global_length(const charT* p)
{
   std::ptrdiff_t n = 0;
   while(*p)
   {
      ++p;
      ++n;
   }
   return n;
}
template<>
inline std::ptrdiff_t global_length<char>(const char* p)
{
   return (std::strlen)(p);
}
#ifndef BOOST_NO_WREGEX
template<>
inline std::ptrdiff_t global_length<wchar_t>(const wchar_t* p)
{
   return (std::ptrdiff_t)(std::wcslen)(p);
}
#endif
template <class charT>
inline charT  global_lower(charT c)
{
   return c;
}
template <class charT>
inline charT  global_upper(charT c)
{
   return c;
}

inline char  do_global_lower(char c)
{
   return static_cast<char>((std::tolower)((unsigned char)c));
}

inline char  do_global_upper(char c)
{
   return static_cast<char>((std::toupper)((unsigned char)c));
}
#ifndef BOOST_NO_WREGEX
inline wchar_t  do_global_lower(wchar_t c)
{
   return (std::towlower)(c);
}

inline wchar_t  do_global_upper(wchar_t c)
{
   return (std::towupper)(c);
}
#endif
//
// This sucks: declare template specialisations of global_lower/global_upper
// that just forward to the non-template implementation functions.  We do
// this because there is one compiler (Compaq Tru64 C++) that doesn't seem
// to differentiate between templates and non-template overloads....
// what's more, the primary template, plus all overloads have to be
// defined in the same translation unit (if one is inline they all must be)
// otherwise the "local template instantiation" compiler option can pick
// the wrong instantiation when linking:
//
template<> inline char  global_lower<char>(char c) { return do_global_lower(c); }
template<> inline char  global_upper<char>(char c) { return do_global_upper(c); }
#ifndef BOOST_NO_WREGEX
template<> inline wchar_t  global_lower<wchar_t>(wchar_t c) { return do_global_lower(c); }
template<> inline wchar_t  global_upper<wchar_t>(wchar_t c) { return do_global_upper(c); }
#endif

template <class charT>
int global_value(charT c)
{
   static const charT zero = '0';
   static const charT nine = '9';
   static const charT a = 'a';
   static const charT f = 'f';
   static const charT A = 'A';
   static const charT F = 'F';

   if(c > f) return -1;
   if(c >= a) return 10 + (c - a);
   if(c > F) return -1;
   if(c >= A) return 10 + (c - A);
   if(c > nine) return -1;
   if(c >= zero) return c - zero;
   return -1;
}
template <class charT, class traits>
std::intmax_t global_toi(const charT*& p1, const charT* p2, int radix, const traits& t)
{
   (void)t; // warning suppression
   std::intmax_t limit = (std::numeric_limits<std::intmax_t>::max)() / radix;
   std::intmax_t next_value = t.value(*p1, radix);
   if((p1 == p2) || (next_value < 0) || (next_value >= radix))
      return -1;
   std::intmax_t result = 0;
   while(p1 != p2)
   {
      next_value = t.value(*p1, radix);
      if((next_value < 0) || (next_value >= radix))
         break;
      result *= radix;
      result += next_value;
      ++p1;
      if (result > limit)
         return -1;
   }
   return result;
}

template <class charT>
inline typename std::enable_if<(sizeof(charT) > 1), const charT*>::type get_escape_R_string()
{
#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#  pragma warning(disable:4309 4245)
#endif
   static const charT e1[] = { '(', '?', '-', 'x', ':', '(', '?', '>', '\x0D', '\x0A', '?',
      '|', '[', '\x0A', '\x0B', '\x0C', static_cast<charT>(0x85), static_cast<charT>(0x2028),
      static_cast<charT>(0x2029), ']', ')', ')', '\0' };
   static const charT e2[] = { '(', '?', '-', 'x', ':', '(', '?', '>', '\x0D', '\x0A', '?',
      '|', '[', '\x0A', '\x0B', '\x0C', static_cast<charT>(0x85), ']', ')', ')', '\0' };

   charT c = static_cast<charT>(0x2029u);
   bool b = (static_cast<unsigned>(c) == 0x2029u);

   return (b ? e1 : e2);
#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif
}

template <class charT>
inline typename std::enable_if<(sizeof(charT) == 1), const charT*>::type get_escape_R_string()
{
#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#  pragma warning(disable:4309 4245)
#endif
   static const charT e2[] = { 
      static_cast<charT>('('), 
      static_cast<charT>('?'), 
      static_cast<charT>('-'), 
      static_cast<charT>('x'), 
      static_cast<charT>(':'), 
      static_cast<charT>('('), 
      static_cast<charT>('?'), 
      static_cast<charT>('>'), 
      static_cast<charT>('\x0D'), 
      static_cast<charT>('\x0A'), 
      static_cast<charT>('?'),
      static_cast<charT>('|'), 
      static_cast<charT>('['), 
      static_cast<charT>('\x0A'), 
      static_cast<charT>('\x0B'), 
      static_cast<charT>('\x0C'), 
      static_cast<charT>('\x85'), 
      static_cast<charT>(']'), 
      static_cast<charT>(')'), 
      static_cast<charT>(')'), 
      static_cast<charT>('\0') 
   };
   return e2;
#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif
}

} // BOOST_REGEX_DETAIL_NS
} // boost

#endif

/* regex_traits_defaults.hpp
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
*/