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
tHdplE5/cFTFHQwZzcN/tlyGYvM/tkKPfjXRDYPT0ZIsYT73DCG4ry7T5xlemrsu3ocNOMIdc7myVaGJ3mdR9ZyWcGKS/vZZ6XcvJBfUnWUqw4lsK2PQea/jCcHw65Kc4W0X3bIdc/bxN+zkHNBRERS2/QXgGmklg+tpoPGAj2ntCJQ6G4SGKRDiV3hBxbxdUrdPHn7KMymT3SCjEr5GKPx/BZYlJks+TX8zD+GALoDJoe+8pLCYigsa58CYAqXzdyM5QgFiy7f93ggk9PtnDGx8M0olxHbWIHOvh0w4IExmvzABrGCjrdrWiKpXcbeehq7ouUv9ZPrequrqTtvAcZ98m4YsdUF3YderGl+1eLfX54w985amUEi+Opkiycf9Ged8/5YUkJLdRGgLYF3h/IhppFePtYZRCV1nBUwBDOH65bq5PkbJJKRbivZ0nqlEkOGr2hNKQg+caZaJ21oiBj09V9WP9vf+IT6kCXVBvyCqlZ1MkIzQF9lKeMLhdaGFIDSC48VUbeIt1+HkixBMVKcqEKjN4oUd6R4Ki+eqGt0BLuGRqDqrADFlJA==
*/