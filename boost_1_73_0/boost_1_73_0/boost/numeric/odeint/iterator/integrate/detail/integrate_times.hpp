/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_times.hpp

 [begin_description]
 Default integrate times implementation.
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED

#include <stdexcept>

#include <boost/config.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/iterator/times_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {



/*
 * integrate_times for all steppers
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepperTag >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , StepperTag
)
{
    size_t obs_calls = 0;

    boost::for_each( make_times_time_range( stepper , system , start_state ,
                                            start_time , end_time , dt ) ,
                         // should we use traits<Stepper>::state_type here instead of State? NO!
                     obs_caller< Observer >( obs_calls , observer ) );

        // step integration steps gives step+1 observer calls
    return obs_calls-1;
}


} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_times.hpp
cwWnaHt4l4KUTFktGFnEfFhNoiDdxiANVVVH4O54wsbeiIJml0kbtK2Yei/IBZVohjwrD6gt7ckgRQyK6mWJ7fIFyn+4Y1T1lNItR7XrmC84MkVoG8uOtZTTbeYyd8CUH6VkwyXONoLrbwDi/XLdiSPJRJYPErCnCPasTlPk9usjASmUPhdYez6gq9YlhlTRSwVLzc4zuj5PyRPexZR/4oCXO3HWoGRsxYVPZWjrtEISKyXs0S1SulUEPLblBdD3J8fy4ugr+M2OHJL9QH1nO5j76FPDbTwED+I2vMAjacyVWrm1E+ThYcui0ILkhXqZ4hz9TOaBePjKihv/CD5Rqm980Hk8Hc4c9Y8ng+brQVGW4m0WGT0g1QL1B/mB+IqrESWgLmmEutYZ/iGKZmpbcnKdX4QiZqYn7wdlWfVFFsW1mm86mEzNwckJBPH/jE/Mn/uHZauTKyjdkB/gt7z1UVzOKO2ilAFBS9W5aAuYEuYHcjQb3gbDtDC3Etw388yPZpZvYv+ujdtpvj4e/9w/Nvt4S3r7BW3xwBz/Uty8rl87qM5SP0hZ75I364VqgBf0w+SWWKh1dAsVn69nr0R0S+bK0tk+t0KMI5vyjWo3BU+jOCVld0ib43dTk9wD3epg7bA3g/7h4KTDescS
*/