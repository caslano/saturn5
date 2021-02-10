// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TYPE_NAME_HPP
#define BOOST_HISTOGRAM_DETAIL_TYPE_NAME_HPP

#include <boost/core/typeinfo.hpp>
#include <boost/type.hpp>
#include <string>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
std::string type_name_impl(boost::type<T>) {
  return boost::core::demangled_name(BOOST_CORE_TYPEID(T));
}

template <class T>
std::string type_name_impl(boost::type<const T>) {
  return type_name_impl(boost::type<T>{}) + " const";
}

template <class T>
std::string type_name_impl(boost::type<T&>) {
  return type_name_impl(boost::type<T>{}) + " &";
}

template <class T>
std::string type_name_impl(boost::type<T&&>) {
  return type_name_impl(boost::type<T>{}) + " &&";
}

template <class T>
std::string type_name() {
  return type_name_impl(boost::type<T>{});
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* type_name.hpp
4V5Dvres644DHWnOM8W39eAQacwf0oy7wRhCSO+OzVijMUE+LuBJrTS0uDykGy7W4WaTfNFckqDlZGmC+5ME4eVEsXoj5ewnCQqEAoLchrKcSXnvwCC4vmT75ZlnUjbHoPQwEWX5PcGR4giXenJEC4fz7kZwsIXGQok288bq8fIlytHQdiVij81PtbYQGSCcG+uPLeXsqtMS9lEuGjgr6aujbFZIp3FjXZ89pZ83qetMa5ldMT5M1+HlRD1heqMJq5AyvVg9rBMdbbBf/F4F8wO5JsYOJb4dRD0xuFUKRchYkrH6hm+oE9UuAVInqSMjwapOI+u0AkydtDMZzVR3W6PC+rxZ//YlltbmhJWniHMTupa07mDqVDYSoFQNIR3BgelU+bKIThmQapHy01KKjFpylSeJ5xYTDi/jQvbpMdpO41MkzQnZ9RW4bJnJYjPjtN8PfKe++ZLDrCVuCY5r/l3dCaZjSH1TvQB0GwMaGspBA6mwQzKmT9Pt7BF+0uSYctd+jXO2BZiR5dU6viqCeeqJFuJoxliEUWijo/AShVG05D9pbhQmELMa1iqek8fxa24CEhjIeHGVj2vpGJR6KEXiPqAxKGfMq9M4t1AUmFaMVSwZyzFth00eN8416byjWC02RUx83myXQjs0
*/