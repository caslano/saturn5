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

#ifndef BOOST_REGEX_V4_STATES_HPP
#define BOOST_REGEX_V4_STATES_HPP

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
iterator BOOST_REGEX_CALL re_is_set_member(iterator next, 
                          iterator last, 
                          const re_set_long<char_classT>* set_, 
                          const regex_data<charT, traits_type>& e, bool icase);

} // namespace BOOST_REGEX_DETAIL_NS

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



/* states.hpp
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
*/