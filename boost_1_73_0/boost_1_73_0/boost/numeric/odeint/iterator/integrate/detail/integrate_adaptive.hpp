/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp

 [begin_description]
 Default Integrate adaptive implementation.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <stdexcept>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/iterator/adaptive_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>
#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer>
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag );

/*
 * integrate_adaptive for simple stepper is basically an integrate_const + some last step
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    size_t steps = detail::integrate_const( stepper , system , start_state , start_time ,
                                            end_time , dt , observer , stepper_tag() );
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time end = start_time + dt*steps;
    if( less_with_sign( end , end_time , dt ) )
    {   //make a last step to end exactly at end_time
        st.do_step( system , start_state , end , end_time - end );
        steps++;
        obs( start_state , end_time );
    }
    return steps;
}


/*
 * classical integrate adaptive
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
)
{
    size_t obs_calls = 0;

    boost::for_each( make_adaptive_time_range( stepper , system , start_state ,
                                               start_time , end_time , dt ) ,
                     obs_caller< Observer >( obs_calls , observer ) );

    return obs_calls-1;
}


/*
 * integrate adaptive for dense output steppers
 *
 * step size control is used if the stepper supports it
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag )
{
    size_t obs_calls = 0;

    boost::for_each( make_adaptive_time_range( stepper , system , start_state ,
                                               start_time , end_time , dt ) ,
                     obs_caller< Observer >( obs_calls , observer ) );

    return obs_calls-1;
}




} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_adaptive.hpp
zsJSwNPquOCJ5y4kX9VYO4dITl1GWLjITjpaGZ49x1EYraEQn8HIyG2ItZBjIBNK98kCoZekiv1MLHW14BXyyq/mFgJknsgszQp5QuQXkjS1JQp+dd3UGKdXukjNoKoeQrQlw68G+hd1lvKQX/OQ/WUX2V8NBDXi3jJxTxPXOVgxRYOHtlxHsJBzB1K3ewKry3LSh22mPDbnSKG50TIc1Iu6fMG9r6rhvi/VcNIsIEnkyQWGUFnog/1B0R+Bjc24GykXRKeu+4pyL4uaXxbzIWAoUqgbHA89H2K3zYvziiX3LtwTElmpnpxSeblNzhdY51x16sGkMeQpt5QzgF9ajoN99OJ8JE64Pef2OYvnluC7Ej6WRRRzy/eLOXzI5IVsfRkwk1IAv/II1SilzsOugjZwd+WVhEmIETYk+qJ0dqKydmq9Fw5HvUDqt4CnedQTU/0XtH0Pu0A7L9i+jCPFwAPpiOoBuODVjy7scnXU3tX3e/DBsU6kfKbWRoRxymjzLg+gvOxlmKkhJ9vc3hscZk1cArVHtkVqzVtM4CWzBR4AJYm1WApRxEXRiwqIvn0z/0Wzb7sYtLJu0EM6egGdXpXrBaXlLmxOqYOHWO5zvS/377NiPbVlNQaqOd3Ktb+pZ/Ok3LNRHQDQDxoq
*/