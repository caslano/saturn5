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
Fmy0I4crKVmOQr/YXNWfaUYFh1w/F1dX2mLPg3+CHhzK0yl6m1FNw9kccVmY5AcvTheQV4sSdcxlDbxkC0Wwfdq17wyA1izvuUxDPjA+u5c1+wTJ+XCd86rcx4CHA7HFltl36J+lH+mfRWYwx1VE1DTvpMR2oZfegbwYkImhG8jrmnkf6NA3q/qnKKNboOdTd7JuBxB2iww9zTBjJw3cX6LM7u67OpWG7kl3wPbVobITZD6NE/aTDpt7NYs3fhKOMK/0lEdhirU9cc7kmOfo5+OrTr5H8usUgxx3eM97gWcJ7+u1+07G9Ava4ZYdAVrdvFtayspPdBvSC3rcqiW07C5K4Ft/T55np8xvIFKtYQLjjbEBQbccHZePlaJuy7EK+c7PVLW7AEK/R8tas9GAp1AdbZRm9o90/afazkvdZj0OTaS/fzF/mBX6edOF2iI00PZOJGQ2nTz+UO3Ge+AtoohIgXHb5QeTB4jLOMmftNe5TSGpJoMGccvuIjzTb/TkK2pG2Wrup1qWihzyL+N8ml8Y9OIbzJyKxf4QAyMNia9uD3+PRMBYEc+5bPf191BTvXuIWPIi/pXVk8AuIXJoghMQuoD2C9xJgTjAGNIRSP+ZaVqF/amsaJ0BSnNWIDRthGx9sJMVREuJn9b0RaS0UEzd6QZKVKlEvK6UVypWggdFPyvysxFzf1Sv1MSw1pY3yheTVCCy8098CcX8
*/