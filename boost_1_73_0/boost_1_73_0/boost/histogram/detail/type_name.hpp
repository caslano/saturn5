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
f7dI7zTL51f9hGopPPLtVj+t26nvxIVq2hJtZvtj/kItTe7dt1AS8L3RfIRcCHqm44Rbe/I0BSogAkq5EgCyw3t6cJ9IISK0DKlDD9aBbckk49ixwgNYTseiC8X7H3fL60yfzdzAtreW3EJIWeRxzBf7l8z9jRVGfjLdBDHmQ+s/1q1CN/pRObS/VDlkIKiOfrJcHS0mQmHuy0KeaHBUCWc1Aiuzw0rzlIuzLlLYr7tttaZMmpV+Wm5hJstDxH4=
*/