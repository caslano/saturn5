// Copyright 2020 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP
#define BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP

#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <cassert>
#include <stdexcept>
#include <string>

namespace boost {
namespace histogram {
namespace detail {

struct reduce_command {
  static constexpr unsigned unset = static_cast<unsigned>(-1);
  unsigned iaxis = unset;
  enum class range_t : char {
    none,
    indices,
    values,
  } range = range_t::none;
  union {
    axis::index_type index;
    double value;
  } begin{0}, end{0};
  unsigned merge = 0; // default value indicates unset option
  bool crop = false;
  // for internal use by the reduce algorithm
  bool is_ordered = true;
  bool use_underflow_bin = true;
  bool use_overflow_bin = true;
};

// - puts commands in correct axis order
// - sets iaxis for positional commands
// - detects and fails on invalid settings
// - fuses merge commands with non-merge commands
inline void normalize_reduce_commands(span<reduce_command> out,
                                      span<const reduce_command> in) {
  unsigned iaxis = 0;
  for (const auto& o_in : in) {
    assert(o_in.merge > 0);
    if (o_in.iaxis != reduce_command::unset && o_in.iaxis >= out.size())
      BOOST_THROW_EXCEPTION(std::invalid_argument("invalid axis index"));
    auto& o_out = out.begin()[o_in.iaxis == reduce_command::unset ? iaxis : o_in.iaxis];
    if (o_out.merge == 0) {
      o_out = o_in;
    } else {
      // Some command was already set for this axis, try to fuse commands.
      if (!((o_in.range == reduce_command::range_t::none) ^
            (o_out.range == reduce_command::range_t::none)) ||
          (o_out.merge > 1 && o_in.merge > 1))
        BOOST_THROW_EXCEPTION(std::invalid_argument(
            "multiple conflicting reduce commands for axis " +
            std::to_string(o_in.iaxis == reduce_command::unset ? iaxis : o_in.iaxis)));
      if (o_in.range != reduce_command::range_t::none) {
        o_out.range = o_in.range;
        o_out.begin = o_in.begin;
        o_out.end = o_in.end;
      } else {
        o_out.merge = o_in.merge;
      }
    }
    ++iaxis;
  }

  iaxis = 0;
  for (auto& o : out) o.iaxis = iaxis++;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* reduce_command.hpp
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
*/