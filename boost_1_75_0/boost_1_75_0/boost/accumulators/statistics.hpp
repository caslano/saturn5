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
/oR+lE1KvBwvTXvIWBnbtTjUxcrko+L9Zq5ulHyrySnrXPL9RhjnX8v75W7lUkO3an02zzyrRc41aW4XK8ywqs5Kdb1tCU/Big4c896EW/TeTOtpZ5nagibk63ZLUHOlCRbFaEhzCbQTl6Dxervt+5of5Dr6aHIyaj2N7haWmLq+Xr06UVFt+DwFcEJR1zbUdsqqZN3EB+6418CVaXaeQxFFyaoz8/4t6Eu8wJzexvvXQ9BFLQDWuDaCHsQZun5EzIPLdncZy0LkEZVuQurNCynOQ7oyFL9hZw6SwKlr+EEO7Wxy3iXWQ/JVKwwTCsze32ZXepOzLd7E7GyvkH2T15x9rdeUPW/Z+Oz7Hrg+mKebJCU0ZHK+A1MRzN+AtSYg5vX+IUdKmFBs5gPf3204Dwiyc5cZs2fWt6EO6FZ4kZ1V/3ZkEwRQ/unrgAbpug6huLxr7wBhp2WFDiAcSjETvsLzUD2wOrrfJYhRF82VW8U9iir2ay1QyEb+w5sxXbQEvh1wVv0oMVrGPzzyKbS7OQO44C/xZSXvv1tCMHK8fzvoRv3PtoP8p75QlBUVivhNHu//+GGgpPXl6ad4fxxkxftPTer9B+3+NdzFbxJ5/+4mUtYTM4GEeKyLBB0A7SQiG4qM57VMk9WPdPI7dAD7ttFHTe8F+IcD/USjQZWJNAARgkqU7ArePxKgA4x7IUQ5EZ4fAAUs+tPu0+gu
*/