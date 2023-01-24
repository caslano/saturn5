/* Boost interval/compare/explicit.hpp template implementation file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Certainly... operations
 */

template<class T, class Policies1, class Policies2> inline
bool cerlt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower();
}

template<class T, class Policies> inline
bool cerlt(const interval<T, Policies>& x, const T& y)
{
  return x.upper() < y;
}

template<class T, class Policies> inline
bool cerlt(const T& x, const interval<T, Policies>& y)
{
  return x < y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool cerle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() <= y.lower();
}

template<class T, class Policies> inline
bool cerle(const interval<T, Policies>& x, const T& y)
{
  return x.upper() <= y;
}

template<class T, class Policies> inline
bool cerle(const T& x, const interval<T, Policies>& y)
{
  return x <= y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool cergt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() > y.upper();
}

template<class T, class Policies> inline
bool cergt(const interval<T, Policies>& x, const T& y)
{
  return x.lower() > y;
}

template<class T, class Policies> inline
bool cergt(const T& x, const interval<T, Policies>& y)
{
  return x > y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cerge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() >= y.upper();
}

template<class T, class Policies> inline
bool cerge(const interval<T, Policies>& x, const T& y)
{
  return x.lower() >= y;
}

template<class T, class Policies> inline
bool cerge(const T& x, const interval<T, Policies>& y)
{
  return x >= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cereq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() == y.upper() && y.lower() == x.upper();
}

template<class T, class Policies> inline
bool cereq(const interval<T, Policies>& x, const T& y)
{
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies> inline
bool cereq(const T& x, const interval<T, Policies>& y)
{
  return x == y.lower() && x == y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cerne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower() || y.upper() < x.lower();
}

template<class T, class Policies> inline
bool cerne(const interval<T, Policies>& x, const T& y)
{
  return x.upper() < y || y < x.lower();
}

template<class T, class Policies> inline
bool cerne(const T& x, const interval<T, Policies>& y)
{
  return x < y.lower() || y.upper() < x;
}

/*
 * Possibly... comparisons
 */

template<class T, class Policies1, class Policies2> inline
bool poslt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() < y.upper();
}

template<class T, class Policies> inline
bool poslt(const interval<T, Policies>& x, const T& y)
{
  return x.lower() < y;
}

template<class T, class Policies> inline
bool poslt(const T& x, const interval<T, Policies>& y)
{
  return x < y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool posle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() <= y.upper();
}

template<class T, class Policies> inline
bool posle(const interval<T, Policies>& x, const T& y)
{
  return x.lower() <= y;
}

template<class T, class Policies> inline
bool posle(const T& x, const interval<T, Policies>& y)
{
  return x <= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool posgt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() > y.lower();
}

template<class T, class Policies> inline
bool posgt(const interval<T, Policies>& x, const T& y)
{
  return x.upper() > y;
}

template<class T, class Policies> inline
bool posgt(const T& x, const interval<T, Policies> & y)
{
  return x > y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool posge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool posge(const interval<T, Policies>& x, const T& y)
{
  return x.upper() >= y;
}

template<class T, class Policies> inline
bool posge(const T& x, const interval<T, Policies>& y)
{
  return x >= y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool poseq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower() && y.upper() >= x.lower();
}

template<class T, class Policies> inline
bool poseq(const interval<T, Policies>& x, const T& y)
{
  return x.upper() >= y && y >= x.lower();
}

template<class T, class Policies> inline
bool poseq(const T& x, const interval<T, Policies>& y)
{
  return x >= y.lower() && y.upper() >= x;
}

template<class T, class Policies1, class Policies2> inline
bool posne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() != y.lower() || y.upper() != x.lower();
}

template<class T, class Policies> inline
bool posne(const interval<T, Policies>& x, const T& y)
{
  return x.upper() != y || y != x.lower();
}

template<class T, class Policies> inline
bool posne(const T& x, const interval<T, Policies>& y)
{
  return x != y.lower() || y.upper() != x;
}

} // namespace interval_lib
} // namespace numeric
} //namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP

/* explicit.hpp
ht1xU2IZXPP02Xf2j9YyTe2Q7w/5/MY7jKRwGPAd9tRyHxU6pYDNX2cR/GYgptIN54m8e668wQnBY5aKDSrcDrXeafNVhhesD3s+wg1Xkl9hTwWOnMVVnod6tmCTX9EOWd8lSR/VJ5nKPf92s1/cS350lS/4l3uJBn/WuvKcttLX4a3B4lC3p+yn4D3ADK8dJ46yX76Ez8k42dklOJpqmX5Qjh12od3et2KuX4y5/ou4VuzPjiX9bb16HUWv8god0ntmsDX+Bc2V5PcPTvSUasEUaR3cW7C2KUyDOgYaKMnrH+gqII3kUd/Xl3NVW3STAz9zqtwYgb+LOhnPj0+VngRZHhmG7Q4Bk6Mk71FYItqnkdySvAXBHCn0kzl4qVRy0hy8GHHVIXzmBP94E3wsxklmfaUPLoWRcOc5gudq9o1P6P0vMUnXV4tUA6890Q6MHQLXICa5p4N4mHb1GjMWJbaVXoGa/vXVWIIVPr6bN7nEFDlIb9nIC14l53QB1nGx7Ul027GqnC6+qbU+1mVjBnESLFaF4w0zkxVqTbGV4smsUOu5ttI8uuhnK72SLgp5sjAfW2j1KqNRDoQwqORHHzsm5S9KX9jPS9ZaUcONLKVZsy8ppTbvl7QtoNB7nHenz/8WXuWfToZPcW3NoKgNQPPO4xzNZeiHyu8bSKM5+uvjfO6dVUEgt7uA1haspQcLHtcHz5WXF7hqieff
*/