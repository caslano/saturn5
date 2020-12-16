/* Boost interval/compare/certain.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace certain {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower();
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y;
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y.lower();
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y.upper();
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y.upper();
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
  return x.upper() == y.lower() && x.lower() == y.upper();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() == y && x.lower() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower() || x.lower() > y.upper();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y || x.lower() > y;
}

} // namespace certain
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP

/* certain.hpp
IMwtbzzPE5YwY2HOr17ZsYbAZD/Td3ewZ52AGQrLN60SxjoBMxKWuK4X8yVYaXdnTGYy67Vidju2rGYNgcmxm7c5yFrQBaYvzKF6gTXzWhnfgX5+wfwWpNjL2pufM3dhesK8D2oucp9W+nKi+G6eWxcpY7jdz5axXaX00/uEixXPfDAzYQ0/tezHczJM5sTZ69mF3+SUvsRWbsz5zFHinpyw6Cr3VCVGpZtd0WOe4Z9aC2tu6GLMs+JV7TGErmzKs4YGZi4s6mqrjswlmOxnRkbCB+YSTMahfCWddbyTKO0mvL7BGIXArIR5LU7hWukI8xMWs3eLEeuLsCg894V9PsQ7OqyosKDDbTSca5hGWKvl/Qrv7zBzYZXSs3N4LoAZCbvtNsmQ9xWYvrBhBs1TuaaVdjXz3IZwTV/T7otT1yMWvPfDTIWF9NnB3PWFyX4ObDq/OecaZiFszLBBRXmmVexWEestXH8w2c/uU7M9edaHyfF1yzL+wfUHMxG2be+obK4/xWase/SR+ybMQc7Z+4kneJ+G6Ql7kV2dOZgCk7GtOz+AdXAHzFiYbvSi9azlMGthrpF9+JvXxbx0wrPG3qETGXeYsbB+NdYGM+4wR2GnhtzgGrO8rm03Lgbe5VqB2QnTrXmmDNcDzEbYpnM2XowRzErY67RznowDzEVYqaDevVjPYO7CZh8YWIf3DlhxYf5HT/zmWQrmJGz09LEurCE3tOes/rG7rsxdmBzDmaZtLvBsA7OV83kweBbHDnMVNmrZ+aLMQcUu+OcksBbALGX87u17yJoMk3Od3anOOZ7PYHJ8+R1/uLO2KmNweTaY+9hXmLWwI8tS7zDuN7E2hW0cf5Vx94TJdofj75hw3SrtXnT+0p7zApNjWDN14BSevWEaYQX9Sk1nTsDkXE/bYvWM6w/mJHOp1orWXGNKXzwHdTjDdQSTcTg307AB50xpd/KsKddKvtLPy9PG8Y6uc0t7fHmPbg7inqPY6A+96nHOYM7CVvoOGcYzO0yOb+bXLR143lV+85+sOTFcKzAHmRPVR1xmfVEs6H0/zmc2zFHYg+imZVhDYDLuaZ1+enHsOdq5G/4w4gHvxYp999iiyz0AJvtSZMkU3i3qw+T4AqsFzWQNgcm8vtbkdEXOC8xSml7TS8wXmBzD/RvNornGlN+cedbhB/MFZiVsRZu97OdlmMzP64fSCvdbmIsw0z07m3DfvK39vikPwsy4xmAyDl2qxjEHa8HknEXWSznGfIHJfpadtWs8aw9Mzmezxp/r8w6kvO+svVNvzotiV1p+L8LaA3MT9unwtsJvo8r4Wu3f1obnCWUM804sr8S6e0c7fhWr+Ttxz4E5CSu30oh1MBRmL8xgU7u9PHvDZBwqtK1XmmOHuQp7tGzmR9YQxeZkT2jJuMPk+CbdHhbMuMOKC1t94zrzxfau9nyOaZSZwn0FJmPUefXKmxwfzExY924+iTxjwuS8RFfZU/j3McVyy4z35z0AJsf3OrjRd8YWJudz+oqp/LZ2D+YsrHKJEWcYW5iDnM/IBZcZ23va43OssKIt72owW2Ehp0tt5dhhJrJed3W4xpyHWQjbUjMzjjkPsxZWz6lRD96dYL5/rSOebydOSeA9B6YnLL5rRk2eNWBmwpab7SvBcznMRNjlzXtH8HwG0xeWdMyH83JPed+waqt2cD+C2Qq7Ns6Csf0KsxC2Mt3oNO9A9wv7Gfnvv7fplVPcjxTTe/GwNteYYq0fnG3N2gMzEpaere/G/R3mLOxu8VZcm71hZf5aBzwNM+fm8VsJLOTvN8eIf/vi1v4Wx3ef59Y/tufbOQue3R4gd4V9G2nejPsKzETYbpcNBcw=
*/