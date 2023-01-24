//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

//  SGI Irix specific config options:

#define BOOST_PLATFORM "SGI Irix"

#define BOOST_NO_SWPRINTF 
//
// these are not auto detected by POSIX feature tests:
//
#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#ifdef __GNUC__
   // GNU C on IRIX does not support threads (checked up to gcc 3.3)
#  define BOOST_DISABLE_THREADS
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>




/* irix.hpp
eiQrysOM/jrYQDhWdInlCTHWxgexogeOgv+PtWGuM0/mYe3V46yNf+JgGGJZuLuYkvsos3BxMJPT/ltPR1nJRszkgjtMt4awki8eJMew7gMP1sndLEUbWOHD/90mRcxJGmC1fbBXk1lzKPbfdcHKLmFRrsxyG4UZ/vnfjnjA2kBnmYKFHWKtdNbiXDygBPSM6ZZ21mqsYQ2xNIvwCwd6QW4xOTEtY/KpxNKjjCXn3YMwjSWXEeu6OMOsrZrPVLPyQC0Ii9BhQ3O4OlTH8c2wIYaXaCLmQRcuribUXYTqRG6Pf80neJDTyOG+UUhHzMkGIXHsIba0IBpfWTVejz+NHDIJykUWEIFf3QsNY3UIIqf2SOiWt0LDzOeLhJ2vWjGbAfvSt8AYcQNZAgWOsY9e3HPWgc5C4h9mk365iGESSbOHBmAoTRMwBiJ1kUBxZUjFJa5780J19uOsJwmkzv9BR6yDrSdpCi5UDQIf8e14b9DWCehs562moU2Uh253gPgtVAZYSR84zUb+HDn8ONQBEi1LIFcehuqgV+qgkX72M3rgRNBCWioJx7mCWPzuPQDTVdAHN5fP3S4VQwCl2YoBfA0eymODocMwICh3E9zcXJxA3Q7JQHoTu9OCwtK+9mryrqHj9r8TN4qqaXi/AZj2L7tPi/blAHJanfIAjD5Mu7262BZsOGgfk2g1SWgueKsNr/WcADCc5ovIo/P4
*/