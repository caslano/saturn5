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
sSHG0cmjy6xtJN5o6rueH7iLRfBueDpfBK+HY/r8mbIhEEzRYGF/3NVIdU08IPv3E2gEfUHfzDDE9svK3PrhzLCBLYGp9Q9BwMtmGaDh8eN1VrQLKc/QcaWyOsNNpdWliLmemA35JXoBbQdEnUTdKL9StSDGh7pdmoVTe9YeWEbNjx+q9HDQZWWaPqGJLjKGxwmOGIpKNtKasghYnvMssrbF4RjkmoP0TurWA7iSeGhQoa6Vq5zuFVaSbtT6Aaq2e5vjTyFUYLO9a7qvkn1BRV1LPqgZHrKmih1TpvMzP8CbA9RNh991O/H9s0o9p0GwI4imoAMDwn4oYpwA5kswnrteMJrP/sCtmMxnHmL06MdRds3xhKDZT4EQMc3oBB56o8mk2ppvU/l4cHrH7sJ3/9xQopAi3png8cSdjqk6HLBSmV3Z9ezesTZM/vXcc2uu70pXy7bTcYGOx+ezkY+iOI2zqRrJ1UTb9i7+kMFWWxkM8miWwYv1iKhc1z28doVmxcUF5wFLU+vetra+OQW2I9/CprUxLRr7/wNQSwMECgAAAAgALWdKUmqVxE8OCAAAtxoAACIACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU1NC5jVVQFAAG2SCRg3Vh7c9pIEv+f
*/