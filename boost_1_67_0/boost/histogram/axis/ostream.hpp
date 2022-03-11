// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// String representations here evaluate correctly in Python.

#ifndef BOOST_HISTOGRAM_AXIS_OSTREAM_HPP
#define BOOST_HISTOGRAM_AXIS_OSTREAM_HPP

#include <boost/assert.hpp>
#include <boost/histogram/axis/regular.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <iomanip>
#include <iosfwd>
#include <sstream>
#include <stdexcept>
#include <type_traits>

/**
  \file boost/histogram/axis/ostream.hpp
  Simple streaming operators for the builtin axis types.

  The text representation is not guaranteed to be stable between versions of
  Boost.Histogram. This header is only included by
  [boost/histogram/ostream.hpp](histogram/reference.html#header.boost.histogram.ostream_hpp).
  To you use your own, include your own implementation instead of this header and do not
  include
  [boost/histogram/ostream.hpp](histogram/reference.html#header.boost.histogram.ostream_hpp).
 */

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

namespace boost {
namespace histogram {

namespace detail {
inline const char* axis_suffix(const axis::transform::id&) { return ""; }
inline const char* axis_suffix(const axis::transform::log&) { return "_log"; }
inline const char* axis_suffix(const axis::transform::sqrt&) { return "_sqrt"; }
inline const char* axis_suffix(const axis::transform::pow&) { return "_pow"; }

template <class OStream, class T>
void stream_metadata(OStream& os, const T& t) {
  detail::static_if<detail::is_streamable<T>>(
      [&os](const auto& t) {
        std::ostringstream oss;
        oss << t;
        if (!oss.str().empty()) { os << ", metadata=" << std::quoted(oss.str()); }
      },
      [&os](const auto&) { os << ", metadata=" << detail::type_name<T>(); }, t);
}

template <class OStream>
void stream_options(OStream& os, const unsigned bits) {
  os << ", options=";
  bool first = true;

#define BOOST_HISTOGRAM_AXIS_OPTION_OSTREAM(x) \
  if (bits & axis::option::x) {                \
    if (first)                                 \
      first = false;                           \
    else {                                     \
      os << " | ";                             \
    }                                          \
    os << #x;                                  \
  }

  BOOST_HISTOGRAM_AXIS_OPTION_OSTREAM(underflow);
  BOOST_HISTOGRAM_AXIS_OPTION_OSTREAM(overflow);
  BOOST_HISTOGRAM_AXIS_OPTION_OSTREAM(circular);
  BOOST_HISTOGRAM_AXIS_OPTION_OSTREAM(growth);

#undef BOOST_HISTOGRAM_AXIS_OPTION_OSTREAM

  if (first) os << "none";
}

template <class OStream, class T>
void stream_transform(OStream&, const T&) {}

template <class OStream>
void stream_transform(OStream& os, const axis::transform::pow& t) {
  os << ", power=" << t.power;
}

template <class OStream, class T>
void stream_value(OStream& os, const T& t) {
  os << t;
}

template <class OStream, class... Ts>
void stream_value(OStream& os, const std::basic_string<Ts...>& t) {
  os << std::quoted(t);
}

} // namespace detail

namespace axis {

template <class T>
class polymorphic_bin;

template <class... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os, const null_type&) {
  return os; // do nothing
}

template <class... Ts, class U>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const interval_view<U>& i) {
  os << "[" << i.lower() << ", " << i.upper() << ")";
  return os;
}

template <class... Ts, class U>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const polymorphic_bin<U>& i) {
  if (i.is_discrete())
    os << static_cast<double>(i);
  else
    os << "[" << i.lower() << ", " << i.upper() << ")";
  return os;
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const regular<Us...>& a) {
  os << "regular" << detail::axis_suffix(a.transform()) << "(" << a.size() << ", "
     << a.value(0) << ", " << a.value(a.size());
  detail::stream_metadata(os, a.metadata());
  detail::stream_options(os, a.options());
  detail::stream_transform(os, a.transform());
  os << ")";
  return os;
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const integer<Us...>& a) {
  os << "integer(" << a.value(0) << ", " << a.value(a.size());
  detail::stream_metadata(os, a.metadata());
  detail::stream_options(os, a.options());
  os << ")";
  return os;
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const variable<Us...>& a) {
  os << "variable(" << a.value(0);
  for (index_type i = 1, n = a.size(); i <= n; ++i) { os << ", " << a.value(i); }
  detail::stream_metadata(os, a.metadata());
  detail::stream_options(os, a.options());
  os << ")";
  return os;
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const category<Us...>& a) {
  os << "category(";
  for (index_type i = 0, n = a.size(); i < n; ++i) {
    detail::stream_value(os, a.value(i));
    os << (i == (a.size() - 1) ? "" : ", ");
  }
  detail::stream_metadata(os, a.metadata());
  detail::stream_options(os, a.options());
  os << ")";
  return os;
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const variant<Us...>& v) {
  visit(
      [&os](const auto& x) {
        using A = std::decay_t<decltype(x)>;
        detail::static_if<detail::is_streamable<A>>(
            [&os](const auto& x) { os << x; },
            [&os](const auto&) { os << "<unstreamable>"; }, x);
      },
      v);
  return os;
}

} // namespace axis
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DOXYGEN_INVOKED

#endif

/* ostream.hpp
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
*/