//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  linux specific config options:

#define BOOST_PLATFORM "linux"

// make sure we have __GLIBC_PREREQ if available at all
#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

//
// <stdint.h> added to glibc 2.1.1
// We can only test for 2.1 though:
//
#if defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1)))
   // <stdint.h> defines int64_t unconditionally, but <sys/types.h> defines
   // int64_t only if __GNUC__.  Thus, assume a fully usable <stdint.h>
   // only when using GCC.  Update 2017: this appears not to be the case for
   // recent glibc releases, see bug report: https://svn.boost.org/trac/boost/ticket/13045
#  if defined(__GNUC__) || ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 5)))
#    define BOOST_HAS_STDINT_H
#  endif
#endif

#if defined(__LIBCOMO__)
   //
   // como on linux doesn't have std:: c functions:
   // NOTE: versions of libcomo prior to beta28 have octal version numbering,
   // e.g. version 25 is 21 (dec)
   //
#  if __LIBCOMO_VERSION__ <= 20
#    define BOOST_NO_STDC_NAMESPACE
#  endif

#  if __LIBCOMO_VERSION__ <= 21
#    define BOOST_NO_SWPRINTF
#  endif

#endif

//
// If glibc is past version 2 then we definitely have
// gettimeofday, earlier versions may or may not have it:
//
#if defined(__GLIBC__) && (__GLIBC__ >= 2)
#  define BOOST_HAS_GETTIMEOFDAY
#endif

#ifdef __USE_POSIX199309
#  define BOOST_HAS_NANOSLEEP
#endif

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
// __GLIBC_PREREQ is available since 2.1.2

   // swprintf is available since glibc 2.2.0
#  if !__GLIBC_PREREQ(2,2) || (!defined(__USE_ISOC99) && !defined(__USE_UNIX98))
#    define BOOST_NO_SWPRINTF
#  endif
#else
#  define BOOST_NO_SWPRINTF
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>
#if defined(__USE_GNU) && !defined(__ANDROID__) && !defined(ANDROID)
#define BOOST_HAS_PTHREAD_YIELD
#endif

#ifndef __GNUC__
//
// if the compiler is not gcc we still need to be able to parse
// the GNU system headers, some of which (mainly <stdint.h>)
// use GNU specific extensions:
//
#  ifndef __extension__
#     define __extension__
#  endif
#  ifndef __const__
#     define __const__ const
#  endif
#  ifndef __volatile__
#     define __volatile__ volatile
#  endif
#  ifndef __signed__
#     define __signed__ signed
#  endif
#  ifndef __typeof__
#     define __typeof__ typeof
#  endif
#  ifndef __inline__
#     define __inline__ inline
#  endif
#endif



/* linux.hpp
xhefyOkizRAqWKV2n27gdFFmdf6MbO12vz18jaEVFtINOz7nHsc33AwPzLqduxAzlC3ODHdAt/PxP87l2OPN8JZgJesOX8HnKMEMVQXbMOytEG4vaN5s8lgqCK2MbvK31WghVJ/O9vbHrotRbIl0LyY7ELymNPfJiWq9kFG9UH5JajnJpHKmoO0U8utmf1KRjznGDGlCup/TbpzmczTWDHbBzj0+EMb1OS73/MLGUb2QSd9+jFPrhUyql3S078mcH6r92qSVL5dlvBlOCpb/VIMqfD1MUMtCJpUlx8D8J5rhc8HOHCzB67Zhkhm6C9Z+X3Rzjg+tm2DnJtsec1kmGZQFzZtNrheYbObvBp03xQW7fjzJ528ytQkyqU1MpvzIpPjezN2C0D5nk2O3TaGxKVndaxXLcDq0vII9+HDdD1wvU3LPL3UKxU4mrddHa0XXrbMOAo7W1sfs09X2Qia1l2y0tmSYET3/0bU5w8zf/znvKJ9+mPozl3Mm3QPIbrX6ivtkx0yKnaxrnYRRHAPaZcHu3vkb10vGWzQOIYvatGIcl9PFXutin8n9yywaT5ANSf7bEI5hNt4bBTs4rEwBbhNouwU7P7F5E47hbboHkK0bX8DCdf2OGay6yftyyEb791C7drGvwz75k/tktFKCfVyg7x5un2gWwVZeGsP3DngXxwWCBZonvcaxvyunC189cxu3QRdbVqLURj63aMVNug28t28YxzAHx7SCDbPUWMH5zaPnKrLS5Uau5vqcR22XbKaSyePIlHlyW5qTd04itxe0LkJ+vX9z8LOTLVV9puT4xv79HS6Liw3Mk2csx+5iad3GduTY0UYJlnX/JreznFR6riIbkC+ztP5dAX4LLVi9oXWacZ2hlRJiWNrhfT6m/0Js14JZbp29wrEvcmkvX5YI5TboYtfqmC9xG3SxjvlndeKyLMq9nWUvktvEmq8/mMWxu5h960B+toDFcn49pw7l73N8Fru0s5PrCnHsLhae1JD7ENtiuU2s+nmSg+sarYVgwV29rnGdofmxuXyPgJZXqOsKN1aP4RiWmtXvmcn+ZrqQwW0CzV+w476NP+f80GaSOQdK0e98qj8HpKnXAxmtdafrIU2tMzJaZ0zXg4ttvjGqEecnmdyHpLtYl5JLT3HsstGcMbUJF7udOGIz90uSyd9sZUsm93U5aK0F25rTjcsZ9Dcz5BNsddHoMK5rF3tvb+E5XGcudn1O9m6uMxfbFzK7D9eZi7Ueeuom15mLVfVpdY7rzMVee7KpLdeZiyVvGeLgOkMLEOP76u/6XNcyen4nKzO55hCul2X6GDrUGe+az/RvqJbnbhlobdjkMa3PCpx/sej2xoWx67mcH5rVuXuyByN/f4vPw0f4XCyYeXvFI5wO7VvBDgy8cJ/bxCoztBSs4+j+3/M1vdoMEYKNvr/vCceA5s3m8v0tWhk2efySg9ZXsGUjw8pxDGvUOVWO3fvDflyW9Wbe58vZ+LYdjOAYUtEWCTZjUGQBPkcbzFDFpNtr5X24PjM/M0N9wZL2fzed+wL8VOA1i24BhVcc5HJuVs8fmXT+MjfTuIfs17Vp5zl2FxvTKGcs961bzPR+hWKYnO7D+aHdE+zMkDi9f9mKz5SCfbok60tuS1+aoadgdybXrsvX35dyujFLG/OeCLBNTreoZzt+ZnagebO5zKWjlWGTz3sGWmPBQuwtL3F+2/E9gkm3UgsPBXJ8O8wQJ6S72vOTs1xnX5lhtWDf7C3xKdc1Wg/BovttKcn1+bUZLrI5n0230HdnIQkpO828D0g4JCXdu9lnl2a2XWZYKZjSd9g9zWA3tQkytU2oFoZ20qzbzDKrbvIx95s=
*/