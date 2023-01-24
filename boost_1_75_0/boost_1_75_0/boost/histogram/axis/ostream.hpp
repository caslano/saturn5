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
gLu5ki18b/BIbu7ld+jstA6LP/A5eqYdfmToqLSsenG11NVb+OTB5eBj5IJvtSak592QuSMO7CbsynybOJP1tyzhmrwFSW4JIP47zBededwNfksSFDRS4nOS9eh1xMvWGdGZg+3RaA0JC8rcSPzgD4fhFinLD2m0NkGTau9aijUYom611hpDtrYCOqPVJkuUNVh8K9HWOBYmOBZG8gZ8SLqt71iNQ8sIoSEAG5E1RszWdXrjBDRMp/WSgig8sa83EPXDxiD1ME79Efte0hsrozFFeHP4lAYcETaPTSUWA9Qd/Y1ZHKRgeD/v6d265w691nM2XOLuo20GwwV84LeJE2v/7g0FYFRTF+5Zd5SALDCoiWHqcmoud0Y6Yi43clbUNQIS1PVX1wyKgBfIY29eUJbXL/5xjscb30mInx9ulfEVi18mNlyFyS89B4NTsWjLZmaK/ftdd1D2AZxCdvfvI6WGnAzMdAB6dbcEgJXV3jMeEnIZTLb006SV3gKZpPee9ZVXgRgCgPPm57Drb6X0Ijy5CoQKbRWkkr/kOp5+62eEitQEvNLftBzz3et5R+uXcP9DQqk0F5ZonmjZiu3QcCyfv6Zzz5/FbdQmJZgHzSObXbvPvTcotjwkWf6NqZEeDOIWneycfhXOAphpsRDJgzLbTKW1E1bqzvdWhlSdLn5R5cC1JDKF01KgCQtH9dJ12E4yJJS1fLj4UHLz
*/