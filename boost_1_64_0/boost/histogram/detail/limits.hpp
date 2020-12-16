// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LIMITS_HPP
#define BOOST_HISTOGRAM_DETAIL_LIMITS_HPP

#include <limits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr T lowest() {
  return std::numeric_limits<T>::lowest();
}

template <>
constexpr double lowest() {
  return -std::numeric_limits<double>::infinity();
}

template <>
constexpr float lowest() {
  return -std::numeric_limits<float>::infinity();
}

template <class T>
constexpr T highest() {
  return (std::numeric_limits<T>::max)();
}

template <>
constexpr double highest() {
  return std::numeric_limits<double>::infinity();
}

template <>
constexpr float highest() {
  return std::numeric_limits<float>::infinity();
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* limits.hpp
L7mKl7SuvDiJl1hTD0ubaycqdhv4WRX7/dMD7+O8My8ZljOuXXkkxE0JWDnKBdKSaTno2p5HgtOswxQvXCquHXkkOI0KRvW+h+WWhDQPQqwAVCixpixLGxgErAsvDsmLvTtenJKX9G54UfJi646XYuIlPcELSEuYkl0w1F255EteenTHS7bkJVXxYgBKDEbAXldecomX1O55KfiQOkKzZllqzszYSfwwL1Pe9/yA876f5Bolk7GL+AFhCVP9C8mLPQO9HekBCsa8sCxt7pGxw7IX9LYkYOXgZQe36YxtxI8CUKFAbC1nwBwxlEGlguwrsFPxYuvKS5HipVdXXqoUL5ldeSlRvPSQvIC0Aav9kHIpVbz06sqLQ/EC6c1APZAmZgArqJIyuI+JQmkgxjJ2NPyEoK5tmLXcwpXVQk10J6q6bU8UYeDtbdeOhof0NLKRoWWYKU0mdatnFD+UCMra8hLy5tqGhBeQbK5q5AjbaZ86Fktdtfkv2jfdlp10AzMi3UNMamSPhLOFq5oI5pqMSZXNsgcchzCBnS+LzZZBwZiKubYh1RmqxNKNErPQOmv+qmZKQpVZOvoekt1GDoSwUN+TwX0PFVzGrlVbCMIlRzLRXf3pUYtU/dlV/SVgFYobu+ImActRvPRQ9ZeAFav6S1P1l4AVKF7SOvPCRa8KpQsvDuIFUo1+tw0dZAdeDFnK6spLleIlqysvpYqXzK68OKlPRosnPoz2nr/nhlmyvfM4hQF5m2rvClYh+55eyX2PgpXKvsee3A8qWL4+bqp+UAKk9j9Z8pLZHS/FxIute15yJS/p3fFSJXnJ6I6Xkk68gAsDli15SeuOFwfxktk9L07JS5riRQGoEwRf6JG1Xd3xUi55sXfHS63kpVd3vBR1p9ucGLPgDsqD0ifSDX3CgOUqfSLN0CcMWK0aw+3GGG7ASiUvJJ97eQBnAFfsMfCFOmJ20J7bOvBSonhJ7cpLQTd6loKVd6PbKFhFNzqfgjm60W0UzKl46dGVlyIpL1nI38EOjEAvR8dCvIDFrrxMVrz06spLjuIlrTMvPEcgMWJeDL28ZfEdn6I8KF3YbujCBqxA6cI9DF3YgOUovdxm6OUGrBa8QGQhL0ovZwBPENCxyHFzJ+vkHXipULxkdeUlW/GS2pWXyYqXrK685CpeEnMnA+ZU5ZLetVyKFC+ZOi+Y5M137cR8MkAl2vA1wqOhh4aLdA0LGpZXwfCuhqcIwEJ1GsNZAPxgXAYL2y3teUiup6IvxVlDFNJ2jhONnas2EwSorAswfeiPLxNv21ZtYdgulvMdmFi+EYvBSJpWolos85GXVkxB95PS9XYshrUcCy1lvKaddr1PqvQhGm/PWJYh3XbwY3lXa3O94zpBfWIIdQkzQOqFj5G6ttf1kmU69wegnon508uubVyQO2KxHmAFwzSIK7oORTfLoIt8vUbt7BBWykAelEG3wNKunaBZ6rtUBiAOukWgi+VBtB+dMq1BgnYx0aZhKZXzDj0hxKVe4jpu2QHC4MOy3XUsSpIGPxRai+UENInJGFulSt3uelfb6zqNqCBcqu2Ui3S98BPAYuQuXo4sxzdACg4iQp+RRz+gcITAvxx7DpFkUTvEOim+CyAA06MzrMBx02oYxCKWYdkRBbrWGp1hQ/gMmvdDbqCyWGzaCSxtARdczojWOjS5HhydkRktxarymt+1yD2dj/r82v8////8//P/z/8//5zPxlv4/O8DyfZ9c2l7cM0m37O/wzFw+3g6CsOWWQvgg3yx8tvQu24OzYNdL2Dbk8JuoRtZQkDNxGk4Z/R4HI9ON25u/To/5gTnusWQecfj+tIz/ILgkrE5iH63jH4=
*/