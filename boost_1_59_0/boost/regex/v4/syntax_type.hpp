/*
 *
 * Copyright (c) 2003
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         syntax_type.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression synatx type enumerator.
  */

#ifndef BOOST_REGEX_SYNTAX_TYPE_HPP
#define BOOST_REGEX_SYNTAX_TYPE_HPP

namespace boost{
namespace regex_constants{

typedef unsigned char syntax_type;

//
// values chosen are binary compatible with previous version:
//
static const syntax_type syntax_char = 0;
static const syntax_type syntax_open_mark = 1;
static const syntax_type syntax_close_mark = 2;
static const syntax_type syntax_dollar = 3;
static const syntax_type syntax_caret = 4;
static const syntax_type syntax_dot = 5;
static const syntax_type syntax_star = 6;
static const syntax_type syntax_plus = 7;
static const syntax_type syntax_question = 8;
static const syntax_type syntax_open_set = 9;
static const syntax_type syntax_close_set = 10;
static const syntax_type syntax_or = 11;
static const syntax_type syntax_escape = 12;
static const syntax_type syntax_dash = 14;
static const syntax_type syntax_open_brace = 15;
static const syntax_type syntax_close_brace = 16;
static const syntax_type syntax_digit = 17;
static const syntax_type syntax_comma = 27;
static const syntax_type syntax_equal = 37;
static const syntax_type syntax_colon = 36;
static const syntax_type syntax_not = 53;

// extensions:

static const syntax_type syntax_hash = 13;
static const syntax_type syntax_newline = 26;

// escapes:

typedef syntax_type escape_syntax_type;

static const escape_syntax_type escape_type_word_assert = 18;
static const escape_syntax_type escape_type_not_word_assert = 19;
static const escape_syntax_type escape_type_control_f = 29;
static const escape_syntax_type escape_type_control_n = 30;
static const escape_syntax_type escape_type_control_r = 31;
static const escape_syntax_type escape_type_control_t = 32;
static const escape_syntax_type escape_type_control_v = 33;
static const escape_syntax_type escape_type_ascii_control = 35;
static const escape_syntax_type escape_type_hex = 34;
static const escape_syntax_type escape_type_unicode = 0; // not used
static const escape_syntax_type escape_type_identity = 0; // not used
static const escape_syntax_type escape_type_backref = syntax_digit;
static const escape_syntax_type escape_type_decimal = syntax_digit; // not used
static const escape_syntax_type escape_type_class = 22; 
static const escape_syntax_type escape_type_not_class = 23; 

// extensions:

static const escape_syntax_type escape_type_left_word = 20;
static const escape_syntax_type escape_type_right_word = 21;
static const escape_syntax_type escape_type_start_buffer = 24;                 // for \`
static const escape_syntax_type escape_type_end_buffer = 25;                   // for \'
static const escape_syntax_type escape_type_control_a = 28;                    // for \a
static const escape_syntax_type escape_type_e = 38;                            // for \e
static const escape_syntax_type escape_type_E = 47;                            // for \Q\E
static const escape_syntax_type escape_type_Q = 48;                            // for \Q\E
static const escape_syntax_type escape_type_X = 49;                            // for \X
static const escape_syntax_type escape_type_C = 50;                            // for \C
static const escape_syntax_type escape_type_Z = 51;                            // for \Z
static const escape_syntax_type escape_type_G = 52;                            // for \G

static const escape_syntax_type escape_type_property = 54;                     // for \p
static const escape_syntax_type escape_type_not_property = 55;                 // for \P
static const escape_syntax_type escape_type_named_char = 56;                   // for \N
static const escape_syntax_type escape_type_extended_backref = 57;             // for \g
static const escape_syntax_type escape_type_reset_start_mark = 58;             // for \K
static const escape_syntax_type escape_type_line_ending = 59;                  // for \R

static const escape_syntax_type syntax_max = 60;

}
}


#endif

/* syntax_type.hpp
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
*/