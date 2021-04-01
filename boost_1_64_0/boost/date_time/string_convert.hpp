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
qlrie1B6biGLWJV8hREYTpmCmMDsB4j7KCgfGEef9ojRa6k9xkc/D5XNfwPUFBXz1mjEa5tZK9JQMRciXz6Q16/BvFJ+BtnZ7BLpmLb9s5ydyPEMX2rT94KH1ydI5Q/9oarVtJbXQaqzcliYWif9UJxulLOhot8IrSjVXfnSnnJbB0wRcpZSSkJ0QdOfJFPWBWZa7s3xw9zp8xTXNaY0nWTDjXiBEaU372wmp/T9CnpSjAyAvPxLRIVIHATNgGtouBn4sWBnqznDlvKFWn7FORaY4VgbJkhpJkyeYEWYIW05w9ZDr8Shgd6XUOcburd3D+9zDGI4uOIntO2mEB0eEloLmMMvjcNlZOGORP43V0soszmOm/sks6OiOEjhfE4k41jFfC2paaqEQu3nSyusJcxW8TQbB7FQDXFKE2gYHrg4XWsyixT16FKjsu25lagTsWNGKURyl83vOKXGC9iVF2we19tU+8mKOCEXZ5lAZHkbicj8KgjxMmr3wBRBxmoKl5paK8yyXv2yFYNYldCSYnSIfebmUVMl7vMNnKdbxyTRCmg9xuA6fUPfxQ==
*/