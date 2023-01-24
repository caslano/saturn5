// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/lambda.hpp
/// \brief Placeholders definition to help in bimap modify function

#ifndef BOOST_BIMAP_SUPPORT_LAMBDA_HPP
#define BOOST_BIMAP_SUPPORT_LAMBDA_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/lambda/lambda.hpp>

namespace boost {
namespace bimaps {

namespace {

/*
boost::lambda::placeholder1_type & _first  = boost::lambda::_1;
boost::lambda::placeholder2_type & _second = boost::lambda::_2;

boost::lambda::placeholder1_type & _left   = boost::lambda::_1;
boost::lambda::placeholder2_type & _right  = boost::lambda::_2;
*/

boost::lambda::placeholder1_type & _key  = boost::lambda::_1;
boost::lambda::placeholder1_type & _data = boost::lambda::_1;

}

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_LAMBDA_HPP


/* lambda.hpp
NfX75jdUcQ77Xa3vd7Wh33x9j5uS32ec5X6flf0+BqT7ZGdSqKSKxcv/DE1JCYyUzpK2CQxXI/i57Jaio+npYlB1LURO+gmGgamOwt9tRZu5ImO8VFvBqxB+TxKUWiF5BFJmH1MlCTifEB0s4ifeOfJb/rAQWcszGwDMVvgnEp/TYDCbhddu6UBEafvLaf3V25m/W2HOAisJBQIJU556V17F4zLfH2SeoFJDfu7fCflRBFL72RepAgyUMiS4gqWygsVaBa25AuTOZ1TQrTwaCGCfKqXiSXTvayscGEprE29WGZl4CTjpcttMiRYIoFPA/v1h0MjSjcD7RFrtP2IVJ8CMTeQpYtoB0BuHN//gdEy0PJHZoXgkPCXIXeCuhELxvIke1R38oq46+y6xpjm3i3dqIfsGqDMeCF5cRSpa7QqquX2DeOQ5/CnmgP3nHEFy8xtwBSoD9lEKnJxbxb+2dZUztpvEzhZ9H1kJzGdPvlMu6KyXdy70MA57mKf1UKBBW+GzSK/vBfMBrb9iol+us2rT57eEhRl3TLFZZYSav/ps3H+ilufCmtx3oPNNgPYgNHPttew28JeOGu9uCqF6Grg+vih/cSjVVx+8j79qvI8hj5L2k2Eff/Qb7uPHltI2BCsG5YM12jbEMvafeBvu1bZh4W80O2RUYr+SKwC+Q/EEV/DVj1xBtVZBKldAtjc0AtrA1sfJP3Vfpy8n
*/