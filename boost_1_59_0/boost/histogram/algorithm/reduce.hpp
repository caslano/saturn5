// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_REDUCE_HPP
#define BOOST_HISTOGRAM_ALGORITHM_REDUCE_HPP

#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/reduce_command.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/histogram/unsafe_access.hpp>
#include <boost/throw_exception.hpp>
#include <cassert>
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

using reduce_option [[deprecated("use reduce_command instead; "
                                 "reduce_option will be removed in boost-1.80")]] =
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
  are discarded, whether underflow and overflow bins are present or not. If the cropped
  range goes beyond the axis range, then the content of the underflow
  or overflow bin which overlaps with the range is kept.

  If the counts in an existing underflow or overflow bin are discared by the crop, the
  corresponding memory cells are not physically removed. Only their contents are set to
  zero. This technical limitation may be lifted in the future, then crop may completely
  remove the cropped memory cells.

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

  An overload allows one to pass reduce_command as positional arguments.

  @param hist original histogram.
  @param options iterable sequence of reduce commands: `shrink`, `slice`, `rebin`,
  `shrink_and_rebin`, or `slice_and_rebin`. The element type of the iterable should be
  `reduce_command`.
*/
template <class Histogram, class Iterable, class = detail::requires_iterable<Iterable>>
Histogram reduce(const Histogram& hist, const Iterable& options) {
  using axis::index_type;

  const auto& old_axes = unsafe_access::axes(hist);
  auto opts = detail::make_stack_buffer(old_axes, reduce_command{});
  detail::normalize_reduce_commands(opts, options);

  auto axes =
      detail::axes_transform(old_axes, [&opts](std::size_t iaxis, const auto& a_in) {
        using A = std::decay_t<decltype(a_in)>;
        using AO = axis::traits::get_options<A>;
        auto& o = opts[iaxis];
        o.is_ordered = axis::traits::ordered(a_in);
        if (o.merge > 0) { // option is set?
          o.use_underflow_bin = AO::test(axis::option::underflow);
          o.use_overflow_bin = AO::test(axis::option::overflow);
          return detail::static_if_c<axis::traits::is_reducible<A>::value>(
              [&o](const auto& a_in) {
                if (o.range == reduce_command::range_t::none) {
                  // no range restriction, pure rebin
                  o.begin.index = 0;
                  o.end.index = a_in.size();
                } else {
                  // range striction, convert values to indices as needed
                  if (o.range == reduce_command::range_t::values) {
                    const auto end_value = o.end.value;
                    o.begin.index = axis::traits::index(a_in, o.begin.value);
                    o.end.index = axis::traits::index(a_in, o.end.value);
                    // end = index + 1, unless end_value equal to upper bin edge
                    if (axis::traits::value_as<double>(a_in, o.end.index) != end_value)
                      ++o.end.index;
                  }

                  // crop flow bins if index range does not include them
                  if (o.crop) {
                    o.use_underflow_bin &= o.begin.index < 0;
                    o.use_overflow_bin &= o.end.index > a_in.size();
                  }

                  // now limit [begin, end] to [0, size()]
                  if (o.begin.index < 0) o.begin.index = 0;
                  if (o.end.index > a_in.size()) o.end.index = a_in.size();
                }
                // shorten the index range to a multiple of o.merge;
                // example [1, 4] with merge = 2 is reduced to [1, 3]
                o.end.index -=
                    (o.end.index - o.begin.index) % static_cast<index_type>(o.merge);
                using A = std::decay_t<decltype(a_in)>;
                return A(a_in, o.begin.index, o.end.index, o.merge);
              },
              [iaxis](const auto& a_in) {
                return BOOST_THROW_EXCEPTION(std::invalid_argument(
                           "axis " + std::to_string(iaxis) + " is not reducible")),
                       a_in;
              },
              a_in);
        } else {
          // command was not set for this axis; fill noop values and copy original axis
          o.use_underflow_bin = AO::test(axis::option::underflow);
          o.use_overflow_bin = AO::test(axis::option::overflow);
          o.merge = 1;
          o.begin.index = 0;
          o.end.index = a_in.size();
          return a_in;
        }
      });

  auto result =
      Histogram(std::move(axes), detail::make_default(unsafe_access::storage(hist)));

  auto idx = detail::make_stack_buffer<index_type>(unsafe_access::axes(result));
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

  An overload allows one to pass an iterable of reduce_command.

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