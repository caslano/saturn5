/*
 [auto_generated]
 boost/numeric/odeint/util/copy.hpp

 [begin_description]
 Copy abstraction for the usage in the steppers.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_COPY_HPP_INCLUDED


#include <boost/range/algorithm/copy.hpp>

#include <boost/utility/enable_if.hpp>

#include <boost/numeric/odeint/util/detail/is_range.hpp>

namespace boost {
namespace numeric {
namespace odeint {

namespace detail {

    template< class Container1 , class Container2 >
    void do_copying( const Container1 &from , Container2 &to , boost::mpl::true_ )
    {
        boost::range::copy( from , boost::begin( to ) );
    }

    template< class Container1 , class Container2 >
    void do_copying( const Container1 &from , Container2 &to , boost::mpl::false_ )
    {
        to = from;
    }

} // namespace detail



/*
 * Default implementation of the copy operation used the assign operator
 * gsl_vector must copied differently
 */
template< class Container1 , class Container2 , class Enabler = void >
struct copy_impl_sfinae
{
    static void copy( const Container1 &from , Container2 &to )
    {
        typedef typename boost::numeric::odeint::detail::is_range< Container1 >::type is_range_type;
        detail::do_copying( from , to , is_range_type() );
    }

};

template< class Container1, class Container2 >
struct copy_impl
{
    static void copy( const Container1 &from , Container2 &to )
    {
        copy_impl_sfinae< Container1 , Container2 >::copy( from , to );
    }
};

// ToDo: allow also to copy INTO a range, not only from a range! Needs "const Container2 &to"
template< class Container1 , class Container2 >
void copy( const Container1 &from , Container2 &to )
{
    copy_impl< Container1 , Container2 >::copy( from , to );
}


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_COPY_HPP_INCLUDED

/* copy.hpp
QiFaARDWqHj482HOp0Tq9sm89Inn5TXGKJmquku4TrCOhr5idpr0UJ4laAtnS2GM8AQIZEEo9eir83/+I8vbiWSRv8uWQLKod1hJ/8Jg4f1bblj8pE5KytHGR5X2e+coHIInOvweL9GazbWNqNBJZH+mYe0wD4qH4YHgDl0OgdYUfZJD3wytYr057jbK5lkODCGCF0EX4j+3Ca9NLZFV9KeAdmDkCrYlw/aK4DVuCI4oFWRN6mdVRpO7Qdwcwwkuqw0X3iumFhiYVjG++vEcN4YlHNdI71yY7qe3+nF+wuiAY730ngGTHND4Ke/xuhyDd0tNmBx1VG+YQ2uuzvFDa75+x1YVulTnAGRWjQmCxg3xXBdieR4teX6dzz+9HP7B4GaVbgNDruSPcXfG405sdTThqzDo3Wp9OAf5pVGXAwuWXQSCn4r9+3jsqTqHJeOwNbyANEVCuqNaIQ05MleJ+REK1F6ZH/4I8f04xBnID74KytLuoLQrKPslFP4I5XAcymxAwVdB2aeg5EooVByWCMlhlZAsVkLij5Cc1hikbwASvqp+mHk1GJ4ZnMkY6HmchVnwhQwizv6VTbH+arYSMmlL0viPL/r/QY85Hzj5ipE7ZZGT+BNuLMG9JUlihMnJS8vD2F4k9/Re3h7IiaSfsEkWJLHHPmHHsdGDSH81ZG/kUmclwt9U5JRNFt80JOcnMER/PXKxdc6qFbaxbH9uoIa+IsVkrneE+8YAIKvwmdnU7VF+pR/gdYuxmkRHivHNsWI0pRm7vXSjMNrvYgFHQA+z+PgFG043h9PUgn07TjcfrcDJ+4UaFJeTREs21jtzv1NNl8aE/O2VjFy6ird3yOx5sE5xeU6uYsIbzBXxT+kSXr3HzvPPrR0Jmn3ddnXxbCb+nHx56Ql3oz5/hZe3zMTOQA9/Iba5dS0l63/OKv1XkbLY8H0BjXCTlU1A229JjdhSYLHzCq8W7hsrNMd37MRthml09Yr3miSORjrbnQigwkbkEf3qMqu73LxqTVLDxPYdTJ4HrFlqRN+8XZ3AcWJVydJ0SjpsuE6K+exWEgwDFPyWR9SWK8tbmVJ5jV9sQzwDp+IhT+OcXiaODk97wfAJXK3mW0lEOgmuiv8wyyssRiXY0eu8vnLRR6bh8OHqtZ7il80yZGvvcnEYiai9x2kJCbTvMBII/oQ9VzyFUK0un1iqItIt+wNo7d5mU2Ku8+CORF6U3m5QheYBa87kxATdKT9qjrdH7TyiWf1381aBXKzF7ArabrNKov2d8PBW9qy0iR5IUnOjISo0D76VKeJbdPldrPps2m9V9b29janmZu/BLgMk/t5yPhTDjayuHJxlJ+nKOFx6X0sHbiZg92rUdpiwJOpsglslwXlaH39eHkj62c7/gkfRVwYJ7lckbyCTfVF1T7/ZPcWwpljPnAAj9N1s5ZEm9sw9XffMpQjAnvljRV7OYscsF8PoqjpmOLFjlouGJrNjzpJdsq4poUte25TYJf3i5q0JXfKc7UaX9ItvbU3ukgR9dVPnLjkQodglP9yW0CXLxeWNRpdkr0AiuWoQSYrzl0ePqxA/Rrq6gH6mgdoea7we71J78fxGYy9+RSMJtk6fH/dWi6saTfrV+T7mnE1SGp8sAoNwfG9Go1kZ/cuLxQgVI29/1UuUSt92RaOcZCvEYtSGX7yDL6LKsznHpeiTgpyhG0HRHKhbz+D9qmS68hBikYaU0/Vq8uTJeNZrOE2jEZx6jQcmc9JPerQsdDxt/7WpbvEb1ZoHdp/SUJv6MVyCdlK0Htg7LbVr4lR8/13+jurP4k7AwO0vmzH+ZxPwXHx0YfZrMEui4qZ4V3YtfR6uVH7xtME=
*/