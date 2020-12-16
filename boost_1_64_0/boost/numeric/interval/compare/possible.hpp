/* Boost interval/compare/possible.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace possible {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y.upper();
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y;
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper();
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y.lower();
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper() && x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y && x.upper() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.upper() || x.upper() != y.lower();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y || x.upper() != y;
}

} // namespace possible
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP

/* possible.hpp
VD+1eKdklnFy7WbKa5gfM5/8nz0ptjB/ZuGL23ajdQvjz8sb+pDyrAjmwqx3efb3dGaHVWe2b6hXX3rvcMCaZmb75EAonTVgzsyil5WOp3MWTMvs2zpBiyhGsAhm/Xz+eEhnBlg4s0Y/2d6leg0LYnbn6oiV9G4hWK+1OZ9RPx2RZ8zGrVoWTWsMxsf31WGr7ykOMN6XyNhF9B6eBePPa3th/DaqBYK12uk/mvZimCezRQcrvqC5dkK9ZrZEnVeN1grMlZnX0bdz6P0P5sMsdvTKXpTzgplsrOhOcw3jY6+ZdKAx1ToYj+3MmAE7KA5CuzqRHX6iGgLjsTUJ9phL+58O64/ZVr+OHnQugNXm6yG6pDft/bCazK7m/XyR3i1gPHfbN77+is5EMB6Hwp0V9J6jcq66bt+Fpsyjb3IwHveSbr5JNJ+wQGbHfO9Mo3cgoZ3rjAfx9N4Pi6+0+Epbtu6XIzQvLlXn7IlXXinlIKwus9OaSem0V8GcmKmONplL8YPxXOqzd+ImOkfCvJl94qEuoVoAi2ZWo6L8Jq0jV3y3YRYR4bWGfpcF43kddXm5CZ1DYPye+28sn0j9hPE4dN5k8Z5qq2DpFy2SqbbC+JwN7zqwHu0dblVr5Icr7wvoHQ/mwax8y4+/0bkAZs1rQZgD5VIWjOfgvKv+tAfsgPGciF0dQTlxC+bJa/K1kfsoB92r3nPo+sYFNAZYMLPEgno/0vsYjD8vo0vBScoJmCMzr4mPZ9Bcw1yZTbSc9yutaRjPF/vz42hPLYF58740KtDS3g/jObHy9MQulC8eVS37u6w6lC8wvjZ/7GRK+20aLITZjKtxQXR+gfkwO5mX25fWO6whs59GtDlI+61n1Toxwt6f+hIH433xn36Lat1wWKhin+CasH9XV9pvYW7Kua4Brue0M21ojXlSrau0ASm9/qC9ChbLzDOtdgC9o3shr5ktzbl3j/oC4/e8/8faR9QXwVZkprSg+MFSlT/3+fG5oRmph2gP8KbzUqU1TmzhRucewQ4sMaexF8DCmC08MovW0TVm9XGtyPtmGH3Lq2Gwergurzkzj3KCWQyuh5tlL6e1CUtQ5joK18WBE6dTnahB31QrzSZ6Ep0ZLsDMmLXefzSD5gVmz6yZbz0fihFstjJnkfjn+jUbjaNa7kvtKq3QXtudxg6zJcO1+xjKz0cwNbMPmwom0zsQzIbZmhutetJ7uB/OL8xcT29YR3kNs2LW223TInp3goUwa/jL2d1UB2GzlfmsjWvY1cm/0pr2o9+TVNovvw5pSmcUf4yd2Qr/XkXUF5g1szmXQndQX2BaZk9CZlP8YmHXlL5E4Pr3hKFb6KwfQO0qrV3sgT307gszZ5b3rv5BqpEwR2ZzJwc+pfoitLv5w7U4ei+GOTF7dTVgPL0jwKyZJdfbup/WH6wWsyH3TjtSDsKSlfGF43r+aYeplPM1Ke6V1nV5txE0PpiG2abzu61oT4WFMZu2aMCPtG5hzz8acjcMV58xS6KpLgVSDsKQd4NsLCmvYXbM3PukDqG1ArNidnzMFNoDSgVr+9SSYlsGG66so9CPtfxWj160HwVTOxhiazWf1sMOmDWzX7u+2EVjgNkwc3teW021QGiXW//ONhqDYN+8bHWMxgCrxczr8MxCyusQzDWzZb73F9C7DCxTmeuP7TOauSyn9R5C66jSwo9t6ETnF5gls4Pvx7+j9Se0cxvXLIfWX62qdujHJv3pXRtmx019rSa9P8BqKxaCa+Pt8xpQnsEiFAvG9f2GYns6TzCriavzimDK3SJmAbim9N3WmMYAy68GQ877f5z7xo/3UU6EUQ2ptMXfBsfT+MKx3pltX5E=
*/