/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_times.hpp

 [begin_description]
 Default integrate times implementation.
 [end_description]

 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED

#include <stdexcept>

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/integrate/max_step_checker.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {



/*
 * integrate_times for simple stepper
 */
template<class Stepper, class System, class State, class TimeIterator, class Time, class Observer>
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;

    stepper_type &st = stepper;
    observer_type &obs = observer;
    typedef typename unit_value_type<Time>::type time_type;

    size_t steps = 0;
    Time current_dt = dt;
    while( true )
    {
        Time current_time = *start_time++;
        obs( start_state , current_time );
        if( start_time == end_time )
            break;
        while( less_with_sign( current_time , static_cast<time_type>(*start_time) , current_dt ) )
        {
            current_dt = min_abs( dt , *start_time - current_time );
            st.do_step( system , start_state , current_time , current_dt );
            current_time += current_dt;
            steps++;
        }
    }
    return steps;
}

/*
 * integrate_times for controlled stepper
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , controlled_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;
    typedef typename unit_value_type<Time>::type time_type;

    failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
    size_t steps = 0;
    while( true )
    {
        Time current_time = *start_time++;
        obs( start_state , current_time );
        if( start_time == end_time )
            break;
        while( less_with_sign( current_time , static_cast<time_type>(*start_time) , dt ) )
        {
            // adjust stepsize to end up exactly at the observation point
            Time current_dt = min_abs( dt , *start_time - current_time );
            if( st.try_step( system , start_state , current_time , current_dt ) == success )
            {
                ++steps;
                // successful step -> reset the fail counter, see #173
                fail_checker.reset();
                // continue with the original step size if dt was reduced due to observation
                dt = max_abs( dt , current_dt );
            }
            else
            {
                fail_checker();  // check for possible overflow of failed steps in step size adjustment
                dt = current_dt;
            }
        }
    }
    return steps;
}

/*
 * integrate_times for dense output stepper
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , dense_output_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    typedef typename unit_value_type<Time>::type time_type;

    if( start_time == end_time )
        return 0;

    TimeIterator last_time_iterator = end_time;
    --last_time_iterator;
    Time last_time_point = static_cast<time_type>(*last_time_iterator);

    st.initialize( start_state , *start_time , dt );
    obs( start_state , *start_time++ );

    size_t count = 0;
    while( start_time != end_time )
    {
        while( ( start_time != end_time ) && less_eq_with_sign( static_cast<time_type>(*start_time) , st.current_time() , st.current_time_step() ) )
        {
            st.calc_state( *start_time , start_state );
            obs( start_state , *start_time );
            start_time++;
        }

        // we have not reached the end, do another real step
        if( less_eq_with_sign( st.current_time() + st.current_time_step() ,
                               last_time_point ,
                               st.current_time_step() ) )
        {
            st.do_step( system );
            ++count;
        }
        else if( start_time != end_time )
        { // do the last step ending exactly on the end point
            st.initialize( st.current_state() , st.current_time() , last_time_point - st.current_time() );
            st.do_step( system );
            ++count;
        }
    }
    return count;
}


} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_times.hpp
paG/AITpi1x64Phs/pdcGvqLumffqLhkB8f9pRz3iznuLxs27vM23SvTY31y/B/O5aFcL6dcp7NNZ0fnugZ7OFa/Uqfe8qB9vGIH5bSNcsr6B1/1yEnXumFtf3enuJn588FTfGb2r5uS9XwH2Eq3RJ7zma/U/HdAT78a491Jl0D4Vzr+hI9iR4vEjsZ8iISzsWCNKgB/TPZV4hl0pTqG1ji5T0K7r1Ltnka/Q/O0Lbf5uu3ed312kGaon9fIuM87V33D6VPKQ4exaae4+Ah9A4P9mVQnMMKvk3SQe9PoWut/SZ0WYVFAKmszOI68NvV/8B3g4nex/fPG6N980+UPOmro+5xPc8MOjtkbOWY7OGZu0mPGP/cNb/DoaE6eq3zy/B/5xaFMb6FMO/LrFMdqV/ca3EWQAcq7g3Ucn+0DRtfoA7Fc8LK8DXirkleJa8sih2NVTOCiYatG2QdFIeV5R9Yw7eiNgkMdu43yOHZ0Pj7D6ziNikVet2f9m9F50REGBc3B5pHuHaR7xgh9eq2vT9PBqH36HeTB5or4WOa7br0LcyXTd7q1rnSuajhTlnsT7i7j27IJpvcJlb73y+ktfkO4OIOU09kjyOn7bqwPunguO+r7H+3ezBsMB3uQPYdYqu47XDjVxXHCuii+1Tkvbdfz0v/Ad/fa5//Bd20oz3sozy3xc/FSIPZ2WmoTNKsLhilP/sZqTE2OHeSq4QkL/2Hd8DfW7t1BG3+f+W6939j4vGbGn+Vk/9yoepY2euaxuZzDi93Y4vQtZaBfuTs2Xr0slfwgS6sM/oCmlu27aRy/+txsueiruztSEfRCX0V/Z1J/D+bbAA8ouc1WY9UqLaHiQ41uE7V+W7Nos3Pz3U/qRn8PE3JU+yuxEe7yf+rs46CmjzhnMh8WD7OdcqfjwWFzXwP5WPsnOWOzgePXR3cWQe0VPFwnZ6geMftmjyKNv9h+4c+5f/IL4nr7bAfXOEP6vyT9VWP0+0Zbx/4Vv3ezTIESZN/N/fUO2o3HaTeya89PjLDeK/VaPmglkh+J57zHIGszxkyO2O0nKd9fjTAmnnLt6o9RgM6POh4q3VzY294pY0hs1Qg+ZalnDIm9+i9xVwJfZ1HEv7ShDVIlLcUWqba0tWJtSxtKmqZtTJqkbUqbxCQtRdTHS/LSBF7ywnsvPUABFQERFfFAVBQUFDwQxVtBvO9b8Va8b04FFVD/u9//fTPf5HtpUvGn+mx2dnZ2dnZ2dr49ZtNjxUHaKvb3AleHso+LYNMEC3s4jEP3C9UfS728moCFKjA6jAOamDmJ9YjHpH9dv/yq5JtPwRa2Kq/D13ZotKi+37C+t0+gB782ehD/Tvfx7KTfD+En/fYU7w8l8RTqD+cU+EjRHPMp7yMhiXpKPtLvtI/0GKw9XvY/GAfv4bww0Xd5ddJ3Oc8l/kG1cS6///ZlsrlRq7M2Q+9V0X8PyvjvlfTfS2t2f9K26zBsS+8U1oYP9/vY6e1fzF7q3UgH9Nll/8n44/RnqujPlPYv70nev7T6KVwmIhziLfApfPO49t3H9iXa/MPQBUfzAdJMfJd9it/kjt7fJsHjVNaRHM2HDrmGfni225+7PCS/U/PLHM2HSfPrsf10iZF6v9etQtTDJdvwVw/PSFcxDtSDHt4v8iadv3s49Vnh/9PD09JslfdIOO7JudRv3qjm2ego7dC8b3QkfKNHJ+kbLTvE2u+/6CNtpp359zg7U2Y9q8wa1rcpd/qw/Jsx/mtDn7WiNjxrMr02xKusDfHecMjvAJiHlox7H9nMYf/9ekC4Vj2KraRA1qp9OoxrsJvrJTNq1XrJY7I/FcoGMomdo6qibI6sncA2HEY=
*/