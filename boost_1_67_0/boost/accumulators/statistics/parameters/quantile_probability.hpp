///////////////////////////////////////////////////////////////////////////////
// quantile_probability.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_PARAMETERS_QUANTILE_PROBABILITY_HPP_EAN_03_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_PARAMETERS_QUANTILE_PROBABILITY_HPP_EAN_03_11_2005

#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

BOOST_PARAMETER_KEYWORD(tag, quantile_probability)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(quantile_probability)

}} // namespace boost::accumulators

#endif

/* quantile_probability.hpp
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
*/