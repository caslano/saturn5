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
  *   FILE         states.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares internal state machine structures.
  */

#ifndef BOOST_REGEX_V5_STATES_HPP
#define BOOST_REGEX_V5_STATES_HPP

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

/*** mask_type *******************************************************
Whenever we have a choice of two alternatives, we use an array of bytes
to indicate which of the two alternatives it is possible to take for any
given input character.  If mask_take is set, then we can take the next 
state, and if mask_skip is set then we can take the alternative.
***********************************************************************/
enum mask_type
{
   mask_take = 1,
   mask_skip = 2,
   mask_init = 4,
   mask_any = mask_skip | mask_take,
   mask_all = mask_any
};

/*** helpers **********************************************************
These helpers let us use function overload resolution to detect whether
we have narrow or wide character strings:
***********************************************************************/
struct _narrow_type{};
struct _wide_type{};
template <class charT> struct is_byte;
template<>             struct is_byte<char>         { typedef _narrow_type width_type; };
template<>             struct is_byte<unsigned char>{ typedef _narrow_type width_type; };
template<>             struct is_byte<signed char>  { typedef _narrow_type width_type; };
template <class charT> struct is_byte               { typedef _wide_type width_type; };

/*** enum syntax_element_type ******************************************
Every record in the state machine falls into one of the following types:
***********************************************************************/
enum syntax_element_type
{
   // start of a marked sub-expression, or perl-style (?...) extension
   syntax_element_startmark = 0,
   // end of a marked sub-expression, or perl-style (?...) extension
   syntax_element_endmark = syntax_element_startmark + 1,
   // any sequence of literal characters
   syntax_element_literal = syntax_element_endmark + 1,
   // start of line assertion: ^
   syntax_element_start_line = syntax_element_literal + 1,
   // end of line assertion $
   syntax_element_end_line = syntax_element_start_line + 1,
   // match any character: .
   syntax_element_wild = syntax_element_end_line + 1,
   // end of expression: we have a match when we get here
   syntax_element_match = syntax_element_wild + 1,
   // perl style word boundary: \b
   syntax_element_word_boundary = syntax_element_match + 1,
   // perl style within word boundary: \B
   syntax_element_within_word = syntax_element_word_boundary + 1,
   // start of word assertion: \<
   syntax_element_word_start = syntax_element_within_word + 1,
   // end of word assertion: \>
   syntax_element_word_end = syntax_element_word_start + 1,
   // start of buffer assertion: \`
   syntax_element_buffer_start = syntax_element_word_end + 1,
   // end of buffer assertion: \'
   syntax_element_buffer_end = syntax_element_buffer_start + 1,
   // backreference to previously matched sub-expression
   syntax_element_backref = syntax_element_buffer_end + 1,
   // either a wide character set [..] or one with multicharacter collating elements:
   syntax_element_long_set = syntax_element_backref + 1,
   // narrow character set: [...]
   syntax_element_set = syntax_element_long_set + 1,
   // jump to a new state in the machine:
   syntax_element_jump = syntax_element_set + 1,
   // choose between two production states:
   syntax_element_alt = syntax_element_jump + 1,
   // a repeat
   syntax_element_rep = syntax_element_alt + 1,
   // match a combining character sequence
   syntax_element_combining = syntax_element_rep + 1,
   // perl style soft buffer end: \z
   syntax_element_soft_buffer_end = syntax_element_combining + 1,
   // perl style continuation: \G
   syntax_element_restart_continue = syntax_element_soft_buffer_end + 1,
   // single character repeats:
   syntax_element_dot_rep = syntax_element_restart_continue + 1,
   syntax_element_char_rep = syntax_element_dot_rep + 1,
   syntax_element_short_set_rep = syntax_element_char_rep + 1,
   syntax_element_long_set_rep = syntax_element_short_set_rep + 1,
   // a backstep for lookbehind repeats:
   syntax_element_backstep = syntax_element_long_set_rep + 1,
   // an assertion that a mark was matched:
   syntax_element_assert_backref = syntax_element_backstep + 1,
   syntax_element_toggle_case = syntax_element_assert_backref + 1,
   // a recursive expression:
   syntax_element_recurse = syntax_element_toggle_case + 1,
   // Verbs:
   syntax_element_fail = syntax_element_recurse + 1,
   syntax_element_accept = syntax_element_fail + 1,
   syntax_element_commit = syntax_element_accept + 1,
   syntax_element_then = syntax_element_commit + 1
};

#ifdef BOOST_REGEX_DEBUG
// dwa 09/26/00 - This is needed to suppress warnings about an ambiguous conversion
std::ostream& operator<<(std::ostream&, syntax_element_type);
#endif

struct re_syntax_base;

/*** union offset_type ************************************************
Points to another state in the machine.  During machine construction
we use integral offsets, but these are converted to pointers before
execution of the machine.
***********************************************************************/
union offset_type
{
   re_syntax_base*   p;
   std::ptrdiff_t    i;
};

/*** struct re_syntax_base ********************************************
Base class for all states in the machine.
***********************************************************************/
struct re_syntax_base
{
   syntax_element_type   type;         // what kind of state this is
   offset_type           next;         // next state in the machine
};

/*** struct re_brace **************************************************
A marked parenthesis.
***********************************************************************/
struct re_brace : public re_syntax_base
{
   // The index to match, can be zero (don't mark the sub-expression)
   // or negative (for perl style (?...) extensions):
   int index;
   bool icase;
};

/*** struct re_dot **************************************************
Match anything.
***********************************************************************/
enum
{
   dont_care = 1,
   force_not_newline = 0,
   force_newline = 2,

   test_not_newline = 2,
   test_newline = 3
};
struct re_dot : public re_syntax_base
{
   unsigned char mask;
};

/*** struct re_literal ************************************************
A string of literals, following this structure will be an 
array of characters: charT[length]
***********************************************************************/
struct re_literal : public re_syntax_base
{
   unsigned int length;
};

/*** struct re_case ************************************************
Indicates whether we are moving to a case insensive block or not
***********************************************************************/
struct re_case : public re_syntax_base
{
   bool icase;
};

/*** struct re_set_long ***********************************************
A wide character set of characters, following this structure will be
an array of type charT:
First csingles null-terminated strings
Then 2 * cranges NULL terminated strings
Then cequivalents NULL terminated strings
***********************************************************************/
template <class mask_type>
struct re_set_long : public re_syntax_base
{
   unsigned int            csingles, cranges, cequivalents;
   mask_type               cclasses;
   mask_type               cnclasses;
   bool                    isnot;
   bool                    singleton;
};

/*** struct re_set ****************************************************
A set of narrow-characters, matches any of _map which is none-zero
***********************************************************************/
struct re_set : public re_syntax_base
{
   unsigned char _map[1 << CHAR_BIT];
};

/*** struct re_jump ***************************************************
Jump to a new location in the machine (not next).
***********************************************************************/
struct re_jump : public re_syntax_base
{
   offset_type     alt;                 // location to jump to
};

/*** struct re_alt ***************************************************
Jump to a new location in the machine (possibly next).
***********************************************************************/
struct re_alt : public re_jump
{
   unsigned char   _map[1 << CHAR_BIT]; // which characters can take the jump
   unsigned int    can_be_null;         // true if we match a NULL string
};

/*** struct re_repeat *************************************************
Repeat a section of the machine
***********************************************************************/
struct re_repeat : public re_alt
{
   std::size_t   min, max;  // min and max allowable repeats
   int           state_id;        // Unique identifier for this repeat
   bool          leading;   // True if this repeat is at the start of the machine (lets us optimize some searches)
   bool          greedy;    // True if this is a greedy repeat
};

/*** struct re_recurse ************************************************
Recurse to a particular subexpression.
**********************************************************************/
struct re_recurse : public re_jump
{
   int state_id;             // identifier of first nested repeat within the recursion.
};

/*** struct re_commit *************************************************
Used for the PRUNE, SKIP and COMMIT verbs which basically differ only in what happens
if no match is found and we start searching forward.
**********************************************************************/
enum commit_type
{
   commit_prune,
   commit_skip,
   commit_commit
};
struct re_commit : public re_syntax_base
{
   commit_type action;
};

/*** enum re_jump_size_type *******************************************
Provides compiled size of re_jump structure (allowing for trailing alignment).
We provide this so we know how manybytes to insert when constructing the machine
(The value of padding_mask is defined in regex_raw_buffer.hpp).
***********************************************************************/
enum re_jump_size_type
{
   re_jump_size = (sizeof(re_jump) + padding_mask) & ~(padding_mask),
   re_repeater_size = (sizeof(re_repeat) + padding_mask) & ~(padding_mask),
   re_alt_size = (sizeof(re_alt) + padding_mask) & ~(padding_mask)
};

/*** proc re_is_set_member *********************************************
Forward declaration: we'll need this one later...
***********************************************************************/

template<class charT, class traits>
struct regex_data;

template <class iterator, class charT, class traits_type, class char_classT>
iterator  re_is_set_member(iterator next, 
                          iterator last, 
                          const re_set_long<char_classT>* set_, 
                          const regex_data<charT, traits_type>& e, bool icase);

} // namespace BOOST_REGEX_DETAIL_NS

} // namespace boost

#endif



/* states.hpp
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
*/