//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP
#define BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

/* min_max.hpp
v/5tYuU2k8ePN4U9dNGS0lWeo/pwfWfZmK6sk6OSI0eO1N+m02m9onDF8pbKxxJCI6CFof0hpXGi6B/5rmjO4UdTzh49VbNsuMsUhRnlGidR6jpRsbK5dN8ua8WWKsESjwBIq9OpTHPRLN+2zPLi4AKDh6klV+dmBdCW2YR1VMl1/Ty41WKx05D5ueEN5A7yUU0yOLbs6XJB7Sx/K5s20bpVuWL6o71PRSZ3mnao3dmzMa5OrFgBLBO2LzwTdW/3iCSvzrcpOnXjQukNTXJjN8gric2Psat0Y4JnZ6Gxn5qt7BCzDrn6trsPDbfBEV/DHYK3cH2Ttj68h26K1r8SEV4yb7TTtY6NHyJXdrUZSsko3V4q+MuoZ8O2jrzgH7srIHvc54DdLnIPI+YMVR5+ZNKRbVJTlWs2ih3erc9+mhA6BZ2MWB0e9irASX+pklX9neLoSa7Kb+ykTw5Mdnq0dGzZ+OaA98mamX+sSjIoG2j2uHYm1ZRRrXWrpkVYL1gX/GbD4saTDgNmHZ2uf1Fa5Wo76+eT8O5wezqtqfJj1EyTxeo/xGsljw4kYuxnBK8eY3a49pd3xx3ZkXK65iJDk9OvxZsf2Mximcg5LM22aqI7LmuxGVsU2PigTX+f1McS9LBh4nRUt/jOx9BnwbJjzt6oLVzXFVKq23xnxaYf1tUdVIP2eeea22qio0p1Sod3vlazbUt/sTjQXzVp
*/