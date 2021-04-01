// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_AT_HPP
#define BOOST_HISTOGRAM_DETAIL_AT_HPP

#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class A, class... Us>
optional_index at(const A& axes, const std::tuple<Us...>& args) noexcept {
  optional_index idx{0}; // offset not used by linearize_index
  mp11::mp_for_each<mp11::mp_iota_c<sizeof...(Us)>>(
      [&, stride = static_cast<std::size_t>(1)](auto i) mutable {
        stride *= linearize_index(idx, stride, axis_get<i>(axes),
                                  static_cast<axis::index_type>(std::get<i>(args)));
      });
  return idx;
}

template <class A, class U>
optional_index at(const A& axes, const U& args) noexcept {
  optional_index idx{0};
  using std::begin;
  for_each_axis(axes, [&, it = begin(args),
                       stride = static_cast<std::size_t>(1)](const auto& a) mutable {
    stride *= linearize_index(idx, stride, a, static_cast<axis::index_type>(*it++));
  });
  return idx;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* at.hpp
p2odlk38VDLNIpjgK2Yzlov6NLEWVXVHMDKuIh7kuoSUX1Y5KQmeZhLyuHKpT3ycH9OluTvQNz0N4/ETvCTs3KKdY4TDUywahQd+vmkkr/2nqX2YtqP+BVR7huIyD7DyxE47VgCTVbQmhhji0gqLqDoBJbUlHvrkDgwu8QjWyQxDUyz/Ayow1yIDlGDlr5d6xI4BiFofrem0TYi9NRijJKzh8r2z3qjDIFo5d9zxOK5PHQ3X95oekHhbylGpX9sYEAE6qUJ0Y1B2I+1CUv+X0MMIdqutJx+HZtR+RIWf0EAddBxCrigOLyXkjWdMPQl24FC+dv6VyjTj4bLeWRDMy6xig5unQfY6zc7IdGfBGjYmUv0vvIIfwz/uELVTvrB/NHf0UAcYfpo0FkSBwQOii5p3+GDB45DDMEau3h876Za6Pbi44XutlxwZnm6Ni7fBKoZpMf3xlTXdDWyQ9NKRDOa+efVt3xkqNeys2gY4vWOy4C3mMuC50I8zRfNpEiLNz5mCu48wwNunWCQGpRddU9kxqPgat7lTlyJ/hXjJXHDlV8JVTi68jihrCw==
*/