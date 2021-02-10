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
ymDde3HdUk5lckhLe5MVRZ80QcnPg2OdnTPMnhZKISEqpPJJE1ZrAN22Hzrt9r9jSwSZOIedxNwOwwDkuLEn8m1Q2wIJDLAsiIMG19rGoHCgcEg31UqbIwESG+QjNkcCIzfIVTbH4m0HVkDuPA+V/0vFn0J/geiDRu3B0TGs+OrSzgdUzVzY2Ws3oT+pr/2qyT8m9nL2/BVIPs5OMJ6xJ0bk0ki8KAojKRl/s8nGOHE4aTiCLvbXgfnWl1QJwvWstABRkatIcgfBLZceiuNLGBrqVJQfq8iiArlgsL6NxXvd186P/c7oEVz8zovAaEEU/rgzmAOhB15yG0YfwTi7iNzoHhkl8n5Z+BGq8HY6l8NIdSyTSCsB57s0rB+UOXdQ0ZElcq0r0nER1UqpA/bx9XxxV2dff50++nFw3OkLCFRiPmLf77O/PX9ez9L8ClCdzo+jTv+gc5AD8hjGsSBL8A5jsCygjm5PsZxt4C/FMbltygYKatqIrtX90Wn1emJajyC94yi88VFQu4CP+dQdeySZ0ViN3AnJMVCWYKjQI8ldbiMEYN76gK4ZKIsgLn2QgCi8wdhEM8BdJCGqVewGLGeAEDdEKyG6w0XEwtuApf1Fi6lXKMLNyUoCf+u865y8bo26R7Uzo5jwfraz
*/