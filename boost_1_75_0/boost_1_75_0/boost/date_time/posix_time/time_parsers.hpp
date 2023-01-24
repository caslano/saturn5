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
gQ+DjD9iwp6Apz5MR2L795tg3Tbv8eGuvutOox93WwktUMpR30kjWu+Wl0+j7ROY8R04kM+jvrNQSm/etpjRt1l4+a1oybQOtM7E0bcZ+sSnPHbaawV72mtVcrO7LTA/7bVGd//Bs9ZXK96t6FhW+/cF3lyLwRfiJOaWzFsrU8pTVwwlvNE3tQARnw35EnCa44yixORvth9Rw9iJ74yTdLGDXb27KmbyqeD3LQ2N+8hstfcvTKwp+owyw9cOb5MmTPHyWSD/3t/cOXH4khWb4SteOedWNO5ZHw/UDHoSi+utaiV/p0131iiPO7TC7Pc+K7rur2s6fiZuinP37RtmhXwDksUzoyoOiL4LN9GVYi1szrpJixS6n1YpL1Z9oElPH0oiVHYjl9unjpudeiNfG++3JESUxJri3e7mGaQ3v1f/mLEmCgq5pI9OOL2aYk8apo8xEPi+T2BC2Bn+Kv655+mSeqbky+MZygKXSZZM1OxP0uES3nl+H7QhW4RJySRvBpaCeo28pGkNgunVt+yn9d1MIuFv13meqiEB4SW7hfgnBBBUYXnf2drwLYnuiBwOTS9MCJEfr1w3q0vs3NsJBAwLzs1PrEdYvhObuePNP3ac3Z+pyg4gdh8/oQKr+Ige6J6agYusXn7rOQzydaNtBsQCJJRMll/gfZBYkP9Si3Qa++3BeuW77JW46Ppf4CHsEJSm5KWNsjsyCviW
*/