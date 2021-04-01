/* boost random.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/random for documentation.
 *
 * $Id$
 *
 * Revision history
 *  2000-02-18  portability fixes (thanks to Beman Dawes)
 *  2000-02-21  shuffle_output, inversive_congruential_schrage,
 *              generator_iterator, uniform_smallint
 *  2000-02-23  generic modulus arithmetic helper, removed *_schrage classes,
 *              implemented Streamable and EqualityComparable concepts for 
 *              generators, added Bernoulli distribution and Box-Muller
 *              transform
 *  2000-03-01  cauchy, lognormal, triangle distributions; fixed 
 *              uniform_smallint; renamed gaussian to normal distribution
 *  2000-03-05  implemented iterator syntax for distribution functions
 *  2000-04-21  removed some optimizations for better BCC/MSVC compatibility
 *  2000-05-10  adapted to BCC and MSVC
 *  2000-06-13  incorporated review results
 *  2000-07-06  moved basic templates from namespace detail to random
 *  2000-09-23  warning removals and int64 fixes (Ed Brey)
 *  2000-09-24  added lagged_fibonacci generator (Matthias Troyer)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_HPP
#define BOOST_RANDOM_HPP

// generators
#include <boost/random/additive_combine.hpp>
#include <boost/random/discard_block.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/random/inversive_congruential.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/linear_feedback_shift.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/ranlux.hpp>
#include <boost/random/shuffle_order.hpp>
#include <boost/random/shuffle_output.hpp>
#include <boost/random/subtract_with_carry.hpp>
#include <boost/random/taus88.hpp>
#include <boost/random/xor_combine.hpp>

// misc
#include <boost/random/generate_canonical.hpp>
#include <boost/random/seed_seq.hpp>
#include <boost/random/random_number_generator.hpp>
#include <boost/random/variate_generator.hpp>

// distributions
#include <boost/random/bernoulli_distribution.hpp>
#include <boost/random/beta_distribution.hpp>
#include <boost/random/binomial_distribution.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/chi_squared_distribution.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/extreme_value_distribution.hpp>
#include <boost/random/fisher_f_distribution.hpp>
#include <boost/random/gamma_distribution.hpp>
#include <boost/random/geometric_distribution.hpp>
#include <boost/random/hyperexponential_distribution.hpp>
#include <boost/random/laplace_distribution.hpp>
#include <boost/random/lognormal_distribution.hpp>
#include <boost/random/negative_binomial_distribution.hpp>
#include <boost/random/non_central_chi_squared_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/piecewise_constant_distribution.hpp>
#include <boost/random/piecewise_linear_distribution.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/student_t_distribution.hpp>
#include <boost/random/triangle_distribution.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_on_sphere.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/weibull_distribution.hpp>

#include <boost/random/generate_canonical.hpp>

#endif // BOOST_RANDOM_HPP

/* random.hpp
yg//tZn4j3n0s2PrfwlW3YD5c+H34IVBpY9MB86U22w6IB0VGf97WkrAn5MUTx0lnnnjTCaR/GJW+kER4nSKlL54ocnUdQCWdRmt6+nta1OSN6Lzr1HVFoqwikpANcm7P4QkYfgPgfLgd4S9CHwq+G1wM9byvKVbW5osLJqyhPrl852KibpCP4QwfpbXq6XyRe0XomrnWYY8C7iGKVqYl9NhBR74mk41AxEFUSuBGxDmtzdFj7KCTdDkrbLaxPCL8VHpsR6viWr3wisdKQUaviesKNincJTUL3vD0IWZmIfENLi0dEWZ1ynzgzy0PGczCcUccm4ivUi6rv2FNyDccQzhsEK5kRlr7RBSplYNzHYApWL8dVFfrQhJfjVdIRWXFw/Poq7hFOhLJDw0PPw8bB28snfss6SpZ1+R2P6mUlzm+K+xJvCzKxnGY9UpIVTJXlN6CoQ6SJB1LyEN7JrkVEdBVwygIjLFHr8/zWDFRfXwo9jp3UWAYCAH1SlPKP6CzxQ9jOnKWW/0ZMwiZT+zm1mHAeGw6WP1N5bRuU2fOtp7S6Y148LmO5+bvw==
*/