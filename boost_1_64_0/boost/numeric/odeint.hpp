/*
 [auto_generated]
 boost/numeric/odeint.hpp

 [begin_description]
 Forward include for odeint. Includes nearly everything.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_HPP_INCLUDED

#include <boost/numeric/odeint/version.hpp>
#include <boost/numeric/odeint/config.hpp>

// start with ublas wrapper because we need its specializations before including state_wrapper.hpp
#include <boost/numeric/odeint/util/ublas_wrapper.hpp>

#include <boost/numeric/odeint/stepper/euler.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4_classic.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_fehlberg78.hpp>

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>

#include <boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp>

#include <boost/numeric/odeint/stepper/bulirsch_stoer.hpp>

#ifndef __CUDACC__
/* Bulirsch Stoer with Dense Output does not compile with nvcc
 * because of the binomial library used there which relies on unsupported SSE functions
 */
#include <boost/numeric/odeint/stepper/bulirsch_stoer_dense_out.hpp>
#endif

#include <boost/numeric/odeint/stepper/symplectic_euler.hpp>
#include <boost/numeric/odeint/stepper/symplectic_rkn_sb3a_mclachlan.hpp>
#include <boost/numeric/odeint/stepper/velocity_verlet.hpp>

#include <boost/numeric/odeint/stepper/adams_bashforth_moulton.hpp>

#include <boost/numeric/odeint/stepper/adaptive_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/controlled_adams_bashforth_moulton.hpp>

#include <boost/numeric/odeint/stepper/implicit_euler.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp>

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/multi_array_algebra.hpp>
#include <boost/numeric/odeint/util/multi_array_adaption.hpp>
/*
 * Including this algebra slows down the compilation time
 */
// #include <boost/numeric/odeint/algebra/fusion_algebra.hpp>

#include <boost/numeric/odeint/integrate/integrate.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/integrate_n_steps.hpp>
#include <boost/numeric/odeint/integrate/integrate_times.hpp>

#include <boost/numeric/odeint/integrate/observer_collection.hpp>
#include <boost/numeric/odeint/integrate/max_step_checker.hpp>

#include <boost/numeric/odeint/stepper/generation.hpp>

#include <boost/numeric/odeint/iterator/adaptive_iterator.hpp>
#include <boost/numeric/odeint/iterator/adaptive_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/const_step_iterator.hpp>
#include <boost/numeric/odeint/iterator/const_step_time_iterator.hpp>


#endif // BOOST_NUMERIC_ODEINT_HPP_INCLUDED

/* odeint.hpp
f59Af5LlYnFrPw7OgblbxiG2sLjYFGW3YT0qS+sDsyOiyBaMbTmH6M1s5qmKsl/KO0Q8sz6v1ozBuJNFMRvypOcb9DXZz8zSHLrlRQ4VHMLKcujx25HiaGdFmvMsLm2LwiUxDvTKqL7MVm6dNhRxZBaY4T7HmOBj64wJHhdDlhFm2L6QRcAM980oyvQo2uJTxCUq2pKkaIuoHLxMZ2XFnFfEuciCtcVNFqwtHkWZPkVbEhWWRLaK2cKtlVMgropDtAyRtnrWXz/AqtO6aZL2x+atC7Fu1nKInzRrn3w8WH7eP+jP2g4xXkhb3KplU+RA1ohZ0y+TR8tn2RxiP7O+9bOfgdWl9YhZ92G95TczuBn2OS6y8swKf/OqDNpCVpjlcCFNxl7Ir75DZGBxeYeWTsA2i2wEs4mX9qZFX5OlZ1Z8VcXl8rkzGiNm/1l/aCzqI4tmVvfYthtYV8g6MsvpH7IJ9ZFlZrasSNU98tkrhyjL7HPmuM4ok6wcs4iipq7Yd5DlZ7bj1JQ8GNsGDlGDWY2n9XOgr8kwDsb34pAVYFasQodJqI+Mt3PJl2IR6LM4h9jG7H7e7g75zI8D9yy4ktvp/Sx/tycryCzl6gYbkDtZamYvXl49j3aSWZhVenBdnleRZWe2KPzse6wrZN8wK5s0+hhyaETrGLPm2R/PxPpOZme2uVbVRpifZL2YZelcZKB8PschcjBrd/LwNuRHFqxMj8J8ZFl4DsXeDsa+gyxCszbGZwMVJpoENzNZW2Ybz9Qbg3Yq4rwK85FFwfS/hydyM/4+TWaDGb4N2DR4mdHcjO/oIQtWZryiTI+iTB9ZsNz9ivoCZPlM0jJP3HYK623z4G1xczPeJ0AWrD6/osyAokzRIniZTrJgZcYwM5bpIgvWZ/GK+jyK+nyK+hIV9QUU9YkfgtfnZGasL4YsWJkuRZluRZlesqDrmKK+RLJsMMMzmi2DW7TCXArzKMxvsJLL1qbB+q4wZ6vgZcYyM8a5FeZTlBlQxJlbB7cYZsYy4xXmVZSZqDDRho41YIZnNBXmUphHYX6FJZFlYjYnPO9Q9JkruEW7FO1UxLkV5lWUmaiIS1KYuW3wMmMUFk8WrEyPwnxkfzE7+Z8Bcp1u58D9RK1p2fVor81YV9o7hJvZkK/ir2P8yFKYpB19OyMb8uuonWtrFjX167aII1vF4qbNLNtI3q/oEBNZXPUOVXsgv876Mv843zgGfdbFIbow23X55F3kR7aGWesPoQL98hOdAzHzHz8+AnFdHeIH1s419dt8j7bQYaqTxTUovHE78jOYaehk+U15sm9ZmbnOHjmDse3pED+yuHbfPCiNOLLfmQ3v/KQjcoh3iAXM0oa7b2Be93KI+czqZis2Ddu63vp25j8/pQHiyCwwwzddyCJhhmu4CgsoyhR9gsc5FRZDFgEzvMdMERevMA/Zz8zubU31H9TX1yFKMRvQedl0xBmseLV6RZE7WVXNWhnuP4vpJ+dgS1q6WtVIg21WfzoPZ5Y3TclFmBNkLZm97NTlCvIb4BCNma01NbmNtpB9Y5J2KG30DtQ3iHLQLPlgodzRa+Gob7Ds6xaG+4nEEDrngunvqTGTdWXmH5JNvrOfLAtM/y7SRLJKMP23R51D6fwdpr+nO4asALOo6+a+mNdkhZgN/CVqFOauoswAGdpp+L6oeVhwi1FYPJkdpr/f20PmhOm/n+onQ18b7pdKZGYchwA3w/1SSdwM90uJ4XQ8CNO/R8lJVoKZqWf8b8iPrAezHplezkaZI/Tm+HHLVORusMkX5n9GfW46pmVWs1b9KehrskiY4Zlzsu6aNafluY9fhiB3sl4maU1urUAO/lF0XTg=
*/