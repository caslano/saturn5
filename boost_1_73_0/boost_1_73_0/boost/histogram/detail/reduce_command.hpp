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
QD/FeBcTG+HFblmtRTtHRfDQt0gS1lfNutT5TSuctFYt8hC20Zyxxri6AFRjLUy6xyUawOI1qCpCzAVMwWc43BPeZBTN3jqm/rHW8qizJZtjpRMJfIy7TMyc1NH2MlMfB7s8Cjfa/oeXKs1yTBVLxir89V9BNd4Y9jHtrS1RE4gBqDlssk88mojFrRqgQiOZXdKZz2AwjQ4FSQNkNcqKYlgsWpytX5+xfn3+BjqAIVGfhL7pBWS5fJbeSaR3J78=
*/