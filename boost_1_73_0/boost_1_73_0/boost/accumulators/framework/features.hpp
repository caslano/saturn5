///////////////////////////////////////////////////////////////////////////////
// features.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// features
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct features
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
{
};

}} // namespace boost::accumulators

#endif

/* features.hpp
EtSq/gLZzu4vgCdhAIhTz/nPMm+CBPgk3gQJ7Em8CQrbX7wJT+hNwL3pL+dN0Cf9JN6ElNcN0PZGJF03FMc3mPq+p31/oX1/jDchlSxlNn3K9uVegpSjl3kJUpRwLwHNOqYN5XP6CDSZrKFYw7CG4HQ2jXS4fxQfQQVxuLqPAIEW+Aiov8f4CLQBl/sIjJ5KfARUD9V0B+dBq7uPRvty2zJrh6zoSsCOS01l045Z2dRfDf7qpv4K8B9j6pvdyOWghY2vnXCexPsb25lSio/Z0Ovol2y2Lo07M0V3aZAQty9tFbUbNEaPQlaYxGTc7yHNKdOLbEGURxWyxSlhcpawdZNyw//j6tnOjuKHsjkavRd3bOsyD92CmCK6UDZvQ58OydZSEjQM6tRvthqxq07VXFZw0dkJ8slI7r+rklyRtwtnWt3bRbJ6ibfLsMEe5u1SDgEt5ktzRiCE/mDYPey3nibpigHQ7lTRq2jRp5WdH7ZQ1SxMicZZfOUEIZos7vQPllvli4PkSR0kWT0bL0KhEruvk87y6FKdoErDgs2KS7Oo6NVXyaCij7668NFbERaqJlARoZCj7lHn3RNJjMSf0ZvaOQ0VyAyzX4s3Fr4LxyrWWckF+5n8tTgv+Cr+VBFigosEQnQxxkscreSL
*/