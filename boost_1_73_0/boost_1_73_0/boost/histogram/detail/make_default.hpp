// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_MAKE_DEFAULT_HPP
#define BOOST_HISTOGRAM_DETAIL_MAKE_DEFAULT_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/static_if.hpp>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
auto make_default(const T& t) {
  return static_if<has_allocator<T>>([](const auto& t) { return T(t.get_allocator()); },
                                     [](const auto&) { return T{}; }, t);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* make_default.hpp
BjU5pCKFlcJSe7n5j8HZIrUVbVR35KipVDf8pJrKbpfcJGqvht9dUF1CWsFVlPlPfMO2JtF0CU9+18qLiK8/qy86UnC1aHl6CEBe1BGun8fyy974Kbx0U2abUib5qwf5zThfRQF6+6S5BakrTAYZtt5wqrzB5pMN6Iry0PfJ35NFblAh734gg2Bk9nz4eHr5QqVyLzACgxmBSRne8AUFmduKC5lbz96JIMUM37J2N8AIIFO4qA5UtilWq9APwty7vsWLl4ui7i2smhRib9sTwUJrJRho1/ukgWi89qr9YYrp6sB1V30cunoBV37LifNSteNtB/PdhmAXLvx16HCd1pBh+dG5fMfNT+cXTDlK8ZuLtqOLccCTKhXDn7ZsaBLGaleLEsM8tAfbQQ9AEBJE9tFpktY1LV1Z6UUjy8FFOPoWLiftWDe5vtVARkC0O3eNT89y8J0cv/yoEZbSt2fiuw+l+83sJh0c5NQe3+4ejrncJIveXafoWW/0umSg4U/uCPPdbKmxaPVq9i7PJluQy3mbTSPXaho2rndcnPtRx1CX9elbHvI19KHtcCcyGXK2E4XYtl2vGEixiM/jcF/1PTbW9L022PDbQ3fA1y7sJuBqoN8LfNW/sQBV1bqI8jb7+AWYwGMHHOT3Al/1
*/