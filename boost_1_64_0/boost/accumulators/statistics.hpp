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
j5hPkREeSlngrtb7YauGw9cFrsKelZh4L+A7HYZdXx+CR0Vqj9wEKKjYC08ofusldIG7FV0zeKirKFE/fXkTndR+nDd5dUS6R1BJw7gkz4SGoTTHF0vI9A82U7JmM5nfSNbPvY62FL+piA6BiyjBr0SCm5ZMhAfa/Yd/5bKEsn+v73ldbCrz/0J/a/QXV7BEEQQHq6FCVunkgiqR4gJOMdTl1/D5lubSr5GUmc9kb6bumv0IyStTsB0ZJe6MOXWt7MI7U7GF9KMn0egxFopa/IqJ0ZGEiZsRuOQmgYXfXUJYeMQbuuhtfcc/KR3OZEJ4cwfClUX3UPaarQIxBc8aiMlV6aoGvqDhqrFXVWBX4gB+0KVH5bossjfPepJ7swZgBW0lZdO7U82TyMRllqqNgJxeP/5howcLg+hVVKtV6dd/yr2h6XotCijZNr0H5SMJSH1WJMLo1xz6z1ZSqlpgIF3V0Ew/xHSLXEjEMv0sbB3z/yWIdQAyce/UZ0Yih+p8bpvx9Ic17YwnT6vx9OJqAWJPa8x4Uo3xtOYFOZ6cJctQpEn7HsRt+lBiDrmfZMrDmAD65w2neT0boPhptsTbBzzoZI+sLuMeufBlgxoKJ+gJb/AoSaevbGCUyDwd6ej7XOr0o5YRkIX5Leh+4gdSDrNB6kxajxbqM5wABwXdQD3OA7SCv28j2rtZ0F7vEUR7D+t3LREEdma5KPbKDXJYucu6Zkyx6J+HEu/pP1gte287jaECGkMYT/pt/zBnnFOpQW9zgxT8vzheNMgL/IcuuUH/2+KmSP1CxsvwVBod6Jtmvzk0jn2MO2L+WxgaicbQeI8QNb9ymJ3IGFMY5dSy0vWmB6hW3ZznPhbT2A0N9zClEOnlk6gsAzw//kIVdsK75Bvu0rrpe8vFOKHFVUNTlMXGIEnH2o9xwkI5fdUKiXBUcjbNAAWYASbn0AywgxBSvUV0zM0wiAL5vf6OmAgmctd4eA5gMogNOpQya8+lYs5zv8kdBez+4WKi/I3qYMVV1A0gbsak3pAIzyWQLPm1Mu407ibCYYQHVBg9dj96JZR7o978mlQjZVwOGif1YA3ofNZGSd8U0UldUnT9fbBGkpGS6kf/Z0NtAfAwyRUJ1dlRjyKePM+gGe3kz6tpuX4/iEkvNv6saDycg9NMr0Safen/WpU3AN3Ylj/7aBWnEqykwYPhr4Pq0P+MPEDliBgmzYUIlx4UEWejL47IJkrPdBX1iUnlQSqPPk6kcklqMXk+t+Q/D/AOkVj4+xnwf6tH3jZnuuOUQBX8G2iJ2etinrM3TTlh0EmLynGnSMegSP6vmmsCb4nx+AGjdEfSD/CXJdUGtX6huixMqkmSLx0ILaz0PgERafvtEzR/YbXZvjsfNtt3MzWs+E88cRfdzAOcVpNcAMdLInNNNITnhXk+v0AsGbAmONOvIV0Own5OCHk5npHTH2Pj9iwXj5Z34iwYI7eF1Hi08xZ99UIDZR4aFoSyDZTz4UQz53ky5/uxOW/VH2idk8nA/D6Qnt+X/e6lmM3zhGE48UB6tyqheX7fr32rfacGr/R4tQZ98EOEwEbCWQ9AMAbb7CvHXnX5lbTMkVgoV4+Aw2McXkEI9eXCQ8jMU7O0NX6tUfeViTX8YjaPy1FhmK2TlF7a+YLLSXya58xC4jIH+/SiKVmY2TG/087mOAjxUAqv41aUgII91JHXYH1lW5NN+qpHAEDJJ857N7NUK8/j05bDfjpXX4rOpju3Fj+CjIF8VyN9BFSXgxqnx1N1gAeTP8An4tdf/Ctk7JSYG4MLV1xiMtwrBPXgACfo6ockxmske7FbUZ9IHvLVgYYoiwNZkJRwwMn7fCg=
*/