/* Boost interval/ext/integer.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP
#define BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {

template<class T, class Policies> inline
interval<T, Policies> operator+ (const interval<T, Policies>& x, int y)
{
  return x + static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator+ (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) + y;
}

template<class T, class Policies> inline
interval<T, Policies> operator- (const interval<T, Policies>& x, int y)
{
  return x - static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator- (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) - y;
}

template<class T, class Policies> inline
interval<T, Policies> operator* (const interval<T, Policies>& x, int y)
{
  return x * static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator* (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) * y;
}

template<class T, class Policies> inline
interval<T, Policies> operator/ (const interval<T, Policies>& x, int y)
{
  return x / static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator/ (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) / y;
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP

/* integer.hpp
t2rkDquGtKtzXuLGdnGnFT5EvvjFh8lnxZIS06NF10gdi2Oxs4e0Z7FgnbqeFh4ozB87GE+H0RT1GJOEZ74c+Uhc4vsbhpyR9Yo6swD05Bcp6gKBurUqfs1ifNZtfeLis8BY3IDL043Bb5o9YwhP60caHa5gdH+JIoF8DelrPTuq8HWi7eGkBUY5q+dfBB8PNmkVJHeodDHuXv+L6G/ufGNd+xgfKXp6lD+9SyOOIpZ05GVn9YILqLX4tu7ib98Qu8hrjFCv0S90DPVSx/+TO9MWXka68Rz+Z8Zlwl4Afnhv1JmG7rJUoyi6kYgMD0l97+Rdu9msdB97NFVynlrQCz1FU/d4We89VNYPeLdKTsd3nKTMxsRSiMLi0PXvl2palL9mFKHCqrydVXySyk+u4ierXrMbR6jJb462IIacwyxVJOBpha78NMBcirtSMPxKfftrTfMp11xShV6u93lE1jNUQ0pRqGoVwxfC7/MqW0XredG+2XQTx0uxn9tmNlpLwEMleIKZf3sUU6Qr9gsfMJv4d9/DDVaG6dfCFoyNW+SsnJ0Q7s7KmvHW8EQ5PMsanpUq0XaIOzy2N/yXPi08CzQA1g862EiVsNlmH1OoBlFOnVcpOXVKW4QhG+dISxK7gh3RrdzstWz152wOfi8rkuYnzlvpKs8VtcHrju2U6JyKlLmNBucfhC7rRwc/sW3aV/g/ty1avY1aHdnP
*/