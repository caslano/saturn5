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
  *   FILE         cregex.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares POSIX API functions
  *                + boost::RegEx high level wrapper.
  */

#ifndef BOOST_RE_CREGEX_HPP_INCLUDED
#define BOOST_RE_CREGEX_HPP_INCLUDED

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/regex/config.hpp>
#endif
#include <boost/regex/v5/match_flags.hpp>
#include <boost/regex/v5/error_type.hpp>

#ifndef BOOST_REGEX_STANDALONE
#if !defined(BOOST_REGEX_NO_LIB) && !defined(BOOST_REGEX_SOURCE) && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_regex
#  if defined(BOOST_REGEX_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  ifdef BOOST_REGEX_DIAG
#     define BOOST_LIB_DIAGNOSTIC
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#endif

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

/* include these defs only for POSIX compatablity */
#ifdef __cplusplus
namespace boost{
extern "C" {
#endif

#if defined(__cplusplus)
typedef std::ptrdiff_t regoff_t;
typedef std::size_t regsize_t;
#else
typedef ptrdiff_t regoff_t;
typedef size_t regsize_t;
#endif

typedef struct
{
   unsigned int re_magic;
#ifdef __cplusplus
   std::size_t  re_nsub;      /* number of parenthesized subexpressions */
#else
   size_t re_nsub; 
#endif
   const char*  re_endp;       /* end pointer for REG_PEND */
   void* guts;                /* none of your business :-) */
   match_flag_type eflags;        /* none of your business :-) */
} regex_tA;

#ifndef BOOST_NO_WREGEX
typedef struct
{
   unsigned int re_magic;
#ifdef __cplusplus
   std::size_t  re_nsub;         /* number of parenthesized subexpressions */
#else
   size_t re_nsub;
#endif
   const wchar_t* re_endp;       /* end pointer for REG_PEND */
   void* guts;                   /* none of your business :-) */
   match_flag_type eflags;           /* none of your business :-) */
} regex_tW;
#endif

typedef struct
{
   regoff_t rm_so;      /* start of match */
   regoff_t rm_eo;      /* end of match */
} regmatch_t;

/* regcomp() flags */
typedef enum{
   REG_BASIC = 0000,
   REG_EXTENDED = 0001,
   REG_ICASE = 0002,
   REG_NOSUB = 0004,
   REG_NEWLINE = 0010,
   REG_NOSPEC = 0020,
   REG_PEND = 0040,
   REG_DUMP = 0200,
   REG_NOCOLLATE = 0400,
   REG_ESCAPE_IN_LISTS = 01000,
   REG_NEWLINE_ALT = 02000,
   REG_PERLEX = 04000,

   REG_PERL = REG_EXTENDED | REG_NOCOLLATE | REG_ESCAPE_IN_LISTS | REG_PERLEX,
   REG_AWK = REG_EXTENDED | REG_ESCAPE_IN_LISTS,
   REG_GREP = REG_BASIC | REG_NEWLINE_ALT,
   REG_EGREP = REG_EXTENDED | REG_NEWLINE_ALT,

   REG_ASSERT = 15,
   REG_INVARG = 16,
   REG_ATOI = 255,   /* convert name to number (!) */
   REG_ITOA = 0400   /* convert number to name (!) */
} reg_comp_flags;

/* regexec() flags */
typedef enum{
   REG_NOTBOL =    00001,
   REG_NOTEOL =    00002,
   REG_STARTEND =  00004
} reg_exec_flags;

/*
 * POSIX error codes:
 */
typedef unsigned reg_error_t;
typedef reg_error_t reg_errcode_t;  /* backwards compatibility */

static const reg_error_t REG_NOERROR = 0;   /* Success.  */
static const reg_error_t REG_NOMATCH = 1;   /* Didn't find a match (for regexec).  */

  /* POSIX regcomp return error codes.  (In the order listed in the
     standard.)  */
static const reg_error_t REG_BADPAT = 2;    /* Invalid pattern.  */
static const reg_error_t REG_ECOLLATE = 3;  /* Undefined collating element.  */
static const reg_error_t REG_ECTYPE = 4;    /* Invalid character class name.  */
static const reg_error_t REG_EESCAPE = 5;   /* Trailing backslash.  */
static const reg_error_t REG_ESUBREG = 6;   /* Invalid back reference.  */
static const reg_error_t REG_EBRACK = 7;    /* Unmatched left bracket.  */
static const reg_error_t REG_EPAREN = 8;    /* Parenthesis imbalance.  */
static const reg_error_t REG_EBRACE = 9;    /* Unmatched \{.  */
static const reg_error_t REG_BADBR = 10;    /* Invalid contents of \{\}.  */
static const reg_error_t REG_ERANGE = 11;   /* Invalid range end.  */
static const reg_error_t REG_ESPACE = 12;   /* Ran out of memory.  */
static const reg_error_t REG_BADRPT = 13;   /* No preceding re for repetition op.  */
static const reg_error_t REG_EEND = 14;     /* unexpected end of expression */
static const reg_error_t REG_ESIZE = 15;    /* expression too big */
static const reg_error_t REG_ERPAREN = 8;   /* = REG_EPAREN : unmatched right parenthesis */
static const reg_error_t REG_EMPTY = 17;    /* empty expression */
static const reg_error_t REG_E_MEMORY = 15; /* = REG_ESIZE : out of memory */
static const reg_error_t REG_ECOMPLEXITY = 18; /* complexity too high */
static const reg_error_t REG_ESTACK = 19;   /* out of stack space */
static const reg_error_t REG_E_PERL = 20;   /* Perl (?...) error */
static const reg_error_t REG_E_UNKNOWN = 21; /* unknown error */
static const reg_error_t REG_ENOSYS = 21;   /* = REG_E_UNKNOWN : Reserved. */

BOOST_REGEX_DECL int BOOST_REGEX_CCALL regcompA(regex_tA*, const char*, int);
BOOST_REGEX_DECL regsize_t BOOST_REGEX_CCALL regerrorA(int, const regex_tA*, char*, regsize_t);
BOOST_REGEX_DECL int BOOST_REGEX_CCALL regexecA(const regex_tA*, const char*, regsize_t, regmatch_t*, int);
BOOST_REGEX_DECL void BOOST_REGEX_CCALL regfreeA(regex_tA*);

#ifndef BOOST_NO_WREGEX
BOOST_REGEX_DECL int BOOST_REGEX_CCALL regcompW(regex_tW*, const wchar_t*, int);
BOOST_REGEX_DECL regsize_t BOOST_REGEX_CCALL regerrorW(int, const regex_tW*, wchar_t*, regsize_t);
BOOST_REGEX_DECL int BOOST_REGEX_CCALL regexecW(const regex_tW*, const wchar_t*, regsize_t, regmatch_t*, int);
BOOST_REGEX_DECL void BOOST_REGEX_CCALL regfreeW(regex_tW*);
#endif

#ifdef UNICODE
#define regcomp regcompW
#define regerror regerrorW
#define regexec regexecW
#define regfree regfreeW
#define regex_t regex_tW
#else
#define regcomp regcompA
#define regerror regerrorA
#define regexec regexecA
#define regfree regfreeA
#define regex_t regex_tA
#endif

#ifdef __cplusplus
} /* extern "C" */
} /* namespace */
#endif

#endif /* include guard */


/* cregex.hpp
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
*/