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
0u7NLynt0g5yNaOeBKqX3MQoX+wJ6WLycUZtjVTKGXL4vzTq7WAlSx7yS0i9G65KHymp0ajy2Dz5deRdczRqP/TgbnKyAyjpJjI3+jOyh9zdpVFHgz8je8kTizVqEKhBcnqpRnXL1dI+MrxCo34VrZYOkNMrNeqr8WrpcjK8RqO+D8hhcrpboxqUL0oj5P71GrUQqWt6JGOeGCH3IXUreUswEBohyzbqVHXoCvKgQbWHJsjaTTq1IXQlecSgsqGryPnn69RI6BryhEFdFzpBtm/WqLfH3xu6jnzcoD4ZegsJXaBTD4ZuIAcM6snQ28hDBjUZejtJXahTvw29g5wwKH/4RjLJqLW+ZPgmUrtFpxrD7yaXMeqvcjp8M3mvQa0Kv4f8gFEPkwvCt5CyrRr1EXJp+FaynVHHpMHwP5GTjMpKV4TfSx6nFMxnvtgbw7eR7xvULTA3vGRQd4c/RF5m1ILo4+GPkFcM6vnwR0nwIp16OfwxUmJQcuTjpN6gyiKfJPMYNTs4N3I3STOqtGhu5DNkF6OuDj4evoe8zqCeD3+OHDSol8P3kQmDkiP/Qq41qLLI/eQko5Lg4QFyH6MU8PAgeY5RTyqPh79CXjKo58MPkd8Z1Mvhr5G/GlRZ5BGibNMpOfIoKWPU75S5kcfJSka9GJ8b+RbJM+pyOIcnyIhBPR9+klxtUC+Hv0veYlBy5Glys0GVRZ4htzMq
*/