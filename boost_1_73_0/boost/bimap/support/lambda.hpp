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
11b/hZ79SW5+a6/YoJRPed7J0f3a+oVfzu9f66oivkupCoMsFOPptJm0VioPPZNNZ8eykEQ0s3iKwaMzyKLBdmdjqTja2KVY5t8fcjYGW6GknI29S8A+wJfAgk4QPc7Gws7Z3TTmveBs9IKfBHRtA963fHzcSZeccxZ0Z3a0/IfhBlKFUjzt1IulZCrL953s+HgpkyoumbTxNLV2kH2nuSXqMnx+r1uMZ4O/sinWhvINn/+l
*/