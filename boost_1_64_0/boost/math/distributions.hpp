//  Copyright John Maddock 2006, 2007.
//  Copyright Paul A. Bristow 2006, 2007, 2009, 2010.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file includes *all* the distributions.
// this *may* be convenient if many are used
// - to avoid including each distribution individually.

#ifndef BOOST_MATH_DISTRIBUTIONS_HPP
#define BOOST_MATH_DISTRIBUTIONS_HPP

#include <boost/math/distributions/arcsine.hpp>
#include <boost/math/distributions/bernoulli.hpp>
#include <boost/math/distributions/beta.hpp>
#include <boost/math/distributions/binomial.hpp>
#include <boost/math/distributions/cauchy.hpp>
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/exponential.hpp>
#include <boost/math/distributions/extreme_value.hpp>
#include <boost/math/distributions/fisher_f.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions/geometric.hpp>
#include <boost/math/distributions/hyperexponential.hpp>
#include <boost/math/distributions/hypergeometric.hpp>
#include <boost/math/distributions/inverse_chi_squared.hpp>
#include <boost/math/distributions/inverse_gamma.hpp>
#include <boost/math/distributions/inverse_gaussian.hpp>
#include <boost/math/distributions/laplace.hpp>
#include <boost/math/distributions/logistic.hpp>
#include <boost/math/distributions/lognormal.hpp>
#include <boost/math/distributions/negative_binomial.hpp>
#include <boost/math/distributions/non_central_chi_squared.hpp>
#include <boost/math/distributions/non_central_beta.hpp>
#include <boost/math/distributions/non_central_f.hpp>
#include <boost/math/distributions/non_central_t.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/pareto.hpp>
#include <boost/math/distributions/poisson.hpp>
#include <boost/math/distributions/rayleigh.hpp>
#include <boost/math/distributions/skew_normal.hpp>
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/distributions/triangular.hpp>
#include <boost/math/distributions/uniform.hpp>
#include <boost/math/distributions/weibull.hpp>
#include <boost/math/distributions/find_scale.hpp>
#include <boost/math/distributions/find_location.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_HPP


/* distributions.hpp
9v/LymFOxT0/wsY4pderfeGfRw9lyS+DjvaFitw5fh+0Qv+zOeRH64x1VlWyfp3cJep7mZKRrw6d3CIbUnMN15cR35o52BFRd++mWjmOrTE4wH0BpT8Uv8dXkfb2kv6O4hW/d1zXkJdP3jkQTZg835qYX6PHjXUsfY2xCzhc+eeZ+VOe6YySEv+z75Lz1je/tvrnra8eodzG52OFdX8i6aqrdCkPdYZJiV1nlsnTrH3k6cRwch1sTvjO7MQ8zdOZdDvqmC5iefUQfxWrh87sitdDc6t62DOELPzj6+E/2TsT8CjKMwDPbgIEEiBcCYQrQESUAAEBue9bCgiICEgSkwUCIYnJQqAih4BCTRUVURAVvKuoaGnFllqsR6FaTZUWVGxpwRYrtpGq9aDSd7/9ZnY2OxuSgrTP0/kfPt7Mf833HzM7/006yI85NaqHvc2zOWsFI2yjEbdG/pRMv3qlPOPwQB+TDav1/GZUM98yapBv6tc2d081cq6T+K9RnTyr5zoprF5aeoWfB6fnkB3w8uwrU6mbWY75LI99+HOv6yIGfHP6dJmEedRa47FCrpvq+hczzrft61+wi3g/iP8+xLdF3DZb8d2xMrSmPs4hPrWLKGNZK0F8D4vbLd4kjW+7XJd5kpnp0NUzS9e4RMardk51wpove5O47/Cira5piYxH7aLWFzOdB8SP15o/+zu5vto7gREWnc8cEbdp57gnpsbzxA0Bdz/vIa+1xnDyqoDdMNE5nTx6UuK40RuI43g/nU+sdXmJ7q+VqnuRmTp7YYbE3c6wnTGHm649lnske5IsN6lSpXm5/nn2dGes0nTr3OX2cv2YpwF2tjQVlpYY1pqYvuJng6eFsYj4sbPStJ9yzfJs9XS0hfUX59j2mtskab3Xu4f9zNZ5EyUPepIHz4j9DZIHHWTf0NCeoVNxx561urrWVe2HYG+ez9m+MWmmsDtApKq/rbUUhzzVX0txyWpz3USvDJwr2/UwzuHvmK7vi3iH4FfqA3XEfmao5E+H/joXW+3IG12HR37peVAPSn0R/eQ6frV5Hf5+Ohwf+TtwAX4qVju+n/ixqd5vaMXq6v0WVKyu/m9Bxeqa/RZUrP7Pfwtq+tta1W+BdX6unme3R+wZz0f2UW6pa6y8nudbkklh88kdtl82GxIZoTV2/cT/Zod817ic88gp//FfOf/ltRGZ/+o3/Kze3Gx/duj9kiPusdaajZ/IdbPIsonUU+OSvLTie0H81LLWWnSU6/pOew9pfM7n7/USt/srvzsljk7i9kNr76EfJVaWM6+dCPt+0LLSdROOz7VVdzSv9b2gZwFLnlZ6L2jeVNrLalLD0J7rhuZDy/7oF9yHurQ4z+/LpPVnaF1KTrTKzKnuaDhd62I+i471JtxvTKx+Fzo/t+rXeg7ZW7n6zyE6a/qxs++Vq7qFnX+IDpXXRPj1Ls018mTNowxbHvFWq1b+ZNQgfzIi8meOc/6o3+qcgfuf5Qn31d+EQXIfTL/qnRHovD4g+jx953UD0ebv13wdRrT1DZ/92YN9i0+++uznR9t9d9Ozf/3gxL8+L635mYU1PYOwpusznNeLRFmncg7XW9T0DELn9SJhZwRK23WvPle6lkL7WqQdjlvYWgqZM2+e0UUSuAidgVau4Vo6hEvWcM1hCmwRCsdf0e9XoOEK9X5FVjhEw7VxCLdaw62BreFaDdfHo9//2obbq2HSsdDvJtZEYAcvhxfCXNgJXge7wBWwK1wPM2xn6D0Ge8K3YC/4DuwNj8M+sEL9nYR9YV3u2Q+2hP1hDzgA9oED4WA4CE6Dg+F0OBSuhcPhVvW/HY6Cu+FouBeOgb+E42A5HA8/gVM=
*/