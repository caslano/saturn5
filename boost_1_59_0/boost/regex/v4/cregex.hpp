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
#include <boost/regex/v4/match_flags.hpp>
#include <boost/regex/v4/error_type.hpp>

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

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

/* include these defs only for POSIX compatablity */
#ifdef __cplusplus
namespace boost{
extern "C" {
#endif

#if defined(__cplusplus) && !defined(BOOST_NO_STDC_NAMESPACE)
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

#ifdef __cplusplus
} /* extern "C" */
} /* namespace */
#endif

#endif /* include guard */











/* cregex.hpp
D8kiPl3wDYDiOQBddAKjXrsZcho/Y7+UBojJvAld5osfuxNlmmRr4L+kU6WEegDc0BdnTSQQnW+IdujL/sJLgKiLsHbs10CSZrxqEmD83NswGGdkaiKjfITRVili7NLA0kpwKnMidQkefRQdIEyLAHeyTuBcyTcAlecAdSEHfYIW5shqooz8UNWAqnMmdTkvfiodKE3z13pA2KCqCwh2KNzQLAvm1HUtThBuGMv+lmUgXNkufpbmuG6g12CZZ3hrUq6BLhyQLXP0dckiLQakJeF5gR408Xvx0AHXTYca4U5zPHPirYGmC0OY9biL3K6SQ8JwftlJX8IE2kyQTotCc4LOe6AaIB7mhGeF2Hm5L37bTbhbYqF90k7AV/mGerTRHWCcTMv+posid1gbQDmSn/28i/h3XByAL/P0dozRHWicYMvbk14lIncCG460jykf/ZHnc91TmhgArXP0dwoYzrgurhVAtKXReyhNQF0JL/6q8z53FhzANsWEe8zIo8JuGuF7zk93vemxKO84L0QZ7ziP9VR7LBcAn+cqdyQd2F3psIGtcwh3KhygOyKFIkQOnMv+rnMjCCeJz36uCz//PIy/62I8wkl6tP/rXFn3FOOi/+v8yD9/CXBb+u2ZLssCzMMn2tc7T3/Hj/HMwwVXAeQ6J2IX9+IHt+hzh8ABzCMh2jd69veNLfrjD6naP3ZBxC7sxU92weeO/B8r/a/tIv0dOsZzvlBOMccd+wY47L9nEe0aLLdUcA/KaRYgvEuMsDduTJIJwStdxb9WDq4tE9avdoF7j/esiZb4AaPZ77cIaO8yyYs43lce7g2UWFfSCG4btkecE1biiFrDGbzUoOJXhOB2rv58CjebBaiUbcO+S2qnULMfgePPTXHg3qcT6xsANghvkeGeKNMDcFa6OcEb/XJgYRPClij3nu856h1ShzO+DKET/FfUBWJ6b+cmReI304XBybOHTcI4mtMVycmny9aU1+5PqtEDMzYw3MJ+ahouF6CPIJxfKLk7eikyBoSPaGrX1Neh1B1YBZhvEeod6Qb0jxT33t9rIN98zX5d89/eNNLuY5g3F6cz6SzMc7o3MOy//efxOKDhFb+0M9EVIEnKcGVlgXjKjLzx4RUmPhSJ4MyPjulYhSY+5InmFLCVRh0bQDNycIGjFdi8E0dszshZ5Sw/RImHy9x7EBbLswzhSqH96hU2UiSNy/x2MRlvkVIn/2YVLuYL1azypeo9L+cNW4Zwhc8+kIu/bgkX77gyjRcAd0bN765ZJssIdvEW70CltM6sbULLuP3oUtiAhktSBXFqzpyf187O4UVxxRa8f2tFJiDF5Vr9winkkROKXqZVxRo4qFXwyS0I0ipU/M0rwKRUnckhx+Wo9Uo2bOXEUjiATSoJ9WI4QE8q5I0hxxWd9Xo2wFHLuPNkrsGglvHt0jkAUcsN9eoxjJXGHJTBUsqi9co3gC6WfebyYP2NL8DNlFKzKuIcmiGZyjerIcvlQvslmidK4iia0Zkqgboh3xM5wHMq/k0Ey4N60RjuKQIWy1J1Ms1+qMtANXKtAc8XeGbKr34szmcCIKXl9ZMoWVVOm/8GjeyzDII9xd97LSir9SxZ8n1UauR30MMAdxFi0Th+QB3JGXEdk11dlIIpe8AnP56KoPTfnw4xaJBHAyDPE+QCn9UR1YLkDL5pYuRY8JFBEOY4jBGmAO+ANDgr4VaAHeWANXigEdg7p3sGFpFuIv0DI3uIdyC4PscAdJAhQoxgWrgd1wAEeDx4I7wJ4RR/WiQd3L5Q0Du4PDgUvIyAWpgdwwA5eCQ8KiEVf5hIGH+YcJigWgR8bJxfXFhcUFxUXEBcRFxIXEycf1x4XHBcdN+HEcJ7xuvqtQBPP/HnlRzqrWZk0rAvUE30pNgbnkYHID4UvrOTsYD/k/NCewL9s9Z4TkVh4OSD+bvDFk2NfatzJxbxURWOqaqnR+ak8AV2j03q7oGLy/u4efRcQjJs7ez5zULNgqpb9A2LaEf75O2dy7r2kBGVY7vm6qda0N/tbBzPSt60DQWd+ExleKnpRY0rndxCaUqxospLh6TSVc3q8xKc2O7K6fkUnRszYXYdXAqjUCKq4DBQXPwQ1NzdSMT7s6JMKl6FmztOjW8b2nJ+/Zl7SmqUVWkbeTSJkWsOOMsw2SLhRY55qmp+RdL5GwTH9O3JixrlsoX54zsOzczGsJUCCqeq6tVDvJWdGdTWyQ39V7vsscKtm1bXjW8dU1kOWmDqBcSMzpV2oMDBD9o50MLJ87OH0sgdrWOtU2jJJTld60qoxST2zqudHYbS3sUbfNDUxu5KJHS1K58Vr3megVPh1tkDl2cZ7oRzEsJyO4OiLn/S5pPm5eascBpYLXTOKx2DqxcPd4Q0Ue1rld7t2BVH0BBauguDufD+rPRlVMTdI7sW1zcgV1X3bB96wqwyzswsFzRMQfvCfgMmdIthEIMOuu40Uinaggy65yaON7sEjdbege3tZdSlqjLWGDizNY65kuTRY3DMx7lz4pzj+3FXoPWwm4EytW+d0G5GqzDLK+6ZlXHFJX/R/DMIpxbXB2QMX79zizaZp+GhInxyIermoH4esstnziZgKxc2utivDWM9nXAcO1sB75X19SDHdU1sKweQxYS6Ztvq+hBtVVdXAweXZo6qGxtbyoi6TywkZw3XkFnu6wAlJ89vbNjc3oHLGyYrJ7fra1ibuC6XlqNo2BV0/AjIVjRr08sI8dO3A9TrVRoh13rxtMXEdaQz8+t1vdOlts6tamwyNMa8ZdtbC1d2kjWMaZ+iWEsgxd4ta6fVtkGVsvLFGyfp/NElPhkYn9JJ0aptnNjNS9aOKx7dsmmWDe0aVM9Lj4CZUQ7d7ToHAzADlL9CSNOKMzvwkShqOvnEb9Da1iy12B7TL9jfKmK6q5xY1iqtk9E04LlVBZoCN0jyPsYgrTyHqkULl1aNG5zy2rSZ7C0dGCF2myzOnCQa7PS6Ujq1mEiAI+G26ssx0bBotzj0ZwbyKy6uDV4j1x0urGmebT4B73BVwXMTjco10cHT+5Caf/zX8WlgTPcdAmQuWXxME7jBYdNk/3IqxuoqGkVCDK6yN06kebj5VRdXXfnhM52YgDo09NcAH1ihm5wex6IFYL3xyKhgXO+03JFrGA6XBcWGb3b3LN5o8w4HsTQ1u2Pz4EoirMDgf5DnVNRSZRqRvdmUUEvsOMznQWTHoZ0Bu4H6U5tKtOpvwcyX5G4b37lN9W+XV67qwWrh/WJ4qr5yPJm2ru5XP7aAQSJ4U5aAXOmGtjgNJxZUG880apC+FLjIH95tbs6tbmnClzNTTjyks3mGtyRKPUkBwtS71Re2fgx2qF82h3urG75Wn4IEpavd+Jh5Btl+uxExMjIS5aBEmQafNQZ8VMU9qeOfNwosmOJ32/HWncmLBq5a3lJfunS0jTcoA6+kVxPUDY241odXt/b5P9X9rJ/tuYSne7QJndTZ9BFAX36Td1pcFM+m6q9BH2DUuyr1m++LENc50DU2kfuJJyYjOck1OAjhbOHINjeb+3Qsu6ucxaA2MVFFD0ZCmifPIU+5ns7g5DwkSKR2Dt9UOHx83bjUdjO6FVa0grSQu1kzZIxXwCpZP8iQTCBdRrEqMwlw0uZ5q7cXkHuNUk3h7NKvH02RQ//FcM3ETg8PHV7+bSePTy6JptvTBzJuSVkOiVYoHsS2EVWDae/MS8YpqzoZlFXjRe1EUnfpt73j3CChgQxcNmOJhTO0a4QsG6GuWN43xf6rAdPjQ1o1OP7ZXeeu/zxqEhPf5DmYlAGEfJFqBPaNaA14fw/BTkcP5pAAhHlHMXxC70OTzmQpbS1jsg2YehWGoIJfVVqo7iw4qLTZWOa5luxs6Pl2M50J6lsAS5O9qvcS3amnzp1fGpRVNZXVJ55f5Src2g1zuUXbMAetpeceFQvgKE9NozQ/j0k3o9LoFnTtqV+dadFn9YKqOhbXEK6479S2MXQdxw/O6RB0BnQMyuzPpOLY16PvEpocsc5tjzs1OZvJpjgffwgjsrUFQctmd+US49pxN0J6FXvIE3DyFtQxsuEwA6E5EwzQSAx9sATVSk/JueQ4JwGbY97o4DgazbUFlnlcJknolVBfzD2/5fqhsa2T2ggiapK7Oy8+pL60tLwtbkV0Vm3Zuu/ZobVx8FocSQLfaKLbTn98bd78aXfnxL6x7r6ssnr96vQJhJ7keZ3JRDkJt8hdlNq0l3RkuTRkceBqycMpfvrSuL1va3GkJS2F2XG9BkGB/UPRWRuISa6J17wZuUMxKC5iBcizANo5DZre5LFNh7iRxRXNlLBMF/Ws4qhtrdg+rqZqY8GwqrIE4qTSIO/pCoTWApJtkrsHZilKgGvfFOHK5tOqyyluK4Di1VVCOeighzEo76D/apXI+PdVnH4WqDZhIz15aSJIxbErX7CThaP5sEssvLNfEFwBeLlAYGMD7WIOYnMAKyTihoanx98VWYsc8VPMbTFmpQpCOqOCfYNk8HbwcM7LcMUp0d6CWwIZm2fHFF9c0DNUKln47l48tqWjsx6OsZbeCz5KazaU8CqnBG7VuqmzA1taemhOr5KQRbEwOqm6JV3MWjC6fMcKmRvHBGuFvTOrB9ZtkkwPcnP/SRkY0QwOybE9MTZye3MzS7quDdvHoKY5nUL6WZoZVFM5sXlCS58QNXDapKLWmMJQWbF7fEPO2rIBA2a5pAQyEMGUd+FkZUIQR+3D2t8etpPBdZlzjcMOPrbED8LiWg3CNbSWrFrCSraMfpVFOc1yUj6cb/wZNLM9ZukvRqzPYF1Dg3lx/o5VGXNGGyDENOX0MUzIRZ4OpZDjiVtu47/Xowcy5mrHZh2/syt954g2MpWsGw+SktgQ7pxNxJnbrSxZ6HkpFSTrBUnyiMnuEWBzUX+AVL8B9xSBpXCNkWIoW6dG94YnLpPm0BsWuLvm2dFngmsEGppVgkUnaqT0s0Vh9Gfh0KFzq4FmmpcUfzrdCn/o7ujs9hVwzPM8xCe2l62YxnXNig1aAhj3VbmTXYmKvu9D/VkHA5pFv7YRTuXtDYXjJ6fdrusSsFV4U7TmXxbCTfVzDU5pZtRNizXbzPBpc/rZ6oL0DUmhFZQpQUGIQ/qaQ1oR5mJU4w3lGRZfMFUL+pLGPScKFhMf0qeM7dp6z81s7a+UMNRHA4kVVubkfIQ0yK1RfI39Aibq37muocGM+X1fmD130AN8jxWAnrvJum8BS8sxYzw4INkomI2dFVQO/jdJzalymVeRUSNvunvkcyaU1pGdHQrOTV/3835KnXt4Wt1Kj7IBrWhpjOaD7mjtDQhS+cfrphSpJYhJ5vKCfGbIFFyVpaGqCyvlEg8D87J/KtAv0nH5qJxVKtuj1Cc6PNZkKeuXa20qGJYGwxAIia5Ip9KXjQhDLi46lEseSiwUrYurJyIaY1BKesI9kdiDpUcoEu+XShwci9dFLKTFSK/qimFROyFG2jqm9LiY75C/VutIMar6s+qS0/SEJjMt1EAupZdDRLSkvFnVNkuUTTSVtQOry3tmRqJsrPPKJCxR+Q+jSko2OjQSwzRUmf5eAKE9q8mFbExYPIl4a7snOjtLq2s3J7+1PUIQRmgDiPTj/yAG+jxbiOpQ+dSaZF+n2cn40tqbhQ73oZZ3W8+R9KKiXfpzF1Vb495/vNFMS9nizUST2+8bLV3rPxZNRDO2dkJlurmPBWbkDmrNhltUl0ix99QFVuQBzDkhJQDbgm3Q3yDfvYbRhHoXFkarOn6BTrZszC/f3PZJZaZF2AJV8YvK6tMvae5HgH4Zu7RJiDqq/R48DWV53EO2b88LvgX1P1W2KKHvWcELRoPMYlhMhkMERtgfYkaP9OHCB7xHtB76vwplv+yghvYf9suLRdY+DAje3ji8aVzjgDGa8aB92VC3UojKtjduj7uQU6d2OH9tjCJvXwl/yzuDppYO4rgJTjFWNrtyvPGMzWjyGJw6sy3PV15HZ0+91rlhX2Zxx7BM5zkkL4/vNAXtnr10BEXrdYqCODxmuj2LT75tYtyvYkIHtyz3Reu/hOouRe1aMnhs49h3BKKFCAaJbmpvX83a9WPq+FB/ARFiDkjLOL0vXWxxIWpIuSEgOY7og/7LiP9Z1T28fY12imc1ZZY0SJSAUDktZwvlptlW0Rilq3YhjVLy4WES3oakYlNBRxcI3Dn/x7N1QsumkkCZxNE4OZrusKGipqdr3MSPmohav3RXpT63CZQVL6s4eorJacMTEFH7wtCDxn03xBTRDrXJUGi7g6+jr3l4B5UJC9YH8cQXZblg+Uba/xDOc/4K7qpw+cZFiuwE0E2+hdBLEboXclcGKPOIgydYYzvG+TKr+kp2yD+wD1i4vXD7ck7rT+ktU+hqtXrYvZIdHb29PH1grnX+0Or2wK+NMEfzog/tuYGp4anIaFtJVeo3e9Wiuev+Vsf8uG5vcBKFBHTKShE1zK5b1HmVT+eq7cDFc7COlB1EczSzlPxUY9pRMzJYQ5oX6dO9uGszZHQqrgoy7wQ7iz6jSwwnY/7qMD5aIgOs9JisVlHBylg22L7Q51szadwI/o7znaODWPjhvX0tZ9m9/SUwOp2cTO76KQunxqPj43ojAHOBhoRQAEQbPomJpXbiupGVAYbpWL5MZm1N3ydeT2TQzrNqCOleizzRu2+yImJyNvl/loAnc5vbHrKlfNA/NqPdJxf5Xf3hSUrq8Eo2dqX4Hj4UFGcylrQZlznQufLddU1IGkY2gSpL8ypyC/fyai2DVDzX+KIDO6GM+YF+DutjGfnEX+fBWpyC8pKKrfXj64jfW/uxBGyl3r+fvIj1eu3/OUYO12RR05V4A2j7ZaxM31dJ1t9vFOjgwrf/9HgoP3xoKu2B6D0umy1TEaEIlUcqZMlzhhbBFA4E0KOZhmVGEUS86T0OBPlaDSESDzFf1rx9R0ell+fPCdtJQLnrEKkITQW3PgpdnGiYaILkAJrhJ07isFXnMJtok+UCWVMoRqA5aHaVKyKDbHNKsmntLEqwR583TgoPo1wO8o8ilbIe6V+xYd1mpzMfEh0K3HvuakWLeiI2EN9vDPK6njHZLvU7gtb+Ob+XzfUF/QJKOjsUspjunRmQWxBEFh+Tpf0r4wcY0sp4DRvwyeYWBoTnMTLPpgUpLxhrARp2k2ZzpVROO9Je93c4HbylyE2SFYLy9b1rMcWaoVgZoD0d1USk7jC+ciuVlj98RdjNfd6hz3jkq7o95k/nnw8fVfYKuZEhoVTeRcFUuxxqZYWEqBQySchyaGp0ZMzRE/YOm7WnUBouUtyuwqhNncjkqi1FmmgNwMMuhWBgppT6Kzz5YiGp4ymE2gl5HaIQbQcjqwYGNaNj/UYjOMPQc3bZLFhNIp0rAzldGR01LuNLCsKTLeHj+saxIevBSftVkdVijusPra/Hu2mAUOPQo5dYb7RinFwYyz6hqcZxcQATa++T9uZt/HyXOxmr4cpkFiEyC1pmfkQDxJNCOVugLT4EOQAgc3o/Adg/2dEF9mjBbhL3iW70ObOo3++A4503TpBqDG8r2L8489dtXbEm9A459kJReP0Hdbz8WhV8Zhez4PDplFcCQ3rHzcRzs3Xq
*/