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
YAFPU5fbLpRo1QKUnqFd5r29Lcjkra1SfGfAWoK9blIvN8rTf4mPyppT4jheKJvtFVu4Req0fscAekIhQu7IzsHIQ8y/sqHfTmJx8qAKVpj5FxxCBT45LjvqxnDU+CvMrv5WmiSygOL5n+YrxwvG4bTWPkjAluSHYaTAArmjnnJkcuCKH9pcdFKeZU1c00qk++7Zykc9tvUzXX/Y7sy/ibR+kdZkza9gd+k1QZzxvQn+doNmVhgVs8knlM/rcgDOTBgvq8y3Av8gCaUCBBaREgCZs8p8oxNHHkYbII9Ntii6Gk7ADw5+/ddemIuY3MkC1sZRGKXtVDSi0BFGzQ+HE73K2e/32rGm6JorYYOzODGIqfAnUfBTegiTFPm9k5Ty5woW1bnZhYlMnEzwI1pK2nrB0gguPXupb0YArtiCIzgOyIPPPOhuuD3oaKajQVaabDNNGTMP3nt0opDVGz2+UgYIfqzqsEEpaVzTKNixQsFP6cK/1331D3ui8FvEEAodhPsRDiYcV5Ug5JGqjBS2hxzToC/XT4JCsUfb0UU1IECqFkUWzClIZS7QPg==
*/