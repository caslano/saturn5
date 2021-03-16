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
oPTttCXXUaubTOyby/VsVu/mD9EhoZcP76bwHmsMR+NsTh9CQLFaxN7vFvoCgzg7ZPag/b0LBqqdpvFl21ikRRqelu1kYV22bL8qvWxNm+ReSsCi7CV4zNcusfE1UzX0qZtcZRrP+kjc06wo9/iElolmXEkaI77QEt9mLZYtSfRgm0goBKfdKYTuWlsm2dJGhTAdM0x0OGYwVU2XwmMjrMTQsDbiSERHFXW2ZNuiJx2Z7ETlG415mPFPBrnf1Ac=
*/