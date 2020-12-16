/* Boost interval/compare/tribool.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/logic/tribool.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace tribool {

template<class T, class Policies1, class Policies2> inline
logic::tribool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower()) return true;
  if (x.lower() >= y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y) return true;
  if (x.lower() >= y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y.lower()) return true;
  if (x.lower() > y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y) return true;
  if (x.lower() > y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y.upper()) return true;
  if (x.upper() <= y.lower()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y) return true;
  if (x.upper() <= y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y.upper()) return true;
  if (x.upper() < y.lower()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y) return true;
  if (x.upper() < y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y.lower() && x.lower() == y.upper()) return true;
  if (x.upper() < y.lower() || x.lower() > y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y && x.lower() == y) return true;
  if (x.upper() < y || x.lower() > y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower() || x.lower() > y.upper()) return true;
  if (x.upper() == y.lower() && x.lower() == y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y || x.lower() > y) return true;
  if (x.upper() == y && x.lower() == y) return false;
  return logic::indeterminate;
}

} // namespace tribool
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP

/* tribool.hpp
9cbwu5Z682qE/GT2y6tRT/UWLJjNdKsGeouBmTPzHRvcWm9xMAtmJo4ZhXpLgJUo+63nx+cFv3bTW0Y8veNVWq+50d/oLQdmxaz57j06veXDbJjNm7Htvt52CDYn5PhQvRUK99T1+r2X3k7DbJkF75o/Sm/XYGpm9VcvjdDbfZg9sy2T6/6utwqYNbMbRR/c9aZuUvWe41/vpr7oYHwMgYe23NVbAIz3c/IksyyKEYw/r2F7R4pfvGAhr+1C9NYGFsHn5eydqXrLglkyi0k4tVlv82EOvJ9H5o+kGMHMmD2/NC9NbxuE8a2oO3mN3nYJ4wtzznyutyKYHbOtn6QV6e0CTMMsPHX8UloPgrXTtrfQ23NhDG+2PHxDMWqKszezf74+TGMPgDkz+/qXiGSaaxjvp/ppg2F66wDj8zlpyZ/z9NYN5sKsZOqGYr2lwXjurg/y3K+3TBifs9qvWj7UWzbMkdmf96bO1FsBLFf5/yn1wM8a3br8Pc31Z9SXSvNsazNab7dgWmbtYmNMaD5hVsxcnod/qjdVc4yd2dqhrVfTXMP4PZd/OrMd1SyYhpnJT1bZeguD8edtjpkarLdYmBOzB+6BvhQHoS+mXVYa4gCzZxaZ/uGA3obD7JitKQgrpHoGs2X2zd99ImitwHTMpvxht4vWA8yG39P9zFFaDzBXZjcujRmkt2KYA7PfooP2Uc4Lzzu0Tv0d1SVhXnZtbXKBak+LquOrM7ypL+U8jI/vXA9TilEMTM3MPLcx1c94mDWzjVvNx1HtEZ4X9/2nXfWWDHNkNr5WuA2tBxjPF6/2cSV6my08b+f7+La0r8D4XOfs+ecmxQEWzmz03cGptAfAeJ79oH1uTnuAMC+acUeb661ceN6U/q+bUc4nVr1nnYcba1McYDw/zx46u4rWA4zn57SiUEe9RcJcmM0yjWpMcw3z5OvhsushymuYO7MzvXwzKHdhPM/+iFSPoDoP4zF6nbSZYrQX5sPvOT5jJNUQGM+Xzm9aLtPbIxiP7dTt145QDWlp+JbnjutPnqnULqEl1YlK+7xLSXe9JcG0zHycd6TrLRUWzuz8lp6jaHywfOV5brj+Ne+KWm8prWgdVdrFCU/t9ZYOi2CW8roB5fyOVobfh7viZ+8vbulOuduG5qXSlh26c4NyF2bNbKFHzWvUT5gts2Znbnak5wntMtb801NvB4R258xUOXQmgmmYXX275RytB6Fd5pjv4ih+wvNKlg0fQOsBZses38BPntN6aIsYMXNdO2Y25TzMntkzS9N/U87DvJjVm7e+M8UdxsdQrc4bOocMEO55Nb1vJsUPxsfncDWpH8VIsOOb/S/rLRfGx3doUsJb2m9hhUrcXT725WJnK9pv29N3t0oba/9QqfPh48thpUoOOuPad/KJ23rTdKQ6UWmL1TNM9KaDWTH7euqdWL35wJyY+UyYuV1vsTAXZoNG5q3TWxIsnNnU0p019TYfVqD0U4fr76Vlrei7RifD+Jxw9by9oAO9A8EuKO0ccT2QffoyWWdaD5V2tGuDvfS7ecECyrv3pu+KMC2z1Xfmd6TvYDBHZne2/HyC3mFhDszuHk9oS++wgi2y+Y5+z1wOs2Y2c2zxcPqun4Q4MNNNOzeI3m9hEcxe2mvp+2AijN/z8zEL/Ok9Vbjnnnf+pfSeCjNjNvWe1Xb6VglzY7asx12a68wkQ211wPXAh18t6btpEq2xSqs5ra3hz3DArJiVze9H93wOc2bW7eGMXBr75zijMFvX49CX9I0Fxu/ZcfCFRfT7HFgYs56Hg/fR9xCYJbNN5a1+om+xMHNmYdeeXqHfI8AsmI0ddJLyM1Ow4b4/udPvGGCzlTk=
*/