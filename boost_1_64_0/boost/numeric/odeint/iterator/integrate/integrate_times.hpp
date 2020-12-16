/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_times.hpp

 [begin_description]
 Integration of ODEs with observation at user defined points
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/range.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_times.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , stepper_category() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , stepper_category() );
}

/**
 * \brief The same function as above, but without observer calls.
 */
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer );
}




/********* DOXYGEN ***********/

    /**
     * \fn size_t integrate_times( Stepper stepper , System system , State &start_state , TimeIterator times_start , TimeIterator times_end , Time dt , Observer observer )
     * \brief Integrates the ODE with observer calls at given time points.
     *
     * Integrates the ODE given by system using the given stepper. This function
     * does observer calls at the subsequent time points given by the range 
     * times_start, times_end. If the stepper has not step size control, the 
     * step size might be reduced occasionally to ensure observer calls exactly
     * at the time points from the given sequence. If the stepper is a 
     * ControlledStepper, the step size is adjusted to meet the error bounds, 
     * but also might be reduced occasionally to ensure correct observer calls.
     * If a DenseOutputStepper is provided, the dense output functionality is
     * used to call the observer at the given times. The end time of the 
     * integration is always *(end_time-1).
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param times_start Iterator to the start time
     * \param times_end Iterator to the end time
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param observer Function/Functor called at equidistant time intervals.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

/* integrate_times.hpp
YUfnUlSESmwawl7P3Yld8NVAf/wSuz/elnyF93kS81+ZBteOZo15BNyMuLkArueCXl8HNzbTxh5Hacckiyj/D/gLOUlB9B4Lh8k8C4aOEGILeP7VMeYsVgJPneBWNYi1C+BQ8ObBPK/4cUWUZPPj5Z/zv5v4NO2c+ba+r7EojSwWFaJv8O/187FBOGsEfGvQdkW8jZ0sakOsOKmIGQt4x2fE+NpwVOJ4093EyhvIohU+GUhcBFfzOHEtfffEBif+XYgFi8ErZ/xpCz46j1g8m/18ONa4DTHvTSFCtjNOByZ9MtkizoP1T+AWW7cQs+DzFWOJVfktYhi2srMobVkIbqLnd8npRk8Hc+jTa2DgqgBiF7zlXdqTAS5tKEFsqQRPAwNWgHt5OoPJ7mA0edDui3CzS4r4EayMrkOMg+P+Rr+2ncLWisH7yqPXu+iK/i8Hf+oNAiNK8WV3YlPpEGLHZHIwuKX7OgVOi42AHVWIEZbuqtjsSr/wqbp1iPfwx/vwruPorS7yaYpfJfYlNj7kvl3Iq74qDsNPkm+SF+1HR+DE+gfo/i46rED8AmfuggmR2HEafufxM77cD87zN/Q6nDxrvyKGEluOc91P+y2i0Svkon8nz+S6tt3ALrCqc4wq6reH674C94Gn1oHPLsROvaay70UlOM1q+uMGT/qWa6zsU4F9esTDkZ3h4Bm0faRFdGpKrH+db0p2IB56kWPEIGdiyrVeiviuAvJC7rPItQcj55vkWqoHX20KwOeR7T3kmEQOOdOCHdKOK/CZGafxsUbgMXgd7Y4thGJvtLc6ccaarIr7cPkmcGHnj8kxuxKjd1rEW2la/sf7Lqmi1lVyDnAmEXuqbWXuEHJuynU70OeNYPaz+lSIA0dpOzzBuhjXexXfusV6Cjdi9zb49yDk/xJceh9270Ks9QPPPBTxaSM4+AkhysDRG5DP7YXjXcH+38BP+nxJ3ANzto9VxJu8dzH43BnM6NkFG6f9B5HtHmxzMZy4/ATqE1Z4+3Tw7yK4Nx7uDdeu/jrx+z1sahXYVV/LG8nViSnvLGKOxDvkA4fpz1i+z7icL5bc4lr46BH8Ifw0OQ2xw78Oc2jz8G1seFF55DEH3HbHdgp5K+KLG/jRKWLmSkWMUeH0G9FfZz7Q8BBMhsNretyCnmZ0J56XJw/BRo8Msog/yA8//QlO8ZtFbC2miDph3EduElQIm3qTL752JC6/Qe2AnMGH+L15MvUGlPm3K/iylRziHjL9ABsg71LfA5/+Rgw+zTXFqZWo2PFKnl2afuwR5AvIi36HopMxecmLuHfJFcamv0Wmp/GjX9EfeU73W+RBwdRuaNsldOQBNtwENyLAumPfg7PwqrFgxCB8pRQLcPLfVcRM9D13PvfsQR+vEmPw2XOZrK9dq4j5x+BvIcS4DYpwx3/9PoIPgB0tq5NzT8U/4Ltve6AHfLMcXKHqTew7H7J1I6fPD8fIh41cBsd+Izbx/t/Pcawm8WaiKoYQS/dVFfBZuLoHOE2/zziBAVqu0w07E/RvDjEJvPkG7jMdWW8bpYq2leGV88GW1sxhxxYnDCCu3kXPcLH+6OgfvdHlCnwJW8mYCdaDSx0+41uNh8HnBeDQMOIEMtqcBhe7Cl/AfhY/toifsY8yB8F3uEKhIPhYClzbl5zuHNwYf4qAU1mTFIIh8bcaXDdOEX1rU4typm5FzvxKvBZ/hThejtpBae7Fbhejq7nH4QTkEHFl8Gv4fEPqWZr+fbzInSL4Xl9L9qWrjR3jv+2QzyHsZjh9utOS/B8MHIhvxTZRRNe/kcsi16ntwOZwbINzyZ2RFzYwlpwjmTjeAQwJ7gpOXVdYc6iKkb8=
*/