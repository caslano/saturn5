///////////////////////////////////////////////////////////////////////////////
/// \file statistics.hpp
/// Includes all of the Statistical Accumulators Library
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_HPP_EAN_01_17_2006
#define BOOST_ACCUMULATORS_STATISTICS_HPP_EAN_01_17_2006

#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/covariance.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>
#include <boost/accumulators/statistics/extended_p_square.hpp>
#include <boost/accumulators/statistics/extended_p_square_quantile.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/pot_tail_mean.hpp>
#include <boost/accumulators/statistics/pot_quantile.hpp>
#include <boost/accumulators/statistics/p_square_cumul_dist.hpp>
#include <boost/accumulators/statistics/p_square_quantile.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/sum_kahan.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_quantile.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>
#include <boost/accumulators/statistics/tail_variate.hpp>
#include <boost/accumulators/statistics/tail_variate_means.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/weighted_covariance.hpp>
#include <boost/accumulators/statistics/weighted_density.hpp>
#include <boost/accumulators/statistics/weighted_kurtosis.hpp>
#include <boost/accumulators/statistics/weighted_extended_p_square.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_median.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>
#include <boost/accumulators/statistics/weighted_peaks_over_threshold.hpp>
#include <boost/accumulators/statistics/weighted_p_square_cumul_dist.hpp>
#include <boost/accumulators/statistics/weighted_p_square_quantile.hpp>
#include <boost/accumulators/statistics/weighted_skewness.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/accumulators/statistics/weighted_sum_kahan.hpp>
#include <boost/accumulators/statistics/weighted_tail_quantile.hpp>
#include <boost/accumulators/statistics/weighted_tail_mean.hpp>
#include <boost/accumulators/statistics/weighted_tail_variate_means.hpp>
#include <boost/accumulators/statistics/weighted_variance.hpp>
#include <boost/accumulators/statistics/with_error.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/accumulators/statistics/variates/covariate.hpp>

#endif

/* statistics.hpp
XhEa8D+71goBSZJ34v+r+G0FzYTdgeFozKr8L0QwGRMpPcWJYQC1wpSxqJE1KBNJ8SnSMMdR+I4TPOv2xOe3PCbRL24uPiCNpWATFrEVbsZXFw0AcdsdPEteYUplkeHHzJ+f0uZExQD3Wr89sznppDP8v3tczTrIZBdRmruvEBOOx71gZKCNjWgIwLimUV1HO/Vmd6At4nsylhKpucu+FlU3OEevz9NSVAGdVEbbfJeu0vEjrsfEP9PjT+e7Naxj/QkerS1/gPmxTNvUe6kzUKJTyuk5KtMxMyY58WEeUapDOGgKaKuXvkgdBQkaL+ssc73HEB2iLJ4RgjmmDMO/6mgDGlpMjBkx5S2V5PEESvyd8B3vIIQ45cQgJ4Cm4I4I5i9xbXtXzpJMJr7zKw8zjLL5JJyvBKOb2VearfTH5u5aEaoAtOILhdkwWLxaFTnGJ4UnGcXGx9RGhDOACpjqLR6rq44Tks9fTymJ5jbVL6K+A8n8yO9+Ggl4JI0dZ5FEpIBmUGVStiErge/0KVvHxRAd2iuKDnxs6FBoxh/bP6jFFVrgPKCe6Yosyg==
*/