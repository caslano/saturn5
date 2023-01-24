//  (C) Copyright Jim Douglas 2005. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  QNX specific config options:

#define BOOST_PLATFORM "QNX"

#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

// QNX claims XOpen version 5 compatibility, but doesn't have an nl_types.h
// or log1p and expm1:
#undef  BOOST_HAS_NL_TYPES_H
#undef  BOOST_HAS_LOG1P
#undef  BOOST_HAS_EXPM1

#define BOOST_HAS_PTHREADS
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_CLOCK_GETTIME
#define BOOST_HAS_NANOSLEEP






/* qnxnto.hpp
vV3LZd1ksQEY2jUP6YjYmcWQFqkW6ku/9rkAOXA0NjF8J/0EwIVGZWIAJNFDvU5wV3XC2mxE5jEYQ9D9+DcLd0ghgK4CrHCG9PbmETA6GQZnCsGY5Q2lh8IDgTbDAN5IJ+eOArw9A56ULYFFNkWSpOL3glAZmuLCRfI773UlyZHZ7zMoHYbPkY6J24ysXjJVDDC6MLaXHBkbc7EBNGUKrpPpBbzER+zWHsGH3wQojwGuKdxGaNRmA9wK2EXmiQA4rc/mIbrVCDYA4hwgAVzuBphYRyJCYeT9SwNUSnaLbi1CHZamgoe3yxLwdi627owRmtDiGIYNcF29JfCKIGbRROlHOQx4LHylO0JWr08ELjKZ6+A6c6btnI8BK12Jwc+F2TTkhdL3LAHiIFs6d1Cwzmx/fzoC6ai0uZ+G7woaAXiDSFQCi2+UH9rpiyosQM75AJOLJX621h7ZEmYKyrwP0qMyyOFjYyZ1kZ3AMKNPYlV+GOAw7xC0D+1AdFAIADHejsCX4O2aqvEIgIH7GNVAD0ptefWungGge/4CmOoBVyqEbjQDLqaZ8gPQnzAwKwhSs47tcoiOGRgkvqj1cduCaeJ2V2DeC3c1o/HhN14h58yFJlTweG2MqjZCsgIoSLx9kYD3+Iwmdcp0l0YWKAPkZW6Ku4Xo7o4BS6D7lbXZhlLkM5VdEUBYjNwX4GVVlJIKCsbgB4ZB2whM9Piz
*/