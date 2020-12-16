/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate.hpp

 [begin_description]
 Convenience methods which choose the stepper for the current ODE.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>

#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/integrate_adaptive.hpp>

// for has_value_type trait
#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>


namespace boost {
namespace numeric {
namespace odeint {


/*
 * ToDo :
 *
 * determine type of dxdt for units
 *
 */
template< class System , class State , class Time , class Observer >
typename boost::enable_if< typename has_value_type<State>::type , size_t >::type
integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
{
    typedef controlled_runge_kutta< runge_kutta_dopri5< State , typename State::value_type , State , Time > > stepper_type;
    return integrate_adaptive( stepper_type() , system , start_state , start_time , end_time , dt , observer );
}



/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class System , class State , class Time >
size_t integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
{
    return integrate( system , start_state , start_time , end_time , dt , null_observer() );
}


/**
 * \fn integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
 * \brief Integrates the ODE.
 *
 * Integrates the ODE given by system from start_time to end_time starting 
 * with start_state as initial condition and dt as initial time step.
 * This function uses a dense output dopri5 stepper and performs an adaptive
 * integration with step size control, thus dt changes during the integration.
 * This method uses standard error bounds of 1E-6.
 * After each step, the observer is called.
 *
 * \param system The system function to solve, hence the r.h.s. of the 
 * ordinary differential equation.
 * \param start_state The initial state.
 * \param start_time Start time of the integration.
 * \param end_time End time of the integration.
 * \param dt Initial step size, will be adjusted during the integration.
 * \param observer Observer that will be called after each time step.
 * \return The number of steps performed.
 */


/**
 * \fn integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
 * \brief Integrates the ODE without observer calls.
 *
 * Integrates the ODE given by system from start_time to end_time starting 
 * with start_state as initial condition and dt as initial time step.
 * This function uses a dense output dopri5 stepper and performs an adaptive
 * integration with step size control, thus dt changes during the integration.
 * This method uses standard error bounds of 1E-6.
 * No observer is called.
 *
 * \param system The system function to solve, hence the r.h.s. of the 
 * ordinary differential equation.
 * \param start_state The initial state.
 * \param start_time Start time of the integration.
 * \param end_time End time of the integration.
 * \param dt Initial step size, will be adjusted during the integration.
 * \return The number of steps performed.
 */

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED

/* integrate.hpp
MBe26f1Mm9ZZgDVWv9P4+fTeVjnfGwlrSIpMTU+3RiZH94yLsb38T0cN39J040WbvextRdqDl8l/vOz8p4lh//r93tL+m5r8x8vkP83t/Mcnh/t99fvtztn7i7SzZtLO/KRP+Ns/04GNe5lsPMjHfJ3RdkfnfO1sPFi+u4Vh48b1JhufKm3cU7/fZs+Nc2HP2rzIAP06e6XyDGw9ULP1P5/Ubb6lvc1jyyGObVm3p/zYcCuzDf+L9uT/bLvOjvXZjhjP0HQUarK7UDu7a2PSsXautbSbtia7CzXZ3Rt2dtcuh/vD5f325wwsNuwuTOo+QmJwe/tnOrC7UJPddfIxX2e03dG5cDu76yzf/aZhd8b1JrubYI+t2npf/s4mdmlLHSVuGidsdtTFAXZ2zCV2vpWDvflLe/ub2d7+BRvhvqyattZHOVbJ34buo+x0H23Sk3ZdN6n7GNkW+3P2Mdr+vto5nLOP39q5WGkrcfLf7vLfHj6yDyb7sPqYniVybp+9jUVJOWjXFStquy7B7rrgnOpz6SZR69/E15mkoxM6l5S2Z7TFZHvfYHv5XXgqx7WYHs+/2WwOW+z5Z4wSvWQ/BxkX68cTOe7E8cz4p/uz8y0O/VhkoNZQzS575dIuk3OwS28Zy1PMdplLjvqceB6VQLOkPctf2W051YR3qXZ4l26yWe1cmrS9DBPepZpsPtPO5vvmcH8/eb+jc7UdnnPMS/tIPOovY/AAadcD7d/rwF5TTTbPolXTdUb/HJ3rZ4eJQ2QbhhqYaFxvsssxDvjm2/ydpRaJh4MkHsqDOha+4wALB+XS5oY9w+YKYHPDzTaXS7tp8xybS02N6heZFJcZKT8zn/UYuxPmfGmkyQ5H2tnheyZ9aufelbbyvskOR5rs8O92dvhBDvePlvfbnXMYd0dJPY+RNvah/TMd2NhIk42N8zFfZ7Td0bnRdjY2Xr77Y8PGjOtNNjZX2liqKe6O5W+HSrlps7ePsuzN7gKZw3ziwPY+yqXtTcjB9trIODzRbHv/pv14muzH085+Jpl0pZ37TOp/ssl+PE32M8XOfqbmcP80eb/9OSN2259zjGOfS/1Olzg2Q9rYTPle7V5P+zzJ/tkO7M/TZH9zfczXGX13dG6anf3Nk+2bn2V/8vpc5NSz+NuUWOo5yOxc5CCabc7RbdO4WbPHBQ7scU4u7fGL58TfL832mMuc2NsRp3mBGu0iySWrO35OWGs5jZA/NO6T05q/tEi2c4oI0bfMaGlFPMxg72fXgOddpD9f84UlJl/4WrZvkKzfLdZllGLXP/McM8ZXtOmIUex3EesflRZnm5P2Ffc5w6IY/zDNdTZWeD2d0/IN15UWKXobTS+43kF+52epuYaa1W/tPXa3yFktz7hA66/j74/8B56ryfFbkxyXm2rxK3yMsYFaUq4r9X7pCNe2u4OnpvGcp2Plq7KPU9k3xU97iKmV9qf09rln+25RYiwzmITx3Z8U0299naP+u7qsY68xvb+gAxulRkW7wmzf/JP9ruuQM2QNOunelfVL+sZ6U2613iTLjXb4vMmEz9p1GyQ+fy/bKZ+VhYVbfEzXCfN1PNuUx2TI5221w1btnJtxzvwMmf84us+ujS+QG2XJxciN7E7Y50byHXb4fEHmRus4ruVBm31MGpC50Q9mfJXHtnEsPiotPlJbtCOPbTdf10z86Vgl07HoOCZPy32bdvBbflc063dqVGakcayE2Pk0FzMap+ddu8x5F3i+Owc812ytIHi+R57XbLDgM2ytVe4wIFd+pdnqPpOt7pf23z3b/PY0hj9YQWLCQid7LJTHnTU8zXqPce6A3qcUu8bdyJq/+6PJR4v+B+M=
*/