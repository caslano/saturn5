/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_n_steps.hpp

 [begin_description]
 integrate steps implementation
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>
#include <boost/numeric/odeint/iterator/n_step_time_iterator.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
);


/* basic version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , stepper_tag )
{
    // ToDo: is there a better way to extract the final time?
    Time t = start_time; // Assignment is only here to avoid warnings.
    boost::for_each( make_n_step_time_range( stepper , system , start_state ,
                                             start_time , dt , num_of_steps ) ,
                     obs_caller_time< Observer , Time >( t , observer ) );
    return t;
}


/* controlled version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , controlled_stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;

    Time time = start_time;
    Time time_step = dt;

    for( size_t step = 0; step < num_of_steps ; ++step )
    {
        obs( start_state , time );
        detail::integrate_adaptive( stepper , system , start_state , time , static_cast<Time>(time+time_step) , dt ,
                null_observer() , controlled_stepper_tag() );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step+1) * time_step;
    }
    obs( start_state , time );

    return time;
}


/* dense output version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , dense_output_stepper_tag )
{
    // ToDo: is there a better way to extract the final time?
    Time t = start_time;  // Assignment is only here to avoid warnings.
    boost::for_each( make_n_step_time_range( stepper , system , start_state ,
                                             start_time , dt , num_of_steps ) ,
                     obs_caller_time< Observer , Time >( t , observer ) );
    return t;
}


}
}
}
}

#endif /* BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED */

/* integrate_n_steps.hpp
zDuPNg9mTYAztoKtF92DzK8QB4axvmEefgum3XemT7+TT1JTHgr3utxcqy3As3mXL/x9ynzifSZ88xrygbt2FyrvJOceTMyglpHMGNZFsHkpa9TEB8SXS/hVCPZfBVsjvmhjVNcnU4OEy7/nRr7xFfznAGsOiBnnXKk/kYOk0bfUQWAfNjcZnth/InZIPaxnK+QMNtXAvpOPYRNw4u7UMyMvYlPEqYRW5OP5GO8jpw4H7z8oi/9NEXqe1vohPK0XNsB9RT6EM0QTfw8i617k0H3g6MSB92sSH+GsxWnfamyyy1R4Wl5tHgxxCfxoSf40H3uNI68LDcaO4Dw/aXP4CsHziWWP6L8bberM8Vbg8FtwlVfQ9dm2rLU5BX7NgN9pa3JSwW5kNB0sjCRWNMTPXqdWVQR7ag/PGXWXeAsvPYCdP9gGN8e+x3fBJ2eRc2jzCoohr/7E9AmMc/Ccl9DD1V7o/u/kBciwGnYQ4YLeClJfJoYvaA3GliKf510pFeCC3wm9bvpZOWyV3DZqEnwHHtNiLr6Anzq7k2sjuxqnsANt/JL2CH9iDRjsAm4M9wfbg8DsxYxNJIHhjHENZAxv+SLGmOETEb2Jx2XhaB9RUz+msEaEGhJELqE9thMCH43mPY2QK7lA5q/YMnh+lLHlk9RoQpIZiySPTRsBx2EcY90dfGEs9UTGtBWwoAkxVykIFirIHlk224CepoDL+Nfgi8SWdsRj2he2XdusS6uxUnegppoEhlwg3jmBOWUmUc9i/DnfWvgHOdFS8G8LPGqeYH7TbmonLoxVFmN8ljFzJ+LhwfXEajAgsQdzqOKpSfdAj8Szj9OoH8xGnvfgBG/BKR4zj68tvowOU6LBFOxr2TLuIdcKK6HNT2ZskdjZ/wE+h34aEDtm0ob89LvycMaT9zCn9gBcHH+Y/gAs7UZsYuBp/7c8KwKd4gPn/bBVYtUdMGLtaup0L1HzQZaVWzBPgPVzCefgUo+oFfTD9h/wjrXUBcCm0ffBjwK0lbzhYSNsE32rNRkzSGVMYR91IAH2kQOVumhbc3uMcemJR5EB/neeWHoxgNhzldgMVt2mxnJ6FPq9QMyG/1RDH+7YyN7v0D/68ES2G+Gfl5HDx4wHdsRnBieQM8BtJ8G3o+CMtYmxN7Dd/HuJc8Rh5Z8s3Xe8zmUfB/D73Achm5CR7aEQkr1nZGWTxzrHXseeIaOhSBRFRmSPhMgmIyMzsmVlZ++R5/075/nDC/e579/vur7X9/v5fL6f6/rdR26vz66npJeX+ewC2vnMn7gqNXxTf9qEWB+2LzxZVZ6+xSG/qI9eXsvzPo1N62y7ri+yFovg15+N6S598GJ9W+k3QkS9PJaTVcrwrowzJc4s4TNvJ5J3ZWlbnm2rcmrsLTxfiXekP2ieIkIzZB7ydF0PmhJ21a+ph7vgczBiyb/8nB/gy2FY/bb5XICX2/iI+uL6g+kXeby5GpyhQe47t/D6BPn4q766rd4kG78L33SD1yv1zzuCtbRW+Wi31t/DunPWon3csyZR4lNaX7JvLPxWy/EW441S8lZM/32Xz+J682jYD4J9xxc0WBFxlOvlEokd/TpS7/5He39gyE4eWkec94PY/Rj43vTzFK9/RK/3UysH7KuuLMsvruDvUXHPOR6v6Xv3ztEh7t/8P/AKP9Zawz9OjRflfwbjzllW3Bqo49r0yTBwMdH7T/D5onAefGyVPMAW4xttb6UKb7MYXa8/yDJIvn4uL/DFi9fxKl+6aj21OBSe8lL6m2+RD/gssHR6AuNs5yzmYu+R72/9Ye86n/zBb4U3x50v/ir4frFx9MZZuWt9alnrpPYX+j3SP/BID8K8W/Y=
*/