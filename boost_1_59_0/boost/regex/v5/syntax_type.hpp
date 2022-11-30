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