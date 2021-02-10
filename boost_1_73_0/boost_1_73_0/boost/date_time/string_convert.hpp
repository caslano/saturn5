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
12D7Lw4IthF5DitOrWamRcX/rrnSClYS4zOEV9dkEQmyykreYEM5cEnBm7HQRAe8oJ5PbLjjazqbfF08dFZIbUaNxQpMM01x9Ds/5hV4U3fmhl6T2Jp9wy5+KosubVkgdVdcWygTM0FYG79pefJs1iiPrUMHz812h13XShMTJDYqjvVkKmgH/RjaHPAljp+m+CmaL2TxbDjxfW8Ydnxa1Pq7mIx/VFbbH4YWI2xDehtxF5cZVgSwdmq5zHiBY0ig5Fo/jxl7Kn7rHmMYFInHeDH+NDnYm3AtLYI3cTtth3x05+PQeqSm0I+x264aub1yXj53ju1Gfg+FjfVIZcVNPAfGMGYSToaTcWBRTGbJ++p+no49yylSq+lmQ8S7O70uCqH72Lwi7dPiAfxrAexmQsX1G3zGYVzja4hBKTxdNBzSN/1knt7d+SliZYkc9/35eGxDL8gkV+IffgrHR72DJxF0jwg3jnmpT5vND4YSLdwOI7wgojtM+Q3DAc+dWK4He8FN8VsDiM9lzPJMKn36+uj10V4Wbstvm8QQg6DBoRnEAUjTYK18mmalvsPXB6Z5p9B7IrPxHMRjEw9q8wbVaRe3UI8a9dLeGFsSz+RObHctOHDBeUnP68ZG5+83OBzskdHtfH9EooYTVMU9
*/