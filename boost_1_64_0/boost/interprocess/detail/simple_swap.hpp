#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP
#define BOOST_INTERPROCESS_DETAIL_SWAP_HPP
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost { namespace interprocess {

template<class T>
void simple_swap(T&x, T&y)
{  T tmp(x); x = y; y = tmp;  }

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP

/* simple_swap.hpp
p7Y27YKYZ/rnY2W6zd7Ne6KAs9FQaBPTxApao9KjzFSeLiR9npmf5YbvCMBYk9ndF1/w7BvRElSX7kXBQpiTg1dAyemWRx9m9rWb4HdgZKYyeaWIVa2tD/xR+oNqAfggYmFtdsrPfup5zJCi26Myf8b6dFuogXC7zXjDy3hZ6ZmiGPdkFa4bcu74mY+vR59GtRUy7Mv7RNVw+G3gL9+M9jwqueDK40ZiZS4QbY2KlN8FrtpeEX5jCpcHK31PH5+aaH+X1iHt9KOH7V1Y7aRqYonfoRohytjObpBeZNN+6JUcYxNeOhlHSISOSOBCVwkTYCi9jmw3Y54TSz8kaEWfaChvyLR6ceBpF8NCK7Iov26Nb4Qr/WV6OtzNrZDTPDTXHuLwADYSw3XRqAzCL2YACqcQf1EBFZSGxVNOTVlXu0cRyOXXgRmqz2cav5fkqweQ2u10fXulwjHCa7llKqcQnWXMFOoBiIExZgJOzhirTeyKHb4RfbwSd9l/LNe90Xo5QuUZQIRXJonjeAt6vkW/6S2G/F2qT+uR/iIIJv1Aw4lYxbZKWeZlSKenSw==
*/