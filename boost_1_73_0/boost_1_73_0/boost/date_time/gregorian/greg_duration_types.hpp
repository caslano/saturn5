#ifndef GREG_DURATION_TYPES_HPP___
#define GREG_DURATION_TYPES_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/adjust_functors.hpp>
#include <boost/date_time/date_duration_types.hpp>
#include <boost/date_time/gregorian/greg_duration.hpp>

namespace boost {
namespace gregorian {

  //! config struct for additional duration types (ie months_duration<> & years_duration<>)
  struct BOOST_SYMBOL_VISIBLE greg_durations_config {
    typedef date date_type;
    typedef date_time::int_adapter<int> int_rep;
    typedef date_time::month_functor<date_type> month_adjustor_type; 
  };

  typedef date_time::months_duration<greg_durations_config> months;
  typedef date_time::years_duration<greg_durations_config> years;

  class BOOST_SYMBOL_VISIBLE weeks_duration : public date_duration {
  public:
    BOOST_CXX14_CONSTEXPR weeks_duration(duration_rep w) 
      : date_duration(w * 7) {}
    BOOST_CXX14_CONSTEXPR weeks_duration(date_time::special_values sv) 
      : date_duration(sv) {}
  };

  typedef weeks_duration weeks;

}} // namespace boost::gregorian

#endif // GREG_DURATION_TYPES_HPP___

/* greg_duration_types.hpp
7bXPur3u+EYM3JBux7Fb098Ep8+D14EQh7cCkCCwsyX4Lni5JcetsC/y4nRHxE/xAylsrVtSbvHcF3p9uiO0Bta+3JtXkOMwR53x1ahPX9q9q44YKYAX/MnnO5PBJ24X2+Z5vSSs75VNL3TV/9QfXPcnA/tty6a/CuE+7w/Gk7Orbg+p6dfq/NcsW5tAmm3dWHd7R/gvF1xTNMJOh9q9cNAQwdmIDm7f1EALoez7SKifi/8AUEsDBAoAAAAIAC1nSlL/G1qLYQQAAGgJAAAvAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IVFRQR0VULjNVVAUAAbZIJGCtVW1vo0YQ/s6vGLlf7IjDSXNS7nrpqcThLjQ+QAZfaskSWsMStrdmKbskcZv+984uOI59lZIPh2UDs/PyzMwzY2c5gKMfdlmOdgcvXqn5pnjhfWsUNeJPmqn/N0jTR+g+aLjE+ytCjWFn9ZiO4FVWjzA0Vmkf61w/p+krwi01SP0z1sbLVD+ipLPs7Sei3jTstlQwnIzg5P37d/AGfj4+eWfDJakY5RArWq1oc2vDeW4kv5Xk4cGR9KMNVAHhzp7DpGQSpCjUPWko4DNnGa0kzYFIyKnMGrbCF1aBKikUjFOY
*/