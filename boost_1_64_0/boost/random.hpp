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
bBVYE3EL+rxikPI58Y4rAuvDNH4tkbU329uEWjspqFhhyo8WyiEZJGOghFRgk70OAq1IS8qtim5bQZMRIMhokd0ZJAOqikoXAznWWLI2kUqKgOWQQEh/DSjUmBD5EESgC4cGPVigoJkBSHjQCFjvYISIKFOE0NInRGAOQGKwEke1Wx7vFFzI8FJcpKFlkAM1zvRssxtRpkMSQ9kJIHoH2MwZgMZieUtfl0KGILx5AIrpiygwAACAG6bBT+wvnmGvRStfCiIRPGS6lw1OOU+xv02zixbbZpJwBw5rKG6FFF6M7QL4Fsp5YA1sZPzwCsp1wLNa8jNxrqoDgEMG63GbZALxN4JvwIWo/kNxRglQnguftGoagLNyFD+w/stVJF/QIpsoTktiMc02bao/0jSPPKaoTweXq8dzS1HBR/VRvgJ1QP7wYsHh3+HfJ/FT+6UnHbO//dJz/tHe8/3SYHSqjyso2Dd9+63cNO6Xymap356cieUErBboTVG1exqOjr6OazSy4JCBBOJwxR1ZplGslmHi6w3ZcUdvk1ulrXBxq1Qcnrijr8m9UnFyr1Q7vdrJ2fVMIOQ6mC6G9Vy1rluj13WrlC6G9d5MqhkhA7nqEvnrEvnrVP4qvR5cxXVgfqu0vgUVK7MKFMHyODTHVpNDid6cgh9rCWMFz9UfDUGs7354DIHdQGKpcBM821Iw9BmO3fDREPyoFARWQHOwoiCRA6YJ/PI+BRQcekAK5n8qKAjqAdPh3fBgASgIg0pFnygVNQWBqEaPVBQMsYhU8oK3qh/JMICz/OPsteTLE58h73LDszGaeQ5uZ4DMa+2xOaZnNQLBFGMzPatOfNpo4/aHSoSKfpItQSZO5RSpZ+thXj4E/IYfkIIFnwIKjugGw7YEhkWfOAVHH5CCxR8rBSvrSz8MlgeTBgve4m6oYVztxit9l+f4jVmZshsJsGa1bIXCyI4pDjccelMUrkwzHpllxmO5LyqRbjoYx51RieLWqERxb1SisDkqUd9T+6Nm9Ry1P2pWf1PtjyJNv0D197IPb4we/v17f+p8a5lXWTvB43RpfCA2qz1TrGPLW3XFzbVQ6hF4VHZy4DG9unvvSN2Ey1LwkOchDajYxns/2i4BrQ/MZmCB2CNUzwn1HSRH4a2DMLuCf0+/OPxJPYX//Zb2nsMPJOC3unoI/9KMQ8D/5b5x+Avj8C1dgLXfEq7b1oMaqPnZAgUfj7DjNXWZlxWwHDqm4EDxvudfVXp1YdW0q3lTU1J/C7Xqbv63v/Tnvtne0e394T05+lrLViz78SJCiYWXCk+LjrnuvjNxWa3i+Pl7+ZRZ+VECcI1zzY72jkgl4Rq16obEchoBU87Kxh7fmlD0rsiJ0zsfFdo/iVsG6Ebs6fmBLk+d9VXl6JeFeO1TLtuZdquyhmbag4cqewYB3iD7LcnG14VDhXv1e6cd6/EA3oLFsrkfxl8AJ63LMmM73R7sBuXBnxHb6YvtgBdul/zPwptMM5G6F1LFdvg8TQjL9jR61uKNEESVW1HEOy8ANRsOO8ZzOoE0fn3VBI/a44RRdTjDRuLqgEunyNQpspiiXFL0qg5kj4XRudOt6etOyRxmVveC4baO+urMYZUvZuNl6wVfom3+LfHqPZGmq/dvq1Sfj6lSUBeODMLs1/R6GAMrqB5YcMpGs/oIqZyu2UgyX+LlNzMyeKg8BvfJGg/uwS/e/2b1Fs7E8kpuyN7mXWbyzpB32TmZIK6JRsCquTSFmYF2gAcul/qAVMFEK/gjeFkI1Bqr26IJbTGCbVEUQJ/Odub0we2nLGeBR9qlSFHdpYg+VpqliEQ/i80yonosY+ScmU4hzTJCUvSqHps=
*/