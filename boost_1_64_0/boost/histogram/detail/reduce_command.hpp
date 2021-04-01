// Copyright 2020 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP
#define BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP

#include <boost/histogram/fwd.hpp>

namespace boost {
namespace histogram {
namespace detail {

struct reduce_command {
  static constexpr unsigned unset = static_cast<unsigned>(-1);
  unsigned iaxis;
  enum class range_t : char {
    none,
    indices,
    values,
  } range = range_t::none;
  union {
    axis::index_type index;
    double value;
  } begin, end;
  unsigned merge = 0; // default value indicates unset option
  bool crop = false;
  // for internal use by the reduce algorithm
  bool is_ordered = true;
  bool use_underflow_bin = true;
  bool use_overflow_bin = true;
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* reduce_command.hpp
8ge0LSe0IvFPvtPhhiFeRdZoZmjOg4m24wAVGy7ckzvdorfpcAZU/yR8dDPsZZdoV3AgRfhV0aukWzZhid6EkQLi4ADmOYtQHQ+ygRuBrzo6j91CJCs1zZhTwFHe35JA0ByWMzdkZZvEIG2L+3yDnsmUQ+OdJXQXfF6KK9aqlOGUXlJAOHwH16mgToVWjGv5Wud1NY3CvpYoB5dXIPTRKfkX1YvrWFnx7h7CbREnD5qzT18p9kNYC4KeWGO4/sUgEgP3pzEEl29I6R2i3Lgj6vFIgRAU6lsg0JK5zHFkzyjDso5Ml0grNqvfuuYYACs1WBsmKS/OaF93Bz33Lo3WuGMREye4g5yLKlF54yzOkQwgAhZHaKY8XaV0fnOODSk61+zIVssqlfLQEGtqJRim9thAv+kUinurHTBbDSqnPy2Ba69j5uAt52vedLJW6nYyb7rhJ57d3NnQcTGCeLA+ZmzbEPtc9Wi7h+vZlRCOZID800acVI4bTv12Y/WLrUquvCG3+4uv7FugLXk3DqZ36YzCjrS2ZNLGpuSklJwiXlaKaoUwjubacxbN0Q==
*/