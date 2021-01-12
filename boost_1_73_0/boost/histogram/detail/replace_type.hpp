// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_REPLACE_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_REPLACE_TYPE_HPP

#include <boost/core/use_default.hpp>
#include <string>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class From, class To>
using replace_type = std::conditional_t<std::is_same<T, From>::value, To, T>;

template <class T, class Default>
using replace_default = replace_type<T, boost::use_default, Default>;

template <class T>
using replace_cstring = replace_type<T, const char*, std::string>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* replace_type.hpp
6bZNPOo2kWHTRIaiw+ejI+n889GVRWY+2mJHxRtM3le7ebeOkNdj8qY25s6TPtTP1bpxhlvGXLeMmiRXV1PG/pA8EEL9b3bJILYuXztsAhudzj+BfSikE5h2Fibtb5EO7LBwqzw3N0XNdIva/1z+omaaorImQceTIeZCt4APPZefIM+PNcR8rcmyJtP+EbLsN1leki2iLlt05WOLLssWnS5bMGzYgiHbkixSfDOVH61ptiVb
*/