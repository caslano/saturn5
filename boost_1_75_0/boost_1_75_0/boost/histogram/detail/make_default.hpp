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
AyrMKTbUjbrZQSvI+p4f+2Mod2cuNttuYBUhHXj+o+fxHU3tqC53SGfzNyDiWD/EuQtU1INdWLuY/UmObIVIiuT7kgupL11WEdq0IctIRb9g4Kix0lVnpxKUVdLvHHgmshHcWjn9GywPHk0qNMpTFZA/OGSHMu77Yh7PTz8eLqqon99Q5G7kYiblb+DXDh4Fg/XAqyWihkqmiI57YSZ7oF8TG/l0JjpcUJEZ28N8ML4wi6kimMNXahfwy89JQjDw5SrsJdNo/ZIHLISV2orA2SIN9qpQBEtUZtzgfT064f7kEZtxJXhf9y0EnazFCBYJa+sTzVG38Jza+AqPEVE2+rIbmBv4acUArAwWUuuWIf0I5fJPh4V2Sfzx5buprNCgJL7BiwBMoO0hSt5qFNjjlA/bIM9pqnt2FEzxp5Uu6X349s4crUMtuK3540Tw1AOHL1ZTAE643ZrX7OCTGYzDaMFrwqsqbnbi0Q1Fxb6CJQcR9zVDj6BQ6GBU4MkgBr/sik/2gAuyBY0jo4Th/bs4NZW5n2E+ioZ1LJ9FB2rf2h6ctArRpO8wEjjMW6Hw+lmetygZN3I5/MoeZjdk/kzYD6ovc+dNYdmFrs1MS5Djsv11xYrN/NJgNZeiI9lulOCqhqhEVpD6DZVtzIOUaWtbpgzF6G5SY37t2vT0mHXQjvqS1hD5uGXdjNFOdkjXvUv7PB7LnYm0ySvCa6qK
*/