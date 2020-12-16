//  (C) Copyright Yuriy Krasnoschek 2009. 
//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  symbian specific config options:


#define BOOST_PLATFORM "Symbian"
#define BOOST_SYMBIAN 1


#if defined(__S60_3X__)
// Open C / C++ plugin was introdused in this SDK, earlier versions don't have CRT / STL
#  define BOOST_S60_3rd_EDITION_FP2_OR_LATER_SDK
// make sure we have __GLIBC_PREREQ if available at all
#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif// boilerplate code:
#  define BOOST_HAS_UNISTD_H
#  include <boost/config/detail/posix_features.hpp>
// S60 SDK defines _POSIX_VERSION as POSIX.1
#  ifndef BOOST_HAS_STDINT_H
#    define BOOST_HAS_STDINT_H
#  endif
#  ifndef BOOST_HAS_GETTIMEOFDAY
#    define BOOST_HAS_GETTIMEOFDAY
#  endif
#  ifndef BOOST_HAS_DIRENT_H
#    define BOOST_HAS_DIRENT_H
#  endif
#  ifndef BOOST_HAS_SIGACTION
#    define BOOST_HAS_SIGACTION
#  endif
#  ifndef BOOST_HAS_PTHREADS
#    define BOOST_HAS_PTHREADS
#  endif
#  ifndef BOOST_HAS_NANOSLEEP
#    define BOOST_HAS_NANOSLEEP
#  endif
#  ifndef BOOST_HAS_SCHED_YIELD
#    define BOOST_HAS_SCHED_YIELD
#  endif
#  ifndef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#    define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  endif
#  ifndef BOOST_HAS_LOG1P
#    define BOOST_HAS_LOG1P
#  endif
#  ifndef BOOST_HAS_EXPM1
#    define BOOST_HAS_EXPM1
#  endif
#  ifndef BOOST_POSIX_API
#    define BOOST_POSIX_API
#  endif
// endianess support
#  include <sys/endian.h>
// Symbian SDK provides _BYTE_ORDER instead of __BYTE_ORDER
#  ifndef __LITTLE_ENDIAN
#    ifdef _LITTLE_ENDIAN
#      define __LITTLE_ENDIAN _LITTLE_ENDIAN
#    else
#      define __LITTLE_ENDIAN 1234
#    endif
#  endif
#  ifndef __BIG_ENDIAN
#    ifdef _BIG_ENDIAN
#      define __BIG_ENDIAN _BIG_ENDIAN
#    else
#      define __BIG_ENDIAN 4321
#    endif
#  endif
#  ifndef __BYTE_ORDER
#    define __BYTE_ORDER __LITTLE_ENDIAN // Symbian is LE
#  endif
// Known limitations
#  define BOOST_ASIO_DISABLE_SERIAL_PORT
#  define BOOST_DATE_TIME_NO_LOCALE
#  define BOOST_NO_STD_WSTRING
#  define BOOST_EXCEPTION_DISABLE
#  define BOOST_NO_EXCEPTIONS

#else // TODO: More platform support e.g. UIQ
#  error "Unsuppoted Symbian SDK"
#endif

#if defined(__WINSCW__) && !defined(BOOST_DISABLE_WIN32)
#  define BOOST_DISABLE_WIN32 // winscw defines WIN32 macro
#endif



/* symbian.hpp
Y0JFL2gvHPNc17yR2rqS9FpevI7zPbBHlg/dcorXcqC1IUuFpKRTpd9fz2s5auduGbkagE8dL17H6Zzs2F28SGl+p49Whcx5Q6n0+rZK/K4crRLZQmwjp/IW6KRZloGBzUu995M92LhlLFloClpjskX4XjskoFtjfj+Npu0RshjfQYt7hKTU9+I9QpZgvOoeIfRusIEX7wOylPYB4feizb3gvEW3Xx7emsTvN1t7wR7B9lf/WZuDTw7r6MX7gKThOzd1HxB6z9XZC0b5qfY3fA9UZ05cMapPfEbw4t8SWQYJjuUL+vjyWofheB7Muo35tuV5OqbdFuvFc0HLsf341WrYULNAtHKC6esLkpIcaE3IVmAdXlxQpJZmmWihgtW59dldfrcU5wWlBDv7W/FZmoWhTRCsnu9PizWDeC9oKtibfl+YNQuKz/2YDrSVgrXbsiWMy5LgBf8U7Njmyf/QLMXhBa0FmzNlG5XFHp+NNozsfbz+u+4p76VZ2Cgv2CjYztSLyzQLTKTrjyz5bFZ+zVLRLIKp88mqpaPZBYss5zVHM/8kLwgw6faF/Z2xnC7ZC/7F111HOXV0AQC/WYktEmxxCK4LgeIaXAvBHQLL4rCBhcUKBClSLMWdFLeWFJcFQnEPLc5XGlxbAsX1uz2Zue9mz8n7C3J+587MnZn33szL25flzMxZ+w6V5knWQjZmYzru/ijNNEILVUGxFt9W20r5oc1n1nRZg2rCeppHaum73RVQsfOK0++uS/Oh6ZnRngTNr2IBtNnMGo2s2UiaZ1T4OK+K+VTMr2IBFYPR4c2kYmYVs6iYVcVsKmZXMYeKOVXMpWJuFfOomFfFfCrmV7GAisF3KuOHVpdZzzcRlanPVOKcKuZSMbeKedCKMivd/0Emyk8lDsZoYSCzaq6Xg6gtY1TaomIeFfOqmE/F/CoWUDEYq4WJzBb+2TaG2jk2XFzPOC9aIWEr8dr4/dw2ydICaHHM6Dfw0CzjwptDxTxoOZj90//ec2k+FQuomMkZ3iwqZlMxhzO0X0ocSjwqze0MzS9rw6bppflVzDw+vNnReFtOFx20XZpTxdwq5lUxv4rBhHDmSDSjbRT2E0yL/PhiVU5pMFELdo1irePTpJPmnSTWUsKe9M7wTdCSkwJot4Wtggrl0g8r81qaabIWZjHrlWdWR2k+tDRRiu1fdTmXNP90LZQFxe7nLXsgaPE9zDO0ME3Yahg25NOL3VOl+dB6Mvvw9d8x0mwztZDMLKnTg7LSAmhmZmky3j9G9c3Swm5mIy8kL5Rmmq2FJGYxV+dMkOZGa8KsRsYF16SBC/d4zBI77fNIc6E1ZGaZ1GYDtRPtW2bT87nHUX4/aqERM2fHtd9L86BFMqNnidG8aLYIxdKmuTiY4uZpwapRrGeNQ6WlWRfgfAHF8m3N9AuViVaEWTnb6DGUw3/Gynyru3Fbmn2RFu4xW1x1ah8qcwnuN5nderktgzTnMi18ZNZlcPQoabBSCyeZ1blRvRbl8JMWHoBi+15N+EBtWSXmtbDONXNUo/pWayGFmWFLj8vSHGtCzVV2/jUqc63Yjwlbt/25Ut86LbRgZlyTuI3mNVo9ZgP8tw9Ks6zXQiwzep8Amk3FHCrmUjGPivlULBDWcI2yQUv3UdbgNS54H0Wcy9GyiPFbi+czXc4pdK7zbRTzTFgOm6OANNgk9tPC3gyb1IbOyWh5mNHeEM2DtoVZyrd1W0lzbdbCTmaxvR52oDK3aGF4pGJzz1f9SOdrjxbegGL6bosGSzNvE9d+YZ3vfV1D+aF9YqYZutkizbRDC/WZ2WLazKY+Q6vA7HSFAXmledFimdE4oPlVDHaGMwAzmqw=
*/