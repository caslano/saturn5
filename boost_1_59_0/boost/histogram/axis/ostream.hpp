// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// String representations here evaluate correctly in Python.

#ifndef BOOST_HISTOGRAM_AXIS_OSTREAM_HPP
#define BOOST_HISTOGRAM_AXIS_OSTREAM_HPP

#include <boost/histogram/axis/regular.hpp>
#include <boost/histogram/detail/counting_streambuf.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <cassert>
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
  To use your own, include your own implementation instead of this header and do not
  include
  [boost/histogram/ostream.hpp](histogram/reference.html#header.boost.histogram.ostream_hpp).
 */

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

namespace boost {
namespace histogram {

namespace detail {

template <class OStream, class T>
auto ostream_any_impl(OStream& os, const T& t, priority<1>) -> decltype(os << t) {
  return os << t;
}

template <class OStream, class T>
OStream& ostream_any_impl(OStream& os, const T&, priority<0>) {
  return os << type_name<T>();
}

template <class OStream, class T>
OStream& ostream_any(OStream& os, const T& t) {
  return ostream_any_impl(os, t, priority<1>{});
}

template <class OStream, class... Ts>
OStream& ostream_any_quoted(OStream& os, const std::basic_string<Ts...>& s) {
  return os << std::quoted(s);
}

template <class OStream, class T>
OStream& ostream_any_quoted(OStream& os, const T& t) {
  return ostream_any(os, t);
}

template <class... Ts, class T>
std::basic_ostream<Ts...>& ostream_metadata(std::basic_ostream<Ts...>& os, const T& t,
                                            const char* prefix = ", ") {
  std::streamsize count = 0;
  {
    auto g = make_count_guard(os, count);
    ostream_any(os, t);
  }
  if (!count) return os;
  os << prefix << "metadata=";
  return ostream_any_quoted(os, t);
}

template <class OStream>
void ostream_options(OStream& os, const unsigned bits) {
  bool first = true;
  os << ", options=";

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
  return os << "[" << i.lower() << ", " << i.upper() << ")";
}

template <class... Ts, class U>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const polymorphic_bin<U>& i) {
  if (i.is_discrete()) return os << static_cast<double>(i);
  return os << "[" << i.lower() << ", " << i.upper() << ")";
}

namespace transform {
template <class... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os, const id&) {
  return os;
}

template <class... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os, const log&) {
  return os << "transform::log{}";
}

template <class... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os, const sqrt&) {
  return os << "transform::sqrt{}";
}

template <class... Ts>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os, const pow& p) {
  return os << "transform::pow{" << p.power << "}";
}
} // namespace transform

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const regular<Us...>& a) {
  os << "regular(";
  const auto pos = os.tellp();
  os << a.transform();
  if (os.tellp() > pos) os << ", ";
  os << a.size() << ", " << a.value(0) << ", " << a.value(a.size());
  detail::ostream_metadata(os, a.metadata());
  detail::ostream_options(os, a.options());
  return os << ")";
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const integer<Us...>& a) {
  os << "integer(" << a.value(0) << ", " << a.value(a.size());
  detail::ostream_metadata(os, a.metadata());
  detail::ostream_options(os, a.options());
  return os << ")";
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const variable<Us...>& a) {
  os << "variable(" << a.value(0);
  for (index_type i = 1, n = a.size(); i <= n; ++i) { os << ", " << a.value(i); }
  detail::ostream_metadata(os, a.metadata());
  detail::ostream_options(os, a.options());
  return os << ")";
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const category<Us...>& a) {
  os << "category(";
  for (index_type i = 0, n = a.size(); i < n; ++i) {
    detail::ostream_any_quoted(os, a.value(i));
    os << (i == (a.size() - 1) ? "" : ", ");
  }
  detail::ostream_metadata(os, a.metadata());
  detail::ostream_options(os, a.options());
  return os << ")";
}

template <class... Ts, class M>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const boolean<M>& a) {
  os << "boolean(";
  detail::ostream_metadata(os, a.metadata(), "");
  return os << ")";
}

template <class... Ts, class... Us>
std::basic_ostream<Ts...>& operator<<(std::basic_ostream<Ts...>& os,
                                      const variant<Us...>& v) {
  visit([&os](const auto& x) { detail::ostream_any(os, x); }, v);
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