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

#ifndef BOOST_REGEX_V5_REGBASE_HPP
#define BOOST_REGEX_V5_REGBASE_HPP

namespace boost{
//
// class regbase
// handles error codes and flags
//
class regbase
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

#endif


/* regbase.hpp
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
*/