/* Boost interval.hpp header file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_HPP
#define BOOST_NUMERIC_INTERVAL_HPP

#include <boost/limits.hpp>
#include <boost/numeric/interval/interval.hpp>
#include <boost/numeric/interval/policies.hpp>

#include <boost/numeric/interval/hw_rounding.hpp>
#include <boost/numeric/interval/rounded_arith.hpp>
#include <boost/numeric/interval/rounded_transc.hpp>
#include <boost/numeric/interval/constants.hpp>

#include <boost/numeric/interval/checking.hpp>
#include <boost/numeric/interval/compare.hpp>
#include <boost/numeric/interval/utility.hpp>

#include <boost/numeric/interval/arith.hpp>
#include <boost/numeric/interval/arith2.hpp>
#include <boost/numeric/interval/arith3.hpp>
#include <boost/numeric/interval/transc.hpp>

#endif // BOOST_NUMERIC_INTERVAL_HPP

/* interval.hpp
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
*/