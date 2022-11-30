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

#ifndef BOOST_REGEX_V4_MATCH_FLAGS
#define BOOST_REGEX_V4_MATCH_FLAGS

#ifdef __cplusplus
#  include <boost/cstdint.hpp>
#endif

#ifdef __cplusplus
namespace boost{
   namespace regex_constants{
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#if BOOST_MSVC >= 1800
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

#if defined(BOOST_BORLANDC) || (defined(_MSC_VER) && (_MSC_VER <= 1310))
typedef unsigned long match_flag_type;
#else
typedef match_flags match_flag_type;


#ifdef __cplusplus
inline match_flags operator&(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) & static_cast<boost::int32_t>(m2)); }
inline match_flags operator|(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) | static_cast<boost::int32_t>(m2)); }
inline match_flags operator^(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) ^ static_cast<boost::int32_t>(m2)); }
inline match_flags operator~(match_flags m1)
{ return static_cast<match_flags>(~static_cast<boost::int32_t>(m1)); }
inline match_flags& operator&=(match_flags& m1, match_flags m2)
{ m1 = m1&m2; return m1; }
inline match_flags& operator|=(match_flags& m1, match_flags m2)
{ m1 = m1|m2; return m1; }
inline match_flags& operator^=(match_flags& m1, match_flags m2)
{ m1 = m1^m2; return m1; }
#endif
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

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


} /* namespace boost */
#endif /* __cplusplus */
#endif /* include guard */


/* match_flags.hpp
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
*/