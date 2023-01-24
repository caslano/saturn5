#ifndef DATE_TIME_LOCAL_TIME_CONVERSION_HPP__
#define DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/posix_time/conversion.hpp"
#include "boost/date_time/c_time.hpp"
#include "boost/date_time/local_time/local_date_time.hpp"

namespace boost {
namespace local_time {

//! Function that creates a tm struct from a local_date_time
inline
std::tm to_tm(const local_date_time& lt) {
  std::tm lt_tm = posix_time::to_tm(lt.local_time());
  if(lt.is_dst()){
    lt_tm.tm_isdst = 1;
  }
  else{
    lt_tm.tm_isdst = 0;
  }
  return lt_tm;
}


}} // namespaces
#endif // DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* conversion.hpp
DVvlXKFDRI4irbaEfSLYv0kryHrU8HU3W9zbB8o/qDYUHKu6AaKKR44baPKXs3rrClzptu60CqbtTbwMreBs9oYix/ETR31Jpwu52rntksgQ4D5iVYwFHhAj+C2X1G9b/AAiRvH4r1eLnjx7owsW7N08Cs0/E0VsS32HPkmZRNBcrsxIwv6nSrN7QHKfF6Q059s6oluMxxlzi2G70O4Tj4MpPKoWAEHL7jaqFdITQaZWfghXAHZ3tibp9qRWo1wbBqM5JXszZayrWBburszMX3j9IC6cxz46uN3ptebTTjN4WsNQLomM2OyvsxK4AIWUxX8fc6CCAJWdWzrg5aKMun/YytDz8FsGkB1co84ggAz1TV7KBzB8zhX8+M6cvtvJ6fM/S+9NV79BGzfgv7r6wOwV2s3WPmiPf1xXM53QsrmFzL5mxjSdWA0Pqwk+avSyY6W3KEkGm+kEdAIgxxAZBivY5nDxEegtXDws21c8IfK7WbHxR8fAUrpwWKmM6+OrkdH+WKE/8CUnhrS4hJcG8JMjHZMij+bEYG6bpu7D0Zw2Vi16pDbLit/fHri8Rv2anxfLzfd09l9K0kQiYv5cQzzrt+K7N1T/BZud24Tkzy8A2XtIeImsMkPFfpbzWkdntrzBoDUQvW6/RNw5IdyI3HlAn/gd/blZvVT/pfLeOr1U/zv1+0KQavWj6iz5YHzsPILNPvl6An+rR3SF
*/