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
OaPm5kzxImDAXWJ0c+U9WeC/9nZXilJiKJt9M27UOJ6hE3b/ztKQqeLjlWlKBut4oYOfnq4N16znVkSFP3iQghI2Z7jF4LHeaIf6Ioe17b+Etn5m3NmMAFJP39CyhG4z14u+IDrfzlcvYW4ZVLvTFbUmKvnNauLig8tDow/Tg7rnV/alLHTWpLhl34ef8GdSE14BEUzh16gwwGLrfPdkr+UmVCNaNDVIxUkItVFLFMkw29J+hwmI1UxKA2LZQuj5I3qbRwhzj8Q0+9r4uELacEUFYTJ8ZPnvHVf1gL9uOzDTAD1bHE4Mi4WSxk3WkRJM7Y2k0MiqE5cee/EdapvDQPknPzNjK/mvn217AqcJsRhdoyfDHK1SB23mUyomtDYHK7JcT3q/DlvMPh/DTFuybYUabX7fwvMLlY8+k+jn4i0ks/2h64tZai36ndHdDYT3YGB43+qvVB934gkF5vTzXoXvrA3UHS+wlSFsEzKWkEvEWdEqUvKbWVQkRFf6+S600WzRbPVndVw0wKdNW7V+ZysHee32LMnoBTXnIxM0vl5M/UZ83n9zZq4bCA==
*/