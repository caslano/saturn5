#ifndef _STRING_CONVERT_HPP___
#define _STRING_CONVERT_HPP___

/* Copyright (c) 2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/compiler_config.hpp"
#include <string>

namespace boost {
namespace date_time {

  //! Converts a string from one value_type to another
  /*! Converts a wstring to a string (or a string to wstring). If both template parameters 
   * are of same type, a copy of the input string is returned. */
  template<class InputT, class OutputT>
  inline
  std::basic_string<OutputT> convert_string_type(const std::basic_string<InputT>& inp_str)
  {
    typedef std::basic_string<OutputT> output_type;
    output_type result;
    result.insert(result.begin(), inp_str.begin(), inp_str.end());
    return result;
  }
  
}} // namespace boost::date_time

#endif // _STRING_CONVERT_HPP___

/* string_convert.hpp
eJw5g3B5mj/Q/CK6ruAGQcqam3E0GJmSHGj+b6I3ua7XSrWWKNDS410zFC/D1VvOljRDkRu5lGdBbHhEvg03V1EEITVLbzUGtX7B/HB6vv0G7tnBW9ofBiOB5GAYv8aimbwEuhHV5sO/m58TTodeA0/lhysTFLuO7oyP4ntjBVcaHowP7U9Dc0TNO1zHXLlQ33GJo9GE4h4Qxu/2qYj1u2GcjNgt8DjoxiqFXv1xnbcf5+PcHap9NT9xQNwJZRs=
*/