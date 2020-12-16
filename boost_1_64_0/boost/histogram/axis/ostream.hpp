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
1ll4SceLQW2eBaNbLpdZXlkmFkv82rqte9AzHq9qIXWZu4qGFW3Fqrb6a7gNxCe4ydyGHx45pDbI/bGFD1GZUG/N4oFM942IX69mRgJ26BJ3PhITIo705SEZG4LNAt1/fDvTfeQM4gfyHh7mDLP+oB19klybLgOfolUSe7fNZCf6DVZfIQPziBNWSH3ahvY5g5bDk4foyLUMITFzixXTs37Zr/8uOnYu8h5LRj8WS//c75PTj3GOf5AGbuWdyeh7YulDV8j0B6oPbcEY5ONATHs0mfrH0qckWX/OcfGxyLH9jmTqH0v/4vx99T+F7P/5gfjxUhDCzjqfdSkt2qr8Zw/FbxaNC182LJ+iPrVbne0/xfg0hWz5iQJrjEWS+U6U1m7q3EgBhkOEpbrCJgJBo5ApU83d9AOwwuVQbsr9zexB10bO0o0vJHi+ZvAhc46HCeSXZrnlutxPfxvTs+uSZ6uScf8P2z4O8akdeH93Y8e+Vb8DICKMOKqWminwTla70QyIZltIfvzerJRXVEirgkqMLj25qgVqYTsGziF+4sbbSkZfZtO+8eniLSfFpTftm99q5p/dZn4r579xf/mlv/VX75XGEcRk83EavNBbFNWiaHhCWtzBzqz4A57UH40Rm5g+A9mFGLCEjWTy67ZJe3PaEvPg1+v2iB1SRkJ0MQWfScG2Hb4s+L83Y7IppivFBJuzkGedGcMGIXR+yraDDo/3I08T+aYHFSiG6tAMuv8NyeVVJlRM4NKW9+OuAM/zZcH5AxKqLfUHqOWdF+vTELfSa5853IQ8fVEXASKALrdHHm958nLTQGWx2iQRM5it2KPKVhXnCkc8qS9ymQKyJUOh+DNjYt0qLTAOBHAgXHQD6qpEzuVMiaWIo97A9QbsMJgcxetWRTrz05YIe5WHnWofqzmKfAuJ/m8hSG/MhrZVdMGxDBYh0/VDlCXj7/EfXYL/ADLGI158hKPHiDuZwRTL8fez+Kf/uT9rCIOiJ1UdlMbemEvo9G3rM8f6nF64wqTexhZbeKxDr3epU9o6yNcA/DdG7GJ2HdP0JYuZIAqJpv2KpmfgV7xVyxFOCphgpYNKI62O1Wc6Vo9Iafw4vfEjZ6ftnb7Gm63xo+zgBnunr/kguLjuatPm9Dh5aUspiZLizRsTaL0j4mx7g7B4pEFW6qgj21V9E30ZCH7FUSYdKxrP0VHzY1HPyahcHTU5FnWfjMrTUUNiUctkVL6OytdR/gAJjBwM65QuZvBkPVdViSdvlZSmv1Xikhv4fOFYWrtIjlxAmMAstPExJsAy0P/TC4lqf2zgbh2DpA0l8ogrTXfGtBiNG4slm//TTXLHUpx8p7K0y8MD03gP+VAqDpcPQ0VH+VApLHhgQv/uDn6YKL68gwoONnBNDI9Yz7MNrNdU4f95IyDxQxot0DhoG8QC7/BH8BVm/rRw+RFhe3lT2H5eGTnlkqH2cLm9Kbje0SjsYfuisL0Cl1gcTB+XxeefINq41eawnRUV6iUz/oUHHm/97sPxfg+Ox9TG/7ibloFHsqrmi+vlgfzcnU1pgZk8Xb2LILr2mY7NByby7NYsg/o3LawM1gC6/1hW/TxqBp8eIm2WZajbfRpsosCjm3jAXRMHamEXM01flcb4xqStWuMqSVuTVygphFL8zAQg59spEPKVJ/lCmp6wG0eHNLvcrVDy7nXqOH+u49pjaEIUa35FC90tYhOdlZvjAAtp3GsPCaCi2ELinh8X+o92l58Gsg01Mevm975KRCPoT9ylhsyVBH19Ggq4JfhJmu25xl22/s87rn1SMwv+52U3L7rPSvgfAp33qVF2hgaSGwPSvNDPy5LuOs4eHzeWm7Y=
*/