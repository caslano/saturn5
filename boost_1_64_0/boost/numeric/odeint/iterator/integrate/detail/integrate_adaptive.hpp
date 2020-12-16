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
CV9YR20b7OnIeFgj/t3NdYFgSG9wPbkhY2hg9+we1Dcf42vw6X5pcCTk+Y/z6Io6akZl5P8qNgbWDEbWHS8wJgBnro49DagHppP7dHeGD4B7ntiEH3L7uiD16vWktYzbVmDOWDQ28l1fxvOCGNecj7x2UGeHP3SCI/rWpg5Xi7aT5wSEYffo3ZfjN4diw+hqGjI+VRm5t2esCT7dDQ77EF8oii3fagzP6AVmKmA1f9dbhC75dy3car47tXDGuR74g7+/Y8vT8IMq5BU8p/Iw/A8caoNsC5LfTyT+1A0AG8BNhf6v91IZy8XeaU9/N/IgYt+M2eAkuYz3cTjbDzwbDAhGr1vWwSteoa7/ITiFD7XEdr4l53hIXtSGd54oRHxFvl0mIgPaf0fhnTXAt1+RH/Y+uREcCN34lmUMErwZRx2nRDBcdzJ2Qx7bBPlmwq36tydGpYEZ+Gdj2j8xDr/kuXXp5zU4yflB5Kf94NHILx8y7UIMy9sOfK7F2A9+W8ST2tV18qxUuM8x6gFTiHU/gNvgUhi6nDsB37vLO8mpa5FDrwWLBlYD6+DWLd5DV+2o5xFTf8XHEpjPNHsKfXzA+AjyK8y4WCV8dk8N5uxch//4Ms+H2LuLPrbswngq9puXOkE97snMTzvp746a1EvxTdeF9Bd7LMuYpXtnbK4KOF0XvszY/N1x+KMWUwSxnXGQyCj411hwmed9sB6MqYmvgid9LhA3ViITH2wbDtCb/iyFS3cagY9H0/b7tJH2POlIDDxGuz3h2sQw/03YFnbY0h9/4Z5ZyK09dbaeXFPvCjExnlhP35flA696ETPhctq8xw4h1F9aYsfkVM0fk8MPZTy4INiMHLaD433TwCjkN6Sk7TtWDdaQv5NnBEdRC1DJy4jvPXuCLyp2+DEx+j7ztj4CY8fy/mPEVuTW7DZ5LONGjX8m7lCvyCyKbbUlv48Bjzpx/QYwtyK6HoRPx2Dn1N7a0b6W0fCoKvj6fHihHxgSDk9eSjyaj03H0j5y8B5fwtXawHNWgnP7wcBHxKE+yJK8wW8feFwen6L+4eICN8fWvukLjxLMjRsPj1GoAVFDcIHvBBLLnBKpASEvZ2TbsT6+xbnGyH7EKmzsngrWEceZowp8UsMmV6HWGjGLnIuYV78J8eEhGET8GQ+fnImNDAzFZtHvvW6MQYwm9vG/FleR7yfUHq3g5Lvouxx5ThFsoCS8sRD980Tn1JkG43cFwfLtGfBd9Oq9kppfFbgVNv2kM3H/LPwYO28C/+o4Au6L/nchowMvY/v58SVw/XSSYA4AscgL/wK3bq2Cy9RHfujgF/xhI9iztCA2W4B85APGBOFNGeuxv+HIYz92Rn8a0e/TN6lnwrFv/gjW9kSmYLIbfrUYX6zSBRtm/CAKWV7BxlKRyf1OyHsIckUW61zgMA/gyZfgE+SyHhbqyvh11/fQtzYung63Oc01bai3wkcO7UZO8NjEX9A5bWqDPWvjXp3Bkojx+CY8+gkcskV7anILkFci+BBPPo8tPcbOD4/BfpBTaTCvI+d6kHNY4Zgx8LW2yFv7Znke7P6bi3C+QMaiXMm3iC0vV4MnEQebYa/rsIXHcMLQ8VxzFO5KHAuAG23DL9/qih9TU/JuQ57AeE0guHwGPl5mNrypPrY4CM5OLcOpIzkU+naCXydx7TyurUff7xFXbrsp+l7/73mBSZepAfVGL92IS7SpNXpszrvCwOOtxxhfm4Pdtoc78O+8TtRkadPVQOIaNdi7jIV+i21WtCAXMNKHutRkledoaxngzjv6Uw8bwjxb5tUco83H4FufHGLe5XJiJLXWoPHkp/hcfmTSsBXPby2YYw43vU0=
*/