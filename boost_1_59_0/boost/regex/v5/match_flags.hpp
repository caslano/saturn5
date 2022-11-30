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
  *   FILE         match_flags.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares match_flags type.
  */

#ifndef BOOST_REGEX_V5_MATCH_FLAGS
#define BOOST_REGEX_V5_MATCH_FLAGS

#ifdef __cplusplus
#  include <cstdint>
#endif

#ifdef __cplusplus
namespace boost{
   namespace regex_constants{
#endif

#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#if BOOST_REGEX_MSVC >= 1800
#pragma warning(disable : 26812)
#endif
#endif

typedef enum _match_flags
{
   match_default = 0,
   match_not_bol = 1,                                /* first is not start of line */
   match_not_eol = match_not_bol << 1,               /* last is not end of line */
   match_not_bob = match_not_eol << 1,               /* first is not start of buffer */
   match_not_eob = match_not_bob << 1,               /* last is not end of buffer */
   match_not_bow = match_not_eob << 1,               /* first is not start of word */
   match_not_eow = match_not_bow << 1,               /* last is not end of word */
   match_not_dot_newline = match_not_eow << 1,       /* \n is not matched by '.' */
   match_not_dot_null = match_not_dot_newline << 1,  /* '\0' is not matched by '.' */
   match_prev_avail = match_not_dot_null << 1,       /* *--first is a valid expression */
   match_init = match_prev_avail << 1,               /* internal use */
   match_any = match_init << 1,                      /* don't care what we match */
   match_not_null = match_any << 1,                  /* string can't be null */
   match_continuous = match_not_null << 1,           /* each grep match must continue from */
                                                     /* uninterrupted from the previous one */
   match_partial = match_continuous << 1,            /* find partial matches */
   
   match_stop = match_partial << 1,                  /* stop after first match (grep) V3 only */
   match_not_initial_null = match_stop,              /* don't match initial null, V4 only */
   match_all = match_stop << 1,                      /* must find the whole of input even if match_any is set */
   match_perl = match_all << 1,                      /* Use perl matching rules */
   match_posix = match_perl << 1,                    /* Use POSIX matching rules */
   match_nosubs = match_posix << 1,                  /* don't trap marked subs */
   match_extra = match_nosubs << 1,                  /* include full capture information for repeated captures */
   match_single_line = match_extra << 1,             /* treat text as single line and ignore any \n's when matching ^ and $. */
   match_unused1 = match_single_line << 1,           /* unused */
   match_unused2 = match_unused1 << 1,               /* unused */
   match_unused3 = match_unused2 << 1,               /* unused */
   match_max = match_unused3,

   format_perl = 0,                                  /* perl style replacement */
   format_default = 0,                               /* ditto. */
   format_sed = match_max << 1,                      /* sed style replacement. */
   format_all = format_sed << 1,                     /* enable all extensions to syntax. */
   format_no_copy = format_all << 1,                 /* don't copy non-matching segments. */
   format_first_only = format_no_copy << 1,          /* Only replace first occurrence. */
   format_is_if = format_first_only << 1,            /* internal use only. */
   format_literal = format_is_if << 1,               /* treat string as a literal */

   match_not_any = match_not_bol | match_not_eol | match_not_bob 
      | match_not_eob | match_not_bow | match_not_eow | match_not_dot_newline 
      | match_not_dot_null | match_prev_avail | match_init | match_not_null
      | match_continuous | match_partial | match_stop | match_not_initial_null 
      | match_stop | match_all | match_perl | match_posix | match_nosubs
      | match_extra | match_single_line | match_unused1 | match_unused2 
      | match_unused3 | match_max | format_perl | format_default | format_sed
      | format_all | format_no_copy | format_first_only | format_is_if
      | format_literal


} match_flags;

typedef match_flags match_flag_type;

#ifdef __cplusplus
inline match_flags operator&(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<std::int32_t>(m1) & static_cast<std::int32_t>(m2)); }
inline match_flags operator|(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<std::int32_t>(m1) | static_cast<std::int32_t>(m2)); }
inline match_flags operator^(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<std::int32_t>(m1) ^ static_cast<std::int32_t>(m2)); }
inline match_flags operator~(match_flags m1)
{ return static_cast<match_flags>(~static_cast<std::int32_t>(m1)); }
inline match_flags& operator&=(match_flags& m1, match_flags m2)
{ m1 = m1&m2; return m1; }
inline match_flags& operator|=(match_flags& m1, match_flags m2)
{ m1 = m1|m2; return m1; }
inline match_flags& operator^=(match_flags& m1, match_flags m2)
{ m1 = m1^m2; return m1; }
#endif

#ifdef __cplusplus
} /* namespace regex_constants */
/*
 * import names into boost for backwards compatibility:
 */
using regex_constants::match_flag_type;
using regex_constants::match_default;
using regex_constants::match_not_bol;
using regex_constants::match_not_eol;
using regex_constants::match_not_bob;
using regex_constants::match_not_eob;
using regex_constants::match_not_bow;
using regex_constants::match_not_eow;
using regex_constants::match_not_dot_newline;
using regex_constants::match_not_dot_null;
using regex_constants::match_prev_avail;
/* using regex_constants::match_init; */
using regex_constants::match_any;
using regex_constants::match_not_null;
using regex_constants::match_continuous;
using regex_constants::match_partial;
/*using regex_constants::match_stop; */
using regex_constants::match_all;
using regex_constants::match_perl;
using regex_constants::match_posix;
using regex_constants::match_nosubs;
using regex_constants::match_extra;
using regex_constants::match_single_line;
/*using regex_constants::match_max; */
using regex_constants::format_all;
using regex_constants::format_sed;
using regex_constants::format_perl;
using regex_constants::format_default;
using regex_constants::format_no_copy;
using regex_constants::format_first_only;
/*using regex_constants::format_is_if;*/

#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif


} /* namespace boost */
#endif /* __cplusplus */
#endif /* include guard */


/* match_flags.hpp
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
*/