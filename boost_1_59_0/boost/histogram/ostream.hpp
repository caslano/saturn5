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
#include <boost/histogram/detail/counting_streambuf.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/term_info.hpp>
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

  To use your own, simply include your own implementation instead of this header.
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
      if (static_cast<unsigned>(iter_ - base_t::begin()) == size_) {
        ++size_;
        assert(size_ <= N);
        assert(iter_ != end());
        *iter_ = 0;
      }
      count_ = 0;
      os_ << t;
      *iter_ = std::max(*iter_, static_cast<int>(count_));
    } else {
      assert(iter_ != end());
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

  explicit tabular_ostream_wrapper(OStream& os)
      : os_(os), cbuf_(count_), orig_(os_.rdbuf(&cbuf_)) {}

  auto end() { return base_t::begin() + size_; }
  auto end() const { return base_t::begin() + size_; }
  auto cend() const { return base_t::cbegin() + size_; }

  void complete() {
    assert(collect_); // only call this once
    collect_ = false;
    os_.rdbuf(orig_);
  }

private:
  typename base_t::iterator iter_ = base_t::begin();
  unsigned size_ = 0;
  std::streamsize count_ = 0;
  bool collect_ = true;
  OStream& os_;
  counting_streambuf<char_type, traits_type> cbuf_;
  std::basic_streambuf<char_type, traits_type>* orig_;
};

template <class OStream, class T>
void ostream_value_impl(OStream& os, const T& t,
                        decltype(static_cast<double>(t), priority<1>{})) {
  // a value from histogram cell
  const auto d = static_cast<double>(t);
  if (std::numeric_limits<int>::min() <= d && d <= std::numeric_limits<int>::max()) {
    const auto i = static_cast<int>(d);
    if (i == d) {
      os << i;
      return;
    }
  }
  os << std::defaultfloat << std::setprecision(4) << d;
}

template <class OStream, class T>
void ostream_value_impl(OStream& os, const T& t, priority<0>) {
  os << t;
}

template <class OStream, class T>
void ostream_value(OStream& os, const T& t) {
  ostream_value_impl(os << std::left, t, priority<1>{});
}

template <class OStream, class Axis>
auto ostream_bin(OStream& os, const Axis& ax, axis::index_type i, std::true_type,
                 priority<1>) -> decltype((void)ax.value(i)) {
  auto a = ax.value(i), b = ax.value(i + 1);
  os << std::right << std::defaultfloat << std::setprecision(4);
  // round edges to zero if deviation from zero is small
  const auto eps = 1e-8 * std::abs(b - a);
  if (std::abs(a) < 1e-14 && std::abs(a) < eps) a = 0;
  if (std::abs(b) < 1e-14 && std::abs(b) < eps) b = 0;
  os << "[" << a << ", " << b << ")";
}

template <class OStream, class Axis>
auto ostream_bin(OStream& os, const Axis& ax, axis::index_type i, std::false_type,
                 priority<1>) -> decltype((void)ax.value(i)) {
  os << std::right;
  os << ax.value(i);
}

template <class OStream, class... Ts>
void ostream_bin(OStream& os, const axis::category<Ts...>& ax, axis::index_type i,
                 std::false_type, priority<1>) {
  os << std::right;
  if (i < ax.size())
    os << ax.value(i);
  else
    os << "other";
}

template <class OStream, class Axis, class B>
void ostream_bin(OStream& os, const Axis&, axis::index_type i, B, priority<0>) {
  os << std::right;
  os << i;
}

struct line {
  const char* ch;
  const int size;
  line(const char* a, int b) : ch{a}, size{std::max(b, 0)} {}
};

template <class T>
std::basic_ostream<char, T>& operator<<(std::basic_ostream<char, T>& os, line&& l) {
  for (int i = 0; i < l.size; ++i) os << l.ch;
  return os;
}

template <class OStream, class Axis>
void ostream_head(OStream& os, const Axis& ax, int index, double val) {
  axis::visit(
      [&](const auto& ax) {
        using A = std::decay_t<decltype(ax)>;
        ostream_bin(os, ax, index, axis::traits::is_continuous<A>{}, priority<1>{});
        os << ' ';
        ostream_value(os, val);
      },
      ax);
}

template <class OStream>
void ostream_bar(OStream& os, int zero_offset, double z, int width, bool utf8) {
  int k = static_cast<int>(std::lround(z * width));
  if (utf8) {
    os << " │";
    if (z > 0) {
      const char* scale[8] = {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉"};
      int j = static_cast<int>(std::lround(8 * (z * width - k)));
      if (j < 0) {
        --k;
        j += 8;
      }
      os << line(" ", zero_offset) << line("█", k);
      os << scale[j];
      os << line(" ", width - zero_offset - k);
    } else if (z < 0) {
      os << line(" ", zero_offset + k) << line("█", -k)
         << line(" ", width - zero_offset + 1);
    } else {
      os << line(" ", width + 1);
    }
    os << "│\n";
  } else {
    os << " |";
    if (z >= 0) {
      os << line(" ", zero_offset) << line("=", k) << line(" ", width - zero_offset - k);
    } else {
      os << line(" ", zero_offset + k) << line("=", -k) << line(" ", width - zero_offset);
    }
    os << " |\n";
  }
}

// cannot display generalized histograms yet; line not reachable by coverage tests
template <class OStream, class Histogram>
void plot(OStream&, const Histogram&, int, std::false_type) {} // LCOV_EXCL_LINE

template <class OStream, class Histogram>
void plot(OStream& os, const Histogram& h, int w_total, std::true_type) {
  if (w_total == 0) {
    w_total = term_info::width();
    if (w_total == 0 || w_total > 78) w_total = 78;
  }
  bool utf8 = term_info::utf8();

  const auto& ax = h.axis();

  // value range; can be integer or float, positive or negative
  double vmin = 0;
  double vmax = 0;
  tabular_ostream_wrapper<OStream, 7> tos(os);
  // first pass to get widths
  for (auto&& v : indexed(h, coverage::all)) {
    auto w = static_cast<double>(*v);
    ostream_head(tos.row(), ax, v.index(), w);
    vmin = std::min(vmin, w);
    vmax = std::max(vmax, w);
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
  os << '\n' << line(" ", w_head + 1);
  if (utf8)
    os << "┌" << line("─", w_bar + 1) << "┐\n";
  else
    os << '+' << line("-", w_bar + 1) << "+\n";

  const int zero_offset = static_cast<int>(std::lround((-vmin) / (vmax - vmin) * w_bar));
  for (auto&& v : indexed(h, coverage::all)) {
    auto w = static_cast<double>(*v);
    ostream_head(tos.row(), ax, v.index(), w);
    // rest uses os, not tos
    ostream_bar(os, zero_offset, w / (vmax - vmin), w_bar, utf8);
  }

  // draw lower line
  os << line(" ", w_head + 1);
  if (utf8)
    os << "└" << line("─", w_bar + 1) << "┘\n";
  else
    os << '+' << line("-", w_bar + 1) << "+\n";
}

template <class OStream, class Histogram>
void ostream(OStream& os, const Histogram& h, const bool show_values = true) {
  os << "histogram(";

  unsigned iaxis = 0;
  const auto rank = h.rank();
  h.for_each_axis([&](const auto& ax) {
    if ((show_values && rank > 0) || rank > 1) os << "\n  ";
    ostream_any(os, ax);
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

  using convertible = detail::is_explicitly_convertible<value_type, double>;
  // must be non-const to avoid a msvc warning about possible use of if constexpr
  bool show_plot = convertible::value && h.rank() == 1;
  if (show_plot) {
    detail::ostream(os, h, false);
    detail::plot(os, h, w, convertible{});
  } else {
    detail::ostream(os, h);
  }

  // restore fmt
  os.flags(flags);
  return os;
}

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

} // namespace histogram
} // namespace boost

#endif

/* ostream.hpp
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
*/