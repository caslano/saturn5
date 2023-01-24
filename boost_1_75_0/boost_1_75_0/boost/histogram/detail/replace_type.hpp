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
Q/AvrX6zbMBwQGNN+DetPgq1AM4WTTxvoz9LM/smvGr19ZYDhL9q9c2xv2n1po6jg8rLnDyDv2l1t3WJPLsAr7mD6GRv0aqy+kR7zovtTGWCmy3v2rKnO6sYiQXHIVS7/dabfmH3cG1ATjI2nJ5yKx1Vy0A2A7uOQPGZOY2X60wmy/VvxFb8evp6La0Vu5GkBD6x4mbfIlSsWwaC95IGYQQ+OqhT30Uzr+bY3G9SBYT+itWb3YQvfr5i9cXaIb9JV4HmNxMGvpQFQ+LKw0IXkAW2VroGt1tjbhZ0H7cPjf5SEwiOWe0irk05bTf+Gp/e6lMdDEf7ax2PWSRAFO6HFZ7lniITuJPclLpKkE1o5QYd2Bx0xm6IF8NEYPk51iZK0Zxj6J8FmB+tLUk42fwDRwVE8TN4FPS/dikODlEJ/kkubY3p1y2j3pQlAiJInHDFXr8ssyyKNHUkmI42kmJap8Kp7ZgrmqMvjEj+K1Zve8XqpoSikg8mkwEkSlOrR2SvWH267ZDSN52tqxRqgZQQPy3t3QSUpxiQaKOBnJSG8UGzL3+IMQvvTL7NS3tuMerduGJ98vJFFuoJmgmaDpp9GH1yXoN5jPfCoGt2ezAtpr9idegIhejRpd9JyuYodDeeCQZm3KcQe8bdgQnerCl/3bgOdBmG3ZXPfTkwKa2focvdjW/XecixWlIU9fjepNcmrg+omua11W/AOGVx
*/