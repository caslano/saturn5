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
q0JUQNYopxr8d7QCIMKuPikkqecc3KlDdDupfw6Mvh3DsFoaCbnFGVUKhmUDhuhfJROvnMW6SNl1KM+dPjsD7TBwJehgvzDpxd09wlv4Bsl57Izn7XlkKP5Qix+6XOnTaSYK/5wDO+000I0y/UqEn2/WF9wCG4Yag+j8sKRYoZ1KVj7GLf4N8o8qpeFO3MN7aj6Z541Dz4yw67JVI57a4et5/A6cHN1sTo3GUzXN1XTAXSP85jHAwV8TymlMHqE3m5p4AzIaw3udhJH2Aoorm1FqCr5bW56FH4d+lL5NcZ6EBvVgkdmeJ0RKHbyahK7vwN61yj0IYjUWNZYvxdA1aqR7aY323Qj//vstxRA/U0NdxQiNh5CEQo23q6nSwwkEHSU5tKgLc9r5Ulc38n8djJ6j3BPDouusCc82LO4oihMXBoLX1mvpmjvl+pi/m9IZWPRrpRLzWyMJ4COb9bgQ0bNg9XFmG1RHc+58BXA+RY3toCg80x8x4x5Sm9/XH1VredowIY9YCUvjj8x3MwTXQ9oy+sWwugo16dgPWIeJcsqTtmNRumPDSEQ5fQ==
*/