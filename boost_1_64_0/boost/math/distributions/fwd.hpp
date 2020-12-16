// fwd.hpp Forward declarations of Boost.Math distributions.

// Copyright Paul A. Bristow 2007, 2010, 2012, 2014.
// Copyright John Maddock 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_FWD_HPP
#define BOOST_MATH_DISTRIBUTIONS_FWD_HPP

// 33 distributions at Boost 1.9.1 after adding hyperexpon and arcsine

namespace boost{ namespace math{

template <class RealType, class Policy>
class arcsine_distribution;

template <class RealType, class Policy>
class bernoulli_distribution;

template <class RealType, class Policy>
class beta_distribution;

template <class RealType, class Policy>
class binomial_distribution;

template <class RealType, class Policy>
class cauchy_distribution;

template <class RealType, class Policy>
class chi_squared_distribution;

template <class RealType, class Policy>
class exponential_distribution;

template <class RealType, class Policy>
class extreme_value_distribution;

template <class RealType, class Policy>
class fisher_f_distribution;

template <class RealType, class Policy>
class gamma_distribution;

template <class RealType, class Policy>
class geometric_distribution;

template <class RealType, class Policy>
class hyperexponential_distribution;

template <class RealType, class Policy>
class hypergeometric_distribution;

template <class RealType, class Policy>
class inverse_chi_squared_distribution;

template <class RealType, class Policy>
class inverse_gamma_distribution;

template <class RealType, class Policy>
class inverse_gaussian_distribution;

template <class RealType, class Policy>
class laplace_distribution;

template <class RealType, class Policy>
class logistic_distribution;

template <class RealType, class Policy>
class lognormal_distribution;

template <class RealType, class Policy>
class negative_binomial_distribution;

template <class RealType, class Policy>
class non_central_beta_distribution;

template <class RealType, class Policy>
class non_central_chi_squared_distribution;

template <class RealType, class Policy>
class non_central_f_distribution;

template <class RealType, class Policy>
class non_central_t_distribution;

template <class RealType, class Policy>
class normal_distribution;

template <class RealType, class Policy>
class pareto_distribution;

template <class RealType, class Policy>
class poisson_distribution;

template <class RealType, class Policy>
class rayleigh_distribution;

template <class RealType, class Policy>
class skew_normal_distribution;

template <class RealType, class Policy>
class students_t_distribution;

template <class RealType, class Policy>
class triangular_distribution;

template <class RealType, class Policy>
class uniform_distribution;

template <class RealType, class Policy>
class weibull_distribution;

}} // namespaces

#define BOOST_MATH_DECLARE_DISTRIBUTIONS(Type, Policy)\
   typedef boost::math::arcsine_distribution<Type, Policy> arcsine;\
   typedef boost::math::bernoulli_distribution<Type, Policy> bernoulli;\
   typedef boost::math::beta_distribution<Type, Policy> beta;\
   typedef boost::math::binomial_distribution<Type, Policy> binomial;\
   typedef boost::math::cauchy_distribution<Type, Policy> cauchy;\
   typedef boost::math::chi_squared_distribution<Type, Policy> chi_squared;\
   typedef boost::math::exponential_distribution<Type, Policy> exponential;\
   typedef boost::math::extreme_value_distribution<Type, Policy> extreme_value;\
   typedef boost::math::fisher_f_distribution<Type, Policy> fisher_f;\
   typedef boost::math::gamma_distribution<Type, Policy> gamma;\
   typedef boost::math::geometric_distribution<Type, Policy> geometric;\
   typedef boost::math::hypergeometric_distribution<Type, Policy> hypergeometric;\
   typedef boost::math::inverse_chi_squared_distribution<Type, Policy> inverse_chi_squared;\
   typedef boost::math::inverse_gaussian_distribution<Type, Policy> inverse_gaussian;\
   typedef boost::math::inverse_gamma_distribution<Type, Policy> inverse_gamma;\
   typedef boost::math::laplace_distribution<Type, Policy> laplace;\
   typedef boost::math::logistic_distribution<Type, Policy> logistic;\
   typedef boost::math::lognormal_distribution<Type, Policy> lognormal;\
   typedef boost::math::negative_binomial_distribution<Type, Policy> negative_binomial;\
   typedef boost::math::non_central_beta_distribution<Type, Policy> non_central_beta;\
   typedef boost::math::non_central_chi_squared_distribution<Type, Policy> non_central_chi_squared;\
   typedef boost::math::non_central_f_distribution<Type, Policy> non_central_f;\
   typedef boost::math::non_central_t_distribution<Type, Policy> non_central_t;\
   typedef boost::math::normal_distribution<Type, Policy> normal;\
   typedef boost::math::pareto_distribution<Type, Policy> pareto;\
   typedef boost::math::poisson_distribution<Type, Policy> poisson;\
   typedef boost::math::rayleigh_distribution<Type, Policy> rayleigh;\
   typedef boost::math::skew_normal_distribution<Type, Policy> skew_normal;\
   typedef boost::math::students_t_distribution<Type, Policy> students_t;\
   typedef boost::math::triangular_distribution<Type, Policy> triangular;\
   typedef boost::math::uniform_distribution<Type, Policy> uniform;\
   typedef boost::math::weibull_distribution<Type, Policy> weibull;

#endif // BOOST_MATH_DISTRIBUTIONS_FWD_HPP

/* fwd.hpp
YLLtDlNhcA/hy+AY+BM4Fc6Fs+A8mAODa/XmwCvEXeod+X4mD0rVO1DypRlsCZvr/ES2jPysL/4aSH42lPxsLPmZFgxHfzdBQzg3yX1eJf5ugXXgatgW3irhjMPkSjhDJZw4zGAJp4bEJwE2h4mwC0ySclJH6v9k2B+mwiHKXe67R9qH0kaeAltg+kr9WCjPwZ1yX9ZZUi7hcHgPHAs3w9lwK1wBH4Q3w5/BDfDn8H74GHwE7oJF8El4GD4FP4BPwy/hc7LP3i9gA/gibAxfhulwD+wAX4Pd4OswE74JL4C/hv3h23AUfAeOg7+HE+FBOAseggvgu3AJfA9eDTfDm+AH8A54F7wHFsPN8FO4DR6Hj8DP4ItyfiVMvSLe6oIZhcnFrMXswhzAFGNMewLmuuaj+ZfFn9WctEjmo7n36HPOQTvaNY65Z8Z5Z2q+Wctl8eXOOQs/34xzhF/WfLO+hJ+DWYXZiTmAKcakXkmeYkZhcjGFmB2YvZijGOuqeKs+JhMz8arKOWqVR+VReVQelUflUXn8a45/xfh//kzOZbzjjzH+3x7jz0AxvbcZTT117Jbv0qcxw/mwKNqh+s3Vhkv0mM9VEbAsxxg6ImPea0n8etxr9hn7v52yc1JUuNOde/K/qs4/bnXi770YU3+3M4xzVKoIY26uHlO1T51/GM29l++ZKD0OrjvXKwiuqZeIgZmGMQl+w9p6wx5xr60n48gkX1S/rGEdPT8knbipdIbsM1coazH2kW/H3piOLelPe8R1LxbNU3dD5W+izjPdF79LyddV/ehESfwnOe8RbpHfI5HV9969X+F+db5JqT0SbdGX1bmOWk97tZ3PEejsg3lK+iSvjHmq+8O5bki/ds8y9tUy9wtXfJ8sc390xffPmqj6x3+/NHFI3MmoGycuiH1iYXbi0P+e/bPM+2T9ePteVbRf3qyHqLie44SqF6V+kd/bRVe6Izh+QvqzkmECrAXrwRTYGdaG58CO8FzYQPoL06RfqzHMhU3gQpgOl8Bm8FbYHq6HHeC9MAM+KOFtg63gTtgaPgHbwqdhR93/KM+v1CvbXf2P3aQ//jzpjz8ftoCZ0q/XQ/o5L4CZ3sj2TDL1ddTH6L2Ryt4Xif2QItsLydkX4t7rqD7MxMjeRuZ9jRx7Gp2G7j2MjuFeAA17Frn7U/QeRaug6leR/Yh2YMrahygfI3sPOfpfkHf0wUT1Knt/IdlbSPYVcu4jZN5DyLx/UPj9gg6b1wvS+wK59wMqkn6d/fAIZh99M8cr+2cqj8qj8qg8Ko//oeNf9f0/Ny9/2hy7A+BH+P73NaM9J9+c6aL3S5X01MYcSGCc99aSb86pM2bYY/CmzcmePHf+jEVzsh1jsxvVL3/MrXP8+Q750Gvi49sNNoR/TKGNHbjejPmT86cvzJbxfnqMHWvTL8rWY+L899uyz3iHWjm00R/zGPsgtrrH6c2bOjfb/H2LrB5b2UTFjryePHcqOzgr+WOMm5K90YPn7IFWepzaUeX/O29VPU5ttuwxzjgTFddcb2vrlKe67Dv+6oO2W6ryfxz/fZXMJm/o9WfOmTorD5lAH8ZhdY3vvTLOmiM7N39hIH5HCaNkjNy82TOskn3Sv1f+qlnB8XEx6lqHvY4xf4stScsZzh9S8nE++3zTmmrs4LyZzv0W1PnfeofxxTHXO8Jyp8mVT1OXStjFhP2Z8ntKXfs+JTQnz9nX8xd1/kvvamsEeuvpakzfEfx1VXF+xGuvG9DSQ38NZaZxIuXAc7U/LtoftaKO3xPNr2AfQ3ECJjhnQPzswU8T209swRa/r4ouvydccseRa2PLxV8T5/fVcO7/reSaY4/Dvpb4j2c=
*/