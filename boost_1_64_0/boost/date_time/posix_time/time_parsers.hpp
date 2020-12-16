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
uJeuxK8mkRiBShtVoPKOmvaoLvKXobpIOxWJ2eTKRFjpL9TbWx1DYXurBkRho9neWrD4iFqcvaIxo5vsywYsC+lPRhuXdVgvIW9pRC7HMQw94cH8EDFViBI9lsRkg5fXnwFXYuWhVG6qrTIUeWYF8skliBflHylnncfw68IN0Zmd6vMXpQBzj6J/i3/8/lt01XKw97HGFq9WSTaGwc0IITf4zt/kCaduo/eEfjc9jSEi2hibjHEhkzsRYl1rvgo5uatU2H9LVVci/YqRVZuKLW1J/VHTP0MBj192XMgiEtnfY70iS90K/KtV+Lhmlc4h5eR0rL2WvZ4lFx3p1l+DysMBTo2oaW/RxT9BxWOJodfCDuj/iQJm+wkNLLSM5/8sj9EUlqD+Ex9T016uu+X6wehOKLt2pCexeaqaO6tpcjSpYAU1edtqPT6Yn6N08brBen6WnSEnFc3LMXpeVg0283KlmZdff5uCPZRgR40V0gRREnq6RGi6RGjUI0wFrlshUmfwWX81ZetjWqxVh2E5KgTdQHEgxKOp/GqVfwfrOvou59Z86B3YkKou3vUUrV7+fdGDiQmgZ9GNuLOUn15vL4J4Cnce80d3qA6aWaKDsSLFu/zezT4LoRiUdqgYyw3ppRxfiJtcDEv4VPWfbjd1yptBsbF/1Sh1iV5v0Z6W8SJsK2q5HC9CaYBzF83egT6PB5NoERzKbipMpA6pl0F50mxTPTN2/RgTRFcPfdna1T30P4kJIBz8qQOpH2IoY7yAi6/LTd6oN+2rxLWhU/Ty0Zzfqp6TLUbub4R7jxP/WWlxgyHhS7wQjiM/Ch2a/mMtor6tfeQVnYd8LLXawDeBmneuRl7Ba2DrPnyQX4MZ0hxAH43sRn3fIwcRKZ7dgmqIyi1AUWr6MBHS4jTM5xA4k/tSPUNElME1RyweSGtsGk79IaR3Q9LEaaR3X2gIYgqTy1Sv6lIXnqVFcwxf1ZfcUDajNlOEjxBHuCUahD5ODU93cIGuvnYxiNv/kS+lRG1mbGqp4f8qi9KEYpV94NQRLWn+n0z838L8z3Nffh+vJUv+b2H+/9OfeuP/nZoFZwn+rwXymjT/1yZvZ9HO/P8B6dbT/H+14f8mDsrV/F+V+PZHJP9jUpuf+X888T8wIAsLNv6BIdWHgzroMYi7w5GgDvtT5Vl/xKnIHUyMVQkzSLN+C2jlqoxyd8Ey/q754hbztQFmYIrGPeQHXSpMYa9R29qxfhx0bjVF6ObrC8S3lHbCGoLDUJ3KTV6n+hXI25gIQquSZ5PABgFTvSUa0F0w5Uw9O5rwlWZHFc0OKj1Lz45amB3c/QW6+iWLYHa8GUR/Vj9thf30Yv2tu9m1y5SwaK5uzZ2lHlTH5Varv8DVEXRER3Qg84qCcs+eoAfduOWqQMKnhg7i5NUzmj5Zzcco2n8as0IxxcMhT7yqoCqhNkq8WlW5dMVIUvgiyimknHrK/fai2bteiJFToviwJi5eYop3MmjWQniTQUrs7SQ1Z5EWAgzjZznsWbMqvYyRBgKBX5WkgYRJA1HqA0w1VWWK1j+qPPFqqFml+uw7AXOgiqKxD2hKV0Q1pb7USOgR1C2uB93iIvUf+4Fe1+9U2e3zb12E45P40UyYFV2J6+osIgat4zB+Slq55fZ8kIajKnGjMorENf5b1St0sX4LrtCCJwszmcjhGO4pmhwlJMMd3d3r1wH62aiudZx/x8bnz8/Z13lMn9adWVO0Pg/FRGqUvQCv9pELFDQMu84i3tnWMV94N1ICzMRfwY3VshssstsHZT6el9EV4OhPqvJBhNK7+bxK6D3mvErQpw3hMJRY+w7FLR15qll50KwcZSuC/BQ=
*/