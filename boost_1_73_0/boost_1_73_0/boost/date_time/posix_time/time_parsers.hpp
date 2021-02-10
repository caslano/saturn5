#ifndef POSIXTIME_PARSERS_HPP___
#define POSIXTIME_PARSERS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/time_parsing.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

 
namespace boost {

namespace posix_time {

  //! Creates a time_duration object from a delimited string
  /*! Expected format for string is "[-]h[h][:mm][:ss][.fff]".
   * A negative duration will be created if the first character in
   * string is a '-', all other '-' will be treated as delimiters.
   * Accepted delimiters are "-:,.". */
  inline time_duration duration_from_string(const std::string& s) {
    return date_time::parse_delimited_time_duration<time_duration>(s);
  }

  inline ptime time_from_string(const std::string& s) {
    return date_time::parse_delimited_time<ptime>(s, ' ');
  }

  inline ptime from_iso_string(const std::string& s) {
    return date_time::parse_iso_time<ptime>(s, 'T');
  }

  inline ptime from_iso_extended_string(const std::string& s) {
    return date_time::parse_delimited_time<ptime>(s, 'T');
  }



} } //namespace posix_time


#endif


/* time_parsers.hpp
yVJvaMsA32ueM6FYAVRBwVTe8hV+4QJ0xaDkNYNRPF1Ek98HsKl4XvU4W9mBqmRXF1DRWwYtyxm/dTANbTXIEhEQv+BKI2anuRQ+hmegWbtWPYxJgtZKAr2lvKYrDEc1VFo36ufhMO/aGk8yLGSuhvmOCr/S60enWmA2a7oF2WjQEjrFBmDWD2AtC16aJ1KEg023qrmqBoe0MKAohrIFxeq6h8OtnCl3BAZJz9bArIQGs+faPJQUykTbVHL9YCHS2gOVXSswHNKC6wqJxA+gEwVr7XpLxC5Kz7Kl/BslO+RegBSYFXhBAlHiwYoqrgbwJUov43kKX4LZLJikC4gvIJgserxP0eQctcExagvsrmmZwixa4Oum5qx4EPy7djrx00sYzWfjeJpm0SQNZxfBKIQ34L06hT86YYT91gOv5itTeTj135z6JzhgvmWMqm2mmDY1xl+Uk0LE5BImwVVInsIuXyJpXZsjZQKZLim+lXhM2elrycU16JaWJc8tRrKYxNMkSsiPXOR1VzA4M0GdAqsPxOLnEscf53JkZuBFhdqoUSJP8kAhVrSFF/skjn+xEc/DZDSLpmkUT8iUYgVov7DvILpmuMHvq8+0sipZltEeaFlOQeCyXvG4j+zPJpjeyPbmcHTXenZ5joJZ
*/