// Copyright 2015-2019 Hans Dembinski
// Copyright 2019 Przemyslaw Bartosik
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_OSTREAM_HPP
#define BOOST_HISTOGRAM_OSTREAM_HPP

#include <boost/histogram/accumulators/ostream.hpp>
#include <boost/histogram/axis/ostream.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/counting_streambuf.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/indexed.hpp>
#include <cmath>
#include <iomanip>
#include <ios>
#include <limits>
#include <numeric>
#include <ostream>
#include <streambuf>
#include <type_traits>

/**
  \file boost/histogram/ostream.hpp

  A simple streaming operator for the histogram type. The text representation is
  rudimentary and not guaranteed to be stable between versions of Boost.Histogram. This
  header is not included by any other header and must be explicitly included to use the
  streaming operator.

  To you use your own, simply include your own implementation instead of this header.
 */

namespace boost {
namespace histogram {
namespace detail {

template <class OStream, unsigned N>
class tabular_ostream_wrapper : public std::array<int, N> {
  using base_t = std::array<int, N>;
  using char_type = typename OStream::char_type;
  using traits_type = typename OStream::traits_type;

public:
  template <class T>
  tabular_ostream_wrapper& operator<<(const T& t) {
    if (collect_) {
      if (static_cast<std::size_t>(iter_ - base_t::begin()) == size_) {
        ++size_;
        BOOST_ASSERT(size_ <= N);
        BOOST_ASSERT(iter_ != end());
        *iter_ = 0;
      }
      cbuf_.count = 0;
      os_ << t;
      *iter_ = std::max(*iter_, static_cast<int>(cbuf_.count));
    } else {
      BOOST_ASSERT(iter_ != end());
      os_ << std::setw(*iter_) << t;
    }
    ++iter_;
    return *this;
  }

  tabular_ostream_wrapper& operator<<(decltype(std::setprecision(0)) t) {
    os_ << t;
    return *this;
  }

  tabular_ostream_wrapper& operator<<(decltype(std::fixed) t) {
    os_ << t;
    return *this;
  }

  tabular_ostream_wrapper& row() {
    iter_ = base_t::begin();
    return *this;
  }

  explicit tabular_ostream_wrapper(OStream& os) : os_(os), orig_(os_.rdbuf(&cbuf_)) {}

  auto end() { return base_t::begin() + size_; }
  auto end() const { return base_t::begin() + size_; }
  auto cend() const { return base_t::cbegin() + size_; }

  void complete() {
    BOOST_ASSERT(collect_); // only call this once
    collect_ = false;
    os_.rdbuf(orig_);
  }

private:
  typename base_t::iterator iter_ = base_t::begin();
  std::size_t size_ = 0;
  bool collect_ = true;
  OStream& os_;
  counting_streambuf<char_type, traits_type> cbuf_;
  std::basic_streambuf<char_type, traits_type>* orig_;
};

template <class OStream, class T>
void ostream_value(OStream& os, const T& val) {
  // a value from bin or histogram cell
  os << std::left;
  static_if_c<(std::is_convertible<T, double>::value && !std::is_integral<T>::value)>(
      [](auto& os, const auto& val) {
        const auto d = static_cast<double>(val);
        if (std::isfinite(d)) {
          const auto i = static_cast<std::int64_t>(d);
          if (i == d) {
            os << i;
            return;
          }
        }
        os << std::defaultfloat << std::setprecision(4) << d;
      },
      [](auto& os, const auto& val) { os << val; }, os, val);
}

template <class OStream, class Axis>
void ostream_bin(OStream& os, const Axis& ax, const int i) {
  os << std::right;
  static_if<has_method_value<Axis>>(
      [&](const auto& ax) {
        static_if<axis::traits::is_continuous<Axis>>(
            [&](const auto& ax) {
              os << std::defaultfloat << std::setprecision(4);
              auto a = ax.value(i);
              auto b = ax.value(i + 1);
              // round bin edge to zero if deviation from zero is absolut and relatively
              // small
              const auto eps = 1e-8 * std::abs(b - a);
              if (std::abs(a) < 1e-14 && std::abs(a) < eps) a = 0;
              if (std::abs(b) < 1e-14 && std::abs(b) < eps) b = 0;
              os << "[" << a << ", " << b << ")";
            },
            [&](const auto& ax) { os << ax.value(i); }, ax);
      },
      [&](const auto&) { os << i; }, ax);
}

template <class OStream, class... Ts>
void ostream_bin(OStream& os, const axis::category<Ts...>& ax, const int i) {
  os << std::right;
  if (i < ax.size())
    os << ax.value(i);
  else
    os << "other";
}

template <class CharT>
struct line_t {
  CharT ch;
  int size;
};

template <class CharT>
auto line(CharT c, int n) {
  return line_t<CharT>{c, n};
}

template <class C, class T>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& os, line_t<C>&& l) {
  for (int i = 0; i < l.size; ++i) os << l.ch;
  return os;
}

template <class OStream, class Axis, class T>
void stream_head(OStream& os, const Axis& ax, int index, const T& val) {
  axis::visit(
      [&](const auto& ax) {
        ostream_bin(os, ax, index);
        os << ' ';
        ostream_value(os, val);
      },
      ax);
}

template <class OStream, class Histogram>
void ascii_plot(OStream& os, const Histogram& h, int w_total) {
  if (w_total == 0) w_total = 78; // TODO detect actual width of terminal

  const auto& ax = h.axis();

  // value range; can be integer or float, positive or negative
  double vmin = 0;
  double vmax = 0;
  tabular_ostream_wrapper<OStream, 7> tos(os);
  // first pass to get widths
  for (auto&& v : indexed(h, coverage::all)) {
    stream_head(tos.row(), ax, v.index(), *v);
    vmin = std::min(vmin, static_cast<double>(*v));
    vmax = std::max(vmax, static_cast<double>(*v));
  }
  tos.complete();
  if (vmax == 0) vmax = 1;

  // calculate width useable by bar (notice extra space at top)
  // <-- head --> |<--- bar ---> |
  // w_head + 2 + 2
  const int w_head = std::accumulate(tos.begin(), tos.end(), 0);
  const int w_bar = w_total - 4 - w_head;
  if (w_bar < 0) return;

  // draw upper line
  os << '\n' << line(' ', w_head + 1) << '+' << line('-', w_bar + 1) << "+\n";

  const int zero_offset = static_cast<int>(std::lround((-vmin) / (vmax - vmin) * w_bar));
  for (auto&& v : indexed(h, coverage::all)) {
    stream_head(tos.row(), ax, v.index(), *v);
    // rest uses os, not tos
    os << " |";
    const int k = static_cast<int>(std::lround(*v / (vmax - vmin) * w_bar));
    if (k < 0) {
      os << line(' ', zero_offset + k) << line('=', -k) << line(' ', w_bar - zero_offset);
    } else {
      os << line(' ', zero_offset) << line('=', k) << line(' ', w_bar - zero_offset - k);
    }
    os << " |\n";
  }

  // draw lower line
  os << line(' ', w_head + 1) << '+' << line('-', w_bar + 1) << "+\n";
}

template <class OStream, class Histogram>
void ostream(OStream& os, const Histogram& h, const bool show_values = true) {
  os << "histogram(";

  unsigned iaxis = 0;
  const auto rank = h.rank();
  h.for_each_axis([&](const auto& ax) {
    using A = std::decay_t<decltype(ax)>;
    if ((show_values && rank > 0) || rank > 1) os << "\n  ";
    static_if<is_streamable<A>>([&](const auto& ax) { os << ax; },
                                [&](const auto&) { os << "<unstreamable>"; }, ax);
  });

  if (show_values && rank > 0) {
    tabular_ostream_wrapper<OStream, (BOOST_HISTOGRAM_DETAIL_AXES_LIMIT + 1)> tos(os);
    for (auto&& v : indexed(h, coverage::all)) {
      tos.row();
      for (auto i : v.indices()) tos << std::right << i;
      ostream_value(tos, *v);
    }
    tos.complete();

    const int w_item = std::accumulate(tos.begin(), tos.end(), 0) + 4 + h.rank();
    const int nrow = std::max(1, 65 / w_item);
    int irow = 0;
    for (auto&& v : indexed(h, coverage::all)) {
      os << (irow == 0 ? "\n  (" : " (");
      tos.row();
      iaxis = 0;
      for (auto i : v.indices()) {
        tos << std::right << i;
        os << (++iaxis == h.rank() ? "):" : " ");
      }
      os << ' ';
      ostream_value(tos, *v);
      ++irow;
      if (nrow > 0 && irow == nrow) irow = 0;
    }
    os << '\n';
  }
  os << ')';
}

} // namespace detail

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

template <class CharT, class Traits, class A, class S>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const histogram<A, S>& h) {
  // save fmt
  const auto flags = os.flags();

  os.flags(std::ios::dec | std::ios::left);

  const auto w = static_cast<int>(os.width());
  os.width(0);

  using value_type = typename histogram<A, S>::value_type;
  detail::static_if<std::is_convertible<value_type, double>>(
      [&os, w](const auto& h) {
        if (h.rank() == 1) {
          detail::ostream(os, h, false);
          detail::ascii_plot(os, h, w);
        } else
          detail::ostream(os, h);
      },
      [&os](const auto& h) { detail::ostream(os, h); }, h);

  // restore fmt
  os.flags(flags);
  return os;
}

} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

#endif

/* ostream.hpp
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
*/