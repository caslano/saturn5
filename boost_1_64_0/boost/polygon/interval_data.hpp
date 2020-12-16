// Boost.Polygon library interval_data.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_DATA_HPP
#define BOOST_POLYGON_INTERVAL_DATA_HPP

#include "isotropy.hpp"
#include "interval_concept.hpp"

namespace boost {
namespace polygon {

template <typename T>
class interval_data {
 public:
  typedef T coordinate_type;

  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}

  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }

  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }

  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }

  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }

  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }

  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }

  coordinate_type low() const {
    return coords_[0];
  }

  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }

  coordinate_type high() const {
    return coords_[1];
  }

  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }

  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }

  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }

  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }

  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }

  bool operator>(const interval_data& that) const {
    return that < *this;
  }

  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

 private:
  coordinate_type coords_[2];
};

template <typename CType>
struct geometry_concept< interval_data<CType> > {
  typedef interval_concept type;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_INTERVAL_DATA_HPP

/* interval_data.hpp
XGhdwrE8g1gXOWp5Hnw9SL9G3fXQX/LPKGmecDltwgfnYnelDdrmb4hLNQefSEuPmEBUkLRQY3KoqZenlIfrr+pH88/ZlIftpIOpP6E3OZcnfnsfLqiRTVRqqvS/ljqS+Ul5zf15ydj0/dbd33/v4ct3+ft1vktfflM93+G7Mn40W5yEijT1QwykUoMp0Ga+t8yy9kPMl+nV+C987+lr6veu9lW/KOP3lv6pP8n3vr62dch1btMnhD+Ww2BLHS6xqUOlaE4qUerwfuuUentkmSl/Q3JSlOl78WX3r8eKmnokc+rE2tfzGsPikqx9PVcqbUO+51vjJKgxjc6Y+4kTb8vaj1PbntpatuuH5D39pHKkvaT+1EXWMrUuiNpo2agKjilTXrtc8dby810pn13sHunjLcsj7cCmL/EqKV+EbG9hpAHK9r/cUr4/ts+JZqw0u22s9MOOsT6InckFZJs8ozJCDeHG8NAQZWc+PHjIsF7Krsi00y+4L7N2Ge9IfrnSHvfjQGXfquYn/YPVhVRah2tt8NpK2zZ4eKVdG9Rpb7fu0968pb0N9pV9ZGw4UfP01/N1tc3ZLu+c0o770CClzT1nWd4/tj+X/r1O9+faGH1eElv/KVnXs0jDKUuuuSy2+3IX1qulDEN9pf3b7MslRoBOe1fjXz7iGDPwceaVsspUnoRYc3Mb3G1QLyWmRKHi+CnrLCHWNr+SZRzj9o1U1oVOfnFJaewNC5+fpQ6UZTbY1X+mTv7jmS5HJ3+CYLqc9yjmERudpOY9lu+RfNfGKClZ1jHvMMbL08mbNp0aFzXpgerbUoZW/NFgt76zysqUUoaapAimyzeX4YG2g4qaNigxHwo4t5G45O6O9bGuCmV73lyWeG3bI8BRYepCjgc2bYGYDTbrw+juGGs3nZ1DV8f81VC7rpTBJh6ou+P29Yw3+x+9PNITC5y3ZfnmezvGDk4o51ifa6jPFJ28CIJa6O25vF0c1Oc9HOKgquv2ejn9dZulVxYCoT5IOdR1qxNjOKO8Y/4GZTvXyV8bYvhBymE5jzrjqR9j+I5OWRax/vJ0yqIESy1MDGnagW6sVG0bDK7g2M7bKLFabfJXm3iBeWvjsO6v4Ni+l3jzn9XaeRcuvu9iWSZtPv4ejvk8puwrbPOhWbueT6BOfOZNHo7rqh35dLXJp/AxhMnLZtsp5uWw7ajL6ufpWIb2lCHMpgyFix9M/nbnB47xgxd66tdxpm2+abFx0cbCbCd69Vy6ouMyLmO9Z9vkVfjYwYudbw/qfnJaRcflfFKJF6TmbQhPiiIKGkfhyORUg9J6C1OGaVVleTW/449IfPyyZFgOH8Zo5Teg5Mm1GM79zD//CE/EqXDBMXjtzj/VZQ4xxYiNV2Mn1inJsQEt59LK+iCsbGq4Kbs0c8wmGS552/1ucvxN563GhJJpQiOJEmeN9RRpmZf5spP6XrR8NRZdCc/Miub3BoxWnsHjYRiQ+FV8lHzSQpXLJA6xETO8pO3I7xdPjFX27esc65Jf0Ep2Bb5Hw1KXUj6pS7Xu1LqU5bepnyTN7xE/xk+xu4ZzprL8vispv+9wAuX1yFbLq1yE1K79AuPyKr+tWqxXf1vptwXNtaaKmvfbyctUpK4d1/t5hmljol21WR/2bUE/Pu5JmS9tIjU9zRhlUNufs7Yh1xQmuam/5aQdq7EN6/B3FjY51e733UKJ4X9IflPlkhKo35QNav2aapZGEWCuXuV7we+3KaBO9doE9WJ33UizHNoy+0ls/JayDwqwlHmjQ5lbaMpc4Ll4YcusbadHpUyHpR7fJSUp25VdmSITosLNl/sKfj+NpTzSnhxjIrIf8CffI6T5fL8=
*/