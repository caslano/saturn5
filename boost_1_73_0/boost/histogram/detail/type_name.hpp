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
5aolI3GVIg9FCnTHbOkDf7kZy4nWjeSef/6ONNPTUV1yfjtH+FXCf6vFRvujBWJUFrSOVA7k2mhfipxaikEnPIySzvDJ1Rk6uZb/Lv/kusNjJ9cM9SjWL0bqPaZXrnFiXli+Ts+35KTk3XEXQoDGfOlLsnreaXLcvZ/cJY1PZ34vQcQSGPNXySRN5LVLUETpDKSuw3N4lGksHkGolHzytyrmVg8RV/zm+MnmgyJnFfs/SKLM
*/