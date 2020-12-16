/* Boost interval/compare/lexicographic.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace lexicographic {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() < y.upper());
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
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() <= y.upper());
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  return xl < y || (xl == y && x.upper() <= y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() > y.upper());
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  return xl > y || (xl == y && x.upper() > y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() >= y.upper());
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() == y.lower() && x.upper() == y.upper();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.lower() || x.upper() != y.upper();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y || x.upper() != y;
}

} // namespace lexicographic
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP

/* lexicographic.hpp
8Uv3HnQ+w+hcmFVcOqSh8xnMhtmRw2NW0RqDuTP7/oOlN737wjyZjYnqfpDWGMyJWee27Sh+2TA/ZjO8f59Ie4BwzzMPeu6g8cFqMHuRE/yW4l7NXKVlFp1VtoviDuPju7B28CHaN2HmzCYHtO5HOQHz5P2ccGUZ1XmYB7NW/R6eojoPs2Km+vZhLM0LzIIM16E5feh3ikJfNs1vOpDex2C1FEvEVd3mh0DKCZgdM83mJ7RuT8NcmfX8udMZqj0wR2Zbho+h+KlMzFVqZh1z8npSLsF4u6Yr29rTfAr293rzYDqbwtyZZQye7EbvRzAPZpZx1o5UB2EuzC4Pee9B51YYH59j8Hs6g+0S+jLRd+V6mheYF7O1i91P0h4H82F2elQ+xcjNtGo/s/6w86e1AnNmVnpzxzE6Swl2+dmkv+hsCuPj26cqpXU7X7DrHwrW0R4A43FfM2W/L60jmIZZ//JsWrcnYJbM/C/tOkD7GCxMsRa4prcrcqX93cxgzXG9tGD1Xho77PNKi49PwPVuyGRP2jdhbZmdOvSKxq4yN1d1Ztbe8jOKbSqsC7Py3kcsqZ8wZY+rtC+uhNFZ+BbMjpnF0MfBFFvWrhmu4X5zHakvFpgzZluqfUb7kRbG29mOPk/z4gNzZXbNtnoq5bzQ7mrtdqOohsCsmDluHJFAtVWwqztfPqJ9BaZjlnYki3IwA+bO7OTM5HG0rwh2cOqjfVRDYA7MSlzqD6a5htkzS1rybBGdFWHVmd1T5WTS+dqyqj3+9v1mqq2CjV/7+E86T8B4Pw/dsqhBa0Ww3JMxFPdsGI/D7L4ve9M5GWbHLGKI5xUaO8yR2YMvB7yn71lCP3eMPxlA36EF238+347OS2rsHcwaXcg11EGYG7MXbzbtp7jDeGzr3Ht7hsYOc2L2am1aAe0PQrugGVf+oPUH8+axPewzlb6DCdbSu7sn7Q/CGBz6bUmi2FpVnbPwiWEraD3AtHzOVhXOprOUYHatvqW9PxHGc3BuxFXKwWSYE+/nlc6v6buG0G5snU930rwIz7u+eSU9Lw/Gx2fjMP055YQwvm6fzY6nnBDMaozrXDqbCn1ZGXegGtUX66ox+tfexdQXNxgfn0Vw/CV6B4J58rxu25r62UG4Z0WvHjT2VOGennPe0Tk5E1aD59L1KY1pX4HxMUwNuvOY5gVmz+xA0TM11QnBzvjfofpSKtwzyv9ZGq0jmB2zW21XtqM8s6laP7Mft+9McwbjcRj1ez0PmjPB9mg3WFCewfh8jluWrKM5E9pdT+3pRnMG4/M5+f3063QOEfrZ2WfpYZpP4Z67Hoyj+lko3PPMoeIRdN6F8XlZ0VI7ldYmTMvbjXpu+LPjwvNiv+pLsdVpquZLpwW/OlNNhvEYla2amk7fYgV7s7N+KZ1tYLyf3/yz4SjtVcLz3MI2ltFeBavOrO34mLVUs4R7Nlm4NpzeG2FuzAIiR76jc51g29sO7UhzBuMxandj7nTKQZg/M53mA70bBthWXSvOEw63pD0cxuelx7EsWg8pMBZbFPDm/6b3AKHdF3OLK+jMB+Px87absYS+BcFsmN08fjCDzruwUMWa4DqrzspfaOwwB+XPDsTjajZwaj7liy2d62BoN6JgLK0jO8wZMwfN1gaUE3aGdo1x9Qq7Y081mVkjXNuOLimn9cDsU1yvdO5hRt8u7Azji8M1+tJqK6qtgjWs2P+AxiDY3qDyjfS+Yo8xMJtVo4jWuxfMjtnylruH0nqA2TMrq2tymMYu3PPJHsdiqskwG97uUdQPlBOwMGYttYn0vTwHZqpYQ1zHNJpxlOoLLJRZiE+rmZTzMF9mtcur+9D3T5g3s6Byj0s=
*/