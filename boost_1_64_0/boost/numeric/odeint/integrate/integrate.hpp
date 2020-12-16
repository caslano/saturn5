/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate.hpp

 [begin_description]
 Convenience methods which choose the stepper for the current ODE.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>

#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>

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

template< class Value , class System , class State , class Time , class Observer >
size_t 
integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
{
    typedef controlled_runge_kutta< runge_kutta_dopri5< State , Value , State , Time > > stepper_type;
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

template< class Value , class System , class State , class Time >
size_t integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
{
    return integrate< Value >( system , start_state , start_time , end_time , dt , null_observer() );
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
 * \attention A second version of this function template exists which explicitly
 * expects the value type as template parameter, i.e. integrate< double >( sys , x , t0 , t1 , dt , obs );
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
 * \attention A second version of this function template exists which explicitly
 * expects the value type as template parameter, i.e. integrate< double >( sys , x , t0 , t1 , dt );
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
/A1+/Jv89PpjG9N/vj7Q6xeY/lTiqnjXsCF4Y7Ez2SFvhVa5d9KwNdbZk2AcfUCqO4mMG+3h5Qv5HoOzas7HW+dmFa70EPT58Gz3dD+N8Ai+y6o7jS3+PnyM3/eJWWO++1S576/ruuLrU14m3XEsR5BU+Ld7uLmAbeV+3DTU5ekIzpzGuuOpjVq+rgDvvp98GMo/rV5q+QxXz8xH7QSaWL5jFuh4nq9jfuuS95k609A4w7zHye1IP24a32Rb58l97NNFDuh4ZRM+/TSsbFzVuCwjhI6i3dFHEfjxXri/5YF4xkEO1qn/TNxb4sPwDJVXIfJqtjlJRMi/J+wtNJafSbv7ar26nyttle1M9vrS6ox1mrmfLeNPZDpJI+PPucz347UD+OUZUrl2Kfp6/QD7cUOsB/fNn3zYz6DtiZ8SWXfRPz7lv4Bp5FsR98BYhxfW0++VqruLdN0Fvodom046HeFkkzd48svzHcpz8SDyXKLkmUZ5Lo2Qp5t+kBjQb3OhTLnr0MvUeHRJBP0KmU9Cr+Ex5UozxiQqgzBw9Kkl++IMR9vLEHTpfJVRR5H+p/KVn2m/z7SUh/MCObsXxLV3rpe3OW1/LWegTP84Gnveqm90c88iL9mW5jmjq9z3j/7su9Wz+A3kB6r+xrn+D3xM38cYeXuI886obwLbaUs3qDkrZEG5+Q2AaW8Gjvv/ZhzezfsxaJJP9PzjVubzQ+bD+Wgkb+tH4namvc6lFXsvDPa62w+iDhdU++NQqiM+w8u2v7uUvm7zsTGf7uvHqUtHuHqPtLUhpPPlu8eM+1Vl4X2ne1mOGjUfri2TuZbztxwx33zY+Oz9eb3UDfWl+uFw3fzSYA8pzo990GB1/26xO9iOIZuZA8u8TtMfERshPXf++ajBRL0R8zgwC4ewT9nUjI84gVu5KEK2zp6sl/1JzNtcW/0b7mVvCJ198CePxqegi+sxfrk560C0zG3Y1lXcefX85rnenUXKntV+Rtlq6SBz2Ez7qZd6wtwmWN/Z9vOsmk+n2SejvUGO8Hz6Oal/uydLrNT/72nLiIf+bDrZU3zRpHtJ6piY3L7iZcG4Ocw2tb+AsMO8ouxtGzG6jfxJ0Z+qBx9Df1WNUaeQ9hTn538xac+qN/uqQVrYjqwh/mrWDW9ZmZHub0x3V7mk+4fpM9424+M7DFdy3fxAuYyXpDNPqXst67sZ2QsEL+tkmz53LPemSnoJA09Z7Vp4V9Ddu+Fq371Kxn5Hu0/vV3EMsHIXThWdXF8dnhPsITIxLPtiDGveGEvN2XGhg3duGYrID+kcv8uYvsrMWa5AvA7faMLbTfhaE77KhNsrc/deEZcjX/nUMB1yhOgVhn6joe9n6NsNvdLQrzX0KkOvMvLVGPpVJn0t6Fx7sC8SfyF6DWHXHnWsl2SBzMXY79Cfsuwn2PFqSsZmlO9WfT6yDn7xdDt42/QXH6Fd76DtCi9pk0iXlUt46XLwHC55/VzxSkt7ZZn0Xl30GDx7qt3X414nf3YcmMN8f8p8mY/aa4zO5xNTZfywMunx45PAaZ5WHs2zEVjrd9GO9fOVHW1F+qvHmbcWQNdndhp5loxhvo8md2lXItyqx3XudciYHj6DdOhU7rPk7H90YXYf8xPr8+dbkgmcwO/BXgXH88VT1Rl0N54397T5txrmy3zdxsqcXfa+rF6WKt2tnBi9T7xc+k9gwva6UuoJtIHrfpXUAbDBT9dBC9sV4s25JcmLeVMujmfKP+fkqPlcvnterL+jp8o9Md5RQ3139hzvSRh+qPrTx8u9k7WqPs7y+eM8TdP8GL5aMxeJcHnJOCv7weAbOm9zRLXIMYvnbWKSD2TyZ52rm5s=
*/