/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * Defines preprocessor symbols expanding to the names of functions in the 
 * C runtime library used to access file descriptors and to the type used
 * to store file offsets for seeking.
 * 
 * File:        boost/iostreams/detail/config/rtl.hpp
 * Date:        Wed Dec 26 11:58:11 MST 2007
 * 
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>

// Handle open, close, read, and write
#ifdef __BORLANDC__
# define BOOST_IOSTREAMS_RTL(x) BOOST_JOIN(_rtl_, x)
#elif defined BOOST_IOSTREAMS_WINDOWS
# define BOOST_IOSTREAMS_RTL(x) BOOST_JOIN(_, x)
#else
# define BOOST_IOSTREAMS_RTL(x) ::x  // Distinguish from member function named x
#endif
#define BOOST_IOSTREAMS_FD_OPEN   BOOST_IOSTREAMS_RTL(open)
#define BOOST_IOSTREAMS_FD_CLOSE  BOOST_IOSTREAMS_RTL(close)
#define BOOST_IOSTREAMS_FD_READ   BOOST_IOSTREAMS_RTL(read)
#define BOOST_IOSTREAMS_FD_WRITE  BOOST_IOSTREAMS_RTL(write)

// Handle lseek, off_t, ftruncate, and stat
#ifdef BOOST_IOSTREAMS_WINDOWS
# if defined(BOOST_MSVC) || defined(__MSVCRT__) // MSVC, MinGW
#  define BOOST_IOSTREAMS_FD_SEEK    _lseeki64
#  define BOOST_IOSTREAMS_FD_OFFSET  __int64
# else                                          // Borland, Metrowerks, ...
#  define BOOST_IOSTREAMS_FD_SEEK    lseek  
#  define BOOST_IOSTREAMS_FD_OFFSET  long
# endif
#else // Non-windows
# if defined(_LARGEFILE64_SOURCE) && !defined(__APPLE__) && \
         (!defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS != 64) || \
     defined(_AIX) && !defined(_LARGE_FILES) || \
     defined(BOOST_IOSTREAMS_HAS_LARGE_FILE_EXTENSIONS)
     /**/

    /* Systems with transitional extensions for large file support */

#  define BOOST_IOSTREAMS_FD_SEEK      lseek64
#  define BOOST_IOSTREAMS_FD_TRUNCATE  ftruncate64
#  define BOOST_IOSTREAMS_FD_MMAP      mmap64
#  define BOOST_IOSTREAMS_FD_STAT      stat64
#  define BOOST_IOSTREAMS_FD_FSTAT     fstat64
#  define BOOST_IOSTREAMS_FD_OFFSET    off64_t
# else
#  define BOOST_IOSTREAMS_FD_SEEK      lseek
#  define BOOST_IOSTREAMS_FD_TRUNCATE  ftruncate
#  define BOOST_IOSTREAMS_FD_MMAP      mmap
#  define BOOST_IOSTREAMS_FD_STAT      stat
#  define BOOST_IOSTREAMS_FD_FSTAT     fstat
#  define BOOST_IOSTREAMS_FD_OFFSET    off_t
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED

/* rtl.hpp
zn0m7pOMOqfv1c9IV8ah53HTbfe+pvZJ31tH14f0UZSufiNuw426cEDcEq3wWpR2DcPmp+Wv1GlKThX3HCMP955jlc6G9GiuJN92zY8nH+dMKXDVNV/aGWXrIkrQB14DL8N/8XSdz5xVpOsu0e9LcPc56r7GSr+flHv+QMpbMDpoZsp3wnWPQVVdqfLjEXGf7GtkncS+sKYmfSAMcz+psdKHB8R9uq8dUliMMegFYUQdH+qxzl3iZwraUY+9Y36jjhCOu6+g67P7xG0iI1S/qc/CveYxoD4rc4acWelh/DaPpy6vZ66U+1bqs8Zqz8RObVbuf5YtL62vW8V/aLy7i3CjjafK6zaeQ0IoP2vyO0nLUMvPvxSrJfo1EZnrcZQeMzXHTMJMxlyk3NSYCBMqHxkex0SNVVlBHyPa4lrQ2Rar8uLsP8j9SVHGLsmVj13k2i49VhF5Rj0j7Pvp5vMrk9R5iCy/sOrDEfBS7i2dqcvejLzC7PRxWdkDM7My0kep02cb6rqsvFx2UDpzj9zbzz+GmO4jHz6FzX1+a4avl3WXb60+b+6xi/GHu6Nsqnh9qtway7rWmTvFbyOrudK5z2fZ9udJW5y1DHOfecyh42is+580I3YrsrBwyoLCch1+XcJrSn7jz5KyIW72Le+KWzunPi8mA7Qu9pK0zbS6MEc4HhOeK7PU2La5qid84m8HrXqCNQ1TiqF/IPr1tcTxjNUDPa5riZ5qM7ppiDcohv/e5GjD46PX8VpvXf1CuV7LoM+NqcNLuLZG6vCsBfNyx9AGhK5fw/UNcj19+MBRE7LGpKfp69vkelr60Ezkq3Tx1ZkhXXy/ccheW9JJndk8ZO/msvedVdH/CJf7VJd9rcv/cy731132b7W9YruU0VKfv8JVch+z2G6XZuuyUYAgskOtoWXsgzSBD4r/081t0Wx3v0JC0zq+UtzPMeqx816pRFR721iVw1JxH2XPYeKnlqe+QK0Y+gKFlu4LiNxODX+fQ507iF+Rax7mWrsuz6/w/SFPZ9Rwj2t+IOo7Ju23ofar9drY/ir/au5E9wNMbSx+3e09pd38rgm/lb+7mZAf/d1NPXEbX+m7mztifHej38novFPjVSXLxnoMGzlGTFJjYGcblqzbMJFBhT77dnWu1b8YXJyhuNwuM/kR354yzrm8/f0PP+wTv9sSwnXkE2KfGJ9OjIN8w6xbfGt80s/iatxc221R/DnWh/4OcUN8hEGaw/EdSahQ1qLokpzJSrz3iPvrCeGyd5fKp3Bf6Lv5tr2Z+K9liENfM+qgOlOXeB4QP8/reLa64mm0wLbXEf+Jhnjkmll35Z4gcTwt7jt1HA+L/UQdR2uJY6Bui88QOdZSY9PIOOWasQyoM3yJc7+4b+GeUJx7xT4j4QRrdILtJ9kQbrIr3FWddB9Uj3tPlGcbEd/Vyoizw9lPXG/JPXcklJexmfnOc9pL5oq7P9vXPbqucK90+EUPBuhx1feSz6frvvxouS8lvrd1t//+uGlahm3mSFnF7gz/HC3Tr8V9cGjejmc+2bYji/I+7Nx5tnbwh+7DrJon70x89BsY+Tew5litfCIHHX6nuCSrYYX3Im2VvGdI+FviB3Ky+3prv/+uuNutcfG1rKnx9fETCv8lCSPP/yQ9ky8tPzOj7a0Ef08r0x/qRzVwyKm2VRNtrx3XKW4wMuR+hxvPINe1DEX/Buh52z7yLOcl1PbVt8r9FM4pGFDetp00X+m5ivdksZ9AGMq/KjvcoudFhoh8mtCzS9Rjb7/oco7Wl64S90bfMGQnfrR+17XC6SgSP1ZCOn24262ceJnvJY+6y/UMh15NtfVKz+F8Or98nLIP/7Y=
*/