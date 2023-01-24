/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_fehlberg78.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Fehlberg 78 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_fehlberg78.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

/* generation_runge_kutta_fehlberg78.hpp
2/taKPQfIEZMGDZs1SLPkS38IUfWmDz+6WMHmFZQJPL1vh0bia1MPlbNVt7Mqu0e1z1q8uTo+5P1DkPxwSy+5auote6xq/06P6pmyWGVrxd8Sjb+5vp1Vleydejpu82SuAS05fHU+P6t8OQ/+8u2JT3nNDSJAZ4smtzyjcjS2uOPzob/UNt8JqvYyv5tu90hf8GpA3UdMiatgHhfMKrFDDz4bwzYLOONL7ianq/EaEz69PKCbV9QuGf1NrPfLgDYjPiH/YoF5BUn7uDTU9I9uKtDBa6yreqHnr2Ky41B1mxoR8TV4/ywXgeTtvRXeMRFuQtft4JXzhP0ZXAsGp6iSF7jtW/v4xZW59oaUQFhlqaoWDzDqY1s1Hu8BLMRbeXXtnb9aFhRS1DrTQsszvlA8+dngbet7m+p0mtx7Q5ZBbnd7PiapBGTCYBE5u7lS65blUD8d/tzbU1ruua8w3KZTkOZSM8epZMrD7YIY7dLuezurg8CO9cLxqSih7DZjhuN1jmDPA1B6bvBqGNpG7/LgP7do2Wf9E2uzrQwOVbGe3Jj8VO6lpaVk+aYDHgyXz33hja8nDLarhs1cWzlmUifTL6W+hFqr+hjKDjckIHIz94rwPaJniDvvNhQeO047btwb3+Sn0v1lreoovuZYVy3KaYi76yav1f5x5R+iMvp3ASzE9TxbnFbbUtWRG8HJifVdL7sh8IP/AC4ocRL
*/