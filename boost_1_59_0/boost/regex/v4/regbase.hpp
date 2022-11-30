/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regbase.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares class regbase.
  */

#ifndef BOOST_REGEX_V4_REGBASE_HPP
#define BOOST_REGEX_V4_REGBASE_HPP

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

namespace boost{
//
// class regbase
// handles error codes and flags
//
class BOOST_REGEX_DECL regbase
{
public:
   enum flag_type_
   {
      //
      // Divide the flags up into logical groups:
      // bits 0-7 indicate main synatx type.
      // bits 8-15 indicate syntax subtype.
      // bits 16-31 indicate options that are common to all
      // regex syntaxes.
      // In all cases the default is 0.
      //
      // Main synatx group:
      //
      perl_syntax_group = 0,                      // default
      basic_syntax_group = 1,                     // POSIX basic
      literal = 2,                                // all characters are literals
      main_option_type = literal | basic_syntax_group | perl_syntax_group, // everything!
      //
      // options specific to perl group:
      //
      no_bk_refs = 1 << 8,                        // \d not allowed
      no_perl_ex = 1 << 9,                        // disable perl extensions
      no_mod_m = 1 << 10,                         // disable Perl m modifier
      mod_x = 1 << 11,                            // Perl x modifier
      mod_s = 1 << 12,                            // force s modifier on (overrides match_not_dot_newline)
      no_mod_s = 1 << 13,                         // force s modifier off (overrides match_not_dot_newline)

      //
      // options specific to basic group:
      //
      no_char_classes = 1 << 8,                   // [[:CLASS:]] not allowed
      no_intervals = 1 << 9,                      // {x,y} not allowed
      bk_plus_qm = 1 << 10,                       // uses \+ and \?
      bk_vbar = 1 << 11,                          // use \| for alternatives
      emacs_ex = 1 << 12,                         // enables emacs extensions

      //
      // options common to all groups:
      //
      no_escape_in_lists = 1 << 16,                     // '\' not special inside [...]
      newline_alt = 1 << 17,                            // \n is the same as |
      no_except = 1 << 18,                              // no exception on error
      failbit = 1 << 19,                                // error flag
      icase = 1 << 20,                                  // characters are matched regardless of case
      nocollate = 0,                                    // don't use locale specific collation (deprecated)
      collate = 1 << 21,                                // use locale specific collation
      nosubs = 1 << 22,                                 // don't mark sub-expressions
      save_subexpression_location = 1 << 23,            // save subexpression locations
      no_empty_expressions = 1 << 24,                   // no empty expressions allowed
      optimize = 0,                                     // not really supported
      


      basic = basic_syntax_group | collate | no_escape_in_lists,
      extended = no_bk_refs | collate | no_perl_ex | no_escape_in_lists,
      normal = 0,
      emacs = basic_syntax_group | collate | emacs_ex | bk_vbar,
      awk = no_bk_refs | collate | no_perl_ex,
      grep = basic | newline_alt,
      egrep = extended | newline_alt,
      sed = basic,
      perl = normal,
      ECMAScript = normal,
      JavaScript = normal,
      JScript = normal
   };
   typedef unsigned int flag_type;

   enum restart_info
   {
      restart_any = 0,
      restart_word = 1,
      restart_line = 2,
      restart_buf = 3,
      restart_continue = 4,
      restart_lit = 5,
      restart_fixed_lit = 6, 
      restart_count = 7
   };
};

//
// provide std lib proposal compatible constants:
//
namespace regex_constants{

   enum flag_type_
   {

      no_except = ::boost::regbase::no_except,
      failbit = ::boost::regbase::failbit,
      literal = ::boost::regbase::literal,
      icase = ::boost::regbase::icase,
      nocollate = ::boost::regbase::nocollate,
      collate = ::boost::regbase::collate,
      nosubs = ::boost::regbase::nosubs,
      optimize = ::boost::regbase::optimize,
      bk_plus_qm = ::boost::regbase::bk_plus_qm,
      bk_vbar = ::boost::regbase::bk_vbar,
      no_intervals = ::boost::regbase::no_intervals,
      no_char_classes = ::boost::regbase::no_char_classes,
      no_escape_in_lists = ::boost::regbase::no_escape_in_lists,
      no_mod_m = ::boost::regbase::no_mod_m,
      mod_x = ::boost::regbase::mod_x,
      mod_s = ::boost::regbase::mod_s,
      no_mod_s = ::boost::regbase::no_mod_s,
      save_subexpression_location = ::boost::regbase::save_subexpression_location,
      no_empty_expressions = ::boost::regbase::no_empty_expressions,

      basic = ::boost::regbase::basic,
      extended = ::boost::regbase::extended,
      normal = ::boost::regbase::normal,
      emacs = ::boost::regbase::emacs,
      awk = ::boost::regbase::awk,
      grep = ::boost::regbase::grep,
      egrep = ::boost::regbase::egrep,
      sed = basic,
      perl = normal,
      ECMAScript = normal,
      JavaScript = normal,
      JScript = normal
   };
   typedef ::boost::regbase::flag_type syntax_option_type;

} // namespace regex_constants

} // namespace boost

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


/* regbase.hpp
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
*/