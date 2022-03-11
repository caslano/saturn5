// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_REDUCE_HPP
#define BOOST_HISTOGRAM_ALGORITHM_REDUCE_HPP

#include <boost/assert.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/reduce_command.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/histogram/unsafe_access.hpp>
#include <boost/throw_exception.hpp>
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <string>

namespace boost {
namespace histogram {
namespace algorithm {

/** Holder for a reduce command.

  Use this type to store reduce commands in a container. The internals of this type are an
  implementation detail.
*/
using reduce_command = detail::reduce_command;

using reduce_option [[deprecated("use reduce_command instead")]] =
    reduce_command; ///< deprecated

/** Shrink command to be used in `reduce`.

  Command is applied to axis with given index.

  Shrinking is based on an inclusive value interval. The bin which contains the first
  value starts the range of bins to keep. The bin which contains the second value is the
  last included in that range. When the second value is exactly equal to a lower bin edge,
  then the previous bin is the last in the range.

  The counts in removed bins are added to the corresponding underflow and overflow bins,
  if they are present. If they are not present, the counts are discarded. Also see
  `crop`, which always discards the counts.

  @param iaxis which axis to operate on.
  @param lower bin which contains lower is first to be kept.
  @param upper bin which contains upper is last to be kept, except if upper is equal to
  the lower edge.
*/
inline reduce_command shrink(unsigned iaxis, double lower, double upper) {
  if (lower == upper)
    BOOST_THROW_EXCEPTION(std::invalid_argument("lower != upper required"));
  reduce_command r;
  r.iaxis = iaxis;
  r.range = reduce_command::range_t::values;
  r.begin.value = lower;
  r.end.value = upper;
  r.merge = 1;
  r.crop = false;
  return r;
}

/** Shrink command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  Shrinking is based on an inclusive value interval. The bin which contains the first
  value starts the range of bins to keep. The bin which contains the second value is the
  last included in that range. When the second value is exactly equal to a lower bin edge,
  then the previous bin is the last in the range.

  The counts in removed bins are added to the corresponding underflow and overflow bins,
  if they are present. If they are not present, the counts are discarded. Also see
  `crop`, which always discards the counts.

  @param lower bin which contains lower is first to be kept.
  @param upper bin which contains upper is last to be kept, except if upper is equal to
  the lower edge.
*/
inline reduce_command shrink(double lower, double upper) {
  return shrink(reduce_command::unset, lower, upper);
}

/** Crop command to be used in `reduce`.

  Command is applied to axis with given index.

  Works like `shrink` (see shrink documentation for details), but counts in removed
  bins are always discarded, whether underflow and overflow bins are present or not.

  @param iaxis which axis to operate on.
  @param lower bin which contains lower is first to be kept.
  @param upper bin which contains upper is last to be kept, except if upper is equal to
  the lower edge.
*/
inline reduce_command crop(unsigned iaxis, double lower, double upper) {
  reduce_command r = shrink(iaxis, lower, upper);
  r.crop = true;
  return r;
}

/** Crop command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  Works like `shrink` (see shrink documentation for details), but counts in removed bins
  are discarded, whether underflow and overflow bins are present or not.

  @param lower bin which contains lower is first to be kept.
  @param upper bin which contains upper is last to be kept, except if upper is equal to
  the lower edge.
*/
inline reduce_command crop(double lower, double upper) {
  return crop(reduce_command::unset, lower, upper);
}

///  Whether to behave like `shrink` or `crop` regarding removed bins.
enum class slice_mode { shrink, crop };

/** Slice command to be used in `reduce`.

  Command is applied to axis with given index.

  Slicing works like `shrink` or `crop`, but uses bin indices instead of values.

  @param iaxis which axis to operate on.
  @param begin first index that should be kept.
  @param end one past the last index that should be kept.
  @param mode whether to behave like `shrink` or `crop` regarding removed bins.
*/
inline reduce_command slice(unsigned iaxis, axis::index_type begin, axis::index_type end,
                            slice_mode mode = slice_mode::shrink) {
  if (!(begin < end))
    BOOST_THROW_EXCEPTION(std::invalid_argument("begin < end required"));

  reduce_command r;
  r.iaxis = iaxis;
  r.range = reduce_command::range_t::indices;
  r.begin.index = begin;
  r.end.index = end;
  r.merge = 1;
  r.crop = mode == slice_mode::crop;
  return r;
}

/** Slice command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  Slicing works like `shrink` or `crop`, but uses bin indices instead of values.

  @param begin first index that should be kept.
  @param end one past the last index that should be kept.
  @param mode whether to behave like `shrink` or `crop` regarding removed bins.
*/
inline reduce_command slice(axis::index_type begin, axis::index_type end,
                            slice_mode mode = slice_mode::shrink) {
  return slice(reduce_command::unset, begin, end, mode);
}

/** Rebin command to be used in `reduce`.

  Command is applied to axis with given index.

  The command merges N adjacent bins into one. This makes the axis coarser and the bins
  wider. The original number of bins is divided by N. If there is a rest to this devision,
  the axis is implicitly shrunk at the upper end by that rest.

  @param iaxis which axis to operate on.
  @param merge how many adjacent bins to merge into one.
*/
inline reduce_command rebin(unsigned iaxis, unsigned merge) {
  if (merge == 0) BOOST_THROW_EXCEPTION(std::invalid_argument("merge > 0 required"));
  reduce_command r;
  r.iaxis = iaxis;
  r.merge = merge;
  r.range = reduce_command::range_t::none;
  r.crop = false;
  return r;
}

/** Rebin command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  The command merges N adjacent bins into one. This makes the axis coarser and the bins
  wider. The original number of bins is divided by N. If there is a rest to this devision,
  the axis is implicitly shrunk at the upper end by that rest.

  @param merge how many adjacent bins to merge into one.
*/
inline reduce_command rebin(unsigned merge) {
  return rebin(reduce_command::unset, merge);
}

/** Shrink and rebin command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  To shrink(unsigned, double, double) and rebin(unsigned, unsigned) in one command (see
  the respective commands for more details). Equivalent to passing both commands for the
  same axis to `reduce`.

  @param iaxis which axis to operate on.
  @param lower lowest bound that should be kept.
  @param upper highest bound that should be kept. If upper is inside bin interval, the
  whole interval is removed.
  @param merge how many adjacent bins to merge into one.
*/
inline reduce_command shrink_and_rebin(unsigned iaxis, double lower, double upper,
                                       unsigned merge) {
  reduce_command r = shrink(iaxis, lower, upper);
  r.merge = rebin(merge).merge;
  return r;
}

/** Shrink and rebin command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  To `shrink` and `rebin` in one command (see the respective commands for more
  details). Equivalent to passing both commands for the same axis to `reduce`.

  @param lower lowest bound that should be kept.
  @param upper highest bound that should be kept. If upper is inside bin interval, the
  whole interval is removed.
  @param merge how many adjacent bins to merge into one.
*/
inline reduce_command shrink_and_rebin(double lower, double upper, unsigned merge) {
  return shrink_and_rebin(reduce_command::unset, lower, upper, merge);
}

/** Crop and rebin command to be used in `reduce`.

  Command is applied to axis with given index.

  To `crop` and `rebin` in one command (see the respective commands for more
  details). Equivalent to passing both commands for the same axis to `reduce`.

  @param iaxis which axis to operate on.
  @param lower lowest bound that should be kept.
  @param upper highest bound that should be kept. If upper is inside bin interval,
  the whole interval is removed.
  @param merge how many adjacent bins to merge into one.
*/
inline reduce_command crop_and_rebin(unsigned iaxis, double lower, double upper,
                                     unsigned merge) {
  reduce_command r = crop(iaxis, lower, upper);
  r.merge = rebin(merge).merge;
  return r;
}

/** Crop and rebin command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  To `crop` and `rebin` in one command (see the respective commands for more
  details). Equivalent to passing both commands for the same axis to `reduce`.

  @param lower lowest bound that should be kept.
  @param upper highest bound that should be kept. If upper is inside bin interval,
  the whole interval is removed.
  @param merge how many adjacent bins to merge into one.
*/
inline reduce_command crop_and_rebin(double lower, double upper, unsigned merge) {
  return crop_and_rebin(reduce_command::unset, lower, upper, merge);
}

/** Slice and rebin command to be used in `reduce`.

  Command is applied to axis with given index.

  To `slice` and `rebin` in one command (see the respective commands for more
  details). Equivalent to passing both commands for the same axis to `reduce`.

  @param iaxis which axis to operate on.
  @param begin first index that should be kept.
  @param end one past the last index that should be kept.
  @param merge how many adjacent bins to merge into one.
  @param mode slice mode, see slice_mode.
*/
inline reduce_command slice_and_rebin(unsigned iaxis, axis::index_type begin,
                                      axis::index_type end, unsigned merge,
                                      slice_mode mode = slice_mode::shrink) {
  reduce_command r = slice(iaxis, begin, end, mode);
  r.merge = rebin(merge).merge;
  return r;
}

/** Slice and rebin command to be used in `reduce`.

  Command is applied to corresponding axis in order of reduce arguments.

  To `slice` and `rebin` in one command (see the respective commands for more
  details). Equivalent to passing both commands for the same axis to `reduce`.

  @param begin first index that should be kept.
  @param end one past the last index that should be kept.
  @param merge how many adjacent bins to merge into one.
  @param mode slice mode, see slice_mode.
*/
inline reduce_command slice_and_rebin(axis::index_type begin, axis::index_type end,
                                      unsigned merge,
                                      slice_mode mode = slice_mode::shrink) {
  return slice_and_rebin(reduce_command::unset, begin, end, merge, mode);
}

/** Shrink, crop, slice, and/or rebin axes of a histogram.

  Returns a new reduced histogram and leaves the original histogram untouched.

  The commands `rebin` and `shrink` or `slice` for the same axis are
  automatically combined, this is not an error. Passing a `shrink` and a `slice`
  command for the same axis or two `rebin` commands triggers an `invalid_argument`
  exception. Trying to reducing a non-reducible axis triggers an `invalid_argument`
  exception. Histograms with  non-reducible axes can still be reduced along the
  other axes that are reducible.

  @param hist original histogram.
  @param options iterable sequence of reduce commands: `shrink`, `slice`, `rebin`,
  `shrink_and_rebin`, or `slice_and_rebin`. The element type of the iterable should be
  `reduce_command`.
*/
template <class Histogram, class Iterable, class = detail::requires_iterable<Iterable>>
Histogram reduce(const Histogram& hist, const Iterable& options) {
  using axis::index_type;

  const auto& old_axes = unsafe_access::axes(hist);

  auto opts = detail::make_stack_buffer<reduce_command>(old_axes);

  // check for invalid commands, merge commands, and set iaxis for positional commands
  unsigned iaxis = 0;
  for (const reduce_command& o_in : options) {
    BOOST_ASSERT(o_in.merge > 0);
    if (o_in.iaxis != reduce_command::unset && o_in.iaxis >= hist.rank())
      BOOST_THROW_EXCEPTION(std::invalid_argument("invalid axis index"));
    auto& o_out = opts[o_in.iaxis == reduce_command::unset ? iaxis : o_in.iaxis];
    if (o_out.merge == 0) {
      o_out = o_in;
    } else {
      // Some command was already set for this axis, see if we can combine commands.
      // We can combine a rebin and non-rebin command.
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

  // make new axes container with default-constructed axis instances
  auto axes = detail::make_default(old_axes);
  detail::static_if<detail::is_tuple<decltype(axes)>>(
      [](auto&, const auto&) {},
      [](auto& axes, const auto& old_axes) {
        axes.reserve(old_axes.size());
        detail::for_each_axis(old_axes, [&axes](const auto& a) {
          axes.emplace_back(detail::make_default(a));
        });
      },
      axes, old_axes);

  // override default-constructed axis instances with modified instances
  iaxis = 0;
  hist.for_each_axis([&](const auto& a_in) {
    using A = std::decay_t<decltype(a_in)>;
    using AO = axis::traits::get_options<A>;
    auto& o = opts[iaxis];
    o.is_ordered = axis::traits::ordered(a_in);
    if (o.merge > 0) { // option is set?
      o.use_underflow_bin = !o.crop && AO::test(axis::option::underflow);
      o.use_overflow_bin = !o.crop && AO::test(axis::option::overflow);
      detail::static_if_c<axis::traits::is_reducible<A>::value>(
          [&o](auto&& a_out, const auto& a_in) {
            using A = std::decay_t<decltype(a_in)>;
            if (o.range == reduce_command::range_t::none) {
              o.begin.index = 0;
              o.end.index = a_in.size();
            } else {
              if (o.range == reduce_command::range_t::values) {
                const auto end_value = o.end.value;
                o.begin.index = axis::traits::index(a_in, o.begin.value);
                o.end.index = axis::traits::index(a_in, o.end.value);
                // end = index + 1, unless end_value is exactly equal to (upper) bin edge
                if (axis::traits::value_as<double>(a_in, o.end.index) != end_value)
                  ++o.end.index;
              }
              // limit [begin, end] to [0, size()]
              if (o.begin.index < 0) o.begin.index = 0;
              if (o.end.index > a_in.size()) o.end.index = a_in.size();
            }
            // shorten the index range to a multiple of o.merge;
            // example [1, 4] with merge = 2 is reduced to [1, 3]
            o.end.index -=
                (o.end.index - o.begin.index) % static_cast<index_type>(o.merge);
            a_out = A(a_in, o.begin.index, o.end.index, o.merge);
          },
          [iaxis](auto&&, const auto&) {
            BOOST_THROW_EXCEPTION(std::invalid_argument("axis " + std::to_string(iaxis) +
                                                        " is not reducible"));
          },
          axis::get<A>(detail::axis_get(axes, iaxis)), a_in);
    } else {
      // command was not set for this axis; fill noop values and copy original axis
      o.use_underflow_bin = AO::test(axis::option::underflow);
      o.use_overflow_bin = AO::test(axis::option::overflow);
      o.merge = 1;
      o.begin.index = 0;
      o.end.index = a_in.size();
      axis::get<A>(detail::axis_get(axes, iaxis)) = a_in;
    }
    ++iaxis;
  });

  auto idx = detail::make_stack_buffer<index_type>(axes);
  auto result =
      Histogram(std::move(axes), detail::make_default(unsafe_access::storage(hist)));
  for (auto&& x : indexed(hist, coverage::all)) {
    auto i = idx.begin();
    auto o = opts.begin();
    bool skip = false;

    for (auto j : x.indices()) {
      *i = (j - o->begin.index);
      if (o->is_ordered && *i <= -1) {
        *i = -1;
        if (!o->use_underflow_bin) skip = true;
      } else {
        if (*i >= 0)
          *i /= static_cast<index_type>(o->merge);
        else
          *i = o->end.index;
        const auto reduced_axis_end =
            (o->end.index - o->begin.index) / static_cast<index_type>(o->merge);
        if (*i >= reduced_axis_end) {
          *i = reduced_axis_end;
          if (!o->use_overflow_bin) skip = true;
        }
      }

      ++i;
      ++o;
    }

    if (!skip) result.at(idx) += *x;
  }

  return result;
}

/** Shrink, slice, and/or rebin axes of a histogram.

  Returns a new reduced histogram and leaves the original histogram untouched.

  The commands `rebin` and `shrink` or `slice` for the same axis are
  automatically combined, this is not an error. Passing a `shrink` and a `slice`
  command for the same axis or two `rebin` commands triggers an invalid_argument
  exception. It is safe to reduce histograms with some axis that are not reducible along
  the other axes. Trying to reducing a non-reducible axis triggers an invalid_argument
  exception.

  @param hist original histogram.
  @param opt first reduce command; one of `shrink`, `slice`, `rebin`,
  `shrink_and_rebin`, or `slice_or_rebin`.
  @param opts more reduce commands.
*/
template <class Histogram, class... Ts>
Histogram reduce(const Histogram& hist, const reduce_command& opt, const Ts&... opts) {
  // this must be in one line, because any of the ts could be a temporary
  return reduce(hist, std::initializer_list<reduce_command>{opt, opts...});
}

} // namespace algorithm
} // namespace histogram
} // namespace boost

#endif

/* reduce.hpp
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
*/