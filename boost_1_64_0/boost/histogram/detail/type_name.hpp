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
z4ohwNB8iBDo/m/yqbTLlJEIelA1EYkdOwXlh+WnuYHD2upXFAWzkJTFCZVaq4lcYD4X/WGdTlk4PHxKHB5mnzHq2DT4KwLG1+BKrPobze5GwI1ZbJk1SZEC4NLBCPK+Q6O2SWf3GG4ygjtyy3ZNYHgLRo6jPdOB29dNHWQikEjQxTHB/tm16qmM8emvzwO7Eu3xTGP0fyQ2XN5zimscD4vskmkTQS6icZUBDVl02OHHGIxm2UfrQeZhGNGJZL7hEu+S29dSeaqsQLyY4JMSbphkYYbKc5R9VsaSC+FOMZC0aXUBz+zPk40icSYS/yolQHMhqaOfhUIanWJSIUsakgl8T6o2ldUVY95xLH7KTe0e5t1jKobd4iX9z0Y/fxpfvwhDBdOV/SOtyw8wrtJrHeO1WQXleR6BJ4NuYiDTSG5RRVi+EFkV7imbkV7yihIpqdbtFr2RKmumFnswcSyhEl3xanBqX0jc3tHctspaYBAH77Nhkqg/cNNC4vvS5ZcWvG9MKoZwArDKnMqWcNGeBds01a7sgOtugi4LMeecXoSHjGk2AFY/M4DCTg==
*/